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

/**
* \brief �f�o�b�O�t�b�N�֐��œn�����I�u�W�F�N�g
*/
class HookInfo : public Base{
public:
	
	/**
	* \brief �t�b�N�̎�ނ�Ԃ�
	*/
	int_t kind(){ return kind_; } 

	/**
	* \brief �t�b�N���ꂽ�ꏊ�̍s����Ԃ�
	*/
	int_t line(){ return line_; }

	/**
	* \brief �t�b�N���ꂽ�ꏊ�̃t�@�C������Ԃ�
	*/
	const StringPtr& file_name(){ return file_name_; }

	/**
	* \brief �t�b�N���ꂽ�ꏊ�̃t�@�C������Ԃ�
	*/
	const StringPtr& fun_name(){ return fun_name_; }

	/**
	* \brief assertion�̃��b�Z�[�W��Ԃ�
	*/
	const StringPtr& assertion_message(){ return assertion_message_; }

	/**
	* \brief ��O�I�u�W�F�N�g��Ԃ�
	*/
	const AnyPtr& exception(){ return exception_; }

	/**
	* \brief �t�b�N���ꂽ�ꏊ�̕ϐ��t���[���I�u�W�F�N�g��Ԃ�
	*/
	const FramePtr& variables_frame(){ return variables_frame_; }

	void set_kind(int_t v){ kind_ = v; }
	void set_line(int_t v){ line_ = v; }
	void set_file_name(const StringPtr& v){ file_name_ = v; }
	void set_fun_name(const StringPtr& v){ fun_name_ = v; }
	void set_assertion_message(const StringPtr& v){ assertion_message_ = v; }
	void set_exception(const AnyPtr& e){ exception_ = e; }
	void set_variables_frame(const FramePtr& v){ variables_frame_ = v; }

	/**
	* \brief �N���[�������
	* DebugInfo�I�u�W�F�N�g�͎g���܂킳��邽�߁A����ێ��������ꍇ�A�N���[�������K�v������B
	*/
	SmartPtr<HookInfo> clone(){
		return xnew<HookInfo>(*this);
	}

private:

	virtual void visit_members(Visitor& m);

	int_t kind_;
	int_t line_;
	StringPtr file_name_;
	StringPtr fun_name_;
	StringPtr assertion_message_;
	AnyPtr exception_;
	FramePtr variables_frame_;
	VMachinePtr vm_;
};

typedef SmartPtr<HookInfo> HookInfoPtr;

class Debug;

/**
* \xbind
* \brief �f�o�b�O�@�\��L���ɂ���
* �f�o�b�O�@�\�̓f�t�H���g�ł͖����ɂȂ��Ă���B
*/
void enable();

/**
* \xbind
* \brief �f�o�b�O�@�\�𖳌��ɂ���
*/
void disable();

/**
* \xbind
* \brief �f�o�b�O�@�\�������I�ɗL���ɂ���
* �f�o�b�O�@�\�̓f�t�H���g�ł͖����ɂȂ��Ă���B
*/
void enable_force(int_t count);

/**
* \xbind
* \brief �f�o�b�O�@�\�������I�ɖ����ɂ���
*/
int_t disable_force();

/**
* \xbind
* \brief �f�o�b�O�@�\���L�����ǂ���
*/
bool is_enabled();

uint_t hook_setting_bit();

/**
* \xbind
* \brief �u���[�N�|�C���g������x�ɌĂяo�����t�b�N�֐���o�^����
* \param hook �o�^����t�b�N�֐�
*/
void set_break_point_hook(const AnyPtr& hook);

/**
* \xbind
* \brief �֐��Ăяo�������x�ɌĂяo�����t�b�N�֐���o�^����
* \param hook �o�^����t�b�N�֐�
*/
void set_call_hook(const AnyPtr& hook);

/**
* \xbind
* \brief �֐�����return�����x�ɌĂяo�����t�b�N�֐���o�^����
* \param hook �o�^����t�b�N�֐�
*/
void set_return_hook(const AnyPtr& hook);

/**
* \xbind
* \brief ��O��throw�����x�ɌĂяo�����t�b�N�֐���o�^����
* \param hook �o�^����t�b�N�֐�
*/
void set_throw_hook(const AnyPtr& hook);

/**
* \xbind
* \brief �A�T�[�g�����s�����x�ɌĂяo�����t�b�N�֐���o�^����
* \param hook �o�^����t�b�N�֐�
*/
void set_assert_hook(const AnyPtr& hook);

/**
* \xbind
* \brief set_break_point_hook�֐��œo�^�����֐����擾����
*/
const AnyPtr& break_point_hook();

/**
* \xbind
* \brief set_call_hook�֐��œo�^�����֐����擾����
*/
const AnyPtr& call_hook();

/**
* \xbind
* \brief set_return_hook�֐��œo�^�����֐����擾����
*/
const AnyPtr& return_hook();

/**
* \xbind
* \brief set_throw_hook�֐��œo�^�����֐����擾����
*/
const AnyPtr& throw_hook();

/**
* \xbind
* \brief set_assert_hook�֐��œo�^�����֐����擾����
*/
const AnyPtr& assert_hook();

};

}

#endif // XTAL_DEBUG_H_INCLUDE_GUARD
