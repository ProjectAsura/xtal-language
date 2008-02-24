
#pragma once

namespace xtal{

class Fun : public HaveName{
public:

	Fun(const FramePtr& outer, const AnyPtr& athis, const CodePtr& code, FunCore* core);

	const FramePtr& outer(){ return outer_; }
	const CodePtr& code(){ return code_; }
	int_t pc(){ return core_->pc; }
	const inst_t* source(){ return code_->data()+core_->pc; }
	const IDPtr& param_name_at(size_t i){ return code_->identifier(i+core_->variable_identifier_offset); }
	int_t param_size(){ return core_->variable_size; }	
	bool extendable_param(){ return (core_->flags&FunCore::FLAG_EXTENDABLE_PARAM)!=0; }
	FunCore* core(){ return core_; }
	void set_core(FunCore* fc){ core_ = fc; }
	void check_arg(const VMachinePtr& vm);
	virtual StringPtr object_name(int_t depth = -1);

public:
		
	virtual void call(const VMachinePtr& vm);
	
protected:

	FramePtr outer_;
	CodePtr code_;
	AnyPtr this_;
	FunCore* core_;
	
	virtual void visit_members(Visitor& m){
		HaveName::visit_members(m);
		m & outer_ & this_ & code_;
	}

};

// XTAL���z�}�V��
class VMachine : public GCObserver{
public:

	VMachine();

public:

	// �֐��Ăяo�������g�����߂̊֐��Q

	/**
	* @brief �֐����Ăяo���p�ӂ�����B
	*
	*/
	void setup_call(int_t need_result_count = 1);

	/**
	* @brief ������1�ςށB
	*
	*/
	void push_arg(const AnyPtr& value);
	
	/**
	* @brief ���O�t��������1�ςށB
	*
	*/
	void push_arg(const IDPtr& name, const AnyPtr& value);
	
	/**
	* @brief ���O�t��������1�ςށB
	*
	*/
	void push_arg(const Named& p){ push_arg(p.name, p.value); }

	/**
	* @brief ������1�ςށB
	*
	*/
	void push_arg(const Param& value);

	/**
	* @brief ������z��̗v�f���ςށB
	*
	*/
	void push_ordered_args(const ArrayPtr& p);

	/**
	* @brief ���O��������A�z�z��̗v�f���ςށB
	*
	*/
	void push_named_args(const MapPtr& p);

	/**
	* @brief pos�Ԗڂ̖߂�l�𓾂�B
	*
	*/
	const AnyPtr& result(int_t pos = 0);

	/**
	* @brief �Ăяo���̌�n��������B
	*
	*/
	void cleanup_call();	

	/**
	* @brief pos�Ԗڂ̖߂�l��Ԃ��A�Ăяo���̌�n��������B
	*
	*/
	AnyPtr result_and_cleanup_call(int_t pos = 0);
		
	/**
	* @brief this�������ւ���B
	*
	*/	
	void set_arg_this(const AnyPtr& self){ 
		ff().self(self);
	}

	/**
	* @brief �q���g�̐ݒ�
	*
	* ��O���N�����Ƃ��̃G���[���b�Z�[�W�̂��߂ɁA
	* ���݌Ăяo���Ă���֐���o�^����B
	*/
	void set_hint(const AnyPtr& object){ 
		ff().hint(object);
	}
	

// 

	/**
	* @brief �֐����Ăяo���p�ӂ����A�����Ɉ�����1�ς�
	*
	*/
	void setup_call(int_t need_result_count, const Param& a1);

	/**
	* @brief �֐����Ăяo���p�ӂ����A�����Ɉ�����2�ς�
	*
	*/
	void setup_call(int_t need_result_count, const Param& a1, const Param& a2);

	/**
	* @brief �֐����Ăяo���p�ӂ����A�����Ɉ�����3�ς�
	*
	*/
	void setup_call(int_t need_result_count, const Param& a1, const Param& a2, const Param& a3);

	/**
	* @brief �֐����Ăяo���p�ӂ����A�����Ɉ�����4�ς�
	*
	*/
	void setup_call(int_t need_result_count, const Param& a1, const Param& a2, const Param& a3, const Param& a4);

	/**
	* @brief �֐����Ăяo���p�ӂ����A�����Ɉ�����5�ς�
	*
	*/
	void setup_call(int_t need_result_count, const Param& a1, const Param& a2, const Param& a3, const Param& a4, const Param& a5);

public:

	// �֐��Ăяo���ꑤ���g�����߂̊֐��Q

	/**
	* @brief pos�Ԗڂ̈����𓾂�B
	*
	*/
	const AnyPtr& arg(int_t pos);

	/**
	* @brief name�ɑΉ���������𓾂�B
	*
	*/
	const AnyPtr& arg(const IDPtr& name);

	/**
	* @brief pos�Ԗڂ̈����𓾂�B����pos�Ԗڂ̈������Ȃ����name�ɑΉ���������𓾂�B
	*
	*/
	const AnyPtr& arg(int_t pos, const IDPtr& name);
	
	const AnyPtr& arg(int_t pos, Fun* names);

	/**
	* @brief pos�Ԗڂ̈����𓾂�B
	*
	* ����pos�Ԗڂ̈������������def�̒l��Ԃ��B
	*/
	const AnyPtr& arg_default(int_t pos, const AnyPtr& def);

	/**
	* @brief name�ɑΉ���������𓾂�B
	*
	* ����name�ɑΉ�����������������def�̒l��Ԃ��B
	*/
	const AnyPtr& arg_default(const IDPtr& name, const AnyPtr& def);

	/**
	* @brief pos�Ԗڂ̈����𓾂�B����pos�Ԗڂ̈������Ȃ����name�ɑΉ���������𓾂�B
	*
	* ����name�ɑΉ�����������������def�̒l��Ԃ��B
	*/
	const AnyPtr& arg_default(int_t pos, const IDPtr& name, const AnyPtr& def);
	
	/**
	* @brief pos�Ԗڂ̖��O�w������̖��O���擾�B
	*
	* @param pos 0〜named_arg_count()-1�܂�
	*/
	const IDPtr& arg_name(int_t pos){
		return static_ptr_cast<ID>(get(named_arg_count()*2-1-(pos*2+0)));
	}

	/**
	* @brief this���擾�B
	*
	*/
	const AnyPtr& get_arg_this(){ 
		return ff().self(); 
	}

	/**
	* @brief �ʒu�w������̐����擾�B
	*
	*/
	int_t ordered_arg_count(){ 
		return ff().ordered_arg_count; 
	}
	
	/**
	* @brief ���O�w������̐����擾
	*
	*/
	int_t named_arg_count(){ 
		return ff().named_arg_count; 
	}
	
	/**
	* @brief �����̐��𒲐�����B
	*
	*/
	void adjust_arg(int_t n);

	/**
	* @brief �����̑��l�𕽂�ɂ���
	*
	*/
	void flatten_arg();

	/**
	* @brief  �����̑��l�𕽂�ɂ���
	*
	*/
	void flatten_all_arg();
	
	/**
	* @brief �Ăяo�������K�v�Ƃ��Ă���߂�l�̐��B
	*
	*/
	int_t need_result_count(){ 
		return ff().need_result_count; 
	}
	
	/**
	* @brief �Ăяo�������߂�l��K�v�Ƃ��Ă��邩�ǂ����B
	*
	*/
	bool need_result(){ 
		return ff().need_result_count!=0; 
	}
	
	/*
	* Arguments�I�u�W�F�N�g�𐶐�����B
	* return_result()���Ă񂾌�͐���Ȓl�͓����Ȃ��B
	*/
	ArgumentsPtr make_arguments();
	
	/**
	* @brief �Ăяo�����Ɉ����̐������̖߂�l��Ԃ��B
	*
	* need_result_count�̕������������ꍇ�͂��̕�null���Ԃ����B
	* need_result_count�̕����������Ȃ��ꍇ�͕Ԃ����l�͎̂Ă���B
	*/
	void return_result();
	void return_result(const AnyPtr& value1);
	void return_result(const AnyPtr& value1, const AnyPtr& value2);
	void return_result(const AnyPtr& value1, const AnyPtr& value2, const AnyPtr& value3);
	void return_result(const AnyPtr& value1, const AnyPtr& value2, const AnyPtr& value3, const AnyPtr& value4);
	void return_result_array(const ArrayPtr& values);

	/**
	* @brief return_result��carry_over�����ɌĂяo�����Ȃ�true���A�����łȂ��Ȃ�false��Ԃ��B
	*
	*/
	bool processed(){ 
		return *ff().called_pc!=InstThrowUnsupportedError::NUMBER; 
	}
	
	void replace_result(int_t pos, const AnyPtr& v);

	void recycle_call();

	void recycle_call(const AnyPtr& a1);

public:

	const AnyPtr& catch_except(){
		except_[2] = except();
		except_[0] = null;
		except_[1] = null;
		return ap(except_[2]);
	}

	const AnyPtr& except(){
		if(ap(except_[0])) return ap(except_[0]);
		return ap(except_[1]);
	}

	void set_except(const AnyPtr& e){
		except_[0] = e;
		except_[1] = null;
	}

	void set_except_0(const Innocence& e);

	void execute_inner(const inst_t* start);

	void execute(Fun* fun, const inst_t* start_pc);

	void carry_over(Fun* fun);

	void mv_carry_over(Fun* fun);

	const inst_t* resume_pc(){
		return resume_pc_;
	}

	void present_for_vm(Fiber* fun, VMachine* vm, bool add_succ_or_fail_result);

	const inst_t* start_fiber(Fiber* fun, VMachine* vm, bool add_succ_or_fail_result);

	const inst_t* resume_fiber(Fiber* fun, const inst_t* pc, VMachine* vm, bool add_succ_or_fail_result);
	
	void exit_fiber();
	
	void reset();

public:

	void adjust_result(int_t n){		
		adjust_result(n, ff().need_result_count);
	}

	void adjust_result(int_t n, int_t need_result_count);

public:

	// �X�^�b�N��i�Ԗڂ̒l���擾����B
	const AnyPtr& get(int_t i){ return ap(stack_[i]); }

	// �X�^�b�N��0�Ԗڂ̒l���擾����B
	const AnyPtr& get(){ return ap(stack_.top()); }

	// �X�^�b�N��i�Ԗڂ̒l��ݒ肷��B
	void set(int_t i, const Innocence& v){ stack_[i]=v; }

	// �X�^�b�N��0�Ԗڂ̒l��ݒ肷��B
	void set(const Innocence& v){ stack_.top()=v; }

	// �X�^�b�N��n�g�傷��B
	void upsize(int_t n){ stack_.upsize_unchecked(n); }

	// �X�^�b�N��n�k������
	void downsize(int_t n){ stack_.downsize(n); }

	// �X�^�b�N��n�ɂ���B
	void resize(int_t n){ stack_.resize(n); }

	// �X�^�b�N�ɒlv���v�b�V������B
	void push(const Innocence& v){ stack_.push_unchecked(v); }

	// �X�^�b�N�ɒlv���v�b�V������B
	void push(const Named& v){ push(v.name); push(v.value); }

	// �X�^�b�N����l���|�b�v����B
	const AnyPtr& pop(){ return ap(stack_.pop()); }

	// �擪�̒l���v�b�V������B
	void dup(){ push(get()); }

	// i�Ԗڂ̒l���v�b�V������B
	void dup(int_t i){ push(get(i)); }

	// �X�^�b�N�̑傫����Ԃ��B
	int_t stack_size(){ return (int_t)stack_.size(); }
	
	// src�̃X�^�b�N�̓��e��size�v�b�V������B
	void push(VMachine* src, int_t size){ stack_.push(src->stack_, size); }
	
	// src�̃X�^�b�N�̓��e��size�v�b�V������B
	void push(VMachine* src, int_t src_offset, int_t size){ stack_.push(src->stack_, src_offset, size); }

	// src�̃X�^�b�N�̓��e��size��菜���āA�v�b�V������B
	void move(VMachine* src, int_t size){ stack_.move(src->stack_, size); }
	
public:

	const VMachinePtr& inner_setup_call(const inst_t* pc, int_t need_result_count);
	const VMachinePtr& inner_setup_call(const inst_t* pc, int_t need_result_count, const AnyPtr& a1);
	const VMachinePtr& inner_setup_call(const inst_t* pc, int_t need_result_count, const AnyPtr& a1, const AnyPtr& a2);

	struct FunFrame{

		// pop_ff�����Ƃ��͂���pc������s����
		const inst_t* poped_pc;

		// call�����Ƃ��͂���pc������s����
		const inst_t* called_pc;

		// �֐����Ă΂ꂽ�Ƃ��̏��Ԏw������̐�
		int_t ordered_arg_count;
		
		// �֐����Ă΂ꂽ�Ƃ��̖��O�w������̐�
		int_t named_arg_count;

		// �֐��Ăяo�������K�v�Ƃ���߂�l�̐�
		int_t need_result_count;

		// yield���\���t���O�B���̃t���O�͌Ăяo�����ׂ��œ`�d����B
		int_t yieldable;

		// this�����C���X�^���X�ϐ��ւ̃|�C���^
		InstanceVariables* instance_variables;

		// �X�R�[�v���I�u�W�F�N�g������ĂȂ����̃��[�J���ϐ��̈�
		Stack<Innocence> variables_;

		// �Ăяo���ꂽ�֐��I�u�W�F�N�g
		Innocence fun_; 

		// �ꎞ�I�Ɋ֐��I�u�W�F�N�g�����V�[�o�I�u�W�F�N�g��u�����߂̏ꏊ
		Innocence temp1_;

		// �ꎞ�I�ɉ�����u�����߂̏ꏊ
		Innocence temp2_;

		// �ꎞ�I�ɉ�����u�����߂̏ꏊ
		Innocence temp3_;

		// �X�R�[�v�̊O���̃t���[���I�u�W�F�N�g
		Innocence outer_;

		// �֐����Ă΂ꂽ�Ƃ���this�I�u�W�F�N�g
		Innocence self_;

		// �I�u�W�F�N�g�����������B
		Innocence arguments_;
		
		// �f�o�b�O���b�Z�[�W�o�͗p�̃q���g
		Innocence hint_;

		void set_null(){
			set_null_force(fun_); 
			set_null_force(temp1_);
			set_null_force(temp2_);
			set_null_force(temp3_);
			set_null_force(outer_);
			set_null_force(arguments_);
			set_null_force(hint_);
		}

		const FunPtr& fun() const{ return static_ptr_cast<Fun>(ap(fun_)); }
		const FramePtr& outer() const{ return static_ptr_cast<Frame>(ap(outer_)); }
		const AnyPtr& variable(int_t i) const{ return ap(variables_[i]); }
		const AnyPtr& self() const{ return ap(self_); }
		const ArgumentsPtr& arguments() const{ return static_ptr_cast<Arguments>(ap(arguments_)); }
		const AnyPtr& hint() const{ return ap(hint_); }

		int_t args_stack_size(){
			return ordered_arg_count+(named_arg_count<<1);
		}

		void fun(const Innocence& v){ fun_ = v; }
		void outer(const Innocence& v){ outer_ = v; }
		void variable(int_t i, const Innocence& v){ variables_[i] = v; }
		void self(const Innocence& v){ self_ = v; }
		void arguments(const Innocence& v){ arguments_ = v; }
		void hint(const Innocence& v){ hint_ = v; }

		void inc_ref();
		void dec_ref();
	};

	friend void visit_members(Visitor& m, const FunFrame& v);

	// ��O���������邽�߂̃t���[��
	struct ExceptFrame{
		ExceptCore* core;
		int_t stack_count;
		int_t fun_frame_count;
		int_t variable_size;
		Innocence outer;
	};

	const AnyPtr& pop_and_save1(){ return ap(ff().temp1_ = pop()); }
	const AnyPtr& pop_and_save2(){ return ap(ff().temp2_ = pop()); }


	void push_ff(const inst_t* pc, int_t need_result_count, int_t ordered_arg_count, int_t named_arg_count, const AnyPtr& self);
	void push_ff(const inst_t* pc, const InstCall& inst, const AnyPtr& self);
	void recycle_ff(const inst_t* pc, int_t ordered_arg_count, int_t named_arg_count, const AnyPtr& self);
	const inst_t* pop_ff(){ return fun_frames_.pop().poped_pc; }

	void push_args(const ArgumentsPtr& args, int_t named_arg_count);

	FunFrame& ff(){ return fun_frames_.top(); }
	FunFrame& prev_ff(){ return fun_frames_[1]; }

	const FunPtr& fun(){ return ff().fun(); }
	const FunPtr& prev_fun(){ return prev_ff().fun(); }

	const FramePtr& outer(){ return ff().outer(); }
	const FramePtr& prev_outer(){ return prev_ff().outer(); }

	const CodePtr& code(){ return fun()->code(); }
	const CodePtr& prev_code(){ return prev_fun()->code(); }

	const IDPtr& identifier(int_t n){ return code()->identifier(n); }
	const IDPtr& prev_identifier(int_t n){ return prev_code()->identifier(n); }
	const IDPtr& identifier_ex(int_t n){ 
		if(n!=0){ return  static_ptr_cast<ID>(ap(ff().temp3_ = identifier(n)));  }
		else{ return static_ptr_cast<ID>(ap(ff().temp3_ = pop()->to_s()->intern())); }
	}

	void return_result_instance_variable(int_t number, ClassCore* core);

	ArgumentsPtr make_args(Fun* fun);

	AnyPtr append_backtrace(const inst_t* pc, const AnyPtr& ep);
	
	const VMachinePtr& myself(){ return *(const VMachinePtr*)&myself_; }

private:

	const inst_t* send1(const inst_t* pc, const IDPtr& name);
	const inst_t* send2(const inst_t* pc, const IDPtr& name);
	const inst_t* send2_r(const inst_t* pc, const IDPtr& name);
	const inst_t* send2_q(const inst_t* pc, const IDPtr& name);

	void set_local_variable(int_t pos, const Innocence&);
	const AnyPtr& local_variable(int_t pos);

	const inst_t* catch_body(const inst_t* pc, int_t stack_size, int_t fun_frames_size);

	void debug_hook(const inst_t* pc, int_t kind);

public:

//{DECLS{{
	const inst_t* FunUndefined(const inst_t* pc);
	const inst_t* FunPushNull(const inst_t* pc);
	const inst_t* FunPushUndefined(const inst_t* pc);
	const inst_t* FunPushTrue(const inst_t* pc);
	const inst_t* FunPushFalse(const inst_t* pc);
	const inst_t* FunPushInt1Byte(const inst_t* pc);
	const inst_t* FunPushInt2Byte(const inst_t* pc);
	const inst_t* FunPushFloat1Byte(const inst_t* pc);
	const inst_t* FunPushFloat2Byte(const inst_t* pc);
	const inst_t* FunPushCallee(const inst_t* pc);
	const inst_t* FunPushArgs(const inst_t* pc);
	const inst_t* FunPushThis(const inst_t* pc);
	const inst_t* FunPushCurrentContext(const inst_t* pc);
	const inst_t* FunPop(const inst_t* pc);
	const inst_t* FunDup(const inst_t* pc);
	const inst_t* FunInsert1(const inst_t* pc);
	const inst_t* FunInsert2(const inst_t* pc);
	const inst_t* FunInsert3(const inst_t* pc);
	const inst_t* FunAdjustResult(const inst_t* pc);
	const inst_t* FunIf(const inst_t* pc);
	const inst_t* FunUnless(const inst_t* pc);
	const inst_t* FunGoto(const inst_t* pc);
	const inst_t* FunLocalVariableInc(const inst_t* pc);
	const inst_t* FunLocalVariableIncDirect(const inst_t* pc);
	const inst_t* FunLocalVariableDec(const inst_t* pc);
	const inst_t* FunLocalVariableDecDirect(const inst_t* pc);
	const inst_t* FunLocalVariableInc2Byte(const inst_t* pc);
	const inst_t* FunLocalVariableDec2Byte(const inst_t* pc);
	const inst_t* FunLocalVariable1Byte(const inst_t* pc);
	const inst_t* FunLocalVariable1ByteDirect(const inst_t* pc);
	const inst_t* FunLocalVariable2Byte(const inst_t* pc);
	const inst_t* FunSetLocalVariable1Byte(const inst_t* pc);
	const inst_t* FunSetLocalVariable1ByteDirect(const inst_t* pc);
	const inst_t* FunSetLocalVariable2Byte(const inst_t* pc);
	const inst_t* FunInstanceVariable(const inst_t* pc);
	const inst_t* FunSetInstanceVariable(const inst_t* pc);
	const inst_t* FunCleanupCall(const inst_t* pc);
	const inst_t* FunReturn(const inst_t* pc);
	const inst_t* FunYield(const inst_t* pc);
	const inst_t* FunExit(const inst_t* pc);
	const inst_t* FunValue(const inst_t* pc);
	const inst_t* FunCheckUnsupported(const inst_t* pc);
	const inst_t* FunProperty(const inst_t* pc);
	const inst_t* FunPropertyNS(const inst_t* pc);
	const inst_t* FunSetProperty(const inst_t* pc);
	const inst_t* FunSetPropertyNS(const inst_t* pc);
	const inst_t* FunCall(const inst_t* pc);
	const inst_t* FunSend(const inst_t* pc);
	const inst_t* FunSendNS(const inst_t* pc);
	const inst_t* FunSendQ(const inst_t* pc);
	const inst_t* FunSendQNS(const inst_t* pc);
	const inst_t* FunMember(const inst_t* pc);
	const inst_t* FunMemberNS(const inst_t* pc);
	const inst_t* FunMemberQ(const inst_t* pc);
	const inst_t* FunMemberQNS(const inst_t* pc);
	const inst_t* FunDefineMember(const inst_t* pc);
	const inst_t* FunDefineMemberNS(const inst_t* pc);
	const inst_t* FunGlobalVariable(const inst_t* pc);
	const inst_t* FunSetGlobalVariable(const inst_t* pc);
	const inst_t* FunDefineGlobalVariable(const inst_t* pc);
	const inst_t* FunOnce(const inst_t* pc);
	const inst_t* FunSetOnce(const inst_t* pc);
	const inst_t* FunBlockBegin(const inst_t* pc);
	const inst_t* FunBlockBeginDirect(const inst_t* pc);
	const inst_t* FunBlockEnd(const inst_t* pc);
	const inst_t* FunBlockEndDirect(const inst_t* pc);
	const inst_t* FunTryBegin(const inst_t* pc);
	const inst_t* FunTryEnd(const inst_t* pc);
	const inst_t* FunPushGoto(const inst_t* pc);
	const inst_t* FunPopGoto(const inst_t* pc);
	const inst_t* FunIfEq(const inst_t* pc);
	const inst_t* FunIfNe(const inst_t* pc);
	const inst_t* FunIfLt(const inst_t* pc);
	const inst_t* FunIfLe(const inst_t* pc);
	const inst_t* FunIfGt(const inst_t* pc);
	const inst_t* FunIfGe(const inst_t* pc);
	const inst_t* FunIfRawEq(const inst_t* pc);
	const inst_t* FunIfRawNe(const inst_t* pc);
	const inst_t* FunIfIn(const inst_t* pc);
	const inst_t* FunIfNin(const inst_t* pc);
	const inst_t* FunIfIs(const inst_t* pc);
	const inst_t* FunIfNis(const inst_t* pc);
	const inst_t* FunIfArgIsUndefined(const inst_t* pc);
	const inst_t* FunIfArgIsUndefinedDirect(const inst_t* pc);
	const inst_t* FunPos(const inst_t* pc);
	const inst_t* FunNeg(const inst_t* pc);
	const inst_t* FunCom(const inst_t* pc);
	const inst_t* FunNot(const inst_t* pc);
	const inst_t* FunAt(const inst_t* pc);
	const inst_t* FunSetAt(const inst_t* pc);
	const inst_t* FunAdd(const inst_t* pc);
	const inst_t* FunSub(const inst_t* pc);
	const inst_t* FunCat(const inst_t* pc);
	const inst_t* FunMul(const inst_t* pc);
	const inst_t* FunDiv(const inst_t* pc);
	const inst_t* FunMod(const inst_t* pc);
	const inst_t* FunAnd(const inst_t* pc);
	const inst_t* FunOr(const inst_t* pc);
	const inst_t* FunXor(const inst_t* pc);
	const inst_t* FunShl(const inst_t* pc);
	const inst_t* FunShr(const inst_t* pc);
	const inst_t* FunUshr(const inst_t* pc);
	const inst_t* FunEq(const inst_t* pc);
	const inst_t* FunNe(const inst_t* pc);
	const inst_t* FunLt(const inst_t* pc);
	const inst_t* FunLe(const inst_t* pc);
	const inst_t* FunGt(const inst_t* pc);
	const inst_t* FunGe(const inst_t* pc);
	const inst_t* FunRawEq(const inst_t* pc);
	const inst_t* FunRawNe(const inst_t* pc);
	const inst_t* FunIn(const inst_t* pc);
	const inst_t* FunNin(const inst_t* pc);
	const inst_t* FunIs(const inst_t* pc);
	const inst_t* FunNis(const inst_t* pc);
	const inst_t* FunInc(const inst_t* pc);
	const inst_t* FunDec(const inst_t* pc);
	const inst_t* FunAddAssign(const inst_t* pc);
	const inst_t* FunSubAssign(const inst_t* pc);
	const inst_t* FunCatAssign(const inst_t* pc);
	const inst_t* FunMulAssign(const inst_t* pc);
	const inst_t* FunDivAssign(const inst_t* pc);
	const inst_t* FunModAssign(const inst_t* pc);
	const inst_t* FunAndAssign(const inst_t* pc);
	const inst_t* FunOrAssign(const inst_t* pc);
	const inst_t* FunXorAssign(const inst_t* pc);
	const inst_t* FunShlAssign(const inst_t* pc);
	const inst_t* FunShrAssign(const inst_t* pc);
	const inst_t* FunUshrAssign(const inst_t* pc);
	const inst_t* FunRange(const inst_t* pc);
	const inst_t* FunClassBegin(const inst_t* pc);
	const inst_t* FunClassEnd(const inst_t* pc);
	const inst_t* FunDefineClassMember(const inst_t* pc);
	const inst_t* FunMakeArray(const inst_t* pc);
	const inst_t* FunArrayAppend(const inst_t* pc);
	const inst_t* FunMakeMap(const inst_t* pc);
	const inst_t* FunMapInsert(const inst_t* pc);
	const inst_t* FunMapSetDefault(const inst_t* pc);
	const inst_t* FunMakeFun(const inst_t* pc);
	const inst_t* FunMakeInstanceVariableAccessor(const inst_t* pc);
	const inst_t* FunThrow(const inst_t* pc);
	const inst_t* FunThrowUnsupportedError(const inst_t* pc);
	const inst_t* FunThrowUndefined(const inst_t* pc);
	const inst_t* FunAssert(const inst_t* pc);
	const inst_t* FunBreakPoint(const inst_t* pc);
	const inst_t* FunMAX(const inst_t* pc);
//}}DECLS}

private:

	VMachine(const VMachine&);
	VMachine& operator=(const VMachine&);

private:

	inst_t end_code_;
	inst_t throw_unsupported_error_code_;
	inst_t check_unsupported_code_;
	inst_t cleanup_call_code_;
	inst_t throw_undefined_code_;

	const inst_t* resume_pc_;
	int_t yield_result_count_;

	Innocence myself_;

	// �v�Z�p�X�^�b�N
	Stack<Innocence> stack_;

	// �֐��Ăяo���̓x�ɐς܂��t���[��
	Stack<FunFrame> fun_frames_;

	// try�̓x�ɐς܂��t���[���B
	PODStack<ExceptFrame> except_frames_;
	
	SmartPtr<debug::Info> debug_info_;

	Innocence except_[3];

	int_t debug_;

protected:

	virtual void visit_members(Visitor& m);

	virtual void before_gc();
	virtual void after_gc();

public:

	void print_info();

};

}
