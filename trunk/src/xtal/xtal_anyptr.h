
#pragma once

namespace xtal{

template<uint_t Size>
struct UserTypeBuffer{
	union{
		u8 buf[Size];
		int_t dummy;
	};

	template<class T>
	void operator()(T* p){
		p->~T();
	}
};

template<class T>
struct UserTypeHolder : public Base{
	UserTypeHolder(){}
	UserTypeHolder(T* p):ptr(p){}
	T* ptr;
};

template<class T, class Deleter = UserTypeBuffer<sizeof(T)> >
struct UserTypeHolderSub : public UserTypeHolder<T>{
	UserTypeHolderSub(){}
	UserTypeHolderSub(T* p, Deleter f):UserTypeHolder<T>(p), fun(f){}
	virtual ~UserTypeHolderSub(){ fun(this->ptr); }
	Deleter fun;
};

struct undeleter_t{
	template<class T>
	void operator()(T* p){}
};

struct deleter_t{
	template<class T>
	void operator()(T* p){
		delete p;
	}
};

extern undeleter_t undeleter;
extern deleter_t deleter;

template<class T>
struct XNewEssence0{};

template<class T, class A0>
struct XNewEssence1{
	A0 a0;
	XNewEssence1(const A0& a0)
		:a0(a0){}
};

template<class T, class A0, class A1>
struct XNewEssence2{
	A0 a0;
	A1 a1;
	XNewEssence2(const A0& a0, const A1& a1)
		:a0(a0), a1(a1){}
};

enum InheritedEnum{
	INHERITED_BASE,
	INHERITED_ANY,
	INHERITED_OTHER
};

template<class T>
struct InheritedN{
	enum{
		value = IsInherited<T, Base>::value ? INHERITED_BASE : 
			IsInherited<T, Any>::value ? INHERITED_ANY : INHERITED_OTHER
	};
};

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

template <int N>
struct SmartPtrSelector{};

/**
* @brief ���̌^�̃I�u�W�F�N�g�ł��ێ�������ꉻ���ꂽ�X�}�[�g�|�C���^
*/
template<>
class SmartPtr<Any> : public Any{
public:
	
	SmartPtr(){}

	template<class T, class Deleter>
	SmartPtr(T* p, Deleter deleter){
		UserTypeHolderSub<T, Deleter>* holder = new UserTypeHolderSub<T, Deleter>(p, deleter);
		set_p_with_class(holder, new_cpp_class<T>());
	}

	SmartPtr(const SmartPtr<Any>& p)
		:Any(p){
		inc_ref_count();
	}

	SmartPtr<Any>& operator =(const Null&){
		dec_ref_count();
		set_null_force(*this);
		return *this;
	}

	SmartPtr<Any>& operator =(const Undefined&){
		dec_ref_count();
		set_undefined_force(*this);
		return *this;
	}

	SmartPtr<Any>& operator =(const SmartPtr<Any>& p);

	explicit SmartPtr(PrimitiveType type)
		:Any(type){}

	explicit SmartPtr(Base* p)
		:Any(p){
		p->inc_ref_count();
	}

	~SmartPtr(){
		dec_ref_count();
		//*(Any*)this = Any();
	}

protected:

	explicit SmartPtr(const Any& innocence)
		:Any(innocence){}

	struct with_class_t{};

	SmartPtr(Base* p, const ClassPtr& c, with_class_t);

	SmartPtr(Singleton* p, const ClassPtr& c, with_class_t);

	SmartPtr(CppSingleton* p, const ClassPtr& c, with_class_t);

	void set_p_with_class(Base* p, const ClassPtr& c);

	void inc_ref_count(){
		if(type(*this)==TYPE_BASE){
			pvalue(*this)->inc_ref_count();
		}
	}

	void dec_ref_count(){
		if(type(*this)==TYPE_BASE){
			pvalue(*this)->dec_ref_count();
		}
	}

public:

	/**
	* @brief �����l����\�z����R���X�g���N�^�B
	*
	*/
	SmartPtr(int_t v){ set_i(v); }
	
	/**
	* @brief ���������_���l����\�z����R���X�g���N�^�B
	*
	*/
	SmartPtr(float_t v){ set_f(v); }
	
	/**
	* @brief �����񂩂�\�z����R���X�g���N�^�B
	*
	*/
	SmartPtr(bool b){ set_b(b); }

	/**
	* @brief �����񂩂�\�z����R���X�g���N�^�B
	*
	*/
	SmartPtr(const char_t* str)
		:Any(str){
		inc_ref_count();
	}

	/**
	* @brief �����񂩂�\�z����R���X�g���N�^�B
	*
	*/
	SmartPtr(const avoid<char>::type* str)
		:Any(str){
		inc_ref_count();
	}

	// ��{�^�̐����A���������_������\�z����R���X�g���N�^
	SmartPtr(avoid<int>::type v){ set_i((int_t)v); }
	SmartPtr(avoid<long>::type v){ set_i((int_t)v); }
	SmartPtr(avoid<short>::type v){ set_i((int_t)v); }
	SmartPtr(avoid<char>::type v){ set_i((int_t)v); }
	SmartPtr(avoid<unsigned int>::type v){ set_i((int_t)v); }
	SmartPtr(avoid<unsigned long>::type v){ set_i((int_t)v); }
	SmartPtr(avoid<unsigned short>::type v){ set_i((int_t)v); }
	SmartPtr(avoid<unsigned char>::type v){ set_i((int_t)v); }
	SmartPtr(avoid<signed char>::type v){ set_i((int_t)v); }
	SmartPtr(avoid<float>::type v){ set_f((float_t)v); }
	SmartPtr(avoid<double>::type v){ set_f((float_t)v); }
	SmartPtr(avoid<long double>::type v){ set_f((float_t)v); }

public:

	/**
	* @brief ->���Z�q
	* �X�}�[�g�|�C���^�Ƃ��Ĉ������߂ɃI�[�o�[���[�h����B
	*/
	Any* operator ->() const{ return get(); }
	
	/**
	* @brief *���Z�q
	* �X�}�[�g�|�C���^�Ƃ��Ĉ������߂ɃI�[�o�[���[�h����B
	*/
	Any& operator *() const{ return *get(); }
	
	/**
	* @brief T�^�ւ̃|�C���^���擾����B
	*/
	Any* get() const{ return (Any*)this; }

public:

	friend inline const AnyPtr& ap(const Any& v){
		return (const AnyPtr&)v;
	}

	friend inline SmartPtr<Any>& ap_copy(SmartPtr<Any>& a, const SmartPtr<Any>& b){
		a.dec_ref_count();
		*(Any*)&a = b;
		a.inc_ref_count();
		return a;
	}

private:

	struct dummy_bool_tag{ void safe_true(dummy_bool_tag){} };
	typedef void (dummy_bool_tag::*safe_bool)(dummy_bool_tag);

public:
	
	/**
	* @brief bool�^�Ɏ����ϊ�����B
	*
	*/
	operator safe_bool() const{
		return type((*this)->self())>TYPE_FALSE ? &dummy_bool_tag::safe_true : (safe_bool)0;
	}

	bool operator !() const{
		return type((*this)->self())<=TYPE_FALSE;
	}

public:

	template<class U>
	SmartPtr(XNewEssence0<U>)
		:Any(Any::noinit_t()){
		gene<U>(SmartPtrSelector<InheritedN<U>::value>());
	}
	
	template<class U>
	SmartPtr& operator= (XNewEssence0<U>){
		dec_ref_count();
		gene<U>(SmartPtrSelector<InheritedN<U>::value>());
		return *this;
	}

public:

	template<class U, class A0>
	SmartPtr(const XNewEssence1<U, A0>& x)
		:Any(Any::noinit_t()){
		gene<U>(SmartPtrSelector<InheritedN<U>::value>(), x.a0);
	}
	
	template<class U, class A0>
	SmartPtr& operator= (const XNewEssence1<U, A0>& x){
		dec_ref_count();
		gene<U>(SmartPtrSelector<InheritedN<U>::value>(), x.a0);
		return *this;
	}

public:

	template<class U, class A0, class A1>
	SmartPtr(const XNewEssence2<U, A0, A1>& x)
		:Any(Any::noinit_t()){
		gene<U>(SmartPtrSelector<InheritedN<U>::value>(), x.a0, x.a1);
	}
	
	template<class U, class A0, class A1>
	SmartPtr& operator= (const XNewEssence2<U, A0, A1>& x){
		dec_ref_count();
		gene<U>(SmartPtrSelector<InheritedN<U>::value>(), x.a0, x.a1);
		return *this;
	}

protected:

	template<class U>
	void gene(SmartPtrSelector<INHERITED_BASE>){
		set_p_with_class(new U(), new_cpp_class<U>());
	}

	template<class U>
	void gene(SmartPtrSelector<INHERITED_ANY>){
		Any::operator =(U());
	}

	template<class U>
	void gene(SmartPtrSelector<INHERITED_OTHER>){
		set_p_with_class(new UserTypeHolderSub<U>(), new_cpp_class<U>());
		UserTypeHolderSub<U>* p = ((UserTypeHolderSub<U>*)pvalue(*this));
		p->ptr = (U*)&p->fun;
		new(p->ptr) U;
	}

protected:

	template<class U, class A0>
	void gene(SmartPtrSelector<INHERITED_BASE>, const A0& a0){
		set_p_with_class(new U(a0), new_cpp_class<U>());
	}

	template<class U, class A0>
	void gene(SmartPtrSelector<INHERITED_ANY>, const A0& a0){
		Any::operator =(U(a0));
	}

	template<class U, class A0>
	void gene(SmartPtrSelector<INHERITED_OTHER>, const A0& a0){
		set_p_with_class(new UserTypeHolderSub<U>(), new_cpp_class<U>());
		UserTypeHolderSub<U>* p = ((UserTypeHolderSub<U>*)pvalue(*this));
		p->ptr = (U*)&p->fun;
		new(p->ptr) U(a0);
	}

protected:

	template<class U, class A0, class A1>
	void gene(SmartPtrSelector<INHERITED_BASE>, const A0& a0, const A1& a1){
		set_p_with_class(new U(a0, a1), new_cpp_class<U>());
	}

	template<class U, class A0, class A1>
	void gene(SmartPtrSelector<INHERITED_ANY>, const A0& a0, const A1& a1){
		Any::operator =(U(a0, a1));
	}

	template<class U, class A0, class A1>
	void gene(SmartPtrSelector<INHERITED_OTHER>, const A0& a0, const A1& a1){
		set_p_with_class(new UserTypeHolderSub<U>(), new_cpp_class<U>());
		UserTypeHolderSub<U>* p = ((UserTypeHolderSub<U>*)pvalue(*this));
		p->ptr = (U*)&p->fun;
		new(p->ptr) U(a0, a1);
	}

private:

	/**
	* @brief �Öق̕ϊ���}���邽�߂̃R���X�g���N�^�B
	*
	* ���̂̒m��Ȃ��|�C���^����̍\�z�����ۂ��邽�߁A���̃R���X�g���N�^��private�Ŏ��������݂��Ȃ��B
	*/
	SmartPtr(void*);

};


class Null : public AnyPtr{};
class Undefined : public AnyPtr{ public: Undefined():AnyPtr(TYPE_UNDEFINED){} };

inline bool operator ==(const AnyPtr& a, const Null&){ return raweq(a, null); }
inline bool operator !=(const AnyPtr& a, const Null&){ return rawne(a, null); }
inline bool operator ==(const Null&, const AnyPtr& a){ return raweq(a, null); }
inline bool operator !=(const Null&, const AnyPtr& a){ return rawne(a, null); }

inline bool operator ==(const AnyPtr& a, const Undefined&){ return raweq(a, undefined); }
inline bool operator !=(const AnyPtr& a, const Undefined&){ return rawne(a, undefined); }
inline bool operator ==(const Undefined&, const AnyPtr& a){ return raweq(a, undefined); }
inline bool operator !=(const Undefined&, const AnyPtr& a){ return rawne(a, undefined); }


}//namespace 
