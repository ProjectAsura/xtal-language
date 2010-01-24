/** \file src/xtal/xtal_base.h
* \brief src/xtal/xtal_base.h
*/

#ifndef XTAL_BASE_H_INCLUDE_GUARD
#define XTAL_BASE_H_INCLUDE_GUARD

#pragma once

namespace xtal{

void* xmalloc(size_t);
void xfree(void*p, size_t);
void* xmalloc_align(size_t, size_t);
void xfree_align(void*p, size_t, size_t);
void register_gc(RefCountingBase* p);
void register_gc_observer(GCObserver* p);
void unregister_gc_observer(GCObserver* p);

template<class T>
inline T* object_xmalloc(){
	if(AlignOf<T>::value<=8){
		return static_cast<T*>(xmalloc(sizeof(T)));
	}
	else{
		return static_cast<T*>(xmalloc_align(sizeof(T), AlignOf<T>::value));
	}
}

template<class T>
inline void object_xfree(T* p){
	if(AlignOf<T>::value<=8){
		return xfree(p, sizeof(T));
	}
	else{
		return xfree_align(p, sizeof(T), AlignOf<T>::value);
	}
}

template<int N, class T>
struct RCBaseClassType{
	enum{ value = -1 };
};

template<class T>
struct RCBaseClassType<INHERITED_RCBASE, T>{
	enum{ value = T::TYPE };
};

struct VirtualMembers{
	CppClassSymbolData** cpp_class_symbol_data;
	int rcbase_class_type;

	void (*destroy)(void*);
	void (*object_free)(void*);
	void (*rawcall)(void* p, const VMachinePtr& vm);
	void (*def)(void* p, const IDPtr& primary_key, const AnyPtr& value, const AnyPtr& secondary_key, int_t accessibility);
	const AnyPtr& (*rawmember)(void* p, const IDPtr& primary_key, const AnyPtr& secondary_key, bool inherited_too, int_t& accessibility, bool& nocache);
	const ClassPtr& (*object_parent)(void* p);
	void (*set_object_parent)(void* p, const ClassPtr& parent);
	void (*finalize)(void* p);
	void (*visit_members)(void* p, Visitor& m);
	void (*gc_signal)(void* p, int_t flag);
};
	
template<class T>
struct VirtualMembersT{
	static const VirtualMembers value;
	
	static T* cast(void* p){ return static_cast<T*>(static_cast<RefCountingBase*>(p)); }
	
	static void destroy(void* p){ cast(p)->~T(); }
	static void object_free(void* p){ object_xfree<T>(cast(p)); }
	static void rawcall(void* p, const VMachinePtr& vm){ cast(p)->on_rawcall(vm); }
	static void def(void* p, const IDPtr& primary_key, const AnyPtr& value, const AnyPtr& secondary_key, int_t accessibility){ cast(p)->on_def(primary_key, value, secondary_key, accessibility); }
	static const AnyPtr& rawmember(void* p, const IDPtr& primary_key, const AnyPtr& secondary_key, bool inherited_too, int_t& accessibility, bool& nocache){ return cast(p)->on_rawmember(primary_key, secondary_key, inherited_too, accessibility, nocache); }
	static const ClassPtr& object_parent(void* p){ return cast(p)->on_object_parent(); }
	static void set_object_parent(void* p, const ClassPtr& parent){ cast(p)->on_set_object_parent(parent); }
	static void finalize(void* p){ cast(p)->on_finalize(); }
	static void visit_members(void* p, Visitor& m){ cast(p)->on_visit_members(m); }
	static void gc_signal(void* p, int_t flag){ cast(p)->on_gc_signal(flag); }
};

template<class T>
const VirtualMembers VirtualMembersT<T>::value = {
	&CppClassSymbol<T>::value,
	RCBaseClassType<InheritedN<T>::value, T>::value,

	&VirtualMembersT<T>::destroy,
	&VirtualMembersT<T>::object_free,
	&VirtualMembersT<T>::rawcall,
	&VirtualMembersT<T>::def,
	&VirtualMembersT<T>::rawmember,
	&VirtualMembersT<T>::object_parent,
	&VirtualMembersT<T>::set_object_parent,
	&VirtualMembersT<T>::finalize,
	&VirtualMembersT<T>::visit_members,
	&VirtualMembersT<T>::gc_signal,
};

/**
* \brief �Q�ƃJ�E���^�̋@�\��L����N���X
*/
class RefCountingBase : public Any{
public:
	
	RefCountingBase()
		:Any(noinit_t()){}

	RefCountingBase(const RefCountingBase& v)
		:Any(v){}

protected:

	~RefCountingBase(){}

public:

	/**
	* \brief �֐��I�u�W�F�N�g�Ƃ݂Ȃ��A�֐��Ăяo��������B
	* ������߂�l��vm��ʂ��Ă���肷��B
	*/
	void rawcall(const VMachinePtr& vm){
		virtual_members()->rawcall(this, vm);
	}

	/**
	* \brief name�����o�������lvalue�Œ�`����B
	*/
	void def(const IDPtr& primary_key, const AnyPtr& value, const AnyPtr& secondary_key, int_t accessibility){
		virtual_members()->def(this, primary_key, value, secondary_key, accessibility);
	}

	/**
	* \brief name�����o���擾����B
	* \retval null ���̃����o�͑��݂��Ȃ�
	* \retval ��null name�ɑΉ����������o  
	*/
	const AnyPtr& rawmember(const IDPtr& primary_key, const AnyPtr& secondary_key, bool inherited_too, int_t& accessibility, bool& nocache){
		return virtual_members()->rawmember(this, primary_key, secondary_key, inherited_too, accessibility, nocache);
	}

	/**
	* \brief ���̃I�u�W�F�N�g�������o�ƂȂ��Ă���e�̃N���X��Ԃ��B
	*/
	const ClassPtr& object_parent(){
		return virtual_members()->object_parent(this);
	}
	
	/**
	* \brief ���̃I�u�W�F�N�g�ɐe��ݒ肷��B
	* �e�����ĂȂ��I�u�W�F�N�g��A�O�ɕt����ꂽ�e�̕��������ꍇ���������B
	* \param parent �e
	*/
	void set_object_parent(const ClassPtr& parent){
		virtual_members()->set_object_parent(this, parent);
	}

	/**
	* \brief �t�@�C�i���C�U
	* full_gc���ɁA���ʗ\��̃I�u�W�F�N�g�ƂȂ������ɔj�������邽�߂̊֐��B
	* �������Aset_finalizer_flag()���Ă�ł��Ȃ���ΌĂ΂�邱�Ƃ͂Ȃ��B
	* �j������Xtal�̃����o�ϐ���G�邱�Ƃ�����̂ł���΂�����g���B
	* �����łȂ��̂ł���΁A�f�X�g���N�^�ɔj���������������ƁB
	*/
	void finalize(){
		virtual_members()->finalize(this);
	}

	void visit_members(Visitor& m){
		virtual_members()->visit_members(this, m);
	}

	void gc_signal(int_t flag){
		virtual_members()->gc_signal(this, flag);
	}

public:
	void on_rawcall(const VMachinePtr& vm);
	void on_def(const IDPtr& primary_key, const AnyPtr& value, const AnyPtr& secondary_key, int_t accessibility){}
	const AnyPtr& on_rawmember(const IDPtr& primary_key, const AnyPtr& secondary_key, bool inherited_too, int_t& accessibility, bool& nocache);
	const ClassPtr& on_object_parent();
	void on_set_object_parent(const ClassPtr& parent){}
	void on_finalize(){}
	void on_visit_members(Visitor& m){}
	void on_gc_signal(int_t flag){}

public:
	bool have_finalizer(){ return value_.have_finalizer(); }
	void set_finalizer_flag(){ value_.set_finalizer_flag(); }
	void unset_finalizer_flag(){ value_.unset_finalizer_flag(); }

	uint_t ref_count(){ return value_.ref_count(); }
	void add_ref_count(int_t rc){ value_.add_ref_count(rc); }
	void inc_ref_count(){ value_.inc_ref_count(); }
	void dec_ref_count(){ value_.dec_ref_count(); }

	uint_t can_not_gc(){ return value_.can_not_gc(); }

	void destroy(){ virtual_members()->destroy(this); }
	void object_free(){ virtual_members()->object_free(this); }

public:

	template<class T>
	void set_virtual_members(){
		vmembers_ = &VirtualMembersT<T>::value;
	}

	const VirtualMembers* virtual_members() const{
		return vmembers_;
	}

private:
	const VirtualMembers* vmembers_;

private:
	static void* operator new(size_t);
public:
	static void operator delete(void*){}
	static void* operator new(size_t, void* p){ return p; }
	static void operator delete(void*, void*){}
	
private:

#ifdef XTAL_DEBUG
	virtual void virtual_function(){}
#endif

};

/**
* @brief ���N���X
*/
class Base : public RefCountingBase{
public:

	/**
	* \brief ���̃I�u�W�F�N�g����������N���X��Ԃ��B
	*/
	const ClassPtr& get_class();

public:
	
	Base();

protected:

	Base(const Base& b);

	Base& operator =(const Base& b);

public:

	~Base();
			
public:

	InstanceVariables* instance_variables(){ return instance_variables_; }

	void make_instance_variables();

	void set_class(const ClassPtr& c);

	void on_visit_members(Visitor& m);

protected:

	// �C���X�^���X�ϐ��e�[�u��
	InstanceVariables* instance_variables_;

	// �����N���X
	Class* class_;
};

}


#endif // XTAL_BASE_H_INCLUDE_GUARD
