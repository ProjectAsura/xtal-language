#include "xtal.h"
#include "xtal_macro.h"

namespace xtal{

class FormatSpecifier : public Base{
public:

	enum{ BUF_MAX = 20, REAL_BUF_MAX = BUF_MAX + 2 };
	
	char_t buf_[REAL_BUF_MAX];
	char_t type_;
	int_t pos_, width_, precision_;
	
public:

	enum{ FORMAT_SPECIFIER_MAX = 20 };
	
	int_t type();
	int_t max_buffer_size();

	char_t change_int_type();
	char_t change_float_type();
	
	void make_format_specifier(char_t* dest, char_t type, bool int_type = false);

	const char_t* parse_format(const char_t* str);

private:
	
	const char_t* parse_format_inner(const char_t* str);

};

class Format : public Base{
public:

	Format(const StringPtr& str = empty_id);
	void set(const char_t* str);
	virtual void rawcall(const VMachinePtr& vm);
	void to_s(const VMachinePtr& vm);
	AnyPtr serial_save();
	void serial_load(const StringPtr& v);

private:

	MapPtr values_;
	StringPtr original_;
	bool have_named_;
	
	virtual void visit_members(Visitor& m){
		Base::visit_members(m);
		m & values_ & original_;
	}
};

class Text : public Base{
public:

	Text(const StringPtr& key = empty_id);
	virtual void rawcall(const VMachinePtr& vm);
	void to_s(const VMachinePtr& vm);
	AnyPtr serial_save();
	void serial_load(const StringPtr& v);

private:	
	StringPtr key_;
};


void assign_text_map(const AnyPtr& map){
	MapPtr m = ptr_cast<Map>(builtin()->member(Xid(_text_map)));
	m->assign(map);
}

void append_text_map(const AnyPtr& map){
	MapPtr m = ptr_cast<Map>(builtin()->member(Xid(_text_map)));
	m->concat(map);
}

AnyPtr text(const StringPtr& text){
	return xnew<Text>(text);
}

AnyPtr format(const StringPtr& text){
	return xnew<Format>(text);
}


char_t FormatSpecifier::change_int_type(){
	switch(type_){
	case 'i': case 'd': case 'x': case 'X':
		return type_;
		break;
	
	default:
		return 'i';
		break;
	}
}

char_t FormatSpecifier::change_float_type(){
	switch(type_){
	case 'e': case 'E': case 'g':
	case 'G': case 'f':
		return type_;
		break;
	
	default:
		return 'g';
		break;
	}
}
	
int_t FormatSpecifier::type(){
	return type_;
}

int_t FormatSpecifier::max_buffer_size(){
	return width_ + precision_;
}

void FormatSpecifier::make_format_specifier(char_t* dest, char_t type, bool int_type){
	*dest++ = '%';

	{ // �����w��q�𖄂ߍ���
		const char_t* src = buf_;
		while(*dest++ = *src++){}
		--dest;
	}

	if(int_type){ // int_t ��64-bit�̎��ɓ��ʂȏ����w��q�𖄂ߍ���
		const char_t* src = XTAL_INT_FMT;
		while(*dest++ = *src++){}
		--dest;
	}

	*dest++ = type;
	*dest++ = 0;
}

const char_t* FormatSpecifier::parse_format(const char_t* str){
	width_ = 0;
	precision_ = 0;
	pos_ = 0;		
	str = parse_format_inner(str);
	if(*str) type_ = *str++;
	buf_[pos_] = '\0';
	return str;
}

const char_t* FormatSpecifier::parse_format_inner(const char_t* str){

	while(str[0]){
		switch(str[0]){
		case '-': case '+': case '0': case ' ': case '#':
			buf_[pos_++] = *str++;
			if(pos_ == BUF_MAX){
				return str;
			}
			continue;
		}
		break;
	}
	
	width_ = 0;
	while(str[0]){
		if(str[0]>='0' && str[0]<= '9'){
			width_ *= 10;
			width_ += str[0]-'0';
			buf_[pos_++] = *str++; 
			if(pos_ == BUF_MAX){
				return str;
			}
		}
		else{
			break;
		}
	}

	if(str[0]=='.'){	
		buf_[pos_++] = *str++; 
		if(pos_ == BUF_MAX){
			return str;
		}
		
		precision_ = 0;
		while(str[0]){
			if(str[0]>='0' && str[0]<= '9'){
				precision_ *= 10;
				precision_ += str[0]-'0';
				buf_[pos_++] = *str++; 
				if(pos_ == BUF_MAX){
					return str;
				}
			}
			else{
				break;
			}
		}
	}

	return str;
}

Format::Format(const StringPtr& str){
	set(str->c_str());
}

void Format::set(const char_t* str){

	values_ = xnew<Map>();
	original_ = xnew<String>(str);
	have_named_ = false;

	const char_t* begin = str;
	char_t buf[256];
	int_t bufpos = 0, n = 0;
	while(true){
		if(str[0]=='%'){
			values_->set_at((int_t)values_->size(), xnew<String>(begin, str));
			str++;
			
			if(str[0]=='%'){
				begin = str++;
			}
			else{
				if(str[0]=='('){
					str++;
					bufpos = 0;
					
					if(!test_digit(str[0])){
						have_named_ = true;
					}

					while(str[0]!=0 && str[0]!=')' && bufpos!=255){
						buf[bufpos++] = str[0];
						str++;					
					}

					if(str[0]==')'){
						str++;
					}

					buf[bufpos++] = 0;
				}
				else{
					bufpos = XTAL_SPRINTF(buf, 256-bufpos, XTAL_STRING("%d"), (u32)n++);
				}

				SmartPtr<FormatSpecifier> ret = xnew<FormatSpecifier>();
				str = ret->parse_format(str);
				values_->set_at(buf, ret);
				begin = str;
			}
		}
		else if(str[0]=='\0'){
			values_->set_at((int_t)values_->size(), xnew<String>(begin, str));
			break;
		}
		else{
			str++;
		}
	}
}

void Format::rawcall(const VMachinePtr& vm){

	if(!have_named_){
		vm->flatten_arg();
	}

	MemoryStreamPtr ms = xnew<MemoryStream>();
	char_t cbuf[256];
	char_t spec[FormatSpecifier::FORMAT_SPECIFIER_MAX];
	char_t* pcbuf;
	
	Xfor2(k, v, values_){
		if(type(k)==TYPE_INT){
			ms->put_s(v->to_s());
		}
		else{
			AnyPtr a = vm->arg(k->to_s()->intern());
			if(!a){
				a = vm->arg(k->to_i());
			}
			
			SmartPtr<FormatSpecifier> fs = xnew<FormatSpecifier>(*ptr_cast<FormatSpecifier>(v));
			size_t malloc_size = 0;
			if(fs->max_buffer_size()>=256){
				malloc_size = fs->max_buffer_size() + 1;
				pcbuf = (char_t*)user_malloc(malloc_size);
			}
			else{
				pcbuf = cbuf;
			}
			
			switch(type(a)){
				XTAL_DEFAULT{
					StringPtr str = a->to_s();
					
					if(str->data_size()>=256){
						if(str->data_size()>malloc_size){
							if(malloc_size!=0){
								user_free(pcbuf);
							}
							
							malloc_size = str->data_size() + fs->max_buffer_size() + 1;
							pcbuf = (char_t*)user_malloc(malloc_size);
						}
					}
					fs->make_format_specifier(spec, 's');
					XTAL_SPRINTF(pcbuf, malloc_size ? malloc_size : 255, spec, str->c_str());
					ms->put_s(pcbuf);
				}

				XTAL_CASE(TYPE_NULL){
					ms->put_s(XTAL_STRING("<null>"));
				}

				XTAL_CASE(TYPE_INT){
					fs->make_format_specifier(spec, fs->change_int_type(), true);
					XTAL_SPRINTF(pcbuf, malloc_size ? malloc_size : 255, spec, ivalue(a));
					ms->put_s(pcbuf);
				}
				
				XTAL_CASE(TYPE_FLOAT){
					fs->make_format_specifier(spec, fs->change_float_type());
					XTAL_SPRINTF(pcbuf, malloc_size ? malloc_size : 255, spec, (double)fvalue(a));
					ms->put_s(pcbuf);
				}
			}
			
			if(malloc_size!=0){
				user_free(pcbuf);
			}
		}
	}

	vm->return_result(ms->to_s());
}

void Format::to_s(const VMachinePtr& vm){
	rawcall(vm);
}

AnyPtr Format::serial_save(){
	return original_;
}

void Format::serial_load(const StringPtr& v){
	set(v->c_str());
}

Text::Text(const StringPtr& key)
	:key_(key){}

void Text::rawcall(const VMachinePtr& vm){
	MapPtr m = ptr_as<Map>(builtin()->member(Xid(_text_map)));
	if(m){
		if(const AnyPtr& value=m->at(key_)){
			xnew<Format>(value->to_s())->rawcall(vm);
			return;
		}
	}
	
	vm->return_result(key_);
}

void Text::to_s(const VMachinePtr& vm){
	rawcall(vm);
}

AnyPtr Text::serial_save(){
	return key_;
}

void Text::serial_load(const StringPtr& v){
	key_ = v;
}


///////////////////////////////////////////////////////////////


void initialize_text(){
	builtin()->def(Xid(_text_map), xnew<Map>());

	{
		ClassPtr p = new_cpp_class<Format>(Xid(Format));
		p->def_method(Xid(to_s), &Format::to_s);
		p->def_method(Xid(serial_save), &Format::serial_save);
		p->def_method(Xid(serial_load), &Format::serial_load);
		p->def(Xid(serial_new), ctor<Format>());
	}

	{
		ClassPtr p = new_cpp_class<Text>(Xid(Text));
		p->def_method(Xid(to_s), &Text::to_s);
		p->def_method(Xid(serial_save), &Text::serial_save);
		p->def_method(Xid(serial_load), &Text::serial_load);
		p->def(Xid(serial_new), ctor<Text>());
	}

	builtin()->def(Xid(Format), get_cpp_class<Format>());
	builtin()->def(Xid(Text), get_cpp_class<Text>());

	builtin()->def_fun(Xid(assign_text_map), &assign_text_map);
	builtin()->def_fun(Xid(append_text_map), &append_text_map);
	builtin()->def_fun(Xid(format), &format);
	builtin()->def_fun(Xid(text), &text);
}

void initialize_text_script(){
	AnyPtr texts = Xemb((
return [
	"Xtal Compile Error 1001":"�\���G���[�ł��B",
	"Xtal Compile Error 1002":"�\�����ʕ��� '%(char)s' �����o����܂����B",
	"Xtal Compile Error 1003":"';' ������܂���B",
	"Xtal Compile Error 1004":"�s���Ȋ֐��̉������ł��B",
	"Xtal Compile Error 1005":"�񖼑O�t�����������O�t�������̌�ɂ���܂��B",

	"Xtal Compile Error 1006":"�s����break���A�܂���continue���ł��B",

	"Xtal Compile Error 1008":"�s���ȑ��d������ł��B",
	"Xtal Compile Error 1009":"��`����Ă��Ȃ��ϐ� '%(name)s' �ɑ�����悤�Ƃ��܂��� �B",
	"Xtal Compile Error 1010":"�s���Ȑ������e�����̃T�t�B�b�N�X�ł��B",
	"Xtal Compile Error 1011":"�����񃊃e�����̓r���Ńt�@�C�����I���܂����B",
	"Xtal Compile Error 1012":"�s���ȑ�����̍��ӂł��B",
	"Xtal Compile Error 1013":"��r���Z���̌��ʂ����Z���悤�Ƃ��Ă��܂��B",
	"Xtal Compile Error 1014":"�s���ȕ��������_�����e�����ł��B",
	"Xtal Compile Error 1015":"�s����%(n)d�i���l���e�����̃T�t�B�b�N�X�ł��B",
	"Xtal Compile Error 1016":"assert���̈����̐����s���ł��B",
	"Xtal Compile Error 1017":"�s����%%�L�@���e�����ł��B",
	"Xtal Compile Error 1018":"default�߂��d����`����܂����B",
	
	"Xtal Compile Error 1019":"'%(name)s'�͑���s�\�ł��B",

	"Xtal Compile Error 1021":"�R�����g�̓r���Ńt�@�C�����I���܂����B",
	"Xtal Compile Error 1022":"�֐�����Ԃ��鑽�l�̍ő��255�ł��B",
	"Xtal Compile Error 1023":"��`����Ă��Ȃ��C���X�^���X�ϐ��� '%(name)s' ���Q�Ƃ��Ă��܂��B",
	"Xtal Compile Error 1024":"�����̃C���X�^���X�ϐ��� '%(name)s' �����ɒ�`����Ă��܂��B",
	"Xtal Compile Error 1025":"��r���Z���̌��ʂ��Ŕ�r���悤�Ƃ��Ă��܂��B",
	"Xtal Compile Error 1026":"�����X�R�[�v���ŁA�����ϐ��� '%(name)s' �����ɒ�`����Ă��܂��B",
	"Xtal Compile Error 1027":"�R�[�h���傫�����āA�o�C�g�R�[�h�̐����Ɏ��s���܂����B",
	"Xtal Compile Error 1028":"���Z�q�̑O��̋󔒂Ɖ��Z�q�̗D�揇�ʂ���v���Ă��܂���B�z�肵�Ă���D�揇�ʂƈقȂ��Ă���\��������܂��B",
	
	"Xtal Runtime Error 1001":"%(object)s �֐��Ăяo���� '%(no)s'�Ԗڂ̈����̌^���s���ł��B",
	"Xtal Runtime Error 1002":"eval�ɓn���ꂽ�\�[�X�̃R���p�C�����A�R���p�C���G���[���������܂����B",
	"Xtal Runtime Error 1003":"�s���ȃC���X�^���X�ϐ��̎Q�Ƃł��B",
	"Xtal Runtime Error 1004":"�^�G���[�ł��B '%(required)s'�^��v�����Ă��܂����A'%(type)s'�^�̒l���n����܂����B",
	"Xtal Runtime Error 1005":"'%(object)s' �֐��Ăяo���̈����̐����s���ł��B%(min)s�ȏ�̈������󂯎��֐��ɁA%(value)s�̈�����n���܂����B",
	"Xtal Runtime Error 1006":"'%(object)s' �֐��Ăяo���̈����̐����s���ł��B%(min)s�ȏ�A%(max)s�ȉ��̈������󂯎��֐��ɁA%(value)s�̈�����n���܂����B",
	"Xtal Runtime Error 1007":"'%(object)s' �֐��Ăяo���̈����̐����s���ł��B���������Ȃ��֐��ɁA%(value)s�̈�����n���܂����B",
	"Xtal Runtime Error 1008":"'%(object)s'�̓V���A���C�Y�ł��܂���B",
	"Xtal Runtime Error 1009":"�s���ȃR���p�C���ς�Xtal�t�@�C���ł��B",
	"Xtal Runtime Error 1010":"�R���p�C���G���[���������܂����B",
	"Xtal Runtime Error 1011":"%(object)s�͊��ɒ�`����Ă��܂��B",
	"Xtal Runtime Error 1012":"yield��fiber�̔���s���Ɏ��s����܂����B",
	"Xtal Runtime Error 1013":"%(object)s :: new �֐����o�^����Ă��Ȃ����߁A�C���X�^���X�𐶐��ł��܂���B",
	"Xtal Runtime Error 1014":"�t�@�C�� '%(name)s' ���J���܂���B",
	"Xtal Runtime Error 1015":"%(object)s �͒�`����Ă��܂���B",
	"Xtal Runtime Error 1016":"�t�@�C�� '%(name)s' �̃R���p�C�����A�R���p�C���G���[���������܂����B",
	"Xtal Runtime Error 1017":"%(object)s �� %(accessibility)s �ł��B",
	"Xtal Runtime Error 1018":"���ɕ���ꂽ�X�g���[���ł��B",
	"Xtal Runtime Error 1019":"C++�Œ�`���ꂽ�N���X�̑��d�p���͏o���܂���B",
	"Xtal Runtime Error 1020":"�z��͈̔͊O�A�N�Z�X�ł��B",
	"Xtal Runtime Error 1021":"%(object)s �͒�`����Ă��܂���B'%(pick)s'�ƊԈႦ�Ă���\��������܂��B",
	"Xtal Runtime Error 1023":"1��蒷��������͔͈͉��Z�q�Ɏw��ł��܂���B",
	"Xtal Runtime Error 1024":"0���Z�G���[�ł��B",
	"Xtal Runtime Error 1025":"ChRange�͕�Ԃł���K�v������܂��B",
	"Xtal Runtime Error 1026":"Xeg�v�f�ɕϊ��ł��܂���B",
	"Xtal Runtime Error 1027":"cap�֐��̈������s���ł��Bcap(name: value)�Ƃ����悤�ɖ��O�t�������ɂ��邩�Acap(\"name\", value)�Ƃ����悤�ɌĂ�ł��������B",
];
	),
"\x78\x74\x61\x6c\x01\x00\x00\x00\x00\x00\x00\x4b\x39\x00\x01\x89\x00\x01\x00\x0f\x0b\x2f\x00\x00\x00\x00\x00\x02\x0b\x25\x01\x25\x00\x37\x00\x03\x39\x00\x01\x89\x00\x02\x00\x0f\x0b\x2f\x00\x00\x00\x00\x00\x04\x01\x25\x01\x25\x00\x37\x00\x05\x39\x00\x01\x89"
"\x00\x03\x00\x0f\x0b\x2f\x00\x00\x00\x00\x00\x04\x01\x25\x01\x25\x00\x37\x00\x06\x25\x00\x8b\x00\x03\x08\x00\x00\x00\x00\x00\x02\x00\x00\x00\x12\x00\x20\x00\x00\x00\x00\x00\x04\x00\x00\x00\x12\x00\x38\x00\x00\x00\x00\x00\x06\x00\x00\x00\x12\x00\x00\x00\x00"
"\x04\x00\x00\x00\x00\x03\x06\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x08\x00\x00\x00\x05\x00\x02\x00\x00\x00\x00\x00\x00\x01\x00\x00\x20\x00\x00\x00\x05\x00\x04\x00\x00\x00\x00\x00\x00\x01\x00\x00\x38\x00\x00\x00\x05\x00\x06\x00\x00\x00\x00\x00\x00\x01\x00"
"\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x14\x00\x00\x00\x00\x11\x00\x00\x00\x00\x00\x00\x00\x06\x00\x00\x00\x00\x00\x00\x00\x03\x00\x00\x00\x03\x00\x00\x00\x06\x00\x00\x00\x08\x00\x00\x00\x04\x00\x00\x00\x10\x00\x00\x00\x05\x00\x00"
"\x00\x13\x00\x00\x00\x06\x00\x00\x00\x18\x00\x00\x00\x0b\x00\x00\x00\x18\x00\x00\x00\x08\x00\x00\x00\x1b\x00\x00\x00\x0b\x00\x00\x00\x20\x00\x00\x00\x09\x00\x00\x00\x28\x00\x00\x00\x0a\x00\x00\x00\x2b\x00\x00\x00\x0b\x00\x00\x00\x30\x00\x00\x00\x10\x00\x00"
"\x00\x30\x00\x00\x00\x0d\x00\x00\x00\x33\x00\x00\x00\x10\x00\x00\x00\x38\x00\x00\x00\x0e\x00\x00\x00\x40\x00\x00\x00\x0f\x00\x00\x00\x43\x00\x00\x00\x10\x00\x00\x00\x48\x00\x00\x00\x11\x00\x00\x00\x00\x01\x0b\x00\x00\x00\x03\x09\x00\x00\x00\x06\x73\x6f\x75"
"\x72\x63\x65\x09\x00\x00\x00\x11\x74\x6f\x6f\x6c\x2f\x74\x65\x6d\x70\x2f\x69\x6e\x2e\x78\x74\x61\x6c\x09\x00\x00\x00\x0b\x69\x64\x65\x6e\x74\x69\x66\x69\x65\x72\x73\x0a\x00\x00\x00\x07\x09\x00\x00\x00\x00\x09\x00\x00\x00\x05\x4d\x75\x74\x65\x78\x09\x00\x00"
"\x00\x04\x6c\x6f\x63\x6b\x09\x00\x00\x00\x0b\x62\x6c\x6f\x63\x6b\x5f\x66\x69\x72\x73\x74\x09\x00\x00\x00\x06\x75\x6e\x6c\x6f\x63\x6b\x09\x00\x00\x00\x0a\x62\x6c\x6f\x63\x6b\x5f\x6e\x65\x78\x74\x09\x00\x00\x00\x0b\x62\x6c\x6f\x63\x6b\x5f\x62\x72\x65\x61\x6b"
"\x09\x00\x00\x00\x06\x76\x61\x6c\x75\x65\x73\x0a\x00\x00\x00\x01\x03"
)->call();

	append_text_map(ptr_cast<Map>(texts));
}

}
