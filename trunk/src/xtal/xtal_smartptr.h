/** \file src/xtal/xtal_smartptr.h
* \brief src/xtal/xtal_smartptr.h
*/

#ifndef XTAL_SMARTPTR_H_INCLUDE_GUARD
#define XTAL_SMARTPTR_H_INCLUDE_GUARD

#pragma once

namespace xtal{

/**
* \brief T�^�ւ̃|�C���^��ێ����邽�߂̃X�}�[�g�|�C���^
*/
template<class T>
class SmartPtr : public SmartPtr<Any>{
public:

	SmartPtr(){}

public:

	SmartPtr(const T* p)
		:SmartPtr<Any>(p){}

public:

	template<class Deleter>
	SmartPtr(const T* p, const Deleter& deleter)
		:SmartPtr<Any>(p, deleter){}

public:

	template<class U>
	SmartPtr(const SmartPtr<U>& p)
		:SmartPtr<Any>(p){
		check_inherit<U>();
	}
	
	template<class U>
	SmartPtr<T>& operator =(const SmartPtr<U>& p){
		check_inherit<U>();
		SmartPtr<Any>::operator =(p);
		return *this;
	}

public:

	SmartPtr(const NullPtr&){}

	SmartPtr<T>& operator =(const NullPtr& null){
		SmartPtr<Any>::operator =(null);
		return *this;
	}

public:
	
	template<class U>
	SmartPtr(const XNew<U>& x)
		:SmartPtr<Any>(x){
		check_inherit<U>();
	}

	template<class U>
	SmartPtr<T>& operator =(const XNew<U>& x){
		check_inherit<U>();
		SmartPtr<Any>::operator =(x);
		return *this;
	}

public:

	/// ���ʂȃR���X�g���N�^1
	SmartPtr(typename SmartPtrCtor1<T>::type v)
		:SmartPtr<Any>(XNew<T>(v)){}

	/// ���ʂȃR���X�g���N�^2
	SmartPtr(typename SmartPtrCtor2<T>::type v)
		:SmartPtr<Any>(XNew<T>(v)){}

	/// ���ʂȃR���X�g���N�^3
	SmartPtr(typename SmartPtrCtor3<T>::type v)
		:SmartPtr<Any>(XNew<T>(v)){}

	/// ���ʂȃR���X�g���N�^4
	SmartPtr(typename SmartPtrCtor4<T>::type v)
		:SmartPtr<Any>(XNew<T>(v)){}

	template<class U>
	SmartPtr<T>& operator =(typename SmartPtrCtor1<T>::type v){
		SmartPtr<Any>::operator =(XNew<T>(v));
		return *this;
	}

	template<class U>
	SmartPtr<T>& operator =(typename SmartPtrCtor2<T>::type v){
		SmartPtr<Any>::operator =(XNew<T>(v));
		return *this;
	}

	template<class U>
	SmartPtr<T>& operator =(typename SmartPtrCtor3<T>::type v){
		SmartPtr<Any>::operator =(XNew<T>(v));
		return *this;
	}

	template<class U>
	SmartPtr<T>& operator =(typename SmartPtrCtor4<T>::type v){
		SmartPtr<Any>::operator =(XNew<T>(v));
		return *this;
	}
private:

	template<class U>
	void check_inherit(){
		// �p���֌W�������Ń`�F�b�N���Ă���B
		// �����ŃR���p�C���G���[�ɂȂ�ꍇ�A
		// ptr_cast�֐������g�p���Č^��ϊ�����K�v������B
		T* n = (U*)0; 
		XTAL_UNUSED_VAR(n);
	}

	/**
	* \brief �Öق̕ϊ���}���邽�߂̃R���X�g���N�^�B
	*
	* AnyPtr����̈Öق̕ϊ������ۂ��邽�߂ɁAprivate�Œ�`����Ă���B
	* AnyPtr����SmartPtr<T>�ɕϊ�����ɂ�ptr_cast�֐��Aptr_cast�֐����g�p���邱�ƁB
	*/
	//SmartPtr(const AnyPtr&);

	/**
	* \brief �Öق̕ϊ���}���邽�߂̃R���X�g���N�^�B
	*
	* ���̂̒m��Ȃ��|�C���^�^����̈Öق̕ϊ������ۂ��邽�߂ɁAprivate�Œ�`����Ă���B
	*
	* Base�N���X���p�����Ă��Ȃ�A�Ƃ����N���X�������������ꍇ�A
	* SmartPtr<A> p = xnew<A>(); 
	* ��xnew�ō��o�����A
	* SmartPtr<A> p = SmartPtr<A>(new A, deleter);
	* �ƃR���X�g���N�^��new�Ő��������|�C���^��deleter��n����
	* static A static_a;
	* SmartPtr<A> p = SmartPtr<A>(&static_a, undeleter);
	* �Ǝ����������I�u�W�F�N�g�ւ̃|�C���^��undeleter��n�����A
	* �܂��͓Ǝ���deleter���`���ēn�����@���Ƃ邱�ƁB
	*/
	SmartPtr(void*);

public:

	/**
	* \brief T�^�ւ̃|�C���^���擾����B
	*/
	T* get() const{ return Extract<InheritedN<T>::value, T>::extract(*this); }

	/**
	* \brief ->���Z�q
	* �X�}�[�g�|�C���^�Ƃ��ĐU�������߂ɁB
	*/
	T* operator ->() const{ return get(); }
	
	/**
	* \brief *���Z�q
	* �X�}�[�g�|�C���^�Ƃ��ĐU�������߂ɁB
	*/
	T& operator *() const{ return *get(); }
};

/// \name �I�u�W�F�N�g����
//@{

enum XNewEnum{
	XNEW_NONE,
	XNEW_BASE,
	XNEW_ANY,
	XNEW_OTHER
};

template<class T>
struct XNewN{
	enum{
		value = 
			IsInherited<T, RefCountingBase>::value ? XNEW_BASE : 
			IsInherited<T, Any>::value ? XNEW_ANY : XNEW_OTHER
	};
};

template<class T, int N = XNEW_NONE>
struct XXNew;

template<class T>
struct XXNew<T, XNEW_NONE> : XXNew<T, XNewN<T>::value>{};

template<class T>
T* make_object(){
	T* p = object_xmalloc<T>();
	p->special_initialize(&VirtualMembersT<T>::value);
	return p;
}

void register_gc(RefCountingBase* p);

template<class T>
struct XXNew<T, XNEW_BASE> : public Any{

	void post(T* ret){
		Any::init(ret);
	}

	void init(){
		post(new(make_object<T>()) T);	
	}

//{REPEAT{{
/*
	template<class A0 #COMMA_REPEAT#class A`i+1`#>
	void init(const A0& a0 #COMMA_REPEAT#const A`i+1`& a`i+1`#){
		post(new(make_object<T>()) T(a0 #COMMA_REPEAT#a`i+1`#));	
	}
*/

	template<class A0 >
	void init(const A0& a0 ){
		post(new(make_object<T>()) T(a0 ));	
	}

	template<class A0 , class A1>
	void init(const A0& a0 , const A1& a1){
		post(new(make_object<T>()) T(a0 , a1));	
	}

	template<class A0 , class A1, class A2>
	void init(const A0& a0 , const A1& a1, const A2& a2){
		post(new(make_object<T>()) T(a0 , a1, a2));	
	}

	template<class A0 , class A1, class A2, class A3>
	void init(const A0& a0 , const A1& a1, const A2& a2, const A3& a3){
		post(new(make_object<T>()) T(a0 , a1, a2, a3));	
	}

	template<class A0 , class A1, class A2, class A3, class A4>
	void init(const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4){
		post(new(make_object<T>()) T(a0 , a1, a2, a3, a4));	
	}

	template<class A0 , class A1, class A2, class A3, class A4, class A5>
	void init(const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5){
		post(new(make_object<T>()) T(a0 , a1, a2, a3, a4, a5));	
	}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6>
	void init(const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6){
		post(new(make_object<T>()) T(a0 , a1, a2, a3, a4, a5, a6));	
	}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7>
	void init(const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7){
		post(new(make_object<T>()) T(a0 , a1, a2, a3, a4, a5, a6, a7));	
	}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
	void init(const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8){
		post(new(make_object<T>()) T(a0 , a1, a2, a3, a4, a5, a6, a7, a8));	
	}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
	void init(const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9){
		post(new(make_object<T>()) T(a0 , a1, a2, a3, a4, a5, a6, a7, a8, a9));	
	}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
	void init(const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10){
		post(new(make_object<T>()) T(a0 , a1, a2, a3, a4, a5, a6, a7, a8, a9, a10));	
	}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11>
	void init(const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11){
		post(new(make_object<T>()) T(a0 , a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11));	
	}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12>
	void init(const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11, const A12& a12){
		post(new(make_object<T>()) T(a0 , a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12));	
	}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13>
	void init(const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11, const A12& a12, const A13& a13){
		post(new(make_object<T>()) T(a0 , a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13));	
	}

//}}REPEAT}

};

template<class T>
struct XXNew<T, XNEW_ANY> : public Any{

	void init(){
		Any::operator=(T());
	}

//{REPEAT{{
/*
	template<class A0 #COMMA_REPEAT#class A`i+1`#>
	void init(const A0& a0 #COMMA_REPEAT#const A`i+1`& a`i+1`#){
		Any::operator=(T(a0 #COMMA_REPEAT#a`i+1`#));		
	}
*/

	template<class A0 >
	void init(const A0& a0 ){
		Any::operator=(T(a0 ));		
	}

	template<class A0 , class A1>
	void init(const A0& a0 , const A1& a1){
		Any::operator=(T(a0 , a1));		
	}

	template<class A0 , class A1, class A2>
	void init(const A0& a0 , const A1& a1, const A2& a2){
		Any::operator=(T(a0 , a1, a2));		
	}

	template<class A0 , class A1, class A2, class A3>
	void init(const A0& a0 , const A1& a1, const A2& a2, const A3& a3){
		Any::operator=(T(a0 , a1, a2, a3));		
	}

	template<class A0 , class A1, class A2, class A3, class A4>
	void init(const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4){
		Any::operator=(T(a0 , a1, a2, a3, a4));		
	}

	template<class A0 , class A1, class A2, class A3, class A4, class A5>
	void init(const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5){
		Any::operator=(T(a0 , a1, a2, a3, a4, a5));		
	}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6>
	void init(const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6){
		Any::operator=(T(a0 , a1, a2, a3, a4, a5, a6));		
	}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7>
	void init(const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7){
		Any::operator=(T(a0 , a1, a2, a3, a4, a5, a6, a7));		
	}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
	void init(const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8){
		Any::operator=(T(a0 , a1, a2, a3, a4, a5, a6, a7, a8));		
	}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
	void init(const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9){
		Any::operator=(T(a0 , a1, a2, a3, a4, a5, a6, a7, a8, a9));		
	}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
	void init(const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10){
		Any::operator=(T(a0 , a1, a2, a3, a4, a5, a6, a7, a8, a9, a10));		
	}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11>
	void init(const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11){
		Any::operator=(T(a0 , a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11));		
	}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12>
	void init(const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11, const A12& a12){
		Any::operator=(T(a0 , a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12));		
	}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13>
	void init(const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11, const A12& a12, const A13& a13){
		Any::operator=(T(a0 , a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13));		
	}

//}}REPEAT}
};

template<class T>
struct XXNew<T, XNEW_OTHER> : public Any{
	typedef UserTypeHolderSub<T> holder;

	static holder* pre(){
		holder* ret = new(make_object<holder>()) holder;
		ret->ptr = static_cast<T*>(static_cast<void*>(ret->buffer()));
		return ret;
	}

	void post(holder* ret){
		Any::init(ret);
	}

	void init(){
		holder* ret = pre(); new(ret->ptr) T; post(ret);
	}

//{REPEAT{{
/*
	template<class A0 #COMMA_REPEAT#class A`i+1`#>
	void init(const A0& a0 #COMMA_REPEAT#const A`i+1`& a`i+1`#){
		holder* ret = pre(); new(ret->ptr) T(a0 #COMMA_REPEAT#a`i+1`#); post(ret);
	}
*/

	template<class A0 >
	void init(const A0& a0 ){
		holder* ret = pre(); new(ret->ptr) T(a0 ); post(ret);
	}

	template<class A0 , class A1>
	void init(const A0& a0 , const A1& a1){
		holder* ret = pre(); new(ret->ptr) T(a0 , a1); post(ret);
	}

	template<class A0 , class A1, class A2>
	void init(const A0& a0 , const A1& a1, const A2& a2){
		holder* ret = pre(); new(ret->ptr) T(a0 , a1, a2); post(ret);
	}

	template<class A0 , class A1, class A2, class A3>
	void init(const A0& a0 , const A1& a1, const A2& a2, const A3& a3){
		holder* ret = pre(); new(ret->ptr) T(a0 , a1, a2, a3); post(ret);
	}

	template<class A0 , class A1, class A2, class A3, class A4>
	void init(const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4){
		holder* ret = pre(); new(ret->ptr) T(a0 , a1, a2, a3, a4); post(ret);
	}

	template<class A0 , class A1, class A2, class A3, class A4, class A5>
	void init(const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5){
		holder* ret = pre(); new(ret->ptr) T(a0 , a1, a2, a3, a4, a5); post(ret);
	}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6>
	void init(const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6){
		holder* ret = pre(); new(ret->ptr) T(a0 , a1, a2, a3, a4, a5, a6); post(ret);
	}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7>
	void init(const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7){
		holder* ret = pre(); new(ret->ptr) T(a0 , a1, a2, a3, a4, a5, a6, a7); post(ret);
	}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
	void init(const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8){
		holder* ret = pre(); new(ret->ptr) T(a0 , a1, a2, a3, a4, a5, a6, a7, a8); post(ret);
	}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
	void init(const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9){
		holder* ret = pre(); new(ret->ptr) T(a0 , a1, a2, a3, a4, a5, a6, a7, a8, a9); post(ret);
	}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
	void init(const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10){
		holder* ret = pre(); new(ret->ptr) T(a0 , a1, a2, a3, a4, a5, a6, a7, a8, a9, a10); post(ret);
	}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11>
	void init(const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11){
		holder* ret = pre(); new(ret->ptr) T(a0 , a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11); post(ret);
	}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12>
	void init(const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11, const A12& a12){
		holder* ret = pre(); new(ret->ptr) T(a0 , a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12); post(ret);
	}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13>
	void init(const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11, const A12& a12, const A13& a13){
		holder* ret = pre(); new(ret->ptr) T(a0 , a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13); post(ret);
	}

//}}REPEAT}
};

template<class T>
struct XNew : XXNew<T>{
	typedef XXNew<T> Super;

	XNew(){
		Super::init();
	}

//{REPEAT{{
/*
	template<class A0 #COMMA_REPEAT#class A`i+1`#>
	XNew(const A0& a0 #COMMA_REPEAT#const A`i+1`& a`i+1`#){
		Super::init(a0 #COMMA_REPEAT#a`i+1`#);
	}
*/

	template<class A0 >
	XNew(const A0& a0 ){
		Super::init(a0 );
	}

	template<class A0 , class A1>
	XNew(const A0& a0 , const A1& a1){
		Super::init(a0 , a1);
	}

	template<class A0 , class A1, class A2>
	XNew(const A0& a0 , const A1& a1, const A2& a2){
		Super::init(a0 , a1, a2);
	}

	template<class A0 , class A1, class A2, class A3>
	XNew(const A0& a0 , const A1& a1, const A2& a2, const A3& a3){
		Super::init(a0 , a1, a2, a3);
	}

	template<class A0 , class A1, class A2, class A3, class A4>
	XNew(const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4){
		Super::init(a0 , a1, a2, a3, a4);
	}

	template<class A0 , class A1, class A2, class A3, class A4, class A5>
	XNew(const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5){
		Super::init(a0 , a1, a2, a3, a4, a5);
	}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6>
	XNew(const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6){
		Super::init(a0 , a1, a2, a3, a4, a5, a6);
	}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7>
	XNew(const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7){
		Super::init(a0 , a1, a2, a3, a4, a5, a6, a7);
	}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
	XNew(const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8){
		Super::init(a0 , a1, a2, a3, a4, a5, a6, a7, a8);
	}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
	XNew(const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9){
		Super::init(a0 , a1, a2, a3, a4, a5, a6, a7, a8, a9);
	}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
	XNew(const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10){
		Super::init(a0 , a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
	}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11>
	XNew(const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11){
		Super::init(a0 , a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11);
	}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12>
	XNew(const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11, const A12& a12){
		Super::init(a0 , a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12);
	}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13>
	XNew(const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11, const A12& a12, const A13& a13){
		Super::init(a0 , a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13);
	}

//}}REPEAT}

};

template<class T>
inline SmartPtr<T> xnew(){
	return XNew<T>();
}

//{REPEAT{{
/*
template<class T, class A0 #COMMA_REPEAT#class A`i+1`#>
inline SmartPtr<T> xnew(const A0& a0 #COMMA_REPEAT#const A`i+1`& a`i+1`#){
	return XNew<T>(a0 #COMMA_REPEAT#a`i+1`#);
}
*/

template<class T, class A0 >
inline SmartPtr<T> xnew(const A0& a0 ){
	return XNew<T>(a0 );
}

template<class T, class A0 , class A1>
inline SmartPtr<T> xnew(const A0& a0 , const A1& a1){
	return XNew<T>(a0 , a1);
}

template<class T, class A0 , class A1, class A2>
inline SmartPtr<T> xnew(const A0& a0 , const A1& a1, const A2& a2){
	return XNew<T>(a0 , a1, a2);
}

template<class T, class A0 , class A1, class A2, class A3>
inline SmartPtr<T> xnew(const A0& a0 , const A1& a1, const A2& a2, const A3& a3){
	return XNew<T>(a0 , a1, a2, a3);
}

template<class T, class A0 , class A1, class A2, class A3, class A4>
inline SmartPtr<T> xnew(const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4){
	return XNew<T>(a0 , a1, a2, a3, a4);
}

template<class T, class A0 , class A1, class A2, class A3, class A4, class A5>
inline SmartPtr<T> xnew(const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5){
	return XNew<T>(a0 , a1, a2, a3, a4, a5);
}

template<class T, class A0 , class A1, class A2, class A3, class A4, class A5, class A6>
inline SmartPtr<T> xnew(const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6){
	return XNew<T>(a0 , a1, a2, a3, a4, a5, a6);
}

template<class T, class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7>
inline SmartPtr<T> xnew(const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7){
	return XNew<T>(a0 , a1, a2, a3, a4, a5, a6, a7);
}

template<class T, class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
inline SmartPtr<T> xnew(const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8){
	return XNew<T>(a0 , a1, a2, a3, a4, a5, a6, a7, a8);
}

template<class T, class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
inline SmartPtr<T> xnew(const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9){
	return XNew<T>(a0 , a1, a2, a3, a4, a5, a6, a7, a8, a9);
}

template<class T, class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
inline SmartPtr<T> xnew(const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10){
	return XNew<T>(a0 , a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
}

template<class T, class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11>
inline SmartPtr<T> xnew(const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11){
	return XNew<T>(a0 , a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11);
}

template<class T, class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12>
inline SmartPtr<T> xnew(const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11, const A12& a12){
	return XNew<T>(a0 , a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12);
}

template<class T, class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13>
inline SmartPtr<T> xnew(const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11, const A12& a12, const A13& a13){
	return XNew<T>(a0 , a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13);
}

//}}REPEAT}

//@}

//////////////////////////////////////////////////////////////

template<int N, class T>
struct ToSmartPtr{};

template<class T>
struct ToSmartPtr<INHERITED_BASE, T>{
	static const SmartPtr<T>& to(const T* p){
		return *static_cast<SmartPtr<T>*>(static_cast<Any*>(const_cast<T*>(p)));
	}
};

template<class T>
struct ToSmartPtr<INHERITED_RCBASE, T>{
	static const SmartPtr<T>& to(const T* p){
		return *static_cast<SmartPtr<T>*>(static_cast<Any*>(const_cast<T*>(p)));
	}
};

template<class T>
struct ToSmartPtr<INHERITED_ANY, T>{
	static const SmartPtr<T>& to(const T* p){
		return *static_cast<SmartPtr<T>*>(static_cast<Any*>(const_cast<T*>(p)));
	}
};

/**
* \brief T*��const SmartPtr<T>&�ɕϊ�����֐�
*/
template<class T>
inline const SmartPtr<T>& to_smartptr(const T* p){
	return ToSmartPtr<InheritedN<T>::value, T>::to(p);
}

/**
* \brief SmartPtr<T>�^��null���擾����֐�
*/
template<class T>
inline const SmartPtr<T>& nul(){
	return *reinterpret_cast<SmartPtr<T>*>(&null);
}

//////////////////////////////////////////////////////////////

// SmartPtr�̏d�˒����R���p�C���G���[�Ƃ��邽�߂̒�`
template<class T>
class SmartPtr< SmartPtr<T> >;

//////////////////////////////////////////////////////////////

template<> 
struct SmartPtrCtor1<String>{
	typedef const char_t* type;
};

template<>
struct SmartPtrCtor2<String>{
	typedef const char8_t* type;
};

template<>
struct SmartPtrCtor3<String>{
	typedef const StringLiteral& type;
};

template<>
struct SmartPtrCtor1<ID>{
	typedef const char_t* type;
};

template<>
struct SmartPtrCtor2<ID>{
	typedef const StringPtr& type;
};

template<>
struct SmartPtrCtor3<ID>{
	typedef const char8_t* type;
};

template<>
struct SmartPtrCtor4<ID>{
	typedef const StringLiteral& type;
};

template<>
class SmartPtr<ID> : public Any{
public:

	SmartPtr()
		:Any(null){}

	SmartPtr(const NullPtr&)
		:Any(null){}

	SmartPtr(const char_t* v);

	SmartPtr(const StringPtr& v);
	
	SmartPtr(const char8_t* v);
	
	SmartPtr(const StringLiteral& v);

	SmartPtr(const ID& v);

public:

	/**
	* \brief T�^�ւ̃|�C���^���擾����B
	*/
	ID* get() const{ return Extract<INHERITED_ANY, ID>::extract(*this); }

	/**
	* \brief ->���Z�q
	* �X�}�[�g�|�C���^�Ƃ��ĐU�������߂ɁB
	*/
	ID* operator ->() const{ return get(); }
	
	/**
	* \brief *���Z�q
	* �X�}�[�g�|�C���^�Ƃ��ĐU�������߂ɁB
	*/
	ID& operator *() const{ return *get(); }

	operator const AnyPtr&() const{
		return *(AnyPtr*)this;
	}

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
};

}

#endif // XTAL_SMARTPTR_H_INCLUDE_GUARD
