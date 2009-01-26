
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
	* @brief name�����o���擾����B
	* �G�����l�����������o�擾
	*
	* @retval undefined ���̃����o�͑��݂��Ȃ�
	* @retval ��undefined name�ɑΉ����������o  
	*/
	const AnyPtr& member(const IDPtr& primary_key, const AnyPtr& secondary_key = (const AnyPtr& )null, const AnyPtr& self = (const AnyPtr& )null, bool inherited_too = true);

	/**
	* @brief name���\�b�h�Ăяo��������
	*
	* ������߂�l��vm��ʂ��Ă���肷��B
	*/
	void rawsend(const VMachinePtr& vm, const IDPtr& primary_key, const AnyPtr& secondary_key = (const AnyPtr& )null, const AnyPtr& self = (const AnyPtr& )null, bool inherited_too = true);

	/**
	* @brief name�����o�������lvalue�Œ�`����B
	*
	*/
	virtual void def(const IDPtr& primary_key, const AnyPtr& value, const AnyPtr& secondary_key = (const AnyPtr&)null, int_t accessibility = 0);

	/**
	* @brief ���̃I�u�W�F�N�g����������N���X��Ԃ��B
	*
	*/
	const ClassPtr& get_class(){ return *(const ClassPtr*)&class_; }

	/**
	* @brief �����ɕϊ����ĕԂ��B
	*
	*/
	int_t to_i();
	
	/**
	* @brief ���������_���ɕϊ����ĕԂ��B
	*
	*/
	float_t to_f();
	
	/**
	* @brief ������ɕϊ����ĕԂ��B
	*
	*/
	StringPtr to_s();

	/**
	* @brief �z��ɕϊ����ĕԂ��B
	*
	*/
	ArrayPtr to_a();

	/**
	* @brief �A�z�z��ɕϊ����ĕԂ��B
	*
	*/
	MapPtr to_m();

	/**
	* @brief cls�N���X�̃C���X�^���X�����ׂ�B
	*
	*/
	bool is(const AnyPtr& klass);

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
	* @brief ���g�𕶎��񉻂���println����B
	* @return ���g��Ԃ��B
	*/
	AnyPtr p();

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
		if(p){ ((Base*)p)->class_ = Innocence((int_t)size); }
	}
	
	static void* operator new(size_t, void* p){ return p; }
	static void operator delete(void*, void*){}

public:

	enum{
		XTAL_INSTANCE_FLAG_SHIFT = TYPE_SHIFT+1,
		XTAL_INSTANCE_FLAG_BIT = 1<<(XTAL_INSTANCE_FLAG_SHIFT),
		REF_COUNT_SHIFT = XTAL_INSTANCE_FLAG_SHIFT+1,
		REF_COUNT_MASK = ~((1<<XTAL_INSTANCE_FLAG_SHIFT)-1)
	};

	InstanceVariables* instance_variables(){ return instance_variables_; }
	void make_instance_variables();

	uint_t ref_count(){ return (type_ & REF_COUNT_MASK)>>REF_COUNT_SHIFT; }
	void add_ref_count(int_t rc){ type_ += rc<<REF_COUNT_SHIFT; }
	void inc_ref_count(){ type_ += 1<<REF_COUNT_SHIFT; }
	void dec_ref_count(){ type_ -= 1<<REF_COUNT_SHIFT; }

	void set_class(const ClassPtr& c);

	virtual void visit_members(Visitor& m);

	bool is_xtal_instance(){ return (type_ & XTAL_INSTANCE_FLAG_BIT)!=0; }
	void set_xtal_instance_flag(){ type_ |= XTAL_INSTANCE_FLAG_BIT; }
	
private:

	// �Q�ƃJ�E���^�l
	//uint_t ref_count_;

	// �C���X�^���X�ϐ��e�[�u��
	InstanceVariables* instance_variables_;

	// �����N���X
	Innocence class_;
	
private:

	friend void gc();
	friend void full_gc();
	friend void initialize();
};

class GCObserver : public Base{
public:
	GCObserver();
	GCObserver(const GCObserver& v);
	virtual ~GCObserver();
	virtual void before_gc(){}
	virtual void after_gc(){}
};

}

