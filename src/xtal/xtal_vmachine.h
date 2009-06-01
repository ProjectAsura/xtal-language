/** \file src/xtal/xtal_vmachine.h
* \brief src/xtal/xtal_vmachine.h
*/

#ifndef XTAL_VMACHINE_H_INCLUDE_GUARD
#define XTAL_VMACHINE_H_INCLUDE_GUARD

#pragma once

namespace xtal{
	
/**
* \brief �֐��Ăяo���ŁA���O�t�������Ƃ��ēn�����߂̃N���X
*
*/
struct Named{
	const IDPtr& name;
	const Any& value;

	/**
	* \brief ���O�ƒl���w�肵�č\�z����B
	*/
	Named(const IDPtr& name, const Any& value)
		:name(name), value(value){}

	/**
	* \brief ��ȏ�ԂŐ�������
	*/
	Named()
		:name((const IDPtr&)null), value(undefined){}
};

struct NamedParam{
	NamedParam()
		:name(null), value(undefined){}
	IDPtr name;
	AnyPtr value;
};

struct Param{
	enum{
		SHIFT = 16,

		NAMED = (1<<SHIFT),
		STR = (2<<SHIFT),
		STR8 = (3<<SHIFT)
	};

	Param(const Named& n){
		type = NAMED;
		name.name = &n.name;
		name.value = &n.value;
	}

	Param(const char_t* s){
		type = STR;
		str = s;
	}

	Param(const char8_t* s){
		type = STR8;
		str8 = s;
	}

	Param(const AnyPtr& v){
		type = xtal::type(v);
		value = rawvalue(v);
	}

	Param(char v){ type = TYPE_INT; value.ivalue = (int_t)v; }
	Param(signed char v){ type = TYPE_INT; value.ivalue = (int_t)v; }
	Param(unsigned char v){ type = TYPE_INT; value.ivalue = (int_t)v; }
	Param(short v){ type = TYPE_INT; value.ivalue = (int_t)v; }
	Param(unsigned short v){ type = TYPE_INT; value.ivalue = (int_t)v; }
	Param(int v){ type = TYPE_INT; value.ivalue = (int_t)v; }
	Param(unsigned int v){ type = TYPE_INT; value.ivalue = (int_t)v; }
	Param(long v){ type = TYPE_INT; value.ivalue = (int_t)v; }
	Param(unsigned long v){ type = TYPE_INT; value.ivalue = (int_t)v; }

	Param(float v){ type = TYPE_FLOAT; value.fvalue = (float_t)v; }
	Param(double v){ type = TYPE_FLOAT; value.fvalue = (float_t)v; }
	Param(long double v){ type = TYPE_FLOAT; value.fvalue = (float_t)v; }

	Param(bool b){ type = TYPE_FALSE + (int)b; value.ivalue = 0; }

	int_t type;

	struct NamedPair{
		const IDPtr* name;
		const Any* value;		
	};

	union{
		const char_t* str;
		const char8_t* str8;
		NamedPair name;
		AnyRawValue value;
	};
};

struct f2{
	float_t a, b;
};

inline void to_f2(f2& ret, int_t atype, const AnyPtr& a, int_t btype, const AnyPtr& b){
	float_t aa[2] = {(float_t)ivalue(a), fvalue(a)};
	float_t bb[2] = {(float_t)ivalue(b), fvalue(b)};
	ret.a = aa[atype];
	ret.b = bb[btype];
}

// XTAL���z�}�V��
class VMachine : public GCObserver{
public:

	VMachine();

	~VMachine();

public:

	// �֐��Ăяo�������g�����߂̊֐��Q

	/**
	* \brief ������1�ςށB
	*
	*/
	void push_arg(const AnyPtr& value);
	
	/**
	* \brief ���O�t��������1�ςށB
	*
	*/
	void push_arg(const IDPtr& name, const AnyPtr& value);
	
	/**
	* \brief ���O�t��������1�ςށB
	*
	*/
	void push_arg(const Named& p){ push_arg(p.name, ap(p.value)); }

	/**
	* \brief ������1�ςށB
	*
	*/
	void push_arg(const Param& p);

	/**
	* \brief ������z��̗v�f���ςށB
	*
	*/
	void push_ordered_args(const ArrayPtr& p);

	/**
	* \brief ���O��������A�z�z��̗v�f���ςށB
	*
	*/
	void push_named_args(const MapPtr& p);

	/**
	* \brief pos�Ԗڂ̖߂�l�𓾂�B
	*
	*/
	const AnyPtr& result(int_t pos = 0);

	/**
	* \brief �Ăяo���̌�n��������B
	*
	*/
	void cleanup_call();	

	/**
	* \brief pos�Ԗڂ̖߂�l��Ԃ��A�Ăяo���̌�n��������B
	*
	*/
	AnyPtr result_and_cleanup_call(int_t pos = 0);
		
	/**
	* \brief this�������ւ���B
	*
	*/	
	void set_arg_this(const AnyPtr& self){ 
		ff().self(self);
	}

// 

	/// \brief �֐����Ăяo���p�ӂ����A�����Ɉ�����`i`�ς�
	void setup_call(int_t need_result_count = 1){
		push_ff();
		set_ff(&end_code_, &throw_unsupported_error_code_, need_result_count, 0, 0, undefined);	
	}

//{REPEAT{{
/*
	/// \brief �֐����Ăяo���p�ӂ����A�����Ɉ�����`n+1`�ς�
	void setup_call(int_t need_result_count, const Param& a0 #COMMA_REPEAT#const Param& a`i+1`#);
*/

	/// \brief �֐����Ăяo���p�ӂ����A�����Ɉ�����1�ς�
	void setup_call(int_t need_result_count, const Param& a0 );

	/// \brief �֐����Ăяo���p�ӂ����A�����Ɉ�����2�ς�
	void setup_call(int_t need_result_count, const Param& a0 , const Param& a1);

	/// \brief �֐����Ăяo���p�ӂ����A�����Ɉ�����3�ς�
	void setup_call(int_t need_result_count, const Param& a0 , const Param& a1, const Param& a2);

	/// \brief �֐����Ăяo���p�ӂ����A�����Ɉ�����4�ς�
	void setup_call(int_t need_result_count, const Param& a0 , const Param& a1, const Param& a2, const Param& a3);

	/// \brief �֐����Ăяo���p�ӂ����A�����Ɉ�����5�ς�
	void setup_call(int_t need_result_count, const Param& a0 , const Param& a1, const Param& a2, const Param& a3, const Param& a4);

	/// \brief �֐����Ăяo���p�ӂ����A�����Ɉ�����6�ς�
	void setup_call(int_t need_result_count, const Param& a0 , const Param& a1, const Param& a2, const Param& a3, const Param& a4, const Param& a5);

//}}REPEAT}

public:

	// �֐��Ăяo���ꑤ���g�����߂̊֐��Q

	/**
	* \brief pos�Ԗڂ̈����𓾂�B
	*
	*/
	const AnyPtr& arg(int_t pos);

	/**
	* \brief name�ɑΉ���������𓾂�B
	*
	*/
	const AnyPtr& arg(const IDPtr& name);

	/**
	* \brief pos�Ԗڂ̈����𓾂�B����pos�Ԗڂ̈������Ȃ����name�ɑΉ���������𓾂�B
	*
	*/
	const AnyPtr& arg(int_t pos, const IDPtr& name);
	
	/**
	* \brief pos�Ԗڂ̈����𓾂�B
	*
	* ����pos�Ԗڂ̈������������def�̒l��Ԃ��B
	*/
	const AnyPtr& arg_default(int_t pos, const AnyPtr& def);

	/**
	* \brief name�ɑΉ���������𓾂�B
	*
	* ����name�ɑΉ�����������������def�̒l��Ԃ��B
	*/
	const AnyPtr& arg_default(const IDPtr& name, const AnyPtr& def);

	/**
	* \brief pos�Ԗڂ̈����𓾂�B����pos�Ԗڂ̈������Ȃ����name�ɑΉ���������𓾂�B
	*
	* ����name�ɑΉ�����������������def�̒l��Ԃ��B
	*/
	const AnyPtr& arg_default(int_t pos, const IDPtr& name, const AnyPtr& def);

	/**
	* \brief pos�Ԗڂ̖��O�w������̖��O���擾�B
	*
	* \param pos 0����named_arg_count()-1�܂�
	*/
	const IDPtr& arg_name(int_t pos){
		return unchecked_ptr_cast<ID>(get(named_arg_count()*2-1-(pos*2+0)));
	}

	void adjust_args(const NamedParam* params, int_t num);

	void adjust_args(Method* params, int_t num);

	/**
	* \brief pos�Ԗڂ̈����𓾂�B
	*
	* adjust_args��ǂ񂾌ゾ���g����
	*/
	const AnyPtr& arg_unchecked(int_t pos){
		return get(ff().ordered_arg_count-1-pos);
	}

	/**
	* \brief this���擾�B
	*
	*/
	const AnyPtr& arg_this(){ 
		return ff().self(); 
	}

	/**
	* \brief �ʒu�w������̐����擾�B
	*
	*/
	int_t ordered_arg_count(){ 
		return ff().ordered_arg_count; 
	}
	
	/**
	* \brief ���O�w������̐����擾
	*
	*/
	int_t named_arg_count(){ 
		return ff().named_arg_count; 
	}

	/**
	* \brief �����̑��l�𕽂�ɂ���
	*
	*/
	void flatten_args();
	
	/**
	* \brief �Ăяo�������K�v�Ƃ��Ă���߂�l�̐��B
	*
	*/
	int_t need_result_count(){ 
		return ff().need_result_count; 
	}
	
	/**
	* \brief �Ăяo�������߂�l��K�v�Ƃ��Ă��邩�ǂ����B
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
	* \brief �Ăяo�����Ɉ����̐������̖߂�l��Ԃ��B
	*
	* need_result_count�̕������������ꍇ�͂��̕�null���Ԃ����B
	* need_result_count�̕����������Ȃ��ꍇ�͕Ԃ����l�͎̂Ă���B
	*/
	void return_result();
	void return_result(const AnyPtr& value1);
	void return_result(const AnyPtr& value1, const AnyPtr& value2);
	void return_result(const AnyPtr& value1, const AnyPtr& value2, const AnyPtr& value3);
	void return_result(const AnyPtr& value1, const AnyPtr& value2, const AnyPtr& value3, const AnyPtr& value4);

	/**
	* \brief ���l��Ԃ��B
	*/
	void return_result_mv(const ValuesPtr& values);

	/**
	* \brief return_result��carry_over�����ɌĂяo�����Ȃ�true���A�����łȂ��Ȃ�false��Ԃ��B
	*
	*/
	bool processed(){ 
		return *ff().called_pc!=InstThrowUnsupportedError::NUMBER; 
	}

	void return_result_args(const VMachinePtr& vm);
	
	void prereturn_result(const AnyPtr& v);

	void recycle_call();

	void recycle_call(const AnyPtr& a1);

public:

	const AnyPtr& catch_except();

	const AnyPtr& except(){
		return ap(except_[0]);
	}

	void set_except(const AnyPtr& e);

	void set_except_0(const Any& e);

	void set_unsuported_error_info(const Any& target, const Any& primary_key, const Any& secondary_key){
		ff().target_ = target;
		ff().primary_key_ = primary_key;
		ff().secondary_key_ = secondary_key;
	}

	void execute_inner(const inst_t* start);

	void execute(Method* fun, const inst_t* start_pc);

	void carry_over(Method* fun);

	void mv_carry_over(Method* fun);

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

	void set_hook_setting_bit(uint_t v){
		hook_setting_bit_ = v;
	}

public:

	// �X�^�b�N��i�Ԗڂ̒l���擾����B
	AnyPtr& get(int_t i){ return (AnyPtr&)ap(stack_[i]); }

	// �X�^�b�N��0�Ԗڂ̒l���擾����B
	AnyPtr& get(){ return (AnyPtr&)ap(stack_.top()); }

	// �X�^�b�N��i�Ԗڂ̒l��ݒ肷��B
	void set(int_t i, const Any& v){ stack_[i]=v; }

	// �X�^�b�N��0�Ԗڂ̒l��ݒ肷��B
	void set(const Any& v){ stack_.top()=v; }

	// �X�^�b�N��n�g�傷��B
	void upsize(int_t n){ stack_.upsize_unchecked(n); }

	// �X�^�b�N��n�k������
	void downsize(int_t n){ stack_.downsize(n); }

	// �X�^�b�N��n�ɂ���B
	void resize(int_t n){ stack_.resize(n); }

	// �X�^�b�N�ɒlv���v�b�V������B
	void push(const Any& v){ stack_.push_unchecked(v); }

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

	int_t push_mv(const ValuesPtr& mv){
		int_t size = mv->size();
		for(int_t i=0; i<size; ++i){
			push(mv->at(i));
		}
		return size;
	}

public:

	debug::CallerInfoPtr caller(uint_t n);

public:

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

		// ���ۂ̖߂�l�̐�
		int_t result_count;

		// yield���\���t���O�B���̃t���O�͌Ăяo�����ׂ��œ`�d����B
		int_t yieldable;

		// this�����C���X�^���X�ϐ��ւ̃|�C���^
		InstanceVariables* instance_variables;

		// ���̊֐��Őς܂ꂽ�X�R�[�v�̐�
		uint_t scope_size;

		// �Ăяo���ꂽ�֐��I�u�W�F�N�g
		Any fun_; 

		// �֐����Ă΂ꂽ�Ƃ���this�I�u�W�F�N�g
		Any self_;

		// UnsuportedError�̂��߂�target�������Ƃ���
		Any target_;

		// UnsuportedError�̂��߂�primary_key�������Ƃ���
		Any primary_key_;

		// UnsuportedError�̂��߂�secondary_key�������Ƃ���
		Any secondary_key_;

		FunFrame();

		void set_null();

		const FunPtr& fun() const{ return unchecked_ptr_cast<Fun>(ap(fun_)); }
		const AnyPtr& self() const{ return ap(self_); }
		const AnyPtr& target() const{ return ap(target_); }
		const IDPtr& primary_key() const{ return unchecked_ptr_cast<ID>(ap(primary_key_)); }
		const AnyPtr& secondary_key() const{ return ap(secondary_key_); }

		int_t args_stack_size(){
			return ordered_arg_count+(named_arg_count<<1);
		}

		void fun(const Any& v){ fun_ = v; }
		void self(const Any& v){ self_ = v; }
		void target(const Any& v){ target_ = v; }
		void primary_key(const Any& v){ primary_key_ = v; }
		void secondary_key(const Any& v){ secondary_key_ = v; }
	};

	friend void visit_members(Visitor& m, FunFrame& v);

	// ��O���������邽�߂̃t���[��
	struct ExceptFrame{
		ExceptInfo* info;
		uint_t stack_size;
		uint_t fun_frame_size;
		uint_t scope_size;
	};

	FunFrame& ff(){ 
		return *fun_frames_.top(); 
	}

private:

	void push_args(const ArgumentsPtr& args, int_t named_arg_count);

	const inst_t* send(const inst_t* pc, const inst_t* npc, const inst_t* cpc,
		int_t result, int_t ordered, int_t named);

	const inst_t* call(const inst_t* pc, const inst_t* npc, const inst_t* cpc,
		int_t result, int_t ordered, int_t named);

	FramePtr& push_scope(ScopeInfo* info = &empty_scope_info);

	void pop_scope();

	FunFrame& push_ff(){
		FunFrame* fp = fun_frames_.push();
		if(!fp){ 
			fun_frames_.top() = fp = new(xmalloc(sizeof(FunFrame))) FunFrame();
		}
		return *fp;
	}

	const inst_t* pop_ff(){
		pop_scope();
		return fun_frames_.pop()->poped_pc; 
	}

	const inst_t* pop_ff2(){
		return fun_frames_.pop()->poped_pc; 
	}


	void set_ff(const inst_t* pc, const inst_t* cpc, int_t need_result_count, 
			int_t ordered_arg_count, int_t named_arg_count, const AnyPtr& self){
		FunFrame& f = *fun_frames_.top();
		f.need_result_count = need_result_count;
		f.ordered_arg_count = ordered_arg_count;
		f.named_arg_count = named_arg_count;
		f.result_count = 0;
		f.called_pc = cpc;
		f.poped_pc = pc;
		f.instance_variables = (InstanceVariables*)&empty_instance_variables;
		f.scope_size = scopes_.size();
		f.self(self);
		f.fun(null);
	}

public:

	FunFrame& prev_ff(){ 
		return *fun_frames_[1]; 
	}

	const FunPtr& fun(){ 
		return ff().fun(); 
	}

	const FunPtr& prev_fun(){ 
		return prev_ff().fun(); 
	}

	const FramePtr& outer(){ 
		return ff().fun()->outer(); 
	}

	const FramePtr& prev_outer(){ 
		return prev_ff().fun()->outer(); 
	}

	const CodePtr& code(){ 
		return ff().fun()->code(); 
	}

	const CodePtr& prev_code(){ 
		return prev_ff().fun()->code(); 
	}

	const IDPtr& identifier(int_t n){ 
		return ff().fun()->code()->identifier(n); 
	}

	const IDPtr& prev_identifier(int_t n){ 
		return prev_ff().fun()->code()->identifier(n);  
	}

	ArgumentsPtr inner_make_arguments(Method* fun);

	AnyPtr append_backtrace(const inst_t* pc, const AnyPtr& ep);

private:
	const inst_t* inner_send_from_stack(const inst_t* pc, int_t need_result_count, const IDPtr& primary_key, int_t ntarget);
	const inst_t* inner_send_from_stack(const inst_t* pc, int_t need_result_count, const IDPtr& primary_key, int_t ntarget, int_t na0);
	const inst_t* inner_send_from_stack(const inst_t* pc, int_t need_result_count, const IDPtr& primary_key, int_t ntarget, int_t na0, int_t na1);
	const inst_t* inner_send_from_stack_q(const inst_t* pc, int_t need_result_count, const IDPtr& primary_key, int_t ntarget, int_t na0);
	const inst_t* inner_send_from_stack_q(const inst_t* pc, int_t need_result_count, const IDPtr& primary_key, int_t ntarget, int_t na0, int_t na1);

	const inst_t* push_except(const inst_t* pc);
	const inst_t* push_except(const inst_t* pc, const AnyPtr& e);

	const AnyPtr& arg(int_t pos, Method* names){
		FunFrame& f = ff();
		if(pos<f.ordered_arg_count){
			return get(f.args_stack_size()-1-pos);
		}
		return arg(names->param_name_at(pos));
	}

	const inst_t* check_accessibility(const inst_t* pc, const AnyPtr& cls, const AnyPtr& self, int_t accessibility);

	void set_local_variable_out_of_fun(uint_t pos, uint_t depth, const Any& value);

	AnyPtr& local_variable_out_of_fun(uint_t pos, uint_t depth);

	AnyPtr& local_variable(uint_t pos){
		return (AnyPtr&)variables_.at(variables_top_-pos-1);
	}

	void set_local_variable(uint_t pos, const Any& value){
		(Any&)variables_.at(variables_top_-pos-1) = value;
	}

	const inst_t* send_inner(const ClassPtr& cls, const AnyPtr& ret);

	const inst_t* catch_body(const inst_t* pc, const ExceptFrame& cur);

	void make_debug_info(const inst_t* pc, int_t kind);

	void debug_hook(const inst_t* pc, int_t kind);

	void check_debug_hook(const inst_t* pc, int_t kind){
		if(disable_debug_ || (hook_setting_bit_&(1<<kind))==0 || !debug::is_enabled()){
			return;
		}
		debug_hook(pc, kind);
	}

public:

//{DECLS{{
	const inst_t* FunNop(const inst_t* pc);
	const inst_t* FunPushNull(const inst_t* pc);
	const inst_t* FunPushUndefined(const inst_t* pc);
	const inst_t* FunPushTrue(const inst_t* pc);
	const inst_t* FunPushFalse(const inst_t* pc);
	const inst_t* FunPushTrueAndSkip(const inst_t* pc);
	const inst_t* FunPushInt1Byte(const inst_t* pc);
	const inst_t* FunPushFloat1Byte(const inst_t* pc);
	const inst_t* FunPushCallee(const inst_t* pc);
	const inst_t* FunPushThis(const inst_t* pc);
	const inst_t* FunPushCurrentContext(const inst_t* pc);
	const inst_t* FunPop(const inst_t* pc);
	const inst_t* FunDup(const inst_t* pc);
	const inst_t* FunInsert1(const inst_t* pc);
	const inst_t* FunInsert2(const inst_t* pc);
	const inst_t* FunAdjustResult(const inst_t* pc);
	const inst_t* FunLocalVariableInc1Byte(const inst_t* pc);
	const inst_t* FunLocalVariableDec1Byte(const inst_t* pc);
	const inst_t* FunLocalVariable1Byte(const inst_t* pc);
	const inst_t* FunLocalVariable1ByteX2(const inst_t* pc);
	const inst_t* FunLocalVariable2Byte(const inst_t* pc);
	const inst_t* FunSetLocalVariable1Byte(const inst_t* pc);
	const inst_t* FunSetLocalVariable1ByteX2(const inst_t* pc);
	const inst_t* FunSetLocalVariable2Byte(const inst_t* pc);
	const inst_t* FunInstanceVariable(const inst_t* pc);
	const inst_t* FunSetInstanceVariable(const inst_t* pc);
	const inst_t* FunFilelocalVariable(const inst_t* pc);
	const inst_t* FunCleanupCall(const inst_t* pc);
	const inst_t* FunReturn(const inst_t* pc);
	const inst_t* FunYield(const inst_t* pc);
	const inst_t* FunExit(const inst_t* pc);
	const inst_t* FunValue(const inst_t* pc);
	const inst_t* FunCheckUnsupported(const inst_t* pc);
	const inst_t* FunProperty(const inst_t* pc);
	const inst_t* FunSetProperty(const inst_t* pc);
	const inst_t* FunCall(const inst_t* pc);
	const inst_t* FunSend(const inst_t* pc);
	const inst_t* FunMember(const inst_t* pc);
	const inst_t* FunDefineMember(const inst_t* pc);
	const inst_t* FunScopeBegin(const inst_t* pc);
	const inst_t* FunScopeEnd(const inst_t* pc);
	const inst_t* FunTryBegin(const inst_t* pc);
	const inst_t* FunTryEnd(const inst_t* pc);
	const inst_t* FunPushGoto(const inst_t* pc);
	const inst_t* FunPopGoto(const inst_t* pc);
	const inst_t* FunGoto(const inst_t* pc);
	const inst_t* FunIf(const inst_t* pc);
	const inst_t* FunIfEq(const inst_t* pc);
	const inst_t* FunIfLt(const inst_t* pc);
	const inst_t* FunIfRawEq(const inst_t* pc);
	const inst_t* FunIfIn(const inst_t* pc);
	const inst_t* FunIfIs(const inst_t* pc);
	const inst_t* FunIfArgIsUndefined(const inst_t* pc);
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
	const inst_t* FunOnce(const inst_t* pc);
	const inst_t* FunSetOnce(const inst_t* pc);
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
	const inst_t* FunIfDebug(const inst_t* pc);
	const inst_t* FunAssert(const inst_t* pc);
	const inst_t* FunBreakPoint(const inst_t* pc);
	const inst_t* FunMAX(const inst_t* pc);
//}}DECLS}
	
	const inst_t* OpAddConstantInt(const inst_t* pc1, const inst_t* pc2, int_t op, Any& a, int_t constant);
	const inst_t* OpAddConstantInt(const inst_t* pc, int_t op, int_t constant);

	const inst_t* OpAdd(const inst_t* pc, int_t op);
	const inst_t* OpSub(const inst_t* pc, int_t op);
	const inst_t* OpMul(const inst_t* pc, int_t op);
	const inst_t* OpDiv(const inst_t* pc, int_t op);
	const inst_t* OpMod(const inst_t* pc, int_t op);
	const inst_t* OpAnd(const inst_t* pc, int_t op);
	const inst_t* OpOr(const inst_t* pc, int_t op);
	const inst_t* OpXor(const inst_t* pc, int_t op);
	const inst_t* OpShl(const inst_t* pc, int_t op);
	const inst_t* OpShr(const inst_t* pc, int_t op);
	const inst_t* OpUshr(const inst_t* pc, int_t op);

private:

	const FramePtr& make_outer(ScopeInfo* scope);
	const FramePtr& make_outer_outer(uint_t i=0);

private:
	inst_t end_code_;
	inst_t throw_code_;
	inst_t throw_unsupported_error_code_;
	inst_t check_unsupported_code_;
	inst_t cleanup_call_code_;

	const inst_t* resume_pc_;
	int_t yield_result_count_;

	const inst_t* throw_pc_;

	const IDPtr* id_;

	// �v�Z�p�X�^�b�N
	FastStack<Any> stack_;

	// �֐��Ăяo���̓x�ɐς܂��t���[��
	FastStack<FunFrame*> fun_frames_;

	// �X�R�[�v���
	FastStack<FramePtr> scopes_;

	xarray variables_;
	uint_t variables_top_;

	// try�̓x�ɐς܂��t���[��
	PODStack<ExceptFrame> except_frames_;
	
	Any except_[3];

	debug::HookInfoPtr debug_info_;
	bool disable_debug_;
	int_t hook_setting_bit_;

	int_t thread_yield_count_;

public:

	void make_procedure(const VMachinePtr& vm);

	void swap_procedure(const VMachinePtr& vm);

protected:

	virtual void visit_members(Visitor& m);

	virtual void before_gc();
	virtual void after_gc();

	void add_ref_count_members(int_t i);

public:

	void print_info();

private:

	XTAL_DISALLOW_COPY_AND_ASSIGN(VMachine);

};


}

#endif // XTAL_VMACHINE_H_INCLUDE_GUARD
