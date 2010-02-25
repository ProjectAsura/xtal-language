#include "xtal.h"
#include "xtal_macro.h"

#include "xtal_stringspace.h"
#include "xtal_details.h"

namespace xtal{

#undef XTAL_USE_COMPUTED_GOTO

//#define XTAL_VM_DEF_INST(key) typedef const Inst##key InstType
//#define inst (*(InstType*)pc)
#define XTAL_VM_DEF_INST(key) const key& inst = *(const key*)pc; XTAL_UNUSED_VAR(inst)

#define XTAL_VM_RETURN return
#define XTAL_VM_CHECK_EXCEPT_PC(pc) (except_[0] ? push_except(pc) : (pc))
#define XTAL_VM_THROW_EXCEPT(e) XTAL_VM_CONTINUE(push_except(pc, e))
#define XTAL_VM_CHECK_EXCEPT if(except_[0]){ XTAL_VM_CONTINUE(push_except(pc)); }

#ifdef XTAL_USE_COMPUTED_GOTO
#	define XTAL_COPY_LABEL_ADDRESS(key) &&Label##key
#	define XTAL_VM_CASE_FIRST(key) Label##key: { XTAL_VM_DEF_INST(key);
#	define XTAL_VM_CASE(key) } Label##key: { XTAL_VM_DEF_INST(key);
#	define XTAL_VM_LOOP vmloopbegin: goto *labels[*pc];
#	define XTAL_VM_LOOP_END }
#	define XTAL_VM_CONTINUE(x) { pc = (x); goto *labels[*pc]; }
#	define XTAL_VM_CONTINUE0 goto *labels[*pc]
#else
#	define XTAL_VM_CASE_FIRST(key) case key::NUMBER: { XTAL_VM_DEF_INST(key);
#	define XTAL_VM_CASE(key) } case key::NUMBER: /*printf("%s\n", #key);*/ { XTAL_VM_DEF_INST(key);
#	define XTAL_VM_LOOP switch(xop){
#	define XTAL_VM_LOOP_END } XTAL_NODEFAULT; }
#	define XTAL_VM_CONTINUE(x) { pc = (x); goto vmloopbegin; }
#	define XTAL_VM_CONTINUE0 goto vmloopbegin
#endif

#ifdef XTAL_NO_THREAD
#	define XTAL_CHECK_YIELD
#else
#	define XTAL_CHECK_YIELD if(--thread_yield_count_<0){ yield_thread(); thread_yield_count_ = 1000; }
#endif

#define XTAL_VM_FUN

const ClassPtr& Any::get_class() const{
	int_t t = type(*this);
	if(t==TYPE_BASE){ return pvalue(*this)->get_class(); }
	if(t==TYPE_POINTER){ return cpp_class(value_.cpp_class_index()); }

	static CppClassSymbolData* const data[] = {
		&CppClassSymbol<Null>::value,
		&CppClassSymbol<Undefined>::value,
		&CppClassSymbol<Bool>::value,
		&CppClassSymbol<Bool>::value,
		&CppClassSymbol<Int>::value,
		&CppClassSymbol<Float>::value,
		&CppClassSymbol<Any>::value,
		&CppClassSymbol<String>::value,
		&CppClassSymbol<String>::value,
		&CppClassSymbol<String>::value,
		&CppClassSymbol<StatelessNativeMethod>::value,
		&CppClassSymbol<Any>::value,
		&CppClassSymbol<Any>::value,
		&CppClassSymbol<String>::value,
		&CppClassSymbol<Array>::value,
		&CppClassSymbol<Values>::value,
		&CppClassSymbol<TreeNode>::value,
		&CppClassSymbol<NativeMethod>::value,
		&CppClassSymbol<NativeFun>::value,
		&CppClassSymbol<InstanceVariableGetter>::value,
		&CppClassSymbol<InstanceVariableSetter>::value,
	};

	// �^�𑝂₵����ύX���邱��
	XTAL_STATIC_ASSERT(sizeof(data)/sizeof(*data) == TYPE_MAX);

	return cpp_class(data[t]);
}

bool Any::is(const AnyPtr& klass) const{
	const ClassPtr& my_class = get_class();
	if(raweq(my_class, klass)) return true;
	return cache_is(my_class, klass);
}

bool Any::is(CppClassSymbolData* key) const{
	const AnyPtr& klass = cpp_class(key);
	const ClassPtr& my_class = get_class();
	if(raweq(my_class, klass)) return true;
	return cache_is(my_class, klass);
}

const AnyPtr& MemberCacheTable::cache(Base* target_class, const IDPtr& primary_key, const AnyPtr& secondary_key, int_t& accessibility){
	uint_t itarget_class = (uint_t)target_class;
	uint_t iprimary_key = rawvalue(primary_key).u();
	uint_t isecondary_key = rawvalue(secondary_key).u();

	uint_t hash = (itarget_class + iprimary_key + isecondary_key) ^ 
				 ((itarget_class>>8) + (iprimary_key>>8) + (isecondary_key>>8)) ^
				 ((itarget_class>>16) + (iprimary_key>>16) + (isecondary_key>>16));

	Unit& unit = table_[calc_index(hash)];

	if(((mutate_count_ ^ unit.mutate_count) | 
		rawbitxor(primary_key, unit.primary_key) | 
		((uint_t)target_class ^ rawvalue(unit.target_class).u()) | 
		rawbitxor(secondary_key, unit.secondary_key))==0){

		hit_++;
		accessibility = unit.accessibility;
		return unit.member;
	}
	else{

		miss_++;

		bool nocache = false;
		const AnyPtr& ret = target_class->rawmember(primary_key, secondary_key, true, accessibility, nocache);
		if(!nocache){
			unit.member = ret;
			unit.target_class = to_smartptr(target_class);
			unit.primary_key = primary_key;
			unit.secondary_key = secondary_key;
			unit.accessibility = accessibility;
			unit.mutate_count = mutate_count_;
		}
		return ret;
	}
}

bool IsCacheTable::cache(const AnyPtr& target_class, const AnyPtr& klass){
	uint_t itarget_class = rawvalue(target_class).u();
	uint_t iklass = rawvalue(klass).u();

	uint_t hash = (itarget_class>>3) ^ (iklass>>2);
	Unit& unit = table_[hash & CACHE_MASK];
	
	if(mutate_count_==unit.mutate_count && 
		raweq(target_class, unit.target_class) && 
		raweq(klass, unit.klass)){

		hit_++;
		return unit.result;
	}
	else{
		miss_++;

		bool ret = unchecked_ptr_cast<Class>(target_class)->is_inherited(klass);

		unit.target_class = target_class;
		unit.klass = klass;
		unit.mutate_count = mutate_count_;
		unit.result = ret;
		return ret;
	}
}

bool CtorCacheTable::cache(const AnyPtr& target_class, int_t kind){
	uint_t itarget_class = rawvalue(target_class).u();

	uint_t hash = (itarget_class>>3) ^ kind*37;
	Unit& unit = table_[hash & CACHE_MASK];
	
	if(mutate_count_==unit.mutate_count && 
		raweq(target_class, unit.target_class) &&
		kind==kind){
		hit_++;
		return true;
	}
	else{
		miss_++;

		unit.target_class = target_class;
		unit.kind = kind;
		unit.mutate_count = mutate_count_;
		return false;
	}
}

////////////////////////////////////////////////

void VMachine::carry_over(Method* fun){
	const inst_t* called_pc =  fun->source();
	check_breakpoint_hook(called_pc, BREAKPOINT_CALL);
	check_breakpoint_hook(called_pc, BREAKPOINT4);

	FunFrame& f = ff();
	
	f.set_fun(to_smartptr(fun));
	f.called_pc = called_pc;
	f.yieldable = f.poped_pc==&end_code_ ? false : prev_ff().yieldable;
	f.instance_variables = f.self()->instance_variables();
	f.processed = 1;

	FunInfo* info = fun->info();
	
	if(fun->extendable_param()){
		set_local_variable(info->variable_size-1, inner_make_arguments(fun));
	}
	else{
		if(f.ordered_arg_count!=fun->param_size()){
			adjust_args(fun);
		}
	}

	push_scope(info);

	f.ordered_arg_count = f.named_arg_count = 0;
}

void VMachine::mv_carry_over(Method* fun){
	const inst_t* called_pc =  fun->source();
	check_breakpoint_hook(called_pc, BREAKPOINT_CALL);
	check_breakpoint_hook(called_pc, BREAKPOINT4);

	FunFrame& f = ff();
	
	f.set_fun(to_smartptr(fun));
	f.called_pc = called_pc;
	f.yieldable = f.poped_pc==&end_code_ ? false : prev_ff().yieldable;
	f.instance_variables = f.self()->instance_variables();
	f.processed = 1;

	FunInfo* info = fun->info();

	int_t size = info->variable_size;
	if(f.ordered_arg_count!=size){
		adjust_values2(0, f.ordered_arg_count, size);
	}

	f.ordered_arg_count = size;
	f.named_arg_count = 0;

	push_scope(info);
}

void VMachine::adjust_values(int_t n, int_t need_result_count){
	if(n<need_result_count){
		for(int_t i=n; i<need_result_count; ++i){
			stack_.push(null);
		}
		adjust_values3((Any*)&stack_[need_result_count-1], n, need_result_count);
	}
	else{
		if(need_result_count!=0){
			adjust_values3((Any*)&stack_[n-1], n, need_result_count);
		}
		stack_.downsize(n-need_result_count);
	}
}

void VMachine::adjust_values2(int_t stack_base, int_t n, int_t need_result_count){
	adjust_values3((Any*)&local_variable(stack_base), n, need_result_count);
}

void VMachine::adjust_values3(Any* values, int_t n, int_t need_result_count){

	// �֐����Ԃ��߂�l�̐��Ɨv�����Ă���߂�l�̐���������
	if(need_result_count==n){
		return;
	}

	// �߂�l�Ȃ�ėv�����ĂȂ�
	if(need_result_count==0){
		return;
	}

	// �֐����Ԃ��߂�l����������̂�undefined�Ŗ��߂�
	if(n==0){
		for(int_t i = 0; i<need_result_count; ++i){
			values[i] = undefined;
		}
		return;
	}

	// ���̎��_�ŁAn��need_result_count��1�ȏ�

	// �v�����Ă���߂�l�̐��̕����A�֐����Ԃ��߂�l��菭�Ȃ�
	if(need_result_count<n){

		// �]�����߂�l�𑽒l�ɒ����B
		int_t size = n-need_result_count+1;
		ValuesPtr ret;
		AnyPtr top = ap(values[n-1]);
		if(type(top)==TYPE_VALUES){
			ret = unchecked_ptr_cast<Values>(top);
		}
		else{
			ret = XNew<Values>(top);
		}

		for(int_t i=1; i<size; ++i){
			ret = XNew<Values>(ap(values[n-1-i]), ret);
		}

		values[need_result_count-1] = ret;
	}
	else{
		// �v�����Ă���߂�l�̐��̕����A�֐����Ԃ��߂�l��葽��

		if(type(values[n-1])==TYPE_VALUES){
			// �Ō�̗v�f�̑��l��W�J�����ߍ���
			ValuesPtr mv = unchecked_ptr_cast<Values>(ap(values[n-1]));

			const ValuesPtr* cur = &mv;
			int_t size = 0;
			while(true){
				if((*cur)->tail()){
					if(need_result_count==n+size){
						values[n-1+size] = *cur;
						++size;
						break;
					}

					values[n-1+size] = (*cur)->head();
					++size;		
					cur = &(*cur)->tail();
				}
				else{
					values[n-1+size] = (*cur)->head();
					++size;		
					while(need_result_count>=n+size){
						values[n-1+size] = undefined;
						++size;
					}
					break;
				}
			}
		}
		else{
			// �Ō�̗v�f�����l�ł͂Ȃ��̂ŁAundefined�Ŗ��߂Ƃ�
			for(int_t i = n; i<need_result_count; ++i){
				values[i] = undefined;
			}
		}
	}
}

void VMachine::upsize_variables(uint_t upsize){
	int_t top = variables_top();

	if(variables_.size()<top+upsize+128){
		variables_.resize(top+upsize+128);
		set_variables_top(top);

		for(uint_t i=0; i<scopes_.size(); ++i){
			Scope& scope = scopes_[i]; 
			if(scope.flags!=Scope::CLASS){
				XTAL_ASSERT(scope.pos+scope.size<=variables_.size());
				scopes_[i].frame->members_.attach((AnyPtr*)variables_.data()+scope.pos, scope.size);
			}
		}
	}

	variables_top_ += upsize;
}

void VMachine::push_ff(CallState& call_state){

	FunFrame* fp = fun_frames_.push();
	if(!fp){ 
		fun_frames_.top() = fp = new(xmalloc(sizeof(FunFrame))) FunFrame();
	}

	FunFrame& f = *fp;
	f.processed = 0;
	f.need_result_count = call_state.need_result_count;
	f.ordered_arg_count = call_state.ordered;
	f.named_arg_count = call_state.named;
	f.result_count = 0;
	f.called_pc = 0;
	f.poped_pc = call_state.npc;
	f.instance_variables = (InstanceVariables*)&empty_instance_variables;
	f.result = call_state.result;
	f.prev_stack_base = variables_top();
	f.stack_base = call_state.stack_base + f.prev_stack_base;
	f.scope_lower = scopes_.size();
	f.set_self(call_state.self);
	f.set_fun();
	upsize_variables(call_state.stack_base);
}

void VMachine::pop_ff(){
	FunFrame& f = *fun_frames_.top();
	set_variables_top(f.prev_stack_base);
	result_base_ = f.result;

	if(f.need_result_count!=f.result_count){
		adjust_values(f.result_count, f.need_result_count); 
	}

	for(uint_t i=0, sz=f.need_result_count; i<sz; ++i){
		set_local_variable(result_base_+i, stack_[sz-1-i]);
	}

	stack_.downsize(f.need_result_count);

	fun_frames_.downsize(1);
	fun_frames_.top()->processed = 2;
	fun_frames_.top()->called_pc = f.poped_pc; 
}

void VMachine::pop_ff2(){
	FunFrame& f = *fun_frames_.top();
	fun_frames_.downsize(1);
	fun_frames_.top()->processed = 2;
	fun_frames_.top()->called_pc = f.poped_pc; 
}

FramePtr& VMachine::push_scope(ScopeInfo* info){
	Scope& scope = scopes_.push();
	if(!scope.frame){
		scope.pos = 0;
		scope.size = 0;
		scope.flags = Scope::NONE;
		scope.frame = XNew<Frame>();
		scope.frame->orphan_ = false;
	}

	upsize_variables(info->variable_size);

	scope.frame->set_info(info);
	scope.frame->set_code(code());
	scope.pos = variables_top()-info->variable_size;
	scope.size = info->variable_size;
	scope.frame->members_.attach((AnyPtr*)variables_.data()+scope.pos, scope.size);
	scope.flags = Scope::NONE;

	return scope.frame;
}

void VMachine::pop_scope(){
	Scope& scope = scopes_.top();
	variables_top_ -= scope.frame->info()->variable_size;

	if(scope.flags==Scope::NONE){
		scope.frame->members_.detach();
	}
	else if(scope.flags==Scope::FRAME){
		scope.frame->members_.reflesh();
		scope.frame->add_ref_count_members(1);
		scope.frame->orphan_ = true;
		scope.frame = null;
	}
	else{
		scope.frame->add_ref_count_members(1);
		scope.frame->orphan_ = true;
		scope.frame = null;
	}

	scopes_.downsize(1);
}

const FramePtr& VMachine::make_outer_outer(uint_t i, uint_t call_n, bool force){
	int_t scope_upper = call_n==0 ? scopes_.size() : fun_frames_[call_n-1]->scope_lower;

	FunFrame& ff = *fun_frames_[call_n];
	if(i < scope_upper-ff.scope_lower){
		Scope& scope = scopes_.reverse_at(scope_upper - i - 1);
		if(scope.flags==0){
			scope.flags = Scope::FRAME;
			if(force || scope.frame->info()->flags&ScopeInfo::FLAG_SCOPE_CHAIN){
				scope.frame->set_outer(make_outer_outer(i+1, call_n, force));
			}
		}
		return scope.frame;
	}

	if(ff.fun()){
		return ff.outer();
	}

	return nul<Frame>();
}

const FramePtr& VMachine::make_outer(ScopeInfo* scope){
	if(debug::is_enabled() || scope->flags&ScopeInfo::FLAG_SCOPE_CHAIN){
		return make_outer_outer(0, 0, debug::is_enabled());
	}
	return nul<Frame>();
}

void VMachine::set_local_variable_out_of_fun(uint_t pos, uint_t depth, const Any& value){
	uint_t size = scopes_.size()-ff().scope_lower;
	if(depth<size){
		scopes_[depth].frame->set_member_direct_unref(pos, value);
		return;
	}

	depth -= size;

	Frame* out = outer().get();
	while(depth){
		out = out->outer().get();
		depth--;
	}

	out->set_member_direct(pos, ap(value));
}

AnyPtr& VMachine::local_variable_out_of_fun(uint_t pos, uint_t depth){
	uint_t size = scopes_.size()-ff().scope_lower;
	if(depth<size){
		return scopes_[depth].frame->member_direct(pos);
	}

	depth -= size;

	Frame* out = outer().get();
	while(depth){
		out = out->outer().get();
		depth--;
	}

	return out->member_direct(pos);
}

void VMachine::execute_inner(const inst_t* start, int_t eval_n){

	const inst_t* pc = start;

	CallState call_state;

	ExceptFrame cur;
	cur.info = 0;
	cur.stack_size = stack_.size() - ff().args_stack_size();
	cur.fun_frame_size = fun_frames_.size();
	cur.scope_size = scopes_.size();
	cur.variables_top = variables_top();

	hook_setting_bit_ = debug::hook_setting_bit_ptr();

	Any values[4] = { null, undefined, Bool(false), Bool(true) };

	int_t eval_base_n = fun_frames_.size();

	inst_t xop = 0;


	XTAL_ASSERT(cur.stack_size>=0);
	
#ifdef XTAL_USE_COMPUTED_GOTO
	static const void* labels[] = {
	//{LABELS{{
		XTAL_COPY_LABEL_ADDRESS(InstLine),
		XTAL_COPY_LABEL_ADDRESS(InstLoadValue),
		XTAL_COPY_LABEL_ADDRESS(InstLoadConstant),
		XTAL_COPY_LABEL_ADDRESS(InstLoadInt1Byte),
		XTAL_COPY_LABEL_ADDRESS(InstLoadFloat1Byte),
		XTAL_COPY_LABEL_ADDRESS(InstLoadCallee),
		XTAL_COPY_LABEL_ADDRESS(InstLoadThis),
		XTAL_COPY_LABEL_ADDRESS(InstCopy),
		XTAL_COPY_LABEL_ADDRESS(InstMember),
		XTAL_COPY_LABEL_ADDRESS(InstUna),
		XTAL_COPY_LABEL_ADDRESS(InstArith),
		XTAL_COPY_LABEL_ADDRESS(InstBitwise),
		XTAL_COPY_LABEL_ADDRESS(InstAt),
		XTAL_COPY_LABEL_ADDRESS(InstSetAt),
		XTAL_COPY_LABEL_ADDRESS(InstGoto),
		XTAL_COPY_LABEL_ADDRESS(InstNot),
		XTAL_COPY_LABEL_ADDRESS(InstIf),
		XTAL_COPY_LABEL_ADDRESS(InstIfComp),
		XTAL_COPY_LABEL_ADDRESS(InstIfRawEq),
		XTAL_COPY_LABEL_ADDRESS(InstIfIs),
		XTAL_COPY_LABEL_ADDRESS(InstIfUndefined),
		XTAL_COPY_LABEL_ADDRESS(InstIfDebug),
		XTAL_COPY_LABEL_ADDRESS(InstPush),
		XTAL_COPY_LABEL_ADDRESS(InstPop),
		XTAL_COPY_LABEL_ADDRESS(InstAdjustValues),
		XTAL_COPY_LABEL_ADDRESS(InstLocalVariable),
		XTAL_COPY_LABEL_ADDRESS(InstSetLocalVariable),
		XTAL_COPY_LABEL_ADDRESS(InstInstanceVariable),
		XTAL_COPY_LABEL_ADDRESS(InstSetInstanceVariable),
		XTAL_COPY_LABEL_ADDRESS(InstInstanceVariableByName),
		XTAL_COPY_LABEL_ADDRESS(InstSetInstanceVariableByName),
		XTAL_COPY_LABEL_ADDRESS(InstFilelocalVariable),
		XTAL_COPY_LABEL_ADDRESS(InstSetFilelocalVariable),
		XTAL_COPY_LABEL_ADDRESS(InstFilelocalVariableByName),
		XTAL_COPY_LABEL_ADDRESS(InstSetFilelocalVariableByName),
		XTAL_COPY_LABEL_ADDRESS(InstCall),
		XTAL_COPY_LABEL_ADDRESS(InstSend),
		XTAL_COPY_LABEL_ADDRESS(InstProperty),
		XTAL_COPY_LABEL_ADDRESS(InstSetProperty),
		XTAL_COPY_LABEL_ADDRESS(InstScopeBegin),
		XTAL_COPY_LABEL_ADDRESS(InstScopeEnd),
		XTAL_COPY_LABEL_ADDRESS(InstReturn),
		XTAL_COPY_LABEL_ADDRESS(InstYield),
		XTAL_COPY_LABEL_ADDRESS(InstExit),
		XTAL_COPY_LABEL_ADDRESS(InstRange),
		XTAL_COPY_LABEL_ADDRESS(InstOnce),
		XTAL_COPY_LABEL_ADDRESS(InstSetOnce),
		XTAL_COPY_LABEL_ADDRESS(InstMakeArray),
		XTAL_COPY_LABEL_ADDRESS(InstArrayAppend),
		XTAL_COPY_LABEL_ADDRESS(InstMakeMap),
		XTAL_COPY_LABEL_ADDRESS(InstMapInsert),
		XTAL_COPY_LABEL_ADDRESS(InstMapSetDefault),
		XTAL_COPY_LABEL_ADDRESS(InstClassBegin),
		XTAL_COPY_LABEL_ADDRESS(InstClassEnd),
		XTAL_COPY_LABEL_ADDRESS(InstDefineClassMember),
		XTAL_COPY_LABEL_ADDRESS(InstDefineMember),
		XTAL_COPY_LABEL_ADDRESS(InstMakeFun),
		XTAL_COPY_LABEL_ADDRESS(InstMakeInstanceVariableAccessor),
		XTAL_COPY_LABEL_ADDRESS(InstTryBegin),
		XTAL_COPY_LABEL_ADDRESS(InstTryEnd),
		XTAL_COPY_LABEL_ADDRESS(InstPushGoto),
		XTAL_COPY_LABEL_ADDRESS(InstPopGoto),
		XTAL_COPY_LABEL_ADDRESS(InstThrow),
		XTAL_COPY_LABEL_ADDRESS(InstAssert),
		XTAL_COPY_LABEL_ADDRESS(InstBreakPoint),
		XTAL_COPY_LABEL_ADDRESS(InstMAX),
//}}LABELS}
		};
#endif

	uint_t common_flag = 0;
	int_t accessibility = 0;

	XTAL_CHECK_YIELD;

XTAL_VM_CONTINUE0;

	enum{
		SEND = 0,
		PROPERTY = 1,
		SET_PROPERTY = 2,
		MEMBER = 3
	};

	{
property_common:
		call_state.cls = call_state.target.get_class();
		common_flag = PROPERTY;
		goto send_common2;

set_property_common:
		call_state.cls = call_state.target.get_class();
		common_flag = SET_PROPERTY;
		goto send_common2;

member_common:
		common_flag = MEMBER;
		if(type(call_state.cls)!=TYPE_BASE){
			goto send_common3;
		}

		goto send_common2;

send_common:
		call_state.cls = call_state.target.get_class();
		common_flag = SEND;
		goto send_common2;

send_common2:
		accessibility = 0;
		call_state.member = cache_member(pvalue(call_state.cls), (IDPtr&)call_state.primary, ap(call_state.secondary), accessibility);

		if(accessibility){
			if(const inst_t* epc = check_accessibility(call_state, accessibility)){
				XTAL_VM_CONTINUE(epc);
			}
		}

		switch(common_flag){
			XTAL_NODEFAULT;

			XTAL_CASE(SEND){

			}

			XTAL_CASE(PROPERTY){
				if(type(call_state.member)==TYPE_IVAR_GETTER){
					const SmartPtr<InstanceVariableGetter>& p = unchecked_ptr_cast<InstanceVariableGetter>(ap(call_state.member));
					set_local_variable(call_state.result, call_state.target.instance_variables()->variable(p->number_, p->info_));
					XTAL_VM_CONTINUE(XTAL_VM_CHECK_EXCEPT_PC(call_state.npc));
				}
			}

			XTAL_CASE(SET_PROPERTY){
				if(type(call_state.member)==TYPE_IVAR_SETTER){
					const SmartPtr<InstanceVariableSetter>& p = unchecked_ptr_cast<InstanceVariableSetter>(ap(call_state.member));
					call_state.target.instance_variables()->set_variable(p->number_, p->info_, local_variable(call_state.stack_base));
					XTAL_VM_CONTINUE(XTAL_VM_CHECK_EXCEPT_PC(call_state.npc));
				}
			}

			XTAL_CASE(MEMBER){
				if(!is_undefined(call_state.member)){
					set_local_variable(call_state.result, ap(call_state.member));
					XTAL_VM_CONTINUE(XTAL_VM_CHECK_EXCEPT_PC(call_state.npc));
				}
			}
		}

		if(is_undefined(call_state.member)){
send_common3:
			XTAL_VM_CHECK_EXCEPT;

			if(call_state.flags&MEMBER_FLAG_Q_BIT){
				for(int_t i=0; i<call_state.need_result_count; ++i){
					set_local_variable(call_state.result+i, undefined);
				}
				XTAL_VM_CONTINUE(call_state.npc);
			}

			XTAL_VM_CONTINUE(push_except(call_state.pc, unsupported_error(ap(call_state.cls), (IDPtr&)call_state.primary, ap(call_state.secondary))));
		}

		call_state.self = call_state.target;
	}

	{
call_common:

		if(call_state.flags&CALL_FLAG_ARGS_BIT){
			if(ArgumentsPtr args = ptr_cast<Arguments>(local_variable(call_state.stack_base+call_state.ordered+call_state.named*2))){
				push_args(args, call_state.stack_base, call_state.ordered, call_state.named);
				call_state.ordered += args->ordered_size();
				call_state.named += args->named_size();
			}
		}

		push_ff(call_state);

		switch(type(call_state.member)){
			XTAL_DEFAULT{
				ap(call_state.member)->rawcall(to_smartptr(this));
			}

			XTAL_CASE(TYPE_UNDEFINED){

			}

			XTAL_CASE(TYPE_BASE){ 
				pvalue(ap(call_state.member))->rawcall(to_smartptr(this)); 
			}
			
			XTAL_CASE(TYPE_STATELESS_NATIVE_METHOD){ 
				unchecked_ptr_cast<StatelessNativeMethod>(ap(call_state.member))->on_rawcall(to_smartptr(this)); 
			}

			XTAL_CASE(TYPE_NATIVE_METHOD){ 
				unchecked_ptr_cast<NativeMethod>(ap(call_state.member))->on_rawcall(to_smartptr(this)); 
			}

			XTAL_CASE(TYPE_NATIVE_FUN){ 
				unchecked_ptr_cast<NativeFun>(ap(call_state.member))->on_rawcall(to_smartptr(this)); 
			}

			XTAL_CASE(TYPE_IVAR_GETTER){ 
				unchecked_ptr_cast<InstanceVariableGetter>(ap(call_state.member))->on_rawcall(to_smartptr(this)); 
			}

			XTAL_CASE(TYPE_IVAR_SETTER){ 
				unchecked_ptr_cast<InstanceVariableSetter>(ap(call_state.member))->on_rawcall(to_smartptr(this)); 
			}
		}

		if(ff().processed==0){
			if(except_[0]){ 
				XTAL_VM_CONTINUE(push_except(call_state.pc, except_[0]));
			}

			XTAL_VM_CONTINUE(push_except(call_state.pc, unsupported_error(ap(call_state.member)->get_class(), id_[IDOp::id_op_call], undefined)));
		}

		XTAL_VM_CONTINUE(XTAL_VM_CHECK_EXCEPT_PC(ff().called_pc));
	}

	{
zerodiv:
		set_runtime_error(Xt("XRE1024"), to_smartptr(this));
		XTAL_VM_CONTINUE(&throw_code_);
	}

vmloopbegin:
	xop = *pc;
vmloopbegin2:
XTAL_VM_LOOP

//{OPS{{
	XTAL_VM_CASE_FIRST(InstLine){ // 3
		check_breakpoint_hook(pc, BREAKPOINT2);
		check_breakpoint_hook(pc, BREAKPOINT_LINE);
		XTAL_VM_CONTINUE(pc + inst.ISIZE); 
	}

	XTAL_VM_CASE(InstLoadValue){ // 3
		set_local_variable(inst.result, values[inst.value]);
		XTAL_VM_CONTINUE(pc + inst.ISIZE); 
	}

	XTAL_VM_CASE(InstLoadConstant){ // 3
		set_local_variable(inst.result, code()->value(inst.value_number)); 
		XTAL_VM_CONTINUE(pc + inst.ISIZE); 
	}

	XTAL_VM_CASE(InstLoadInt1Byte){ // 3
		variables_top_[inst.result].value_.init_int(inst.value);
		XTAL_VM_CONTINUE(pc + inst.ISIZE); 
	}

	XTAL_VM_CASE(InstLoadFloat1Byte){ // 3
		variables_top_[inst.result].value_.init_float((float_t)inst.value);
		XTAL_VM_CONTINUE(pc + inst.ISIZE); 
	}

	XTAL_VM_CASE(InstLoadCallee){ // 3
		set_local_variable(inst.result, fun());
		XTAL_VM_CONTINUE(pc + inst.ISIZE); 
	}

	XTAL_VM_CASE(InstLoadThis){ // 3
		set_local_variable(inst.result, ff().self());
		XTAL_VM_CONTINUE(pc + inst.ISIZE); 
	}

	XTAL_VM_CASE(InstCopy){ // 3
		set_local_variable(inst.result, local_variable(inst.target));
		XTAL_VM_CONTINUE(pc + inst.ISIZE); 
	}

	XTAL_VM_CASE(InstMember){ // 11
		int_t flags = inst.flags;
		call_state.result = inst.result;
		call_state.need_result_count = 1;
		call_state.npc = pc + inst.ISIZE;
		call_state.flags = flags;
		call_state.primary = (flags&MEMBER_FLAG_P_BIT) ? (const IDPtr&)local_variable(inst.primary) : identifier(inst.primary);
		call_state.secondary = (flags&MEMBER_FLAG_S_BIT) ? local_variable(inst.secondary) : undefined;
		call_state.cls = local_variable(inst.target);
		call_state.self = ff().self();
		goto member_common;
	}

	XTAL_VM_CASE(InstUna){ // 27
		const AnyPtr& a = local_variable(inst.target); uint_t atype = rawtype(a);

		if(atype==TYPE_INT){
			int_t iret = 0, ia = ivalue(a);
			switch(inst.kind){
				XTAL_NODEFAULT;
				XTAL_CASE(UNA_INC){ iret = ia + 1; }
				XTAL_CASE(UNA_DEC){ iret = ia - 1; }
				XTAL_CASE(UNA_POS){ iret = ia; } 
				XTAL_CASE(UNA_NEG){ iret = -ia; }
				XTAL_CASE(UNA_COM){ iret = ~ia; }
			}
			variables_top_[inst.result].value_.init_int(iret);
			XTAL_VM_CONTINUE(pc + inst.ISIZE);
		}

		if(atype==TYPE_FLOAT){
			float_t fret = 0, fa = fvalue(a);
			switch(inst.kind){
				XTAL_NODEFAULT;
				XTAL_CASE(UNA_INC){ fret = fa + 1; }
				XTAL_CASE(UNA_DEC){ fret = fa - 1; }
				XTAL_CASE(UNA_POS){ fret = fa; } 
				XTAL_CASE(UNA_NEG){ fret = -fa; }
				XTAL_CASE(UNA_COM){ goto una_send; }
			}
			variables_top_[inst.result].value_.init_float(fret);
			XTAL_VM_CONTINUE(pc + inst.ISIZE);
		}

una_send:
		call_state.set(pc, pc+inst.ISIZE, inst.result, 1, inst.stack_base, 0, 0, 0);
		call_state.target = a;
		call_state.primary = id_[IDOp::id_op_inc+inst.kind];
		call_state.secondary = undefined;
		call_state.self = ff().self();
		goto send_common;
	}

	XTAL_VM_CASE(InstArith){ // 50
		AnyPtr& a = local_variable(inst.lhs); uint_t atype = rawtype(a);
		AnyPtr& b = local_variable(inst.rhs); uint_t btype = rawtype(b);
		uint_t kind = inst.kind&0x7;
				
		int_t ia, ib, iret;
		float_t fa, fb, fret;

		if(atype==TYPE_INT){
			ia = ivalue(a);
			if(btype==TYPE_INT){
				ib = ivalue(b);
				goto icalc;
			}

			if(btype==TYPE_FLOAT){
				fa = (float_t)ia;
				fb = fvalue(b);
				goto fcalc;
			}
		}
		else if(atype==TYPE_FLOAT){
			fa = fvalue(a);
			if(btype==TYPE_INT){
				fb = (float_t)ivalue(b);
				goto fcalc;
			}

			if(btype==TYPE_FLOAT){
				fb = fvalue(b);
				goto fcalc;
			}
		}

		goto send;

icalc:
		switch(kind){
			XTAL_NODEFAULT;
			XTAL_CASE(ARITH_ADD){ iret = ia + ib; } 
			XTAL_CASE(ARITH_SUB){ iret = ia - ib; }
			XTAL_CASE(ARITH_CAT){ goto send; }
			XTAL_CASE(ARITH_MUL){ iret = ia * ib; }
			XTAL_CASE(ARITH_DIV){ if(ib==0) goto zerodiv; iret = ia / ib; }
			XTAL_CASE(ARITH_MOD){ if(ib==0) goto zerodiv; iret = ia % ib; }
		}

		variables_top_[inst.result].value_.init_int(iret);
		XTAL_VM_CONTINUE(pc + inst.ISIZE);

fcalc:
		using namespace std;
		switch(kind){
			XTAL_NODEFAULT;
			XTAL_CASE(ARITH_ADD){ fret = fa + fb; } 
			XTAL_CASE(ARITH_SUB){ fret = fa - fb; }
			XTAL_CASE(ARITH_CAT){ goto send; }
			XTAL_CASE(ARITH_MUL){ fret = fa * fb; }
			XTAL_CASE(ARITH_DIV){ if(fb==0) goto zerodiv; fret = fa / fb; }
			XTAL_CASE(ARITH_MOD){ if(fb==0) goto zerodiv; fret = fmodf(fa, fb); }
		}
		variables_top_[inst.result].value_.init_float(fret);
		XTAL_VM_CONTINUE(pc + inst.ISIZE);

send:
		set_local_variable(inst.stack_base, b);
		call_state.set(pc, pc+inst.ISIZE, inst.result, 1, inst.stack_base, 1, 0, 0);
		call_state.target = a;
		call_state.primary = id_[inst.kind>=ARITH_ADD_ASSIGN ? IDOp::id_op_add_assign+kind : IDOp::id_op_add+kind];
		call_state.secondary = undefined;
		call_state.self = ff().self();
		goto send_common;
	}

	XTAL_VM_CASE(InstBitwise){ // 23
		AnyPtr& a = local_variable(inst.lhs);
		AnyPtr& b = local_variable(inst.rhs);
		uint_t kind = inst.kind&0x7;

		if(rawtype(a)==TYPE_INT && rawtype(b)==TYPE_INT){
			int_t ia, ib, iret;
			ia = ivalue(a); ib = ivalue(b);
			switch(kind){
				XTAL_NODEFAULT;
				XTAL_CASE(BITWISE_AND){ iret = ia & ib; }
				XTAL_CASE(BITWISE_OR){ iret = ia | ib; }
				XTAL_CASE(BITWISE_XOR){ iret = ia ^ ib; }
				XTAL_CASE(BITWISE_SHL){ iret = ia << ib; }
				XTAL_CASE(BITWISE_SHR){ iret = ia >> ib; }
				XTAL_CASE(BITWISE_USHR){ iret = (uint_t)ia >> ib; }
			}

			variables_top_[inst.result].value_.init_int(iret);
			XTAL_VM_CONTINUE(pc + inst.ISIZE);
		}

		set_local_variable(inst.stack_base, b);
		call_state.set(pc, pc+inst.ISIZE, inst.result, 1, inst.stack_base, 1, 0, 0);
		call_state.target = a;
		call_state.primary = id_[inst.kind>=BITWISE_AND_ASSIGN ? IDOp::id_op_and_assign+kind : IDOp::id_op_and+kind];
		call_state.secondary = undefined;
		call_state.self = ff().self();
		goto send_common;
	}

	XTAL_VM_CASE(InstAt){ // 22
		AnyPtr& a = local_variable(inst.target); uint_t atype = type(a);
		AnyPtr& b = local_variable(inst.index); uint_t btype = rawtype(b);

		if(atype==TYPE_ARRAY && btype==TYPE_INT){
			int_t index = ivalue(b);
			const ArrayPtr& ary = unchecked_ptr_cast<Array>(a);

			if((uint_t)index<ary->size()){
				set_local_variable(inst.result, ary->at(index));
			}
			else{
				set_local_variable(inst.result, ary->op_at(index));
				XTAL_VM_CHECK_EXCEPT;
			}
			XTAL_VM_CONTINUE(pc+inst.ISIZE); 
		}
		else if(raweq(a->get_class(), cpp_class<Map>())){
			Any ret = unchecked_ptr_cast<Map>(a)->op_at(b);
			XTAL_VM_CHECK_EXCEPT;
			set_local_variable(inst.result, ret);
			XTAL_VM_CONTINUE(pc+inst.ISIZE); 
		}
		else{
			set_local_variable(inst.stack_base, b);
			call_state.set(pc, pc+inst.ISIZE, inst.result, 1, inst.stack_base, 1, 0, 0);
			call_state.target = a;
			call_state.primary = id_[IDOp::id_op_at];
			call_state.secondary = undefined;
			call_state.self = ff().self();
			goto send_common;
		}
	}

	XTAL_VM_CASE(InstSetAt){ // 23
		AnyPtr& a = local_variable(inst.target); uint_t atype = type(a);
		AnyPtr& b = local_variable(inst.index); uint_t btype = rawtype(b);
		AnyPtr& c = local_variable(inst.value);

		if(atype==TYPE_ARRAY && btype==TYPE_INT){
			int_t index = ivalue(b);
			const ArrayPtr& ary = unchecked_ptr_cast<Array>(a);

			if((uint_t)index<ary->size()){
				ary->set_at(index, c);
			}
			else{
				ary->op_set_at(index, c);
				XTAL_VM_CHECK_EXCEPT;
			}
			XTAL_VM_CONTINUE(pc+inst.ISIZE); 
		}
		else if(raweq(a->get_class(), cpp_class<Map>())){
			unchecked_ptr_cast<Map>(a)->op_set_at(b, c);
			XTAL_VM_CHECK_EXCEPT;
			XTAL_VM_CONTINUE(pc+inst.ISIZE); 
		}
		else{
			set_local_variable(inst.stack_base+0, b);
			set_local_variable(inst.stack_base+1, c);

			call_state.set(pc, pc + inst.ISIZE, inst.stack_base, 0, inst.stack_base, 2, 0, 0);
			call_state.target = a;
			call_state.primary = id_[IDOp::id_op_set_at];
			call_state.secondary = undefined;
			call_state.self = ff().self();
			goto send_common;
		}
	}

	XTAL_VM_CASE(InstGoto){ // 3
		XTAL_CHECK_YIELD;
		XTAL_VM_CONTINUE(pc + inst.address); 
	}

	XTAL_VM_CASE(InstNot){ // 3
		set_local_variable(inst.result, Bool(!local_variable(inst.target))); 
		XTAL_VM_CONTINUE(pc+inst.ISIZE); 
	}

	XTAL_VM_CASE(InstIf){ // 3
		XTAL_CHECK_YIELD;
		XTAL_VM_CONTINUE(pc + (local_variable(inst.target) ? inst.address_true : inst.address_false));
	}

	XTAL_VM_CASE(InstIfComp){ // 41
		XTAL_CHECK_YIELD;
		typedef InstIf InstType2; 
		InstType2& inst2 = *(InstType2*)(pc+inst.ISIZE);
	
		AnyPtr& a = local_variable(inst.lhs); uint_t atype = rawtype(a);
		AnyPtr& b = local_variable(inst.rhs); uint_t btype = rawtype(b);

		int next;
		int_t ia, ib;
		float_t fa, fb;

		if(atype==TYPE_INT){
			ia = ivalue(a);
			if(btype==TYPE_INT){
				ib = ivalue(b);
				goto icomp;
			}

			if(btype==TYPE_FLOAT){
				fa = (float_t)ia;
				fb = fvalue(b);
				goto fcomp;
			}
		}
		else if(atype==TYPE_FLOAT){
			fa = fvalue(a);
			if(btype==TYPE_INT){
				fb = (float_t)ivalue(b);
				goto fcomp;
			}

			if(btype==TYPE_FLOAT){
				fb = fvalue(b);
				goto fcomp;
			}
		}

		goto comp_send;

icomp:
		switch(inst.kind){
			XTAL_NODEFAULT;
			XTAL_CASE(IF_COMP_EQ){ next = ia==ib ? inst2.address_true : inst2.address_false; } 
			XTAL_CASE(IF_COMP_LT){ next = ia<ib ? inst2.address_true : inst2.address_false; } 
			XTAL_CASE(IF_COMP_IN){ goto comp_send; }
		}
		XTAL_VM_CONTINUE(next + pc + inst.ISIZE);

fcomp:
		switch(inst.kind){
			XTAL_NODEFAULT;
			XTAL_CASE(IF_COMP_EQ){ next = fa==fb ? inst2.address_true : inst2.address_false; } 
			XTAL_CASE(IF_COMP_LT){ next = fa<fb ? inst2.address_true : inst2.address_false; } 
			XTAL_CASE(IF_COMP_IN){ goto comp_send; }
		}
		XTAL_VM_CONTINUE(next + pc + inst.ISIZE);

comp_send:
		if(inst.kind==IF_COMP_EQ && raweq(a, b)){
			XTAL_VM_CONTINUE(inst2.address_true + pc + inst.ISIZE);
		}		

		set_local_variable(inst.stack_base, b);
		call_state.set(pc, pc+inst.ISIZE, inst2.target, 1, inst.stack_base, 1, 0, MEMBER_FLAG_Q_BIT);
		call_state.target = a;
		call_state.primary = id_[IDOp::id_op_eq+inst.kind];
		call_state.secondary = undefined;
		call_state.self = ff().self();
		goto send_common;
	}

	XTAL_VM_CASE(InstIfRawEq){ // 8
		XTAL_CHECK_YIELD;
		typedef InstIf InstType2; 
		InstType2& inst2 = *(InstType2*)(pc+inst.ISIZE);

		const AnyPtr& a = local_variable(inst.lhs);
		const AnyPtr& b = local_variable(inst.rhs);

		pc = (raweq(a, b) ? 
			(int)(inst2.address_true) : 
			(int)(inst2.address_false)) + pc + inst.ISIZE;

		XTAL_VM_CONTINUE(pc);
	}

	XTAL_VM_CASE(InstIfIs){ // 8
		XTAL_CHECK_YIELD;
		typedef InstIf InstType2; 
		InstType2& inst2 = *(InstType2*)(pc+inst.ISIZE);

		const AnyPtr& a = local_variable(inst.lhs);
		const AnyPtr& b = local_variable(inst.rhs);

		pc = (a->is(b) ? 
			(int)(inst2.address_true) : 
			(int)(inst2.address_false)) + pc + inst.ISIZE;

		XTAL_VM_CONTINUE(pc);
	}

	XTAL_VM_CASE(InstIfUndefined){ // 3
		XTAL_CHECK_YIELD;
		XTAL_VM_CONTINUE(pc + (is_undefined(local_variable(inst.target)) ? inst.address_true : inst.address_false));
	}

	XTAL_VM_CASE(InstIfDebug){ // 2
		XTAL_VM_CONTINUE(pc + (debug::is_enabled() ? inst.ISIZE : inst.address));
	}

	XTAL_VM_CASE(InstPush){ // 3
		stack_.push(local_variable(inst.target));
		XTAL_VM_CONTINUE(pc + inst.ISIZE); 
	}

	XTAL_VM_CASE(InstPop){ // 3
		Any ret = stack_.top(); stack_.pop();
		set_local_variable(inst.result, ret);
		XTAL_VM_CONTINUE(pc + inst.ISIZE); 
	}

	XTAL_VM_CASE(InstAdjustValues){ // 3
		adjust_values2(inst.stack_base, inst.result_count, inst.need_result_count);
		XTAL_VM_CONTINUE(pc + inst.ISIZE); 
	}

	XTAL_VM_CASE(InstLocalVariable){ // 3
		set_local_variable(inst.result, local_variable_out_of_fun(inst.number, inst.depth)); 
		XTAL_VM_CONTINUE(pc + inst.ISIZE); 
	}

	XTAL_VM_CASE(InstSetLocalVariable){ // 3
		set_local_variable_out_of_fun(inst.number, inst.depth, local_variable(inst.target)); 
		XTAL_VM_CONTINUE(pc + inst.ISIZE); 
	}

	XTAL_VM_CASE(InstInstanceVariable){ // 3
		set_local_variable(inst.result, ff().instance_variables->variable(inst.number, code()->class_info(inst.info_number)));
		XTAL_VM_CONTINUE(pc + inst.ISIZE); 
	}

	XTAL_VM_CASE(InstSetInstanceVariable){ // 3
		ff().instance_variables->set_variable(inst.number, code()->class_info(inst.info_number), local_variable(inst.value));
		XTAL_VM_CONTINUE(pc + inst.ISIZE);
	}

	XTAL_VM_CASE(InstInstanceVariableByName){ // 3
		if(eval_n){
			const AnyPtr& ret = eval_instance_variable(ff().self(), identifier(inst.identifier_number));
			set_local_variable(inst.result, ret);
		}

		XTAL_VM_CONTINUE(pc + inst.ISIZE); 
	}

	XTAL_VM_CASE(InstSetInstanceVariableByName){ // 3
		if(eval_n){
			eval_set_instance_variable(ff().self(), identifier(inst.identifier_number), local_variable(inst.value));
		}

		XTAL_VM_CONTINUE(pc + inst.ISIZE);
	}

	XTAL_VM_CASE(InstFilelocalVariable){ // 3
		set_local_variable(inst.result, code()->member_direct(inst.value_number));
		XTAL_VM_CONTINUE(pc + inst.ISIZE); 
	}

	XTAL_VM_CASE(InstSetFilelocalVariable){ // 3
		code()->Frame::set_member_direct(inst.value_number, local_variable(inst.value));
		XTAL_VM_CONTINUE(pc + inst.ISIZE);
	}

	XTAL_VM_CASE(InstFilelocalVariableByName){ // 8
		if(eval_n){
			const AnyPtr& ret = eval_local_variable(identifier(inst.identifier_number), eval_n + (fun_frames_.size()-eval_base_n));
			if(!is_undefined(ret)){
				set_local_variable(inst.result, ret);
				XTAL_VM_CONTINUE(pc + inst.ISIZE);
			}
		}

		const AnyPtr& ret = code()->member(identifier(inst.identifier_number));
		if(!is_undefined(ret)){
			set_local_variable(inst.result, ret);
			XTAL_VM_CONTINUE(pc + inst.ISIZE);
		}
		else{
			XTAL_VM_THROW_EXCEPT(filelocal_unsupported_error(code(), identifier(inst.identifier_number)));
		}
	}

	XTAL_VM_CASE(InstSetFilelocalVariableByName){ // 3
		if(eval_n){
			if(eval_set_local_variable(identifier(inst.identifier_number), local_variable(inst.value), eval_n + (fun_frames_.size()-eval_base_n))){
				XTAL_VM_CONTINUE(pc + inst.ISIZE);
			}
		}

		XTAL_VM_THROW_EXCEPT(filelocal_unsupported_error(code(), identifier(inst.identifier_number)));
	}

	XTAL_VM_CASE(InstCall){ // 6
		int_t flags = inst.flags;
		call_state.set(pc, pc + inst.ISIZE, inst.result, inst.need_result, inst.stack_base, inst.ordered, inst.named, flags);
		call_state.member = local_variable(inst.target);
		call_state.self = (flags&CALL_FLAG_THIS) ? local_variable(inst.self) : ff().self();
		goto call_common;
	}

	XTAL_VM_CASE(InstSend){ // 8
		int_t flags = inst.flags;
		call_state.set(pc, pc + inst.ISIZE, inst.result, inst.need_result, inst.stack_base, inst.ordered, inst.named, flags);
		call_state.target = local_variable(inst.target);
		call_state.primary = (flags&MEMBER_FLAG_P_BIT) ? (IDPtr&)local_variable(inst.primary) : identifier(inst.primary);
		call_state.secondary = (flags&MEMBER_FLAG_S_BIT) ? local_variable(inst.secondary) : undefined;
		call_state.self = ff().self();
		goto send_common;
	}

	XTAL_VM_CASE(InstProperty){ // 7
		call_state.set(pc, pc + inst.ISIZE, inst.result, 1, inst.stack_base, 0, 0, 0);
		call_state.target = local_variable(inst.target);
		call_state.primary = identifier(inst.primary);
		call_state.secondary = undefined;
		call_state.self = ff().self();
		goto property_common;
	}

	XTAL_VM_CASE(InstSetProperty){ // 7
		call_state.set(pc, pc + inst.ISIZE, inst.stack_base, 0, inst.stack_base, 1, 0, 0);
		call_state.target = local_variable(inst.target);
		call_state.primary = identifier(inst.primary);
		call_state.secondary = undefined;
		call_state.self = ff().self();
		goto set_property_common;
	}

	XTAL_VM_CASE(InstScopeBegin){ // 3
		push_scope(code()->scope_info(inst.info_number));
		XTAL_VM_CONTINUE(pc + inst.ISIZE);
	}

	XTAL_VM_CASE(InstScopeEnd){ // 3
		pop_scope();
		XTAL_VM_CONTINUE(pc + inst.ISIZE);
	}

	XTAL_VM_CASE(InstReturn){ // 7
		check_breakpoint_hook(pc, BREAKPOINT_RETURN);

		FunFrame& f = ff();
		f.result_count += inst.result_count;
		pop_scope();
		pop_ff();
			
		const inst_t* next_pc = ff().called_pc;
		check_breakpoint_hook(next_pc-1, BREAKPOINT3);
		XTAL_VM_CONTINUE(next_pc);
	}

	XTAL_VM_CASE(InstYield){ // 7
		yield_target_count_ = inst.target_count;	
		yield_result_ = inst.result;
		yield_need_result_count_ = inst.need_result_count;

		if(ff().yieldable){
			resume_pc_ = pc + inst.ISIZE;
			XTAL_VM_RETURN;
		}
		else{
			XTAL_VM_THROW_EXCEPT(cpp_class<YieldError>()->call(Xt("XRE1012")));
		}
	}

	XTAL_VM_CASE(InstExit){ // 3
		resume_pc_ = 0; 
		XTAL_VM_RETURN;
	}

	XTAL_VM_CASE(InstRange){ // 11
		AnyPtr& a = local_variable(inst.lhs);
		AnyPtr& b = local_variable(inst.rhs);

		set_local_variable(inst.stack_base+0, b);
		set_local_variable(inst.stack_base+1, Int(inst.kind));

		call_state.set(pc, pc + inst.ISIZE, inst.result, 1, inst.stack_base, 2, 0, 0);
		call_state.target = a;
		call_state.primary = id_[IDOp::id_op_range];
		call_state.secondary = undefined;
		call_state.self = ff().self();
		goto send_common;
	}

	XTAL_VM_CASE(InstOnce){ // 5
		const AnyPtr& ret = code()->once_value(inst.value_number);
		if(!is_undefined(ret)){
			set_local_variable(inst.result, ret);
			XTAL_VM_CONTINUE(pc + inst.address);
		}
		else{
			XTAL_VM_CONTINUE(pc + inst.ISIZE);
		}
	}

	XTAL_VM_CASE(InstSetOnce){ // 3
		code()->set_once_value(inst.value_number, local_variable(inst.target)); 
		XTAL_VM_CONTINUE(pc + inst.ISIZE); 
	}

	XTAL_VM_CASE(InstMakeArray){ // 4
		SmartPtr<Array> value = xnew<Array>();
		set_local_variable(inst.result, value);
		XTAL_VM_CONTINUE(pc + inst.ISIZE);
	}

	XTAL_VM_CASE(InstArrayAppend){ // 3
		ptr_cast<Array>(local_variable(inst.target))->push_back(local_variable(inst.value)); 
		XTAL_VM_CONTINUE(pc + inst.ISIZE);
	}

	XTAL_VM_CASE(InstMakeMap){ // 4
		SmartPtr<Map> value = xnew<Map>();
		set_local_variable(inst.result, value);
		XTAL_VM_CONTINUE(pc + inst.ISIZE);
	}

	XTAL_VM_CASE(InstMapInsert){ // 3
		ptr_cast<Map>(local_variable(inst.target))->set_at(local_variable(inst.key), local_variable(inst.value)); 
		XTAL_VM_CONTINUE(pc + inst.ISIZE);
	}

	XTAL_VM_CASE(InstMapSetDefault){ // 3
		ptr_cast<Map>(local_variable(inst.target))->set_default_value(local_variable(inst.value)); 
		XTAL_VM_CONTINUE(pc + inst.ISIZE);
	}

	XTAL_VM_CASE(InstClassBegin){ XTAL_VM_CONTINUE(FunInstClassBegin(pc)); /*
		XTAL_VM_FUN;
		ClassInfo* info = code()->class_info(inst.info_number);
		const FramePtr& outer = make_outer(info);
		ClassPtr cp = xnew<Class>(outer, code(), info);

		switch(info->kind){
			XTAL_NODEFAULT;

			XTAL_CASE(KIND_CLASS){

			}

			XTAL_CASE(KIND_SINGLETON){
				cp->set_singleton();
			}
		}
		
		int_t n = info->mixins;
		for(int_t i = 0; i<n; ++i){
			AnyPtr popped = local_variable(inst.mixin_base+i);
			if(const ClassPtr& cls = ptr_cast<Class>(popped)){
				cp->inherit_first(cls);
			}
			else{
				set_runtime_error(undefined);
			}
		}

		Scope& scope = scopes_.push();
		scope.frame = cp;
		scope.pos = 0;
		scope.size = 0;
		scope.flags = Scope::CLASS;
		cp->orphan_ = false;

		CallState call_state;
		call_state.self = cp;
		call_state.npc = pc + inst.ISIZE;
		call_state.result = 0;
		call_state.need_result_count = 0;
		call_state.stack_base = 0;
		call_state.ordered = 0;
		call_state.named = 0;
		push_ff(call_state);

		ff().set_fun(prev_fun());
		ff().set_outer(cp);
		XTAL_VM_CONTINUE(pc + inst.ISIZE);
	}*/ }

	XTAL_VM_CASE(InstClassEnd){ XTAL_VM_CONTINUE(FunInstClassEnd(pc)); /*
		XTAL_VM_FUN;
		Scope& scope = scopes_.top();
		if(raweq(scope.frame->get_class(), scope.frame)){
			Class* singleton = static_cast<Class*>(pvalue(scope.frame));
			singleton->init_singleton(to_smartptr(this));
		}

		set_local_variable(inst.result, scope.frame);
		scope.frame->add_ref_count_members(1);
		scope.frame->orphan_ = true;
		scope.frame = null;
		scopes_.downsize(1);

		fun_frames_.downsize(1);
		XTAL_VM_CONTINUE(pc + inst.ISIZE);
	}*/ }

	XTAL_VM_CASE(InstDefineClassMember){ XTAL_VM_CONTINUE(FunInstDefineClassMember(pc)); /*
		XTAL_VM_FUN;
		if(const ClassPtr& p = ptr_cast<Class>(scopes_.top().frame)){
			p->set_member_direct(inst.number, identifier(inst.primary), local_variable(inst.value), local_variable(inst.secondary), inst.accessibility);
		}
		XTAL_VM_CONTINUE(pc + inst.ISIZE);
	}*/ }

	XTAL_VM_CASE(InstDefineMember){ XTAL_VM_CONTINUE(FunInstDefineMember(pc)); /*
		XTAL_VM_FUN;
		IDPtr primary = (inst.flags&MEMBER_FLAG_P_BIT) ? (const IDPtr&)local_variable(inst.primary) : identifier(inst.primary);
		AnyPtr secondary = (inst.flags&MEMBER_FLAG_S_BIT) ? local_variable(inst.secondary) : undefined;
		AnyPtr cls = local_variable(inst.target);
		AnyPtr value = local_variable(inst.value);
		cls->def(primary, ap(value), secondary, KIND_PUBLIC);
		XTAL_VM_CHECK_EXCEPT;
		XTAL_VM_CONTINUE(pc + inst.ISIZE); 
	}*/ }

	XTAL_VM_CASE(InstMakeFun){ XTAL_VM_CONTINUE(FunInstMakeFun(pc)); /*
		XTAL_VM_FUN;
		int_t table_n = inst.info_number, end = inst.address;
		FunInfo* info = code()->fun_info(table_n);
		const FramePtr& outer = make_outer(info);
		switch(info->kind){
			XTAL_NODEFAULT;
			XTAL_CASE(KIND_FUN){ set_local_variable(inst.result, xnew<Fun>(outer, ff().self(), code(), info)); }
			XTAL_CASE(KIND_LAMBDA){ set_local_variable(inst.result, xnew<Lambda>(outer, ff().self(), code(), info)); }
			XTAL_CASE(KIND_METHOD){ set_local_variable(inst.result, xnew<Method>(outer, code(), info)); }
			XTAL_CASE(KIND_FIBER){ set_local_variable(inst.result, xnew<Fiber>(outer, ff().self(), code(), info)); }
		}
		XTAL_VM_CONTINUE(pc + end);
	}*/ }

	XTAL_VM_CASE(InstMakeInstanceVariableAccessor){ XTAL_VM_CONTINUE(FunInstMakeInstanceVariableAccessor(pc)); /*
		XTAL_VM_FUN;
		AnyPtr ret;
		switch(inst.type){
			XTAL_NODEFAULT;
			XTAL_CASE(0){ ret = XNew<InstanceVariableGetter>(inst.number, code()->class_info(inst.info_number)); }
			XTAL_CASE(1){ ret = XNew<InstanceVariableSetter>(inst.number, code()->class_info(inst.info_number)); }
		}
		set_local_variable(inst.result, ret);
		XTAL_VM_CONTINUE(pc + inst.ISIZE); 
	}*/ }

	XTAL_VM_CASE(InstTryBegin){ XTAL_VM_CONTINUE(FunInstTryBegin(pc)); /*
		XTAL_VM_FUN;
		//FunFrame& f = ff();
		ExceptFrame& ef = except_frames_.push();
		ef.info = code()->except_info(inst.info_number);
		ef.fun_frame_size = fun_frames_.size();
		ef.stack_size = stack_.size();
		ef.scope_size = scopes_.size();
		ef.variables_top = variables_top();
		XTAL_VM_CONTINUE(pc + inst.ISIZE);
	}*/ }

	XTAL_VM_CASE(InstTryEnd){ // 2
		XTAL_VM_CONTINUE(except_frames_.pop().info->finally_pc + code()->data()); 
	}

	XTAL_VM_CASE(InstPushGoto){ // 3
		stack_.push(Int((int_t)((pc+inst.address)-code()->data()))); 
		XTAL_VM_CONTINUE(pc + inst.ISIZE); 
	}

	XTAL_VM_CASE(InstPopGoto){ // 2
		Any ret = stack_.top(); stack_.pop();
		XTAL_VM_CONTINUE(code()->data()+ivalue(ret));
	}

	XTAL_VM_CASE(InstThrow){ // 12
		AnyPtr except = ap(stack_.top());
		stack_.pop();

		if(!except){
			except = except_[0];
		}

		if(pc!=&throw_code_){
			throw_pc_ = pc;
		}

		if(!except->is(cpp_class<Exception>())){
			except = cpp_class<RuntimeError>()->call(except);
		}

		except_[0] = except; 
		check_breakpoint_hook(pc==&throw_code_ ? throw_pc_ : pc, BREAKPOINT_THROW); 

		// ��O�Ƀo�b�N�g���[�X��ǉ�����
		AnyPtr e = catch_except();
		set_except_x(append_backtrace(throw_pc_, e));

		// Xtal�\�[�X���ŃL���b�`�����邩���ׂ�
		pc = catch_body(throw_pc_, cur);

		// Xtal�\�[�X���ŃL���b�`�����ꂽ�Ȃ�ŏ��ɖ߂�
		if(pc){
			XTAL_VM_CONTINUE(pc);
		}
		
		// ����ĂȂ��Ȃ烋�[�v�E�o
		XTAL_VM_RETURN;
	}

	XTAL_VM_CASE(InstAssert){ XTAL_VM_CONTINUE(FunInstAssert(pc)); /*
		XTAL_VM_FUN;
		set_except_x(cpp_class<AssertionFailed>()->call(ptr_cast<String>(local_variable(inst.message))));
		breakpoint_hook(pc, fun(), BREAKPOINT_ASSERT);

		if(except_[0]){
			XTAL_VM_THROW_EXCEPT(except_[0]);
		}

		XTAL_VM_CONTINUE(pc + inst.ISIZE);
	}*/ }

	XTAL_VM_CASE(InstBreakPoint){ // 5
		check_breakpoint_hook(pc, BREAKPOINT);
		if(inst_t opp = code()->original_op(pc)){
			xop = opp;
			goto vmloopbegin2;
		}

		XTAL_VM_CONTINUE(pc + inst.ISIZE); 
	}

	XTAL_VM_CASE(InstMAX){ // 2
		XTAL_VM_CONTINUE(pc + inst.ISIZE);
	}

//}}OPS}

XTAL_VM_LOOP_END

}

#undef XTAL_VM_CONTINUE
#undef XTAL_VM_CONTINUE0
#undef XTAL_VM_THROW_EXCEPT
#undef XTAL_VM_CHECK_EXCEPT

#define XTAL_VM_CONTINUE(x) return (x)
#define XTAL_VM_CONTINUE0 return pc
#define XTAL_VM_THROW_EXCEPT(e) XTAL_VM_CONTINUE(push_except(pc, e))
#define XTAL_VM_CHECK_EXCEPT if(except_[0]){ XTAL_VM_CONTINUE(push_except(pc)); }

//{FUNS{{
const inst_t* VMachine::FunInstClassBegin(const inst_t* pc){
		XTAL_VM_DEF_INST(InstClassBegin);
		XTAL_VM_FUN;
		ClassInfo* info = code()->class_info(inst.info_number);
		const FramePtr& outer = make_outer(info);
		ClassPtr cp = xnew<Class>(outer, code(), info);

		switch(info->kind){
			XTAL_NODEFAULT;

			XTAL_CASE(KIND_CLASS){

			}

			XTAL_CASE(KIND_SINGLETON){
				cp->set_singleton();
			}
		}
		
		int_t n = info->mixins;
		for(int_t i = 0; i<n; ++i){
			AnyPtr popped = local_variable(inst.mixin_base+i);
			if(const ClassPtr& cls = ptr_cast<Class>(popped)){
				cp->inherit_first(cls);
			}
			else{
				XTAL_VM_THROW_EXCEPT(cpp_class<RuntimeError>()->call());
			}
		}

		Scope& scope = scopes_.push();
		scope.frame = cp;
		scope.pos = 0;
		scope.size = 0;
		scope.flags = Scope::CLASS;
		cp->orphan_ = false;

		CallState call_state;
		call_state.self = cp;
		call_state.npc = pc + inst.ISIZE;
		call_state.result = 0;
		call_state.need_result_count = 0;
		call_state.stack_base = 0;
		call_state.ordered = 0;
		call_state.named = 0;
		push_ff(call_state);

		ff().set_fun(prev_fun());
		ff().set_outer(cp);
		XTAL_VM_CONTINUE(pc + inst.ISIZE);
}

const inst_t* VMachine::FunInstClassEnd(const inst_t* pc){
		XTAL_VM_DEF_INST(InstClassEnd);
		XTAL_VM_FUN;
		Scope& scope = scopes_.top();
		if(raweq(scope.frame->get_class(), scope.frame)){
			Class* singleton = static_cast<Class*>(pvalue(scope.frame));
			singleton->init_singleton(to_smartptr(this));
		}

		set_local_variable(inst.result, scope.frame);
		scope.frame->add_ref_count_members(1);
		scope.frame->orphan_ = true;
		scope.frame = null;
		scopes_.downsize(1);

		fun_frames_.downsize(1);
		XTAL_VM_CONTINUE(pc + inst.ISIZE);
}

const inst_t* VMachine::FunInstDefineClassMember(const inst_t* pc){
		XTAL_VM_DEF_INST(InstDefineClassMember);
		XTAL_VM_FUN;
		if(const ClassPtr& p = ptr_cast<Class>(scopes_.top().frame)){
			p->set_member_direct(inst.number, identifier(inst.primary), local_variable(inst.value), local_variable(inst.secondary), inst.accessibility);
		}
		XTAL_VM_CONTINUE(pc + inst.ISIZE);
}

const inst_t* VMachine::FunInstDefineMember(const inst_t* pc){
		XTAL_VM_DEF_INST(InstDefineMember);
		XTAL_VM_FUN;
		IDPtr primary = (inst.flags&MEMBER_FLAG_P_BIT) ? (const IDPtr&)local_variable(inst.primary) : identifier(inst.primary);
		AnyPtr secondary = (inst.flags&MEMBER_FLAG_S_BIT) ? local_variable(inst.secondary) : undefined;
		AnyPtr cls = local_variable(inst.target);
		AnyPtr value = local_variable(inst.value);
		cls->def(primary, value, secondary, KIND_PUBLIC);
		XTAL_VM_CHECK_EXCEPT;
		XTAL_VM_CONTINUE(pc + inst.ISIZE); 
}

const inst_t* VMachine::FunInstMakeFun(const inst_t* pc){
		XTAL_VM_DEF_INST(InstMakeFun);
		XTAL_VM_FUN;
		int_t table_n = inst.info_number, end = inst.address;
		FunInfo* info = code()->fun_info(table_n);
		const FramePtr& outer = make_outer(info);
		switch(info->kind){
			XTAL_NODEFAULT;
			XTAL_CASE(KIND_FUN){ set_local_variable(inst.result, xnew<Fun>(outer, ff().self(), code(), info)); }
			XTAL_CASE(KIND_LAMBDA){ set_local_variable(inst.result, xnew<Lambda>(outer, ff().self(), code(), info)); }
			XTAL_CASE(KIND_METHOD){ set_local_variable(inst.result, xnew<Method>(outer, code(), info)); }
			XTAL_CASE(KIND_FIBER){ set_local_variable(inst.result, xnew<Fiber>(outer, ff().self(), code(), info)); }
		}
		XTAL_VM_CONTINUE(pc + end);
}

const inst_t* VMachine::FunInstMakeInstanceVariableAccessor(const inst_t* pc){
		XTAL_VM_DEF_INST(InstMakeInstanceVariableAccessor);
		XTAL_VM_FUN;
		AnyPtr ret;
		switch(inst.type){
			XTAL_NODEFAULT;
			XTAL_CASE(0){ ret = XNew<InstanceVariableGetter>(inst.number, code()->class_info(inst.info_number)); }
			XTAL_CASE(1){ ret = XNew<InstanceVariableSetter>(inst.number, code()->class_info(inst.info_number)); }
		}
		set_local_variable(inst.result, ret);
		XTAL_VM_CONTINUE(pc + inst.ISIZE); 
}

const inst_t* VMachine::FunInstTryBegin(const inst_t* pc){
		XTAL_VM_DEF_INST(InstTryBegin);
		XTAL_VM_FUN;
		//FunFrame& f = ff();
		ExceptFrame& ef = except_frames_.push();
		ef.info = code()->except_info(inst.info_number);
		ef.fun_frame_size = fun_frames_.size();
		ef.stack_size = stack_.size();
		ef.scope_size = scopes_.size();
		ef.variables_top = variables_top();
		XTAL_VM_CONTINUE(pc + inst.ISIZE);
}

const inst_t* VMachine::FunInstAssert(const inst_t* pc){
		XTAL_VM_DEF_INST(InstAssert);
		XTAL_VM_FUN;
		set_except_x(cpp_class<AssertionFailed>()->call(ptr_cast<String>(local_variable(inst.message))));
		breakpoint_hook(pc, fun(), BREAKPOINT_ASSERT);

		if(except_[0]){
			XTAL_VM_THROW_EXCEPT(except_[0]);
		}

		XTAL_VM_CONTINUE(pc + inst.ISIZE);
}

//}}FUNS}

#undef XTAL_VM_NODEFAULT
#undef XTAL_VM_CASE_FIRST
#undef XTAL_VM_CASE
#undef XTAL_VM_SWITCH
#undef XTAL_VM_DEF_INST
#undef XTAL_VM_CONTINUE
#undef XTAL_VM_CONTINUE0
#undef XTAL_VM_RETURN

#undef XTAL_VM_EXCEPT
#undef XTAL_VM_CHECK_EXCEPT_PC
#undef XTAL_VM_THROW_EXCEPT
#undef XTAL_VM_CHECK_EXCEPT

#undef XTAL_CHECK_YIELD

//#undef inst

}//namespace

