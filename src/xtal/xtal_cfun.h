
#pragma once

namespace xtal{

class CFun;	

struct Result{
	static void return_result(const VMachinePtr& vm){
		vm->return_result();
	}

	static void return_result2(const VMachinePtr& vm, const AnyPtr& ret, Bool<true>){
		vm->return_result(ret);
	}

	template<class T>
	static void return_result2(const VMachinePtr& vm, const T& ret, Bool<false>){
		vm->return_result(xnew<T>(ret));
	}

	template<class T>
	static void return_result(const VMachinePtr& vm, const T& ret){
		return_result2(vm, ret, Bool<Convertible<T, AnyPtr>::value>());
	}
};

struct ReturnThis{
	static void return_result(const VMachinePtr& vm){
		vm->return_result(vm->get_arg_this());
	}

	template<class T>
	static void return_result(const VMachinePtr& vm, const T&){
		return_result(vm);
	}
};

struct ReturnUndefined{
	static void return_result(const VMachinePtr& vm){
		vm->return_result();
	}

	template<class T>
	static void return_result(const VMachinePtr& vm, const T&){
		return_result(vm);
	}
};


struct ParamInfo{
	Named* params;
	int_t min_param_count;
	int_t max_param_count;
	Innocence fun;
};

struct ParamAndVM{
	ParamAndVM(){}
};

template<class T, int N>
inline typename CastResult<T>::type 
arg_get(const VMachinePtr& vm, const ParamInfo& p){
	Named& temp = p.params[N];
	return arg_cast<T>(vm->arg_default(N, temp.name, temp.value), N, temp.name);
}

namespace detail{

template<class R>
struct fun_R{
	template<class T, class Policy>
	struct fun0{
		static void f(const VMachinePtr& vm, const ParamInfo&, T& fun){
			Policy::return_result(vm, fun(
			));
		}
	};
	
	template<class T, class A0, class Policy>
	struct fun1{
		static void f(const VMachinePtr& vm, const ParamInfo& p, T& fun){
			Policy::return_result(vm, fun(
				arg_get<A0, 0>(vm, p)
			));
		}

		static void f_args(const VMachinePtr& vm, const ParamInfo& p, T& fun){
			Policy::return_result(vm, fun(
				vm
			));
		}
	};

	template<class T, class A0, class A1, class Policy>
	struct fun2{
		static void f(const VMachinePtr& vm, const ParamInfo& p, T& fun){
			Policy::return_result(vm, fun(
				arg_get<A0, 0>(vm, p), 
				arg_get<A1, 1>(vm, p)
			));
		}
	};

	template<class T, class A0, class A1, class A2, class Policy>
	struct fun3{
		static void f(const VMachinePtr& vm, const ParamInfo& p, T& fun){
			Policy::return_result(vm, fun(
				arg_get<A0, 0>(vm, p), 
				arg_get<A1, 1>(vm, p), 
				arg_get<A2, 2>(vm, p)
			));
		}
	};

	template<class T, class A0, class A1, class A2, class A3, class Policy>
	struct fun4{
		static void f(const VMachinePtr& vm, const ParamInfo& p, T& fun){
			Policy::return_result(vm, fun(
				arg_get<A0, 0>(vm, p), 
				arg_get<A1, 1>(vm, p), 
				arg_get<A2, 2>(vm, p), 
				arg_get<A3, 3>(vm, p)
			));
		}
	};

	template<class T, class A0, class A1, class A2, class A3, class A4, class Policy>
	struct fun5{
		static void f(const VMachinePtr& vm, const ParamInfo& p, T& fun){
			Policy::return_result(vm, fun(
				arg_get<A0, 0>(vm, p), 
				arg_get<A1, 1>(vm, p), 
				arg_get<A2, 2>(vm, p), 
				arg_get<A3, 3>(vm, p),
				arg_get<A4, 4>(vm, p)
			));
		}
	};


	template<class T, class C, class Policy>
	struct method0{		
		static void f(const VMachinePtr& vm, const ParamInfo& p, T& fun){
			Policy::return_result(vm, fun(
				cast<C>(vm->get_arg_this())
			));
		}
	};

	template<class T, class C, class A0, class Policy>
	struct method1{		
		static void f(const VMachinePtr& vm, const ParamInfo& p, T& fun){
			Policy::return_result(vm, fun(
				cast<C>(vm->get_arg_this()), 
				arg_get<A0, 0>(vm, p)
			));
		}

		static void f_args(const VMachinePtr& vm, const ParamInfo& p, T& fun){
			Policy::return_result(vm, fun(
				cast<C>(vm->get_arg_this()), 
				vm
			));
		}
	};

	template<class T, class C, class A0, class A1, class Policy>
	struct method2{		
		static void f(const VMachinePtr& vm, const ParamInfo& p, T& fun){
			Policy::return_result(vm, fun(
				cast<C>(vm->get_arg_this()), 
				arg_get<A0, 0>(vm, p), 
				arg_get<A1, 1>(vm, p)
			));
		}
	};

	template<class T, class C, class A0, class A1, class A2, class Policy>
	struct method3{		
		static void f(const VMachinePtr& vm, const ParamInfo& p, T& fun){
			Policy::return_result(vm, fun(
				cast<C>(vm->get_arg_this()), 
				arg_get<A0, 0>(vm, p), 
				arg_get<A1, 1>(vm, p), 
				arg_get<A2, 2>(vm, p)
			));
		}
	};

	template<class T, class C, class A0, class A1, class A2, class A3, class Policy>
	struct method4{		
		static void f(const VMachinePtr& vm, const ParamInfo& p, T& fun){
			Policy::return_result(vm, fun(
				cast<C>(vm->get_arg_this()), 
				arg_get<A0, 0>(vm, p), 
				arg_get<A1, 1>(vm, p), 
				arg_get<A2, 2>(vm, p), 
				arg_get<A3, 3>(vm, p)
			));
		}
	};

	template<class T, class C, class A0, class A1, class A2, class A3, class A4, class Policy>
	struct method5{		
		static void f(const VMachinePtr& vm, const ParamInfo& p, T& fun){
			Policy::return_result(vm, fun(
				cast<C>(vm->get_arg_this()), 
				arg_get<A0, 0>(vm, p), 
				arg_get<A1, 1>(vm, p), 
				arg_get<A2, 2>(vm, p), 
				arg_get<A3, 3>(vm, p),
				arg_get<A4, 4>(vm, p)
			));
		}
	};
};

template<>
struct fun_R<void>{
	template<class T, class Policy>
	struct fun0{
		static void f(const VMachinePtr& vm, const ParamInfo&, T& fun){
			fun(
			);
			Policy::return_result(vm);
		}
	};
	
	template<class T, class A0, class Policy>
	struct fun1{
		static void f(const VMachinePtr& vm, const ParamInfo& p, T& fun){
			fun(
				arg_get<A0, 0>(vm, p)
			);
			Policy::return_result(vm);
		}

		static void f_args(const VMachinePtr& vm, const ParamInfo& p, T& fun){
			fun(
				vm
			);
		}
	};

	template<class T, class A0, class A1, class Policy>
	struct fun2{
		static void f(const VMachinePtr& vm, const ParamInfo& p, T& fun){
			fun(
				arg_get<A0, 0>(vm, p), 
				arg_get<A1, 1>(vm, p)
			);
			Policy::return_result(vm);
		}
	};

	template<class T, class A0, class A1, class A2, class Policy>
	struct fun3{
		static void f(const VMachinePtr& vm, const ParamInfo& p, T& fun){
			fun(
				arg_get<A0, 0>(vm, p), 
				arg_get<A1, 1>(vm, p), 
				arg_get<A2, 2>(vm, p)
			);
			Policy::return_result(vm);
		}
	};

	template<class T, class A0, class A1, class A2, class A3, class Policy>
	struct fun4{
		static void f(const VMachinePtr& vm, const ParamInfo& p, T& fun){
			fun(
				arg_get<A0, 0>(vm, p), 
				arg_get<A1, 1>(vm, p), 
				arg_get<A2, 2>(vm, p), 
				arg_get<A3, 3>(vm, p)
			);
			Policy::return_result(vm);
		}
	};

	template<class T, class A0, class A1, class A2, class A3, class A4, class Policy>
	struct fun5{
		static void f(const VMachinePtr& vm, const ParamInfo& p, T& fun){
			fun(
				arg_get<A0, 0>(vm, p), 
				arg_get<A1, 1>(vm, p), 
				arg_get<A2, 2>(vm, p), 
				arg_get<A3, 3>(vm, p),
				arg_get<A4, 4>(vm, p)
			);
			Policy::return_result(vm);
		}
	};

	template<class T, class C, class Policy>
	struct method0{
		static void f(const VMachinePtr& vm, const ParamInfo& p, T& fun){
			fun(
				cast<C>(vm->get_arg_this())
			);
			Policy::return_result(vm);
		}
	};

	template<class T, class C, class A0, class Policy>
	struct method1{
		static void f(const VMachinePtr& vm, const ParamInfo& p, T& fun){
			fun(
				cast<C>(vm->get_arg_this()), 
				arg_get<A0, 0>(vm, p)
			);
			Policy::return_result(vm);
		}

		static void f_args(const VMachinePtr& vm, const ParamInfo& p, T& fun){
			fun(
				cast<C>(vm->get_arg_this()), 
				vm
			);
		}
	};

	template<class T, class C, class A0, class A1, class Policy>
	struct method2{
		static void f(const VMachinePtr& vm, const ParamInfo& p, T& fun){
			fun(
				cast<C>(vm->get_arg_this()), 
				arg_get<A0, 0>(vm, p), 
				arg_get<A1, 1>(vm, p)
			);
			Policy::return_result(vm);
		}
	};

	template<class T, class C, class A0, class A1, class A2, class Policy>
	struct method3{
		static void f(const VMachinePtr& vm, const ParamInfo& p, T& fun){
			fun(
				cast<C>(vm->get_arg_this()), 
				arg_get<A0, 0>(vm, p), 
				arg_get<A1, 1>(vm, p), 
				arg_get<A2, 2>(vm, p)
			);
			Policy::return_result(vm);
		}
	};

	template<class T, class C, class A0, class A1, class A2, class A3, class Policy>
	struct method4{
		static void f(const VMachinePtr& vm, const ParamInfo& p, T& fun){
			fun(
				cast<C>(vm->get_arg_this()), 
				arg_get<A0, 0>(vm, p), 
				arg_get<A1, 1>(vm, p), 
				arg_get<A2, 2>(vm, p), 
				arg_get<A3, 3>(vm, p)
			);
			Policy::return_result(vm);
		}
	};

	template<class T, class C, class A0, class A1, class A2, class A3, class A4, class Policy>
	struct method5{
		static void f(const VMachinePtr& vm, const ParamInfo& p, T& fun){
			fun(
				cast<C>(vm->get_arg_this()), 
				arg_get<A0, 0>(vm, p), 
				arg_get<A1, 1>(vm, p), 
				arg_get<A2, 2>(vm, p), 
				arg_get<A3, 3>(vm, p),
				arg_get<A4, 4>(vm, p)
			);
			Policy::return_result(vm);
		}
	};
};

template<class T, class R, class Policy>
struct fun0{
	static void f(const VMachinePtr& vm, const ParamInfo& p, void* data){
		fun_R<R>::template fun0<T, Policy>::f(vm, p, *(T*)data);
	}
};
	
template<class T, class R, class A0, class Policy>
struct fun1{
	static void f(const VMachinePtr& vm, const ParamInfo& p, void* data){
		fun_R<R>::template fun1<T, A0, Policy>::f(vm, p, *(T*)data);
	}

	static void f_args(const VMachinePtr& vm, const ParamInfo& p, void* data){
		fun_R<R>::template fun1<T, A0, Policy>::f_args(vm, p, *(T*)data);
	}

	typedef void (*t)(const VMachinePtr&, const ParamInfo&, void*);
	static t get_f(I2T<1>){ return &f_args; }
	static t get_f(I2T<0>){ return &f; }
};

template<class T, class R, class A0, class A1, class Policy>
struct fun2{
	static void f(const VMachinePtr& vm, const ParamInfo& p, void* data){
		fun_R<R>::template fun2<T, A0, A1, Policy>::f(vm, p, *(T*)data);
	}
};

template<class T, class R, class A0, class A1, class A2, class Policy>
struct fun3{
	static void f(const VMachinePtr& vm, const ParamInfo& p, void* data){
		fun_R<R>::template fun3<T, A0, A1, A2, Policy>::f(vm, p, *(T*)data);
	}
};

template<class T, class R, class A0, class A1, class A2, class A3, class Policy>
struct fun4{
	static void f(const VMachinePtr& vm, const ParamInfo& p, void* data){
		fun_R<R>::template fun4<T, A0, A1, A2, A3, Policy>::f(vm, p, *(T*)data);
	}
};

template<class T, class R, class A0, class A1, class A2, class A3, class A4, class Policy>
struct fun5{
	static void f(const VMachinePtr& vm, const ParamInfo& p, void* data){
		fun_R<R>::template fun5<T, A0, A1, A2, A3, A4, Policy>::f(vm, p, *(T*)data);
	}
};


template<class T, class C, class R, class Policy>
struct method0{
	static void f(const VMachinePtr& vm, const ParamInfo& p, void* data){
		fun_R<R>::template method0<T, C, Policy>::f(vm, p, *(T*)data);
	}
};

template<class T, class C, class R, class A0, class Policy>
struct method1{
	static void f(const VMachinePtr& vm, const ParamInfo& p, void* data){
		fun_R<R>::template method1<T, C, A0, Policy>::f(vm, p, *(T*)data);
	}

	static void f_args(const VMachinePtr& vm, const ParamInfo& p, void* data){
		fun_R<R>::template method1<T, C, A0, Policy>::f_args(vm, p, *(T*)data);
	}

	typedef void (*t)(const VMachinePtr&, const ParamInfo&, void*);
	static t get_f(I2T<1>){ return &f_args; }
	static t get_f(I2T<0>){ return &f; }
};

template<class T, class C, class R, class A0, class A1, class Policy>
struct method2{
	static void f(const VMachinePtr& vm, const ParamInfo& p, void* data){
		fun_R<R>::template method2<T, C, A0, A1, Policy>::f(vm, p, *(T*)data);
	}
};

template<class T, class C, class R, class A0, class A1, class A2, class Policy>
struct method3{
	static void f(const VMachinePtr& vm, const ParamInfo& p, void* data){
		fun_R<R>::template method3<T, C, A0, A1, A2, Policy>::f(vm, p, *(T*)data);
	}
};

template<class T, class C, class R, class A0, class A1, class A2, class A3, class Policy>
struct method4{
	static void f(const VMachinePtr& vm, const ParamInfo& p, void* data){
		fun_R<R>::template method4<T, C, A0, A1, A2, A3, Policy>::f(vm, p, *(T*)data);
	}
};

template<class T, class C, class R, class A0, class A1, class A2, class A3, class A4, class Policy>
struct method5{
	static void f(const VMachinePtr& vm, const ParamInfo& p, void* data){
		fun_R<R>::template method5<T, C, A0, A1, A2, A3, A4, Policy>::f(vm, p, *(T*)data);
	}
};

template<class C, class R>
struct memfun0{
	R (C::*fun)();
	memfun0(R (C::*fun)()):fun(fun){}
	memfun0(R (C::*fun)() const):fun((R (C::*)())fun){}
	R operator()(C* self){ return (self->*fun)(); }
};

template<class C, class R, class A0>
struct memfun1{
	R (C::*fun)(A0);
	memfun1(R (C::*fun)(A0)):fun(fun){}
	memfun1(R (C::*fun)(A0) const):fun((R (C::*)(A0))fun){}
	R operator()(C* self, A0 a0){ return (self->*fun)(a0); }
};

template<class C, class R, class A0, class A1>
struct memfun2{
	R (C::*fun)(A0, A1);
	memfun2(R (C::*fun)(A0, A1)):fun(fun){}
	memfun2(R (C::*fun)(A0, A1) const):fun((R (C::*)(A0, A1))fun){}
	R operator()(C* self, A0 a0, A1 a1){ return (self->*fun)(a0, a1); }
};

template<class C, class R, class A0, class A1, class A2>
struct memfun3{
	R (C::*fun)(A0, A1, A2);
	memfun3(R (C::*fun)(A0, A1, A2)):fun(fun){}
	memfun3(R (C::*fun)(A0, A1, A2) const):fun((R (C::*)(A0, A1, A2))fun){}
	R operator()(C* self, A0 a0, A1 a1, A2 a2){ return (self->*fun)(a0, a1, a2); }
};

template<class C, class R, class A0, class A1, class A2, class A3>
struct memfun4{
	R (C::*fun)(A0, A1, A2, A3);
	memfun4(R (C::*fun)(A0, A1, A2, A3)):fun(fun){}
	memfun4(R (C::*fun)(A0, A1, A2, A3) const):fun((R (C::*)(A0, A1, A2, A3))fun){}
	R operator()(C* self, A0 a0, A1 a1, A2 a2, A3 a3){ return (self->*fun)(a0, a1, a2, a3); }
};

template<class C, class R, class A0, class A1, class A2, class A3, class A4>
struct memfun5{
	R (C::*fun)(A0, A1, A2, A3, A4);
	memfun5(R (C::*fun)(A0, A1, A2, A3, A4)):fun(fun){}
	memfun5(R (C::*fun)(A0, A1, A2, A3, A4) const):fun((R (C::*)(A0, A1, A2, A3, A4))fun){}
	R operator()(C* self, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4){ return (self->*fun)(a0, a1, a2, a3, a4); }
};

template<class C, class T>
struct getter{
	T C::* var;
	getter(T C::* var):var(var){}
	const T& operator()(C* self){ return self->*var; }
};

template<class C, class T>
struct setter{
	T C::* var;
	setter(T C::* var):var(var){}
	const T& operator()(C* self, const T& v){ return self->*var = v; }
};

template<int N>
struct ctor_fun;

template<>
struct ctor_fun<0>{
	template<class T, class A0, class A1, class A2, class A3, class A4>
	struct inner{ static SmartPtr<T> make(){ return xnew<T>(); } };
};

template<>
struct ctor_fun<1>{
	template<class T, class A0, class A1, class A2, class A3, class A4>
	struct inner{ static SmartPtr<T> make(A0 a0){ return xnew<T>(a0); } };
};

template<>
struct ctor_fun<2>{
	template<class T, class A0, class A1, class A2, class A3, class A4>
	struct inner{ static SmartPtr<T> make(A0 a0, A1 a1){ return xnew<T>(a0, a1); } };
};

template<>
struct ctor_fun<3>{
	template<class T, class A0, class A1, class A2, class A3, class A4>
	struct inner{ static SmartPtr<T> make(A0 a0, A1 a1, A2 a2){ return xnew<T>(a0, a1, a2); } };
};

template<>
struct ctor_fun<4>{
	template<class T, class A0, class A1, class A2, class A3, class A4>
	struct inner{ static SmartPtr<T> make(A0 a0, A1 a1, A2 a2, A3 a3){ return xnew<T>(a0, a1, a2, a3); } };
};

template<>
struct ctor_fun<5>{
	template<class T, class A0, class A1, class A2, class A3, class A4>
	struct inner{ static SmartPtr<T> make(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4){ return xnew<T>(a0, a1, a2, a3, a4); } };
};

}

class CFun : public HaveName{
public:
	typedef void (*fun_t)(const VMachinePtr&, const ParamInfo&, void* data);

	CFun(fun_t f, void* val, int_t param_n);
	
	virtual ~CFun();

	CFunPtr param(
		const Named2& value0 = null_named, 
		const Named2& value1 = null_named,
		const Named2& value2 = null_named,
		const Named2& value3 = null_named,
		const Named2& value4 = null_named
	);

	virtual void visit_members(Visitor& m);

	void check_arg(const VMachinePtr& vm);

	virtual void call(const VMachinePtr& vm);

protected:
	void* val_;
	fun_t fun_;
	ParamInfo pi_;
	int_t param_n_;
};

class CFunArgs : public CFun{
public:

	CFunArgs(fun_t f, void* val, int_t param_n);

	virtual void call(const VMachinePtr& vm);
};

struct CFunEssence{
	CFunEssence(CFun::fun_t f, const void* val, int_t val_size, int_t param_n, bool args = false);

	CFun::fun_t f;
	void* val;
	int_t param_n;
	bool args;
};

CFunPtr new_cfun(const CFunEssence& essence);

namespace detail{

template<class R, class Policy>
inline CFunEssence fun_impl(R (*f)(), const Policy&){
	return CFunEssence(&detail::fun0<R (*)(), R, Policy>::f, &f, sizeof(f), 0);
}

template<class R, class A0, class Policy>
inline CFunEssence fun_impl(R (*f)(A0), const Policy&){
	const bool V = IsSame<A0, const VMachinePtr&>::value;
	return CFunEssence(detail::fun1<R (*)(A0), R, A0, Policy>::get_f(I2T<V>()), &f, sizeof(f), 1, V);
}

template<class R, class A0, class A1, class Policy>
inline CFunEssence fun_impl(R (*f)(A0, A1), const Policy&){
	return CFunEssence(&detail::fun2<R (*)(A0, A1), R, A0, A1, Policy>::f, &f, sizeof(f), 2);
}

template<class R, class A0, class A1, class A2, class Policy>
inline CFunEssence fun_impl(R (*f)(A0, A1, A2), const Policy&){
	return CFunEssence(&detail::fun3<R (*)(A0, A1, A2), R, A0, A1, A2, Policy>::f, &f, sizeof(f), 3);
}


template<class R, class A0, class A1, class A2, class A3, class Policy>
inline CFunEssence fun_impl(R (*f)(A0, A1, A2, A3), const Policy&){
	return CFunEssence(&detail::fun4<R (*)(A0, A1, A2, A3), R, A0, A1, A2, A3, Policy>::f, &f, sizeof(f), 4);
}

template<class R, class A0, class A1, class A2, class A3, class A4, class Policy>
inline CFunEssence fun_impl(R (*f)(A0, A1, A2, A3, A4), const Policy&){
	return CFunEssence(&detail::fun5<R (*)(A0, A1, A2, A3, A4), R, A0, A1, A2, A3, A4, Policy>::f, &f, sizeof(f), 5);
}

template<class C, class R, class Policy>
inline CFunEssence method_impl(R (C::*f)(), const Policy&){
	typedef detail::memfun0<C, R> memfun;
	memfun data(f);
	return CFunEssence(&detail::method0<memfun, C*, R, Policy>::f, &data, sizeof(data), 0);
}

template<class C, class R, class A0, class Policy>
inline CFunEssence method_impl(R (C::*f)(A0), const Policy&){
	const bool V = IsSame<A0, const VMachinePtr&>::value;
	typedef detail::memfun1<C, R, A0> memfun;
	memfun data(f);
	return CFunEssence(detail::method1<memfun, C*, R, A0, Policy>::get_f(I2T<V>()), &data, sizeof(data), 1, V);
}

template<class C, class R, class A0, class A1, class Policy>
inline CFunEssence method_impl(R (C::*f)(A0, A1), const Policy&){
	typedef detail::memfun2<C, R, A0, A1> memfun;
	memfun data(f);
	return CFunEssence(&detail::method2<memfun, C*, R, A0, A1, Policy>::f, &data, sizeof(data), 2);
}

template<class C, class R, class A0, class A1, class A2, class Policy>
inline CFunEssence method_impl(R (C::*f)(A0, A1, A2), const Policy&){
	typedef detail::memfun3<C, R, A0, A1, A2> memfun;
	memfun data(f);
	return CFunEssence(&detail::method3<memfun, C*, R, A0, A1, A2, Policy>::f, &data, sizeof(data), 3);
}

template<class C, class R, class A0, class A1, class A2, class A3, class Policy>
inline CFunEssence method_impl(R (C::*f)(A0, A1, A2, A3), const Policy&){
	typedef detail::memfun4<C, R, A0, A1, A2, A3> memfun;
	memfun data(f);
	return CFunEssence(&detail::method4<memfun, C*, R, A0, A1, A2, A3, Policy>::f, &data, sizeof(data), 4);
}

template<class C, class R, class A0, class A1, class A2, class A3, class A4, class Policy>
inline CFunEssence method_impl(R (C::*f)(A0, A1, A2, A3, A4), const Policy&){
	typedef detail::memfun5<C, R, A0, A1, A2, A3, A4> memfun;
	memfun data(f);
	return CFunEssence(&detail::method5<memfun, C*, R, A0, A1, A2, A3, A4, Policy>::f, &data, sizeof(data), 5);
}

template<class C, class R, class Policy>
inline CFunEssence method_impl(R (C::*f)() const, const Policy&){
	typedef detail::memfun0<C, R> memfun;
	memfun data(f);
	return CFunEssence(&detail::method0<memfun, C*, R, Policy>::f, &data, sizeof(data), 0);
}

template<class C, class R, class A0, class Policy>
inline CFunEssence method_impl(R (C::*f)(A0) const, const Policy&){
	const bool V = IsSame<A0, const VMachinePtr&>::value;
	typedef detail::memfun1<C, R, A0> memfun;
	memfun data(f);
	return CFunEssence(detail::method1<memfun, C*, R, A0, Policy>::get_f(I2T<V>()), &data, sizeof(data), 1, V);
}

template<class C, class R, class A0, class A1, class Policy>
inline CFunEssence method_impl(R (C::*f)(A0, A1) const, const Policy&){
	typedef detail::memfun2<C, R, A0, A1> memfun;
	memfun data(f);
	return CFunEssence(&detail::method2<memfun, C*, R, A0, A1, Policy>::f, &data, sizeof(data), 2);
}

template<class C, class R, class A0, class A1, class A2, class Policy>
inline CFunEssence method_impl(R (C::*f)(A0, A1, A2) const, const Policy&){
	typedef detail::memfun3<C, R, A0, A1, A2> memfun;
	memfun data(f);
	return CFunEssence(&detail::method3<memfun, C*, R, A0, A1, A2, Policy>::f, &data, sizeof(data), 3);
}

template<class C, class R, class A0, class A1, class A2, class A3, class Policy>
inline CFunEssence method_impl(R (C::*f)(A0, A1, A2, A3) const, const Policy&){
	typedef detail::memfun4<C, R, A0, A1, A2, A3> memfun;
	memfun data(f);
	return CFunEssence(&detail::method4<memfun, C*, R, A0, A1, A2, A3, Policy>::f, &data, sizeof(data), 4);
}

template<class C, class R, class A0, class A1, class A2, class A3, class A4, class Policy>
inline CFunEssence method_impl(R (C::*f)(A0, A1, A2, A3, A4) const, const Policy&){
	typedef detail::memfun5<C, R, A0, A1, A2, A3, A4> memfun;
	memfun data(f);
	return CFunEssence(&detail::method5<memfun, C*, R, A0, A1, A2, A3, A4, Policy>::f, &data, sizeof(data), 5);
}


template<class C, class R, class Policy>
inline CFunEssence method_impl(R (*f)(C), const Policy&){
	return CFunEssence(&detail::method0<R (*)(C), C, R, Policy>::f, &f, sizeof(f), 0);
}

template<class C, class R, class A0, class Policy>
inline CFunEssence method_impl(R (*f)(C, A0), const Policy&){
	const bool V = IsSame<A0, const VMachinePtr&>::value;
	return CFunEssence(detail::method1<R (*)(C, A0), C, R, A0, Policy>::get_f(I2T<V>()), &f, sizeof(f), 1, V);
}

template<class C, class R, class A0, class A1, class Policy>
inline CFunEssence method_impl(R (*f)(C, A0, A1), const Policy&){
	return CFunEssence(&detail::method2<R (*)(C, A0, A1), C, R, A0, A1, Policy>::f, &f, sizeof(f), 2);
}

template<class C, class R, class A0, class A1, class A2, class Policy>
inline CFunEssence method_impl(R (*f)(C, A0, A1, A2), const Policy&){
	return CFunEssence(&detail::method3<R (*)(C, A0, A1, A2), C, R, A0, A1, A2, Policy>::f, &f, sizeof(f), 3);
}

template<class C, class R, class A0, class A1, class A2, class A3, class Policy>
inline CFunEssence method_impl(R (*f)(C, A0, A1, A2, A3), const Policy&){
	return CFunEssence(&detail::method4<R (*)(C, A0, A1, A2, A3), C, R, A0, A1, A2, A3, Policy>::f, &f, sizeof(f), 4);
}

template<class C, class R, class A0, class A1, class A2, class A3, class A4, class Policy>
inline CFunEssence method_impl(R (*f)(C, A0, A1, A2, A3, A4), const Policy&){
	return CFunEssence(&detail::method5<R (*)(C, A0, A1, A2, A3, A4), C, R, A0, A1, A2, A3, A4, Policy>::f, &f, sizeof(f), 5);
}

}

/**
* @brief C++の関数をXtalから呼び出せるオブジェクトに変換するための関数
*
*/
template<class Fun>
inline CFunPtr fun(Fun f){
	return new_cfun(detail::fun_impl(f, result));
}

/**
* @brief C++の関数をXtalから呼び出せるオブジェクトに変換するための関数
*
*/
template<class Fun, class Policy>
inline CFunPtr fun(Fun f, const Policy& policy){
	return new_cfun(detail::fun_impl(f, policy));
}


/**
* @brief C++のメンバ関数をXtalから呼び出せるオブジェクトに変換するための関数
*
* 普通の関数をメソッドとして変換したい場合、第一引数をその型にすること。
*/
template<class Fun>
inline CFunPtr method(Fun f){
	return new_cfun(detail::method_impl(f, result));
}

/**
* @brief C++のメンバ関数をXtalから呼び出せるオブジェクトに変換するための関数
*
* 普通の関数をメソッドとして変換したい場合、第一引数をその型にすること。
*/
template<class Fun, class Policy>
inline CFunPtr method(Fun f, const Policy& policy){
	return new_cfun(detail::method_impl(f, policy));
}

/**
* @brief C++のコンストラクタをXtalから呼び出せるオブジェクトに変換するための擬似関数
*
*/
template<class T, class A0=void, class A1=void, class A2=void, class A3=void, class A4=void>
class ctor : public CFunPtr{
	enum{
		N = 
		IsNotVoid<A0>::value + 
		IsNotVoid<A1>::value + 
		IsNotVoid<A2>::value + 
		IsNotVoid<A3>::value + 
		IsNotVoid<A4>::value
	};
public:
	
	ctor()
		:CFunPtr(fun(&detail::ctor_fun<N>::template inner<T, A0, A1, A2, A3, A4>::make)){}
};

	
/**
* @brief メンバ変数へのポインタからゲッター関数を生成する
*
*/
template<class T, class C, class Policy>
CFunPtr getter(T C::* v, const Policy&){
	typedef detail::getter<C, T> getter;
	getter data(v);
	return new_cfun(&detail::method0<getter, C*, const T&, Policy>::f, (const void*)&data, sizeof(data), 0);
}
	
/**
* @brief メンバ変数へのポインタからセッター関数を生成する
*
*/
template<class T, class C, class Policy>
CFunPtr setter(T C::* v, const Policy&){
	typedef detail::setter<C, T> setter;
	setter data(v);
	return new_cfun(&detail::method1<setter, C*, const T&, const T&, Policy>::f, (const void*)&data, sizeof(data), 1);
}


/**
* @birief 2重ディスパッチメソッド
*/
class DualDispatchMethod : public HaveName{
public:

	DualDispatchMethod(const IDPtr& primary_key)
		:primary_key_(primary_key){}

	virtual void call(const VMachinePtr& vm){
		vm->get_arg_this()->rawsend(vm, primary_key_, vm->arg(0)->get_class(), vm->get_arg_this());
	}

private:
	IDPtr primary_key_;
};

/**
* @brief 2重ディスパッチメソッドオブジェクトを生成する
*
*/
DualDispatchMethodPtr dual_dispatch_method(const IDPtr& primary_key);

/**
* @birief 2重ディスパッチ関数
*/
class DualDispatchFun : public HaveName{
public:

	DualDispatchFun(const ClassPtr& klass, const IDPtr& primary_key)
		:klass_(klass), primary_key_(primary_key){}

	virtual void call(const VMachinePtr& vm){
		klass_->member(primary_key_, vm->arg(0)->get_class(), vm->get_arg_this())->call(vm);
	}

private:

	virtual void visit_members(Visitor& m){
		HaveName::visit_members(m);
		m & klass_;
	}

	IDPtr primary_key_;
	AnyPtr klass_;
};

/**
* @brief 2重ディスパッチメソッドオブジェクトを生成する
*
*/
DualDispatchFunPtr dual_dispatch_fun(const ClassPtr& klass, const IDPtr& primary_key);

}
