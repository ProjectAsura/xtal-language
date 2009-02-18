
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
		return variables_->at(find_class_info(class_info) + index);
	}

	void set_variable(int_t index, ClassInfo* class_info, const AnyPtr& value){
		variables_->set_at(find_class_info(class_info) + index, value);
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

	bool empty(){
		return variables_->empty();
	}

	void visit_members(Visitor& m){
		m & variables_;
	}

protected:
	
	struct VariablesInfo{
		ClassInfo* class_info;
		int_t pos;
	};

	PODStack<VariablesInfo> variables_info_;
	ArrayPtr variables_;
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

	Class(const FramePtr& outer, const CodePtr& code, ClassInfo* core);

	void overwrite(const ClassPtr& p);

public:

	/**
	* @brief �V���������o���`����
	*
	* @param name �V������`���郁���o�̖��O
	*/
	virtual void def(const IDPtr& primary_key, const AnyPtr& value, const AnyPtr& secondary_key = null, int_t accessibility = KIND_PUBLIC);

	/**
	* @brief �����o�����o��
	* �G�����l�����Ď��o��
	*
	* @param name ���o�����������o�̖��O
	* @param self �����𔻒肷�邽�߂̃I�u�W�F�N�g
	*/
	virtual const AnyPtr& do_member(const IDPtr& primary_key, const AnyPtr& secondary_key, const AnyPtr& self, bool inherited_too, bool* nocache);

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
	* @brief Mix-in����Ă��邩���ׂ�
	*
	* @param md Mix-in����Ă��钲�ׂ����N���X�I�u�W�F�N�g
	*/
	bool is_inherited(const AnyPtr& md);

	/**
	* @brief C++�̃N���X��Mix-in����Ă��邩���ׂ�
	*
	*/
	bool is_inherited_cpp_class();

	/**
	* @brief Mix-in����Ă���N���X��Iterator��Ԃ�
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
	const CFunPtr& def_fun(const IDPtr& primary_key, const TFun& f, const AnyPtr& secondary_key = null, int_t accessibility = KIND_PUBLIC){
		typedef cfun_holder<TFun> fun_t;
		fun_t fun(f);
		return def_and_return(primary_key, secondary_key, accessibility, fun_param_holder<fun_t>::value, &fun, sizeof(fun));
	}

	/**
	* @brief �֐����`����
	*
	* cls->def_method("name", &Klass::foo); �� cls->def("name", xtal::method(&Klass::foo)); �Ɠ���
	*/
	template<class TFun>
	const CFunPtr& def_method(const IDPtr& primary_key, const TFun& f, const AnyPtr& secondary_key = null, int_t accessibility = KIND_PUBLIC){
		typedef cmemfun_holder<TFun> fun_t;
		fun_t fun(f);
		return def_and_return(primary_key, secondary_key, accessibility, fun_param_holder<fun_t>::value, &fun, sizeof(fun));
	}

	/**
	* @brief �����o�ϐ��ւ̃|�C���^����Q�b�^�[�𐶐����A��`����
	*
	*/
	template<class T, class C>
	const CFunPtr& def_getter(const IDPtr& primary_key, T C::* v, const AnyPtr& secondary_key = null, int_t accessibility = KIND_PUBLIC){
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
	const CFunPtr& def_setter(const IDPtr& primary_key, T C::* v, const AnyPtr& secondary_key = null, int_t accessibility = KIND_PUBLIC){
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
	void def_dual_dispatch_method(const IDPtr& primary_key, int_t accessibility = KIND_PUBLIC);

	/**
	* @brief 2�d�f�B�X�p�b�`�֐����`����B
	*/
	void def_dual_dispatch_fun(const IDPtr& primary_key, int_t accessibility = KIND_PUBLIC);

public:
	struct cpp_class_t{};

	Class(cpp_class_t, const StringPtr& name = empty_string);

	virtual void rawcall(const VMachinePtr& vm);
	
	virtual void s_new(const VMachinePtr& vm);

	void init_instance(const AnyPtr& self, const VMachinePtr& vm);
	
	void set_member_direct(int_t i, const IDPtr& primary_key, const AnyPtr& value, const AnyPtr& secondary_key, int_t accessibility);

	const AnyPtr& any_member(const IDPtr& primary_key, const AnyPtr& secondary_key);
	
	const AnyPtr& bases_member(const IDPtr& primary_key);

	const AnyPtr& find_member(const IDPtr& primary_key, const AnyPtr& secondary_key = null, const AnyPtr& self = null, bool inherited_too = true);

	MultiValuePtr child_object_name(const AnyPtr& a);

	void set_object_name(const StringPtr& name);

	StringPtr object_name();

	void set_object_parent(const ClassPtr& parent, int_t force);

	ClassInfo* info(){
		return (ClassInfo*)scope_info_;
	}
	
	bool is_native(){
		return is_native_;
	}

	bool is_final(){
		return is_final_;
	}

	void set_final(){
		is_final_ = true;
	}

protected:

	const CFunPtr& def_and_return(const IDPtr& primary_key, const AnyPtr& secondary_key, int_t accessibility, const param_types_holder_n& pth, const void* val, int_t val_size);
	
	const AnyPtr& def2(const IDPtr& primary_key, const AnyPtr& value, const AnyPtr& secondary_key = null, int_t accessibility = KIND_PUBLIC);

	StringPtr name_;
	ArrayPtr mixins_;
	bool is_native_;
	bool is_final_;

	virtual void visit_members(Visitor& m){
		Frame::visit_members(m);
		m & mixins_;
	}

};

class CppClass : public Class{
public:
		
	CppClass(const StringPtr& name = empty_string);

public:

	virtual void rawcall(const VMachinePtr& vm);

	virtual void s_new(const VMachinePtr& vm);
};

class Singleton : public Class{
public:

	Singleton(const StringPtr& name = empty_string);

	Singleton(const FramePtr& outer, const CodePtr& code, ClassInfo* core);
	
public:

	void init_singleton(const VMachinePtr& vm);

	// �N���X�̐ݒ�̓X���[����
	void set_class(const ClassPtr&){}

	virtual void rawcall(const VMachinePtr& vm);
	
	virtual void s_new(const VMachinePtr& vm);
};

class CppSingleton : public Class{
public:
		
	CppSingleton(const StringPtr& name = empty_string);

public:

	// �N���X�̐ݒ�̓X���[����
	void set_class(const ClassPtr&){}

};

}
