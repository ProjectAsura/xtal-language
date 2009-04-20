/** \file src/xtal/xtal_objectspace.h
* \brief src/xtal/xtal_objectspace.h
*/

#ifndef XTAL_OBJECTSPACE_H_INCLUDE_GUARD
#define XTAL_OBJECTSPACE_H_INCLUDE_GUARD

#pragma once

namespace xtal{

class ObjectSpace{
public:

	void initialize();

	void uninitialize();

	void enable_gc();

	void disable_gc();

	void gc();

	void full_gc();

	void register_gc(RefCountingBase* p);

	void register_gc_observer(GCObserver* p);

	void unregister_gc_observer(GCObserver* p);

	bool exists_cpp_class(uint_t key){
		return class_table_[key]!=0;
	}

	const ClassPtr& cpp_class(uint_t key){
		return to_smartptr(class_table_[key]);
	}

	void set_cpp_class(const ClassPtr& cls, uint_t key){
		int_t index = key;
		
		if(class_table_[index]->prebinder()){
			cls->set_prebinder(class_table_[index]->prebinder());
		}

		if(class_table_[index]->binder()){
			cls->set_binder(class_table_[index]->binder());
		}

		if(class_table_[index]){
			class_table_[index]->dec_ref_count();
		}
		class_table_[index] = cls.get();
		class_table_[index]->inc_ref_count();
	}

	void* cpp_var(uint_t key){
		return var_table_[key].var;
	}

	void set_cpp_var(void* var, void (*deleter)(void*), uint_t key){
		int_t index = key;
		var_table_[index].var = var;
		var_table_[index].deleter = deleter;
	}

	void print_alive_objects();

	uint_t alive_object_count();

	RefCountingBase* alive_object(uint_t i);

private:

	void expand_objects_list();

	RefCountingBase** objects_begin_ ;
	RefCountingBase** objects_current_;
	RefCountingBase** objects_end_;

	RefCountingBase*** objects_list_begin_;
	RefCountingBase*** objects_list_current_;
	RefCountingBase*** objects_list_end_;

	GCObserver** gcobservers_begin_;
	GCObserver** gcobservers_current_;
	GCObserver** gcobservers_end_;

	uint_t objects_count_;
	uint_t prev_objects_count_;

	uint_t cycle_count_;

	PODArrayList<Class*> class_table_;

	struct VarInfo{
		void* var;
		void (*deleter)(void*);
	};

	PODArrayList<VarInfo> var_table_;
};

}

#endif // XTAL_OBJECTSPACE_H_INCLUDE_GUARD