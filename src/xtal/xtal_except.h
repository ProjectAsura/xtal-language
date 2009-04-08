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

	void initialize(const AnyPtr& message = empty_string);

	void append_backtrace(const AnyPtr& file, int_t line, const AnyPtr& function_name = empty_string);

	/**
	* \brief �����񉻂���
	*/
	StringPtr to_s();

	/**
	* \brief ���b�Z�[�W��Ԃ�
	*/
	StringPtr message(){
		return message_;
	}

	/**
	* \brief �o�b�N�g���[�X�̏���v�f�Ƃ���Iterator��Ԃ�
	*/
	AnyPtr backtrace(){
		return backtrace_->each();
	}

private:

	virtual void visit_members(Visitor& m){
		Base::visit_members(m);
		m & message_ & backtrace_;
	}

	StringPtr message_;
	ArrayPtr backtrace_;
};

class StandardError;
class RuntimeError;
class IOError;
class LogicError;
class CastError;
class ArgumentError;
class YieldError;
class InstanceVariableError;
class UnsupportedError;
class RedefinedError;
class AccessibilityError;
class AssertionFailed;
class CompileError;

AnyPtr cast_error(const AnyPtr& from, const AnyPtr& to);
AnyPtr argument_error(const AnyPtr& object, int_t no, const ClassPtr& required, const ClassPtr& type);
AnyPtr unsupported_error(const AnyPtr& target, const IDPtr& primary_key, const AnyPtr& secondary_key);

/**
* \brief ��O��ݒ肷��
* \hideinitializer
*/
#define XTAL_SET_EXCEPT(e) ::xtal::vmachine()->set_except(e)

/**
* \brief ��O�����o����Ă���Ȃ���o��
* \hideinitializer
*/
#define XTAL_CATCH_EXCEPT(e) if(const ::xtal::AnyPtr& e = ::xtal::unchecked_ptr_cast<::xtal::Exception>(::xtal::vmachine()->catch_except()))

/**
* \brief ��O�����o����Ă��邩���ׂ�
* \hideinitializer
*/
#define XTAL_CHECK_EXCEPT(e) if(const ::xtal::AnyPtr& e = ::xtal::unchecked_ptr_cast<::xtal::Exception>(::xtal::vmachine()->except()))

}

#endif // XTAL_EXCEPT_H_INCLUDE_GUARD
