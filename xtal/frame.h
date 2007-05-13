
#pragma once

#include "any.h"
#include "code.h"
#include "vmachine.h"
#include "cfun.h"
#include "utilimpl.h"

namespace xtal{

void InitClass();

// fwd decl
class ModuleImpl;
class ClassImpl;
class InstanceImpl;

/**
* @brief�u���b�N��\���N���X
*
*/
class Frame : public Any{
public:
		
	Frame();
	
	Frame(const Frame& outer, const Code& code, FrameCore* core);
	
	Frame(FrameImpl* p)
		:Any((AnyImpl*)p){}
	
	Frame(const Null&)
		:Any(null){}
	
public:
	
	/**
	* @brief �O���̃X�R�[�v��\��Frame�I�u�W�F�N�g��Ԃ��B
	*
	*/
	const Frame& outer() const;

	/**
	* @brief ���e�������ɒ�`���ꂽ�v�f�̐���Ԃ��B
	*
	*/
	int_t block_size() const;

	/**
	* @brief i�Ԗڂ̃����o�[���_�C���N�g�Ɏ擾�B
	*
	*/
	const Any& member_direct(int_t i) const;

	/**
	* @brief i�Ԗڂ̃����o�[���_�C���N�g�ɐݒ�B
	*
	*/
	void set_member_direct(int_t i, const Any& value) const;

	/**
	* @brief �����o���������o��Iterator��Ԃ�
	*
	* @code
	* Xfor2(key, value, frame.members()){
	*   puts(Xf("%s %s")(key, value).to_s().c_str());
	* }
	* @endcode
	*/
	Any members() const;

	/**
	* @brief Xtal�Œ�`����Ă���Ȃ�true��Ԃ��B
	*
	*/
	bool is_defined_by_xtal() const;
	
	FrameImpl* impl() const{ return (FrameImpl*)Any::impl(); }

};

/**
* @brief�N���X
*
*/ 
class Class : public Frame{
public:

	/**
	* @brief ���O��^���č\�z����
	*
	*/	
	Class(const char* = 0);
	
	/**
	* @brief �N���X�𐶐������Anull������
	*
	*/
	Class(const Null&)
		:Frame(null){}
	
	Class(const Frame& outer, const Code& code, FrameCore* core);

	explicit Class(ClassImpl* p)
		:Frame((FrameImpl*)p){}

public:
	/**
	* @brief �V���������o���`����
	*
	* @param name �V������`���郁���o�̖��O
	*/
	void def(const ID& name, const Any& value) const{ Any::def(name, value); }

	/**
	* @brief �����o�����o��
	*
	* @param name ���o�����������o�̖��O
	*/
	const Any& member(const ID& name) const;

	/**
	* @brief �����o���Đݒ肷��
	*
	* @param name �Đݒ肵���������o�̖��O
	*/
	void set_member(const ID& name, const Any& value) const;

	/**
	* @brief Mix-in����
	*
	* @param md Mix-in����N���X�I�u�W�F�N�g
	*/
	void inherit(const Any& md) const;

	/**
	* @brief Mix-in����Ă��邩���ׂ�
	*
	* @param md Mix-in����Ă��钲�ׂ����N���X�I�u�W�F�N�g
	*/
	bool is_inherited(const Any& md) const;

	/**
	* @brief �֐����`����
	*
	* cls.fun("name", &foo); �� cls.def("name", xtal::fun(&foo)); �Ɠ���
	*/
	template<class Fun, class Policy>
	CFun fun(const ID& name, Fun fun, const Policy& policy) const{
		return def_and_return(name, xtal::fun(fun, policy));
	}

	/**
	* @brief �֐����`����
	*
	* cls.fun("name", &foo); �� cls.def("name", xtal::fun(&foo)); �Ɠ���
	*/
	template<class Fun>
	CFun fun(const ID& name, Fun f) const{
		return fun(name, f, result);
	}

	/**
	* @brief �֐����`����
	*
	* cls.method("name", &foo); �� cls.def("name", xtal::method(&foo)); �Ɠ���
	*/
	template<class Fun, class Policy>
	CFun method(const ID& name, Fun fun, const Policy& policy) const{
		return def_and_return(name, xtal::method(fun, policy));
	}

	/**
	* @brief �֐����`����
	*
	* cls.method("name", &foo); �� cls.def("name", xtal::method(&foo)); �Ɠ���
	*/
	template<class Fun>
	CFun method(const ID& name, Fun fun) const{
		return method(name, fun, result);
	}

public:

	void marshal_new(const VMachine& vm);

	const Any& member(const ID& name, int_t*& mutate_count) const;

	void init_instance(HaveInstanceVariables* inst, const VMachine& vm, const Any& self) const;

	void mutate() const;

	ClassImpl* impl() const{ return (ClassImpl*)Any::impl(); }

protected:

	CFun def_and_return(const ID& name, const CFun& cfun) const{
		def(name, cfun);
		return cfun;
	}

protected:

	struct init_tag{};
	
	static void make_place(Any*& p);

	static Class& make_impl(Any*& p);

	Class(const char* name, Any*& p, init_tag);

};

/**
* @brief C++�̃N���X�ɑΉ������N���X
*
* ��x�\�z�����ƁA���s�������ƕێ������B
* TClass<Foo>::get()�֐��ł�����擾�ł���B
*/
template<class C>
class TClass : public Class{
public:

	/**
	* @brief ���O��^���č\�z����
	*
	*/	
	TClass(const char* name = "")
		:Class(name, pinst_, init_tag()){}
	
	/**
	* @brief �N���X�𐶐������Anull������
	*
	*/
	TClass(const Null&)
		:Class(null){}
				
	TClass(ClassImpl* p)
		:Class(p){}

private:

	static Any* pinst_;
	
	static TClass<C>& inst(){ 
		return *(TClass<C>*)pinst_;
	}

public:

	/**
	* @brief ���̃N���X�����ɍ\�z����Ă��邩���ׂ�
	*
	*/
	static bool exists(){
		return pinst_ != 0 && *pinst_;
	}

	/**
	* @brief �\�z���ꂽ�I�u�W�F�N�g���擾����
	*
	*/
	static const TClass<C>& get(){
		XTAL_ASSERT(exists());
		return inst();
	}

	static const TClass<C>& get_uncheck(){
		return inst();
	}
	
	static void set(const TClass<C>& v){
		make_place(pinst_);
		inst() = v;
	}
	
	/**
	* @brief �w�肵���N���X�Ɠ������m��ݒ肷��
	*
	*/
	static void conform_to(const Class& v){
		make_place(pinst_);
		inst() = (const TClass<C>&)v;
	}
	
public:
	
	/**
	* @brief �����o�ϐ��ւ̃|�C���^����Q�b�^�[�𐶐����A��`����
	*
	*/
	template<class T, class U, class Policy>
	CFun getter(const ID& name, T U::* v, const Policy&) const{
		typedef detail::getter<C, T> getter;
		getter data(v);
		return def_and_return(name, CFun(&detail::method0<getter, C*, const T&, Policy>::f, &data, sizeof(data), 0));
	}
	
	/**
	* @brief �����o�ϐ��ւ̃|�C���^����Z�b�^�[�𐶐����A��`����
	*
	* Xtal�ł́Aobj.name = 10; �Ƃ���ɂ�set_name��set_��O�u�������\�b�h���`����K�v�����邽�߁A
	* �P���ȃZ�b�^�[���`�������ꍇ�Aset_xxx�Ƃ��邱�Ƃ�Y��Ȃ����ƁB
	*/
	template<class T, class U, class Policy>
	CFun setter(const ID& name, T U::* v, const Policy&) const{
		typedef detail::setter<C, T> setter;
		setter data(v);
		return def_and_return(name, CFun(&detail::method1<setter, C*, const T&, const T&, Policy>::f, &data, sizeof(data), 1));
	}
	
	/**
	* @brief �����o�ϐ��ւ̃|�C���^����Q�b�^�[�A�Z�b�^�[�𗼕��������A��`����
	*
	* cls.getter(name, var, policy);
	* cls.setter(String("set_").cat(name), v, policy);
	* �Ɠ�����	
	*/	
	template<class T, class U, class Policy>
	void var(const ID& name, T U::* v, const Policy& policy) const{
		getter(name, v, policy);
		setter(String("set_").cat(name), v, policy);
	}
	
	/**
	* @brief �����o�ϐ��ւ̃|�C���^����Q�b�^�[�𐶐����A��`����
	*
	*/
	template<class T, class U>
	CFun getter(const ID& name, T U::* v) const{
		return getter(name, v, result);
	}
	
	/**
	* @brief �����o�ϐ��ւ̃|�C���^����Z�b�^�[�𐶐����A��`����
	*
	*/
	template<class T, class U>
	CFun setter(const ID& name, T U::* v) const{
		return setter(name, v, result);
	}
	
	/**
	* @brief �����o�ϐ��ւ̃|�C���^����Q�b�^�[�A�Z�b�^�[�𗼕��������A��`����
	*
	* cls.getter(name, v);
	* cls.setter(String("set_").cat(name), v);
	* �Ɠ�����	
	*/	
	template<class T, class U>
	void var(const ID& name, T U::* v) const{
		var(name, v, result);
	}
};

template<class C>
Any* TClass<C>::pinst_ = 0;

Class new_xclass(const Frame& outer, const Code& code, FrameCore* core);

class Instance : public Any{
public:
	
	Instance(const Class& c);
	
	Instance(InstanceImpl* p)
		:Any((AnyImpl*)p){}
	
	Instance(const Null&)
		:Any(null){}
	
	InstanceImpl* impl() const{ return (InstanceImpl*)Any::impl(); }
};

}
