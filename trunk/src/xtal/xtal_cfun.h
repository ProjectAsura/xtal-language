/** \file src/xtal/xtal_cfun.h
* \brief src/xtal/xtal_cfun.h
*/

#ifndef XTAL_CFUN_H_INCLUDE_GUARD
#define XTAL_CFUN_H_INCLUDE_GUARD

#pragma once

namespace xtal{

class NativeMethod;	

///////////////////////////////////////////////////////

struct ReturnResult{
	static void return_result(const VMachinePtr& vm){
		vm->return_result();
	}

	template<class T>
	static void return_result(const VMachinePtr& vm, const T& ret){
		return_result2(vm, ret, TypeIntType<Convertible<T, AnyPtr>::value>());
	}

	template<class T>
	static void return_result2(const VMachinePtr& vm, const T& ret, TypeIntType<1>){
		vm->return_result(ret);
	}
		
	template<class T>
	static void return_result2(const VMachinePtr& vm, const T& ret, TypeIntType<0>){
		vm->return_result(xnew<T>(ret));
	}
};

struct ReturnValueToVMTest{
	const VMachinePtr* vm;

	ReturnValueToVMTest(const VMachinePtr& vm)
		:vm(&vm){}
};

struct ReturnVoidToVMTest{};

template<class T>
inline int operator ,(const T& val, ReturnValueToVMTest rp){
	(*rp.vm)->return_result(val);
	return 0;
}

inline int operator ,(ReturnValueToVMTest rp, ReturnVoidToVMTest){
	(*rp.vm)->return_result();
	return 0;
}

#define XTAL_RETURN_TO_VM(expr) expr, ReturnValueToVMTest(vm), ReturnVoidToVMTest()

////////////////////////////////////////////

template<class Fun>
struct cfun_holder_base{};

template<class Fun>
struct cmemfun_holder_base{};

template<class T>
struct CommonThisType{ typedef T type; };

template<class T>
struct CommonType{ typedef T type; };


/*
template<class T>
struct CommonThisType{ 
	typedef typename If<IsInherited<T, Base>::value, Base, 
		typename If<IsInherited<T, RefCountingBase>::value, RefCountingBase, T>::type
	>::type type;
};

template<class T>
struct CommonType{ typedef T type; };

template<>
struct CommonType<const AnyPtr&>{ typedef const AnyPtr& type; };

template<class T>
struct CommonType<const SmartPtr<T>&> : CommonType<const AnyPtr&>{};

template<class T>
struct CommonType<T*>{ 
	typedef typename If<IsInherited<T, Base>::value, Base*, 
		typename If<IsInherited<T, RefCountingBase>::value, RefCountingBase*, T*>::type
	>::type type;
};
*/

template<class Fun>
struct cfun_holder{};

template<class Fun>
struct cmemfun_holder{};

template<class C, class T>
struct getter_holder;

template<class C, class T>
struct setter_holder;

template<class T, 
class A0=void, class A1=void, class A2=void, class A3=void, class A4=void, 
class A5=void, class A6=void, class A7=void, class A8=void, class A9=void,
class A10=void, class A11=void, class A12=void, class A13=void, class A14=void>
struct ctor_fun{};

struct param_types_holder_n{
	void (*fun)(const VMachinePtr& vm, const void* data, UninitializedAny* args); // �֐�
	CppClassSymbolData** const * param_types; // this�ƈ����̌^��\���N���X�V���{���ւ̃|�C���^
	u8 size;
	u8 param_n; // �����̐�
	u8 extendable; // �ϒ����ǂ���
};

template<class Func>
struct fun_param_holder{
	enum{
		PARAM_N = Func::PARAM_N,
		EXTENDABLE = Func::EXTENDABLE
	};

	typedef typename Func::fun_param_holder fph;
	typedef typename Func::fun_t fun_t;
	typedef Func cfun_t;

	static const param_types_holder_n value;
};

template<class Fun>
const param_types_holder_n fun_param_holder<Fun>::value = {
	&cfun_t::call,
	fph::values,
	sizeof(fun_t),
	PARAM_N,
	EXTENDABLE,
};

//////////////////////////////////////////////////////////////

class NativeMethod : public HaveParentRefCountingBase{
public:
	enum{ TYPE = TYPE_NATIVE_METHOD };

	typedef void (*fun_t)(const VMachinePtr& vm, const void* data, UninitializedAny* args);

	NativeMethod(const param_types_holder_n& pth, const void* val = 0);
	
	~NativeMethod();

public:

	const NativeFunPtr& param(int_t i, const IDPtr& key, const AnyPtr& value);

public:

	void on_visit_members(Visitor& m);

	void on_rawcall(const VMachinePtr& vm);

protected:
	fun_t fun_;
	void* data_;

	u8 param_n_;
	u8 min_param_count_;
	u8 max_param_count_;
	u8 val_size_;
};

class NativeFun : public NativeMethod{
public:
	enum{ TYPE = TYPE_NATIVE_FUN };

	NativeFun(const param_types_holder_n& pth, const void* val, const AnyPtr& this_);

public:

	void on_visit_members(Visitor& m);

	void on_rawcall(const VMachinePtr& vm);

private:
	AnyPtr this_;
};

NativeFunPtr new_native_fun(const param_types_holder_n& pth, const void* val);
NativeFunPtr new_native_fun(const param_types_holder_n& pth, const void* val, const AnyPtr& this_);

//////////////////////////////////////////////////////////////

/*
* \brief C++�̃R���X�g���N�^��Xtal����Ăяo����I�u�W�F�N�g�ɕϊ����邽�߂̋[���֐�
*
*/
template<class T, 
class A0=void, class A1=void, class A2=void, class A3=void, class A4=void, 
class A5=void, class A6=void, class A7=void, class A8=void, class A9=void,
class A10=void, class A11=void, class A12=void, class A13=void, class A14=void>
struct ctor : public NativeFunPtr{
	typedef ctor_fun<T, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14> fun_t;
	ctor(){
		NativeFunPtr::operator =(new_native_fun(fun_param_holder<fun_t>::value, 0));
	}
};
	
/**
* @brief 2�d�f�B�X�p�b�`���\�b�h
*/
class DoubleDispatchMethod : public HaveParentBase{
public:

	DoubleDispatchMethod(const IDPtr& primary_key)
		:primary_key_(primary_key){}

	void on_rawcall(const VMachinePtr& vm){
		if(vm->ordered_arg_count()>0){
			vm->arg_this()->rawsend(vm, primary_key_, vm->arg(0)->get_class());
		}
	}

private:
	IDPtr primary_key_;
};

/**
* @brief 2�d�f�B�X�p�b�`�֐�
*/
class DoubleDispatchFun : public HaveParentBase{
public:

	DoubleDispatchFun(const ClassPtr& klass, const IDPtr& primary_key)
		:klass_(klass), primary_key_(primary_key){}

	void on_rawcall(const VMachinePtr& vm){
		klass_->member(primary_key_, vm->arg(0)->get_class())->rawcall(vm);
	}

	void on_visit_members(Visitor& m){
		HaveParentBase::on_visit_members(m);
		m & klass_;
	}

private:
	AnyPtr klass_;
	IDPtr primary_key_;
};

/// \name �l�C�e�B�u�֐���Xtal�ŌĂяo����I�u�W�F�N�g�ɕϊ����邽�߂̊֐��Q
//@{

/**
* \brief C++�̊֐���Xtal����Ăяo����I�u�W�F�N�g�ɕϊ����邽�߂̊֐�
*
*/
template<class Fun>
inline NativeFunPtr fun(const Fun& f){
	return new_native_fun(fun_param_holder<cfun_holder<Fun> >::value, &f);
}

/**
* \brief C++�̃����o�֐���Xtal����Ăяo����I�u�W�F�N�g�ɕϊ����邽�߂̊֐�
*
* ���ʂ̊֐������\�b�h�Ƃ��ĕϊ��������ꍇ�A�����������̌^�ɂ��邱�ƁB
*/
template<class Fun>
inline NativeFunPtr method(const Fun& f){
	return new_native_fun(fun_param_holder<cmemfun_holder<Fun> >::value, &f);
}

/**
* \brief �����o�ϐ��ւ̃|�C���^����Q�b�^�[�֐��𐶐�����
*
*/
template<class T, class C>
inline NativeFunPtr getter(T C::* f){
	return new_native_fun(fun_param_holder<getter_holder<C, T> >::value, &f);
}
	
/**
* \brief �����o�ϐ��ւ̃|�C���^����Z�b�^�[�֐��𐶐�����
*
*/
template<class T, class C>
inline NativeFunPtr setter(T C::* f){
	return new_native_fun(fun_param_holder<setter_holder<C, T> >::value(), &f);
}

/**
* \brief 2�d�f�B�X�p�b�`���\�b�h�I�u�W�F�N�g�𐶐�����
*
*/
DoubleDispatchMethodPtr double_dispatch_method(const IDPtr& primary_key);

/**
* \brief 2�d�f�B�X�p�b�`���\�b�h�I�u�W�F�N�g�𐶐�����
*
*/
DoubleDispatchFunPtr double_dispatch_fun(const ClassPtr& klass, const IDPtr& primary_key);

//@}

}

#endif // XTAL_CFUN_H_INCLUDE_GUARD
