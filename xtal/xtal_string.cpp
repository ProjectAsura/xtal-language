
#include "xtal.h"

#include <string.h>

#include "xtal_string.h"
#include "xtal_macro.h"
#include "xtal_stack.h"

namespace xtal{

uint_t make_hashcode(const char* p, uint_t size){
	const u8* str = (u8*)p;
	uint_t value = 3;
	for(uint_t i=0; i<size; ++i){
		value = value*137 + str[i] + (value>>16);
	}
	return value;
}

class StringSplit : public Base{
	StringPtr str_, sep_;
	uint_t index_;

	virtual void visit_members(Visitor& m){
		Base::visit_members(m);
		m & str_ & sep_;
	}

public:

	StringSplit(const StringPtr& str, const StringPtr& sep)
		:str_(str), sep_(sep), index_(0){
	}
	
	AnyPtr reset(){
		index_ = 0;
		return SmartPtr<StringSplit>::from_this(this);
	}

	void iter_next(const VMachinePtr& vm){
		if(str_->size()<=index_){
			reset();
			vm->return_result(null);
			return;
		}
		const char* sep = sep_->c_str();
		const char* str = str_->c_str();

		if(sep[0]==0){
			vm->return_result(SmartPtr<StringSplit>::from_this(this), xnew<String>(&str[index_], 1));
			index_ += 1;
			return;
		}

		for(int_t j=index_, jsz=str_->size(); j<jsz; j+=ch_len(str[j])){
			for(int_t i=0, sz=sep_->size()+1; i<sz; ++i){
				if(sep[i]==0){
					vm->return_result(SmartPtr<StringSplit>::from_this(this), xnew<String>(&str[index_], j-index_));
					index_ = j+i;
					return;
				}
				if(str[j+i]==0){
					vm->return_result(SmartPtr<StringSplit>::from_this(this), xnew<String>(&str[index_], j-index_));
					index_ = j+i;
					return;
				}
				if(str[j+i]!=sep[i]){
					break;
				}
			}
		}
		vm->return_result(SmartPtr<StringSplit>::from_this(this), xnew<String>(&str[index_], str_->size()-index_));
		index_ = str_->size();
	}
};

void InitString(){

	{
		ClassPtr p = new_cpp_class<StringSplit>("StringSplit");
		p->inherit(Iterator());
		p->method("reset", &StringSplit::reset);
		p->method("iter_first", &StringSplit::iter_next);
		p->method("iter_next", &StringSplit::iter_next);
	}

	{
		ClassPtr p = new_cpp_class<String>("String");

		p->def("new", New<String>());
		p->method("to_i", &String::to_i);
		p->method("to_f", &String::to_f);
		p->method("to_s", &String::to_s);
		p->method("clone", &String::clone);

		p->method("length", &String::length);
		p->method("size", &String::size);
		p->method("slice", &String::slice);
		p->method("intern", &String::intern);

		p->method("split", &String::split);

		p->method("op_cat", &String::op_cat);
		p->method("op_eq", &String::op_eq);
		p->method("op_lt", &String::op_lt);

		p->method("op_cat_r_String", &String::op_cat_r_String);
		p->method("op_eq_r_String", &String::op_eq_r_String);
		p->method("op_lt_r_String", &String::op_lt_r_String);
		
		p->method("op_cat_assign", &String::op_cat);
	}
}

void String::visit_members(Visitor& m){
	Base::visit_members(m);
	if((flags_ & ROPE)!=0){
		m & rope_.left & rope_.right;
	}
}

void visit_members(Visitor& m, const Named& p){
	m & p.name & p.value;
}

struct StringKey{
	const char* str;
	int_t size;

	StringKey(const char* str, int_t size)
		:str(str), size(size){}

	friend bool operator <(const StringKey& a, const StringKey& b){
		if(a.size<b.size)
			return true;
		if(a.size>b.size)
			return false;
		return memcmp(a.str, b.str, a.size)<0;
	}
};

class StringMgr : public GCObserver{
public:

	struct Node{
		uint_t hashcode;
		const char* str;
		uint_t size;
		StringPtr value;
		Node* next;

		Node()
			:value(null), next(0){}
	};


	StringMgr(){
		size_ = 0;
		begin_ = 0;
		used_size_ = 0;
		guard_ = 0;
		expand(7);
	}

	virtual ~StringMgr(){
		for(uint_t i = 0; i<size_; ++i){
			Node* p = begin_[i];
			while(p){
				Node* next = p->next;
				p->~Node();
				user_free(p, sizeof(Node));
				p = next;
			}
		}
		user_free(begin_, sizeof(Node*)*size_);
	}
		
protected:

	float_t rate(){
		return used_size_/(float_t)size_;
	}
	
	void set_node(Node* node){
		Node** p = &begin_[node->hashcode % size_];
		while(*p){
			p = &(*p)->next;
		}
		*p = node;
	}

	void expand(int_t addsize){
		Node** oldbegin = begin_;
		uint_t oldsize = size_;

		size_ = size_ + size_/2 + addsize;
		begin_ = (Node**)user_malloc(sizeof(Node*)*size_);
		for(uint_t i = 0; i<size_; ++i){
			begin_[i] = 0;
		}

		for(uint_t i = 0; i<oldsize; ++i){
			Node* p = oldbegin[i];
			while(p){
				Node* next = p->next;
				set_node(p);
				p->next = 0;
				p = next;
			}
		}
		user_free(oldbegin, sizeof(Node*)*oldsize);
	}
	
protected:

	Node** begin_;
	uint_t size_;
	uint_t used_size_;
	int_t guard_;

	struct Guard{
		int_t& count;
		Guard(int_t& c):count(c){ count++; }
		~Guard(){ count--; }
	private:
		void operator=(const Guard&);
	};

	virtual void visit_members(Visitor& m){
		Base::visit_members(m);
		for(uint_t i = 0; i<size_; ++i){
			Node* p = begin_[i];
			while(p){
				Node* next = p->next;
				m & p->value;
				p = next;
			}
		}		
	}

public:

	const StringPtr& insert(const char* str, uint_t size);

	virtual void before_gc();
};

const StringPtr& StringMgr::insert(const char* str, uint_t size){
	Guard guard(guard_);

	uint_t hashcode = make_hashcode(str, size);
	Node** p = &begin_[hashcode % size_];
	while(*p){
		if((*p)->size==size && memcmp((*p)->str, str, size)==0){
			return (*p)->value;
		}
		p = &(*p)->next;
	}

	*p = (Node*)user_malloc(sizeof(Node));
	new(*p) Node();
	
	(*p)->value = xnew<String>(str, size, hashcode);
	(*p)->hashcode = hashcode;
	(*p)->str = (*p)->value->c_str();
	(*p)->size = size;

	used_size_++;
	if(rate()>0.5f){
		expand(17);

		p = &begin_[hashcode % size_];
		while(*p){
			if((*p)->size==size && memcmp((*p)->str, str, size)==0){
				return (*p)->value;
			}
			p = &(*p)->next;
		}
		return (*p)->value;
	}else{
		return (*p)->value;
	}
}

void StringMgr::before_gc(){
	return;

	if(guard_){
		return;
	}

	for(uint_t i = 0; i<size_; ++i){
		Node* p = begin_[i];
		Node* prev = 0;
		while(p){
			Node* next = p->next;
			if(pvalue(p->value)->ref_count()==1){
				p->~Node();
				user_free(p, sizeof(Node));
				used_size_--;
				if(prev){
					prev->next = next;
				}else{
					begin_[i] = next;
				}
			}else{
				prev = p;
			}
			p = next;
		}
	}
}
	
static const SmartPtr<StringMgr>& str_mgr(){
	static LLVar<SmartPtr<StringMgr> > p = xnew<StringMgr>();
	return p;
}

void String::common_init(uint_t len){
	size_ = len;
	str_.p = static_cast<char*>(user_malloc(size_+1));
	str_.p[size_] = 0;
	flags_ = 0;
}

	
String::String(const char* str){
	common_init(strlen(str));
	memcpy(str_.p, str, size_);
}

String::String(const char* str, uint_t len){
	common_init(len);
	memcpy(str_.p, str, size_);
}

String::String(const char* begin, const char* last){
	common_init(last-begin);
	memcpy(str_.p, begin, size_);
}

String::String(const char* str1, uint_t size1, const char* str2, uint_t size2){
	common_init(size1 + size2);
	memcpy(str_.p, str1, size1);
	memcpy(str_.p+size1, str2, size2);
}

String::String(const string_t& str){
	common_init(str.size());
	memcpy(str_.p, str.c_str(), size_);
}

String::String(const char* str, uint_t len, uint_t hashcode){
	common_init(len);
	memcpy(str_.p, str, size_);
	str_.hashcode = hashcode;
	flags_ = INTERNED | HASHED;
}

String::String(char* str, uint_t len, uint_t /*buffer_size*/, delegate_memory_t){
	size_ = len;
	str_.p = str;
	flags_ = 0;
}

String::String(String* left, String* right){
	left->inc_ref_count();
	right->inc_ref_count();
	rope_.left = left;
	rope_.right = right;
	size_ = left->size() + right->size();
	flags_ = ROPE;
}

String::~String(){
	if((flags_ & ROPE)==0){
		if((flags_ & NOFREE)==0){
			user_free(str_.p, size_+1);
		}
	}else{
		rope_.left->dec_ref_count();
		rope_.right->dec_ref_count();
	}
}

const char* String::c_str(){ 
	became_unified();
	return str_.p; 
}

uint_t String::size(){ 
	return size_; 
}

uint_t String::length(){ 
	return size_; 
}

StringPtr String::slice(int_t first, int_t last){ 
	return xnew<String>(c_str()+first, last-first); 
}

uint_t String::hashcode(){ 
	if((flags_ & HASHED)!=0)
		return str_.hashcode;		
	became_unified(); 
	str_.hashcode = make_hashcode(str_.p, size_);
	flags_ |= HASHED;
	return str_.hashcode; 
}

StringPtr String::clone(){ 
	return StringPtr::from_this(this); 
}

InternedStringPtr String::intern(){ 
	return StringPtr::from_this(this); 
}

bool String::is_interned(){ 
	return (flags_ & INTERNED)!=0; 
}

int_t String::to_i(){ 
	return atoi(c_str()); 
}

float_t String::to_f(){ 
	return (float_t)atof(c_str()); 
}

StringPtr String::to_s(){ 
	return StringPtr::from_this(this); 
}

AnyPtr String::split(const StringPtr& sep){
	return xnew<StringSplit>(StringPtr::from_this(this), sep);
}

StringPtr String::op_cat_String(const StringPtr& v){
	if(size_+v->size_ <= 16)
		return xnew<String>(c_str(), size(), v->c_str(), v->size());
	return xnew<String>(this, v.get());
}

bool String::op_eq_r_String(const StringPtr& v){ 
	return v->size()==size() && memcmp(v->c_str(), c_str(), size())==0; 
}

bool String::op_lt_r_String(const StringPtr& v){ 
	return strcmp(v->c_str(), c_str())<0; 
}

void String::became_unified(){
	if((flags_ & ROPE)==0)
		return;

	uint_t pos = 0;
	char_t* memory = (char_t*)user_malloc(sizeof(char_t)*(size_+1));
	write_to_memory(this, memory, pos);
	memory[pos] = 0;
	rope_.left->dec_ref_count();
	rope_.right->dec_ref_count();
	str_.p = memory;
	flags_ = 0;
}

void String::write_to_memory(String* p, char_t* memory, uint_t& pos){
	PStack<String*> stack;
	for(;;){
		if((p->flags_ & ROPE)==0){
			memcpy(&memory[pos], p->str_.p, p->size_);
			pos += p->size_;
			if(stack.empty())
				return;
			p = stack.pop();
		}else{
			stack.push(p->rope_.right);
			p = p->rope_.left;
		}
	}
}

StringPtr String::cat(const StringPtr& v){
	return op_cat_String(v);
}

StringPtr String::op_cat_r_String(const StringPtr& v){
	return v->op_cat_String(StringPtr::from_this(this));
}

void String::op_cat(const VMachinePtr& vm){
	AnyPtr a = vm->arg(0); 
	vm->recycle_call(StringPtr::from_this(this)); 
	a->rawsend(vm, Xid(op_cat_r_String));
}

void String::op_eq(const VMachinePtr& vm){
	AnyPtr a = vm->arg(0); 
	vm->recycle_call(StringPtr::from_this(this)); 
	a->rawsend(vm, Xid(op_eq_r_String));
	if(!vm->processed()){
		vm->return_result(null);
	}
}

void String::op_lt(const VMachinePtr& vm){
	AnyPtr a = vm->arg(0); 
	vm->recycle_call(StringPtr::from_this(this)); 
	a->rawsend(vm, Xid(op_lt_r_String));
}



InternedStringPtr::InternedStringPtr(const char* name)
	:StringPtr(name ? str_mgr()->insert(name, strlen(name)) : null){}

InternedStringPtr::InternedStringPtr(const char* name, int_t size)
	:StringPtr(str_mgr()->insert(name, size)){}

InternedStringPtr::InternedStringPtr(const StringPtr& name)
	:StringPtr(!name ? null : name->is_interned() ? name : str_mgr()->insert(name->c_str(), name->size())){}

#ifdef XTAL_USE_PREDEFINED_ID

//{InternedStringPtr{{
namespace id{
InternedStringPtr id__ARGS__(null);
InternedStringPtr idop_or_assign(null);
InternedStringPtr idop_add_assign(null);
InternedStringPtr idop_shr(null);
InternedStringPtr idop_ushr_assign(null);
InternedStringPtr idop_call(null);
InternedStringPtr idop_sub_assign(null);
InternedStringPtr idop_lt(null);
InternedStringPtr idop_eq(null);
InternedStringPtr idop_mul(null);
InternedStringPtr idop_neg(null);
InternedStringPtr idserial_new(null);
InternedStringPtr iditer_next(null);
InternedStringPtr iditer_first(null);
InternedStringPtr idtrue(null);
InternedStringPtr idserial_save(null);
InternedStringPtr idop_and_assign(null);
InternedStringPtr idop_mod_assign(null);
InternedStringPtr idop_div_assign(null);
InternedStringPtr idop_or(null);
InternedStringPtr idop_div(null);
InternedStringPtr idlib(null);
InternedStringPtr idop_cat_assign(null);
InternedStringPtr idop_cat(null);
InternedStringPtr idIOError(null);
InternedStringPtr idserial_load(null);
InternedStringPtr idfalse(null);
InternedStringPtr idop_add(null);
InternedStringPtr idop_cat_r_String(null);
InternedStringPtr idop_dec(null);
InternedStringPtr idop_inc(null);
InternedStringPtr idop_ushr(null);
InternedStringPtr idop_pos(null);
InternedStringPtr idop_shr_assign(null);
InternedStringPtr idop_mod(null);
InternedStringPtr iditer_break(null);
InternedStringPtr idop_eq_r_String(null);
InternedStringPtr idstring(null);
InternedStringPtr idinitialize(null);
InternedStringPtr idop_set_at(null);
InternedStringPtr idop_lt_r_String(null);
InternedStringPtr idtest(null);
InternedStringPtr idop_at(null);
InternedStringPtr idop_shl_assign(null);
InternedStringPtr idop_sub(null);
InternedStringPtr idvalue(null);
InternedStringPtr idop_clone(null);
InternedStringPtr idop_com(null);
InternedStringPtr idnew(null);
InternedStringPtr idop_shl(null);
InternedStringPtr idop_xor(null);
InternedStringPtr idop_and(null);
InternedStringPtr idsize(null);
InternedStringPtr idop_xor_assign(null);
InternedStringPtr idop_mul_assign(null);
}
void InitID(){
id::id__ARGS__ = InternedStringPtr("__ARGS__", 8); add_long_life_var(&id::id__ARGS__); 
id::idop_or_assign = InternedStringPtr("op_or_assign", 12); add_long_life_var(&id::idop_or_assign); 
id::idop_add_assign = InternedStringPtr("op_add_assign", 13); add_long_life_var(&id::idop_add_assign); 
id::idop_shr = InternedStringPtr("op_shr", 6); add_long_life_var(&id::idop_shr); 
id::idop_ushr_assign = InternedStringPtr("op_ushr_assign", 14); add_long_life_var(&id::idop_ushr_assign); 
id::idop_call = InternedStringPtr("op_call", 7); add_long_life_var(&id::idop_call); 
id::idop_sub_assign = InternedStringPtr("op_sub_assign", 13); add_long_life_var(&id::idop_sub_assign); 
id::idop_lt = InternedStringPtr("op_lt", 5); add_long_life_var(&id::idop_lt); 
id::idop_eq = InternedStringPtr("op_eq", 5); add_long_life_var(&id::idop_eq); 
id::idop_mul = InternedStringPtr("op_mul", 6); add_long_life_var(&id::idop_mul); 
id::idop_neg = InternedStringPtr("op_neg", 6); add_long_life_var(&id::idop_neg); 
id::idserial_new = InternedStringPtr("serial_new", 10); add_long_life_var(&id::idserial_new); 
id::iditer_next = InternedStringPtr("iter_next", 9); add_long_life_var(&id::iditer_next); 
id::iditer_first = InternedStringPtr("iter_first", 10); add_long_life_var(&id::iditer_first); 
id::idtrue = InternedStringPtr("true", 4); add_long_life_var(&id::idtrue); 
id::idserial_save = InternedStringPtr("serial_save", 11); add_long_life_var(&id::idserial_save); 
id::idop_and_assign = InternedStringPtr("op_and_assign", 13); add_long_life_var(&id::idop_and_assign); 
id::idop_mod_assign = InternedStringPtr("op_mod_assign", 13); add_long_life_var(&id::idop_mod_assign); 
id::idop_div_assign = InternedStringPtr("op_div_assign", 13); add_long_life_var(&id::idop_div_assign); 
id::idop_or = InternedStringPtr("op_or", 5); add_long_life_var(&id::idop_or); 
id::idop_div = InternedStringPtr("op_div", 6); add_long_life_var(&id::idop_div); 
id::idlib = InternedStringPtr("lib", 3); add_long_life_var(&id::idlib); 
id::idop_cat_assign = InternedStringPtr("op_cat_assign", 13); add_long_life_var(&id::idop_cat_assign); 
id::idop_cat = InternedStringPtr("op_cat", 6); add_long_life_var(&id::idop_cat); 
id::idIOError = InternedStringPtr("IOError", 7); add_long_life_var(&id::idIOError); 
id::idserial_load = InternedStringPtr("serial_load", 11); add_long_life_var(&id::idserial_load); 
id::idfalse = InternedStringPtr("false", 5); add_long_life_var(&id::idfalse); 
id::idop_add = InternedStringPtr("op_add", 6); add_long_life_var(&id::idop_add); 
id::idop_cat_r_String = InternedStringPtr("op_cat_r_String", 15); add_long_life_var(&id::idop_cat_r_String); 
id::idop_dec = InternedStringPtr("op_dec", 6); add_long_life_var(&id::idop_dec); 
id::idop_inc = InternedStringPtr("op_inc", 6); add_long_life_var(&id::idop_inc); 
id::idop_ushr = InternedStringPtr("op_ushr", 7); add_long_life_var(&id::idop_ushr); 
id::idop_pos = InternedStringPtr("op_pos", 6); add_long_life_var(&id::idop_pos); 
id::idop_shr_assign = InternedStringPtr("op_shr_assign", 13); add_long_life_var(&id::idop_shr_assign); 
id::idop_mod = InternedStringPtr("op_mod", 6); add_long_life_var(&id::idop_mod); 
id::iditer_break = InternedStringPtr("iter_break", 10); add_long_life_var(&id::iditer_break); 
id::idop_eq_r_String = InternedStringPtr("op_eq_r_String", 14); add_long_life_var(&id::idop_eq_r_String); 
id::idstring = InternedStringPtr("string", 6); add_long_life_var(&id::idstring); 
id::idinitialize = InternedStringPtr("initialize", 10); add_long_life_var(&id::idinitialize); 
id::idop_set_at = InternedStringPtr("op_set_at", 9); add_long_life_var(&id::idop_set_at); 
id::idop_lt_r_String = InternedStringPtr("op_lt_r_String", 14); add_long_life_var(&id::idop_lt_r_String); 
id::idtest = InternedStringPtr("test", 4); add_long_life_var(&id::idtest); 
id::idop_at = InternedStringPtr("op_at", 5); add_long_life_var(&id::idop_at); 
id::idop_shl_assign = InternedStringPtr("op_shl_assign", 13); add_long_life_var(&id::idop_shl_assign); 
id::idop_sub = InternedStringPtr("op_sub", 6); add_long_life_var(&id::idop_sub); 
id::idvalue = InternedStringPtr("value", 5); add_long_life_var(&id::idvalue); 
id::idop_clone = InternedStringPtr("op_clone", 8); add_long_life_var(&id::idop_clone); 
id::idop_com = InternedStringPtr("op_com", 6); add_long_life_var(&id::idop_com); 
id::idnew = InternedStringPtr("new", 3); add_long_life_var(&id::idnew); 
id::idop_shl = InternedStringPtr("op_shl", 6); add_long_life_var(&id::idop_shl); 
id::idop_xor = InternedStringPtr("op_xor", 6); add_long_life_var(&id::idop_xor); 
id::idop_and = InternedStringPtr("op_and", 6); add_long_life_var(&id::idop_and); 
id::idsize = InternedStringPtr("size", 4); add_long_life_var(&id::idsize); 
id::idop_xor_assign = InternedStringPtr("op_xor_assign", 13); add_long_life_var(&id::idop_xor_assign); 
id::idop_mul_assign = InternedStringPtr("op_mul_assign", 13); add_long_life_var(&id::idop_mul_assign); 
}
//}}InternedStringPtr}




#else

void InitID(){}

#endif









}