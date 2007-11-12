
#pragma once

namespace xtal{

class InstanceVariables{
public:

	struct uninit_t{};

	InstanceVariables(uninit_t){}

	InstanceVariables()		
		:variables_(xnew<Array>()){
		VariablesInfo vi;
		vi.core = 0;
		vi.pos = 0;
		variables_info_.push(vi);
	}
			
	~InstanceVariables(){}
		
	void init_variables(ClassCore* core){
		VariablesInfo vi;
		vi.core = core;
		vi.pos = (int_t)variables_->size();
		variables_->resize(vi.pos+core->instance_variable_size);
		variables_info_.push(vi);
	}

	const AnyPtr& variable(int_t index, ClassCore* core){
		return variables_->at(find_core(core) + index);
	}

	void set_variable(int_t index, ClassCore* core, const AnyPtr& value){
		variables_->set_at(find_core(core) + index, value);
	}

	int_t find_core(ClassCore* core){
		VariablesInfo& info = variables_info_.top();
		if(info.core == core)
			return info.pos;
		return find_core_inner(core);
	}

	bool is_included(ClassCore* core){
		VariablesInfo& info = variables_info_.top();
		if(info.core == core)
			return true;
		for(int_t i = 1, size = (int_t)variables_info_.size(); i<size; ++i){
			if(variables_info_[i].core==core){
				std::swap(variables_info_[0], variables_info_[i]);
				return true;
			}	
		}
		return false;
	}

	int_t find_core_inner(ClassCore* core);

	bool empty(){
		return variables_->empty();
	}

	void visit_members(Visitor& m){
		m & variables_;
	}

protected:
	
	struct VariablesInfo{
		ClassCore* core;
		int_t pos;
	};

	PODStack<VariablesInfo> variables_info_;
	ArrayPtr variables_;
};

class EmptyInstanceVariables : public InstanceVariables{
public:
	EmptyInstanceVariables():InstanceVariables(uninit_t()){}

	void init(){
		VariablesInfo vi;
		vi.core = 0;
		vi.pos = 0;
		variables_info_.push(vi);
	}

	void uninit(){
		variables_info_.release();
	}	
};
	
class Frame : public HaveName{
public:
	
	Frame(const FramePtr& outer, const CodePtr& code, BlockCore* core);
	
	Frame();
		
	~Frame();

public:
	
	/**
	* @brief $B30B&$N%9%3!<%W$rI=$9(BFrame$B%*%V%8%'%/%H$rJV$9!#(B
	*
	*/
	const FramePtr& outer(){ 
		return outer_; 
	}

	const CodePtr& code(){ 
		return code_; 
	}

	/**
	* @brief $B%j%F%i%k;~$KDj5A$5$l$?MWAG$N?t$rJV$9!#(B
	*
	*/
	int_t block_size(){ 
		return core_->variable_size; 
	}

	/**
	* @brief i$BHVL\$N%a%s%P!<$r%@%$%l%/%H$K<hF@!#(B
	*
	*/
	const AnyPtr& member_direct(int_t i){
		return members_->at(i);
	}

	/**
	* @brief i$BHVL\$N%a%s%P!<$r%@%$%l%/%H$K@_Dj!#(B
	*
	*/
	void set_member_direct(int_t i, const AnyPtr& value){
		members_->set_at(i, value);
	}

	void set_class_member(int_t i, const IDPtr& primary_key, const AnyPtr& value, const AnyPtr& secondary_key, int_t accessibility);
		
	void set_object_name(const StringPtr& name, int_t force, const AnyPtr& parent);

	virtual StringPtr object_name();

public:

	/**
	* @brief $B%a%s%P$,3JG<$5$l$?!"(BIterator$B$rJV$9(B
	*
	* @code
	* Xfor2(key, value, frame.members()){
	*   puts(Xf("%s %s")(key, value).to_s().c_str());
	* }
	* @endcode
	*/
	AnyPtr members();

protected:

	void make_map_members();

	friend class MembersIter;

	FramePtr outer_;
	CodePtr code_;
	BlockCore* core_;
	
	ArrayPtr members_;

	struct Key{
		IDPtr primary_key;
		AnyPtr secondary_key;

		friend void visit_members(Visitor& m, const Key& a){
			m & a.primary_key & a.secondary_key;
		}
	};

	struct Value{
		u16 num;
		u16 flags;

		friend void visit_members(Visitor& m, const Value&){}
	};

	struct Fun{
		static uint_t hash(const Key& key){
			return (rawvalue(key.primary_key)>>3) ^ rawvalue(key.secondary_key);
		}

		static bool eq(const Key& a, const Key& b){
			return raweq(a.primary_key, b.primary_key) && raweq(a.secondary_key, b.secondary_key);
		}
	};

	typedef Hashtable<Key, Value, Fun> map_t; 
	map_t table_;

	map_t* map_members_;


	virtual void visit_members(Visitor& m){
		HaveName::visit_members(m);
		m & outer_ & code_ & members_;
		if(map_members_){
			m & *map_members_;
		}
	}
};

class Class : public Frame{
public:

	Class(const char* name = "");

	Class(const FramePtr& outer, const CodePtr& code, ClassCore* core);

public:
	
	/**
	* @brief $B?7$7$$%a%s%P$rDj5A$9$k(B
	*
	* @param name $B?7$7$/Dj5A$9$k%a%s%P$NL>A0(B
	*/
	virtual void def(const IDPtr& primary_key, const AnyPtr& value, const AnyPtr& secondary_key = null, int_t accessibility = KIND_PUBLIC);

	/**
	* @brief $B%a%s%P$r<h$j=P$9(B
	* $B2D?(@-$r9MN8$7$F<h$j=P$9(B
	*
	* @param name $B<h$j=P$7$?$$%a%s%P$NL>A0(B
	* @param self $B2D;k@-$rH=Dj$9$k$?$a$N%*%V%8%'%/%H(B
	*/
	virtual const AnyPtr& do_member(const IDPtr& primary_key, const AnyPtr& secondary_key = null, const AnyPtr& self = null, bool inherited_too = true);

	/**
	* @brief $B%a%s%P$r:F@_Dj$9$k(B
	* Xtal$B%l%Y%k$G$O6X;_$5$l$F$$$kA`:n$@$,!"(BC++$B%l%Y%k$G$O2DG=$K$7$F$*$/(B
	*
	* @param name $B:F@_Dj$7$?$$%a%s%P$NL>A0(B
	*/
	void set_member(const IDPtr& primary_key, const AnyPtr& value, const AnyPtr& secondary_key);

	/**
	* @brief Mix-in$B$9$k(B
	*
	* @param md Mix-in$B$9$k%/%i%9%*%V%8%'%/%H(B
	*/
	void inherit(const ClassPtr& md);

	/**
	* @brief Mix-in$B$9$k(B
	*
	* @param md Mix-in$B$9$k%/%i%9%*%V%8%'%/%H(B
	*/
	void inherit_strict(const ClassPtr& md);

	/**
	* @brief Mix-in$B$5$l$F$$$k$+D4$Y$k(B
	*
	* @param md Mix-in$B$5$l$F$$$kD4$Y$?$$%/%i%9%*%V%8%'%/%H(B
	*/
	bool is_inherited(const AnyPtr& md);

	/**
	* @brief C++$B$N%/%i%9$,(BMix-in$B$5$l$F$$$k$+D4$Y$k(B
	*
	*/
	bool is_inherited_cpp_class();

	/**
	* @brief Mix-in$B$5$l$F$$$k%/%i%9$N(BIterator$B$rJV$9(B
	*
	*/
	AnyPtr inherited_classes();

	/**
	* @brief $B4X?t$rDj5A$9$k(B
	*
	* cls->fun("name", &foo); $B$O(B cls->def("name", xtal::fun(&foo)); $B$HF10l(B
	*/
	template<class Fun, class Policy>
	const CFunPtr& fun(const IDPtr& primary_key, Fun f, const AnyPtr& secondary_key, int_t accessibility, const Policy& policy){
		return def_and_return(primary_key, xtal::fun_impl(f, policy), secondary_key, accessibility);
	}

	/**
	* @brief $B4X?t$rDj5A$9$k(B
	*
	* cls->fun("name", &foo); $B$O(B cls->def("name", xtal::fun(&foo)); $B$HF10l(B
	*/
	template<class Fun>
	const CFunPtr& fun(const IDPtr& primary_key, Fun f, const AnyPtr& secondary_key = null, int_t accessibility = KIND_PUBLIC){
		return fun(primary_key, f, secondary_key, accessibility, result);
	}

	/**
	* @brief $B4X?t$rDj5A$9$k(B
	*
	* cls->method("name", &foo); $B$O(B cls->def("name", xtal::method(&foo)); $B$HF10l(B
	*/
	template<class Fun, class Policy>
	const CFunPtr& method(const IDPtr& primary_key, Fun f, const AnyPtr& secondary_key, int_t accessibility, const Policy& policy){
		return def_and_return(primary_key, method_impl(f, policy), secondary_key, accessibility);
	}

	/**
	* @brief $B4X?t$rDj5A$9$k(B
	*
	* cls->method("name", &Klass::foo); $B$O(B cls->def("name", xtal::method(&Klass::foo)); $B$HF10l(B
	*/
	template<class Fun>
	const CFunPtr& method(const IDPtr& primary_key, Fun f, const AnyPtr& secondary_key = null, int_t accessibility = KIND_PUBLIC){
		return method(primary_key, f, secondary_key, accessibility, result);
	}

	
	/**
	* @brief $B%a%s%PJQ?t$X$N%]%$%s%?$+$i%2%C%?!<$r@8@.$7!"Dj5A$9$k(B
	*
	*/
	template<class T, class U, class Policy>
	const CFunPtr& getter(const IDPtr& primary_key, T U::* v, const AnyPtr& secondary_key, int_t accessibility, const Policy& policy){
		return def_and_return(primary_key, getter_impl(v, policy), secondary_key, accessibility);
	}
	
	/**
	* @brief $B%a%s%PJQ?t$X$N%]%$%s%?$+$i%;%C%?!<$r@8@.$7!"Dj5A$9$k(B
	*
	* Xtal$B$G$O!"(Bobj.name = 10; $B$H$9$k$K$O(Bset_name$B$H(Bset_$B$rA0CV$7$?%a%=%C%I$rDj5A$9$kI,MW$,$"$k$?$a!"(B
	* $BC1=c$J%;%C%?!<$rDj5A$7$?$$>l9g!"(Bset_xxx$B$H$9$k$3$H$rK:$l$J$$$3$H!#(B
	*/
	template<class T, class U, class Policy>
	const CFunPtr& setter(const IDPtr& primary_key, T U::* v, const AnyPtr& secondary_key, int_t accessibility, const Policy& policy){
		return def_and_return(primary_key, setter_impl(v, policy), secondary_key, accessibility);
	}
	
	/**
	* @brief $B%a%s%PJQ?t$X$N%]%$%s%?$+$i%2%C%?!<!"%;%C%?!<$rN>J}@8@.$7!"Dj5A$9$k(B
	*
	* cls->getter(name, var, policy);
	* cls->setter(StringPtr("set_")->cat(name), v, policy);
	* $B$HEy$7$$(B	
	*/	
	template<class T, class U, class Policy>
	void var(const IDPtr& primary_key, T U::* v, const AnyPtr& secondary_key, int_t accessibility, const Policy& policy){
		getter(primary_key, v, secondary_key, accessibility, policy);
		setter(String("set_").cat(primary_key), v, secondary_key, accessibility, policy);
	}
	
	/**
	* @brief $B%a%s%PJQ?t$X$N%]%$%s%?$+$i%2%C%?!<$r@8@.$7!"Dj5A$9$k(B
	*
	*/
	template<class T, class U>
	const CFunPtr& getter(const IDPtr& primary_key, T U::* v, const AnyPtr& secondary_key = null, int_t accessibility = KIND_PUBLIC){
		return getter(primary_key, v, secondary_key, accessibility, result);
	}
	
	/**
	* @brief $B%a%s%PJQ?t$X$N%]%$%s%?$+$i%;%C%?!<$r@8@.$7!"Dj5A$9$k(B
	*
	*/
	template<class T, class U>
	const CFunPtr& setter(const IDPtr& primary_key, T U::* v, const AnyPtr& secondary_key = null, int_t accessibility = KIND_PUBLIC){
		return setter(primary_key, v, secondary_key, accessibility, result);
	}
	
	/**
	* @brief $B%a%s%PJQ?t$X$N%]%$%s%?$+$i%2%C%?!<!"%;%C%?!<$rN>J}@8@.$7!"Dj5A$9$k(B
	*
	* cls->getter(name, v);
	* cls->setter(StringPtr("set_")->cat(name), v);
	* $B$HEy$7$$(B	
	*/	
	template<class T, class U>
	void var(const IDPtr& primary_key, T U::* v, const AnyPtr& secondary_key = null, int_t accessibility = KIND_PUBLIC){
		var(primary_key, v, secondary_key, accessibility, result);
	}

	/**
	* @brief 2$B=E%G%#%9%Q%C%A%a%=%C%I$rDj5A$9$k!#(B
	*/
	void dual_dispatch_method(const IDPtr& primary_key, int_t accessibility = KIND_PUBLIC){
		def(primary_key, xtal::dual_dispatch_method(primary_key), null, accessibility);
	}

	/**
	* @brief 2$B=E%G%#%9%Q%C%A4X?t$rDj5A$9$k!#(B
	*/
	void dual_dispatch_fun(const IDPtr& primary_key, int_t accessibility = KIND_PUBLIC){
		def(primary_key, xtal::dual_dispatch_fun(from_this(this), primary_key), null, accessibility);
	}

public:

	virtual void call(const VMachinePtr& vm);
	
	virtual void s_new(const VMachinePtr& vm);

	void init_instance(const AnyPtr& self, const VMachinePtr& vm);
	
	const AnyPtr& any_member(const IDPtr& primary_key, const AnyPtr& secondary_key);
	
	const AnyPtr& bases_member(const IDPtr& primary_key);

	const AnyPtr& find_member(const IDPtr& primary_key, const AnyPtr& secondary_key = null, const AnyPtr& self = null, bool inherited_too = true);

	ClassCore* core(){
		return (ClassCore*)core_;
	}
	
	struct cpp_class_t{};

	Class(cpp_class_t, const char* name = "");

	bool is_cpp_class(){
		return is_cpp_class_;
	}

protected:

	const CFunPtr& def_and_return(const IDPtr& primary_key, const CFunEssence& cfun, const AnyPtr& secondary_key = null, int_t accessibility = KIND_PUBLIC);

	const CFunPtr& def_and_return(const IDPtr& primary_key, const CFunPtr& cfun, const AnyPtr& secondary_key = null, int_t accessibility = KIND_PUBLIC){
		return static_ptr_cast<CFun>(def2(primary_key, cfun, secondary_key, accessibility));
	}

	const AnyPtr& def2(const IDPtr& primary_key, const AnyPtr& value, const AnyPtr& secondary_key = null, int_t accessibility = KIND_PUBLIC);


	ArrayPtr mixins_;
	bool is_cpp_class_;

	virtual void visit_members(Visitor& m){
		Frame::visit_members(m);
		m & mixins_;
	}

};

class CppClass : public Class{
public:
		
	CppClass(const char* name = "");

public:

	virtual void call(const VMachinePtr& vm);

	virtual void s_new(const VMachinePtr& vm);
};

class Lib : public Class{
public:

	Lib();

	Lib(const ArrayPtr& path);
	
	virtual const AnyPtr& do_member(const IDPtr& primary_key, const AnyPtr& secondary_key, const AnyPtr& self, bool inherited_too = true);

	virtual void def(const IDPtr& primary_key, const AnyPtr& value, const AnyPtr& secondary_key, int_t accessibility);

	void append_load_path(const StringPtr& path){
		load_path_list_->push_back(path);
	}

private:

	const AnyPtr& rawdef(const IDPtr& primary_key, const AnyPtr& value, const AnyPtr& secondary_key);

	StringPtr join_path(const StringPtr& sep);

private:

	ArrayPtr load_path_list_;
	ArrayPtr path_;

	virtual void visit_members(Visitor& m){
		Class::visit_members(m);
		m & path_ & load_path_list_;
	}
};

class Singleton : public Class{
public:

	Singleton(const char* name = "");

	Singleton(const FramePtr& outer, const CodePtr& code, ClassCore* core);
	
public:

	void init_singleton(const VMachinePtr& vm);

	// $B%/%i%9$N@_Dj$O%9%k!<$9$k(B
	void set_class(const ClassPtr&){}

	virtual void call(const VMachinePtr& vm);
	
	virtual void s_new(const VMachinePtr& vm);
};



struct CppClassHolderList{
	ClassPtr value;
	CppClassHolderList* next;
};

void chain_cpp_class(CppClassHolderList& link);
const ClassPtr& new_cpp_class_impl(CppClassHolderList& list, const char* name);

// C++$B$N%/%i%9$NJ];}$N$?$a$N%/%i%9(B
template<class T>
struct CppClassHolder{
	static CppClassHolderList value;
};

template<class T>
CppClassHolderList CppClassHolder<T>::value;


template<class T>
inline const ClassPtr& new_cpp_class(const char* name){
	return new_cpp_class_impl(CppClassHolder<T>::value, name);
}

template<class T>
inline bool exists_cpp_class(){
	return CppClassHolder<T>::value.value;
}

template<class T>
inline const ClassPtr& get_cpp_class(){
	XTAL_ASSERT(exists_cpp_class<T>());
	return CppClassHolder<T>::value.value;
}

template<class T>
void set_cpp_class(const ClassPtr& cls){
	if(!CppClassHolder<T>::value.value){
		chain_cpp_class(CppClassHolder<T>::value);
	}
	CppClassHolder<T>::value.value = cls;
}

}
