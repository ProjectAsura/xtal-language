#include "xtal.h"
#include "xtal_bind.h"
#include "xtal_macro.h"

namespace xtal{

namespace{

void filelocal_check_implicit_lookup(const AnyPtr& a){
	if(CodePtr code = ptr_cast<Code>(a->member(Xid(code)))){
		code->check_implicit_lookup();
	}
}

void Class_inherit(const ClassPtr& cls, const ClassPtr cls2){
	cls->inherit(cls2);
}

}

Code::Code()
	:source_file_name_(XTAL_STRING("<noname>")){
	set_singleton();
	set_object_temporary_name(Xid(filelocal));
	set_object_force(500);
	inherit(builtin());

	def_method(Xid(inherit), &Class_inherit);
	def_method(Xid(check_implicit_lookup), &filelocal_check_implicit_lookup);
	def(Xid(filelocal), to_smartptr(this));

	identifier_table_ = xnew<Array>();
	value_table_ = xnew<Array>();

	first_fun_ = xnew<Method>(nul<Frame>(), to_smartptr(this), (FunInfo*)0);
}

Code::~Code(){

}

bool Code::set_lineno_info(uint_t line){
	if(!lineno_table_.empty() && lineno_table_.back().lineno==line)
		return false;
	LineNumberInfo lnt={(u16)code_.size(), (u16)line, 0, 0};
	lineno_table_.push_back(lnt);
	return true;
}
	
int_t Code::final_lineno(){
	if(lineno_table_.empty())
		return 0;
	return lineno_table_.back().lineno;
}

int_t Code::compliant_lineno(const inst_t* p){
	if(LineNumberInfo* lni = compliant_lineno_info(p)){
		return lni->lineno;
	}
	return 0;
}

const inst_t* Code::compliant_pc(int_t lineno){
	int_t nearv = 0xffffff;
	int_t neari = -1;
	for(uint_t i=0; i<lineno_table_.size(); ++i){
		int_t diff = lineno_table_[i].lineno - lineno;
		if(diff>=0 && diff<nearv){
			nearv = diff;
			neari = i;
		}
	}

	return neari<0 ? 0 : data() + lineno_table_[neari].start_pc;
}

Code::LineNumberInfo* Code::compliant_lineno_info(const inst_t* p){
	if(!lineno_table_.empty()){
		LineNumberInfo* begin = &lineno_table_[0];
		LineNumberInfo* end = begin+lineno_table_.size();
		LineNumberInfo* it=
			std::upper_bound(
				begin,
				end,
				static_cast<int_t>(p-data()),
				LineNumberCmp()
			);

		if(it!=end){
			if(it==begin){
				return &*it;
			}
			--it;
			return &*it;
		}
	}

	return 0;
}

void Code::rawcall(const VMachinePtr& vm){
	vm->set_arg_this(to_smartptr(this));
	first_fun_->rawcall(vm);
}

void Code::find_near_variable_inner(const IDPtr& primary_key, const ScopeInfo& info, IDPtr& pick, int_t& minv){
	for(uint_t j=0; j<info.variable_size; ++j){
		IDPtr id = identifier(info.variable_identifier_offset+j);
		int_t dist = edit_distance(primary_key, id);
		if(dist!=0 && dist<minv){
			minv = dist;
			pick = id;
		}
	}
}
	
IDPtr Code::find_near_variable(const IDPtr& primary_key){
	int_t minv = 0xffffff;
	IDPtr pick;

	if(const ClassPtr& klass = filelocal()){
		pick = klass->find_near_member(primary_key, undefined, minv);
	}

	for(uint_t i=0; i<xfun_info_table_.size(); ++i){
		find_near_variable_inner(primary_key, xfun_info_table_[i], pick, minv);
	}

	for(uint_t i=0; i<scope_info_table_.size(); ++i){
		find_near_variable_inner(primary_key, scope_info_table_[i], pick, minv);
	}

	for(uint_t i=0; i<class_info_table_.size(); ++i){
		find_near_variable_inner(primary_key, class_info_table_[i], pick, minv);
	}

	return pick;
}

void Code::check_implicit_lookup(){
	ArrayPtr ary;
	for(uint_t i=0; i<implicit_table_.size(); ++i){
		const IDPtr& id = unchecked_ptr_cast<ID>(identifier_table_->at(implicit_table_[i].id));
		const AnyPtr& ret = member(id);
		if(raweq(undefined, ret)){
			if(!ary){
				ary = xnew<Array>();
			}

			ary->push_back(Xf("%s(%d)")->call(filelocal_unsupported_error(to_smartptr(this), id), implicit_table_[i].lineno));
		}
	}

	if(ary){
		XTAL_SET_EXCEPT(cpp_class<RuntimeError>()->call(Xt("XRE1030")->call(Named(Xid(name), ary))));
	}
}

StringPtr Code::inspect(){

#ifdef XTAL_DEBUG

	MemoryStreamPtr ms(xnew<MemoryStream>());

	ms->put_s(XTAL_STRING("identifier_table\n"));
	for(uint_t i=0; i<identifier_table_->size(); ++i){
		Xf("\t%04d:%s\n")->call(i, identifier_table_->at(i));
		ms->put_s(Xf("\t%04d:%s\n")->call(i, identifier_table_->at(i))->to_s());
	}

	ms->put_s(XTAL_STRING("value_table\n"));
	for(uint_t i=0; i<value_table_->size(); ++i){
		ms->put_s(Xf("\t%04d:%s\n")->call(i, value_table_->at(i))->to_s());
	}
	
	ms->put_s(XTAL_STRING("\n"));
	ms->put_s(inspect_range(0, size()));

	ms->seek(0);
	return ms->get_s(ms->size());
	
#endif

	return empty_string;
}

StringPtr Code::inspect_range(int_t start, int_t end){
	return xtal::inspect_range(to_smartptr(this), data()+start, data()+end);
}

}
