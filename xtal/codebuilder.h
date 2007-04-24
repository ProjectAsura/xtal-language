

#pragma once

#include "expr.h"
#include "parser.h"

namespace xtal{

class CodeBuilder{
public:

	CodeBuilder();
	
	~CodeBuilder();
	
	Fun compile(const Stream& stream, const String& source_file_name = "anonymous");

	void adjust_result(int_t required_result_count, int_t result_count);

	void compile(Expr* p, int_t required_result_count=1);
	
	void compile(Stmt* p);	
	
	/**
	* �R���p�C���G���[���擾����B
	*/
	Array errors();
		
	/**
	* ���ʎq���ϐ��Ƃ��Ă��邩�T���A�ϐ��ʒu��Ԃ��B
	* @param key ���ʎq
	* @retval -1 �o�^����Ă��Ȃ�
	* @retval ��-1 �ϐ��ʒu
	*/
	int_t lookup_variable(int_t key);

	bool variable_on_heap(int_t n);
	
	/**
	* ���x���ԍ���\�񂵁A�Ԃ��B
	*/
	int_t reserve_label();
	
	/**
	* ���x����ݒ肷��B
	*/
	void set_label(int_t lableno);

	/**
	* ���x���ɃW�����v����R�[�h�𖄂ߍ��߂�悤�ɍ׍H����B
	*/	
	void put_jump_code_nocode(int_t oppos, int_t labelno);

	void put_jump_code(int_t code, int_t labelno);

	void process_labels();

	bool put_local_code(int_t var);
	
	bool put_set_local_code(int_t var);
	
	void put_send_code(int_t var, int_t required_result_count, int_t result_flag, bool tail, bool if_defined);

	void put_set_send_code(int_t var, bool if_defined);

	void put_member_code(int_t var, bool if_defined);

	void put_define_member_code(int_t var);

	/**
	* ���ʎq���ϐ��Ƃ��Ă��邩�T���A�ϐ��ʒu��Ԃ��B
	* @param key ���ʎq
	* @retval -1 �o�^����Ă��Ȃ�
	* @retval ��-1 �ϐ��ʒu
	*/
	int_t lookup_instance_variable(int_t key);

	void put_set_instance_variable_code(int_t var);

	void put_instance_variable_code(int_t var);

	void put_if_code(Expr* cond, int_t label_if, int_t label_if2);
			
	void push_loop(int break_labelno, int continue_labelno, int_t name = 0, bool have_label = false);
	
	void pop_loop();
	
	/**
	* �u���b�N�̏I��𖄂ߍ���
	*/
	void break_off(int_t to, int_t block_end = 0, int_t j = 0);
		
	/**
	* �����ɃR�[�h����ǉ�����B
	*/
	void put_code_u8(int_t val);
	void put_code_u16(int_t val);
	void put_code_s8(int_t val);
	void put_code_s16(int_t val);

	/**
	* i�Ԗڂ̕����̒l������������B
	*/
	void set_code_u8(int_t i, int_t val);
	void set_code_u16(int_t i, int_t val);
	void set_code_s8(int_t i, int_t val);
	void set_code_s16(int_t i, int_t val);
	
	/**
	* �R�[�h�̃T�C�Y�𓾂�B
	*/
	int_t code_size();
		
	ID to_id(int_t i);

	void assign_lhs(Expr* lhs);
	void define_lhs(Expr* lhs);
		
	struct Scope{
		int_t variable_size;
		int_t type;
		int_t kind;
		bool on_heap;
		int_t mixins;
		int_t frame_core_num;
	};
	
	struct FunFrame{

		int_t frame_count;

		struct Label{
			int pos;
			struct From{
				int line;
				int pos;
				int set_pos;
			};
			AC<From>::vector froms;
		};
		
		AC<Label>::vector labels;
		
		struct Loop{
			int_t name; ///< ���x����
			int frame_count; ///< �t���[���̐�
			int break_label; ///< break_label�̔ԍ�
			int continue_label; ///< continue_label�̔ԍ�
			bool have_label; /// �Ή����郉�x���������Ă��邩
		};
		
		PODStack<Loop> loops;

		struct Finally{
			int frame_count;
			int finally_label;
		};

		PODStack<Finally> finallys;

		bool used_args_object;
	};

	enum {
		SCOPE, BLOCK, FRAME, FUN
	};

	void block_begin(int_t type, int_t kind, TList<int_t>& vars, bool on_heap, int_t mixins = 0);

	void block_end();

	int_t fun_frame_begin(bool have_args, int_t offset, unsigned char min_param_count, unsigned char max_param_count);

	void register_param(int_t name);

	void fun_frame_end();

	FunFrame& fun_frame();

	struct ClassFrame{
		int_t n;
		AC<int_t>::vector inst_vars;
	};
	
	int_t line(){ return lines_.top(); }

private:
	
	Parser parser_;
	LPCCommon com_;
	
	PODStack<int_t> variables_;
	PODStack<int_t> label_names_;
	Stack<FunFrame> fun_frames_;
	Code result_;
	CodeImpl* p_;
	PODStack<Scope> scopes_;
	PODStack<int_t> lines_;
	Stack<ClassFrame> class_scopes_;
};

}
