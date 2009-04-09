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

	template<class Deleter>
	SmartPtr(T* p, Deleter deleter)
		:SmartPtr<Any>(p, deleter){}

	template<class U>
	SmartPtr(const SmartPtr<U>& p)
		:SmartPtr<Any>(p){

		// �p���֌W�������Ń`�F�b�N���Ă���B
		// �����ŃR���p�C���G���[�ɂȂ�ꍇ�A
		// ptr_cast�֐������g�p���Č^��ϊ�����K�v������B
		T* n = (U*)0; 
		XTAL_UNUSED_VAR(n);
	}

	SmartPtr<T>& operator =(const Null&){
		dec_ref_count();
		set_null(*this);
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

	SmartPtr(SmartPtrSelector<INHERITED_BASE>, T* p){ 
		set_p(*this, (Base*)p); 
		p->inc_ref_count();
	}

	SmartPtr(SmartPtrSelector<INHERITED_ANY>, T* p){ 
		*(Any*)this = *(Any*)p; 
		inc_ref_count();
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
	SmartPtr(SmartPtrSelector<INHERITED_OTHER>, T* p);

private:

	T* get2(SmartPtrSelector<INHERITED_BASE>) const{ 
		XTAL_ASSERT(type(*this)!=TYPE_NULL); // ���̃A�T�[�V�����Ŏ~�܂�ꍇ�Anull�|�C���^���i�[����Ă���
		return (T*)pvalue(*this); 
	}

	T* get2(SmartPtrSelector<INHERITED_RCBASE>) const{ 
		XTAL_ASSERT(type(*this)!=TYPE_NULL); // ���̃A�T�[�V�����Ŏ~�܂�ꍇ�Anull�|�C���^���i�[����Ă���
		return (T*)rcpvalue(*this); 
	}

	T* get2(SmartPtrSelector<INHERITED_ANY>) const{ 
		return (T*)this; 
	}

	T* get2(SmartPtrSelector<INHERITED_OTHER>) const{ 
		return (T*)((UserTypeHolder<T>*)pvalue(*this))->ptr; 
	}

public:

	/**
	* \brief ->���Z�q
	* �X�}�[�g�|�C���^�Ƃ��Ĉ������߂ɁB
	*/
	T* operator ->() const{ return get(); }
	
	/**
	* \brief *���Z�q
	* �X�}�[�g�|�C���^�Ƃ��Ĉ������߂ɁB
	*/
	T& operator *() const{ return *get(); }
	
	/**
	* \brief T�^�ւ̃|�C���^���擾����B
	*/
	T* get() const{ return get2(SmartPtrSelector<InheritedN<T>::value>()); }

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

	template<class A0>
	SmartPtr(SmartPtrSelector<INHERITED_BASE>, const A0& a0)
		:SmartPtr<Any>(new T(a0), cpp_class<T>(), special_ctor_t()){}

	template<class A0>
	SmartPtr(SmartPtrSelector<INHERITED_RCBASE>, const A0& a0)
		:SmartPtr<Any>(new T(a0), T::TYPE, special_ctor_t()){}

	template<class A0>
	SmartPtr(SmartPtrSelector<INHERITED_ANY>, const A0& a0)
		:SmartPtr<Any>(T(a0), special_ctor_t()){}

	template<class A0>
	SmartPtr(SmartPtrSelector<INHERITED_OTHER>, const A0& a0)
		:SmartPtr<Any>(new UserTypeHolderSub<T>(), cpp_class<T>(), special_ctor_t()){
		UserTypeHolderSub<T>* p = ((UserTypeHolderSub<T>*)pvalue(*this));
		p->ptr = (T*)p->buf;
		new(p->ptr) T(a0);
	}

/////////////////////

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

/**
* \brief T�I�u�W�F�N�g�𐶐�����
*/
template<class T>
inline SmartPtr<T> xnew(){
	return SmartPtr<T>(SmartPtrSelector<InheritedN<T>::value>());
}

/**
* \brief T�I�u�W�F�N�g�𐶐�����
*/
template<class T, class A0>
inline SmartPtr<T> xnew(const A0& a0){
	return SmartPtr<T>(SmartPtrSelector<InheritedN<T>::value>(), a0);
}

/**
* \brief T�I�u�W�F�N�g�𐶐�����
*/
template<class T, class A0, class A1>
inline SmartPtr<T> xnew(const A0& a0, const A1& a1){
	return SmartPtr<T>(SmartPtrSelector<InheritedN<T>::value>(), a0, a1);
}

/**
* \brief T�I�u�W�F�N�g�𐶐�����
*/
template<class T, class A0, class A1, class A2>
inline SmartPtr<T> xnew(const A0& a0, const A1& a1, const A2& a2){
	return SmartPtr<T>(SmartPtrSelector<InheritedN<T>::value>(), a0, a1, a2);
}

/**
* \brief T�I�u�W�F�N�g�𐶐�����
*/
template<class T, class A0, class A1, class A2, class A3>
inline SmartPtr<T> xnew(const A0& a0, const A1& a1, const A2& a2, const A3& a3){
	return SmartPtr<T>(SmartPtrSelector<InheritedN<T>::value>(), a0, a1, a2, a3);
}

/**
* \brief T�I�u�W�F�N�g�𐶐�����
*/
template<class T, class A0, class A1, class A2, class A3, class A4>
inline SmartPtr<T> xnew(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4){
	return SmartPtr<T>(SmartPtrSelector<InheritedN<T>::value>(), a0, a1, a2, a3, a4);
}

//@}

//////////////////////////////////////////////////////////////

template<class T>
inline const SmartPtr<T>& to_smartptr(SmartPtrSelector<INHERITED_BASE>, const T* p){
	return *static_cast<SmartPtr<T>*>(static_cast<Any*>(const_cast<T*>(p)));
}

template<class T>
inline const SmartPtr<T>& to_smartptr(SmartPtrSelector<INHERITED_RCBASE>, const T* p){
	return *static_cast<SmartPtr<T>*>(static_cast<Any*>(const_cast<T*>(p)));
}

template<class T>
inline const SmartPtr<T>& to_smartptr(SmartPtrSelector<INHERITED_ANY>, const T* p){
	return *static_cast<SmartPtr<T>*>(static_cast<Any*>(const_cast<T*>(p)));
}

/**
* \brief T*��SmartPtr<T>�ɕϊ�����֐�
*/
template<class T>
inline const SmartPtr<T>& to_smartptr(const T* p){
	return to_smartptr(SmartPtrSelector<InheritedN<T>::value>(), p);
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
