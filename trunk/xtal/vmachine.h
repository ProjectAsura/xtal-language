
#pragma once

#include "any.h"
#include "string.h"

namespace xtal{

void InitArguments();

// fwd decl
class VMachineImpl;
class ArgumentsImpl;

class Arguments : public Any{
public:

	Arguments();

	explicit Arguments(ArgumentsImpl* p)
		:Any((AnyImpl*)p){}

	Arguments(const Null&)
		:Any(null){}

	const Any& op_at(const Any& index) const;
	
	int_t length() const;
	
	Any ordered_args() const;
	
	Any named_args() const;

	ArgumentsImpl* impl() const{ return (ArgumentsImpl*)Any::impl(); }
};

/**
* @brief XTAL���z�}�V��
*
*/
class VMachine : public Any{
public:

	VMachine();

	explicit VMachine(VMachineImpl* p)
		:Any((AnyImpl*)p){}

	VMachine(const Null&)
		:Any(null){}

public:

	// �֐��Ăяo�������g�����߂̊֐��Q

	/**
	* @brief �֐����Ăяo���p�ӂ�����B
	*
	*/
	void setup_call(int_t required_result_count) const;
	void setup_call(int_t required_result_count, const Any& a1) const;
	void setup_call(int_t required_result_count, const Any& a1, const Any& a2) const;
	void setup_call(int_t required_result_count, const Any& a1, const Any& a2, const Any& a3) const;
	void setup_call(int_t required_result_count, const Any& a1, const Any& a2, const Any& a3, const Any& a4) const;
	
	/**
	* @brief ������ςށB
	*
	*/
	void push_arg(const Any& value) const;
	
	/**
	* @brief ���O�t��������ςށB
	*
	*/
	void push_arg(const ID& name, const Any& value) const;

	/**
	* @brief ���O�t��������ςށB
	*
	*/
	void push_arg(const Named& p) const{ push_arg(p.name, p.value); }

	void set_call_flags(int_t flags) const;

	/**
	* @brief pos�Ԗڂ̖߂�l�𓾂�B
	*
	*/
	const Any& result(int_t pos = 0) const;
	
	/**
	* @brief pos�Ԗڂ̖߂�l��Ԃ��A�Ăяo���̌�n��������B
	*
	*/
	Any result_and_cleanup_call(int_t pos = 0) const;
	
	/**
	* @brief �Ăяo���̌�n��������B
	*
	*/
	void cleanup_call() const;
	
	/**
	* @brief this�������ւ���B
	*
	*/
	void set_arg_this(const Any& self) const;

	/**
	* @brief �q���g�̐ݒ�
	*
	* ��O���N�����Ƃ��̃G���[���b�Z�[�W�̂��߂ɁA
	* ���݌Ăяo���Ă���I�u�W�F�N�g�ƃ��\�b�h����o�^����B
	*/
	void set_hint(const Any& hint1, const String& hint2) const;
	
public:

	// �֐��Ăяo���ꑤ���g�����߂̊֐��Q

	/**
	* @brief pos�Ԗڂ̈����𓾂�B
	*
	*/
	const Any& arg(int_t pos) const;
	
	/**
	* @brief name�ɑΉ���������𓾂�B
	*
	*/
	const Any& arg(const ID& name) const;
	
	/**
	* @brief pos�Ԗڂ̈����𓾂�B����pos�Ԗڂ̈������Ȃ����name�ɑΉ���������𓾂�B
	*
	*/
	const Any& arg(int_t pos, const ID& name) const;
	
	/**
	* @brief pos�Ԗڂ̈����𓾂�B
	*
	* ����pos�Ԗڂ̈������������def�̒l��Ԃ��B
	*/
	const Any& arg_default(int_t pos, const Any& def) const;
	
	/**
	* @brief name�ɑΉ���������𓾂�B
	*
	* ����name�ɑΉ�����������������def�̒l��Ԃ��B
	*/
	const Any& arg_default(const ID& name, const Any& def) const;
	
	/**
	* @brief pos�Ԗڂ̈����𓾂�B����pos�Ԗڂ̈������Ȃ����name�ɑΉ���������𓾂�B
	*
	* ����name�ɑΉ�����������������def�̒l��Ԃ��B
	*/
	const Any& arg_default(int_t pos, const ID& name, const Any& def) const;	

	/**
	* @brief this���擾�B
	*
	*/
	const Any& get_arg_this() const;

	/**
	* @brief pos�Ԗڂ̖��O�w������̖��O���擾�B
	*
	* @param pos 0�`named_arg_count()-1�܂�
	*/
	const ID& arg_name(int_t pos) const;

	/**
	* @brief �ʒu�w������̐����擾�B
	*
	*/
	int_t ordered_arg_count() const;
	
	/**
	* @brief ���O�w������̐����擾
	*
	*/
	int_t named_arg_count() const;
	
	/**
	* @brief �Ăяo�������K�v�Ƃ��Ă���߂�l�̐��B
	*
	*/
	int_t required_result_count() const;
	
	/**
	* @brief �Ăяo�����Ɉ����̐������̖߂�l��Ԃ��B
	*
	* required_result_count�̕������������ꍇ�͂��̕�null���Ԃ����B
	* required_result_count�̕����������Ȃ��ꍇ�͕Ԃ����l�͎̂Ă���B
	*/
	void return_result() const;
	void return_result(const Any& value1) const;
	void return_result(const Any& value1, const Any& value2) const;
	void return_result(const Any& value1, const Any& value2, const Any& value3) const;
	void return_result(const Any& value1, const Any& value2, const Any& value3, const Any& value4) const;

	/**
	* @brief �Ăяo�����ɔz��̗v�f�̐������̖߂�l��Ԃ��B
	*
	* values.length�̕������������ꍇ�͂��̕�null���Ԃ����B
	* values.length�̕����������Ȃ��ꍇ�͕Ԃ����l�͎̂Ă���B
	*/
	void return_result_array(const Array& values) const;

	/**
	* @brief return_result��carry_over�����ɌĂяo�����Ȃ�true���A�����łȂ��Ȃ�false��Ԃ��B
	*
	*/
	bool processed() const;
	
	void replace_result(int_t pos, const Any& v) const;
	
	void recycle_call() const;
	
	void recycle_call(const Any& a1) const;
		
public:

	void push(const Any& v) const;

	VMachineImpl* impl() const{ return (VMachineImpl*)Any::impl(); }

	void reset() const;
};

}

