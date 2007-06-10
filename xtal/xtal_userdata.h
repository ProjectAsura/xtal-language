
#pragma once

#include <stddef.h>

#include "xtal_utilimpl.h"

namespace xtal{

template<class T>
class UserDataImpl : public AnyImpl{
public:

	UserDataImpl(){
		if(TClass<T>::get_uncheck()){
			set_class(TClass<T>::get_uncheck());
		}
	}

	~UserDataImpl(){
		get()->~T();
	}

	T* get(){ return (T*)&buf_[0]; }

	static UserDataImpl<T>* from_this(T* p){
		return (UserDataImpl<T>*)(((char*)p) - offsetof(UserDataImpl, i_));//(((char*)&((UserDataImpl*)0)->i_) - ((char*)(UserDataImpl*)0)));
	}
	
protected:
		
	union{
		int i_;
		double d_;
		void* p_;
		char buf_[sizeof(T)];
	};
};

/**
* @brief ���[�U�[��`�^��ێ����邽�߂̃N���X
*/
template<class T>
class UserData : public Any{
public:
	
	UserData(UserDataImpl<T>* p=0)
		:Any(p){}

	template<class U>
	UserData(const UserData<U>& p)
		:Any(p){
		T* n = (U*)0; // extends test
	}

	UserData(const Null&)
		:Any(null){}
	
	/**
	* @brief ->���Z�q
	* �X�}�[�g�|�C���^�Ƃ��Ĉ������߂ɃI�[�o�[���[�h����B
	*/
	T* operator ->() const{ return get(); }
	
	/**
	* @brief *���Z�q
	* �X�}�[�g�|�C���^�Ƃ��Ĉ������߂ɃI�[�o�[���[�h����B
	*/
	T& operator *() const{ return *get(); }
	
	/**
	* @brief T�^�ւ̃|�C���^���擾����B
	*/
	T* get() const{ return impl()->get(); }

	/**
	* @brief T�^��UserData<T>�ɕϊ�����B
	*/
	static UserData<T> from_this(T* p){
		return UserData<T>(UserDataImpl<T>::from_this(p));
	}
	
	UserDataImpl<T>* impl() const{ return (UserDataImpl<T>*)Any::impl(); }
};

template<class T>
UserData<T> new_userdata(){
	UserData<T> ret(null);
	new(ret) UserDataImpl<T>();
	new(ret.impl()->get()) T();
	return ret;
}

template<class T, class A0>
UserData<T> new_userdata(const A0& a0){
	UserData<T> ret(null);
	new(ret) UserDataImpl<T>();
	new(ret.impl()->get()) T(a0);
	return ret;
}

template<class T, class A0, class A1>
UserData<T> new_userdata(const A0& a0, const A1& a1){
	UserData<T> ret(null);
	new(ret) UserDataImpl<T>();
	new(ret.impl()->get()) T(a0, a1);
	return ret;
}

template<class T, class A0, class A1, class A2>
UserData<T> new_userdata(const A0& a0, const A1& a1, const A2& a2){
	UserData<T> ret(null);
	new(ret) UserDataImpl<T>();
	new(ret.impl()->get()) T(a0, a1, a2);
	return ret;
}

template<class T, class A0, class A1, class A2, class A3>
UserData<T> new_userdata(const A0& a0, const A1& a1, const A2& a2, const A3& a3){
	UserData<T> ret(null);
	new(ret) UserDataImpl<T>();
	new(ret.impl()->get()) T(a0, a1, a2, a3);
	return ret;
}

template<class T, class A0, class A1, class A2, class A3, class A4>
UserData<T> new_userdata(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4){
	UserData<T> ret(null);
	new(ret) UserDataImpl<T>();
	new(ret.impl()->get()) T(a0, a1, a2, a3, a4);
	return ret;
}

}
