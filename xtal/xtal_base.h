
#pragma once

namespace xtal{

class Base{
public:

	/**
	* @brief �֐��I�u�W�F�N�g�Ƃ݂Ȃ��A�֐��Ăяo��������B
	*
	* ������߂�l��vm��ʂ��Ă���肷��B
	*/
	virtual void call(const VMachinePtr& vm);
	
	/**
	* @brief name�����o���擾����B
	* �G�����l�����������o�擾
	*
	* @retval null ���̃����o�͑��݂��Ȃ�
	* @retval ��null name�ɑΉ����������o  
	*/
	const AnyPtr& member(const InternedStringPtr& name, const AnyPtr& self = (const AnyPtr& )null, const AnyPtr& ns = (const AnyPtr& )null);

	/**
	* @brief name���\�b�h�Ăяo��������
	*
	* ������߂�l��vm��ʂ��Ă���肷��B
	*/
	void rawsend(const VMachinePtr& vm, const InternedStringPtr& name, const AnyPtr& self = (const AnyPtr& )null, const AnyPtr& ns = (const AnyPtr& )null);

	/**
	* @brief name�����o�������lvalue�Œ�`����B
	*
	*/
	virtual void def(const InternedStringPtr& name, const AnyPtr& value, int_t accessibility = 0, const AnyPtr& ns = (const AnyPtr&)null);

	/**
	* @brief ���̃I�u�W�F�N�g����������N���X��Ԃ��B
	*
	*/
	const ClassPtr& get_class(){ return (const ClassPtr&)class_; }

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
	* @brief cls�N���X�̃C���X�^���X�����ׂ�B
	*
	*/
	bool is(const ClassPtr& klass);

	/**
	* @brief name�����o���擾����B
	* �G�����l�����������o�擾
	*
	* @retval null ���̃����o�͑��݂��Ȃ�
	* @retval ��null name�ɑΉ����������o  
	*/
	virtual const AnyPtr& do_member(const InternedStringPtr& name, const AnyPtr& self = (const AnyPtr& )null, const AnyPtr& ns = (const AnyPtr& )null);

	/**
	* @brief ���̃I�u�W�F�N�g�ɕt����ꂽ���O��Ԃ��B
	*
	*/
	virtual StringPtr object_name();
		
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

	AnyPtr send(const InternedStringPtr& name);

	template<class A0>
	AnyPtr send(const InternedStringPtr& name, const A0& a0);

	template<class A0, class A1>
	AnyPtr send(const InternedStringPtr& name, const A0& a0, const A1& a1);

	template<class A0, class A1, class A2>
	AnyPtr send(const InternedStringPtr& name, const A0& a0, const A1& a1, const A2& a2);

	template<class A0, class A1, class A2, class A3>
	AnyPtr send(const InternedStringPtr& name, const A0& a0, const A1& a1, const A2& a2, const A3& a3);

	template<class A0, class A1, class A2, class A3, class A4>
	AnyPtr send(const InternedStringPtr& name, const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4);

public:
	
	Base();

	Base(const Base& b);

	Base& operator =(const Base& b);

	virtual ~Base();
			
public:
	
	static void* operator new(size_t size);
	static void operator delete(void* p);
	
	static void* operator new(size_t, void* p){ return p; }
	static void operator delete(void*, void*){}

public:

	InstanceVariables* instance_variables(){ return instance_variables_; }
	void make_instance_variables();

	uint_t ref_count(){ return ref_count_; }
	void add_ref_count(int_t rc){ ref_count_+=rc; }
	void inc_ref_count(){ ++ref_count_; }
	void dec_ref_count(){ --ref_count_; }
	void set_ref_count(uint_t rc){ ref_count_ = rc; }

	void set_class(const ClassPtr& c);

	virtual void visit_members(Visitor& m);
	
private:

	// �Q�ƃJ�E���^�l
	uint_t ref_count_;

	// �C���X�^���X�ϐ��e�[�u��
	InstanceVariables* instance_variables_;

	// �����N���X
	Innocence class_;
	
private:

	friend void gc();
	friend void full_gc();
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

