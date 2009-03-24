#ifndef XTAL_CLASS_H_INCLUDE_GUARD
#define XTAL_CLASS_H_INCLUDE_GUARD

#pragma once

namespace xtal{

class InstanceVariables{
public:

	struct uninit_t{};

	InstanceVariables(uninit_t){}

	InstanceVariables();
			
	~InstanceVariables();
		
	void init_variables(ClassInfo* class_info);

	const AnyPtr& variable(int_t index, ClassInfo* class_info){
		int_t i = find_class_info(class_info) + index;
		if(i<0){ return undefined; }
		return variables_.at(i);
	}

	void set_variable(int_t index, ClassInfo* class_info, const AnyPtr& value){
		int_t i = find_class_info(class_info) + index;
		if(i<0){ return; }
		variables_.set_at(i, value);
	}

	int_t find_class_info(ClassInfo* class_info){
		VariablesInfo& info = variables_info_.top();
		if(info.class_info == class_info){
			return info.pos;
		}
		return find_class_info_inner(class_info);
	}

	bool is_included(ClassInfo* class_info);

	int_t find_class_info_inner(ClassInfo* class_info);

	void replace(ClassInfo* from, ClassInfo* to);

	bool empty(){
		return variables_.empty();
	}

	void visit_members(Visitor& m){
		for(uint_t i=0; i<variables_.size(); ++i){
			m & variables_.at(i);
		}
	}

protected:
	
	struct VariablesInfo{
		ClassInfo* class_info;
		int_t pos;
	};

	PODStack<VariablesInfo> variables_info_;
	Array variables_;
};

class EmptyInstanceVariables : public InstanceVariables{
public:

	EmptyInstanceVariables();

	~EmptyInstanceVariables();

	static VariablesInfo vi;
};

class Class : public Frame{
public:

	Class(const StringPtr& name = empty_string);

	Class(const FramePtr& outer, const CodePtr& code, ClassInfo* info);

	virtual ~Class();

	void overwrite(const ClassPtr& p);

	void overwrite_member(const IDPtr& primary_key, const AnyPtr& value, const AnyPtr& secondary_key = null, int_t accessibility = KIND_PUBLIC);

public:

	/**
	* @brief �V���������o���`����
	*
	* @param name �V������`���郁���o�̖��O
	*/
	virtual void def(const IDPtr& primary_key, const AnyPtr& value, const AnyPtr& secondary_key = null, int_t accessibility = KIND_PUBLIC);

	/**
	* @brief �����o�����o��
	*
	* @param name ���o�����������o�̖��O
	*/
	virtual const AnyPtr& do_member(const IDPtr& primary_key, const AnyPtr& secondary_key, bool inherited_too, int_t& accessibility, bool& nocache);

	/**
	* @brief �����o���Đݒ肷��
	* Xtal���x���ł͋֎~����Ă��鑀�삾���AC++���x���ł͉\�ɂ��Ă���
	*
	* @param name �Đݒ肵���������o�̖��O
	*/
	void set_member(const IDPtr& primary_key, const AnyPtr& value, const AnyPtr& secondary_key);

	/**
	* @brief �p��
	*
	* @param cls �p������N���X�I�u�W�F�N�g
	*/
	void inherit(const ClassPtr& cls);

	/**
	* @brief �p������
	*
	* @param cls �p������N���X�I�u�W�F�N�g
	*/
	void inherit_first(const ClassPtr& cls);

	/**
	* @brief �p������
	*
	* @param cls �p������N���X�I�u�W�F�N�g
	*/
	void inherit_strict(const ClassPtr& cls);

	/**
	* @brief �p������Ă��邩���ׂ�
	*
	* @param md �p������Ă��钲�ׂ����N���X�I�u�W�F�N�g
	*/
	bool is_inherited(const AnyPtr& md);

	/**
	* @brief C++�̃N���X��Mix-in����Ă��邩���ׂ�
	*
	*/
	bool is_inherited_cpp_class();

	/**
	* @brief �p������Ă���N���X��Iterator��Ԃ�
	*
	*/
	AnyPtr inherited_classes();

	/**
	* @brief �߂����O�̃����o����������
	*/
	IDPtr find_near_member(const IDPtr& primary_key, const AnyPtr& secondary_key = null);
	
	AnyPtr ancestors();

public:
	/**
	* @brief �֐����`����
	*
	* cls->def_fun("name", &foo); �� cls->def("name", xtal::fun(&foo)); �Ɠ���
	*/
	template<class TFun>
	const NativeFunPtr& def_fun(const IDPtr& primary_key, const TFun& f, const AnyPtr& secondary_key = null, int_t accessibility = KIND_PUBLIC){
		typedef cfun_holder<TFun> fun_t;
		fun_t fun(f);
		return def_and_return(primary_key, secondary_key, accessibility, fun_param_holder<fun_t>::value, &fun, sizeof(fun));
	}

	/**
	* @brief ���\�b�h���`����
	*
	* cls->def_method("name", &Klass::foo); �� cls->def("name", xtal::method(&Klass::foo)); �Ɠ���
	*/
	template<class TFun>
	const NativeFunPtr& def_method(const IDPtr& primary_key, const TFun& f, const AnyPtr& secondary_key = null, int_t accessibility = KIND_PUBLIC){
		typedef cmemfun_holder<TFun> fun_t;
		fun_t fun(f);
		return def_and_return(primary_key, secondary_key, accessibility, fun_param_holder<fun_t>::value, &fun, sizeof(fun));
	}

	/**
	* @brief �����o�ϐ��ւ̃|�C���^����Q�b�^�[�𐶐����A��`����
	*
	*/
	template<class T, class C>
	const NativeFunPtr& def_getter(const IDPtr& primary_key, T C::* v, const AnyPtr& secondary_key = null, int_t accessibility = KIND_PUBLIC){
		typedef getter_holder<C, T> fun_t;
		fun_t fun(v);
		return def_and_return(primary_key, secondary_key, accessibility, fun_param_holder<fun_t>::value, &fun, sizeof(fun));
	}
	
	/**
	* @brief �����o�ϐ��ւ̃|�C���^����Z�b�^�[�𐶐����A��`����
	*
	* Xtal�ł́Aobj.name = 10; �Ƃ���ɂ�set_name��set_��O�u�������\�b�h���`����K�v�����邽�߁A
	* �P���ȃZ�b�^�[���`�������ꍇ�Aset_xxx�Ƃ��邱�Ƃ�Y��Ȃ����ƁB
	*/
	template<class T, class C>
	const NativeFunPtr& def_setter(const IDPtr& primary_key, T C::* v, const AnyPtr& secondary_key = null, int_t accessibility = KIND_PUBLIC){
		typedef setter_holder<C, T> fun_t;
		fun_t fun(v);
		return def_and_return(primary_key, secondary_key, accessibility, fun_param_holder<fun_t>::value, &fun, sizeof(fun));
	}
	
	/**
	* @brief �����o�ϐ��ւ̃|�C���^����Q�b�^�[�A�Z�b�^�[�𗼕��������A��`����
	*
	* cls->def_getter(primary_key, var, policy);
	* cls->def_setter(StringPtr("set_")->cat(primary_key), v, policy);
	* �Ɠ�����	
	*/	
	template<class T, class U>
	void def_var(const IDPtr& primary_key, T U::* v, const AnyPtr& secondary_key = null, int_t accessibility = KIND_PUBLIC){
		def_getter(primary_key, v, secondary_key, accessibility);
		def_setter(String("set_").cat(primary_key), v, secondary_key, accessibility);
	}

	/**
	* @brief 2�d�f�B�X�p�b�`���\�b�h���`����B
	*/
	void def_double_dispatch_method(const IDPtr& primary_key, int_t accessibility = KIND_PUBLIC);

	/**
	* @brief 2�d�f�B�X�p�b�`�֐����`����B
	*/
	void def_double_dispatch_fun(const IDPtr& primary_key, int_t accessibility = KIND_PUBLIC);

public:

	/**
	* @brief ���\�b�h���`����
	*
	*/
	template<class TFun>
	const NativeFunPtr& def_singleton_method(const IDPtr& primary_key, const TFun& f, const AnyPtr& secondary_key = null, int_t accessibility = KIND_PUBLIC){
		typedef cmemfun_holder<TFun> fun_t;
		fun_t fun(f);
		return def_and_return_bind_this(primary_key, secondary_key, accessibility, fun_param_holder<fun_t>::value, &fun, sizeof(fun));
	}

	/**
	* @brief �����o�ϐ��ւ̃|�C���^����Q�b�^�[�𐶐����A��`����
	*
	*/
	template<class T, class C>
	const NativeFunPtr& def_singleton_getter(const IDPtr& primary_key, T C::* v, const AnyPtr& secondary_key = null, int_t accessibility = KIND_PUBLIC){
		typedef getter_holder<C, T> fun_t;
		fun_t fun(v);
		return def_and_return_bind_this(primary_key, secondary_key, accessibility, fun_param_holder<fun_t>::value, &fun, sizeof(fun));
	}
	
	/**
	* @brief �����o�ϐ��ւ̃|�C���^����Z�b�^�[�𐶐����A��`����
	*
	* Xtal�ł́Aobj.name = 10; �Ƃ���ɂ�set_name��set_��O�u�������\�b�h���`����K�v�����邽�߁A
	* �P���ȃZ�b�^�[���`�������ꍇ�Aset_xxx�Ƃ��邱�Ƃ�Y��Ȃ����ƁB
	*/
	template<class T, class C>
	const NativeFunPtr& def_singleton_setter(const IDPtr& primary_key, T C::* v, const AnyPtr& secondary_key = null, int_t accessibility = KIND_PUBLIC){
		typedef setter_holder<C, T> fun_t;
		fun_t fun(v);
		return def_and_return_bind_this(primary_key, secondary_key, accessibility, fun_param_holder<fun_t>::value, &fun, sizeof(fun));
	}
	
	/**
	* @brief �����o�ϐ��ւ̃|�C���^����Q�b�^�[�A�Z�b�^�[�𗼕��������A��`����
	*
	* cls->def_getter(primary_key, var, policy);
	* cls->def_setter(StringPtr("set_")->cat(primary_key), v, policy);
	* �Ɠ�����	
	*/	
	template<class T, class U>
	void def_singleton_var(const IDPtr& primary_key, T U::* v, const AnyPtr& secondary_key = null, int_t accessibility = KIND_PUBLIC){
		def_singleton_getter(primary_key, v, secondary_key, accessibility);
		def_singleton_setter(String("set_").cat(primary_key), v, secondary_key, accessibility);
	}

public:

	struct cpp_class_t{};

	Class(cpp_class_t);

	virtual void rawcall(const VMachinePtr& vm);
	
	virtual void s_new(const VMachinePtr& vm);

	void init_instance(const AnyPtr& self, const VMachinePtr& vm);
	
	void set_member_direct(int_t i, const IDPtr& primary_key, const AnyPtr& value, const AnyPtr& secondary_key, int_t accessibility);

	const AnyPtr& any_member(const IDPtr& primary_key, const AnyPtr& secondary_key);
	
	const AnyPtr& bases_member(const IDPtr& primary_key);

	const AnyPtr& find_member(const IDPtr& primary_key, const AnyPtr& secondary_key, bool inherited_too, int_t& accessibility, bool& nocache);

	MultiValuePtr child_object_name(const AnyPtr& a);

	void set_object_name(const StringPtr& name);

	StringPtr object_name();

	void set_object_parent(const ClassPtr& parent);

	uint_t object_force(){
		return object_force_;
	}

	void set_object_force(uint_t force){
		object_force_ = (u16)force;
	}

	ClassInfo* info(){
		return (ClassInfo*)scope_info_;
	}

	void unset_native(){
		flags_ &= ~FLAG_NATIVE;
	}
	
	bool is_native(){
		return (flags_&FLAG_NATIVE)!=0;
	}

	bool is_final(){
		return (flags_&FLAG_FINAL)!=0;
	}

	void set_final(){
		flags_ |= FLAG_FINAL;
	}

	bool is_singleton(){
		return (flags_&FLAG_SINGLETON)!=0;
	}

	void prebind();

	void set_prebinder(bind_class_fun_t binder){
		prebinder_ = binder;
	}

	bind_class_fun_t prebinder(){
		return prebinder_;
	}

	void bind();

	void set_binder(bind_class_fun_t binder){
		binder_ = binder;
	}

	bind_class_fun_t binder(){
		return binder_;
	}

	void def_ctor(const AnyPtr& ctor_fun);

	const AnyPtr& ctor();

	void def_serial_ctor(const AnyPtr& ctor_fun);

	const AnyPtr& serial_ctor();

protected:

	const NativeFunPtr& def_and_return(const IDPtr& primary_key, const AnyPtr& secondary_key, int_t accessibility, const param_types_holder_n& pth, const void* val, int_t val_size);

	const NativeFunPtr& def_and_return_bind_this(const IDPtr& primary_key, const AnyPtr& secondary_key, int_t accessibility, const param_types_holder_n& pth, const void* val, int_t val_size);
	
	const AnyPtr& def2(const IDPtr& primary_key, const AnyPtr& value, const AnyPtr& secondary_key = null, int_t accessibility = KIND_PUBLIC);

	StringPtr name_;

	AnyPtr ctor_;
	AnyPtr serial_ctor_;

	PODArrayList<Class*> inherited_classes_;
	void (*prebinder_)(const ClassPtr& cls);
	void (*binder_)(const ClassPtr& cls);
	u16 object_force_;
	u16 flags_;

	enum{
		FLAG_NATIVE = 1<<0,
		FLAG_FINAL = 1<<1,
		FLAG_SINGLETON = 1<<2
	};

	virtual void visit_members(Visitor& m){
		Frame::visit_members(m);
		for(uint_t i=0; i<inherited_classes_.size(); ++i){
			m & inherited_classes_[i];
		}
	}

	friend class ClassInheritedClassesIter;
};


class ClassInheritedClassesIter : public Base{
public:

	ClassInheritedClassesIter(const ClassPtr& cls)
		:class_(cls), index_(0){}
	
	void block_next(const VMachinePtr& vm){
		++index_;
		if(index_<=class_->inherited_classes_.size()){
			vm->return_result(to_smartptr(this), to_smartptr(class_->inherited_classes_[index_-1]));
		}
		else{
			vm->return_result(null, null);
		}
	}

private:
	ClassPtr class_;
	uint_t index_;

	virtual void visit_members(Visitor& m){
		Base::visit_members(m);
		m & class_;
	}
};

class Singleton : public Class{
public:

	Singleton(const StringPtr& name = empty_string);

	Singleton(const FramePtr& outer, const CodePtr& code, ClassInfo* info);
	
public:

	void init_singleton(const VMachinePtr& vm);

	// �N���X�̐ݒ�̓X���[����
	void set_class(const ClassPtr&){}

	virtual void rawcall(const VMachinePtr& vm);
	
	virtual void s_new(const VMachinePtr& vm);
};

class CppSingleton : public Class{
public:
		
	CppSingleton();

public:

	// �N���X�̐ݒ�̓X���[����
	void set_class(const ClassPtr&){}

};

}

#endif // XTAL_CLASS_H_INCLUDE_GUARD
