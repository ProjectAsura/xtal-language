#include "xtal.h"
#include "xtal_macro.h"

namespace xtal{

ZipIter::ZipIter(const VMachinePtr& vm){
	next = xnew<Array>(vm->ordered_arg_count());
	for(int_t i = 0, len = next->size(); i<len; ++i){
		next->set_at(i, vm->arg(i));
	}
}

void ZipIter::common(const VMachinePtr& vm, const IDPtr& id){
	bool all = true;
	value = xnew<MultiValue>(next->size());
	for(int_t i = 0, len = next->size(); i<len; ++i){
		vm->setup_call(2);
		next->at(i)->rawsend(vm, id);
		next->set_at(i, vm->result(0));
		value->set_at(i, vm->result(1));
		vm->cleanup_call();
		if(!next->at(i))
			all = false;
	}
	if(all){
		vm->return_result(from_this(this), value);
	}
	else{
		vm->return_result(null, null);
	}
}

void ZipIter::block_first(const VMachinePtr& vm){
	common(vm, Xid(block_first));
}

void ZipIter::block_next(const VMachinePtr& vm){
	common(vm, Xid(block_next));
}

void ZipIter::block_break(const VMachinePtr& vm){
	IDPtr id = Xid(block_break);
	for(int_t i = 0, len = next->size(); i<len; ++i){
		vm->setup_call(0);
		next->at(i)->rawsend(vm, id);
		if(!vm->processed()){
			vm->return_result();	
		}
		vm->cleanup_call();
	}
	vm->return_result();
}

void ZipIter::visit_members(Visitor& m){
	Base::visit_members(m);
	m & next & value;
}

void DelegateToIterator::rawcall(const VMachinePtr& vm){
	vm->get_arg_this()->send(Xid(each))->rawsend(vm, member_);
}

void IteratorClass::def(const IDPtr& primary_key, const AnyPtr& value, const AnyPtr& secondary_key, int_t accessibility){
	Class::def(primary_key, value, secondary_key, accessibility);
	if(rawne(Xid(p), primary_key) && rawne(Xid(each), primary_key)){
		Iterable()->def(primary_key, xnew<DelegateToIterator>(primary_key), secondary_key, accessibility);
	}
}

void block_break(AnyPtr& target){
	if(target){
		const VMachinePtr& vm = vmachine();
		vm->setup_call(0);
		target->rawsend(vm, Xid(block_break));
		if(!vm->processed()){
			vm->return_result();
		}
		vm->cleanup_call();
	}
}

bool block_next(BlockValueHolder1& holder, bool first){
	if(holder.it){
		if(!holder.it->block_next_direct(holder.values[0])){
			holder.target = null;
		}
	}
	else{
		const VMachinePtr& vm = vmachine();
		vm->setup_call(2);
		holder.target->rawsend(vm, first ? Xid(block_first) : Xid(block_next));
		holder.target = vm->result(0);
		holder.values[0] = vm->result(1);
		vm->cleanup_call();
	}
	return holder.target;
}

bool block_next(BlockValueHolder2& holder, bool first){
	if(holder.it){
		if(!holder.it->block_next_direct(holder.values[0], holder.values[1])){
			holder.target = null;
		}
	}
	else{
		const VMachinePtr& vm = vmachine();
		vm->setup_call(3);
		holder.target->rawsend(vm, first ? Xid(block_first) : Xid(block_next));
		holder.target = vm->result(0);
		holder.values[0] = vm->result(1);
		holder.values[1] = vm->result(2);
		vm->cleanup_call();
	}
	return holder.target;
}

bool block_next(BlockValueHolder3& holder, bool first){
	const VMachinePtr& vm = vmachine();
	vm->setup_call(4);
	holder.target->rawsend(vm, first ? Xid(block_first) : Xid(block_next));
	holder.target = vm->result(0);
	holder.values[0] = vm->result(1);
	holder.values[1] = vm->result(2);
	holder.values[2] = vm->result(3);
	vm->cleanup_call();
	return holder.target;
}

BlockValueHolder1::BlockValueHolder1(const AnyPtr& tar, bool& not_end)
	:target(tar){
	not_end = tar;
	const ArrayPtr& array = ptr_as<Array>(tar);
	if(array){ it = unchecked_ptr_cast<ArrayIter>(array->each()); }
	else{ 
		it = ptr_as<ArrayIter>(tar); 
	}
}

BlockValueHolder1::BlockValueHolder1(const ArrayPtr& tar, bool& not_end)
	:target(tar){
	not_end = tar;
	const ArrayPtr& array = tar;
	if(array){ it = unchecked_ptr_cast<ArrayIter>(array->each()); }
}

BlockValueHolder1::~BlockValueHolder1(){ 
	block_break(target); 
}
	
BlockValueHolder2::BlockValueHolder2(const AnyPtr& tar, bool& not_end)
	:target(tar){
	not_end = tar;
	const MapPtr& map = ptr_as<Map>(tar);
	if(map){ it = unchecked_ptr_cast<MapIter>(map->each()); }
	else{ 
		it = ptr_as<MapIter>(tar); 
	}
}

BlockValueHolder2::BlockValueHolder2(const MapPtr& tar, bool& not_end)
	:target(tar){
	not_end = tar;
	const MapPtr& map = tar;
	if(map){ it = unchecked_ptr_cast<MapIter>(map->each()); }
}

BlockValueHolder2::~BlockValueHolder2(){ 
	block_break(target); 
}

BlockValueHolder3::BlockValueHolder3(const AnyPtr& tar, bool& not_end)
	:target(tar){
	not_end = tar;
}

BlockValueHolder3::~BlockValueHolder3(){ 
	block_break(target); 
}

}
