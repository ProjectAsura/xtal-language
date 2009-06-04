/** \file src/xtal/xtal_debug.h
* \brief src/xtal/xtal_debug.h
*/

#ifndef XTAL_DEBUG_H_INCLUDE_GUARD
#define XTAL_DEBUG_H_INCLUDE_GUARD

#pragma once

namespace xtal{

/**
* \xbind lib::builtin
* \brief �f�o�b�O
*/
namespace debug{

class CallerInfo : public Base{
public:

	/**
	* \xbind
	* \brief �Ăяo���ꏊ�̍s����Ԃ�
	*/
	int_t line(){ return line_; }

	/**
	* \xbind
	* \brief �Ăяo���ꏊ�̃t�@�C������Ԃ�
	*/
	const StringPtr& file_name(){ return file_name_; }

	/**
	* \xbind
	* \brief �Ăяo���ꏊ�̊֐�����Ԃ�
	*/
	const StringPtr& fun_name(){ return fun_name_; }

	/**
	* \xbind
	* \brief �Ăяo���ꏊ�̕ϐ��t���[���I�u�W�F�N�g��Ԃ�
	*/
	const FramePtr& variables_frame(){ return variables_frame_; }

	void set_line(int_t v){ line_ = v; }
	void set_file_name(const StringPtr& v){ file_name_ = v; }
	void set_fun_name(const StringPtr& v){ fun_name_ = v; }
	void set_variables_frame(const FramePtr& v){ variables_frame_ = v; }

	virtual void visit_members(Visitor& m);

private:
	int_t line_;
	StringPtr file_name_;
	StringPtr fun_name_;
	FramePtr variables_frame_;
};

typedef SmartPtr<CallerInfo> CallerInfoPtr;

/**
* \xbind lib::builtin::debug
* \xinherit lib::builtin::Any
* \brief �f�o�b�O�t�b�N�֐��œn�����I�u�W�F�N�g
*/
class HookInfo : public Base{
public:
	
	/**
	* \xbind
	* \brief �t�b�N�̎�ނ�Ԃ�
	*/
	int_t kind(){ return kind_; } 

	/**
	* \xbind
	* \brief �t�b�N���ꂽ�ꏊ�̍s����Ԃ�
	*/
	int_t line(){ return line_; }

	/**
	* \xbind
	* \brief �t�b�N���ꂽ�ꏊ�̃t�@�C������Ԃ�
	*/
	const StringPtr& file_name(){ return file_name_; }

	/**
	* \xbind
	* \brief �t�b�N���ꂽ�ꏊ�̊֐�����Ԃ�
	*/
	const StringPtr& fun_name(){ return fun_name_; }

	/**
	* \xbind
	* \brief assertion�̃��b�Z�[�W��Ԃ�
	*/
	const StringPtr& assertion_message(){ return assertion_message_; }

	/**
	* \xbind
	* \brief ��O�I�u�W�F�N�g��Ԃ�
	*/
	const AnyPtr& exception(){ return exception_; }

	/**
	* \xbind
	* \brief �t�b�N���ꂽ�ꏊ�̕ϐ��t���[���I�u�W�F�N�g��Ԃ�
	*/
	const FramePtr& variables_frame(){ return variables_frame_; }

	/**
	* \brief �Ăяo�����̏���Ԃ�
	*/
	CallerInfoPtr caller(uint_t n);

	void set_kind(int_t v){ kind_ = v; }
	void set_line(int_t v){ line_ = v; }
	void set_file_name(const StringPtr& v){ file_name_ = v; }
	void set_fun_name(const StringPtr& v){ fun_name_ = v; }
	void set_assertion_message(const StringPtr& v){ assertion_message_ = v; }
	void set_exception(const AnyPtr& e){ exception_ = e; }
	void set_variables_frame(const FramePtr& v){ variables_frame_ = v; }

	/**
	* \xbind
	* \brief �N���[�������
	* DebugInfo�I�u�W�F�N�g�͎g���܂킳��邽�߁A����ێ��������ꍇ�A�N���[�������K�v������B
	*/
	SmartPtr<HookInfo> clone(){
		return xnew<HookInfo>(*this);
	}

	void set_vm(const VMachinePtr& v){ vm_ = v; }

	const VMachinePtr& vm(){ return ptr_cast<VMachine>(ap(vm_)); }

private:

	virtual void visit_members(Visitor& m);

	int_t kind_;
	int_t line_;
	StringPtr file_name_;
	StringPtr fun_name_;
	StringPtr assertion_message_;
	AnyPtr exception_;
	FramePtr variables_frame_;
	Any vm_;
	uint_t funframe_;

	friend class VMachine;
};

typedef SmartPtr<HookInfo> HookInfoPtr;

class Debug;

/**
* \xbind lib::builtin::debug
* \brief �f�o�b�O�@�\��L���ɂ���
* �f�o�b�O�@�\�̓f�t�H���g�ł͖����ɂȂ��Ă���B
*/
void enable();

/**
* \xbind lib::builtin::debug
* \brief �f�o�b�O�@�\�𖳌��ɂ���
*/
void disable();

/**
* \xbind lib::builtin::debug
* \brief �f�o�b�O�@�\�������I�ɗL���ɂ���
* �f�o�b�O�@�\�̓f�t�H���g�ł͖����ɂȂ��Ă���B
*/
void enable_force(int_t count);

/**
* \xbind lib::builtin::debug
* \brief �f�o�b�O�@�\�������I�ɖ����ɂ���
*/
int_t disable_force();

/**
* \xbind lib::builtin::debug
* \brief �f�o�b�O�@�\���L�����ǂ���
*/
bool is_enabled();

uint_t hook_setting_bit();

/**
* \xbind lib::builtin::debug
* \brief �u���[�N�|�C���g������x�ɌĂяo�����t�b�N�֐���o�^����
* \param hook �o�^����t�b�N�֐�
*/
void set_break_point_hook(const AnyPtr& hook);

/**
* \xbind lib::builtin::debug
* \brief �֐��Ăяo�������x�ɌĂяo�����t�b�N�֐���o�^����
* \param hook �o�^����t�b�N�֐�
*/
void set_call_hook(const AnyPtr& hook);

/**
* \xbind lib::builtin::debug
* \brief �֐�����return�����x�ɌĂяo�����t�b�N�֐���o�^����
* \param hook �o�^����t�b�N�֐�
*/
void set_return_hook(const AnyPtr& hook);

/**
* \xbind lib::builtin::debug
* \brief ��O��throw�����x�ɌĂяo�����t�b�N�֐���o�^����
* \param hook �o�^����t�b�N�֐�
*/
void set_throw_hook(const AnyPtr& hook);

/**
* \xbind lib::builtin::debug
* \brief �A�T�[�g�����s�����x�ɌĂяo�����t�b�N�֐���o�^����
* \param hook �o�^����t�b�N�֐�
*/
void set_assert_hook(const AnyPtr& hook);

/**
* \xbind lib::builtin::debug
* \brief set_break_point_hook�֐��œo�^�����֐����擾����
*/
const AnyPtr& break_point_hook();

/**
* \xbind lib::builtin::debug
* \brief set_call_hook�֐��œo�^�����֐����擾����
*/
const AnyPtr& call_hook();

/**
* \xbind lib::builtin::debug
* \brief set_return_hook�֐��œo�^�����֐����擾����
*/
const AnyPtr& return_hook();

/**
* \xbind lib::builtin::debug
* \brief set_throw_hook�֐��œo�^�����֐����擾����
*/
const AnyPtr& throw_hook();

/**
* \xbind lib::builtin::debug
* \brief set_assert_hook�֐��œo�^�����֐����擾����
*/
const AnyPtr& assert_hook();

};

}

#endif // XTAL_DEBUG_H_INCLUDE_GUARD
