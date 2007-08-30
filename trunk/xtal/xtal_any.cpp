
#include <vector>
#include <iostream>
#include <fstream>

#include "xtal.h"

#include "xtal_fwd.h"
#include "xtal_any.h"
#include "xtal_frame.h"
#include "xtal_fun.h"
#include "xtal_string.h"
#include "xtal_code.h"
#include "xtal_lexer.h"
#include "xtal_frame.h"
#include "xtal_macro.h"
#include "xtal_stream.h"
#include "xtal_vmachine.h"

namespace xtal{

void InitAny(){
	{
		ClassPtr p = new_cpp_class<Any>("Any");
		p->method("class", &Any::get_class);
		p->method("get_class", &Any::get_class);
		p->method("object_name", &Any::object_name);
	}

	builtin()->def("Any", get_cpp_class<Any>());
}

AnyPtr operator +(const AnyPtr& a, const AnyPtr& b){ return a->send(Xid(op_add), b); }
AnyPtr operator -(const AnyPtr& a, const AnyPtr& b){ return a->send(Xid(op_sub), b); }
AnyPtr operator *(const AnyPtr& a, const AnyPtr& b){ return a->send(Xid(op_mul), b); }
AnyPtr operator /(const AnyPtr& a, const AnyPtr& b){ return a->send(Xid(op_div), b); }
AnyPtr operator %(const AnyPtr& a, const AnyPtr& b){ return a->send(Xid(op_mod), b); }
AnyPtr operator |(const AnyPtr& a, const AnyPtr& b){ return a->send(Xid(op_or), b); }
AnyPtr operator &(const AnyPtr& a, const AnyPtr& b){ return a->send(Xid(op_and), b); }
AnyPtr operator ^(const AnyPtr& a, const AnyPtr& b){ return a->send(Xid(op_xor), b); }
AnyPtr operator >>(const AnyPtr& a, const AnyPtr& b){ return a->send(Xid(op_shr), b); }
AnyPtr operator <<(const AnyPtr& a, const AnyPtr& b){ return a->send(Xid(op_shl), b); }

AnyPtr operator ==(const AnyPtr& a, const AnyPtr& b){ 
	if(raweq(a, b))
		return true;

	const VMachinePtr& vm = vmachine();
	vm->setup_call(1, b);
	a->rawsend(vm, Xid(op_eq));
	if(vm->processed() && vm->result()){
		vm->cleanup_call();
		return true;
	}
	vm->cleanup_call();
	return false;
}

AnyPtr operator !=(const AnyPtr& a, const AnyPtr& b){ return !(a==b); }
AnyPtr operator <(const AnyPtr& a, const AnyPtr& b){ return a->send(Xid(op_lt), b); }
AnyPtr operator >(const AnyPtr& a, const AnyPtr& b){ return b<a; }
AnyPtr operator <=(const AnyPtr& a, const AnyPtr& b){ return !(b<a); }
AnyPtr operator >=(const AnyPtr& a, const AnyPtr& b){ return !(a<b); }

AnyPtr& operator +=(AnyPtr& a, const AnyPtr& b){ a = a->send(Xid(op_add_assign), b); return a; }
AnyPtr& operator -=(AnyPtr& a, const AnyPtr& b){ a = a->send(Xid(op_sub_assign), b); return a; }
AnyPtr& operator *=(AnyPtr& a, const AnyPtr& b){ a = a->send(Xid(op_mul_assign), b); return a; }
AnyPtr& operator /=(AnyPtr& a, const AnyPtr& b){ a = a->send(Xid(op_div_assign), b); return a; }
AnyPtr& operator %=(AnyPtr& a, const AnyPtr& b){ a = a->send(Xid(op_mod_assign), b); return a; }
AnyPtr& operator |=(AnyPtr& a, const AnyPtr& b){ a = a->send(Xid(op_or_assign), b); return a; }
AnyPtr& operator &=(AnyPtr& a, const AnyPtr& b){ a = a->send(Xid(op_and_assign), b); return a; }
AnyPtr& operator ^=(AnyPtr& a, const AnyPtr& b){ a = a->send(Xid(op_xor_assign), b); return a; }
AnyPtr& operator >>=(AnyPtr& a, const AnyPtr& b){ a = a->send(Xid(op_shr_assign), b); return a; }
AnyPtr& operator <<=(AnyPtr& a, const AnyPtr& b){ a = a->send(Xid(op_shl_assign), b); return a; }


Innocence::Innocence(const char_t* str){
	*this = xnew<String>(str);
}

AnyPtr Innocence::operator()() const{
	const VMachinePtr& vm = vmachine();
	vm->setup_call(1);
	ap(*this)->call(vm);
	return vm->result_and_cleanup_call();
}

AnyPtr Any::send(const InternedStringPtr& name) const{
	const VMachinePtr& vm = vmachine();
	vm->setup_call(1);
	rawsend(vm, name);
	return vm->result_and_cleanup_call();
}
const AtProxy& AtProxy::operator =(const AnyPtr& value){
	obj->send(Xid(set_at), key, value);
	return *this;
}

AtProxy Innocence::operator[](const AnyPtr& key) const{
	return AtProxy(ap(*this), key);
}

AtProxy::operator const AnyPtr&(){
	return obj = obj->send(Xid(at), key);
}

const AnyPtr& AtProxy::operator ->(){
	return obj = obj->send(Xid(at), key);
}

const Any& AtProxy::operator *(){
	return *(obj = obj->send(Xid(at), key));
}

struct MemberCacheTable{
	struct Unit{
		uint_t mutate_count;
		uint_t target_class;
		uint_t ns;
		Innocence member_name;
		Innocence member;
	};

	enum{ CACHE_MAX = 512, CACHE_MASK = CACHE_MAX-1 };

	Unit table_[CACHE_MAX];

	int_t hit_;
	int_t miss_;

	MemberCacheTable(){
		hit_ = 0;
		miss_ = 0;
	}

	void print_result(){
		printf("MemberCacheTable hit count=%d, miss count=%d, hit rate=%g, miss rate=%g\n", hit_, miss_, hit_/(float)(hit_+miss_), miss_/(float)(hit_+miss_));
	}

	const AnyPtr& cache(const Innocence& target_class, const InternedStringPtr& member_name, const Innocence& self, const Innocence& ns){
		uint_t itarget_class = rawvalue(target_class);
		uint_t imember_name = rawvalue(member_name);
		uint_t ins = rawvalue(ns);

		uint_t hash = (itarget_class>>3) ^ (imember_name>>2) ^ ins + imember_name ^ type(member_name);
		Unit& unit = table_[hash & CACHE_MASK];
		if(global_mutate_count==unit.mutate_count && itarget_class==unit.target_class && raweq(member_name, unit.member_name) && ins==unit.ns){
			hit_++;
			return ap(unit.member);
		}else{
			miss_++;

			if(type(target_class)!=TYPE_BASE)
				return nop;

			unit.member = pvalue(target_class)->do_member(member_name, ap(self), ap(ns));
			unit.target_class = itarget_class;
			unit.member_name = member_name;
			unit.ns = ins;
			unit.mutate_count = global_mutate_count;
			return ap(unit.member);
		}
	}
};

struct IsCacheTable{
	struct Unit{
		uint_t mutate_count;
		uint_t target_class;
		uint_t klass;
	};

	enum{ CACHE_MAX = 512, CACHE_MASK = CACHE_MAX-1 };

	Unit table_[CACHE_MAX];

	int_t hit_;
	int_t miss_;

	IsCacheTable(){
		hit_ = 0;
		miss_ = 0;
	}

	void print_result(){
		printf("IsCacheTable hit count=%d, miss count=%d, hit rate=%g, miss rate=%g\n", hit_, miss_, hit_/(float)(hit_+miss_), miss_/(float)(hit_+miss_));
	}

	bool cache(const Innocence& target_class, const Innocence& klass){
		uint_t itarget_class = rawvalue(target_class);
		uint_t iklass = rawvalue(klass);

		uint_t hash = (itarget_class>>3) ^ (iklass>>2);
		Unit& unit = table_[hash & CACHE_MASK];

		if(global_mutate_count==unit.mutate_count && itarget_class==unit.target_class && iklass==unit.klass){
			hit_++;
			return true;
		}else{
			miss_++;
			if(static_ptr_cast<Class>(ap(target_class))->is_inherited(static_ptr_cast<Class>(ap(klass)))){
				// キャッシュに保存
				unit.target_class = itarget_class;
				unit.klass = iklass;
				unit.mutate_count = global_mutate_count;
				return true;
			}

			return false;
		}
	}
};

namespace{
	MemberCacheTable member_cache_table;
	IsCacheTable is_cache_table;
}

void print_result_of_cache(){
	member_cache_table.print_result();
	is_cache_table.print_result();
}

const AnyPtr& Any::member(const InternedStringPtr& name, const AnyPtr& self, const AnyPtr& ns) const{
	return member_cache_table.cache(*this, name, self, ns);
}

void Any::def(const InternedStringPtr& name, const AnyPtr& value, int_t accessibility, const AnyPtr& ns) const{
	switch(type(*this)){
		XTAL_DEFAULT;
		XTAL_CASE(TYPE_BASE){
			value->set_object_name(name, object_name_force(), ap(*this));
			pvalue(*this)->def(name, value, accessibility, ns);
		}
	}
}

void Any::rawsend(const VMachinePtr& vm, const InternedStringPtr& name, const AnyPtr& self, const AnyPtr& ns) const{
	const ClassPtr& cls = get_class();
	vm->set_hint(cls, name);
	if(const AnyPtr& ret = member_cache_table.cache(cls, name, self, ns)){
		vm->set_arg_this(ap(*this));
		ret->call(vm);
	}
}

void Any::call(const VMachinePtr& vm) const{
	switch(type(*this)){
		XTAL_DEFAULT{}
		XTAL_CASE(TYPE_BASE){ pvalue(*this)->call(vm); }
	}
}

int_t Any::to_i() const{
	switch(type(*this)){
		XTAL_DEFAULT{ return cast<int_t>((*this).send("to_i")); }
		XTAL_CASE(TYPE_NULL){ return 0; }
		XTAL_CASE(TYPE_INT){ return ivalue(*this); }
		XTAL_CASE(TYPE_FLOAT){ return (int_t)fvalue(*this); }
	}
	return 0;
}

float_t Any::to_f() const{
	switch(type(*this)){
		XTAL_DEFAULT{ return cast<float_t>((*this).send("to_f")); }
		XTAL_CASE(TYPE_NULL){ return 0; }
		XTAL_CASE(TYPE_INT){ return (float_t)ivalue(*this); }
		XTAL_CASE(TYPE_FLOAT){ return fvalue(*this); }
	}
	return 0;
}

StringPtr Any::to_s() const{
	if(const StringPtr& ret = as<StringPtr>(ap(*this))){
		return ret;
	}
	return cast<StringPtr>((*this).send("to_s"));
}

StringPtr Any::object_name() const{
	switch(type(*this)){
		XTAL_NODEFAULT;
		XTAL_CASE(TYPE_NULL){ return xnew<String>("instance of Null"); }
		XTAL_CASE(TYPE_BASE){ return pvalue(*this)->object_name(); }
		XTAL_CASE(TYPE_INT){ return xnew<String>("instance of Int"); }
		XTAL_CASE(TYPE_FLOAT){ return xnew<String>("instance of Float"); }
		XTAL_CASE(TYPE_FALSE){ return xnew<String>("instance of False"); }
		XTAL_CASE(TYPE_TRUE){ return xnew<String>("instance of True"); }
		XTAL_CASE(TYPE_NOP){ return xnew<String>("instance of Nop"); }
		XTAL_CASE(TYPE_SMALL_STRING){ return xnew<String>("instance of String"); }
	}
	return null;	
}

int_t Any::object_name_force() const{
	if(type(*this)==TYPE_BASE){ 
		pvalue(*this)->object_name_force(); 
	}
	return 0;
}
	
void Any::set_object_name(const StringPtr& name, int_t force, const AnyPtr& parent) const{
	if(type(*this)==TYPE_BASE){ 
		pvalue(*this)->set_object_name(name, force, parent); 
	}
}

const ClassPtr& Any::get_class() const{
	switch(type(*this)){
		XTAL_NODEFAULT;
		XTAL_CASE(TYPE_NULL){ return get_cpp_class<Null>(); }
		XTAL_CASE(TYPE_BASE){ return pvalue(*this)->get_class(); }
		XTAL_CASE(TYPE_INT){ return get_cpp_class<Int>(); }
		XTAL_CASE(TYPE_FLOAT){ return get_cpp_class<Float>(); }
		XTAL_CASE(TYPE_FALSE){ return get_cpp_class<False>(); }
		XTAL_CASE(TYPE_TRUE){ return get_cpp_class<True>(); }
		XTAL_CASE(TYPE_NOP){ return get_cpp_class<Nop>(); }
		XTAL_CASE(TYPE_SMALL_STRING){ return get_cpp_class<String>(); }
	}
	return get_cpp_class<Any>();
}

uint_t Any::hashcode() const{
	if(type(*this)==TYPE_BASE){
		return pvalue(*this)->hashcode();
	}
	return (uint_t)rawvalue(*this);
}


bool Any::is(const ClassPtr& klass) const{
	return is_cache_table.cache(get_class(), klass);
}

AnyPtr Any::p() const{
	ap(*this)->send("p");
	return ap(*this);
}

void visit_members(Visitor& m, const AnyPtr& p){
	if(type(p)==TYPE_BASE){
		XTAL_ASSERT((int)pvalue(p)->ref_count() >= -m.value());
		pvalue(p)->add_ref_count(m.value());
	}
}




}
