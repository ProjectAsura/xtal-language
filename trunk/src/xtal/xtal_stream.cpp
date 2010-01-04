#include "xtal.h"
#include "xtal_macro.h"

#include "xtal_serializer.h"

namespace xtal{

uint_t Stream::tell(){
	XTAL_SET_EXCEPT(unsupported_error(get_class(), Xid(tell), null));
	return 0;
}

uint_t Stream::write(const void* p, uint_t size){
	XTAL_SET_EXCEPT(unsupported_error(get_class(), Xid(write), null));
	return 0;
}

uint_t Stream::read(void* p, uint_t size){
	XTAL_SET_EXCEPT(unsupported_error(get_class(), Xid(read), null));
	return 0;
}

void Stream::seek(uint_t offset){
	XTAL_SET_EXCEPT(unsupported_error(get_class(), Xid(seek), null));
}

StringPtr Stream::get_s(uint_t length){
	if(eos()){
		return empty_string;
	}

	if(length==1){
		return get_ch();
	}

	MemoryStreamPtr ms = xnew<MemoryStream>();
	for(uint_t i=0; i<length; ++i){
		ms->put_s(get_s(1));
	}

	return ms->to_s();
}

StringPtr Stream::get_ch(){
	char_t ch;
	ChMaker chm;
	while(!chm.is_completed()){
		read(&ch, sizeof(char_t));
		chm.add(ch);
	}
	return chm.to_s();
}

StringPtr Stream::get_s_all(){
	if(eos()){
		return empty_string;
	}

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

void Stream::read_strict(void* p, uint_t size){
	uint_t read = 0;
	while(true){
		int temp = this->read((char*)p+read, size-read);

		if(temp<=0){
			XTAL_SET_EXCEPT(cpp_class<EOSError>()->call(Xt("XRE1033")));
			return;
		}

		read += temp;

		if(read==size){
			break;
		}
	}
}

uint_t Stream::print(const AnyPtr& value){
	StringPtr str = value->to_s(); 
	return write(str->data(), str->data_size()*sizeof(char_t));
}

void Stream::println(const AnyPtr& value){
	StringPtr str = value->to_s(); 
	write(str->data(), str->data_size()*sizeof(char_t));
	write(XTAL_STRING("\n"), sizeof(char_t)*1);
}

uint_t Stream::pour(const StreamPtr& in_stream, uint_t size){
	XMallocGuard umg(size*sizeof(xtal::u8));
	xtal::u8* buf = (xtal::u8*)umg.get();
	uint_t len = in_stream->read(buf, size);
	write(buf, len);
	return len;
}

uint_t Stream::pour_all(const StreamPtr& in_stream){
	uint_t size = 1024*10, len, sum = 0;
	XMallocGuard umg(size*sizeof(xtal::u8));
	xtal::u8* buf = (xtal::u8*)umg.get();
	do{
		len = in_stream->read(buf, size);
		sum += len;
		write(buf, len);
	}while(len==size);
	return sum;
}

uint_t Stream::size(){
	XTAL_SET_EXCEPT(unsupported_error(get_class(), Xid(size), null));
	return 0;
}

void Stream::block_first(const VMachinePtr& vm){
	vm->return_result(to_smartptr(this), to_smartptr(this));
}

void Stream::block_next(const VMachinePtr& vm){
	vm->return_result(null, null);
	close();
}

void Stream::block_break(const VMachinePtr& vm){
	close();
}

void Stream::serialize(const AnyPtr& obj){
	Serializer s(to_smartptr(this));
	s.serialize(obj);
}

AnyPtr Stream::deserialize(){
	Serializer s(to_smartptr(this));
	return s.deserialize();
}

void Stream::put_u16be(u16 v){
	struct{ u8 data[2]; } data;
	data.data[0] = (u8)(v>>8);
	data.data[1] = (u8)(v>>0);
	write(data.data, 2);
}

void Stream::put_u16le(u16 v){
	struct{ u8 data[2]; } data;
	data.data[1] = (u8)(v>>8);
	data.data[0] = (u8)(v>>0);
	write(data.data, 2);
}

void Stream::put_u32be(u32 v){
	struct{ u8 data[4]; } data;
	data.data[0] = (u8)(v>>24);
	data.data[1] = (u8)(v>>16);
	data.data[2] = (u8)(v>>8);
	data.data[3] = (u8)(v>>0);
	write(data.data, 4);
}

void Stream::put_u32le(u32 v){
	struct{ u8 data[4]; } data;
	data.data[3] = (u8)(v>>24);
	data.data[2] = (u8)(v>>16);
	data.data[1] = (u8)(v>>8);
	data.data[0] = (u8)(v>>0);
	write(data.data, 4);
}

void Stream::put_u64be(u64 v){
	struct{ u8 data[8]; } data;
	data.data[0] = (u8)(v>>56);
	data.data[1] = (u8)(v>>48);
	data.data[2] = (u8)(v>>40);
	data.data[3] = (u8)(v>>32);
	data.data[4] = (u8)(v>>24);
	data.data[5] = (u8)(v>>16);
	data.data[6] = (u8)(v>>8);
	data.data[7] = (u8)(v>>0);
	write(data.data, 8);
}

void Stream::put_u64le(u64 v){
	struct{ u8 data[8]; } data;
	data.data[7] = (u8)(v>>56);
	data.data[6] = (u8)(v>>48);
	data.data[5] = (u8)(v>>40);
	data.data[4] = (u8)(v>>32);
	data.data[3] = (u8)(v>>24);
	data.data[2] = (u8)(v>>16);
	data.data[1] = (u8)(v>>8);
	data.data[0] = (u8)(v>>0);
	write(data.data, 8);
}

u16 Stream::get_u16be(){
	struct{ u8 data[2]; } data = {0};
	read_strict(data.data, 2);
	return (u16)((data.data[0]<<8) | data.data[1]);
}

u16 Stream::get_u16le(){
	struct{ u8 data[2]; } data = {0};
	read_strict(data.data, 2);
	return (u16)((data.data[1]<<8) | data.data[0]);
}

u32 Stream::get_u32be(){
	struct{ u8 data[4]; } data = {0};
	read_strict(data.data, 4);
	return (u32)((data.data[0]<<24) | (data.data[1]<<16) | (data.data[2]<<8) | data.data[3]);
}

u32 Stream::get_u32le(){
	struct{ u8 data[4]; } data = {0};
	read_strict(data.data, 4);
	return (u32)((data.data[3]<<24) | (data.data[2]<<16) | (data.data[1]<<8) | data.data[0]);
}

u64 Stream::get_u64be(){
	struct{ u8 data[8]; } data = {0};
	read_strict(data.data, 8);
	return (u64)(((u64)data.data[0]<<56) | ((u64)data.data[1]<<48) | ((u64)data.data[2]<<40) | ((u64)data.data[3]<<32) | (data.data[4]<<24) | (data.data[5]<<16) | (data.data[6]<<8) | data.data[7]);
}

u64 Stream::get_u64le(){
	struct{ u8 data[8]; } data = {0};
	read_strict(data.data, 8);
	return (u64)(((u64)data.data[7]<<56) | ((u64)data.data[6]<<48) | ((u64)data.data[5]<<40) | ((u64)data.data[4]<<32) | (data.data[3]<<24) | (data.data[2]<<16) | (data.data[1]<<8) | data.data[0]);
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

uint_t PointerStream::read(void* p, uint_t size){
	if(pos_+size>size_){ 
		size = size_-pos_;
	}
	
	if(size>0){
		std::memcpy(p, &data_[pos_], size);
	}

	pos_ += size;
	return size;
}

void PointerStream::seek(uint_t offset){
	pos_ = offset;
}

StringPtr PointerStream::get_s(uint_t length){
	if(pos_ >= size_)
		return empty_string;

	if(length==1){
		return get_ch();
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
		return empty_string;

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
		xfree((void*)data_, capa_);
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
		uint_t newcapa = size + capa_*2;
		void* newp = xmalloc(newcapa);
		std::memcpy(newp, data_, size_);
		if(capa_){
			xfree((void*)data_, capa_);
		}
		data_ = (u8*)newp;
		capa_ = newcapa;
	}
	size_ = size;
}

//////////////////////////////////////////////////////////////////////////

StringStream::StringStream(const StringPtr& str)
:str_(str ? str : empty_string){
	data_ = (u8*)str_->data();
	size_ = str_->data_size()*sizeof(char_t);
	pos_ = 0;
}

//////////////////////////////////////////////////////////////////////////

void FileStream::open(const StringPtr& path, const StringPtr& aflags){
	close();

	const char_t* flags = aflags->data();
	char_t flags_temp[256];
	bool text = false;
	uint_t i = 0;
	uint_t sz = aflags->data_size();
	for(; flags[i]!=0 && i<sz; ++i){
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

	impl_ = filesystem_lib()->new_file_stream(path->c_str(), flags_temp);
}

////////////////////////////////////////////////////////////////////////////

uint_t InteractiveStream::read(void* p, uint_t size){
	if(continue_stmt_){
		stdout_stream()->put_s(format(XTAL_STRING("ix:%03d>    "))->call(line_)->to_s());
	}
	else{
		stdout_stream()->put_s(format(XTAL_STRING("ix:%03d>"))->call(line_)->to_s());
	}

	continue_stmt_ = true;
	if(uint_t sz = read_line(p, size)){
		if(sz!=size-1){
			line_++;
		}
		return sz;
	}
	return 0;
}

uint_t InteractiveStream::read_line(void* p, uint_t size){
	ChMaker chm;
	char_t ch;
	uint_t sz = 0;
	do{
		chm.clear();
		while(!chm.is_completed()){
			if(stdin_stream()->read((char_t*)p+sz, sizeof(ch))!=sizeof(ch)){
				return sz*sizeof(ch);
			}
			chm.add(*((char_t*)p+sz));
			sz++;
		}
	}while(chm.data()[0]!='\n');

	return sz*sizeof(ch);
}

}
