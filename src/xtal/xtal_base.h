
#pragma once

namespace xtal{

class Base : public Any{
public:

	/**
	* @brief �֐��I�u�W�F�N�g�Ƃ݂Ȃ��A�֐��Ăяo��������B
	*
	* ������߂�l��vm��ʂ��Ă���肷��B
	*/
	virtual void rawcall(const VMachinePtr& vm);

	/**
	* @brief name�����o�������lvalue�Œ�`����B
	*
	*/
	virtual void def(const IDPtr& primary_key, const AnyPtr& value, const AnyPtr& secondary_key = (const AnyPtr&)null, int_t accessibility = 0);

	/**
	* @brief name�����o���擾����B
	* �G�����l�����������o�擾
	*
	* @retval null ���̃����o�͑��݂��Ȃ�
	* @retval ��null name�ɑΉ����������o  
	*/
	virtual const AnyPtr& do_member(const IDPtr& primary_key, const AnyPtr& secondary_key, const AnyPtr& self, bool inherited_too, bool* nocache);

	/**
	* @brief ���̃I�u�W�F�N�g�ɕt����ꂽ���O��Ԃ��B
	*
	*/
	virtual StringPtr object_name(int_t depth = -1);

	/**
	* @brief ���̃I�u�W�F�N�g�ɕt����ꂽ���O�̐e�̖��O����Ȃ郊�X�g��Ԃ��B
	*
	*/
	virtual ArrayPtr object_name_list();
		
	/**
	* @brief ���̃I�u�W�F�N�g�ɕt����ꂽ���O�̋�����Ԃ��B
	*
	*/
	virtual int_t object_name_force();
	
	/**
	* @brief ���̃I�u�W�F�N�g�ɖ��O������B
	*
	* ���O�����ĂȂ��I�u�W�F�N�g��A�O�ɕt����ꂽ���O�̕��������ꍇ���������B
	* @param name ���閼�O
	* @param force ���O�̋���
	* @param parent �e
	*/
	virtual void set_object_name(const StringPtr& name, int_t force, const AnyPtr& parent);

	/**
	* @brief �n�b�V���l��Ԃ�
	*
	*/
	virtual uint_t hashcode();

	/**
	* @brief �t�@�C�i���C�U
	*
	* full_gc���ɁA���ʗ\��̃I�u�W�F�N�g�ƂȂ������ɔj�������邽�߂̊֐��B
	* �������Aset_finalizer_flag()���Ă�ł��Ȃ���ΌĂ΂�邱�Ƃ͂Ȃ��B
	*/
	virtual void finalize();

	/**
	* @brief ���̃I�u�W�F�N�g����������N���X��Ԃ��B
	*
	*/
	const ClassPtr& get_class(){ return *(const ClassPtr*)&class_; }

public:
	
	Base();

protected:

	Base(const Base& b);

	Base& operator =(const Base& b);

public:

	virtual ~Base();
			
public:
	
	static void* operator new(size_t size){ 
		return so_malloc(size);
	}

	static void operator delete(void* p, size_t size){
		if(p){ ((Base*)p)->class_ = Any((int_t)size); }
	}
	
	static void* operator new(size_t, void* p){ return p; }
	static void operator delete(void*, void*){}

public:

	enum{
		HAVE_FINALIZER_FLAG_SHIFT = TYPE_SHIFT+1,
		HAVE_FINALIZER_FLAG_BIT = 1<<HAVE_FINALIZER_FLAG_SHIFT,

		XTAL_INSTANCE_FLAG_SHIFT = HAVE_FINALIZER_FLAG_SHIFT+1,
		XTAL_INSTANCE_FLAG_BIT = 1<<XTAL_INSTANCE_FLAG_SHIFT,

		REF_COUNT_SHIFT = XTAL_INSTANCE_FLAG_SHIFT+1,
		REF_COUNT_MASK = ~((1<<REF_COUNT_SHIFT)-1)
	};

	InstanceVariables* instance_variables(){ return instance_variables_; }
	void make_instance_variables();

	bool is_xtal_instance(){ return (type_ & XTAL_INSTANCE_FLAG_BIT)!=0; }
	void set_xtal_instance_flag(){ type_ |= XTAL_INSTANCE_FLAG_BIT; }

	bool have_finalizer(){ return (type_ & HAVE_FINALIZER_FLAG_BIT)!=0; }
	void set_finalizer_flag(){ type_ |= HAVE_FINALIZER_FLAG_BIT; }

	uint_t ref_count(){ return (type_ & REF_COUNT_MASK)>>REF_COUNT_SHIFT; }
	void add_ref_count(int_t rc){ type_ += rc<<REF_COUNT_SHIFT; }
	void inc_ref_count(){ type_ += 1<<REF_COUNT_SHIFT; }
	void dec_ref_count(){ type_ -= 1<<REF_COUNT_SHIFT; }

	void set_class(const ClassPtr& c);

	virtual void visit_members(Visitor& m);

private:

	// �Q�ƃJ�E���^�l
	//uint_t ref_count_;

	// �C���X�^���X�ϐ��e�[�u��
	InstanceVariables* instance_variables_;

	// �����N���X
	Any class_;
	
private:

	friend class Core;
};

inline void inc_ref_count_force(const Any& v){
	if(type(v)==TYPE_BASE){
		pvalue(v)->inc_ref_count();
	}
}

inline void dec_ref_count_force(const Any& v){
	if(type(v)==TYPE_BASE){
		pvalue(v)->dec_ref_count();
	}
}

}

