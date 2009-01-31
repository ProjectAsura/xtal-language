#include "xtal.h"
#include "xtal_macro.h"

namespace xtal{

namespace{
	FileLib* file_lib_ = 0;
}

StringPtr Stream::get_s(uint_t length){
	if(eos())
		return empty_id;

	if(length==1){
		char_t ch;
		ChMaker chm;
		while(!chm.is_completed()){
			read(&ch, sizeof(char_t));
			chm.add(ch);
		}
		return chm.to_s();
	}

	MemoryStreamPtr ms = xnew<MemoryStream>();
	for(uint_t i=0; i<length; ++i){
		ms->put_s(get_s(1));
	}
	return ms->to_s();
}

StringPtr Stream::get_s_all(){
	if(eos())
		return empty_id;

	MemoryStreamPtr ms = xnew<MemoryStream>();
	while(!eos()){
		ms->put_s(get_s(1));
	}
	return ms->to_s();
}

uint_t Stream::read_charactors(AnyPtr* buffer, uint_t max){
	for(uint_t i=0; i<max; ++i){
		if(eos()){
			return i;
		}

		char_t ch;
		ChMaker chm;
		while(!chm.is_completed()){
			read(&ch, sizeof(char_t));
			chm.add(ch);
		}
	
		buffer[i] = chm.to_s();
	}
	return max;
}

uint_t Stream::print(const StringPtr& str){
	return write(str->data(), str->data_size()*sizeof(char_t));
}

void Stream::println(const StringPtr& str){
	write(str->data(), str->data_size()*sizeof(char_t));
	write(XTAL_STRING("\n"), sizeof(char_t)*1);
}

uint_t Stream::pour(const StreamPtr& in_stream, uint_t size){
	UserMallocGuard umg(size*sizeof(xtal::u8));
	xtal::u8* buf = (xtal::u8*)umg.get();
	uint_t len = in_stream->read(buf, size);
	write(buf, len);
	return len;
}

uint_t Stream::pour_all(const StreamPtr& in_stream){
	uint_t size = 1024*10, len, sum = 0;
	UserMallocGuard umg(size*sizeof(xtal::u8));
	xtal::u8* buf = (xtal::u8*)umg.get();
	do{
		len = in_stream->read(buf, size);
		sum += len;
		write(buf, len);
	}while(len==size);
	return sum;
}

uint_t Stream::size(){
	uint_t pos = tell();
	seek(0, XSEEK_END);
	uint_t len = tell();
	seek(pos, XSEEK_SET);
	return len;
}

void Stream::block_first(const VMachinePtr& vm){
	vm->return_result(from_this(this), from_this(this));
}

void Stream::block_next(const VMachinePtr& vm){
	vm->return_result(null, null);
	close();
}

void Stream::block_break(const VMachinePtr& vm){
	close();
}

void Stream::serialize(const AnyPtr& obj){
	Serializer s(from_this(this));
	s.serialize(obj);
}

AnyPtr Stream::deserialize(){
	Serializer s(from_this(this));
	return s.deserialize();
}

void Stream::xtalize(const AnyPtr& obj){

}

AnyPtr Stream::dextalize(){
	return null;
}

/////////////////////////////////////////////////////////////////

PointerStream::PointerStream(const void* data, uint_t size){
	static u8 temp = 0;
	if(data){
		data_ = (u8*)data;
	}
	else{
		data_ = &temp;
	}
	size_ = size;
	pos_ = 0;
}
	
uint_t PointerStream::tell(){
	return pos_;
}

uint_t PointerStream::write(const void* p, uint_t size){
	XTAL_THROW(unsupported_error(get_class(), Xid(write), null), return 0);
}

uint_t PointerStream::read(void* p, uint_t size){
	if(pos_+size>size_){ 
		uint_t diff = size_-pos_;
		if(diff>0){
			std::memcpy(p, &data_[pos_], diff);
		}
		pos_ += diff;
		return diff; 
	}
	
	if(size>0){
		std::memcpy(p, &data_[pos_], size);
	}

	pos_ += size;
	return size;
}

void PointerStream::seek(int_t offset, int_t whence){
	switch(whence){
	case XSEEK_END:
		pos_ = size_-offset;
		break;
	case XSEEK_CUR:
		pos_ += offset;
		break;
	default:
		if(offset<0){
			offset = 0;
		}
		pos_ = offset;
		break;
	}
}

StringPtr PointerStream::get_s(uint_t length){
	if(pos_ >= size_)
		return "";

	if(length==1){
		char_t ch;
		ChMaker chm;
		while(!chm.is_completed()){
			read(&ch, sizeof(char_t));
			chm.add(ch);
		}
		return chm.to_s();
	}

	uint_t saved = pos_;

	uint_t slen = 0;
	char_t ch;
	ChMaker chm;
	while(slen<length){
		chm.clear();
		while(!chm.is_completed()){
			read(&ch, sizeof(char_t));
			chm.add(ch);
		}
		slen += 1;
	}

	return xnew<String>((char_t*)&data_[saved], (pos_ - saved)/sizeof(char_t));	
}

StringPtr PointerStream::get_s_all(){
	if(pos_ >= size_)
		return empty_id;

	char_t* data = (char_t*)data_;
	StringPtr ret = xnew<String>((char_t*)&data[pos_], size_ - pos_);
	pos_ = size_;
	return ret;
}

bool PointerStream::eos(){
	return pos_>=size_;
}

///////////////////////////////////////////////////////////////

MemoryStream::MemoryStream(){
	pos_ = 0;
	capa_ = 0;
}

MemoryStream::MemoryStream(const void* data, uint_t data_size){
	pos_ = 0;
	capa_ = 0;
	resize(data_size);
	std::memcpy((void*)data_, data, data_size);
}

MemoryStream::~MemoryStream(){
	if(capa_){
		user_free((void*)data_);
	}
}

uint_t MemoryStream::write(const void* p, uint_t size){
	if(pos_+size>capa_){
		resize(pos_+size);
	}
	else{
		size_ = pos_+size;
	}

	std::memcpy((void*)&data_[pos_], p, size);

	pos_ += size;

	return size;	
}

uint_t MemoryStream::pour(const StreamPtr& in_stream, uint_t size){
	if(size==0){
		return 0;
	}

	resize(pos_+size);

	uint_t len = in_stream->read((void*)&data_[pos_], size);
	resize(size_ - (size - len));
	pos_ += len;
	return len;
}

uint_t MemoryStream::pour_all(const StreamPtr& in_stream){
	uint_t size = 1024*10, len, sum = 0;
	do{
		if(size_ <= pos_ + size){
			resize(pos_+size);
		}

		len = in_stream->read((void*)&data_[pos_], size);
		sum += len;
	}while(len==size);
	resize(size_ - (size - len));
	pos_ += sum;
	return sum;
}

StringPtr MemoryStream::to_s(){
	return xnew<String>((char_t*)data_, size_/sizeof(char_t));
}

void MemoryStream::clear(){
	seek(0);
	resize(0);
}

void MemoryStream::resize(uint_t size){
	if(size>capa_){
		uint_t newcapa = size + capa_;
		void* newp = user_malloc(newcapa);
		std::memcpy(newp, data_, size_);
		if(capa_){
			user_free((void*)data_);
		}
		data_ = (u8*)newp;
		capa_ = newcapa;
	}
	size_ = size;
}

//////////////////////////////////////////////////////////////////////////

StringStream::StringStream(const StringPtr& str)
:str_(str ? str : unchecked_ptr_cast<String>(empty_id)){
	data_ = (u8*)str_->data();
	size_ = str_->data_size()*sizeof(char_t);
	pos_ = 0;
}

/////////////////////////////////////////////////////////////////////

InteractiveStream::InteractiveStream(){
	line_ = 1;
	continue_stmt_ = false;
	fp_ = stdin;
}

uint_t InteractiveStream::tell(){
	XTAL_THROW(unsupported_error(get_cpp_class<InteractiveStream>(), Xid(tell), null), return 0);
}

uint_t InteractiveStream::write(const void* p, uint_t size){
	XTAL_THROW(unsupported_error(get_cpp_class<InteractiveStream>(), Xid(write), null), return 0);
}

uint_t InteractiveStream::read(void* p, uint_t size){
	if(!fp_)
		return 0;
	if(continue_stmt_){
		stdout_stream()->put_s(Xf("ix:%03d>    ")->call(line_)->to_s());
	}
	else{
		stdout_stream()->put_s(Xf("ix:%03d>")->call(line_)->to_s());
	}

	continue_stmt_ = true;
	if(fgets((char*)p, size, stdin)){
		uint_t sz = std::strlen((char*)p);
		if(sz!=size-1){
			line_++;
		}
		return sz;
	}
	fp_ = 0;
	return 0;
}

void InteractiveStream::seek(int_t offset, int_t whence){
	XTAL_THROW(unsupported_error(get_cpp_class<InteractiveStream>(), Xid(seek), null), return);
}

void InteractiveStream::close(){
	if(fp_){
		fclose(fp_);
		fp_ = 0;
	}
}

void InteractiveStream::terminate_statement(){
	continue_stmt_ = false;
}

///////////////////////////////////////////////////////////

StdioStream::StdioStream(std::FILE* fp){
	fp_ = fp;
}

StdioStream::~StdioStream(){
	close();
}

uint_t StdioStream::tell(){
	if(!fp_){ XTAL_THROW(builtin()->member(Xid(IOError))->call(Xt("Xtal Runtime Error 1018")), return 0); }

	return ftell(fp_);
}

uint_t StdioStream::write(const void* p, uint_t size){
	if(!fp_){ XTAL_THROW(builtin()->member(Xid(IOError))->call(Xt("Xtal Runtime Error 1018")), return 0); }

	XTAL_UNLOCK{
#ifdef XTAL_USE_WCHAR
		char_t buf[256];
		XTAL_SPRINTF(buf, 256, L"%%.%ds", size/sizeof(char_t));
		uint_t ret = fwprintf(fp_, buf, p);
#else
		uint_t ret = fwrite(p, size, 1, fp_);
#endif
		fflush(fp_);
		return ret;
	}
	return 0;
}

uint_t StdioStream::read(void* p, uint_t size){
	if(!fp_){ XTAL_THROW(builtin()->member(Xid(IOError))->call(Xt("Xtal Runtime Error 1018")), return 0); }

	XTAL_UNLOCK{
		return fread(p, 1, size, fp_);
	}
	return 0;
}

void StdioStream::seek(int_t offset, int_t whence){
	if(!fp_){ XTAL_THROW(builtin()->member(Xid(IOError))->call(Xt("Xtal Runtime Error 1018")), return); }

	int wh = whence==XSEEK_END ? SEEK_END : whence==XSEEK_CUR ? SEEK_CUR : SEEK_SET;
	fseek(fp_, offset, wh);
}

void StdioStream::close(){
	if(fp_){
		fclose(fp_);
		fp_ = 0;
	}
}

bool StdioStream::eos(){
	if(!fp_){ return true; }
	int ch = getc(fp_);
	if(feof(fp_)){
		return true;
	}
	ungetc(ch, fp_);
	return false;
}

class CStdioFileLib : public FileLib{
public:

	virtual void initialize(){}

	virtual StreamPtr open(const char_t* file_name, const char_t* flags){
#ifdef XTAL_USE_WCHAR
		FILE* fp = _wfopen(file_name, flags);
#else
		FILE* fp = std::fopen(file_name, flags);
#endif
		if(!fp){ XTAL_THROW(builtin()->member(Xid(IOError))->call(Xt("Xtal Runtime Error 1014")->call(Named(Xid(name), file_name))), return null); }
		return xnew<StdioStream>(fp);
	}

} cstdio_file_lib;

void set_file(){
	file_lib_ = &cstdio_file_lib;
}

void set_file(FileLib& lib){
	file_lib_ = &lib;
}

StreamPtr open(const StringPtr& file_name, const StringPtr& aflags){
	const char_t* flags = aflags->c_str();
	char_t flags_temp[16];
	bool text = false;
	uint_t i = 0;
	for(; flags[i]!=0 && i<10; ++i){
		if(flags[i]=='t'){
			text = true;
		}
		else{
			flags_temp[i] = flags[i];
		}
	}

	if(!text){
		flags_temp[i++] = 'b';
	}
	flags_temp[i++] = 0;
	
	return file_lib_->open(file_name->c_str(), flags_temp);
}

void initialize_stream(){
	if(!file_lib_){
		set_file();
	}

	{
		ClassPtr p = new_cpp_class<Stream>(Xid(Stream));
		
		p->method(Xid(get_s), &Stream::get_s);
		p->method(Xid(get_s_all), &Stream::get_s_all);
		p->method(Xid(put_s), &Stream::put_s);

		p->method(Xid(print), &Stream::print);
		p->method(Xid(println), &Stream::println);

		p->method(Xid(seek), &Stream::seek)->params(null, null, Xid(whence), Stream::XSEEK_SET);
		p->method(Xid(tell), &Stream::tell);
		p->method(Xid(pour), &Stream::pour);
		p->method(Xid(pour_all), &Stream::pour_all);
		p->method(Xid(size), &Stream::size);
		p->method(Xid(close), &Stream::close);

		p->method(Xid(eos), &Stream::eos);

		p->method(Xid(serialize), &Stream::serialize);
		p->method(Xid(deserialize), &Stream::deserialize);
		p->method(Xid(xtalize), &Stream::xtalize);
		p->method(Xid(dextalize), &Stream::dextalize);

		p->method(Xid(block_first), &Stream::block_first);
		p->method(Xid(block_next), &Stream::block_next);
		p->method(Xid(block_break), &Stream::block_break);

		p->def(Xid(SEEK_SET), Stream::XSEEK_SET);
		p->def(Xid(SEEK_CUR), Stream::XSEEK_CUR);
		p->def(Xid(SEEK_END), Stream::XSEEK_END);
	}

	{
		ClassPtr p = new_cpp_class<MemoryStream>(Xid(MemoryStream));
		p->inherit(get_cpp_class<Stream>());
		p->def(Xid(new), ctor<MemoryStream>());
		p->method(Xid(to_s), &MemoryStream::to_s);
		p->method(Xid(resize), &MemoryStream::resize);
	}

	{
		ClassPtr p = new_cpp_class<StringStream>(Xid(StringStream));
		p->inherit(get_cpp_class<Stream>());
		p->def(Xid(new), ctor<StringStream, const StringPtr&>());
		p->method(Xid(to_s), &StringStream::to_s);
	}

	{
		ClassPtr p = new_cpp_class<StdioStream>(Xid(StdioStream));
		p->inherit(get_cpp_class<Stream>());
	}

	builtin()->def(Xid(Stream), get_cpp_class<Stream>());
	builtin()->def(Xid(StdioStream), get_cpp_class<StdioStream>());
	builtin()->def(Xid(MemoryStream), get_cpp_class<MemoryStream>());
	builtin()->def(Xid(StringStream), get_cpp_class<StringStream>());

	if(stdin){
		builtin()->def(Xid(stdin), xnew<StdioStream>(stdin));
	}

	if(stdout){
		builtin()->def(Xid(stdout), xnew<StdioStream>(stdout));
	}

	if(stderr){
		builtin()->def(Xid(stderr), xnew<StdioStream>(stderr));
	}
}

void initialize_stream_script(){
	Xemb((

Stream::scan: method(pattern) fiber{
	exec: xpeg::Executor(this);
	while(exec.match(pattern)){
		yield exec;
	}
}

Stream::split: method(pattern) fiber{
	exec: xpeg::Executor(this);
	if(exec.match(pattern)){
		yield exec.prefix;
		while(exec.match(pattern)){
			yield exec.prefix;
		}
		yield exec.suffix;
	}
	else{
		yield this.to_s;
	}
}
	),
		""
	)->call();
}

}
