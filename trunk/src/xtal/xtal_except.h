/** \file src/xtal/xtal_except.h
* \brief src/xtal/xtal_except.h
*/

#ifndef XTAL_EXCEPT_H_INCLUDE_GUARD
#define XTAL_EXCEPT_H_INCLUDE_GUARD

#pragma once

namespace xtal{

/**
* \xbind lib::builtin
* \brief ��O
*/
class Exception : public Base{
public:

	Exception(const AnyPtr& message = empty_string);

	/**
	* \xbind
	* \brief ����������
	*/
	void initialize(const AnyPtr& message = empty_string);

	/**
	* \xbind
	* \brief �o�b�N�g���[�X��ǉ�����
	*/
	void append_backtrace(const AnyPtr& file, int_t line, const AnyPtr& function_name = empty_string);

	/**
	* \xbind
	* \brief �����񉻂���
	*/
	StringPtr to_s();

	/**
	* \xbind
	* \brief ���b�Z�[�W��Ԃ�
	*/
	StringPtr message(){
		return message_;
	}

	/**
	* \xbind
	* \brief �o�b�N�g���[�X�̏���v�f�Ƃ���Iterator��Ԃ�
	*/
	AnyPtr backtrace(){
		return backtrace_->each();
	}

	void on_visit_members(Visitor& m){
		Base::on_visit_members(m);
		m & message_ & backtrace_;
	}

private:
	StringPtr message_;
	ArrayPtr backtrace_;
};

class StandardError{};
class RuntimeError{};
class IOError{};
class EOSError{};
class LogicError{};
class CastError{};
class ArgumentError{};
class YieldError{};
class InstanceVariableError{};
class UnsupportedError{};
class RedefinedError{};
class AccessibilityError{};
class AssertionFailed{};
class CompileError{};

AnyPtr cast_error(const AnyPtr& from, const AnyPtr& to);
AnyPtr argument_error(const AnyPtr& object, int_t no, const ClassPtr& required, const ClassPtr& type);
AnyPtr unsupported_error(const AnyPtr& target, const IDPtr& primary_key, const AnyPtr& secondary_key);
AnyPtr filelocal_unsupported_error(const CodePtr& code, const IDPtr& primary_key);

/**
* \brief ��O��ݒ肷��
* \hideinitializer
*/
#define XTAL_SET_EXCEPT(e) ::xtal::vmachine()->set_except(e)

/**
* \brief ��O�����o����Ă���Ȃ���o��
* \hideinitializer
*/
#define XTAL_CATCH_EXCEPT(e) if(const ::xtal::ExceptionPtr& e = (XTAL_UNUSED_VAR(e), ::xtal::unchecked_ptr_cast< ::xtal::Exception>(::xtal::vmachine()->catch_except())))

/**
* \brief ��O�����o����Ă��邩���ׂ�
* XTAL_CATCH_EXCEPT�ƈႢ�A��O�͐ݒ肳�ꂽ�܂܁B
* \hideinitializer
*/
#define XTAL_CHECK_EXCEPT(e) if(const ::xtal::ExceptionPtr& e = (XTAL_UNUSED_VAR(e), ::xtal::unchecked_ptr_cast< ::xtal::Exception>(::xtal::vmachine()->except())))

}

#endif // XTAL_EXCEPT_H_INCLUDE_GUARD
