/** \file src/xtal/xtal_smartptr.h
* \brief src/xtal/xtal_smartptr.h
*/

#ifndef XTAL_SMARTPTR_H_INCLUDE_GUARD
#define XTAL_SMARTPTR_H_INCLUDE_GUARD

#pragma once

namespace xtal{

template<int N, class T>
struct ExtractSmartPtr{};

template<class T>
struct ExtractSmartPtr<INHERITED_BASE, T>{
	static T* extract(const Any& a){
		XTAL_ASSERT(type(a)!=TYPE_NULL); // ���̃A�T�[�V�����Ŏ~�܂�ꍇ�Anull�|�C���^���i�[����Ă���
		XTAL_ASSERT(type(a)!=TYPE_UNDEFINED); // ���̃A�T�[�V�����Ŏ~�܂�ꍇ�Aundefined���i�[����Ă���
		return (T*)pvalue(a);
	}
};

template<class T>
struct ExtractSmartPtr<INHERITED_RCBASE, T>{
	static T* extract(const Any& a){
		XTAL_ASSERT(type(a)!=TYPE_NULL); // ���̃A�T�[�V�����Ŏ~�܂�ꍇ�Anull�|�C���^���i�[����Ă���
		XTAL_ASSERT(type(a)!=TYPE_UNDEFINED); // ���̃A�T�[�V�����Ŏ~�܂�ꍇ�Aundefined���i�[����Ă���
		return (T*)rcpvalue(a);
	}
};

template<class T>
struct ExtractSmartPtr<INHERITED_ANY, T>{
	static T* extract(const Any& a){
		return (T*)&a;
	}
};

template<class T>
struct ExtractSmartPtr<INHERITED_OTHER, T>{
	static T* extract(const Any& a){
		return (T*)((UserTypeHolder<T>*)pvalue(a))->ptr; 
	}
};

/**
* \brief T�^�ւ̃|�C���^��ێ����邽�߂̃X�}�[�g�|�C���^
*/
template<class T>
class SmartPtr : public SmartPtr<Any>{
public:
	
	SmartPtr(){}

	template<class Deleter>
	SmartPtr(const T* p, const Deleter& deleter)
		:SmartPtr<Any>((T*)p, deleter){}

	template<class U>
	SmartPtr(const SmartPtr<U>& p)
		:SmartPtr<Any>(p){

		// �p���֌W�������Ń`�F�b�N���Ă���B
		// �����ŃR���p�C���G���[�ɂȂ�ꍇ�A
		// ptr_cast�֐������g�p���Č^��ϊ�����K�v������B
		T* n = (U*)0; 
		XTAL_UNUSED_VAR(n);
	}
	
	template<class U>
	SmartPtr<T>& operator =(const SmartPtr<U>& p){
		// �p���֌W�������Ń`�F�b�N���Ă���B
		// �����ŃR���p�C���G���[�ɂȂ�ꍇ�A
		// ptr_cast�֐������g�p���Č^��ϊ�����K�v������B
		T* n = (U*)0; 
		XTAL_UNUSED_VAR(n);
		
		SmartPtr<Any>::operator =(p);
		return *this;
	}
	
	SmartPtr<T>& operator =(const NullPtr& null){
		SmartPtr<Any>::operator =(null);
		return *this;
	}

	/// null���󂯎��R���X�g���N�^
	SmartPtr(const NullPtr&){}

	/// ���ʂȃR���X�g���N�^1
	SmartPtr(typename SmartPtrCtor1<T>::type v);

	/// ���ʂȃR���X�g���N�^2
	SmartPtr(typename SmartPtrCtor2<T>::type v);

	/// ���ʂȃR���X�g���N�^3
	SmartPtr(typename SmartPtrCtor3<T>::type v);

	/// ���ʂȃR���X�g���N�^4
	SmartPtr(typename SmartPtrCtor4<T>::type v);

public:

	template<class U>
	void assign_direct(const SmartPtr<U>& a){
		AnyPtr::assign_direct(a);

		// �p���֌W�������Ń`�F�b�N���Ă���B
		// �����ŃR���p�C���G���[�ɂȂ�ꍇ�A
		// ptr_cast�֐������g�p���Č^��ϊ�����K�v������B
		T* n = (U*)0; 
		XTAL_UNUSED_VAR(n);
	}

private:

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
	T* get() const{ return ExtractSmartPtr<InheritedN<T>::value, T>::extract(*this); }

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
	
public:

	SmartPtr(SmartPtrSelector<INHERITED_BASE>)
		:SmartPtr<Any>(new T(), cpp_class<T>(), special_ctor_t()){}

	SmartPtr(SmartPtrSelector<INHERITED_RCBASE>)
		:SmartPtr<Any>(new T(), T::TYPE, special_ctor_t()){}

	SmartPtr(SmartPtrSelector<INHERITED_ANY>)
		:SmartPtr<Any>(T(), special_ctor_t()){}

	SmartPtr(SmartPtrSelector<INHERITED_OTHER>)
		:SmartPtr<Any>(new UserTypeHolderSub<T>(), cpp_class<T>(), special_ctor_t()){
		UserTypeHolderSub<T>* p = ((UserTypeHolderSub<T>*)pvalue(*this));
		p->ptr = (T*)p->buf;
		new(p->ptr) T;
	}

/////////////////////

//{REPEAT{{
/*
	template<class A0 #COMMA_REPEAT#class A`i+1`#>
	SmartPtr(SmartPtrSelector<INHERITED_BASE>, const A0& a0 #COMMA_REPEAT#const A`i+1`& a`i+1`#)
		:SmartPtr<Any>(new T(a0 #COMMA_REPEAT#a`i+1`#), cpp_class<T>(), special_ctor_t()){}

	template<class A0 #COMMA_REPEAT#class A`i+1`#>
	SmartPtr(SmartPtrSelector<INHERITED_RCBASE>, const A0& a0 #COMMA_REPEAT#const A`i+1`& a`i+1`#)
		:SmartPtr<Any>(new T(a0 #COMMA_REPEAT#a`i+1`#), T::TYPE, special_ctor_t()){}

	template<class A0 #COMMA_REPEAT#class A`i+1`#>
	SmartPtr(SmartPtrSelector<INHERITED_ANY>, const A0& a0 #COMMA_REPEAT#const A`i+1`& a`i+1`#)
		:SmartPtr<Any>(T(a0 #COMMA_REPEAT#a`i+1`#), special_ctor_t()){}

	template<class A0 #COMMA_REPEAT#class A`i+1`#>
	SmartPtr(SmartPtrSelector<INHERITED_OTHER>, const A0& a0 #COMMA_REPEAT#const A`i+1`& a`i+1`#)
		:SmartPtr<Any>(new UserTypeHolderSub<T>(), cpp_class<T>(), special_ctor_t()){
		UserTypeHolderSub<T>* p = ((UserTypeHolderSub<T>*)pvalue(*this));
		p->ptr = (T*)p->buf;
		new(p->ptr) T(a0 #COMMA_REPEAT#a`i+1`#);
	}
*/

	template<class A0 >
	SmartPtr(SmartPtrSelector<INHERITED_BASE>, const A0& a0 )
		:SmartPtr<Any>(new T(a0 ), cpp_class<T>(), special_ctor_t()){}

	template<class A0 >
	SmartPtr(SmartPtrSelector<INHERITED_RCBASE>, const A0& a0 )
		:SmartPtr<Any>(new T(a0 ), T::TYPE, special_ctor_t()){}

	template<class A0 >
	SmartPtr(SmartPtrSelector<INHERITED_ANY>, const A0& a0 )
		:SmartPtr<Any>(T(a0 ), special_ctor_t()){}

	template<class A0 >
	SmartPtr(SmartPtrSelector<INHERITED_OTHER>, const A0& a0 )
		:SmartPtr<Any>(new UserTypeHolderSub<T>(), cpp_class<T>(), special_ctor_t()){
		UserTypeHolderSub<T>* p = ((UserTypeHolderSub<T>*)pvalue(*this));
		p->ptr = (T*)p->buf;
		new(p->ptr) T(a0 );
	}

	template<class A0 , class A1>
	SmartPtr(SmartPtrSelector<INHERITED_BASE>, const A0& a0 , const A1& a1)
		:SmartPtr<Any>(new T(a0 , a1), cpp_class<T>(), special_ctor_t()){}

	template<class A0 , class A1>
	SmartPtr(SmartPtrSelector<INHERITED_RCBASE>, const A0& a0 , const A1& a1)
		:SmartPtr<Any>(new T(a0 , a1), T::TYPE, special_ctor_t()){}

	template<class A0 , class A1>
	SmartPtr(SmartPtrSelector<INHERITED_ANY>, const A0& a0 , const A1& a1)
		:SmartPtr<Any>(T(a0 , a1), special_ctor_t()){}

	template<class A0 , class A1>
	SmartPtr(SmartPtrSelector<INHERITED_OTHER>, const A0& a0 , const A1& a1)
		:SmartPtr<Any>(new UserTypeHolderSub<T>(), cpp_class<T>(), special_ctor_t()){
		UserTypeHolderSub<T>* p = ((UserTypeHolderSub<T>*)pvalue(*this));
		p->ptr = (T*)p->buf;
		new(p->ptr) T(a0 , a1);
	}

	template<class A0 , class A1, class A2>
	SmartPtr(SmartPtrSelector<INHERITED_BASE>, const A0& a0 , const A1& a1, const A2& a2)
		:SmartPtr<Any>(new T(a0 , a1, a2), cpp_class<T>(), special_ctor_t()){}

	template<class A0 , class A1, class A2>
	SmartPtr(SmartPtrSelector<INHERITED_RCBASE>, const A0& a0 , const A1& a1, const A2& a2)
		:SmartPtr<Any>(new T(a0 , a1, a2), T::TYPE, special_ctor_t()){}

	template<class A0 , class A1, class A2>
	SmartPtr(SmartPtrSelector<INHERITED_ANY>, const A0& a0 , const A1& a1, const A2& a2)
		:SmartPtr<Any>(T(a0 , a1, a2), special_ctor_t()){}

	template<class A0 , class A1, class A2>
	SmartPtr(SmartPtrSelector<INHERITED_OTHER>, const A0& a0 , const A1& a1, const A2& a2)
		:SmartPtr<Any>(new UserTypeHolderSub<T>(), cpp_class<T>(), special_ctor_t()){
		UserTypeHolderSub<T>* p = ((UserTypeHolderSub<T>*)pvalue(*this));
		p->ptr = (T*)p->buf;
		new(p->ptr) T(a0 , a1, a2);
	}

	template<class A0 , class A1, class A2, class A3>
	SmartPtr(SmartPtrSelector<INHERITED_BASE>, const A0& a0 , const A1& a1, const A2& a2, const A3& a3)
		:SmartPtr<Any>(new T(a0 , a1, a2, a3), cpp_class<T>(), special_ctor_t()){}

	template<class A0 , class A1, class A2, class A3>
	SmartPtr(SmartPtrSelector<INHERITED_RCBASE>, const A0& a0 , const A1& a1, const A2& a2, const A3& a3)
		:SmartPtr<Any>(new T(a0 , a1, a2, a3), T::TYPE, special_ctor_t()){}

	template<class A0 , class A1, class A2, class A3>
	SmartPtr(SmartPtrSelector<INHERITED_ANY>, const A0& a0 , const A1& a1, const A2& a2, const A3& a3)
		:SmartPtr<Any>(T(a0 , a1, a2, a3), special_ctor_t()){}

	template<class A0 , class A1, class A2, class A3>
	SmartPtr(SmartPtrSelector<INHERITED_OTHER>, const A0& a0 , const A1& a1, const A2& a2, const A3& a3)
		:SmartPtr<Any>(new UserTypeHolderSub<T>(), cpp_class<T>(), special_ctor_t()){
		UserTypeHolderSub<T>* p = ((UserTypeHolderSub<T>*)pvalue(*this));
		p->ptr = (T*)p->buf;
		new(p->ptr) T(a0 , a1, a2, a3);
	}

	template<class A0 , class A1, class A2, class A3, class A4>
	SmartPtr(SmartPtrSelector<INHERITED_BASE>, const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4)
		:SmartPtr<Any>(new T(a0 , a1, a2, a3, a4), cpp_class<T>(), special_ctor_t()){}

	template<class A0 , class A1, class A2, class A3, class A4>
	SmartPtr(SmartPtrSelector<INHERITED_RCBASE>, const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4)
		:SmartPtr<Any>(new T(a0 , a1, a2, a3, a4), T::TYPE, special_ctor_t()){}

	template<class A0 , class A1, class A2, class A3, class A4>
	SmartPtr(SmartPtrSelector<INHERITED_ANY>, const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4)
		:SmartPtr<Any>(T(a0 , a1, a2, a3, a4), special_ctor_t()){}

	template<class A0 , class A1, class A2, class A3, class A4>
	SmartPtr(SmartPtrSelector<INHERITED_OTHER>, const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4)
		:SmartPtr<Any>(new UserTypeHolderSub<T>(), cpp_class<T>(), special_ctor_t()){
		UserTypeHolderSub<T>* p = ((UserTypeHolderSub<T>*)pvalue(*this));
		p->ptr = (T*)p->buf;
		new(p->ptr) T(a0 , a1, a2, a3, a4);
	}

	template<class A0 , class A1, class A2, class A3, class A4, class A5>
	SmartPtr(SmartPtrSelector<INHERITED_BASE>, const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5)
		:SmartPtr<Any>(new T(a0 , a1, a2, a3, a4, a5), cpp_class<T>(), special_ctor_t()){}

	template<class A0 , class A1, class A2, class A3, class A4, class A5>
	SmartPtr(SmartPtrSelector<INHERITED_RCBASE>, const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5)
		:SmartPtr<Any>(new T(a0 , a1, a2, a3, a4, a5), T::TYPE, special_ctor_t()){}

	template<class A0 , class A1, class A2, class A3, class A4, class A5>
	SmartPtr(SmartPtrSelector<INHERITED_ANY>, const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5)
		:SmartPtr<Any>(T(a0 , a1, a2, a3, a4, a5), special_ctor_t()){}

	template<class A0 , class A1, class A2, class A3, class A4, class A5>
	SmartPtr(SmartPtrSelector<INHERITED_OTHER>, const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5)
		:SmartPtr<Any>(new UserTypeHolderSub<T>(), cpp_class<T>(), special_ctor_t()){
		UserTypeHolderSub<T>* p = ((UserTypeHolderSub<T>*)pvalue(*this));
		p->ptr = (T*)p->buf;
		new(p->ptr) T(a0 , a1, a2, a3, a4, a5);
	}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6>
	SmartPtr(SmartPtrSelector<INHERITED_BASE>, const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6)
		:SmartPtr<Any>(new T(a0 , a1, a2, a3, a4, a5, a6), cpp_class<T>(), special_ctor_t()){}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6>
	SmartPtr(SmartPtrSelector<INHERITED_RCBASE>, const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6)
		:SmartPtr<Any>(new T(a0 , a1, a2, a3, a4, a5, a6), T::TYPE, special_ctor_t()){}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6>
	SmartPtr(SmartPtrSelector<INHERITED_ANY>, const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6)
		:SmartPtr<Any>(T(a0 , a1, a2, a3, a4, a5, a6), special_ctor_t()){}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6>
	SmartPtr(SmartPtrSelector<INHERITED_OTHER>, const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6)
		:SmartPtr<Any>(new UserTypeHolderSub<T>(), cpp_class<T>(), special_ctor_t()){
		UserTypeHolderSub<T>* p = ((UserTypeHolderSub<T>*)pvalue(*this));
		p->ptr = (T*)p->buf;
		new(p->ptr) T(a0 , a1, a2, a3, a4, a5, a6);
	}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7>
	SmartPtr(SmartPtrSelector<INHERITED_BASE>, const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7)
		:SmartPtr<Any>(new T(a0 , a1, a2, a3, a4, a5, a6, a7), cpp_class<T>(), special_ctor_t()){}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7>
	SmartPtr(SmartPtrSelector<INHERITED_RCBASE>, const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7)
		:SmartPtr<Any>(new T(a0 , a1, a2, a3, a4, a5, a6, a7), T::TYPE, special_ctor_t()){}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7>
	SmartPtr(SmartPtrSelector<INHERITED_ANY>, const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7)
		:SmartPtr<Any>(T(a0 , a1, a2, a3, a4, a5, a6, a7), special_ctor_t()){}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7>
	SmartPtr(SmartPtrSelector<INHERITED_OTHER>, const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7)
		:SmartPtr<Any>(new UserTypeHolderSub<T>(), cpp_class<T>(), special_ctor_t()){
		UserTypeHolderSub<T>* p = ((UserTypeHolderSub<T>*)pvalue(*this));
		p->ptr = (T*)p->buf;
		new(p->ptr) T(a0 , a1, a2, a3, a4, a5, a6, a7);
	}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
	SmartPtr(SmartPtrSelector<INHERITED_BASE>, const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8)
		:SmartPtr<Any>(new T(a0 , a1, a2, a3, a4, a5, a6, a7, a8), cpp_class<T>(), special_ctor_t()){}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
	SmartPtr(SmartPtrSelector<INHERITED_RCBASE>, const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8)
		:SmartPtr<Any>(new T(a0 , a1, a2, a3, a4, a5, a6, a7, a8), T::TYPE, special_ctor_t()){}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
	SmartPtr(SmartPtrSelector<INHERITED_ANY>, const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8)
		:SmartPtr<Any>(T(a0 , a1, a2, a3, a4, a5, a6, a7, a8), special_ctor_t()){}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
	SmartPtr(SmartPtrSelector<INHERITED_OTHER>, const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8)
		:SmartPtr<Any>(new UserTypeHolderSub<T>(), cpp_class<T>(), special_ctor_t()){
		UserTypeHolderSub<T>* p = ((UserTypeHolderSub<T>*)pvalue(*this));
		p->ptr = (T*)p->buf;
		new(p->ptr) T(a0 , a1, a2, a3, a4, a5, a6, a7, a8);
	}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
	SmartPtr(SmartPtrSelector<INHERITED_BASE>, const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9)
		:SmartPtr<Any>(new T(a0 , a1, a2, a3, a4, a5, a6, a7, a8, a9), cpp_class<T>(), special_ctor_t()){}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
	SmartPtr(SmartPtrSelector<INHERITED_RCBASE>, const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9)
		:SmartPtr<Any>(new T(a0 , a1, a2, a3, a4, a5, a6, a7, a8, a9), T::TYPE, special_ctor_t()){}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
	SmartPtr(SmartPtrSelector<INHERITED_ANY>, const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9)
		:SmartPtr<Any>(T(a0 , a1, a2, a3, a4, a5, a6, a7, a8, a9), special_ctor_t()){}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
	SmartPtr(SmartPtrSelector<INHERITED_OTHER>, const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9)
		:SmartPtr<Any>(new UserTypeHolderSub<T>(), cpp_class<T>(), special_ctor_t()){
		UserTypeHolderSub<T>* p = ((UserTypeHolderSub<T>*)pvalue(*this));
		p->ptr = (T*)p->buf;
		new(p->ptr) T(a0 , a1, a2, a3, a4, a5, a6, a7, a8, a9);
	}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
	SmartPtr(SmartPtrSelector<INHERITED_BASE>, const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10)
		:SmartPtr<Any>(new T(a0 , a1, a2, a3, a4, a5, a6, a7, a8, a9, a10), cpp_class<T>(), special_ctor_t()){}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
	SmartPtr(SmartPtrSelector<INHERITED_RCBASE>, const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10)
		:SmartPtr<Any>(new T(a0 , a1, a2, a3, a4, a5, a6, a7, a8, a9, a10), T::TYPE, special_ctor_t()){}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
	SmartPtr(SmartPtrSelector<INHERITED_ANY>, const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10)
		:SmartPtr<Any>(T(a0 , a1, a2, a3, a4, a5, a6, a7, a8, a9, a10), special_ctor_t()){}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
	SmartPtr(SmartPtrSelector<INHERITED_OTHER>, const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10)
		:SmartPtr<Any>(new UserTypeHolderSub<T>(), cpp_class<T>(), special_ctor_t()){
		UserTypeHolderSub<T>* p = ((UserTypeHolderSub<T>*)pvalue(*this));
		p->ptr = (T*)p->buf;
		new(p->ptr) T(a0 , a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
	}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11>
	SmartPtr(SmartPtrSelector<INHERITED_BASE>, const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11)
		:SmartPtr<Any>(new T(a0 , a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11), cpp_class<T>(), special_ctor_t()){}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11>
	SmartPtr(SmartPtrSelector<INHERITED_RCBASE>, const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11)
		:SmartPtr<Any>(new T(a0 , a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11), T::TYPE, special_ctor_t()){}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11>
	SmartPtr(SmartPtrSelector<INHERITED_ANY>, const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11)
		:SmartPtr<Any>(T(a0 , a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11), special_ctor_t()){}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11>
	SmartPtr(SmartPtrSelector<INHERITED_OTHER>, const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11)
		:SmartPtr<Any>(new UserTypeHolderSub<T>(), cpp_class<T>(), special_ctor_t()){
		UserTypeHolderSub<T>* p = ((UserTypeHolderSub<T>*)pvalue(*this));
		p->ptr = (T*)p->buf;
		new(p->ptr) T(a0 , a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11);
	}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12>
	SmartPtr(SmartPtrSelector<INHERITED_BASE>, const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11, const A12& a12)
		:SmartPtr<Any>(new T(a0 , a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12), cpp_class<T>(), special_ctor_t()){}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12>
	SmartPtr(SmartPtrSelector<INHERITED_RCBASE>, const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11, const A12& a12)
		:SmartPtr<Any>(new T(a0 , a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12), T::TYPE, special_ctor_t()){}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12>
	SmartPtr(SmartPtrSelector<INHERITED_ANY>, const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11, const A12& a12)
		:SmartPtr<Any>(T(a0 , a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12), special_ctor_t()){}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12>
	SmartPtr(SmartPtrSelector<INHERITED_OTHER>, const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11, const A12& a12)
		:SmartPtr<Any>(new UserTypeHolderSub<T>(), cpp_class<T>(), special_ctor_t()){
		UserTypeHolderSub<T>* p = ((UserTypeHolderSub<T>*)pvalue(*this));
		p->ptr = (T*)p->buf;
		new(p->ptr) T(a0 , a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12);
	}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13>
	SmartPtr(SmartPtrSelector<INHERITED_BASE>, const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11, const A12& a12, const A13& a13)
		:SmartPtr<Any>(new T(a0 , a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13), cpp_class<T>(), special_ctor_t()){}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13>
	SmartPtr(SmartPtrSelector<INHERITED_RCBASE>, const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11, const A12& a12, const A13& a13)
		:SmartPtr<Any>(new T(a0 , a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13), T::TYPE, special_ctor_t()){}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13>
	SmartPtr(SmartPtrSelector<INHERITED_ANY>, const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11, const A12& a12, const A13& a13)
		:SmartPtr<Any>(T(a0 , a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13), special_ctor_t()){}

	template<class A0 , class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13>
	SmartPtr(SmartPtrSelector<INHERITED_OTHER>, const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11, const A12& a12, const A13& a13)
		:SmartPtr<Any>(new UserTypeHolderSub<T>(), cpp_class<T>(), special_ctor_t()){
		UserTypeHolderSub<T>* p = ((UserTypeHolderSub<T>*)pvalue(*this));
		p->ptr = (T*)p->buf;
		new(p->ptr) T(a0 , a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13);
	}

//}}REPEAT}

	/*
	template<class A0, class A1>
	SmartPtr(SmartPtrSelector<INHERITED_BASE>, const A0& a0, const A1& a1)
		:SmartPtr<Any>(new T(a0, a1), cpp_class<T>(), special_ctor_t()){}

	template<class A0, class A1>
	SmartPtr(SmartPtrSelector<INHERITED_RCBASE>, const A0& a0, const A1& a1)
		:SmartPtr<Any>(new T(a0, a1), T::TYPE, special_ctor_t()){}

	template<class A0, class A1>
	SmartPtr(SmartPtrSelector<INHERITED_ANY>, const A0& a0, const A1& a1)
		:SmartPtr<Any>(T(a0, a1), special_ctor_t()){}

	template<class A0, class A1>
	SmartPtr(SmartPtrSelector<INHERITED_OTHER>, const A0& a0, const A1& a1)
		:SmartPtr<Any>(new UserTypeHolderSub<T>(), cpp_class<T>(), special_ctor_t()){
		UserTypeHolderSub<T>* p = ((UserTypeHolderSub<T>*)pvalue(*this));
		p->ptr = (T*)p->buf;
		new(p->ptr) T(a0, a1);
	}

/////////////////////

	template<class A0, class A1, class A2>
	SmartPtr(SmartPtrSelector<INHERITED_BASE>, const A0& a0, const A1& a1, const A2& a2)
		:SmartPtr<Any>(new T(a0, a1, a2), cpp_class<T>(), special_ctor_t()){}

	template<class A0, class A1, class A2>
	SmartPtr(SmartPtrSelector<INHERITED_RCBASE>, const A0& a0, const A1& a1, const A2& a2)
		:SmartPtr<Any>(new T(a0, a1, a2), T::TYPE, special_ctor_t()){}

	template<class A0, class A1, class A2>
	SmartPtr(SmartPtrSelector<INHERITED_ANY>, const A0& a0, const A1& a1, const A2& a2)
		:SmartPtr<Any>(T(a0, a1, a2), special_ctor_t()){}

	template<class A0, class A1, class A2>
	SmartPtr(SmartPtrSelector<INHERITED_OTHER>, const A0& a0, const A1& a1, const A2& a2)
		:SmartPtr<Any>(new UserTypeHolderSub<T>(), cpp_class<T>(), special_ctor_t()){
		UserTypeHolderSub<T>* p = ((UserTypeHolderSub<T>*)pvalue(*this));
		p->ptr = (T*)p->buf;
		new(p->ptr) T(a0, a1, a2);
	}

/////////////////////

	template<class A0, class A1, class A2, class A3>
	SmartPtr(SmartPtrSelector<INHERITED_BASE>, const A0& a0, const A1& a1, const A2& a2, const A3& a3)
		:SmartPtr<Any>(new T(a0, a1, a2, a3), cpp_class<T>(), special_ctor_t()){}

	template<class A0, class A1, class A2, class A3>
	SmartPtr(SmartPtrSelector<INHERITED_RCBASE>, const A0& a0, const A1& a1, const A2& a2, const A3& a3)
		:SmartPtr<Any>(new T(a0, a1, a2, a3), T::TYPE, special_ctor_t()){}

	template<class A0, class A1, class A2, class A3>
	SmartPtr(SmartPtrSelector<INHERITED_ANY>, const A0& a0, const A1& a1, const A2& a2, const A3& a3)
		:SmartPtr<Any>(T(a0, a1, a2, a3), special_ctor_t()){}

	template<class A0, class A1, class A2, class A3>
	SmartPtr(SmartPtrSelector<INHERITED_OTHER>, const A0& a0, const A1& a1, const A2& a2, const A3& a3)
		:SmartPtr<Any>(new UserTypeHolderSub<T>(), cpp_class<T>(), special_ctor_t()){
		UserTypeHolderSub<T>* p = ((UserTypeHolderSub<T>*)pvalue(*this));
		p->ptr = (T*)p->buf;
		new(p->ptr) T(a0, a1, a2, a3);
	}

/////////////////////

	template<class A0, class A1, class A2, class A3, class A4>
	SmartPtr(SmartPtrSelector<INHERITED_BASE>, const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4)
		:SmartPtr<Any>(new T(a0, a1, a2, a3, a4), cpp_class<T>(), special_ctor_t()){}

	template<class A0, class A1, class A2, class A3, class A4>
	SmartPtr(SmartPtrSelector<INHERITED_RCBASE>, const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4)
		:SmartPtr<Any>(new T(a0, a1, a2, a3, a4), T::TYPE, special_ctor_t()){}

	template<class A0, class A1, class A2, class A3, class A4>
	SmartPtr(SmartPtrSelector<INHERITED_ANY>, const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4)
		:SmartPtr<Any>(T(a0, a1, a2, a3, a4), special_ctor_t()){}

	template<class A0, class A1, class A2, class A3, class A4>
	SmartPtr(SmartPtrSelector<INHERITED_OTHER>, const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4)
		:SmartPtr<Any>(new UserTypeHolderSub<T>(), cpp_class<T>(), special_ctor_t()){
		UserTypeHolderSub<T>* p = ((UserTypeHolderSub<T>*)pvalue(*this));
		p->ptr = (T*)p->buf;
		new(p->ptr) T(a0, a1, a2, a3, a4);
	}
*/
};

template<class T>
SmartPtr<T>::SmartPtr(typename SmartPtrCtor1<T>::type v)
	:SmartPtr<Any>(SmartPtrCtor1<T>::call(v)){}

template<class T>
SmartPtr<T>::SmartPtr(typename SmartPtrCtor2<T>::type v)
	:SmartPtr<Any>(SmartPtrCtor2<T>::call(v)){}

template<class T>
SmartPtr<T>::SmartPtr(typename SmartPtrCtor3<T>::type v)
	:SmartPtr<Any>(SmartPtrCtor3<T>::call(v)){}

template<class T>
SmartPtr<T>::SmartPtr(typename SmartPtrCtor4<T>::type v)
	:SmartPtr<Any>(SmartPtrCtor4<T>::call(v)){}


/// \name �I�u�W�F�N�g����
//@{

//{REPEAT{{
/*
template<class T #COMMA_REPEAT#class A`i`#>
inline SmartPtr<T> xnew(#REPEAT_COMMA#const A`i`& a`i`#){
	return SmartPtr<T>(SmartPtrSelector<InheritedN<T>::value>() #COMMA_REPEAT#a`i`#);
}
*/

template<class T >
inline SmartPtr<T> xnew(){
	return SmartPtr<T>(SmartPtrSelector<InheritedN<T>::value>() );
}

template<class T , class A0>
inline SmartPtr<T> xnew(const A0& a0){
	return SmartPtr<T>(SmartPtrSelector<InheritedN<T>::value>() , a0);
}

template<class T , class A0, class A1>
inline SmartPtr<T> xnew(const A0& a0, const A1& a1){
	return SmartPtr<T>(SmartPtrSelector<InheritedN<T>::value>() , a0, a1);
}

template<class T , class A0, class A1, class A2>
inline SmartPtr<T> xnew(const A0& a0, const A1& a1, const A2& a2){
	return SmartPtr<T>(SmartPtrSelector<InheritedN<T>::value>() , a0, a1, a2);
}

template<class T , class A0, class A1, class A2, class A3>
inline SmartPtr<T> xnew(const A0& a0, const A1& a1, const A2& a2, const A3& a3){
	return SmartPtr<T>(SmartPtrSelector<InheritedN<T>::value>() , a0, a1, a2, a3);
}

template<class T , class A0, class A1, class A2, class A3, class A4>
inline SmartPtr<T> xnew(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4){
	return SmartPtr<T>(SmartPtrSelector<InheritedN<T>::value>() , a0, a1, a2, a3, a4);
}

template<class T , class A0, class A1, class A2, class A3, class A4, class A5>
inline SmartPtr<T> xnew(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5){
	return SmartPtr<T>(SmartPtrSelector<InheritedN<T>::value>() , a0, a1, a2, a3, a4, a5);
}

template<class T , class A0, class A1, class A2, class A3, class A4, class A5, class A6>
inline SmartPtr<T> xnew(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6){
	return SmartPtr<T>(SmartPtrSelector<InheritedN<T>::value>() , a0, a1, a2, a3, a4, a5, a6);
}

template<class T , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
inline SmartPtr<T> xnew(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7){
	return SmartPtr<T>(SmartPtrSelector<InheritedN<T>::value>() , a0, a1, a2, a3, a4, a5, a6, a7);
}

template<class T , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
inline SmartPtr<T> xnew(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8){
	return SmartPtr<T>(SmartPtrSelector<InheritedN<T>::value>() , a0, a1, a2, a3, a4, a5, a6, a7, a8);
}

template<class T , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
inline SmartPtr<T> xnew(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9){
	return SmartPtr<T>(SmartPtrSelector<InheritedN<T>::value>() , a0, a1, a2, a3, a4, a5, a6, a7, a8, a9);
}

template<class T , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
inline SmartPtr<T> xnew(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10){
	return SmartPtr<T>(SmartPtrSelector<InheritedN<T>::value>() , a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
}

template<class T , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11>
inline SmartPtr<T> xnew(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11){
	return SmartPtr<T>(SmartPtrSelector<InheritedN<T>::value>() , a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11);
}

template<class T , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12>
inline SmartPtr<T> xnew(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11, const A12& a12){
	return SmartPtr<T>(SmartPtrSelector<InheritedN<T>::value>() , a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12);
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
* \brief T*��SmartPtr<T>�ɕϊ�����֐�
*/
template<class T>
inline const SmartPtr<T>& to_smartptr(const T* p){
	return ToSmartPtr<InheritedN<T>::value, T>::to(p);
}

//////////////////////////////////////////////////////////////

// SmartPtr�̏d�˒����R���p�C���G���[�Ƃ��邽�߂̒�`
template<class T>
class SmartPtr< SmartPtr<T> >;

///////////////////////////////////////////////////////////////

template<>
struct SmartPtrCtor1<String>{
	typedef const char_t* type;
	static AnyPtr call(type v);
};

template<>
struct SmartPtrCtor2<String>{
	typedef const char8_t* type;
	static AnyPtr call(type v);
};

template<>
struct SmartPtrCtor3<String>{
	typedef const StringLiteral& type;
	static AnyPtr call(type v);
};

template<>
struct SmartPtrCtor1<ID>{
	typedef const char_t* type;
	static AnyPtr call(type v);
};

template<>
struct SmartPtrCtor2<ID>{
	typedef const StringPtr& type;
	static AnyPtr call(type v);
};

template<>
struct SmartPtrCtor3<ID>{
	typedef const char8_t* type;
	static AnyPtr call(type v);
};

template<>
struct SmartPtrCtor4<ID>{
	typedef const StringLiteral& type;
	static AnyPtr call(type v);
};

}

#endif // XTAL_SMARTPTR_H_INCLUDE_GUARD
