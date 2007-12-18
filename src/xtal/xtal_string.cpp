#include "xtal.h"
#include "xtal_macro.h"

#include <string.h>

namespace xtal{

static uint_t make_hashcode(const char_t* str, uint_t size){
	uint_t hash = 2166136261U;
	for(uint_t i=0; i<size; ++i){
		hash = hash*137 ^ str[i];
	}
	return hash;
}

static void make_hashcode_and_length(const char_t* str, uint_t size, uint_t& hash, uint_t& length){
	hash = 2166136261U;
	length = 0;

	ChMaker chm;

	uint_t i=0;
	while(i<size){
		chm.clear();
		while(!chm.is_completed()){
			if(i<size){ chm.add(str[i++]); } 
			else{ break; }
		}
	
		for(int_t j=0; j<chm.pos; ++j){
			hash = hash*137 ^ chm.buf[j];
		}

		length += 1;
	}
}

static void make_size_and_hashcode_and_length(const char_t* str, uint_t& size, uint_t& hash, uint_t& length){
	hash = 2166136261U;
	length = 0;
	size = 0;

	ChMaker chm;

	uint_t i=0;
	while(str[i]){
		chm.clear();
		while(!chm.is_completed()){
			if(str[i]){ chm.add(str[i++]); } 
			else{ break; }
		}
	
		for(int_t j=0; j<chm.pos; ++j){
			hash = hash*137 ^ chm.buf[j];
		}

		length += 1;
		size += chm.pos;
	}
}

static void make_size_and_hashcode_and_length_limit(const char_t* str, uint_t& size, uint_t& hash, uint_t& length){
	hash = 2166136261U;
	length = 0;
	size = 0;

	ChMaker chm;

	uint_t i=0;
	while(str[i] && i<Innocence::SMALL_STRING_MAX){
		chm.clear();
		while(!chm.is_completed()){
			if(str[i] && i<Innocence::SMALL_STRING_MAX){ chm.add(str[i++]); } 
			else{ break; }
		}
	
		for(int_t j=0; j<chm.pos; ++j){
			hash = hash*137 ^ chm.buf[j];
		}

		length += 1;
		size += chm.pos;
	}
}

static uint_t string_length(const char_t* str){
	uint_t ret = 0;
	while(*str++){
		ret++;
	}
	return ret;
}

static int_t string_compare(const char_t* a, const char_t* b){
	while(*a!=*b){
		if(!*a)
			return 0;
		a++;
		b++;
	}
	return (int_t)*a - (int_t)*b;
}

class StringEachIter : public Base{
	StringStreamPtr ss_;

	virtual void visit_members(Visitor& m){
		Base::visit_members(m);
		m & ss_;
	}

public:

	StringEachIter(const StringPtr& str)
		:ss_(xnew<StringStream>(str)){
	}

	void block_next(const VMachinePtr& vm){
		if(ss_->eos()){
			vm->return_result(null, null);
			return;
		}

		vm->return_result(from_this(this), ss_->get_s(1));
	}
};

class ChRangeIter : public Base{
public:

	ChRangeIter(const ChRangePtr& range)
		:it_(range->left()), end_(range->right()){}

	void block_next(const VMachinePtr& vm){
		if(ch_cmp(it_->data(), it_->buffer_size(), end_->data(), end_->buffer_size())>0){
			vm->return_result(null, null);
			return;
		}

		StringPtr temp = it_;
		it_ = ch_inc(it_->data(), it_->buffer_size());
		vm->return_result(from_this(this), temp);
	}

private:

	virtual void visit_members(Visitor& m){
		Base::visit_members(m);
		m & it_ & end_;
	}

	StringPtr it_, end_;
};

AnyPtr ChRange::each(){
	return xnew<ChRangeIter>(from_this(this));
}

////////////////////////////////////////////////////////////////

class StringMgr : public GCObserver{
public:

	struct Key{
		const char_t* str;
		uint_t size;
	};

	struct Value{
		uint_t hashcode;
		IDPtr value;
		char_t buf[Innocence::SMALL_STRING_MAX+1];
	};

	struct Fun{
		static uint_t hash(const Key& key){
			return make_hashcode(key.str, key.size);
		}

		static bool eq(const Key& a, const Key& b){
			return a.size==b.size && memcmp(a.str, b.str, a.size)==0;
		}
	};

	typedef Hashtable<Key, Value, Fun> table_t; 
	table_t table_;

	StringMgr(){
		guard_ = 0;
	}

protected:

	int_t guard_;

	struct Guard{
		int_t& count;
		Guard(int_t& c):count(c){ count++; }
		~Guard(){ count--; }
	private:
		void operator=(const Guard&);
	};

	virtual void visit_members(Visitor& m){
		GCObserver::visit_members(m);
		for(table_t::iterator it = table_.begin(); it!=table_.end(); ++it){
			m & it->second.value;
		}		
	}

public:

	const Value& insert(const char_t* str, uint_t size){
		uint_t hashcode;
		uint_t length;
		make_hashcode_and_length(str, size, hashcode, length);
		return insert(str, size, hashcode, length);
	}

	const Value& insert(const char_t* str){
		uint_t hashcode;
		uint_t length;
		uint_t size;
		make_size_and_hashcode_and_length(str, size, hashcode, length);
		return insert(str, size, hashcode, length);
	}

	const Value& insert(const char_t* str, uint_t size, uint_t hash, uint_t length);

	virtual void before_gc();
};

const StringMgr::Value& StringMgr::insert(const char_t* str, uint_t size, uint_t hashcode, uint_t length){
	Guard guard(guard_);

	Key key = {str, size};
	table_t::iterator it = table_.find(key, hashcode);
	if(it!=table_.end()){
		return it->second;
	}

	Value value = {hashcode, xnew<ID>(str, size, hashcode, length)};
	if(size<=Innocence::SMALL_STRING_MAX){
		std::memcpy(value.buf, str, sizeof(char_t)*size);
		value.buf[size] = 0;
	}

	it = table_.insert(key, value, hashcode).first;
	it->first.str = it->second.value->data();
	return it->second;
}

void StringMgr::before_gc(){
	return;

	if(guard_){
		return;
	}
}


namespace{

SmartPtr<StringMgr> str_mgr_;

void uninitialize_string(){
	str_mgr_ = null;
}

}

class InternedStringIter : public Base{
	StringMgr::table_t::iterator iter_, last_;
public:

	InternedStringIter()
		:iter_(str_mgr_->table_.begin()), last_(str_mgr_->table_.end()){
	}
			
	void block_next(const VMachinePtr& vm){
		if(iter_!=last_){
			vm->return_result(from_this(this), iter_->second.value);
			++iter_;
		}
		else{
			vm->return_result(null, null);
		}
	}
};

AnyPtr interned_strings(){
	return xnew<InternedStringIter>();
}

int_t shortest_edit_distance(const StringPtr& str1, const StringPtr& str2){
	return shortest_edit_distance(str1->data(), str1->buffer_size(), str2->data(), str2->buffer_size());
}

////////////////////////////////////////////////////////////////

void initialize_string(){
	register_uninitializer(&uninitialize_string);
	str_mgr_ = xnew<StringMgr>();
		
	{
		ClassPtr p = new_cpp_class<StringEachIter>("StringEachIter");
		p->inherit(Iterator());
		p->method("block_next", &StringEachIter::block_next);
	}

	{
		ClassPtr p = new_cpp_class<ChRangeIter>("ChRangeIter");
		p->inherit(Iterator());
		p->method("block_next", &ChRangeIter::block_next);
	}

	{
		ClassPtr p = new_cpp_class<ChRange>("ChRange");
		p->inherit(Iterable());
		p->def("new", ctor<ChRange, const StringPtr&, const StringPtr&>()->param(Named("left", null), Named("right", null)));
		p->method("left", &ChRange::left);
		p->method("right", &ChRange::right);
		p->method("each", &ChRange::each);
	}

	{
		ClassPtr p = new_cpp_class<String>("String");
		p->inherit(Iterable());

		p->def("new", ctor<String>());
		p->method("to_i", &String::to_i);
		p->method("to_f", &String::to_f);
		p->method("to_s", &String::to_s);
		p->method("clone", &String::clone);

		p->method("length", &String::length);
		p->method("size", &String::size);
		p->method("intern", &String::intern);

		p->method("each", &String::each);

		p->method("op_range", &String::op_range, get_cpp_class<String>());
		p->method("op_cat", &String::op_cat, get_cpp_class<String>());
		p->method("op_cat_assign", &String::op_cat, get_cpp_class<String>());
		p->method("op_eq", &String::op_eq, get_cpp_class<String>());
		p->method("op_lt", &String::op_lt, get_cpp_class<String>());
	}

	{
		ClassPtr p = new_cpp_class<InternedStringIter>("InternedStringIter");
		p->inherit(Iterator());
		p->method("block_next", &InternedStringIter::block_next);
	}

	set_cpp_class<ID>(get_cpp_class<String>());
}

////////////////////////////////////////////////////////////////

void String::init_string(const char_t* str, uint_t sz){
	if(sz<=SMALL_STRING_MAX){
		set_small_string();
		std::memcpy(svalue_, str, sz*sizeof(char_t));
	}
	else{
		uint_t hash, length;
		make_hashcode_and_length(str, sz, hash, length);
		if(length<=1){
			set_p(pvalue(str_mgr_->insert(str, sz, hash, length).value));
			pvalue(*this)->inc_ref_count();
		}
		else{
			set_p(new LargeString(str, sz, hash, length));
			pvalue(*this)->set_class(new_cpp_class<String>());
			register_gc(pvalue(*this));
		}
	}
}


String::String(const char_t* str):Any(noinit_t()){
	init_string(str, string_length(str));
}

String::String(const avoid<char>::type* str):Any(noinit_t()){
	uint_t n = strlen((char*)str);
	UserMallocGuard umg(n*sizeof(char_t));
	char_t* buf = (char_t*)umg.get();
	for(uint_t i=0; i<n; ++i){
		buf[i] = str[i];
	}
	init_string(buf, n);
}

String::String(const string_t& str):Any(noinit_t()){
	init_string(str.c_str(), str.size());
}

String::String(const char_t* str, uint_t size):Any(noinit_t()){
	init_string(str, size);
}

String::String(const char_t* begin, const char_t* last):Any(noinit_t()){
	init_string(begin, last-begin);
}

String::String(const char_t* str1, uint_t size1, const char_t* str2, uint_t size2):Any(noinit_t()){
	if(size1==0){
		init_string(str2, size2);
		return;
	}
	else if(size2==0){
		init_string(str1, size1);
		return;
	}

	uint_t sz = size1 + size2;
	if(sz<=SMALL_STRING_MAX){
		set_small_string();
		std::memcpy(svalue_, str1, size1*sizeof(char_t));
		std::memcpy(&svalue_[size1], str2, size2*sizeof(char_t));
	}
	else{
		set_p(new LargeString(str1, size1, str2, size2));
		pvalue(*this)->set_class(new_cpp_class<String>());
		register_gc(pvalue(*this));
	}
}

String::String(char_t a)
	:Any(noinit_t()){
	if(1<=SMALL_STRING_MAX){
		set_small_string();
		svalue_[0] = a;
	}
	else{
		init_string(&a, 1);
	}
}

String::String(char_t a, char_t b)
	:Any(noinit_t()){
	if(2<=SMALL_STRING_MAX){
		set_small_string();
		svalue_[0] = a; svalue_[1] = b;
	}
	else{
		char_t buf[2] = {a, b};
		init_string(buf, 2);
	}
}

String::String(char_t a, char_t b, char_t c)
	:Any(noinit_t()){
	if(3<=SMALL_STRING_MAX){
		set_small_string();
		svalue_[0] = a; svalue_[1] = b; svalue_[2] = c;
	}
	else{
		char_t buf[3] = {a, b, c};
		init_string(buf, 3);
	}
}

String::String(const char_t* str, uint_t size, uint_t hashcode, uint_t length, bool intern_flag):Any(noinit_t()){
	uint_t sz = size;
	if(sz<=SMALL_STRING_MAX){
		set_small_string();
		std::memcpy(svalue_, str, sz*sizeof(char_t));
	}
	else{
		if(!intern_flag && length<=1){
			set_p(pvalue(str_mgr_->insert(str, sz, hashcode, length).value));
			pvalue(*this)->inc_ref_count();
		}
		else{
			set_p(new LargeString(str, sz, hashcode, length, intern_flag));
			pvalue(*this)->set_class(new_cpp_class<String>());
			register_gc(pvalue(*this));
		}
	}
}

String::String(LargeString* left, LargeString* right):Any(noinit_t()){
	if(left->buffer_size()==0){
		init_string(right->c_str(), right->buffer_size());
		return;
	}
	else if(right->buffer_size()==0){
		init_string(left->c_str(), left->buffer_size());
		return;
	}

	set_p(new LargeString(left, right));
	pvalue(*this)->set_class(new_cpp_class<String>());
	register_gc(pvalue(*this));
}

String::String(const String& s)
	:Any(s){
	inc_ref_count_force(s);
}

const char_t* String::c_str(){
	if(type(*this)==TYPE_BASE){
		return ((LargeString*)pvalue(*this))->c_str();
	}
	else{
		uint_t size, hash, length;
		make_size_and_hashcode_and_length_limit(svalue_, size, hash, length);
		return str_mgr_->insert(svalue_, size, hash, length).buf;
	}
}

const char_t* String::data(){
	if(type(*this)==TYPE_BASE){
		return ((LargeString*)pvalue(*this))->c_str();
	}
	else{
		return svalue_;
	}
}

uint_t String::buffer_size(){
	if(type(*this)==TYPE_BASE){
		return ((LargeString*)pvalue(*this))->buffer_size();
	}
	else{
		for(uint_t i=0; i<=SMALL_STRING_MAX; ++i){
			if(svalue_[i]=='\0'){
				return i;
			}
		}
		return SMALL_STRING_MAX;
	}
}

uint_t String::length(){
	if(type(*this)==TYPE_BASE){
		return ((LargeString*)pvalue(*this))->length();
	}
	else{
		uint_t size, hash, length;
		make_size_and_hashcode_and_length(svalue_, size, hash, length);
		return length;
	}
}

uint_t String::size(){
	return length();
}

StringPtr String::clone(){
	return from_this(this);
}

const IDPtr& String::intern(){
	if(type(*this)==TYPE_BASE){
		LargeString* p = ((LargeString*)pvalue(*this));
		if(p->is_interned()) return static_ptr_cast<ID>(ap(*this));
		return static_ptr_cast<ID>(str_mgr_->insert(p->c_str(), p->buffer_size(), p->hashcode(), p->length()).value);
	}
	else{
		return static_ptr_cast<ID>(ap(*this));
	}
}

bool String::is_interned(){
	if(type(*this)==TYPE_BASE){
		return ((LargeString*)pvalue(*this))->is_interned();
	}
	else{
		return true;
	}
}

StringPtr String::to_s(){
	return from_this(this);
}

int_t String::to_i(){
	return std::atoi(c_str()); 
}

float_t String::to_f(){
	return (float_t)std::atof(c_str()); 
}

AnyPtr String::each(){
	return xnew<StringEachIter>(from_this(this));
}

ChRangePtr String::op_range(const StringPtr& right, int_t kind){
	if(kind!=RANGE_CLOSED){
		XTAL_THROW(builtin()->member("RuntimeError")(Xt("Xtal Runtime Error 1025")), return xnew<ChRange>("", ""));		
	}

	if(length()==1 && right->length()==1){
		return xnew<ChRange>(from_this(this), right);
	}
	else{
		XTAL_THROW(builtin()->member("RuntimeError")(Xt("Xtal Runtime Error 1023")), return xnew<ChRange>("", ""));		
	}
}

StringPtr String::op_cat(const StringPtr& v){
	uint_t mysize = buffer_size();
	uint_t vsize = v->buffer_size();

	if(mysize+vsize <= 16 || mysize<=SMALL_STRING_MAX || vsize<=SMALL_STRING_MAX)
		return xnew<String>(data(), mysize, v->data(), vsize);
	return xnew<String>((LargeString*)pvalue(*this), (LargeString*)pvalue(v));
}

bool String::op_eq(const StringPtr& v){ 
	return buffer_size()==v->buffer_size() && memcmp(data(), v->data(), buffer_size())==0; 
}

bool String::op_lt(const StringPtr& v){
	return string_compare(c_str(), v->c_str()) < 0;
}

StringPtr String::cat(const StringPtr& v){
	return op_cat(v);
}

uint_t String::hashcode(){
	if(type(*this)==TYPE_BASE){
		return ((LargeString*)pvalue(*this))->hashcode();
	}
	else{
		return make_hashcode(svalue_, buffer_size());
	}
}

int_t String::calc_offset(int_t i){
	uint_t sz = buffer_size();
	if(i<0){
		i = sz + i;
		if(i<0){
			throw_index_error();
			return 0;
		}
	}
	else{
		if((uint_t)i >= sz){
			throw_index_error();
			return 0;
		}
	}
	return i;
}

void String::throw_index_error(){
	XTAL_THROW(builtin()->member("RuntimeError")(Xt("Xtal Runtime Error 1020")), return);
}

////////////////////////////////////////////////////////////////


void LargeString::visit_members(Visitor& m){
	Base::visit_members(m);
	if((flags_ & ROPE)!=0){
		m & rope_.left & rope_.right;
	}
}

void visit_members(Visitor& m, const Named& p){
	m & p.name & p.value;
}

struct StringKey{
	const char_t* str;
	int_t size;

	StringKey(const char_t* str, int_t size)
		:str(str), size(size){}

	friend bool operator <(const StringKey& a, const StringKey& b){
		if(a.size<b.size)
			return true;
		if(a.size>b.size)
			return false;
		return memcmp(a.str, b.str, a.size)<0;
	}
};

void LargeString::common_init(uint_t size){
	XTAL_ASSERT(size>Innocence::SMALL_STRING_MAX);

	buffer_size_ = size;
	str_.p = static_cast<char_t*>(user_malloc(sizeof(char_t)*(buffer_size_+1)));
	str_.p[buffer_size_] = 0;
	flags_ = 0;
}

LargeString::LargeString(const char_t* str1, uint_t size1, const char_t* str2, uint_t size2){
	common_init(size1 + size2);
	std::memcpy(str_.p, str1, size1*sizeof(char_t));
	std::memcpy(str_.p+size1, str2, size2*sizeof(char_t));
	make_hashcode_and_length(str_.p, buffer_size_, str_.hashcode, length_);
}

LargeString::LargeString(const char_t* str, uint_t size, uint_t hashcode, uint_t length, bool intern_flag){
	common_init(size);
	std::memcpy(str_.p, str, buffer_size_*sizeof(char_t));
	str_.hashcode = hashcode;
	flags_ = intern_flag ? INTERNED : 0;
	length_ = length;
}

LargeString::LargeString(LargeString* left, LargeString* right){
	left->inc_ref_count();
	right->inc_ref_count();
	rope_.left = left;
	rope_.right = right;
	buffer_size_ = left->buffer_size() + right->buffer_size();
	flags_ = ROPE;
	length_ = left->length() + right->length();
}

LargeString::~LargeString(){
	if((flags_ & ROPE)==0){
		user_free(str_.p);
	}
	else{
		rope_.left->dec_ref_count();
		rope_.right->dec_ref_count();
	}
}

const char_t* LargeString::c_str(){ 
	if((flags_ & ROPE)!=0)
		became_unified();
	return str_.p; 
}

uint_t LargeString::hashcode(){ 
	if((flags_ & ROPE)!=0)
		became_unified();
	return str_.hashcode; 
}

void LargeString::became_unified(){
	uint_t pos = 0;
	char_t* memory = (char_t*)user_malloc(sizeof(char_t)*(buffer_size_+1));
	write_to_memory(this, memory, pos);
	memory[pos] = 0;
	rope_.left->dec_ref_count();
	rope_.right->dec_ref_count();
	str_.p = memory;
	flags_ = 0;
	make_hashcode_and_length(str_.p, buffer_size_, str_.hashcode, length_);
}

void LargeString::write_to_memory(LargeString* p, char_t* memory, uint_t& pos){
	PStack<LargeString*> stack;
	for(;;){
		if((p->flags_ & ROPE)==0){
			std::memcpy(&memory[pos], p->str_.p, p->buffer_size_*sizeof(char_t));
			pos += p->buffer_size_;
			if(stack.empty())
				return;
			p = stack.pop();
		}
		else{
			stack.push(p->rope_.right);
			p = p->rope_.left;
		}
	}
}



ID::ID(const char_t* str)
	:String(*str_mgr_->insert(str).value){}

ID::ID(const avoid<char>::type* str)	
	:String(noinit_t()){
	uint_t n = strlen((char*)str);
	UserMallocGuard umg(n*sizeof(char_t));
	char_t* buf = (char_t*)umg.get();
	for(uint_t i=0; i<n; ++i){
		buf[i] = str[i];
	}
		
	*this = ID(buf, n);
}

ID::ID(const string_t& str)
	:String(*str_mgr_->insert(str.c_str(), str.size()).value){}

ID::ID(const char_t* str, uint_t size)
	:String(*str_mgr_->insert(str, size).value){}

ID::ID(const char_t* begin, const char_t* last)
	:String(*str_mgr_->insert(begin, last-begin).value){}

ID::ID(char_t a)
	:String(noinit_t()){
	if(1<=SMALL_STRING_MAX){
		set_small_string();
		svalue_[0] = a;
	}
	else{
		*this = ID(&a, 1);
	}
}

ID::ID(char_t a, char_t b)
	:String(noinit_t()){
	if(2<=SMALL_STRING_MAX){
		set_small_string();
		svalue_[0] = a; svalue_[1] = b;
	}
	else{
		char_t buf[2] = {a, b};
		*this = ID(buf, 2);
	}
}

ID::ID(char_t a, char_t b, char_t c)
	:String(noinit_t()){
	if(3<=SMALL_STRING_MAX){
		set_small_string();
		svalue_[0] = a; svalue_[1] = b; svalue_[2] = c;
	}
	else{
		char_t buf[3] = {a, b, c};
		*this = ID(buf, 3);
	}
}

ID::ID(const char_t* str, uint_t len, uint_t hashcode, uint_t length)
	:String(str, len, hashcode, length, true){}


ID::ID(const StringPtr& name)
	:String(*(name ? name->intern() : (const IDPtr&)name)){}


AnyPtr SmartPtrCtor1<String>::call(type v){
	return xnew<String>(v);
}

AnyPtr SmartPtrCtor2<String>::call(type v){
	return xnew<String>(v);
}

AnyPtr SmartPtrCtor1<ID>::call(type v){
	return str_mgr_->insert(v).value;
}

AnyPtr SmartPtrCtor2<ID>::call(type v){
	if(v) return v->intern();
	return v;
}

AnyPtr SmartPtrCtor3<ID>::call(type v){
	return xnew<ID>(v);
}

#ifdef XTAL_USE_PREDEFINED_ID

namespace id{
	IDPtr id_list[IDMAX];
}

IDPtr empty_id;

void uninitialize_interned_string(){
	empty_id = null;
	for(int i=0; i<id::IDMAX; ++i){
		id::id_list[i] = null;
	}
}

void initialize_interned_string(){
	register_uninitializer(&uninitialize_interned_string);
	
	empty_id = xnew<ID>("");

//{ID{{
	id::id_list[id::idop_inc] = xnew<ID>((const char*)XTAL_STRING("op_inc"), 6);
	id::id_list[id::idblock_catch] = xnew<ID>((const char*)XTAL_STRING("block_catch"), 11);
	id::id_list[id::idcallee] = xnew<ID>((const char*)XTAL_STRING("callee"), 6);
	id::id_list[id::idnew] = xnew<ID>((const char*)XTAL_STRING("new"), 3);
	id::id_list[id::idop_shl_assign] = xnew<ID>((const char*)XTAL_STRING("op_shl_assign"), 13);
	id::id_list[id::idop_at] = xnew<ID>((const char*)XTAL_STRING("op_at"), 5);
	id::id_list[id::idtest] = xnew<ID>((const char*)XTAL_STRING("test"), 4);
	id::id_list[id::idfor] = xnew<ID>((const char*)XTAL_STRING("for"), 3);
	id::id_list[id::idmembers] = xnew<ID>((const char*)XTAL_STRING("members"), 7);
	id::id_list[id::idserial_new] = xnew<ID>((const char*)XTAL_STRING("serial_new"), 10);
	id::id_list[id::idop_div_assign] = xnew<ID>((const char*)XTAL_STRING("op_div_assign"), 13);
	id::id_list[id::idop_mul] = xnew<ID>((const char*)XTAL_STRING("op_mul"), 6);
	id::id_list[id::idop_xor_assign] = xnew<ID>((const char*)XTAL_STRING("op_xor_assign"), 13);
	id::id_list[id::idto_a] = xnew<ID>((const char*)XTAL_STRING("to_a"), 4);
	id::id_list[id::idinitialize] = xnew<ID>((const char*)XTAL_STRING("initialize"), 10);
	id::id_list[id::idonce] = xnew<ID>((const char*)XTAL_STRING("once"), 4);
	id::id_list[id::idfalse] = xnew<ID>((const char*)XTAL_STRING("false"), 5);
	id::id_list[id::iddo] = xnew<ID>((const char*)XTAL_STRING("do"), 2);
	id::id_list[id::idstring] = xnew<ID>((const char*)XTAL_STRING("string"), 6);
	id::id_list[id::idancestors] = xnew<ID>((const char*)XTAL_STRING("ancestors"), 9);
	id::id_list[id::idop_and_assign] = xnew<ID>((const char*)XTAL_STRING("op_and_assign"), 13);
	id::id_list[id::idop_add_assign] = xnew<ID>((const char*)XTAL_STRING("op_add_assign"), 13);
	id::id_list[id::idop_cat_assign] = xnew<ID>((const char*)XTAL_STRING("op_cat_assign"), 13);
	id::id_list[id::idsingleton] = xnew<ID>((const char*)XTAL_STRING("singleton"), 9);
	id::id_list[id::idop_shl] = xnew<ID>((const char*)XTAL_STRING("op_shl"), 6);
	id::id_list[id::idblock_next] = xnew<ID>((const char*)XTAL_STRING("block_next"), 10);
	id::id_list[id::idyield] = xnew<ID>((const char*)XTAL_STRING("yield"), 5);
	id::id_list[id::idop_shr_assign] = xnew<ID>((const char*)XTAL_STRING("op_shr_assign"), 13);
	id::id_list[id::idop_cat] = xnew<ID>((const char*)XTAL_STRING("op_cat"), 6);
	id::id_list[id::idop_neg] = xnew<ID>((const char*)XTAL_STRING("op_neg"), 6);
	id::id_list[id::idop_dec] = xnew<ID>((const char*)XTAL_STRING("op_dec"), 6);
	id::id_list[id::iddefault] = xnew<ID>((const char*)XTAL_STRING("default"), 7);
	id::id_list[id::idcase] = xnew<ID>((const char*)XTAL_STRING("case"), 4);
	id::id_list[id::idto_s] = xnew<ID>((const char*)XTAL_STRING("to_s"), 4);
	id::id_list[id::idvalue] = xnew<ID>((const char*)XTAL_STRING("value"), 5);
	id::id_list[id::idop_shr] = xnew<ID>((const char*)XTAL_STRING("op_shr"), 6);
	id::id_list[id::idpure] = xnew<ID>((const char*)XTAL_STRING("pure"), 4);
	id::id_list[id::idfinally] = xnew<ID>((const char*)XTAL_STRING("finally"), 7);
	id::id_list[id::idthis] = xnew<ID>((const char*)XTAL_STRING("this"), 4);
	id::id_list[id::idnull] = xnew<ID>((const char*)XTAL_STRING("null"), 4);
	id::id_list[id::idop_div] = xnew<ID>((const char*)XTAL_STRING("op_div"), 6);
	id::id_list[id::idserial_load] = xnew<ID>((const char*)XTAL_STRING("serial_load"), 11);
	id::id_list[id::idIOError] = xnew<ID>((const char*)XTAL_STRING("IOError"), 7);
	id::id_list[id::idin] = xnew<ID>((const char*)XTAL_STRING("in"), 2);
	id::id_list[id::idcatch] = xnew<ID>((const char*)XTAL_STRING("catch"), 5);
	id::id_list[id::idop_mul_assign] = xnew<ID>((const char*)XTAL_STRING("op_mul_assign"), 13);
	id::id_list[id::idmethod] = xnew<ID>((const char*)XTAL_STRING("method"), 6);
	id::id_list[id::idop_lt] = xnew<ID>((const char*)XTAL_STRING("op_lt"), 5);
	id::id_list[id::idset_at] = xnew<ID>((const char*)XTAL_STRING("set_at"), 6);
	id::id_list[id::idop_mod_assign] = xnew<ID>((const char*)XTAL_STRING("op_mod_assign"), 13);
	id::id_list[id::idbreak] = xnew<ID>((const char*)XTAL_STRING("break"), 5);
	id::id_list[id::idtry] = xnew<ID>((const char*)XTAL_STRING("try"), 3);
	id::id_list[id::idop_mod] = xnew<ID>((const char*)XTAL_STRING("op_mod"), 6);
	id::id_list[id::idto_i] = xnew<ID>((const char*)XTAL_STRING("to_i"), 4);
	id::id_list[id::idop_or] = xnew<ID>((const char*)XTAL_STRING("op_or"), 5);
	id::id_list[id::idcontinue] = xnew<ID>((const char*)XTAL_STRING("continue"), 8);
	id::id_list[id::ide] = xnew<ID>((const char*)XTAL_STRING("e"), 1);
	id::id_list[id::iditerator] = xnew<ID>((const char*)XTAL_STRING("iterator"), 8);
	id::id_list[id::idthrow] = xnew<ID>((const char*)XTAL_STRING("throw"), 5);
	id::id_list[id::idop_and] = xnew<ID>((const char*)XTAL_STRING("op_and"), 6);
	id::id_list[id::idundefined] = xnew<ID>((const char*)XTAL_STRING("undefined"), 9);
	id::id_list[id::idelse] = xnew<ID>((const char*)XTAL_STRING("else"), 4);
	id::id_list[id::idfun] = xnew<ID>((const char*)XTAL_STRING("fun"), 3);
	id::id_list[id::idto_f] = xnew<ID>((const char*)XTAL_STRING("to_f"), 4);
	id::id_list[id::idop_sub_assign] = xnew<ID>((const char*)XTAL_STRING("op_sub_assign"), 13);
	id::id_list[id::idlib] = xnew<ID>((const char*)XTAL_STRING("lib"), 3);
	id::id_list[id::iddofun] = xnew<ID>((const char*)XTAL_STRING("dofun"), 5);
	id::id_list[id::ideach] = xnew<ID>((const char*)XTAL_STRING("each"), 4);
	id::id_list[id::idop_set_at] = xnew<ID>((const char*)XTAL_STRING("op_set_at"), 9);
	id::id_list[id::idop_in] = xnew<ID>((const char*)XTAL_STRING("op_in"), 5);
	id::id_list[id::ids_load] = xnew<ID>((const char*)XTAL_STRING("s_load"), 6);
	id::id_list[id::idclass] = xnew<ID>((const char*)XTAL_STRING("class"), 5);
	id::id_list[id::idop_com] = xnew<ID>((const char*)XTAL_STRING("op_com"), 6);
	id::id_list[id::idop_pos] = xnew<ID>((const char*)XTAL_STRING("op_pos"), 6);
	id::id_list[id::idop_add] = xnew<ID>((const char*)XTAL_STRING("op_add"), 6);
	id::id_list[id::idop_ushr_assign] = xnew<ID>((const char*)XTAL_STRING("op_ushr_assign"), 14);
	id::id_list[id::idnobreak] = xnew<ID>((const char*)XTAL_STRING("nobreak"), 7);
	id::id_list[id::idcurrent_context] = xnew<ID>((const char*)XTAL_STRING("current_context"), 15);
	id::id_list[id::idto_m] = xnew<ID>((const char*)XTAL_STRING("to_m"), 4);
	id::id_list[id::idreturn] = xnew<ID>((const char*)XTAL_STRING("return"), 6);
	id::id_list[id::idop_eq] = xnew<ID>((const char*)XTAL_STRING("op_eq"), 5);
	id::id_list[id::idfiber] = xnew<ID>((const char*)XTAL_STRING("fiber"), 5);
	id::id_list[id::idop_or_assign] = xnew<ID>((const char*)XTAL_STRING("op_or_assign"), 12);
	id::id_list[id::ids_save] = xnew<ID>((const char*)XTAL_STRING("s_save"), 6);
	id::id_list[id::idswitch] = xnew<ID>((const char*)XTAL_STRING("switch"), 6);
	id::id_list[id::idop_sub] = xnew<ID>((const char*)XTAL_STRING("op_sub"), 6);
	id::id_list[id::idop_ushr] = xnew<ID>((const char*)XTAL_STRING("op_ushr"), 7);
	id::id_list[id::idfirst_step] = xnew<ID>((const char*)XTAL_STRING("first_step"), 10);
	id::id_list[id::idblock_break] = xnew<ID>((const char*)XTAL_STRING("block_break"), 11);
	id::id_list[id::idserial_save] = xnew<ID>((const char*)XTAL_STRING("serial_save"), 11);
	id::id_list[id::idop_range] = xnew<ID>((const char*)XTAL_STRING("op_range"), 8);
	id::id_list[id::idunittest] = xnew<ID>((const char*)XTAL_STRING("unittest"), 8);
	id::id_list[id::idtrue] = xnew<ID>((const char*)XTAL_STRING("true"), 4);
	id::id_list[id::idop_xor] = xnew<ID>((const char*)XTAL_STRING("op_xor"), 6);
	id::id_list[id::idblock_first] = xnew<ID>((const char*)XTAL_STRING("block_first"), 11);
	id::id_list[id::idop_call] = xnew<ID>((const char*)XTAL_STRING("op_call"), 7);
	id::id_list[id::id_initialize_] = xnew<ID>((const char*)XTAL_STRING("_initialize_"), 12);
	id::id_list[id::idis] = xnew<ID>((const char*)XTAL_STRING("is"), 2);
	id::id_list[id::idwhile] = xnew<ID>((const char*)XTAL_STRING("while"), 5);
	id::id_list[id::idit] = xnew<ID>((const char*)XTAL_STRING("it"), 2);
	id::id_list[id::idassert] = xnew<ID>((const char*)XTAL_STRING("assert"), 6);
	id::id_list[id::idxtal] = xnew<ID>((const char*)XTAL_STRING("xtal"), 4);
	id::id_list[id::idif] = xnew<ID>((const char*)XTAL_STRING("if"), 2);
	id::id_list[id::idp] = xnew<ID>((const char*)XTAL_STRING("p"), 1);
//}}ID}




}

#else

void initialize_interned_string(){
	empty_id = xnew<ID>("");
}

#endif









}