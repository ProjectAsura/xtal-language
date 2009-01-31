
#pragma once

namespace xtal{

class InstanceVariables{
public:

	struct uninit_t{};

	InstanceVariables(uninit_t){}

	InstanceVariables()		
		:variables_(xnew<Array>()){
		VariablesInfo vi;
		vi.core = 0;
		vi.pos = 0;
		variables_info_.push(vi);
	}
			
	~InstanceVariables(){}
		
	void init_variables(ClassCore* core){
		VariablesInfo vi;
		vi.core = core;
		vi.pos = (int_t)variables_->size();
		variables_->resize(vi.pos+core->instance_variable_size);
		variables_info_.push(vi);
	}

	const AnyPtr& variable(int_t index, ClassCore* core){
		return variables_->at(find_core(core) + index);
	}

	void set_variable(int_t index, ClassCore* core, const AnyPtr& value){
		variables_->set_at(find_core(core) + index, value);
	}

	int_t find_core(ClassCore* core){
		VariablesInfo& info = variables_info_.top();
		if(info.core == core)
			return info.pos;
		return find_core_inner(core);
	}

	bool is_included(ClassCore* core){
		VariablesInfo& info = variables_info_.top();
		if(info.core == core)
			return true;
		for(int_t i = 1, size = (int_t)variables_info_.size(); i<size; ++i){
			if(variables_info_[i].core==core){
				std::swap(variables_info_[0], variables_info_[i]);
				return true;
			}	
		}
		return false;
	}

	int_t find_core_inner(ClassCore* core);

	bool empty(){
		return variables_->empty();
	}

	void visit_members(Visitor& m){
		m & variables_;
	}

protected:
	
	struct VariablesInfo{
		ClassCore* core;
		int_t pos;
	};

	PODStack<VariablesInfo> variables_info_;
	ArrayPtr variables_;
};

class EmptyInstanceVariables : public InstanceVariables{
public:
	EmptyInstanceVariables():InstanceVariables(uninit_t()){}

	void init(){
		VariablesInfo vi;
		vi.core = 0;
		vi.pos = 0;
		variables_info_.push(vi);
	}

	void uninit(){
		variables_info_.release();
	}	
};
	
class Frame : public HaveName{
public:
	
	Frame(const FramePtr& outer, const CodePtr& code, ScopeCore* core);
	
	Frame();

	Frame(const Frame& frame);

	Frame& operator=(const Frame& frame);
		
	~Frame();

public:
	
	/**
	* @brief �O���̃X�R�[�v��\��Frame�I�u�W�F�N�g��Ԃ��B
	*
	*/
	const FramePtr& outer(){ 
		return outer_; 
	}

	const CodePtr& code(){ 
		return code_; 
	}

	/**
	* @brief ���e�������ɒ�`���ꂽ�v�f�̐���Ԃ��B
	*
	*/
	int_t block_size(){ 
		return core_->variable_size; 
	}

	/**
	* @brief i�Ԗڂ̃����o�[���_�C���N�g�Ɏ擾�B
	*
	*/
	const AnyPtr& member_direct(int_t i){
		return members_->at(i);
	}

	/**
	* @brief i�Ԗڂ̃����o�[���_�C���N�g�ɐݒ�B
	*
	*/
	void set_member_direct(int_t i, const AnyPtr& value){
		members_->set_at(i, value);
	}

	void set_class_member(int_t i, const IDPtr& primary_key, const AnyPtr& value, const AnyPtr& secondary_key, int_t accessibility);
		
	void set_object_name(const StringPtr& name, int_t force, const AnyPtr& parent);

	virtual StringPtr object_name(int_t depth = -1);

public:

	/**
	* @brief �����o���i�[���ꂽ�AIterator��Ԃ�
	*
	* @code
	* Xfor2(key, value, frame.members()){
	*   puts(Xf("%s %s")(key, value).to_s().c_str());
	* }
	* @endcode
	*/
	AnyPtr members();

protected:

	void make_map_members();

	friend class MembersIter;

	FramePtr outer_;
	CodePtr code_;
	ScopeCore* core_;
	
	ArrayPtr members_;

	struct Key{
		IDPtr primary_key;
		AnyPtr secondary_key;

		friend void visit_members(Visitor& m, const Key& a){
			m & a.primary_key & a.secondary_key;
		}
	};

	struct Value{
		u16 num;
		u16 flags;

		friend void visit_members(Visitor& m, const Value&){}
	};

	struct Fun{
		static uint_t hash(const Key& key){
			return (rawvalue(key.primary_key)>>3) ^ rawvalue(key.secondary_key);
		}

		static bool eq(const Key& a, const Key& b){
			return raweq(a.primary_key, b.primary_key) && raweq(a.secondary_key, b.secondary_key);
		}
	};

	typedef Hashtable<Key, Value, Fun> map_t; 
	//map_t table_;

	map_t* map_members_;


	virtual void visit_members(Visitor& m){
		HaveName::visit_members(m);
		m & outer_ & code_ & members_;
		if(map_members_){
			m & *map_members_;
		}
	}
};

class Class : public Frame{
public:

	Class(const StringPtr& name = empty_id);

	Class(const FramePtr& outer, const CodePtr& code, ClassCore* core);

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
	* @brief Mix-in����
	*
	* @param md Mix-in����N���X�I�u�W�F�N�g
	*/
	void inherit(const ClassPtr& md);

	/**
	* @brief Mix-in����
	*
	* @param md Mix-in����N���X�I�u�W�F�N�g
	*/
	void inherit_strict(const ClassPtr& md);

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
	
public:

	/**
	* @brief �֐����`����
	*
	* cls->fun("name", &foo); �� cls->def("name", xtal::fun(&foo)); �Ɠ���
	*/
	template<class TFun>
	const CFunPtr& fun(const IDPtr& primary_key, const TFun& f, const AnyPtr& secondary_key = null, int_t accessibility = KIND_PUBLIC){
		typedef cfun_holder<TFun> fun_t;
		fun_t fun(f);
		return def_and_return(primary_key, secondary_key, accessibility, &cfun<fun_t::PARAMS, fun_t>::f, &fun, sizeof(fun), fun_t::PARAMS2);
	}

	template<class TFun, TFun fun_s>
	const CFunPtr& fun_static(const IDPtr& primary_key, const AnyPtr& secondary_key = null, int_t accessibility = KIND_PUBLIC){
		typedef cfun_holder_static<TFun, fun_s> fun_t;
		fun_t fun;
		return def_and_return(primary_key, secondary_key, accessibility, &cfun<fun_t::PARAMS, fun_t>::f, &fun, sizeof(fun), fun_t::PARAMS2);
	}

	/**
	* @brief �֐����`����
	*
	* cls->method("name", &Klass::foo); �� cls->def("name", xtal::method(&Klass::foo)); �Ɠ���
	*/
	template<class TFun>
	const CFunPtr& method(const IDPtr& primary_key, const TFun& f, const AnyPtr& secondary_key = null, int_t accessibility = KIND_PUBLIC){
		typedef cmemfun_holder<TFun> fun_t;
		fun_t fun(f);
		return def_and_return(primary_key, secondary_key, accessibility, &cfun<fun_t::PARAMS, fun_t>::f, &fun, sizeof(fun), fun_t::PARAMS2);
	}

	template<class TFun, TFun fun_s>
	const CFunPtr& method_static(const IDPtr& primary_key, const AnyPtr& secondary_key, int_t accessibility = KIND_PUBLIC){
		typedef cmemfun_holder_static<TFun, fun_s> fun_t;
		fun_t fun;
		return def_and_return(primary_key, secondary_key, accessibility, &cfun<fun_t::PARAMS, fun_t>::f, &fun, 0, fun_t::PARAMS2);
	}

	template<class TFun, TFun fun_s>
	const CFunPtr& method_static(const IDPtr& primary_key){
		typedef cmemfun_holder_static<TFun, fun_s> fun_t;
		fun_t fun;
		return def_and_return(primary_key, &cfun<fun_t::PARAMS, fun_t>::f, &fun, 0, fun_t::PARAMS2);
	}

	/**
	* @brief �����o�ϐ��ւ̃|�C���^����Q�b�^�[�𐶐����A��`����
	*
	*/
	template<class T, class C>
	const CFunPtr& getter(const IDPtr& primary_key, T C::* v, const AnyPtr& secondary_key = null, int_t accessibility = KIND_PUBLIC){
		typedef getter_holder<C, T> fun_t;
		fun_t fun(v);
		return new_cfun(&cfun<fun_t::PARAMS, fun_t>::f, &fun, sizeof(fun), fun_t::PARAMS2);
	}
	
	/**
	* @brief �����o�ϐ��ւ̃|�C���^����Z�b�^�[�𐶐����A��`����
	*
	* Xtal�ł́Aobj.name = 10; �Ƃ���ɂ�set_name��set_��O�u�������\�b�h���`����K�v�����邽�߁A
	* �P���ȃZ�b�^�[���`�������ꍇ�Aset_xxx�Ƃ��邱�Ƃ�Y��Ȃ����ƁB
	*/
	template<class T, class C>
	const CFunPtr& setter(const IDPtr& primary_key, T C::* v, const AnyPtr& secondary_key = null, int_t accessibility = KIND_PUBLIC){
		typedef setter_holder<C, T> fun_t;
		fun_t fun(v);
		return new_cfun(&cfun<fun_t::PARAMS, fun_t>::f, &fun, sizeof(fun), fun_t::PARAMS2);
	}
	
	/**
	* @brief �����o�ϐ��ւ̃|�C���^����Q�b�^�[�A�Z�b�^�[�𗼕��������A��`����
	*
	* cls->getter(primary_key, var, policy);
	* cls->setter(StringPtr("set_")->cat(primary_key), v, policy);
	* �Ɠ�����	
	*/	
	template<class T, class U>
	void var(const IDPtr& primary_key, T U::* v, const AnyPtr& secondary_key = null, int_t accessibility = KIND_PUBLIC){
		getter(primary_key, v, secondary_key, accessibility);
		setter(String("set_").cat(primary_key), v, secondary_key, accessibility);
	}

	/**
	* @brief 2�d�f�B�X�p�b�`���\�b�h���`����B
	*/
	void dual_dispatch_method(const IDPtr& primary_key, int_t accessibility = KIND_PUBLIC){
		def(primary_key, xtal::dual_dispatch_method(primary_key), null, accessibility);
	}

	/**
	* @brief 2�d�f�B�X�p�b�`�֐����`����B
	*/
	void dual_dispatch_fun(const IDPtr& primary_key, int_t accessibility = KIND_PUBLIC){
		def(primary_key, xtal::dual_dispatch_fun(from_this(this), primary_key), null, accessibility);
	}

	AnyPtr ancestors();

public:

	virtual void rawcall(const VMachinePtr& vm);
	
	virtual void s_new(const VMachinePtr& vm);

	void init_instance(const AnyPtr& self, const VMachinePtr& vm);
	
	const AnyPtr& any_member(const IDPtr& primary_key, const AnyPtr& secondary_key);
	
	const AnyPtr& bases_member(const IDPtr& primary_key);

	const AnyPtr& find_member(const IDPtr& primary_key, const AnyPtr& secondary_key = null, const AnyPtr& self = null, bool inherited_too = true);

	ClassCore* core(){
		return (ClassCore*)core_;
	}
	
	struct cpp_class_t{};

	Class(cpp_class_t, const StringPtr& name = empty_id);

	bool is_cpp_class(){
		return is_cpp_class_;
	}

protected:

	const CFunPtr& def_and_return(const IDPtr& primary_key, const AnyPtr& secondary_key, int_t accessibility, void (*fun_t)(ParamInfoAndVM& pvm), const void* val, int_t val_size, int_t param_n);
	const CFunPtr& def_and_return(const IDPtr& primary_key, void (*fun_t)(ParamInfoAndVM& pvm), const void* val, int_t val_size, int_t param_n);

	const AnyPtr& def2(const IDPtr& primary_key, const AnyPtr& value, const AnyPtr& secondary_key = null, int_t accessibility = KIND_PUBLIC);

	ArrayPtr mixins_;
	bool is_cpp_class_;

	virtual void visit_members(Visitor& m){
		Frame::visit_members(m);
		m & mixins_;
	}

};

class CppClass : public Class{
public:
		
	CppClass(const StringPtr& name = empty_id);

public:

	virtual void rawcall(const VMachinePtr& vm);

	virtual void s_new(const VMachinePtr& vm);
};

class Lib : public Class{
public:

	Lib();

	Lib(const ArrayPtr& path);
	
	virtual const AnyPtr& do_member(const IDPtr& primary_key, const AnyPtr& secondary_key, const AnyPtr& self, bool inherited_too, bool* nocache);

	virtual void def(const IDPtr& primary_key, const AnyPtr& value, const AnyPtr& secondary_key, int_t accessibility);

	void append_load_path(const StringPtr& path){
		load_path_list_->push_back(path);
	}

private:

	const AnyPtr& rawdef(const IDPtr& primary_key, const AnyPtr& value, const AnyPtr& secondary_key);

	StringPtr join_path(const StringPtr& sep);

private:

	ArrayPtr load_path_list_;
	ArrayPtr path_;

	virtual void visit_members(Visitor& m){
		Class::visit_members(m);
		m & path_ & load_path_list_;
	}
};

class Singleton : public Class{
public:

	Singleton(const StringPtr& name = empty_id);

	Singleton(const FramePtr& outer, const CodePtr& code, ClassCore* core);
	
public:

	void init_singleton(const VMachinePtr& vm);

	// �N���X�̐ݒ�̓X���[����
	void set_class(const ClassPtr&){}

	virtual void rawcall(const VMachinePtr& vm);
	
	virtual void s_new(const VMachinePtr& vm);
};

class CppSingleton : public Class{
public:
		
	CppSingleton(const StringPtr& name = empty_id);

public:

	// �N���X�̐ݒ�̓X���[����
	void set_class(const ClassPtr&){}

};

}
