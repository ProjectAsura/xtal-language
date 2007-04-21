
#pragma once

#include "allocator.h"
#include "stack.h"
#include "string.h"

namespace xtal{

void InitPrototypes();

struct FrameCore{
	FrameCore()
		:kind(0),
		variable_symbol_offset(0), variable_size(0),
		instance_variable_symbol_offset(0), instance_variable_size(0),
		line_number(0){}
	u8 kind;
	u16 variable_symbol_offset;
	u16 variable_size;
	u16 instance_variable_symbol_offset;
	u16 instance_variable_size;
	u16 line_number;
};

struct FunCore : public FrameCore{
	FunCore()
		:pc(0), used_args_object(0), max_stack(256), min_param_count(0), max_param_count(0){}
	u16 pc;
	u16 max_stack;
	u8 min_param_count;
	u8 max_param_count;
	u8 used_args_object;
};

extern FrameCore empty_frame_core;
extern FunCore empty_fun_core;

// fwd decl
class CodeImpl;

/**
* @brief Xtal�̃o�C�g�R�[�h��\��
*/
class Code : public Any{
public:
		
	Code();

	Code(CodeImpl* p)
		:Any((AnyImpl*)p){}

	Code(const Null&)
		:Any(null){}

	/**
	* @brief �R�[�h�̐擪�|�C���^�𓾂�B
	*/
	const u8* data() const;
			
	/**
	* @brief �R�[�h�̃T�C�Y�𓾂�B
	*/
	int_t size() const;
		
	/**
	* @brief �V���{���e�[�u������i�Ԗڂ̃V���{�������o���B
	*/
	const ID& get_symbol(int_t i) const;
	
	/**
	* @brief �l�e�[�u������i�Ԗڂ̒l�����o���B
	*/
	const Any& get_value(int_t i) const;
	
	/**
	* @brief �l�e�[�u����i�Ԗڂɒl��ݒ肷��B
	*/
	void set_value(int_t i, const Any& v) const;

	/**
	* @brief �R�[�h�ɑΉ������\�[�X�s����Ԃ��B
	*/
	int_t compliant_line_number(const u8* p) const;

	FrameCore* get_frame_core(int_t i) const;

	FunCore* get_fun_core(int_t i) const;

	String source_file_name() const;

	const Class& toplevel() const;

	CodeImpl* impl() const{ return (CodeImpl*)Any::impl(); }
};
	
}
