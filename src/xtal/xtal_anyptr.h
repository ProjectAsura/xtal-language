/** \file src/xtal/xtal_anyptr.h
* \brief src/xtal/xtal_anyptr.h
*/

#ifndef XTAL_ANYPTR_H_INCLUDE_GUARD
#define XTAL_ANYPTR_H_INCLUDE_GUARD

#pragma once

namespace xtal{

template<class T>
struct UserTypeBuffer{
	AlignBuffer<T> buf;

	void* buffer(){ return buf.buffer; }

	template<class U>
	void destroy(U* p){
		p->~U();
	}
};

struct UserTypeHolder : public Base{
	UserTypeHolder(){}
	UserTypeHolder(void* p):ptr(p){}
	void* ptr;
};

template<class T, class Deleter = UserTypeBuffer<T> >
struct UserTypeHolderSub : public UserTypeHolder, public Deleter{
	UserTypeHolderSub(){}
	UserTypeHolderSub(T* p, const Deleter& f):UserTypeHolder(p), Deleter(f){}
	~UserTypeHolderSub(){ Deleter::destroy((T*)this->ptr); }
};

struct undeleter_t{
	template<class T>
	void destroy(T* p){}

	template<class T>
	SmartPtr<T> operator()(const T* p){
		return SmartPtr<T>(p, *this);
	}
};

struct deleter_t{
	template<class T>
	void destroy(T* p){
		delete p;
	}

	template<class T>
	SmartPtr<T> operator()(const T* p){
		return SmartPtr<T>(p, *this);
	}
};

extern undeleter_t undeleter;
extern deleter_t deleter;

///////////////////////////////////////////

struct XNewXBase_INHERITED_BASE{

	template<class T>
	void init();
	
	void* ptr(){ return value; }

	void* value;
	Base* pvalue;
};

template<class T>
void XNewXBase_INHERITED_BASE::init(){
	value = object_xmalloc<T>();
	static_cast<T*>(value)->template set_virtual_members<T>();
	pvalue = static_cast<T*>(value);
}

struct XNewXBase_INHERITED_RCBASE{

	template<class T>
	void init();

	void* ptr(){ return value; }

	void* value;
	RefCountingBase* pvalue;
};

template<class T>
void XNewXBase_INHERITED_RCBASE::init(){
	value = object_xmalloc<T>();
	static_cast<T*>(value)->template set_virtual_members<T>();
	pvalue = static_cast<T*>(value);
}

struct XNewXBase_INHERITED_ANY{

	template<class T>
	void init(){}

	void* ptr(){ return &value; }

	UninitializedAny value;
};

struct XNewXBase_INHERITED_OTHER{

	template<class T>
	void init();

	void* ptr(){ return value->ptr; }

	UserTypeHolder* value;
};

template<class T>
void XNewXBase_INHERITED_OTHER::init(){
	typedef UserTypeHolderSub<T> holder;
	holder* p = new(object_xmalloc<holder>()) holder();
	p->ptr = static_cast<T*>(static_cast<void*>(p->buffer()));
	value = p;
	p->template set_virtual_members<holder>();
}

template<int N> struct XNewXBase{};
template<> struct XNewXBase<INHERITED_BASE> : XNewXBase_INHERITED_BASE{};
template<> struct XNewXBase<INHERITED_RCBASE> : XNewXBase_INHERITED_RCBASE{};
template<> struct XNewXBase<INHERITED_ANY> : XNewXBase_INHERITED_ANY{};
template<> struct XNewXBase<INHERITED_OTHER> : XNewXBase_INHERITED_OTHER{};

template<class T>
struct XNewX : public XNewXBase<InheritedN<T>::value>{
	XNewX(){
		XNewXBase<InheritedN<T>::value>::template init<T>();
	}

	static void* operator new(std::size_t, XNewX<T>* self){ return self->ptr(); }
	static void operator delete(void*){}
};

template<class T, class Deleter>
UserTypeHolderSub<T, Deleter>* xnew_with_deleter(const T* tp, const Deleter& deleter){
	typedef UserTypeHolderSub<T, Deleter> holder;
	holder* p = new(object_xmalloc<holder>()) holder();
	p->ptr = const_cast<T*>(tp);
	p->template set_virtual_members<holder>();
	return p;
}

////////////////////////////////////

template<class T>
struct SmartPtrCtor1{
	struct type{};
	static int_t call(type){ return 0; };
};

template<class T>
struct SmartPtrCtor2{
	struct type{};
	static int_t call(type){ return 0; };
};

template<class T>
struct SmartPtrCtor3{
	struct type{};
	static int_t call(type){ return 0; };
};

template<class T>
struct SmartPtrCtor4{
	struct type{};
	static int_t call(type){ return 0; };
};

template<class T>
inline const ClassPtr& cpp_class();

/////////////////////////////////////////

/**
* \brief ���̌^�̃I�u�W�F�N�g�ł��ێ�������ꉻ���ꂽ�X�}�[�g�|�C���^
*/
template<>
class SmartPtr<Any> : public Any{
public:
	
	/**
	* \brief null�ō\�z����R���X�g���N�^
	*/
	SmartPtr(){}

	/**
	* \brief T�̃|�C���^�ƁA�����j�����邽�߂̊֐��I�u�W�F�N�g���󂯎���č\�z����R���X�g���N�^
	*/
	template<class T, class Deleter>
	SmartPtr(const T* tp, const Deleter& deleter)
		:Any(noinit_t()){
		init_smartptr(xnew_with_deleter<T, Deleter>(tp, deleter));
	}

	template<class T>
	SmartPtr(const T* p, const undeleter_t&)
		:Any(noinit_t()){
		value_.init_pointer(p, CppClassSymbol<T>::value->value);
	}

	// �C�ӂ̃|�C���^�^���󂯎����xtal�ŎQ�Ƃł���悤�ɂ���R���X�g���N�^
	template<class T>
	SmartPtr(const T* p)
		:Any(noinit_t()){
		set_unknown_pointer(p, p);
	}

	SmartPtr(const SmartPtr<Any>& p);

	/// null���󂯎��R���X�g���N�^
	SmartPtr(const NullPtr&){}

public:

	SmartPtr<Any>& operator =(const SmartPtr<Any>& p);

	void assign_direct(const SmartPtr<Any>& a);

	explicit SmartPtr(PrimitiveType type)
		:Any(type){}
	
	~SmartPtr();

public:

	SmartPtr(const XNewXBase<INHERITED_BASE>& m);
	SmartPtr(const XNewXBase<INHERITED_RCBASE>& m);
	SmartPtr(const XNewXBase<INHERITED_ANY>& m);
	SmartPtr(const XNewXBase<INHERITED_OTHER>& m);
	
	SmartPtr<Any>& operator =(const XNewXBase<INHERITED_BASE>& m);
	SmartPtr<Any>& operator =(const XNewXBase<INHERITED_RCBASE>& m);
	SmartPtr<Any>& operator =(const XNewXBase<INHERITED_ANY>& m);
	SmartPtr<Any>& operator =(const XNewXBase<INHERITED_OTHER>& m);

protected:

	SmartPtr(noinit_t)
		:Any(noinit_t()){}

	void set_unknown_pointer(const Base* p, const Base*);

	template<class T>
	void set_unknown_pointer(const T* p, const void*){
		value_.init_pointer(p, CppClassSymbol<T>::value->value);
	}

	void init_smartptr(const Any& a){
		*static_cast<Any*>(this) = a;
	}

	void init_smartptr(RefCountingBase* p);

	void init_smartptr(Base* p);

public:

	/**
	* \brief boolean����\�z����R���X�g���N�^�B
	*
	*/
	SmartPtr(bool v):Any(v){}

	/**
	* \brief �����񂩂�\�z����R���X�g���N�^�B
	*
	*/
	SmartPtr(const char_t* str);

	/**
	* \brief �����񂩂�\�z����R���X�g���N�^�B
	*
	*/
	SmartPtr(const char8_t* str);

	/**
	* \brief �����񂩂�\�z����R���X�g���N�^�B
	*
	*/
	SmartPtr(const StringLiteral& str);

	// ��{�^�̐����A���������_������\�z����R���X�g���N�^
	SmartPtr(char v):Any(v){}
	SmartPtr(signed char v):Any(v){}
	SmartPtr(unsigned char v):Any(v){}
	SmartPtr(short v):Any(v){}
	SmartPtr(unsigned short v):Any(v){}
	SmartPtr(int v):Any(v){}
	SmartPtr(unsigned int v):Any(v){}
	SmartPtr(long v):Any(v){}
	SmartPtr(unsigned long v):Any(v){}
	SmartPtr(long long v):Any(v){}
	SmartPtr(unsigned long long v):Any(v){}

	SmartPtr(float v):Any(v){}
	SmartPtr(double v):Any(v){}
	SmartPtr(long double v):Any(v){}

	// ��{�^�̐����A���������_������\�z����R���X�g���N�^
	SmartPtr(const bool* v):Any(*v){}
	SmartPtr(const unsigned char* v):Any(*v){}
	SmartPtr(const short* v):Any(*v){}
	SmartPtr(const unsigned short* v):Any(*v){}
	SmartPtr(const int* v):Any(*v){}
	SmartPtr(const unsigned int* v):Any(*v){}
	SmartPtr(const long* v):Any(*v){}
	SmartPtr(const unsigned long* v):Any(*v){}

	SmartPtr(const float* v):Any(*v){}
	SmartPtr(const double* v):Any(*v){}
	SmartPtr(const long double* v):Any(*v){}

public:

	/**
	* \brief Any�^�ւ̃|�C���^���擾����B
	*/
	Any* get() const{ return (Any*)this; }

	/**
	* \brief ->���Z�q
	* �X�}�[�g�|�C���^�Ƃ��Ĉ������߂ɃI�[�o�[���[�h����B
	*/
	Any* operator ->() const{ return get(); }
	
	/**
	* \brief *���Z�q
	* �X�}�[�g�|�C���^�Ƃ��Ĉ������߂ɃI�[�o�[���[�h����B
	*/
	Any& operator *() const{ return *get(); }
	
private:

	bool is_true() const{
		return rawtype(*this)>TYPE_FALSE;
	}

public:

#ifdef XTAL_DEBUG

	struct dummy_bool_tag{ void safe_true(){} };
	typedef void (dummy_bool_tag::*safe_bool)();

	operator safe_bool() const{
		return is_true() ? &dummy_bool_tag::safe_true : (safe_bool)0;
	}

#else

	/**
	* \brief boolean�ւ̎����ϊ�
	*/
	operator bool() const{
		return is_true();
	}

#endif

	/**
	* \biref !���Z�q
	*/
	bool operator !() const{
		return !is_true();
	}

private:

	/**
	* \brief �Öق̕ϊ���}���邽�߂̃R���X�g���N�^�B
	* ���̂̒m��Ȃ��|�C���^����̍\�z�����ۂ��邽�߁A���̃R���X�g���N�^��private�Ŏ��������݂��Ȃ��B
	*/
	SmartPtr(void*);

	/**
	* \brief �Öق̕ϊ���}���邽�߂̃R���X�g���N�^�B
	* ���̂̒m��Ȃ��֐��|�C���^����̍\�z�����ۂ��邽�߁A���̃R���X�g���N�^��private�Ŏ��������݂��Ȃ��B
	*/
	template<class R> SmartPtr(R (*a)());
	template<class R, class A1> SmartPtr(R (*a)(A1));
	template<class R, class A1, class A2> SmartPtr(R (*a)(A1, A2));

};

///////////////////////////////////////////

template<int N, class T>
struct Extract{};

template<class T>
struct Extract<INHERITED_BASE, T>{
	static T* extract(const AnyPtr& a){
		return static_cast<T*>(pvalue(a));
	}
};

template<class T>
struct Extract<INHERITED_RCBASE, T>{
	static T* extract(const AnyPtr& a){
		return static_cast<T*>(rcpvalue(a));
	}
};

template<class T>
struct Extract<INHERITED_ANY, T>{
	static T* extract(const AnyPtr& a){
		return reinterpret_cast<T*>(const_cast<AnyPtr*>(&a));
	}
};

template<class T>
struct Extract<INHERITED_OTHER, T>{
	static T* extract(const AnyPtr& a){
		if(type(a)==TYPE_BASE){
			return static_cast<T*>((static_cast<UserTypeHolder*>(pvalue(a)))->ptr); 
		}
		else{
			return static_cast<T*>(rawvalue(a).vp());
		}
	}
};

/////////////////////////////////////////////////////////////////////////////

template<int N, class T>
struct GetNull{};

template<class T>
struct GetNull<INHERITED_BASE, T>{
	static T* get(){ return 0; }
};

template<class T>
struct GetNull<INHERITED_RCBASE, T>{
	static T* get(){ return 0; }
};

template<class T>
struct GetNull<INHERITED_ANY, T>{
	static T* get(){ return (T*)&null; }
};

template<class T>
struct GetNull<INHERITED_OTHER, T>{
	static T* get(){ return 0; }
};

/////////////////////////////////////////////////

void visit_members(Visitor& m, const Any& p);

class Visitor{
	int_t value_;
public:	

	Visitor(int_t value){
		value_ = value;
	}

	int_t value(){
		return value_;
	}

	template<class T> Visitor& operator &(T& value){
		visit_members(*this, value);
		return *this;
	}

	template<class T> Visitor& operator ()(T& value){
		visit_members(*this, value);
		return *this;
	}
};

inline const AnyPtr& ap(const Any& v){
	return (const AnyPtr&)v;
}

template<class F, class S>
void visit_members(Visitor& m, const std::pair<F, S>& value){
	m & value.first & value.second;
}

/////////////////////////////////////////////////

struct BindBase{
	void XTAL_set(BindBase*& dest, StringLiteral& name,  const StringLiteral& given);
	virtual void XTAL_bind(const ClassPtr& it) = 0;
};

struct CppClassSymbolData{ 
	CppClassSymbolData();

	enum{
		BIND = 3
	};

	unsigned int value;

	BindBase* prebind;
	BindBase* bind[BIND];
	
	StringLiteral name;

	CppClassSymbolData* prev;
};

template<class T>
struct CppClassSymbol{
	static CppClassSymbolData* value;
	static CppClassSymbolData* make();

	typedef T type;
};

template<class T>
CppClassSymbolData* CppClassSymbol<T>::make(){
	static CppClassSymbolData data;
	return &data;
}

template<class T>
CppClassSymbolData* CppClassSymbol<T>::value = CppClassSymbol<T>::make();

// CppClassSymbol�̏C���q���͂������߂̒�`
template<class T> struct CppClassSymbol<T&> : public CppClassSymbol<T>{};
template<class T> struct CppClassSymbol<T*> : public CppClassSymbol<T>{};
template<class T> struct CppClassSymbol<const T> : public CppClassSymbol<T>{};
template<class T> struct CppClassSymbol<volatile T> : public CppClassSymbol<T>{};
template<class T> struct CppClassSymbol<SmartPtr<T> > : public CppClassSymbol<T>{};
template<class T, class Deleter> struct CppClassSymbol<UserTypeHolderSub<T, Deleter> > : public CppClassSymbol<T>{};

template<> struct CppClassSymbol<Base> : public CppClassSymbol<Any>{};
template<> struct CppClassSymbol<ID> : public CppClassSymbol<String>{};

#define XTAL_BIND_(ClassName, xtbind, xtname, N) \
	template<class T> struct XTAL_bind_template##N;\
	template<> struct XTAL_bind_template##N<ClassName> : public ::xtal::BindBase{\
		typedef ClassName Self;\
		XTAL_bind_template##N(){\
			::xtal::CppClassSymbolData* key = ::xtal::CppClassSymbol<ClassName>::make();\
			XTAL_set(key->xtbind, key->name, xtname);\
		}\
		virtual void XTAL_bind(const ::xtal::ClassPtr& it);\
	};\
	static volatile XTAL_bind_template##N<ClassName> XTAL_UNIQUE(XTAL_bind_variable##N);\
	inline void XTAL_bind_template##N<ClassName>::XTAL_bind(const ::xtal::ClassPtr& it)


#define XTAL_PREBIND(ClassName) XTAL_BIND_(ClassName, prebind, XTAL_STRING(#ClassName), 0)
#define XTAL_BIND(ClassName) XTAL_BIND_(ClassName, bind[0], XTAL_STRING(#ClassName), 1)
#define XTAL_BIND2(ClassName) XTAL_BIND_(ClassName, bind[1], XTAL_STRING(#ClassName), 2)
#define XTAL_BIND3(ClassName) XTAL_BIND_(ClassName, bind[2], XTAL_STRING(#ClassName), 3)

#define XTAL_NAMED_PREBIND(ClassName, Name) XTAL_BIND_(ClassName, prebind, XTAL_STRING(#Name), 0)
#define XTAL_NAMED_BIND(ClassName, Name) XTAL_BIND_(ClassName, bind, XTAL_STRING(#Name), 1)

////////////////////////////////////

typedef AnyPtr (*bind_var_fun_t)();

struct CppVarSymbolData{ 
	CppVarSymbolData(bind_var_fun_t fun);

	CppVarSymbolData* prev;
	bind_var_fun_t maker;
	unsigned int value;
};

template<class T>
struct CppVarSymbol{
	static CppVarSymbolData value;
	static AnyPtr maker(){ return xnew<T>(); }
};

template<class T>
CppVarSymbolData CppVarSymbol<T>::value(&CppVarSymbol<T>::maker);

}//namespace 

#endif // XTAL_ANYPTR_H_INCLUDE_GUARD
