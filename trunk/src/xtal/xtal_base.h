/** \file src/xtal/xtal_base.h
* \brief src/xtal/xtal_base.h
*/

#ifndef XTAL_BASE_H_INCLUDE_GUARD
#define XTAL_BASE_H_INCLUDE_GUARD

#pragma once

namespace xtal{

void* xmalloc(size_t);
void xfree(void*p, size_t);
void register_gc(RefCountingBase* p);
void register_gc_observer(GCObserver* p);
void unregister_gc_observer(GCObserver* p);

/**
* \brief �Q�ƃJ�E���^�̋@�\��L����N���X
*/
class RefCountingBase : public Any{
public:
	
	RefCountingBase()
		:Any(noinit_t()){}

	virtual ~RefCountingBase(){}

public:

	/**
	* \brief �֐��I�u�W�F�N�g�Ƃ݂Ȃ��A�֐��Ăяo��������B
	* ������߂�l��vm��ʂ��Ă���肷��B
	*/
	virtual void rawcall(const VMachinePtr& vm);

	/**
	* \brief name�����o�������lvalue�Œ�`����B
	*/
	virtual void def(const IDPtr& primary_key, const AnyPtr& value, const AnyPtr& secondary_key = (const AnyPtr&)undefined, int_t accessibility = 0);

	/**
	* \brief name�����o���擾����B
	* \retval null ���̃����o�͑��݂��Ȃ�
	* \retval ��null name�ɑΉ����������o  
	*/
	virtual const AnyPtr& rawmember(const IDPtr& primary_key, const AnyPtr& secondary_key, bool inherited_too, int_t& accessibility, bool& nocache);

	/**
	* \brief ���̃I�u�W�F�N�g�������o�ƂȂ��Ă���e�̃N���X��Ԃ��B
	*/
	virtual const ClassPtr& object_parent();
	
	/**
	* \brief ���̃I�u�W�F�N�g�ɐe��ݒ肷��B
	* �e�����ĂȂ��I�u�W�F�N�g��A�O�ɕt����ꂽ�e�̕��������ꍇ���������B
	* \param parent �e
	*/
	virtual void set_object_parent(const ClassPtr& parent);

	/**
	* \brief �t�@�C�i���C�U
	* full_gc���ɁA���ʗ\��̃I�u�W�F�N�g�ƂȂ������ɔj�������邽�߂̊֐��B
	* �������Aset_finalizer_flag()���Ă�ł��Ȃ���ΌĂ΂�邱�Ƃ͂Ȃ��B
	* �j������Xtal�̃����o�ϐ���G�邱�Ƃ�����̂ł���΂�����g���B
	* �����łȂ��̂ł���΁A�f�X�g���N�^�ɔj���������������ƁB
	*/
	virtual void finalize();

	virtual void visit_members(Visitor& m){}

public:

	bool have_finalizer(){ return value_.have_finalizer(); }
	void set_finalizer_flag(){ value_.set_finalizer_flag(); }
	void unset_finalizer_flag(){ value_.unset_finalizer_flag(); }

	uint_t ref_count(){ return value_.ref_count(); }
	void add_ref_count(int_t rc){ value_.add_ref_count(rc); }
	void inc_ref_count(){ value_.inc_ref_count(); }
	void dec_ref_count(){ value_.dec_ref_count(); }

	uint_t ungc(){ return value_.ungc(); }

	void destroy(){ delete this; }

	void object_free(){ xfree(this, value_.object_size()); }

public:

	static void* operator new(size_t size){ 
		return xmalloc(size);
	}

	static void operator delete(void* p, size_t size){
		if(p){ ((RefCountingBase*)p)->value_.set_object_size(size); }
	}
	
	static void* operator new(size_t, void* p){ return p; }
	static void operator delete(void*, void*){}

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

	virtual ~Base();
			
public:

	InstanceVariables* instance_variables(){ return instance_variables_; }

	void make_instance_variables();

	void set_class(const ClassPtr& c);

	virtual void visit_members(Visitor& m);

protected:

	// �C���X�^���X�ϐ��e�[�u��
	InstanceVariables* instance_variables_;

	// �����N���X
	Class* class_;
};

}


#endif // XTAL_BASE_H_INCLUDE_GUARD
