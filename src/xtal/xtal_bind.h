/** \file src/xtal/xtal_bind.h
* \brief src/xtal/xtal_bind.h
*/

#ifndef XTAL_BIND_H_INCLUDE_GUARD
#define XTAL_BIND_H_INCLUDE_GUARD

#pragma once

namespace xtal{

template<class C = Any >
struct param_types_holderM1;

//{REPEAT{{
/*
template<class C #COMMA_REPEAT#class A`i`#>
struct param_types_holder`n`{
	static CppClassSymbolData* const values[`n`+1];
};

template<class C #COMMA_REPEAT#class A`i`#>
CppClassSymbolData* const param_types_holder`n`<C #COMMA_REPEAT#A`i`#>::values[`n`+1] = {
	&CppClassSymbol<C>::value,
	#REPEAT#&CppClassSymbol<A`i`>::value,#
};
*/

template<class C >
struct param_types_holder0{
	static CppClassSymbolData* const values[0+1];
};

template<class C >
CppClassSymbolData* const param_types_holder0<C >::values[0+1] = {
	&CppClassSymbol<C>::value,
	
};

template<class C , class A0>
struct param_types_holder1{
	static CppClassSymbolData* const values[1+1];
};

template<class C , class A0>
CppClassSymbolData* const param_types_holder1<C , A0>::values[1+1] = {
	&CppClassSymbol<C>::value,
	&CppClassSymbol<A0>::value,
};

template<class C , class A0, class A1>
struct param_types_holder2{
	static CppClassSymbolData* const values[2+1];
};

template<class C , class A0, class A1>
CppClassSymbolData* const param_types_holder2<C , A0, A1>::values[2+1] = {
	&CppClassSymbol<C>::value,
	&CppClassSymbol<A0>::value,&CppClassSymbol<A1>::value,
};

template<class C , class A0, class A1, class A2>
struct param_types_holder3{
	static CppClassSymbolData* const values[3+1];
};

template<class C , class A0, class A1, class A2>
CppClassSymbolData* const param_types_holder3<C , A0, A1, A2>::values[3+1] = {
	&CppClassSymbol<C>::value,
	&CppClassSymbol<A0>::value,&CppClassSymbol<A1>::value,&CppClassSymbol<A2>::value,
};

template<class C , class A0, class A1, class A2, class A3>
struct param_types_holder4{
	static CppClassSymbolData* const values[4+1];
};

template<class C , class A0, class A1, class A2, class A3>
CppClassSymbolData* const param_types_holder4<C , A0, A1, A2, A3>::values[4+1] = {
	&CppClassSymbol<C>::value,
	&CppClassSymbol<A0>::value,&CppClassSymbol<A1>::value,&CppClassSymbol<A2>::value,&CppClassSymbol<A3>::value,
};

template<class C , class A0, class A1, class A2, class A3, class A4>
struct param_types_holder5{
	static CppClassSymbolData* const values[5+1];
};

template<class C , class A0, class A1, class A2, class A3, class A4>
CppClassSymbolData* const param_types_holder5<C , A0, A1, A2, A3, A4>::values[5+1] = {
	&CppClassSymbol<C>::value,
	&CppClassSymbol<A0>::value,&CppClassSymbol<A1>::value,&CppClassSymbol<A2>::value,&CppClassSymbol<A3>::value,&CppClassSymbol<A4>::value,
};

template<class C , class A0, class A1, class A2, class A3, class A4, class A5>
struct param_types_holder6{
	static CppClassSymbolData* const values[6+1];
};

template<class C , class A0, class A1, class A2, class A3, class A4, class A5>
CppClassSymbolData* const param_types_holder6<C , A0, A1, A2, A3, A4, A5>::values[6+1] = {
	&CppClassSymbol<C>::value,
	&CppClassSymbol<A0>::value,&CppClassSymbol<A1>::value,&CppClassSymbol<A2>::value,&CppClassSymbol<A3>::value,&CppClassSymbol<A4>::value,&CppClassSymbol<A5>::value,
};

template<class C , class A0, class A1, class A2, class A3, class A4, class A5, class A6>
struct param_types_holder7{
	static CppClassSymbolData* const values[7+1];
};

template<class C , class A0, class A1, class A2, class A3, class A4, class A5, class A6>
CppClassSymbolData* const param_types_holder7<C , A0, A1, A2, A3, A4, A5, A6>::values[7+1] = {
	&CppClassSymbol<C>::value,
	&CppClassSymbol<A0>::value,&CppClassSymbol<A1>::value,&CppClassSymbol<A2>::value,&CppClassSymbol<A3>::value,&CppClassSymbol<A4>::value,&CppClassSymbol<A5>::value,&CppClassSymbol<A6>::value,
};

template<class C , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
struct param_types_holder8{
	static CppClassSymbolData* const values[8+1];
};

template<class C , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
CppClassSymbolData* const param_types_holder8<C , A0, A1, A2, A3, A4, A5, A6, A7>::values[8+1] = {
	&CppClassSymbol<C>::value,
	&CppClassSymbol<A0>::value,&CppClassSymbol<A1>::value,&CppClassSymbol<A2>::value,&CppClassSymbol<A3>::value,&CppClassSymbol<A4>::value,&CppClassSymbol<A5>::value,&CppClassSymbol<A6>::value,&CppClassSymbol<A7>::value,
};

template<class C , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
struct param_types_holder9{
	static CppClassSymbolData* const values[9+1];
};

template<class C , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
CppClassSymbolData* const param_types_holder9<C , A0, A1, A2, A3, A4, A5, A6, A7, A8>::values[9+1] = {
	&CppClassSymbol<C>::value,
	&CppClassSymbol<A0>::value,&CppClassSymbol<A1>::value,&CppClassSymbol<A2>::value,&CppClassSymbol<A3>::value,&CppClassSymbol<A4>::value,&CppClassSymbol<A5>::value,&CppClassSymbol<A6>::value,&CppClassSymbol<A7>::value,&CppClassSymbol<A8>::value,
};

template<class C , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
struct param_types_holder10{
	static CppClassSymbolData* const values[10+1];
};

template<class C , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
CppClassSymbolData* const param_types_holder10<C , A0, A1, A2, A3, A4, A5, A6, A7, A8, A9>::values[10+1] = {
	&CppClassSymbol<C>::value,
	&CppClassSymbol<A0>::value,&CppClassSymbol<A1>::value,&CppClassSymbol<A2>::value,&CppClassSymbol<A3>::value,&CppClassSymbol<A4>::value,&CppClassSymbol<A5>::value,&CppClassSymbol<A6>::value,&CppClassSymbol<A7>::value,&CppClassSymbol<A8>::value,&CppClassSymbol<A9>::value,
};

template<class C , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
struct param_types_holder11{
	static CppClassSymbolData* const values[11+1];
};

template<class C , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
CppClassSymbolData* const param_types_holder11<C , A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10>::values[11+1] = {
	&CppClassSymbol<C>::value,
	&CppClassSymbol<A0>::value,&CppClassSymbol<A1>::value,&CppClassSymbol<A2>::value,&CppClassSymbol<A3>::value,&CppClassSymbol<A4>::value,&CppClassSymbol<A5>::value,&CppClassSymbol<A6>::value,&CppClassSymbol<A7>::value,&CppClassSymbol<A8>::value,&CppClassSymbol<A9>::value,&CppClassSymbol<A10>::value,
};

template<class C , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11>
struct param_types_holder12{
	static CppClassSymbolData* const values[12+1];
};

template<class C , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11>
CppClassSymbolData* const param_types_holder12<C , A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11>::values[12+1] = {
	&CppClassSymbol<C>::value,
	&CppClassSymbol<A0>::value,&CppClassSymbol<A1>::value,&CppClassSymbol<A2>::value,&CppClassSymbol<A3>::value,&CppClassSymbol<A4>::value,&CppClassSymbol<A5>::value,&CppClassSymbol<A6>::value,&CppClassSymbol<A7>::value,&CppClassSymbol<A8>::value,&CppClassSymbol<A9>::value,&CppClassSymbol<A10>::value,&CppClassSymbol<A11>::value,
};

template<class C , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12>
struct param_types_holder13{
	static CppClassSymbolData* const values[13+1];
};

template<class C , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12>
CppClassSymbolData* const param_types_holder13<C , A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12>::values[13+1] = {
	&CppClassSymbol<C>::value,
	&CppClassSymbol<A0>::value,&CppClassSymbol<A1>::value,&CppClassSymbol<A2>::value,&CppClassSymbol<A3>::value,&CppClassSymbol<A4>::value,&CppClassSymbol<A5>::value,&CppClassSymbol<A6>::value,&CppClassSymbol<A7>::value,&CppClassSymbol<A8>::value,&CppClassSymbol<A9>::value,&CppClassSymbol<A10>::value,&CppClassSymbol<A11>::value,&CppClassSymbol<A12>::value,
};

//}}REPEAT}

struct AM1{};

//{REPEAT{{
/*
template<class TFun, int Method, class R #COMMA_REPEAT#class A`i`#>
struct nfun_base`n`{
	typedef TFun fun_type;
	#REPEAT#typedef typename CppClassSymbol<A`i`>::type AA`i`; #
	typedef typename If<Method,
		param_types_holder`n-1`<#REPEAT_COMMA#AA`i`#>,
		param_types_holder`n`<Any #COMMA_REPEAT#AA`i`#>
		>::type fun_param_holder;
	enum{ extendable = (Method==1 && `n`==1) ? 0 : IsSame<Arguments, typename CppClassSymbol<A`n-1`>::type>::value };
	enum{ ArgBase = 1-Method, method = Method, arity = `n`-Method, vm = 0 };
	static void call(FunctorParam& fp){ 
		(*(fun_type*)fp.fun)(fp
			#COMMA_REPEAT#unchecked_cast<A`i`>((AnyPtr&)fp.args[ArgBase+`i`])#
		);
	}
};

template<class TFun, int Method, class R>
struct nfun_base<`n`, TFun, Method, R>
	: nfun_base`n`<TFun, Method, R #COMMA_REPEAT#typename TFun::arg`i+1`_type#>{};

*/

template<class TFun, int Method, class R >
struct nfun_base0{
	typedef TFun fun_type;
	
	typedef typename If<Method,
		param_types_holderM1<>,
		param_types_holder0<Any >
		>::type fun_param_holder;
	enum{ extendable = (Method==1 && 0==1) ? 0 : IsSame<Arguments, typename CppClassSymbol<AM1>::type>::value };
	enum{ ArgBase = 1-Method, method = Method, arity = 0-Method, vm = 0 };
	static void call(FunctorParam& fp){ 
		(*(fun_type*)fp.fun)(fp
			
		);
	}
};

template<class TFun, int Method, class R>
struct nfun_base<0, TFun, Method, R>
	: nfun_base0<TFun, Method, R >{};


template<class TFun, int Method, class R , class A0>
struct nfun_base1{
	typedef TFun fun_type;
	typedef typename CppClassSymbol<A0>::type AA0; 
	typedef typename If<Method,
		param_types_holder0<AA0>,
		param_types_holder1<Any , AA0>
		>::type fun_param_holder;
	enum{ extendable = (Method==1 && 1==1) ? 0 : IsSame<Arguments, typename CppClassSymbol<A0>::type>::value };
	enum{ ArgBase = 1-Method, method = Method, arity = 1-Method, vm = 0 };
	static void call(FunctorParam& fp){ 
		(*(fun_type*)fp.fun)(fp
			, unchecked_cast<A0>((AnyPtr&)fp.args[ArgBase+0])
		);
	}
};

template<class TFun, int Method, class R>
struct nfun_base<1, TFun, Method, R>
	: nfun_base1<TFun, Method, R , typename TFun::arg1_type>{};


template<class TFun, int Method, class R , class A0, class A1>
struct nfun_base2{
	typedef TFun fun_type;
	typedef typename CppClassSymbol<A0>::type AA0; typedef typename CppClassSymbol<A1>::type AA1; 
	typedef typename If<Method,
		param_types_holder1<AA0, AA1>,
		param_types_holder2<Any , AA0, AA1>
		>::type fun_param_holder;
	enum{ extendable = (Method==1 && 2==1) ? 0 : IsSame<Arguments, typename CppClassSymbol<A1>::type>::value };
	enum{ ArgBase = 1-Method, method = Method, arity = 2-Method, vm = 0 };
	static void call(FunctorParam& fp){ 
		(*(fun_type*)fp.fun)(fp
			, unchecked_cast<A0>((AnyPtr&)fp.args[ArgBase+0]), unchecked_cast<A1>((AnyPtr&)fp.args[ArgBase+1])
		);
	}
};

template<class TFun, int Method, class R>
struct nfun_base<2, TFun, Method, R>
	: nfun_base2<TFun, Method, R , typename TFun::arg1_type, typename TFun::arg2_type>{};


template<class TFun, int Method, class R , class A0, class A1, class A2>
struct nfun_base3{
	typedef TFun fun_type;
	typedef typename CppClassSymbol<A0>::type AA0; typedef typename CppClassSymbol<A1>::type AA1; typedef typename CppClassSymbol<A2>::type AA2; 
	typedef typename If<Method,
		param_types_holder2<AA0, AA1, AA2>,
		param_types_holder3<Any , AA0, AA1, AA2>
		>::type fun_param_holder;
	enum{ extendable = (Method==1 && 3==1) ? 0 : IsSame<Arguments, typename CppClassSymbol<A2>::type>::value };
	enum{ ArgBase = 1-Method, method = Method, arity = 3-Method, vm = 0 };
	static void call(FunctorParam& fp){ 
		(*(fun_type*)fp.fun)(fp
			, unchecked_cast<A0>((AnyPtr&)fp.args[ArgBase+0]), unchecked_cast<A1>((AnyPtr&)fp.args[ArgBase+1]), unchecked_cast<A2>((AnyPtr&)fp.args[ArgBase+2])
		);
	}
};

template<class TFun, int Method, class R>
struct nfun_base<3, TFun, Method, R>
	: nfun_base3<TFun, Method, R , typename TFun::arg1_type, typename TFun::arg2_type, typename TFun::arg3_type>{};


template<class TFun, int Method, class R , class A0, class A1, class A2, class A3>
struct nfun_base4{
	typedef TFun fun_type;
	typedef typename CppClassSymbol<A0>::type AA0; typedef typename CppClassSymbol<A1>::type AA1; typedef typename CppClassSymbol<A2>::type AA2; typedef typename CppClassSymbol<A3>::type AA3; 
	typedef typename If<Method,
		param_types_holder3<AA0, AA1, AA2, AA3>,
		param_types_holder4<Any , AA0, AA1, AA2, AA3>
		>::type fun_param_holder;
	enum{ extendable = (Method==1 && 4==1) ? 0 : IsSame<Arguments, typename CppClassSymbol<A3>::type>::value };
	enum{ ArgBase = 1-Method, method = Method, arity = 4-Method, vm = 0 };
	static void call(FunctorParam& fp){ 
		(*(fun_type*)fp.fun)(fp
			, unchecked_cast<A0>((AnyPtr&)fp.args[ArgBase+0]), unchecked_cast<A1>((AnyPtr&)fp.args[ArgBase+1]), unchecked_cast<A2>((AnyPtr&)fp.args[ArgBase+2]), unchecked_cast<A3>((AnyPtr&)fp.args[ArgBase+3])
		);
	}
};

template<class TFun, int Method, class R>
struct nfun_base<4, TFun, Method, R>
	: nfun_base4<TFun, Method, R , typename TFun::arg1_type, typename TFun::arg2_type, typename TFun::arg3_type, typename TFun::arg4_type>{};


template<class TFun, int Method, class R , class A0, class A1, class A2, class A3, class A4>
struct nfun_base5{
	typedef TFun fun_type;
	typedef typename CppClassSymbol<A0>::type AA0; typedef typename CppClassSymbol<A1>::type AA1; typedef typename CppClassSymbol<A2>::type AA2; typedef typename CppClassSymbol<A3>::type AA3; typedef typename CppClassSymbol<A4>::type AA4; 
	typedef typename If<Method,
		param_types_holder4<AA0, AA1, AA2, AA3, AA4>,
		param_types_holder5<Any , AA0, AA1, AA2, AA3, AA4>
		>::type fun_param_holder;
	enum{ extendable = (Method==1 && 5==1) ? 0 : IsSame<Arguments, typename CppClassSymbol<A4>::type>::value };
	enum{ ArgBase = 1-Method, method = Method, arity = 5-Method, vm = 0 };
	static void call(FunctorParam& fp){ 
		(*(fun_type*)fp.fun)(fp
			, unchecked_cast<A0>((AnyPtr&)fp.args[ArgBase+0]), unchecked_cast<A1>((AnyPtr&)fp.args[ArgBase+1]), unchecked_cast<A2>((AnyPtr&)fp.args[ArgBase+2]), unchecked_cast<A3>((AnyPtr&)fp.args[ArgBase+3]), unchecked_cast<A4>((AnyPtr&)fp.args[ArgBase+4])
		);
	}
};

template<class TFun, int Method, class R>
struct nfun_base<5, TFun, Method, R>
	: nfun_base5<TFun, Method, R , typename TFun::arg1_type, typename TFun::arg2_type, typename TFun::arg3_type, typename TFun::arg4_type, typename TFun::arg5_type>{};


template<class TFun, int Method, class R , class A0, class A1, class A2, class A3, class A4, class A5>
struct nfun_base6{
	typedef TFun fun_type;
	typedef typename CppClassSymbol<A0>::type AA0; typedef typename CppClassSymbol<A1>::type AA1; typedef typename CppClassSymbol<A2>::type AA2; typedef typename CppClassSymbol<A3>::type AA3; typedef typename CppClassSymbol<A4>::type AA4; typedef typename CppClassSymbol<A5>::type AA5; 
	typedef typename If<Method,
		param_types_holder5<AA0, AA1, AA2, AA3, AA4, AA5>,
		param_types_holder6<Any , AA0, AA1, AA2, AA3, AA4, AA5>
		>::type fun_param_holder;
	enum{ extendable = (Method==1 && 6==1) ? 0 : IsSame<Arguments, typename CppClassSymbol<A5>::type>::value };
	enum{ ArgBase = 1-Method, method = Method, arity = 6-Method, vm = 0 };
	static void call(FunctorParam& fp){ 
		(*(fun_type*)fp.fun)(fp
			, unchecked_cast<A0>((AnyPtr&)fp.args[ArgBase+0]), unchecked_cast<A1>((AnyPtr&)fp.args[ArgBase+1]), unchecked_cast<A2>((AnyPtr&)fp.args[ArgBase+2]), unchecked_cast<A3>((AnyPtr&)fp.args[ArgBase+3]), unchecked_cast<A4>((AnyPtr&)fp.args[ArgBase+4]), unchecked_cast<A5>((AnyPtr&)fp.args[ArgBase+5])
		);
	}
};

template<class TFun, int Method, class R>
struct nfun_base<6, TFun, Method, R>
	: nfun_base6<TFun, Method, R , typename TFun::arg1_type, typename TFun::arg2_type, typename TFun::arg3_type, typename TFun::arg4_type, typename TFun::arg5_type, typename TFun::arg6_type>{};


template<class TFun, int Method, class R , class A0, class A1, class A2, class A3, class A4, class A5, class A6>
struct nfun_base7{
	typedef TFun fun_type;
	typedef typename CppClassSymbol<A0>::type AA0; typedef typename CppClassSymbol<A1>::type AA1; typedef typename CppClassSymbol<A2>::type AA2; typedef typename CppClassSymbol<A3>::type AA3; typedef typename CppClassSymbol<A4>::type AA4; typedef typename CppClassSymbol<A5>::type AA5; typedef typename CppClassSymbol<A6>::type AA6; 
	typedef typename If<Method,
		param_types_holder6<AA0, AA1, AA2, AA3, AA4, AA5, AA6>,
		param_types_holder7<Any , AA0, AA1, AA2, AA3, AA4, AA5, AA6>
		>::type fun_param_holder;
	enum{ extendable = (Method==1 && 7==1) ? 0 : IsSame<Arguments, typename CppClassSymbol<A6>::type>::value };
	enum{ ArgBase = 1-Method, method = Method, arity = 7-Method, vm = 0 };
	static void call(FunctorParam& fp){ 
		(*(fun_type*)fp.fun)(fp
			, unchecked_cast<A0>((AnyPtr&)fp.args[ArgBase+0]), unchecked_cast<A1>((AnyPtr&)fp.args[ArgBase+1]), unchecked_cast<A2>((AnyPtr&)fp.args[ArgBase+2]), unchecked_cast<A3>((AnyPtr&)fp.args[ArgBase+3]), unchecked_cast<A4>((AnyPtr&)fp.args[ArgBase+4]), unchecked_cast<A5>((AnyPtr&)fp.args[ArgBase+5]), unchecked_cast<A6>((AnyPtr&)fp.args[ArgBase+6])
		);
	}
};

template<class TFun, int Method, class R>
struct nfun_base<7, TFun, Method, R>
	: nfun_base7<TFun, Method, R , typename TFun::arg1_type, typename TFun::arg2_type, typename TFun::arg3_type, typename TFun::arg4_type, typename TFun::arg5_type, typename TFun::arg6_type, typename TFun::arg7_type>{};


template<class TFun, int Method, class R , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
struct nfun_base8{
	typedef TFun fun_type;
	typedef typename CppClassSymbol<A0>::type AA0; typedef typename CppClassSymbol<A1>::type AA1; typedef typename CppClassSymbol<A2>::type AA2; typedef typename CppClassSymbol<A3>::type AA3; typedef typename CppClassSymbol<A4>::type AA4; typedef typename CppClassSymbol<A5>::type AA5; typedef typename CppClassSymbol<A6>::type AA6; typedef typename CppClassSymbol<A7>::type AA7; 
	typedef typename If<Method,
		param_types_holder7<AA0, AA1, AA2, AA3, AA4, AA5, AA6, AA7>,
		param_types_holder8<Any , AA0, AA1, AA2, AA3, AA4, AA5, AA6, AA7>
		>::type fun_param_holder;
	enum{ extendable = (Method==1 && 8==1) ? 0 : IsSame<Arguments, typename CppClassSymbol<A7>::type>::value };
	enum{ ArgBase = 1-Method, method = Method, arity = 8-Method, vm = 0 };
	static void call(FunctorParam& fp){ 
		(*(fun_type*)fp.fun)(fp
			, unchecked_cast<A0>((AnyPtr&)fp.args[ArgBase+0]), unchecked_cast<A1>((AnyPtr&)fp.args[ArgBase+1]), unchecked_cast<A2>((AnyPtr&)fp.args[ArgBase+2]), unchecked_cast<A3>((AnyPtr&)fp.args[ArgBase+3]), unchecked_cast<A4>((AnyPtr&)fp.args[ArgBase+4]), unchecked_cast<A5>((AnyPtr&)fp.args[ArgBase+5]), unchecked_cast<A6>((AnyPtr&)fp.args[ArgBase+6]), unchecked_cast<A7>((AnyPtr&)fp.args[ArgBase+7])
		);
	}
};

template<class TFun, int Method, class R>
struct nfun_base<8, TFun, Method, R>
	: nfun_base8<TFun, Method, R , typename TFun::arg1_type, typename TFun::arg2_type, typename TFun::arg3_type, typename TFun::arg4_type, typename TFun::arg5_type, typename TFun::arg6_type, typename TFun::arg7_type, typename TFun::arg8_type>{};


template<class TFun, int Method, class R , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
struct nfun_base9{
	typedef TFun fun_type;
	typedef typename CppClassSymbol<A0>::type AA0; typedef typename CppClassSymbol<A1>::type AA1; typedef typename CppClassSymbol<A2>::type AA2; typedef typename CppClassSymbol<A3>::type AA3; typedef typename CppClassSymbol<A4>::type AA4; typedef typename CppClassSymbol<A5>::type AA5; typedef typename CppClassSymbol<A6>::type AA6; typedef typename CppClassSymbol<A7>::type AA7; typedef typename CppClassSymbol<A8>::type AA8; 
	typedef typename If<Method,
		param_types_holder8<AA0, AA1, AA2, AA3, AA4, AA5, AA6, AA7, AA8>,
		param_types_holder9<Any , AA0, AA1, AA2, AA3, AA4, AA5, AA6, AA7, AA8>
		>::type fun_param_holder;
	enum{ extendable = (Method==1 && 9==1) ? 0 : IsSame<Arguments, typename CppClassSymbol<A8>::type>::value };
	enum{ ArgBase = 1-Method, method = Method, arity = 9-Method, vm = 0 };
	static void call(FunctorParam& fp){ 
		(*(fun_type*)fp.fun)(fp
			, unchecked_cast<A0>((AnyPtr&)fp.args[ArgBase+0]), unchecked_cast<A1>((AnyPtr&)fp.args[ArgBase+1]), unchecked_cast<A2>((AnyPtr&)fp.args[ArgBase+2]), unchecked_cast<A3>((AnyPtr&)fp.args[ArgBase+3]), unchecked_cast<A4>((AnyPtr&)fp.args[ArgBase+4]), unchecked_cast<A5>((AnyPtr&)fp.args[ArgBase+5]), unchecked_cast<A6>((AnyPtr&)fp.args[ArgBase+6]), unchecked_cast<A7>((AnyPtr&)fp.args[ArgBase+7]), unchecked_cast<A8>((AnyPtr&)fp.args[ArgBase+8])
		);
	}
};

template<class TFun, int Method, class R>
struct nfun_base<9, TFun, Method, R>
	: nfun_base9<TFun, Method, R , typename TFun::arg1_type, typename TFun::arg2_type, typename TFun::arg3_type, typename TFun::arg4_type, typename TFun::arg5_type, typename TFun::arg6_type, typename TFun::arg7_type, typename TFun::arg8_type, typename TFun::arg9_type>{};


template<class TFun, int Method, class R , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
struct nfun_base10{
	typedef TFun fun_type;
	typedef typename CppClassSymbol<A0>::type AA0; typedef typename CppClassSymbol<A1>::type AA1; typedef typename CppClassSymbol<A2>::type AA2; typedef typename CppClassSymbol<A3>::type AA3; typedef typename CppClassSymbol<A4>::type AA4; typedef typename CppClassSymbol<A5>::type AA5; typedef typename CppClassSymbol<A6>::type AA6; typedef typename CppClassSymbol<A7>::type AA7; typedef typename CppClassSymbol<A8>::type AA8; typedef typename CppClassSymbol<A9>::type AA9; 
	typedef typename If<Method,
		param_types_holder9<AA0, AA1, AA2, AA3, AA4, AA5, AA6, AA7, AA8, AA9>,
		param_types_holder10<Any , AA0, AA1, AA2, AA3, AA4, AA5, AA6, AA7, AA8, AA9>
		>::type fun_param_holder;
	enum{ extendable = (Method==1 && 10==1) ? 0 : IsSame<Arguments, typename CppClassSymbol<A9>::type>::value };
	enum{ ArgBase = 1-Method, method = Method, arity = 10-Method, vm = 0 };
	static void call(FunctorParam& fp){ 
		(*(fun_type*)fp.fun)(fp
			, unchecked_cast<A0>((AnyPtr&)fp.args[ArgBase+0]), unchecked_cast<A1>((AnyPtr&)fp.args[ArgBase+1]), unchecked_cast<A2>((AnyPtr&)fp.args[ArgBase+2]), unchecked_cast<A3>((AnyPtr&)fp.args[ArgBase+3]), unchecked_cast<A4>((AnyPtr&)fp.args[ArgBase+4]), unchecked_cast<A5>((AnyPtr&)fp.args[ArgBase+5]), unchecked_cast<A6>((AnyPtr&)fp.args[ArgBase+6]), unchecked_cast<A7>((AnyPtr&)fp.args[ArgBase+7]), unchecked_cast<A8>((AnyPtr&)fp.args[ArgBase+8]), unchecked_cast<A9>((AnyPtr&)fp.args[ArgBase+9])
		);
	}
};

template<class TFun, int Method, class R>
struct nfun_base<10, TFun, Method, R>
	: nfun_base10<TFun, Method, R , typename TFun::arg1_type, typename TFun::arg2_type, typename TFun::arg3_type, typename TFun::arg4_type, typename TFun::arg5_type, typename TFun::arg6_type, typename TFun::arg7_type, typename TFun::arg8_type, typename TFun::arg9_type, typename TFun::arg10_type>{};


template<class TFun, int Method, class R , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
struct nfun_base11{
	typedef TFun fun_type;
	typedef typename CppClassSymbol<A0>::type AA0; typedef typename CppClassSymbol<A1>::type AA1; typedef typename CppClassSymbol<A2>::type AA2; typedef typename CppClassSymbol<A3>::type AA3; typedef typename CppClassSymbol<A4>::type AA4; typedef typename CppClassSymbol<A5>::type AA5; typedef typename CppClassSymbol<A6>::type AA6; typedef typename CppClassSymbol<A7>::type AA7; typedef typename CppClassSymbol<A8>::type AA8; typedef typename CppClassSymbol<A9>::type AA9; typedef typename CppClassSymbol<A10>::type AA10; 
	typedef typename If<Method,
		param_types_holder10<AA0, AA1, AA2, AA3, AA4, AA5, AA6, AA7, AA8, AA9, AA10>,
		param_types_holder11<Any , AA0, AA1, AA2, AA3, AA4, AA5, AA6, AA7, AA8, AA9, AA10>
		>::type fun_param_holder;
	enum{ extendable = (Method==1 && 11==1) ? 0 : IsSame<Arguments, typename CppClassSymbol<A10>::type>::value };
	enum{ ArgBase = 1-Method, method = Method, arity = 11-Method, vm = 0 };
	static void call(FunctorParam& fp){ 
		(*(fun_type*)fp.fun)(fp
			, unchecked_cast<A0>((AnyPtr&)fp.args[ArgBase+0]), unchecked_cast<A1>((AnyPtr&)fp.args[ArgBase+1]), unchecked_cast<A2>((AnyPtr&)fp.args[ArgBase+2]), unchecked_cast<A3>((AnyPtr&)fp.args[ArgBase+3]), unchecked_cast<A4>((AnyPtr&)fp.args[ArgBase+4]), unchecked_cast<A5>((AnyPtr&)fp.args[ArgBase+5]), unchecked_cast<A6>((AnyPtr&)fp.args[ArgBase+6]), unchecked_cast<A7>((AnyPtr&)fp.args[ArgBase+7]), unchecked_cast<A8>((AnyPtr&)fp.args[ArgBase+8]), unchecked_cast<A9>((AnyPtr&)fp.args[ArgBase+9]), unchecked_cast<A10>((AnyPtr&)fp.args[ArgBase+10])
		);
	}
};

template<class TFun, int Method, class R>
struct nfun_base<11, TFun, Method, R>
	: nfun_base11<TFun, Method, R , typename TFun::arg1_type, typename TFun::arg2_type, typename TFun::arg3_type, typename TFun::arg4_type, typename TFun::arg5_type, typename TFun::arg6_type, typename TFun::arg7_type, typename TFun::arg8_type, typename TFun::arg9_type, typename TFun::arg10_type, typename TFun::arg11_type>{};


template<class TFun, int Method, class R , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11>
struct nfun_base12{
	typedef TFun fun_type;
	typedef typename CppClassSymbol<A0>::type AA0; typedef typename CppClassSymbol<A1>::type AA1; typedef typename CppClassSymbol<A2>::type AA2; typedef typename CppClassSymbol<A3>::type AA3; typedef typename CppClassSymbol<A4>::type AA4; typedef typename CppClassSymbol<A5>::type AA5; typedef typename CppClassSymbol<A6>::type AA6; typedef typename CppClassSymbol<A7>::type AA7; typedef typename CppClassSymbol<A8>::type AA8; typedef typename CppClassSymbol<A9>::type AA9; typedef typename CppClassSymbol<A10>::type AA10; typedef typename CppClassSymbol<A11>::type AA11; 
	typedef typename If<Method,
		param_types_holder11<AA0, AA1, AA2, AA3, AA4, AA5, AA6, AA7, AA8, AA9, AA10, AA11>,
		param_types_holder12<Any , AA0, AA1, AA2, AA3, AA4, AA5, AA6, AA7, AA8, AA9, AA10, AA11>
		>::type fun_param_holder;
	enum{ extendable = (Method==1 && 12==1) ? 0 : IsSame<Arguments, typename CppClassSymbol<A11>::type>::value };
	enum{ ArgBase = 1-Method, method = Method, arity = 12-Method, vm = 0 };
	static void call(FunctorParam& fp){ 
		(*(fun_type*)fp.fun)(fp
			, unchecked_cast<A0>((AnyPtr&)fp.args[ArgBase+0]), unchecked_cast<A1>((AnyPtr&)fp.args[ArgBase+1]), unchecked_cast<A2>((AnyPtr&)fp.args[ArgBase+2]), unchecked_cast<A3>((AnyPtr&)fp.args[ArgBase+3]), unchecked_cast<A4>((AnyPtr&)fp.args[ArgBase+4]), unchecked_cast<A5>((AnyPtr&)fp.args[ArgBase+5]), unchecked_cast<A6>((AnyPtr&)fp.args[ArgBase+6]), unchecked_cast<A7>((AnyPtr&)fp.args[ArgBase+7]), unchecked_cast<A8>((AnyPtr&)fp.args[ArgBase+8]), unchecked_cast<A9>((AnyPtr&)fp.args[ArgBase+9]), unchecked_cast<A10>((AnyPtr&)fp.args[ArgBase+10]), unchecked_cast<A11>((AnyPtr&)fp.args[ArgBase+11])
		);
	}
};

template<class TFun, int Method, class R>
struct nfun_base<12, TFun, Method, R>
	: nfun_base12<TFun, Method, R , typename TFun::arg1_type, typename TFun::arg2_type, typename TFun::arg3_type, typename TFun::arg4_type, typename TFun::arg5_type, typename TFun::arg6_type, typename TFun::arg7_type, typename TFun::arg8_type, typename TFun::arg9_type, typename TFun::arg10_type, typename TFun::arg11_type, typename TFun::arg12_type>{};


template<class TFun, int Method, class R , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12>
struct nfun_base13{
	typedef TFun fun_type;
	typedef typename CppClassSymbol<A0>::type AA0; typedef typename CppClassSymbol<A1>::type AA1; typedef typename CppClassSymbol<A2>::type AA2; typedef typename CppClassSymbol<A3>::type AA3; typedef typename CppClassSymbol<A4>::type AA4; typedef typename CppClassSymbol<A5>::type AA5; typedef typename CppClassSymbol<A6>::type AA6; typedef typename CppClassSymbol<A7>::type AA7; typedef typename CppClassSymbol<A8>::type AA8; typedef typename CppClassSymbol<A9>::type AA9; typedef typename CppClassSymbol<A10>::type AA10; typedef typename CppClassSymbol<A11>::type AA11; typedef typename CppClassSymbol<A12>::type AA12; 
	typedef typename If<Method,
		param_types_holder12<AA0, AA1, AA2, AA3, AA4, AA5, AA6, AA7, AA8, AA9, AA10, AA11, AA12>,
		param_types_holder13<Any , AA0, AA1, AA2, AA3, AA4, AA5, AA6, AA7, AA8, AA9, AA10, AA11, AA12>
		>::type fun_param_holder;
	enum{ extendable = (Method==1 && 13==1) ? 0 : IsSame<Arguments, typename CppClassSymbol<A12>::type>::value };
	enum{ ArgBase = 1-Method, method = Method, arity = 13-Method, vm = 0 };
	static void call(FunctorParam& fp){ 
		(*(fun_type*)fp.fun)(fp
			, unchecked_cast<A0>((AnyPtr&)fp.args[ArgBase+0]), unchecked_cast<A1>((AnyPtr&)fp.args[ArgBase+1]), unchecked_cast<A2>((AnyPtr&)fp.args[ArgBase+2]), unchecked_cast<A3>((AnyPtr&)fp.args[ArgBase+3]), unchecked_cast<A4>((AnyPtr&)fp.args[ArgBase+4]), unchecked_cast<A5>((AnyPtr&)fp.args[ArgBase+5]), unchecked_cast<A6>((AnyPtr&)fp.args[ArgBase+6]), unchecked_cast<A7>((AnyPtr&)fp.args[ArgBase+7]), unchecked_cast<A8>((AnyPtr&)fp.args[ArgBase+8]), unchecked_cast<A9>((AnyPtr&)fp.args[ArgBase+9]), unchecked_cast<A10>((AnyPtr&)fp.args[ArgBase+10]), unchecked_cast<A11>((AnyPtr&)fp.args[ArgBase+11]), unchecked_cast<A12>((AnyPtr&)fp.args[ArgBase+12])
		);
	}
};

template<class TFun, int Method, class R>
struct nfun_base<13, TFun, Method, R>
	: nfun_base13<TFun, Method, R , typename TFun::arg1_type, typename TFun::arg2_type, typename TFun::arg3_type, typename TFun::arg4_type, typename TFun::arg5_type, typename TFun::arg6_type, typename TFun::arg7_type, typename TFun::arg8_type, typename TFun::arg9_type, typename TFun::arg10_type, typename TFun::arg11_type, typename TFun::arg12_type, typename TFun::arg13_type>{};


//}}REPEAT}

template<class TFun, class R>
struct nfun_base1<TFun, 0, R, const VMachinePtr&>{
	typedef TFun fun_type;
	typedef param_types_holder1<Any, Any> fun_param_holder;
	enum{ method = 0, arity = 1, extendable = 0, vm = 1 };
	static void call(FunctorParam& fp){ 
		(*(TFun*)fp.fun)(fp,
			to_smartptr(fp.vm)
		);
	}
};

template<class TFun, class R>
struct nfun_base1<TFun, 1, R, const VMachinePtr&>{
	typedef TFun fun_type;
	typedef param_types_holder1<Any, Any> fun_param_holder;
	enum{ method = 1, arity = 1, extendable = 0, vm = 1 };
	static void call(FunctorParam& fp){ 
		(*(TFun*)fp.fun)(fp,
			to_smartptr(fp.vm)
		);
	}
};

template<class TFun, class R, class C>
struct nfun_base2<TFun, 1, R , C, const VMachinePtr&>{
	typedef TFun fun_type;
	typedef param_types_holder1<C, Any> fun_param_holder;
	enum{ method = 1, arity = 1, extendable = 0, vm = 1 };
	static void call(FunctorParam& fp){ 
		(*(TFun*)fp.fun)(fp,
			unchecked_cast<C>((AnyPtr&)fp.args[0]),
			to_smartptr(fp.vm)
		);
	}
};

//{REPEAT{{
/*
template<int Method, class R #COMMA_REPEAT#class A`i`#>
struct nfun<R (*)(#REPEAT_COMMA#A`i`#), Method>
	: nfun_base<`n`, functor<R (*)(#REPEAT_COMMA#A`i`#)>, Method, R>{};

// 関数を関数オブジェクト化する
template<class R #COMMA_REPEAT#class A`i`#>
struct functor<R (*)(#REPEAT_COMMA#A`i`#)>{
	typedef R result_type; #REPEAT#typedef A`i` arg`i+1`_type; #
	typedef R (*fun_type)(#REPEAT_COMMA#A`i`#);
	enum{ arity = `n`};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret #COMMA_REPEAT#A`i` a`i`#) const{
		fun_(#REPEAT_COMMA#a`i`#), rcast<R>(ret);
	}
};

template<int Method, class R, class C #COMMA_REPEAT#class A`i`#>
struct nfun<R (C::*)(#REPEAT_COMMA#A`i`#), Method>
	: nfun_base<`n+1`, functor<R (C::*)(#REPEAT_COMMA#A`i`#)>, Method, R>{};

// メンバ関数を関数オブジェクト化する
template<class R, class C #COMMA_REPEAT#class A`i`#>
struct functor<R (C::*)(#REPEAT_COMMA#A`i`#)>{
	typedef R result_type; typedef C* arg1_type; #REPEAT#typedef A`i` arg`i+2`_type; #
	typedef R (C::*fun_type)(#REPEAT_COMMA#A`i`#);
	enum{ arity = `n+1`};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret, C* self #COMMA_REPEAT#A`i` a`i`#) const{
		(self->*fun_)(#REPEAT_COMMA#a`i`#), rcast<R>(ret);
	}
};

template<int Method, class R, class C #COMMA_REPEAT#class A`i`#>
struct nfun<R (C::*)(#REPEAT_COMMA#A`i`#) const, Method>
	: nfun_base<`n+1`, functor<R (C::*)(#REPEAT_COMMA#A`i`#) const>, Method, R>{};

// constメンバ関数を関数オブジェクト化する
template<class R, class C #COMMA_REPEAT#class A`i`#>
struct functor<R (C::*)(#REPEAT_COMMA#A`i`#) const>{
	typedef R result_type; typedef C* arg1_type; #REPEAT#typedef A`i` arg`i+2`_type; #
	typedef R (C::*fun_type)(#REPEAT_COMMA#A`i`#) const;
	enum{ arity = `n+1`};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret, C* self #COMMA_REPEAT#A`i` a`i`#) const{
		(self->*fun_)(#REPEAT_COMMA#a`i`#), rcast<R>(ret);
	}
};

////

// 関数を関数オブジェクト化する
template<class R #COMMA_REPEAT#class A`i`#, R (*fun_)(#REPEAT_COMMA#A`i`#)>
struct static_functor<R (*)(#REPEAT_COMMA#A`i`#), fun_>{
	typedef R result_type; #REPEAT#typedef A`i` arg`i+1`_type; #
	enum{ arity = `n`};

	void operator()(FunctorParam& ret #COMMA_REPEAT#A`i` a`i`#) const{
		fun_(#REPEAT_COMMA#a`i`#), rcast<R>(ret);
	}
};

// メンバ関数を関数オブジェクト化する
template<class R, class C #COMMA_REPEAT#class A`i`#, R (C::*fun_)(#REPEAT_COMMA#A`i`#)>
struct static_functor<R (C::*)(#REPEAT_COMMA#A`i`#), fun_>{
	typedef R result_type; typedef C* arg1_type; #REPEAT#typedef A`i` arg`i+2`_type; #
	enum{ arity = `n+1`};

	void operator()(FunctorParam& ret, C* self #COMMA_REPEAT#A`i` a`i`#) const{
		(self->*fun_)(#REPEAT_COMMA#a`i`#), rcast<R>(ret);
	}
};

// constメンバ関数を関数オブジェクト化する
template<class R, class C #COMMA_REPEAT#class A`i`#, R (C::*fun_)(#REPEAT_COMMA#A`i`#) const>
struct static_functor<R (C::*)(#REPEAT_COMMA#A`i`#) const, fun_>{
	typedef R result_type; typedef C* arg1_type; #REPEAT#typedef A`i` arg`i+2`_type; #
	enum{ arity = `n+1`};

	void operator()(FunctorParam& ret, C* self #COMMA_REPEAT#A`i` a`i`#) const{
		(self->*fun_)(#REPEAT_COMMA#a`i`#), rcast<R>(ret);
	}
};

// コンストラクタを関数オブジェクト化する
template<class T #COMMA_REPEAT#class A`i`#>
struct ctor_functor<T #COMMA_REPEAT#A`i`#>{
	typedef SmartPtr<T> R;
	typedef R result_type; #REPEAT#typedef A`i` arg`i+1`_type; #
	enum{ arity = `n`};

	void operator()(FunctorParam& ret #COMMA_REPEAT#A`i` a`i`#) const{
		xnew<T>(#REPEAT_COMMA#a`i`#), rcast<R>(ret);
	}
};

// stdcall版
#if defined(_WIN32) && defined(_M_IX86)

template<int Method, class R #COMMA_REPEAT#class A`i`#>
struct nfun<R (__stdcall *)(#REPEAT_COMMA#A`i`#), Method>
	: nfun_base<`n`, functor<R (__stdcall *)(#REPEAT_COMMA#A`i`#)>, Method, R>{};

// 関数を関数オブジェクト化する
template<class R #COMMA_REPEAT#class A`i`#>
struct functor<R (__stdcall *)(#REPEAT_COMMA#A`i`#)>{
	typedef R result_type; #REPEAT#typedef A`i` arg`i+1`_type; #
	typedef R (__stdcall *fun_type)(#REPEAT_COMMA#A`i`#);
	enum{ arity = `n`};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret #COMMA_REPEAT#A`i` a`i`#) const{
		fun_(#REPEAT_COMMA#a`i`#), rcast<R>(ret);
	}
};

// 関数を関数オブジェクト化する
template<class R #COMMA_REPEAT#class A`i`#, R (__stdcall *fun_)(#REPEAT_COMMA#A`i`#)>
struct static_functor<R (__stdcall *)(#REPEAT_COMMA#A`i`#), fun_>{
	typedef R result_type; #REPEAT#typedef A`i` arg`i+1`_type; #
	enum{ arity = `n`};

	void operator()(FunctorParam& ret #COMMA_REPEAT#A`i` a`i`#) const{
		fun_(#REPEAT_COMMA#a`i`#), rcast<R>(ret);
	}
};

#endif

*/

template<int Method, class R >
struct nfun<R (*)(), Method>
	: nfun_base<0, functor<R (*)()>, Method, R>{};

// 関数を関数オブジェクト化する
template<class R >
struct functor<R (*)()>{
	typedef R result_type; 
	typedef R (*fun_type)();
	enum{ arity = 0};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret ) const{
		fun_(), rcast<R>(ret);
	}
};

template<int Method, class R, class C >
struct nfun<R (C::*)(), Method>
	: nfun_base<1, functor<R (C::*)()>, Method, R>{};

// メンバ関数を関数オブジェクト化する
template<class R, class C >
struct functor<R (C::*)()>{
	typedef R result_type; typedef C* arg1_type; 
	typedef R (C::*fun_type)();
	enum{ arity = 1};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret, C* self ) const{
		(self->*fun_)(), rcast<R>(ret);
	}
};

template<int Method, class R, class C >
struct nfun<R (C::*)() const, Method>
	: nfun_base<1, functor<R (C::*)() const>, Method, R>{};

// constメンバ関数を関数オブジェクト化する
template<class R, class C >
struct functor<R (C::*)() const>{
	typedef R result_type; typedef C* arg1_type; 
	typedef R (C::*fun_type)() const;
	enum{ arity = 1};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret, C* self ) const{
		(self->*fun_)(), rcast<R>(ret);
	}
};

////

// 関数を関数オブジェクト化する
template<class R , R (*fun_)()>
struct static_functor<R (*)(), fun_>{
	typedef R result_type; 
	enum{ arity = 0};

	void operator()(FunctorParam& ret ) const{
		fun_(), rcast<R>(ret);
	}
};

// メンバ関数を関数オブジェクト化する
template<class R, class C , R (C::*fun_)()>
struct static_functor<R (C::*)(), fun_>{
	typedef R result_type; typedef C* arg1_type; 
	enum{ arity = 1};

	void operator()(FunctorParam& ret, C* self ) const{
		(self->*fun_)(), rcast<R>(ret);
	}
};

// constメンバ関数を関数オブジェクト化する
template<class R, class C , R (C::*fun_)() const>
struct static_functor<R (C::*)() const, fun_>{
	typedef R result_type; typedef C* arg1_type; 
	enum{ arity = 1};

	void operator()(FunctorParam& ret, C* self ) const{
		(self->*fun_)(), rcast<R>(ret);
	}
};

// コンストラクタを関数オブジェクト化する
template<class T >
struct ctor_functor<T >{
	typedef SmartPtr<T> R;
	typedef R result_type; 
	enum{ arity = 0};

	void operator()(FunctorParam& ret ) const{
		xnew<T>(), rcast<R>(ret);
	}
};

// stdcall版
#if defined(_WIN32) && defined(_M_IX86)

template<int Method, class R >
struct nfun<R (__stdcall *)(), Method>
	: nfun_base<0, functor<R (__stdcall *)()>, Method, R>{};

// 関数を関数オブジェクト化する
template<class R >
struct functor<R (__stdcall *)()>{
	typedef R result_type; 
	typedef R (__stdcall *fun_type)();
	enum{ arity = 0};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret ) const{
		fun_(), rcast<R>(ret);
	}
};

// 関数を関数オブジェクト化する
template<class R , R (__stdcall *fun_)()>
struct static_functor<R (__stdcall *)(), fun_>{
	typedef R result_type; 
	enum{ arity = 0};

	void operator()(FunctorParam& ret ) const{
		fun_(), rcast<R>(ret);
	}
};

#endif


template<int Method, class R , class A0>
struct nfun<R (*)(A0), Method>
	: nfun_base<1, functor<R (*)(A0)>, Method, R>{};

// 関数を関数オブジェクト化する
template<class R , class A0>
struct functor<R (*)(A0)>{
	typedef R result_type; typedef A0 arg1_type; 
	typedef R (*fun_type)(A0);
	enum{ arity = 1};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret , A0 a0) const{
		fun_(a0), rcast<R>(ret);
	}
};

template<int Method, class R, class C , class A0>
struct nfun<R (C::*)(A0), Method>
	: nfun_base<2, functor<R (C::*)(A0)>, Method, R>{};

// メンバ関数を関数オブジェクト化する
template<class R, class C , class A0>
struct functor<R (C::*)(A0)>{
	typedef R result_type; typedef C* arg1_type; typedef A0 arg2_type; 
	typedef R (C::*fun_type)(A0);
	enum{ arity = 2};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret, C* self , A0 a0) const{
		(self->*fun_)(a0), rcast<R>(ret);
	}
};

template<int Method, class R, class C , class A0>
struct nfun<R (C::*)(A0) const, Method>
	: nfun_base<2, functor<R (C::*)(A0) const>, Method, R>{};

// constメンバ関数を関数オブジェクト化する
template<class R, class C , class A0>
struct functor<R (C::*)(A0) const>{
	typedef R result_type; typedef C* arg1_type; typedef A0 arg2_type; 
	typedef R (C::*fun_type)(A0) const;
	enum{ arity = 2};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret, C* self , A0 a0) const{
		(self->*fun_)(a0), rcast<R>(ret);
	}
};

////

// 関数を関数オブジェクト化する
template<class R , class A0, R (*fun_)(A0)>
struct static_functor<R (*)(A0), fun_>{
	typedef R result_type; typedef A0 arg1_type; 
	enum{ arity = 1};

	void operator()(FunctorParam& ret , A0 a0) const{
		fun_(a0), rcast<R>(ret);
	}
};

// メンバ関数を関数オブジェクト化する
template<class R, class C , class A0, R (C::*fun_)(A0)>
struct static_functor<R (C::*)(A0), fun_>{
	typedef R result_type; typedef C* arg1_type; typedef A0 arg2_type; 
	enum{ arity = 2};

	void operator()(FunctorParam& ret, C* self , A0 a0) const{
		(self->*fun_)(a0), rcast<R>(ret);
	}
};

// constメンバ関数を関数オブジェクト化する
template<class R, class C , class A0, R (C::*fun_)(A0) const>
struct static_functor<R (C::*)(A0) const, fun_>{
	typedef R result_type; typedef C* arg1_type; typedef A0 arg2_type; 
	enum{ arity = 2};

	void operator()(FunctorParam& ret, C* self , A0 a0) const{
		(self->*fun_)(a0), rcast<R>(ret);
	}
};

// コンストラクタを関数オブジェクト化する
template<class T , class A0>
struct ctor_functor<T , A0>{
	typedef SmartPtr<T> R;
	typedef R result_type; typedef A0 arg1_type; 
	enum{ arity = 1};

	void operator()(FunctorParam& ret , A0 a0) const{
		xnew<T>(a0), rcast<R>(ret);
	}
};

// stdcall版
#if defined(_WIN32) && defined(_M_IX86)

template<int Method, class R , class A0>
struct nfun<R (__stdcall *)(A0), Method>
	: nfun_base<1, functor<R (__stdcall *)(A0)>, Method, R>{};

// 関数を関数オブジェクト化する
template<class R , class A0>
struct functor<R (__stdcall *)(A0)>{
	typedef R result_type; typedef A0 arg1_type; 
	typedef R (__stdcall *fun_type)(A0);
	enum{ arity = 1};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret , A0 a0) const{
		fun_(a0), rcast<R>(ret);
	}
};

// 関数を関数オブジェクト化する
template<class R , class A0, R (__stdcall *fun_)(A0)>
struct static_functor<R (__stdcall *)(A0), fun_>{
	typedef R result_type; typedef A0 arg1_type; 
	enum{ arity = 1};

	void operator()(FunctorParam& ret , A0 a0) const{
		fun_(a0), rcast<R>(ret);
	}
};

#endif


template<int Method, class R , class A0, class A1>
struct nfun<R (*)(A0, A1), Method>
	: nfun_base<2, functor<R (*)(A0, A1)>, Method, R>{};

// 関数を関数オブジェクト化する
template<class R , class A0, class A1>
struct functor<R (*)(A0, A1)>{
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; 
	typedef R (*fun_type)(A0, A1);
	enum{ arity = 2};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret , A0 a0, A1 a1) const{
		fun_(a0, a1), rcast<R>(ret);
	}
};

template<int Method, class R, class C , class A0, class A1>
struct nfun<R (C::*)(A0, A1), Method>
	: nfun_base<3, functor<R (C::*)(A0, A1)>, Method, R>{};

// メンバ関数を関数オブジェクト化する
template<class R, class C , class A0, class A1>
struct functor<R (C::*)(A0, A1)>{
	typedef R result_type; typedef C* arg1_type; typedef A0 arg2_type; typedef A1 arg3_type; 
	typedef R (C::*fun_type)(A0, A1);
	enum{ arity = 3};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret, C* self , A0 a0, A1 a1) const{
		(self->*fun_)(a0, a1), rcast<R>(ret);
	}
};

template<int Method, class R, class C , class A0, class A1>
struct nfun<R (C::*)(A0, A1) const, Method>
	: nfun_base<3, functor<R (C::*)(A0, A1) const>, Method, R>{};

// constメンバ関数を関数オブジェクト化する
template<class R, class C , class A0, class A1>
struct functor<R (C::*)(A0, A1) const>{
	typedef R result_type; typedef C* arg1_type; typedef A0 arg2_type; typedef A1 arg3_type; 
	typedef R (C::*fun_type)(A0, A1) const;
	enum{ arity = 3};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret, C* self , A0 a0, A1 a1) const{
		(self->*fun_)(a0, a1), rcast<R>(ret);
	}
};

////

// 関数を関数オブジェクト化する
template<class R , class A0, class A1, R (*fun_)(A0, A1)>
struct static_functor<R (*)(A0, A1), fun_>{
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; 
	enum{ arity = 2};

	void operator()(FunctorParam& ret , A0 a0, A1 a1) const{
		fun_(a0, a1), rcast<R>(ret);
	}
};

// メンバ関数を関数オブジェクト化する
template<class R, class C , class A0, class A1, R (C::*fun_)(A0, A1)>
struct static_functor<R (C::*)(A0, A1), fun_>{
	typedef R result_type; typedef C* arg1_type; typedef A0 arg2_type; typedef A1 arg3_type; 
	enum{ arity = 3};

	void operator()(FunctorParam& ret, C* self , A0 a0, A1 a1) const{
		(self->*fun_)(a0, a1), rcast<R>(ret);
	}
};

// constメンバ関数を関数オブジェクト化する
template<class R, class C , class A0, class A1, R (C::*fun_)(A0, A1) const>
struct static_functor<R (C::*)(A0, A1) const, fun_>{
	typedef R result_type; typedef C* arg1_type; typedef A0 arg2_type; typedef A1 arg3_type; 
	enum{ arity = 3};

	void operator()(FunctorParam& ret, C* self , A0 a0, A1 a1) const{
		(self->*fun_)(a0, a1), rcast<R>(ret);
	}
};

// コンストラクタを関数オブジェクト化する
template<class T , class A0, class A1>
struct ctor_functor<T , A0, A1>{
	typedef SmartPtr<T> R;
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; 
	enum{ arity = 2};

	void operator()(FunctorParam& ret , A0 a0, A1 a1) const{
		xnew<T>(a0, a1), rcast<R>(ret);
	}
};

// stdcall版
#if defined(_WIN32) && defined(_M_IX86)

template<int Method, class R , class A0, class A1>
struct nfun<R (__stdcall *)(A0, A1), Method>
	: nfun_base<2, functor<R (__stdcall *)(A0, A1)>, Method, R>{};

// 関数を関数オブジェクト化する
template<class R , class A0, class A1>
struct functor<R (__stdcall *)(A0, A1)>{
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; 
	typedef R (__stdcall *fun_type)(A0, A1);
	enum{ arity = 2};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret , A0 a0, A1 a1) const{
		fun_(a0, a1), rcast<R>(ret);
	}
};

// 関数を関数オブジェクト化する
template<class R , class A0, class A1, R (__stdcall *fun_)(A0, A1)>
struct static_functor<R (__stdcall *)(A0, A1), fun_>{
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; 
	enum{ arity = 2};

	void operator()(FunctorParam& ret , A0 a0, A1 a1) const{
		fun_(a0, a1), rcast<R>(ret);
	}
};

#endif


template<int Method, class R , class A0, class A1, class A2>
struct nfun<R (*)(A0, A1, A2), Method>
	: nfun_base<3, functor<R (*)(A0, A1, A2)>, Method, R>{};

// 関数を関数オブジェクト化する
template<class R , class A0, class A1, class A2>
struct functor<R (*)(A0, A1, A2)>{
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; typedef A2 arg3_type; 
	typedef R (*fun_type)(A0, A1, A2);
	enum{ arity = 3};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret , A0 a0, A1 a1, A2 a2) const{
		fun_(a0, a1, a2), rcast<R>(ret);
	}
};

template<int Method, class R, class C , class A0, class A1, class A2>
struct nfun<R (C::*)(A0, A1, A2), Method>
	: nfun_base<4, functor<R (C::*)(A0, A1, A2)>, Method, R>{};

// メンバ関数を関数オブジェクト化する
template<class R, class C , class A0, class A1, class A2>
struct functor<R (C::*)(A0, A1, A2)>{
	typedef R result_type; typedef C* arg1_type; typedef A0 arg2_type; typedef A1 arg3_type; typedef A2 arg4_type; 
	typedef R (C::*fun_type)(A0, A1, A2);
	enum{ arity = 4};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret, C* self , A0 a0, A1 a1, A2 a2) const{
		(self->*fun_)(a0, a1, a2), rcast<R>(ret);
	}
};

template<int Method, class R, class C , class A0, class A1, class A2>
struct nfun<R (C::*)(A0, A1, A2) const, Method>
	: nfun_base<4, functor<R (C::*)(A0, A1, A2) const>, Method, R>{};

// constメンバ関数を関数オブジェクト化する
template<class R, class C , class A0, class A1, class A2>
struct functor<R (C::*)(A0, A1, A2) const>{
	typedef R result_type; typedef C* arg1_type; typedef A0 arg2_type; typedef A1 arg3_type; typedef A2 arg4_type; 
	typedef R (C::*fun_type)(A0, A1, A2) const;
	enum{ arity = 4};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret, C* self , A0 a0, A1 a1, A2 a2) const{
		(self->*fun_)(a0, a1, a2), rcast<R>(ret);
	}
};

////

// 関数を関数オブジェクト化する
template<class R , class A0, class A1, class A2, R (*fun_)(A0, A1, A2)>
struct static_functor<R (*)(A0, A1, A2), fun_>{
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; typedef A2 arg3_type; 
	enum{ arity = 3};

	void operator()(FunctorParam& ret , A0 a0, A1 a1, A2 a2) const{
		fun_(a0, a1, a2), rcast<R>(ret);
	}
};

// メンバ関数を関数オブジェクト化する
template<class R, class C , class A0, class A1, class A2, R (C::*fun_)(A0, A1, A2)>
struct static_functor<R (C::*)(A0, A1, A2), fun_>{
	typedef R result_type; typedef C* arg1_type; typedef A0 arg2_type; typedef A1 arg3_type; typedef A2 arg4_type; 
	enum{ arity = 4};

	void operator()(FunctorParam& ret, C* self , A0 a0, A1 a1, A2 a2) const{
		(self->*fun_)(a0, a1, a2), rcast<R>(ret);
	}
};

// constメンバ関数を関数オブジェクト化する
template<class R, class C , class A0, class A1, class A2, R (C::*fun_)(A0, A1, A2) const>
struct static_functor<R (C::*)(A0, A1, A2) const, fun_>{
	typedef R result_type; typedef C* arg1_type; typedef A0 arg2_type; typedef A1 arg3_type; typedef A2 arg4_type; 
	enum{ arity = 4};

	void operator()(FunctorParam& ret, C* self , A0 a0, A1 a1, A2 a2) const{
		(self->*fun_)(a0, a1, a2), rcast<R>(ret);
	}
};

// コンストラクタを関数オブジェクト化する
template<class T , class A0, class A1, class A2>
struct ctor_functor<T , A0, A1, A2>{
	typedef SmartPtr<T> R;
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; typedef A2 arg3_type; 
	enum{ arity = 3};

	void operator()(FunctorParam& ret , A0 a0, A1 a1, A2 a2) const{
		xnew<T>(a0, a1, a2), rcast<R>(ret);
	}
};

// stdcall版
#if defined(_WIN32) && defined(_M_IX86)

template<int Method, class R , class A0, class A1, class A2>
struct nfun<R (__stdcall *)(A0, A1, A2), Method>
	: nfun_base<3, functor<R (__stdcall *)(A0, A1, A2)>, Method, R>{};

// 関数を関数オブジェクト化する
template<class R , class A0, class A1, class A2>
struct functor<R (__stdcall *)(A0, A1, A2)>{
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; typedef A2 arg3_type; 
	typedef R (__stdcall *fun_type)(A0, A1, A2);
	enum{ arity = 3};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret , A0 a0, A1 a1, A2 a2) const{
		fun_(a0, a1, a2), rcast<R>(ret);
	}
};

// 関数を関数オブジェクト化する
template<class R , class A0, class A1, class A2, R (__stdcall *fun_)(A0, A1, A2)>
struct static_functor<R (__stdcall *)(A0, A1, A2), fun_>{
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; typedef A2 arg3_type; 
	enum{ arity = 3};

	void operator()(FunctorParam& ret , A0 a0, A1 a1, A2 a2) const{
		fun_(a0, a1, a2), rcast<R>(ret);
	}
};

#endif


template<int Method, class R , class A0, class A1, class A2, class A3>
struct nfun<R (*)(A0, A1, A2, A3), Method>
	: nfun_base<4, functor<R (*)(A0, A1, A2, A3)>, Method, R>{};

// 関数を関数オブジェクト化する
template<class R , class A0, class A1, class A2, class A3>
struct functor<R (*)(A0, A1, A2, A3)>{
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; typedef A2 arg3_type; typedef A3 arg4_type; 
	typedef R (*fun_type)(A0, A1, A2, A3);
	enum{ arity = 4};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret , A0 a0, A1 a1, A2 a2, A3 a3) const{
		fun_(a0, a1, a2, a3), rcast<R>(ret);
	}
};

template<int Method, class R, class C , class A0, class A1, class A2, class A3>
struct nfun<R (C::*)(A0, A1, A2, A3), Method>
	: nfun_base<5, functor<R (C::*)(A0, A1, A2, A3)>, Method, R>{};

// メンバ関数を関数オブジェクト化する
template<class R, class C , class A0, class A1, class A2, class A3>
struct functor<R (C::*)(A0, A1, A2, A3)>{
	typedef R result_type; typedef C* arg1_type; typedef A0 arg2_type; typedef A1 arg3_type; typedef A2 arg4_type; typedef A3 arg5_type; 
	typedef R (C::*fun_type)(A0, A1, A2, A3);
	enum{ arity = 5};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret, C* self , A0 a0, A1 a1, A2 a2, A3 a3) const{
		(self->*fun_)(a0, a1, a2, a3), rcast<R>(ret);
	}
};

template<int Method, class R, class C , class A0, class A1, class A2, class A3>
struct nfun<R (C::*)(A0, A1, A2, A3) const, Method>
	: nfun_base<5, functor<R (C::*)(A0, A1, A2, A3) const>, Method, R>{};

// constメンバ関数を関数オブジェクト化する
template<class R, class C , class A0, class A1, class A2, class A3>
struct functor<R (C::*)(A0, A1, A2, A3) const>{
	typedef R result_type; typedef C* arg1_type; typedef A0 arg2_type; typedef A1 arg3_type; typedef A2 arg4_type; typedef A3 arg5_type; 
	typedef R (C::*fun_type)(A0, A1, A2, A3) const;
	enum{ arity = 5};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret, C* self , A0 a0, A1 a1, A2 a2, A3 a3) const{
		(self->*fun_)(a0, a1, a2, a3), rcast<R>(ret);
	}
};

////

// 関数を関数オブジェクト化する
template<class R , class A0, class A1, class A2, class A3, R (*fun_)(A0, A1, A2, A3)>
struct static_functor<R (*)(A0, A1, A2, A3), fun_>{
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; typedef A2 arg3_type; typedef A3 arg4_type; 
	enum{ arity = 4};

	void operator()(FunctorParam& ret , A0 a0, A1 a1, A2 a2, A3 a3) const{
		fun_(a0, a1, a2, a3), rcast<R>(ret);
	}
};

// メンバ関数を関数オブジェクト化する
template<class R, class C , class A0, class A1, class A2, class A3, R (C::*fun_)(A0, A1, A2, A3)>
struct static_functor<R (C::*)(A0, A1, A2, A3), fun_>{
	typedef R result_type; typedef C* arg1_type; typedef A0 arg2_type; typedef A1 arg3_type; typedef A2 arg4_type; typedef A3 arg5_type; 
	enum{ arity = 5};

	void operator()(FunctorParam& ret, C* self , A0 a0, A1 a1, A2 a2, A3 a3) const{
		(self->*fun_)(a0, a1, a2, a3), rcast<R>(ret);
	}
};

// constメンバ関数を関数オブジェクト化する
template<class R, class C , class A0, class A1, class A2, class A3, R (C::*fun_)(A0, A1, A2, A3) const>
struct static_functor<R (C::*)(A0, A1, A2, A3) const, fun_>{
	typedef R result_type; typedef C* arg1_type; typedef A0 arg2_type; typedef A1 arg3_type; typedef A2 arg4_type; typedef A3 arg5_type; 
	enum{ arity = 5};

	void operator()(FunctorParam& ret, C* self , A0 a0, A1 a1, A2 a2, A3 a3) const{
		(self->*fun_)(a0, a1, a2, a3), rcast<R>(ret);
	}
};

// コンストラクタを関数オブジェクト化する
template<class T , class A0, class A1, class A2, class A3>
struct ctor_functor<T , A0, A1, A2, A3>{
	typedef SmartPtr<T> R;
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; typedef A2 arg3_type; typedef A3 arg4_type; 
	enum{ arity = 4};

	void operator()(FunctorParam& ret , A0 a0, A1 a1, A2 a2, A3 a3) const{
		xnew<T>(a0, a1, a2, a3), rcast<R>(ret);
	}
};

// stdcall版
#if defined(_WIN32) && defined(_M_IX86)

template<int Method, class R , class A0, class A1, class A2, class A3>
struct nfun<R (__stdcall *)(A0, A1, A2, A3), Method>
	: nfun_base<4, functor<R (__stdcall *)(A0, A1, A2, A3)>, Method, R>{};

// 関数を関数オブジェクト化する
template<class R , class A0, class A1, class A2, class A3>
struct functor<R (__stdcall *)(A0, A1, A2, A3)>{
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; typedef A2 arg3_type; typedef A3 arg4_type; 
	typedef R (__stdcall *fun_type)(A0, A1, A2, A3);
	enum{ arity = 4};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret , A0 a0, A1 a1, A2 a2, A3 a3) const{
		fun_(a0, a1, a2, a3), rcast<R>(ret);
	}
};

// 関数を関数オブジェクト化する
template<class R , class A0, class A1, class A2, class A3, R (__stdcall *fun_)(A0, A1, A2, A3)>
struct static_functor<R (__stdcall *)(A0, A1, A2, A3), fun_>{
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; typedef A2 arg3_type; typedef A3 arg4_type; 
	enum{ arity = 4};

	void operator()(FunctorParam& ret , A0 a0, A1 a1, A2 a2, A3 a3) const{
		fun_(a0, a1, a2, a3), rcast<R>(ret);
	}
};

#endif


template<int Method, class R , class A0, class A1, class A2, class A3, class A4>
struct nfun<R (*)(A0, A1, A2, A3, A4), Method>
	: nfun_base<5, functor<R (*)(A0, A1, A2, A3, A4)>, Method, R>{};

// 関数を関数オブジェクト化する
template<class R , class A0, class A1, class A2, class A3, class A4>
struct functor<R (*)(A0, A1, A2, A3, A4)>{
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; typedef A2 arg3_type; typedef A3 arg4_type; typedef A4 arg5_type; 
	typedef R (*fun_type)(A0, A1, A2, A3, A4);
	enum{ arity = 5};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4) const{
		fun_(a0, a1, a2, a3, a4), rcast<R>(ret);
	}
};

template<int Method, class R, class C , class A0, class A1, class A2, class A3, class A4>
struct nfun<R (C::*)(A0, A1, A2, A3, A4), Method>
	: nfun_base<6, functor<R (C::*)(A0, A1, A2, A3, A4)>, Method, R>{};

// メンバ関数を関数オブジェクト化する
template<class R, class C , class A0, class A1, class A2, class A3, class A4>
struct functor<R (C::*)(A0, A1, A2, A3, A4)>{
	typedef R result_type; typedef C* arg1_type; typedef A0 arg2_type; typedef A1 arg3_type; typedef A2 arg4_type; typedef A3 arg5_type; typedef A4 arg6_type; 
	typedef R (C::*fun_type)(A0, A1, A2, A3, A4);
	enum{ arity = 6};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret, C* self , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4) const{
		(self->*fun_)(a0, a1, a2, a3, a4), rcast<R>(ret);
	}
};

template<int Method, class R, class C , class A0, class A1, class A2, class A3, class A4>
struct nfun<R (C::*)(A0, A1, A2, A3, A4) const, Method>
	: nfun_base<6, functor<R (C::*)(A0, A1, A2, A3, A4) const>, Method, R>{};

// constメンバ関数を関数オブジェクト化する
template<class R, class C , class A0, class A1, class A2, class A3, class A4>
struct functor<R (C::*)(A0, A1, A2, A3, A4) const>{
	typedef R result_type; typedef C* arg1_type; typedef A0 arg2_type; typedef A1 arg3_type; typedef A2 arg4_type; typedef A3 arg5_type; typedef A4 arg6_type; 
	typedef R (C::*fun_type)(A0, A1, A2, A3, A4) const;
	enum{ arity = 6};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret, C* self , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4) const{
		(self->*fun_)(a0, a1, a2, a3, a4), rcast<R>(ret);
	}
};

////

// 関数を関数オブジェクト化する
template<class R , class A0, class A1, class A2, class A3, class A4, R (*fun_)(A0, A1, A2, A3, A4)>
struct static_functor<R (*)(A0, A1, A2, A3, A4), fun_>{
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; typedef A2 arg3_type; typedef A3 arg4_type; typedef A4 arg5_type; 
	enum{ arity = 5};

	void operator()(FunctorParam& ret , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4) const{
		fun_(a0, a1, a2, a3, a4), rcast<R>(ret);
	}
};

// メンバ関数を関数オブジェクト化する
template<class R, class C , class A0, class A1, class A2, class A3, class A4, R (C::*fun_)(A0, A1, A2, A3, A4)>
struct static_functor<R (C::*)(A0, A1, A2, A3, A4), fun_>{
	typedef R result_type; typedef C* arg1_type; typedef A0 arg2_type; typedef A1 arg3_type; typedef A2 arg4_type; typedef A3 arg5_type; typedef A4 arg6_type; 
	enum{ arity = 6};

	void operator()(FunctorParam& ret, C* self , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4) const{
		(self->*fun_)(a0, a1, a2, a3, a4), rcast<R>(ret);
	}
};

// constメンバ関数を関数オブジェクト化する
template<class R, class C , class A0, class A1, class A2, class A3, class A4, R (C::*fun_)(A0, A1, A2, A3, A4) const>
struct static_functor<R (C::*)(A0, A1, A2, A3, A4) const, fun_>{
	typedef R result_type; typedef C* arg1_type; typedef A0 arg2_type; typedef A1 arg3_type; typedef A2 arg4_type; typedef A3 arg5_type; typedef A4 arg6_type; 
	enum{ arity = 6};

	void operator()(FunctorParam& ret, C* self , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4) const{
		(self->*fun_)(a0, a1, a2, a3, a4), rcast<R>(ret);
	}
};

// コンストラクタを関数オブジェクト化する
template<class T , class A0, class A1, class A2, class A3, class A4>
struct ctor_functor<T , A0, A1, A2, A3, A4>{
	typedef SmartPtr<T> R;
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; typedef A2 arg3_type; typedef A3 arg4_type; typedef A4 arg5_type; 
	enum{ arity = 5};

	void operator()(FunctorParam& ret , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4) const{
		xnew<T>(a0, a1, a2, a3, a4), rcast<R>(ret);
	}
};

// stdcall版
#if defined(_WIN32) && defined(_M_IX86)

template<int Method, class R , class A0, class A1, class A2, class A3, class A4>
struct nfun<R (__stdcall *)(A0, A1, A2, A3, A4), Method>
	: nfun_base<5, functor<R (__stdcall *)(A0, A1, A2, A3, A4)>, Method, R>{};

// 関数を関数オブジェクト化する
template<class R , class A0, class A1, class A2, class A3, class A4>
struct functor<R (__stdcall *)(A0, A1, A2, A3, A4)>{
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; typedef A2 arg3_type; typedef A3 arg4_type; typedef A4 arg5_type; 
	typedef R (__stdcall *fun_type)(A0, A1, A2, A3, A4);
	enum{ arity = 5};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4) const{
		fun_(a0, a1, a2, a3, a4), rcast<R>(ret);
	}
};

// 関数を関数オブジェクト化する
template<class R , class A0, class A1, class A2, class A3, class A4, R (__stdcall *fun_)(A0, A1, A2, A3, A4)>
struct static_functor<R (__stdcall *)(A0, A1, A2, A3, A4), fun_>{
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; typedef A2 arg3_type; typedef A3 arg4_type; typedef A4 arg5_type; 
	enum{ arity = 5};

	void operator()(FunctorParam& ret , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4) const{
		fun_(a0, a1, a2, a3, a4), rcast<R>(ret);
	}
};

#endif


template<int Method, class R , class A0, class A1, class A2, class A3, class A4, class A5>
struct nfun<R (*)(A0, A1, A2, A3, A4, A5), Method>
	: nfun_base<6, functor<R (*)(A0, A1, A2, A3, A4, A5)>, Method, R>{};

// 関数を関数オブジェクト化する
template<class R , class A0, class A1, class A2, class A3, class A4, class A5>
struct functor<R (*)(A0, A1, A2, A3, A4, A5)>{
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; typedef A2 arg3_type; typedef A3 arg4_type; typedef A4 arg5_type; typedef A5 arg6_type; 
	typedef R (*fun_type)(A0, A1, A2, A3, A4, A5);
	enum{ arity = 6};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const{
		fun_(a0, a1, a2, a3, a4, a5), rcast<R>(ret);
	}
};

template<int Method, class R, class C , class A0, class A1, class A2, class A3, class A4, class A5>
struct nfun<R (C::*)(A0, A1, A2, A3, A4, A5), Method>
	: nfun_base<7, functor<R (C::*)(A0, A1, A2, A3, A4, A5)>, Method, R>{};

// メンバ関数を関数オブジェクト化する
template<class R, class C , class A0, class A1, class A2, class A3, class A4, class A5>
struct functor<R (C::*)(A0, A1, A2, A3, A4, A5)>{
	typedef R result_type; typedef C* arg1_type; typedef A0 arg2_type; typedef A1 arg3_type; typedef A2 arg4_type; typedef A3 arg5_type; typedef A4 arg6_type; typedef A5 arg7_type; 
	typedef R (C::*fun_type)(A0, A1, A2, A3, A4, A5);
	enum{ arity = 7};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret, C* self , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const{
		(self->*fun_)(a0, a1, a2, a3, a4, a5), rcast<R>(ret);
	}
};

template<int Method, class R, class C , class A0, class A1, class A2, class A3, class A4, class A5>
struct nfun<R (C::*)(A0, A1, A2, A3, A4, A5) const, Method>
	: nfun_base<7, functor<R (C::*)(A0, A1, A2, A3, A4, A5) const>, Method, R>{};

// constメンバ関数を関数オブジェクト化する
template<class R, class C , class A0, class A1, class A2, class A3, class A4, class A5>
struct functor<R (C::*)(A0, A1, A2, A3, A4, A5) const>{
	typedef R result_type; typedef C* arg1_type; typedef A0 arg2_type; typedef A1 arg3_type; typedef A2 arg4_type; typedef A3 arg5_type; typedef A4 arg6_type; typedef A5 arg7_type; 
	typedef R (C::*fun_type)(A0, A1, A2, A3, A4, A5) const;
	enum{ arity = 7};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret, C* self , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const{
		(self->*fun_)(a0, a1, a2, a3, a4, a5), rcast<R>(ret);
	}
};

////

// 関数を関数オブジェクト化する
template<class R , class A0, class A1, class A2, class A3, class A4, class A5, R (*fun_)(A0, A1, A2, A3, A4, A5)>
struct static_functor<R (*)(A0, A1, A2, A3, A4, A5), fun_>{
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; typedef A2 arg3_type; typedef A3 arg4_type; typedef A4 arg5_type; typedef A5 arg6_type; 
	enum{ arity = 6};

	void operator()(FunctorParam& ret , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const{
		fun_(a0, a1, a2, a3, a4, a5), rcast<R>(ret);
	}
};

// メンバ関数を関数オブジェクト化する
template<class R, class C , class A0, class A1, class A2, class A3, class A4, class A5, R (C::*fun_)(A0, A1, A2, A3, A4, A5)>
struct static_functor<R (C::*)(A0, A1, A2, A3, A4, A5), fun_>{
	typedef R result_type; typedef C* arg1_type; typedef A0 arg2_type; typedef A1 arg3_type; typedef A2 arg4_type; typedef A3 arg5_type; typedef A4 arg6_type; typedef A5 arg7_type; 
	enum{ arity = 7};

	void operator()(FunctorParam& ret, C* self , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const{
		(self->*fun_)(a0, a1, a2, a3, a4, a5), rcast<R>(ret);
	}
};

// constメンバ関数を関数オブジェクト化する
template<class R, class C , class A0, class A1, class A2, class A3, class A4, class A5, R (C::*fun_)(A0, A1, A2, A3, A4, A5) const>
struct static_functor<R (C::*)(A0, A1, A2, A3, A4, A5) const, fun_>{
	typedef R result_type; typedef C* arg1_type; typedef A0 arg2_type; typedef A1 arg3_type; typedef A2 arg4_type; typedef A3 arg5_type; typedef A4 arg6_type; typedef A5 arg7_type; 
	enum{ arity = 7};

	void operator()(FunctorParam& ret, C* self , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const{
		(self->*fun_)(a0, a1, a2, a3, a4, a5), rcast<R>(ret);
	}
};

// コンストラクタを関数オブジェクト化する
template<class T , class A0, class A1, class A2, class A3, class A4, class A5>
struct ctor_functor<T , A0, A1, A2, A3, A4, A5>{
	typedef SmartPtr<T> R;
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; typedef A2 arg3_type; typedef A3 arg4_type; typedef A4 arg5_type; typedef A5 arg6_type; 
	enum{ arity = 6};

	void operator()(FunctorParam& ret , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const{
		xnew<T>(a0, a1, a2, a3, a4, a5), rcast<R>(ret);
	}
};

// stdcall版
#if defined(_WIN32) && defined(_M_IX86)

template<int Method, class R , class A0, class A1, class A2, class A3, class A4, class A5>
struct nfun<R (__stdcall *)(A0, A1, A2, A3, A4, A5), Method>
	: nfun_base<6, functor<R (__stdcall *)(A0, A1, A2, A3, A4, A5)>, Method, R>{};

// 関数を関数オブジェクト化する
template<class R , class A0, class A1, class A2, class A3, class A4, class A5>
struct functor<R (__stdcall *)(A0, A1, A2, A3, A4, A5)>{
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; typedef A2 arg3_type; typedef A3 arg4_type; typedef A4 arg5_type; typedef A5 arg6_type; 
	typedef R (__stdcall *fun_type)(A0, A1, A2, A3, A4, A5);
	enum{ arity = 6};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const{
		fun_(a0, a1, a2, a3, a4, a5), rcast<R>(ret);
	}
};

// 関数を関数オブジェクト化する
template<class R , class A0, class A1, class A2, class A3, class A4, class A5, R (__stdcall *fun_)(A0, A1, A2, A3, A4, A5)>
struct static_functor<R (__stdcall *)(A0, A1, A2, A3, A4, A5), fun_>{
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; typedef A2 arg3_type; typedef A3 arg4_type; typedef A4 arg5_type; typedef A5 arg6_type; 
	enum{ arity = 6};

	void operator()(FunctorParam& ret , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const{
		fun_(a0, a1, a2, a3, a4, a5), rcast<R>(ret);
	}
};

#endif


template<int Method, class R , class A0, class A1, class A2, class A3, class A4, class A5, class A6>
struct nfun<R (*)(A0, A1, A2, A3, A4, A5, A6), Method>
	: nfun_base<7, functor<R (*)(A0, A1, A2, A3, A4, A5, A6)>, Method, R>{};

// 関数を関数オブジェクト化する
template<class R , class A0, class A1, class A2, class A3, class A4, class A5, class A6>
struct functor<R (*)(A0, A1, A2, A3, A4, A5, A6)>{
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; typedef A2 arg3_type; typedef A3 arg4_type; typedef A4 arg5_type; typedef A5 arg6_type; typedef A6 arg7_type; 
	typedef R (*fun_type)(A0, A1, A2, A3, A4, A5, A6);
	enum{ arity = 7};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) const{
		fun_(a0, a1, a2, a3, a4, a5, a6), rcast<R>(ret);
	}
};

template<int Method, class R, class C , class A0, class A1, class A2, class A3, class A4, class A5, class A6>
struct nfun<R (C::*)(A0, A1, A2, A3, A4, A5, A6), Method>
	: nfun_base<8, functor<R (C::*)(A0, A1, A2, A3, A4, A5, A6)>, Method, R>{};

// メンバ関数を関数オブジェクト化する
template<class R, class C , class A0, class A1, class A2, class A3, class A4, class A5, class A6>
struct functor<R (C::*)(A0, A1, A2, A3, A4, A5, A6)>{
	typedef R result_type; typedef C* arg1_type; typedef A0 arg2_type; typedef A1 arg3_type; typedef A2 arg4_type; typedef A3 arg5_type; typedef A4 arg6_type; typedef A5 arg7_type; typedef A6 arg8_type; 
	typedef R (C::*fun_type)(A0, A1, A2, A3, A4, A5, A6);
	enum{ arity = 8};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret, C* self , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) const{
		(self->*fun_)(a0, a1, a2, a3, a4, a5, a6), rcast<R>(ret);
	}
};

template<int Method, class R, class C , class A0, class A1, class A2, class A3, class A4, class A5, class A6>
struct nfun<R (C::*)(A0, A1, A2, A3, A4, A5, A6) const, Method>
	: nfun_base<8, functor<R (C::*)(A0, A1, A2, A3, A4, A5, A6) const>, Method, R>{};

// constメンバ関数を関数オブジェクト化する
template<class R, class C , class A0, class A1, class A2, class A3, class A4, class A5, class A6>
struct functor<R (C::*)(A0, A1, A2, A3, A4, A5, A6) const>{
	typedef R result_type; typedef C* arg1_type; typedef A0 arg2_type; typedef A1 arg3_type; typedef A2 arg4_type; typedef A3 arg5_type; typedef A4 arg6_type; typedef A5 arg7_type; typedef A6 arg8_type; 
	typedef R (C::*fun_type)(A0, A1, A2, A3, A4, A5, A6) const;
	enum{ arity = 8};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret, C* self , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) const{
		(self->*fun_)(a0, a1, a2, a3, a4, a5, a6), rcast<R>(ret);
	}
};

////

// 関数を関数オブジェクト化する
template<class R , class A0, class A1, class A2, class A3, class A4, class A5, class A6, R (*fun_)(A0, A1, A2, A3, A4, A5, A6)>
struct static_functor<R (*)(A0, A1, A2, A3, A4, A5, A6), fun_>{
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; typedef A2 arg3_type; typedef A3 arg4_type; typedef A4 arg5_type; typedef A5 arg6_type; typedef A6 arg7_type; 
	enum{ arity = 7};

	void operator()(FunctorParam& ret , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) const{
		fun_(a0, a1, a2, a3, a4, a5, a6), rcast<R>(ret);
	}
};

// メンバ関数を関数オブジェクト化する
template<class R, class C , class A0, class A1, class A2, class A3, class A4, class A5, class A6, R (C::*fun_)(A0, A1, A2, A3, A4, A5, A6)>
struct static_functor<R (C::*)(A0, A1, A2, A3, A4, A5, A6), fun_>{
	typedef R result_type; typedef C* arg1_type; typedef A0 arg2_type; typedef A1 arg3_type; typedef A2 arg4_type; typedef A3 arg5_type; typedef A4 arg6_type; typedef A5 arg7_type; typedef A6 arg8_type; 
	enum{ arity = 8};

	void operator()(FunctorParam& ret, C* self , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) const{
		(self->*fun_)(a0, a1, a2, a3, a4, a5, a6), rcast<R>(ret);
	}
};

// constメンバ関数を関数オブジェクト化する
template<class R, class C , class A0, class A1, class A2, class A3, class A4, class A5, class A6, R (C::*fun_)(A0, A1, A2, A3, A4, A5, A6) const>
struct static_functor<R (C::*)(A0, A1, A2, A3, A4, A5, A6) const, fun_>{
	typedef R result_type; typedef C* arg1_type; typedef A0 arg2_type; typedef A1 arg3_type; typedef A2 arg4_type; typedef A3 arg5_type; typedef A4 arg6_type; typedef A5 arg7_type; typedef A6 arg8_type; 
	enum{ arity = 8};

	void operator()(FunctorParam& ret, C* self , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) const{
		(self->*fun_)(a0, a1, a2, a3, a4, a5, a6), rcast<R>(ret);
	}
};

// コンストラクタを関数オブジェクト化する
template<class T , class A0, class A1, class A2, class A3, class A4, class A5, class A6>
struct ctor_functor<T , A0, A1, A2, A3, A4, A5, A6>{
	typedef SmartPtr<T> R;
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; typedef A2 arg3_type; typedef A3 arg4_type; typedef A4 arg5_type; typedef A5 arg6_type; typedef A6 arg7_type; 
	enum{ arity = 7};

	void operator()(FunctorParam& ret , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) const{
		xnew<T>(a0, a1, a2, a3, a4, a5, a6), rcast<R>(ret);
	}
};

// stdcall版
#if defined(_WIN32) && defined(_M_IX86)

template<int Method, class R , class A0, class A1, class A2, class A3, class A4, class A5, class A6>
struct nfun<R (__stdcall *)(A0, A1, A2, A3, A4, A5, A6), Method>
	: nfun_base<7, functor<R (__stdcall *)(A0, A1, A2, A3, A4, A5, A6)>, Method, R>{};

// 関数を関数オブジェクト化する
template<class R , class A0, class A1, class A2, class A3, class A4, class A5, class A6>
struct functor<R (__stdcall *)(A0, A1, A2, A3, A4, A5, A6)>{
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; typedef A2 arg3_type; typedef A3 arg4_type; typedef A4 arg5_type; typedef A5 arg6_type; typedef A6 arg7_type; 
	typedef R (__stdcall *fun_type)(A0, A1, A2, A3, A4, A5, A6);
	enum{ arity = 7};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) const{
		fun_(a0, a1, a2, a3, a4, a5, a6), rcast<R>(ret);
	}
};

// 関数を関数オブジェクト化する
template<class R , class A0, class A1, class A2, class A3, class A4, class A5, class A6, R (__stdcall *fun_)(A0, A1, A2, A3, A4, A5, A6)>
struct static_functor<R (__stdcall *)(A0, A1, A2, A3, A4, A5, A6), fun_>{
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; typedef A2 arg3_type; typedef A3 arg4_type; typedef A4 arg5_type; typedef A5 arg6_type; typedef A6 arg7_type; 
	enum{ arity = 7};

	void operator()(FunctorParam& ret , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) const{
		fun_(a0, a1, a2, a3, a4, a5, a6), rcast<R>(ret);
	}
};

#endif


template<int Method, class R , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
struct nfun<R (*)(A0, A1, A2, A3, A4, A5, A6, A7), Method>
	: nfun_base<8, functor<R (*)(A0, A1, A2, A3, A4, A5, A6, A7)>, Method, R>{};

// 関数を関数オブジェクト化する
template<class R , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
struct functor<R (*)(A0, A1, A2, A3, A4, A5, A6, A7)>{
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; typedef A2 arg3_type; typedef A3 arg4_type; typedef A4 arg5_type; typedef A5 arg6_type; typedef A6 arg7_type; typedef A7 arg8_type; 
	typedef R (*fun_type)(A0, A1, A2, A3, A4, A5, A6, A7);
	enum{ arity = 8};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const{
		fun_(a0, a1, a2, a3, a4, a5, a6, a7), rcast<R>(ret);
	}
};

template<int Method, class R, class C , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
struct nfun<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7), Method>
	: nfun_base<9, functor<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7)>, Method, R>{};

// メンバ関数を関数オブジェクト化する
template<class R, class C , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
struct functor<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7)>{
	typedef R result_type; typedef C* arg1_type; typedef A0 arg2_type; typedef A1 arg3_type; typedef A2 arg4_type; typedef A3 arg5_type; typedef A4 arg6_type; typedef A5 arg7_type; typedef A6 arg8_type; typedef A7 arg9_type; 
	typedef R (C::*fun_type)(A0, A1, A2, A3, A4, A5, A6, A7);
	enum{ arity = 9};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret, C* self , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const{
		(self->*fun_)(a0, a1, a2, a3, a4, a5, a6, a7), rcast<R>(ret);
	}
};

template<int Method, class R, class C , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
struct nfun<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7) const, Method>
	: nfun_base<9, functor<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7) const>, Method, R>{};

// constメンバ関数を関数オブジェクト化する
template<class R, class C , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
struct functor<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7) const>{
	typedef R result_type; typedef C* arg1_type; typedef A0 arg2_type; typedef A1 arg3_type; typedef A2 arg4_type; typedef A3 arg5_type; typedef A4 arg6_type; typedef A5 arg7_type; typedef A6 arg8_type; typedef A7 arg9_type; 
	typedef R (C::*fun_type)(A0, A1, A2, A3, A4, A5, A6, A7) const;
	enum{ arity = 9};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret, C* self , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const{
		(self->*fun_)(a0, a1, a2, a3, a4, a5, a6, a7), rcast<R>(ret);
	}
};

////

// 関数を関数オブジェクト化する
template<class R , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, R (*fun_)(A0, A1, A2, A3, A4, A5, A6, A7)>
struct static_functor<R (*)(A0, A1, A2, A3, A4, A5, A6, A7), fun_>{
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; typedef A2 arg3_type; typedef A3 arg4_type; typedef A4 arg5_type; typedef A5 arg6_type; typedef A6 arg7_type; typedef A7 arg8_type; 
	enum{ arity = 8};

	void operator()(FunctorParam& ret , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const{
		fun_(a0, a1, a2, a3, a4, a5, a6, a7), rcast<R>(ret);
	}
};

// メンバ関数を関数オブジェクト化する
template<class R, class C , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, R (C::*fun_)(A0, A1, A2, A3, A4, A5, A6, A7)>
struct static_functor<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7), fun_>{
	typedef R result_type; typedef C* arg1_type; typedef A0 arg2_type; typedef A1 arg3_type; typedef A2 arg4_type; typedef A3 arg5_type; typedef A4 arg6_type; typedef A5 arg7_type; typedef A6 arg8_type; typedef A7 arg9_type; 
	enum{ arity = 9};

	void operator()(FunctorParam& ret, C* self , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const{
		(self->*fun_)(a0, a1, a2, a3, a4, a5, a6, a7), rcast<R>(ret);
	}
};

// constメンバ関数を関数オブジェクト化する
template<class R, class C , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, R (C::*fun_)(A0, A1, A2, A3, A4, A5, A6, A7) const>
struct static_functor<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7) const, fun_>{
	typedef R result_type; typedef C* arg1_type; typedef A0 arg2_type; typedef A1 arg3_type; typedef A2 arg4_type; typedef A3 arg5_type; typedef A4 arg6_type; typedef A5 arg7_type; typedef A6 arg8_type; typedef A7 arg9_type; 
	enum{ arity = 9};

	void operator()(FunctorParam& ret, C* self , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const{
		(self->*fun_)(a0, a1, a2, a3, a4, a5, a6, a7), rcast<R>(ret);
	}
};

// コンストラクタを関数オブジェクト化する
template<class T , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
struct ctor_functor<T , A0, A1, A2, A3, A4, A5, A6, A7>{
	typedef SmartPtr<T> R;
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; typedef A2 arg3_type; typedef A3 arg4_type; typedef A4 arg5_type; typedef A5 arg6_type; typedef A6 arg7_type; typedef A7 arg8_type; 
	enum{ arity = 8};

	void operator()(FunctorParam& ret , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const{
		xnew<T>(a0, a1, a2, a3, a4, a5, a6, a7), rcast<R>(ret);
	}
};

// stdcall版
#if defined(_WIN32) && defined(_M_IX86)

template<int Method, class R , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
struct nfun<R (__stdcall *)(A0, A1, A2, A3, A4, A5, A6, A7), Method>
	: nfun_base<8, functor<R (__stdcall *)(A0, A1, A2, A3, A4, A5, A6, A7)>, Method, R>{};

// 関数を関数オブジェクト化する
template<class R , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
struct functor<R (__stdcall *)(A0, A1, A2, A3, A4, A5, A6, A7)>{
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; typedef A2 arg3_type; typedef A3 arg4_type; typedef A4 arg5_type; typedef A5 arg6_type; typedef A6 arg7_type; typedef A7 arg8_type; 
	typedef R (__stdcall *fun_type)(A0, A1, A2, A3, A4, A5, A6, A7);
	enum{ arity = 8};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const{
		fun_(a0, a1, a2, a3, a4, a5, a6, a7), rcast<R>(ret);
	}
};

// 関数を関数オブジェクト化する
template<class R , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, R (__stdcall *fun_)(A0, A1, A2, A3, A4, A5, A6, A7)>
struct static_functor<R (__stdcall *)(A0, A1, A2, A3, A4, A5, A6, A7), fun_>{
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; typedef A2 arg3_type; typedef A3 arg4_type; typedef A4 arg5_type; typedef A5 arg6_type; typedef A6 arg7_type; typedef A7 arg8_type; 
	enum{ arity = 8};

	void operator()(FunctorParam& ret , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const{
		fun_(a0, a1, a2, a3, a4, a5, a6, a7), rcast<R>(ret);
	}
};

#endif


template<int Method, class R , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
struct nfun<R (*)(A0, A1, A2, A3, A4, A5, A6, A7, A8), Method>
	: nfun_base<9, functor<R (*)(A0, A1, A2, A3, A4, A5, A6, A7, A8)>, Method, R>{};

// 関数を関数オブジェクト化する
template<class R , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
struct functor<R (*)(A0, A1, A2, A3, A4, A5, A6, A7, A8)>{
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; typedef A2 arg3_type; typedef A3 arg4_type; typedef A4 arg5_type; typedef A5 arg6_type; typedef A6 arg7_type; typedef A7 arg8_type; typedef A8 arg9_type; 
	typedef R (*fun_type)(A0, A1, A2, A3, A4, A5, A6, A7, A8);
	enum{ arity = 9};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) const{
		fun_(a0, a1, a2, a3, a4, a5, a6, a7, a8), rcast<R>(ret);
	}
};

template<int Method, class R, class C , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
struct nfun<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8), Method>
	: nfun_base<10, functor<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8)>, Method, R>{};

// メンバ関数を関数オブジェクト化する
template<class R, class C , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
struct functor<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8)>{
	typedef R result_type; typedef C* arg1_type; typedef A0 arg2_type; typedef A1 arg3_type; typedef A2 arg4_type; typedef A3 arg5_type; typedef A4 arg6_type; typedef A5 arg7_type; typedef A6 arg8_type; typedef A7 arg9_type; typedef A8 arg10_type; 
	typedef R (C::*fun_type)(A0, A1, A2, A3, A4, A5, A6, A7, A8);
	enum{ arity = 10};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret, C* self , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) const{
		(self->*fun_)(a0, a1, a2, a3, a4, a5, a6, a7, a8), rcast<R>(ret);
	}
};

template<int Method, class R, class C , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
struct nfun<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8) const, Method>
	: nfun_base<10, functor<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8) const>, Method, R>{};

// constメンバ関数を関数オブジェクト化する
template<class R, class C , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
struct functor<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8) const>{
	typedef R result_type; typedef C* arg1_type; typedef A0 arg2_type; typedef A1 arg3_type; typedef A2 arg4_type; typedef A3 arg5_type; typedef A4 arg6_type; typedef A5 arg7_type; typedef A6 arg8_type; typedef A7 arg9_type; typedef A8 arg10_type; 
	typedef R (C::*fun_type)(A0, A1, A2, A3, A4, A5, A6, A7, A8) const;
	enum{ arity = 10};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret, C* self , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) const{
		(self->*fun_)(a0, a1, a2, a3, a4, a5, a6, a7, a8), rcast<R>(ret);
	}
};

////

// 関数を関数オブジェクト化する
template<class R , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, R (*fun_)(A0, A1, A2, A3, A4, A5, A6, A7, A8)>
struct static_functor<R (*)(A0, A1, A2, A3, A4, A5, A6, A7, A8), fun_>{
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; typedef A2 arg3_type; typedef A3 arg4_type; typedef A4 arg5_type; typedef A5 arg6_type; typedef A6 arg7_type; typedef A7 arg8_type; typedef A8 arg9_type; 
	enum{ arity = 9};

	void operator()(FunctorParam& ret , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) const{
		fun_(a0, a1, a2, a3, a4, a5, a6, a7, a8), rcast<R>(ret);
	}
};

// メンバ関数を関数オブジェクト化する
template<class R, class C , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, R (C::*fun_)(A0, A1, A2, A3, A4, A5, A6, A7, A8)>
struct static_functor<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8), fun_>{
	typedef R result_type; typedef C* arg1_type; typedef A0 arg2_type; typedef A1 arg3_type; typedef A2 arg4_type; typedef A3 arg5_type; typedef A4 arg6_type; typedef A5 arg7_type; typedef A6 arg8_type; typedef A7 arg9_type; typedef A8 arg10_type; 
	enum{ arity = 10};

	void operator()(FunctorParam& ret, C* self , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) const{
		(self->*fun_)(a0, a1, a2, a3, a4, a5, a6, a7, a8), rcast<R>(ret);
	}
};

// constメンバ関数を関数オブジェクト化する
template<class R, class C , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, R (C::*fun_)(A0, A1, A2, A3, A4, A5, A6, A7, A8) const>
struct static_functor<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8) const, fun_>{
	typedef R result_type; typedef C* arg1_type; typedef A0 arg2_type; typedef A1 arg3_type; typedef A2 arg4_type; typedef A3 arg5_type; typedef A4 arg6_type; typedef A5 arg7_type; typedef A6 arg8_type; typedef A7 arg9_type; typedef A8 arg10_type; 
	enum{ arity = 10};

	void operator()(FunctorParam& ret, C* self , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) const{
		(self->*fun_)(a0, a1, a2, a3, a4, a5, a6, a7, a8), rcast<R>(ret);
	}
};

// コンストラクタを関数オブジェクト化する
template<class T , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
struct ctor_functor<T , A0, A1, A2, A3, A4, A5, A6, A7, A8>{
	typedef SmartPtr<T> R;
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; typedef A2 arg3_type; typedef A3 arg4_type; typedef A4 arg5_type; typedef A5 arg6_type; typedef A6 arg7_type; typedef A7 arg8_type; typedef A8 arg9_type; 
	enum{ arity = 9};

	void operator()(FunctorParam& ret , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) const{
		xnew<T>(a0, a1, a2, a3, a4, a5, a6, a7, a8), rcast<R>(ret);
	}
};

// stdcall版
#if defined(_WIN32) && defined(_M_IX86)

template<int Method, class R , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
struct nfun<R (__stdcall *)(A0, A1, A2, A3, A4, A5, A6, A7, A8), Method>
	: nfun_base<9, functor<R (__stdcall *)(A0, A1, A2, A3, A4, A5, A6, A7, A8)>, Method, R>{};

// 関数を関数オブジェクト化する
template<class R , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
struct functor<R (__stdcall *)(A0, A1, A2, A3, A4, A5, A6, A7, A8)>{
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; typedef A2 arg3_type; typedef A3 arg4_type; typedef A4 arg5_type; typedef A5 arg6_type; typedef A6 arg7_type; typedef A7 arg8_type; typedef A8 arg9_type; 
	typedef R (__stdcall *fun_type)(A0, A1, A2, A3, A4, A5, A6, A7, A8);
	enum{ arity = 9};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) const{
		fun_(a0, a1, a2, a3, a4, a5, a6, a7, a8), rcast<R>(ret);
	}
};

// 関数を関数オブジェクト化する
template<class R , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, R (__stdcall *fun_)(A0, A1, A2, A3, A4, A5, A6, A7, A8)>
struct static_functor<R (__stdcall *)(A0, A1, A2, A3, A4, A5, A6, A7, A8), fun_>{
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; typedef A2 arg3_type; typedef A3 arg4_type; typedef A4 arg5_type; typedef A5 arg6_type; typedef A6 arg7_type; typedef A7 arg8_type; typedef A8 arg9_type; 
	enum{ arity = 9};

	void operator()(FunctorParam& ret , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) const{
		fun_(a0, a1, a2, a3, a4, a5, a6, a7, a8), rcast<R>(ret);
	}
};

#endif


template<int Method, class R , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
struct nfun<R (*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9), Method>
	: nfun_base<10, functor<R (*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9)>, Method, R>{};

// 関数を関数オブジェクト化する
template<class R , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
struct functor<R (*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9)>{
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; typedef A2 arg3_type; typedef A3 arg4_type; typedef A4 arg5_type; typedef A5 arg6_type; typedef A6 arg7_type; typedef A7 arg8_type; typedef A8 arg9_type; typedef A9 arg10_type; 
	typedef R (*fun_type)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9);
	enum{ arity = 10};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9) const{
		fun_(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9), rcast<R>(ret);
	}
};

template<int Method, class R, class C , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
struct nfun<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9), Method>
	: nfun_base<11, functor<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9)>, Method, R>{};

// メンバ関数を関数オブジェクト化する
template<class R, class C , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
struct functor<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9)>{
	typedef R result_type; typedef C* arg1_type; typedef A0 arg2_type; typedef A1 arg3_type; typedef A2 arg4_type; typedef A3 arg5_type; typedef A4 arg6_type; typedef A5 arg7_type; typedef A6 arg8_type; typedef A7 arg9_type; typedef A8 arg10_type; typedef A9 arg11_type; 
	typedef R (C::*fun_type)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9);
	enum{ arity = 11};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret, C* self , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9) const{
		(self->*fun_)(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9), rcast<R>(ret);
	}
};

template<int Method, class R, class C , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
struct nfun<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9) const, Method>
	: nfun_base<11, functor<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9) const>, Method, R>{};

// constメンバ関数を関数オブジェクト化する
template<class R, class C , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
struct functor<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9) const>{
	typedef R result_type; typedef C* arg1_type; typedef A0 arg2_type; typedef A1 arg3_type; typedef A2 arg4_type; typedef A3 arg5_type; typedef A4 arg6_type; typedef A5 arg7_type; typedef A6 arg8_type; typedef A7 arg9_type; typedef A8 arg10_type; typedef A9 arg11_type; 
	typedef R (C::*fun_type)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9) const;
	enum{ arity = 11};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret, C* self , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9) const{
		(self->*fun_)(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9), rcast<R>(ret);
	}
};

////

// 関数を関数オブジェクト化する
template<class R , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, R (*fun_)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9)>
struct static_functor<R (*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9), fun_>{
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; typedef A2 arg3_type; typedef A3 arg4_type; typedef A4 arg5_type; typedef A5 arg6_type; typedef A6 arg7_type; typedef A7 arg8_type; typedef A8 arg9_type; typedef A9 arg10_type; 
	enum{ arity = 10};

	void operator()(FunctorParam& ret , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9) const{
		fun_(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9), rcast<R>(ret);
	}
};

// メンバ関数を関数オブジェクト化する
template<class R, class C , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, R (C::*fun_)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9)>
struct static_functor<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9), fun_>{
	typedef R result_type; typedef C* arg1_type; typedef A0 arg2_type; typedef A1 arg3_type; typedef A2 arg4_type; typedef A3 arg5_type; typedef A4 arg6_type; typedef A5 arg7_type; typedef A6 arg8_type; typedef A7 arg9_type; typedef A8 arg10_type; typedef A9 arg11_type; 
	enum{ arity = 11};

	void operator()(FunctorParam& ret, C* self , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9) const{
		(self->*fun_)(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9), rcast<R>(ret);
	}
};

// constメンバ関数を関数オブジェクト化する
template<class R, class C , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, R (C::*fun_)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9) const>
struct static_functor<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9) const, fun_>{
	typedef R result_type; typedef C* arg1_type; typedef A0 arg2_type; typedef A1 arg3_type; typedef A2 arg4_type; typedef A3 arg5_type; typedef A4 arg6_type; typedef A5 arg7_type; typedef A6 arg8_type; typedef A7 arg9_type; typedef A8 arg10_type; typedef A9 arg11_type; 
	enum{ arity = 11};

	void operator()(FunctorParam& ret, C* self , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9) const{
		(self->*fun_)(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9), rcast<R>(ret);
	}
};

// コンストラクタを関数オブジェクト化する
template<class T , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
struct ctor_functor<T , A0, A1, A2, A3, A4, A5, A6, A7, A8, A9>{
	typedef SmartPtr<T> R;
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; typedef A2 arg3_type; typedef A3 arg4_type; typedef A4 arg5_type; typedef A5 arg6_type; typedef A6 arg7_type; typedef A7 arg8_type; typedef A8 arg9_type; typedef A9 arg10_type; 
	enum{ arity = 10};

	void operator()(FunctorParam& ret , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9) const{
		xnew<T>(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9), rcast<R>(ret);
	}
};

// stdcall版
#if defined(_WIN32) && defined(_M_IX86)

template<int Method, class R , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
struct nfun<R (__stdcall *)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9), Method>
	: nfun_base<10, functor<R (__stdcall *)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9)>, Method, R>{};

// 関数を関数オブジェクト化する
template<class R , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
struct functor<R (__stdcall *)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9)>{
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; typedef A2 arg3_type; typedef A3 arg4_type; typedef A4 arg5_type; typedef A5 arg6_type; typedef A6 arg7_type; typedef A7 arg8_type; typedef A8 arg9_type; typedef A9 arg10_type; 
	typedef R (__stdcall *fun_type)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9);
	enum{ arity = 10};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9) const{
		fun_(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9), rcast<R>(ret);
	}
};

// 関数を関数オブジェクト化する
template<class R , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, R (__stdcall *fun_)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9)>
struct static_functor<R (__stdcall *)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9), fun_>{
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; typedef A2 arg3_type; typedef A3 arg4_type; typedef A4 arg5_type; typedef A5 arg6_type; typedef A6 arg7_type; typedef A7 arg8_type; typedef A8 arg9_type; typedef A9 arg10_type; 
	enum{ arity = 10};

	void operator()(FunctorParam& ret , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9) const{
		fun_(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9), rcast<R>(ret);
	}
};

#endif


template<int Method, class R , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
struct nfun<R (*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10), Method>
	: nfun_base<11, functor<R (*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)>, Method, R>{};

// 関数を関数オブジェクト化する
template<class R , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
struct functor<R (*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)>{
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; typedef A2 arg3_type; typedef A3 arg4_type; typedef A4 arg5_type; typedef A5 arg6_type; typedef A6 arg7_type; typedef A7 arg8_type; typedef A8 arg9_type; typedef A9 arg10_type; typedef A10 arg11_type; 
	typedef R (*fun_type)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10);
	enum{ arity = 11};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10) const{
		fun_(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10), rcast<R>(ret);
	}
};

template<int Method, class R, class C , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
struct nfun<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10), Method>
	: nfun_base<12, functor<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)>, Method, R>{};

// メンバ関数を関数オブジェクト化する
template<class R, class C , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
struct functor<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)>{
	typedef R result_type; typedef C* arg1_type; typedef A0 arg2_type; typedef A1 arg3_type; typedef A2 arg4_type; typedef A3 arg5_type; typedef A4 arg6_type; typedef A5 arg7_type; typedef A6 arg8_type; typedef A7 arg9_type; typedef A8 arg10_type; typedef A9 arg11_type; typedef A10 arg12_type; 
	typedef R (C::*fun_type)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10);
	enum{ arity = 12};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret, C* self , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10) const{
		(self->*fun_)(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10), rcast<R>(ret);
	}
};

template<int Method, class R, class C , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
struct nfun<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10) const, Method>
	: nfun_base<12, functor<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10) const>, Method, R>{};

// constメンバ関数を関数オブジェクト化する
template<class R, class C , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
struct functor<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10) const>{
	typedef R result_type; typedef C* arg1_type; typedef A0 arg2_type; typedef A1 arg3_type; typedef A2 arg4_type; typedef A3 arg5_type; typedef A4 arg6_type; typedef A5 arg7_type; typedef A6 arg8_type; typedef A7 arg9_type; typedef A8 arg10_type; typedef A9 arg11_type; typedef A10 arg12_type; 
	typedef R (C::*fun_type)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10) const;
	enum{ arity = 12};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret, C* self , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10) const{
		(self->*fun_)(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10), rcast<R>(ret);
	}
};

////

// 関数を関数オブジェクト化する
template<class R , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, R (*fun_)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)>
struct static_functor<R (*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10), fun_>{
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; typedef A2 arg3_type; typedef A3 arg4_type; typedef A4 arg5_type; typedef A5 arg6_type; typedef A6 arg7_type; typedef A7 arg8_type; typedef A8 arg9_type; typedef A9 arg10_type; typedef A10 arg11_type; 
	enum{ arity = 11};

	void operator()(FunctorParam& ret , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10) const{
		fun_(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10), rcast<R>(ret);
	}
};

// メンバ関数を関数オブジェクト化する
template<class R, class C , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, R (C::*fun_)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)>
struct static_functor<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10), fun_>{
	typedef R result_type; typedef C* arg1_type; typedef A0 arg2_type; typedef A1 arg3_type; typedef A2 arg4_type; typedef A3 arg5_type; typedef A4 arg6_type; typedef A5 arg7_type; typedef A6 arg8_type; typedef A7 arg9_type; typedef A8 arg10_type; typedef A9 arg11_type; typedef A10 arg12_type; 
	enum{ arity = 12};

	void operator()(FunctorParam& ret, C* self , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10) const{
		(self->*fun_)(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10), rcast<R>(ret);
	}
};

// constメンバ関数を関数オブジェクト化する
template<class R, class C , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, R (C::*fun_)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10) const>
struct static_functor<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10) const, fun_>{
	typedef R result_type; typedef C* arg1_type; typedef A0 arg2_type; typedef A1 arg3_type; typedef A2 arg4_type; typedef A3 arg5_type; typedef A4 arg6_type; typedef A5 arg7_type; typedef A6 arg8_type; typedef A7 arg9_type; typedef A8 arg10_type; typedef A9 arg11_type; typedef A10 arg12_type; 
	enum{ arity = 12};

	void operator()(FunctorParam& ret, C* self , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10) const{
		(self->*fun_)(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10), rcast<R>(ret);
	}
};

// コンストラクタを関数オブジェクト化する
template<class T , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
struct ctor_functor<T , A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10>{
	typedef SmartPtr<T> R;
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; typedef A2 arg3_type; typedef A3 arg4_type; typedef A4 arg5_type; typedef A5 arg6_type; typedef A6 arg7_type; typedef A7 arg8_type; typedef A8 arg9_type; typedef A9 arg10_type; typedef A10 arg11_type; 
	enum{ arity = 11};

	void operator()(FunctorParam& ret , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10) const{
		xnew<T>(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10), rcast<R>(ret);
	}
};

// stdcall版
#if defined(_WIN32) && defined(_M_IX86)

template<int Method, class R , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
struct nfun<R (__stdcall *)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10), Method>
	: nfun_base<11, functor<R (__stdcall *)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)>, Method, R>{};

// 関数を関数オブジェクト化する
template<class R , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
struct functor<R (__stdcall *)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)>{
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; typedef A2 arg3_type; typedef A3 arg4_type; typedef A4 arg5_type; typedef A5 arg6_type; typedef A6 arg7_type; typedef A7 arg8_type; typedef A8 arg9_type; typedef A9 arg10_type; typedef A10 arg11_type; 
	typedef R (__stdcall *fun_type)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10);
	enum{ arity = 11};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10) const{
		fun_(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10), rcast<R>(ret);
	}
};

// 関数を関数オブジェクト化する
template<class R , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, R (__stdcall *fun_)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)>
struct static_functor<R (__stdcall *)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10), fun_>{
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; typedef A2 arg3_type; typedef A3 arg4_type; typedef A4 arg5_type; typedef A5 arg6_type; typedef A6 arg7_type; typedef A7 arg8_type; typedef A8 arg9_type; typedef A9 arg10_type; typedef A10 arg11_type; 
	enum{ arity = 11};

	void operator()(FunctorParam& ret , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10) const{
		fun_(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10), rcast<R>(ret);
	}
};

#endif


template<int Method, class R , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11>
struct nfun<R (*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11), Method>
	: nfun_base<12, functor<R (*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11)>, Method, R>{};

// 関数を関数オブジェクト化する
template<class R , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11>
struct functor<R (*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11)>{
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; typedef A2 arg3_type; typedef A3 arg4_type; typedef A4 arg5_type; typedef A5 arg6_type; typedef A6 arg7_type; typedef A7 arg8_type; typedef A8 arg9_type; typedef A9 arg10_type; typedef A10 arg11_type; typedef A11 arg12_type; 
	typedef R (*fun_type)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11);
	enum{ arity = 12};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11) const{
		fun_(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11), rcast<R>(ret);
	}
};

template<int Method, class R, class C , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11>
struct nfun<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11), Method>
	: nfun_base<13, functor<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11)>, Method, R>{};

// メンバ関数を関数オブジェクト化する
template<class R, class C , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11>
struct functor<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11)>{
	typedef R result_type; typedef C* arg1_type; typedef A0 arg2_type; typedef A1 arg3_type; typedef A2 arg4_type; typedef A3 arg5_type; typedef A4 arg6_type; typedef A5 arg7_type; typedef A6 arg8_type; typedef A7 arg9_type; typedef A8 arg10_type; typedef A9 arg11_type; typedef A10 arg12_type; typedef A11 arg13_type; 
	typedef R (C::*fun_type)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11);
	enum{ arity = 13};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret, C* self , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11) const{
		(self->*fun_)(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11), rcast<R>(ret);
	}
};

template<int Method, class R, class C , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11>
struct nfun<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11) const, Method>
	: nfun_base<13, functor<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11) const>, Method, R>{};

// constメンバ関数を関数オブジェクト化する
template<class R, class C , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11>
struct functor<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11) const>{
	typedef R result_type; typedef C* arg1_type; typedef A0 arg2_type; typedef A1 arg3_type; typedef A2 arg4_type; typedef A3 arg5_type; typedef A4 arg6_type; typedef A5 arg7_type; typedef A6 arg8_type; typedef A7 arg9_type; typedef A8 arg10_type; typedef A9 arg11_type; typedef A10 arg12_type; typedef A11 arg13_type; 
	typedef R (C::*fun_type)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11) const;
	enum{ arity = 13};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret, C* self , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11) const{
		(self->*fun_)(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11), rcast<R>(ret);
	}
};

////

// 関数を関数オブジェクト化する
template<class R , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, R (*fun_)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11)>
struct static_functor<R (*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11), fun_>{
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; typedef A2 arg3_type; typedef A3 arg4_type; typedef A4 arg5_type; typedef A5 arg6_type; typedef A6 arg7_type; typedef A7 arg8_type; typedef A8 arg9_type; typedef A9 arg10_type; typedef A10 arg11_type; typedef A11 arg12_type; 
	enum{ arity = 12};

	void operator()(FunctorParam& ret , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11) const{
		fun_(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11), rcast<R>(ret);
	}
};

// メンバ関数を関数オブジェクト化する
template<class R, class C , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, R (C::*fun_)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11)>
struct static_functor<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11), fun_>{
	typedef R result_type; typedef C* arg1_type; typedef A0 arg2_type; typedef A1 arg3_type; typedef A2 arg4_type; typedef A3 arg5_type; typedef A4 arg6_type; typedef A5 arg7_type; typedef A6 arg8_type; typedef A7 arg9_type; typedef A8 arg10_type; typedef A9 arg11_type; typedef A10 arg12_type; typedef A11 arg13_type; 
	enum{ arity = 13};

	void operator()(FunctorParam& ret, C* self , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11) const{
		(self->*fun_)(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11), rcast<R>(ret);
	}
};

// constメンバ関数を関数オブジェクト化する
template<class R, class C , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, R (C::*fun_)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11) const>
struct static_functor<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11) const, fun_>{
	typedef R result_type; typedef C* arg1_type; typedef A0 arg2_type; typedef A1 arg3_type; typedef A2 arg4_type; typedef A3 arg5_type; typedef A4 arg6_type; typedef A5 arg7_type; typedef A6 arg8_type; typedef A7 arg9_type; typedef A8 arg10_type; typedef A9 arg11_type; typedef A10 arg12_type; typedef A11 arg13_type; 
	enum{ arity = 13};

	void operator()(FunctorParam& ret, C* self , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11) const{
		(self->*fun_)(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11), rcast<R>(ret);
	}
};

// コンストラクタを関数オブジェクト化する
template<class T , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11>
struct ctor_functor<T , A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11>{
	typedef SmartPtr<T> R;
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; typedef A2 arg3_type; typedef A3 arg4_type; typedef A4 arg5_type; typedef A5 arg6_type; typedef A6 arg7_type; typedef A7 arg8_type; typedef A8 arg9_type; typedef A9 arg10_type; typedef A10 arg11_type; typedef A11 arg12_type; 
	enum{ arity = 12};

	void operator()(FunctorParam& ret , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11) const{
		xnew<T>(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11), rcast<R>(ret);
	}
};

// stdcall版
#if defined(_WIN32) && defined(_M_IX86)

template<int Method, class R , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11>
struct nfun<R (__stdcall *)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11), Method>
	: nfun_base<12, functor<R (__stdcall *)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11)>, Method, R>{};

// 関数を関数オブジェクト化する
template<class R , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11>
struct functor<R (__stdcall *)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11)>{
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; typedef A2 arg3_type; typedef A3 arg4_type; typedef A4 arg5_type; typedef A5 arg6_type; typedef A6 arg7_type; typedef A7 arg8_type; typedef A8 arg9_type; typedef A9 arg10_type; typedef A10 arg11_type; typedef A11 arg12_type; 
	typedef R (__stdcall *fun_type)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11);
	enum{ arity = 12};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11) const{
		fun_(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11), rcast<R>(ret);
	}
};

// 関数を関数オブジェクト化する
template<class R , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, R (__stdcall *fun_)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11)>
struct static_functor<R (__stdcall *)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11), fun_>{
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; typedef A2 arg3_type; typedef A3 arg4_type; typedef A4 arg5_type; typedef A5 arg6_type; typedef A6 arg7_type; typedef A7 arg8_type; typedef A8 arg9_type; typedef A9 arg10_type; typedef A10 arg11_type; typedef A11 arg12_type; 
	enum{ arity = 12};

	void operator()(FunctorParam& ret , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11) const{
		fun_(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11), rcast<R>(ret);
	}
};

#endif


template<int Method, class R , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12>
struct nfun<R (*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12), Method>
	: nfun_base<13, functor<R (*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12)>, Method, R>{};

// 関数を関数オブジェクト化する
template<class R , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12>
struct functor<R (*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12)>{
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; typedef A2 arg3_type; typedef A3 arg4_type; typedef A4 arg5_type; typedef A5 arg6_type; typedef A6 arg7_type; typedef A7 arg8_type; typedef A8 arg9_type; typedef A9 arg10_type; typedef A10 arg11_type; typedef A11 arg12_type; typedef A12 arg13_type; 
	typedef R (*fun_type)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12);
	enum{ arity = 13};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12) const{
		fun_(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12), rcast<R>(ret);
	}
};

template<int Method, class R, class C , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12>
struct nfun<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12), Method>
	: nfun_base<14, functor<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12)>, Method, R>{};

// メンバ関数を関数オブジェクト化する
template<class R, class C , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12>
struct functor<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12)>{
	typedef R result_type; typedef C* arg1_type; typedef A0 arg2_type; typedef A1 arg3_type; typedef A2 arg4_type; typedef A3 arg5_type; typedef A4 arg6_type; typedef A5 arg7_type; typedef A6 arg8_type; typedef A7 arg9_type; typedef A8 arg10_type; typedef A9 arg11_type; typedef A10 arg12_type; typedef A11 arg13_type; typedef A12 arg14_type; 
	typedef R (C::*fun_type)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12);
	enum{ arity = 14};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret, C* self , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12) const{
		(self->*fun_)(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12), rcast<R>(ret);
	}
};

template<int Method, class R, class C , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12>
struct nfun<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12) const, Method>
	: nfun_base<14, functor<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12) const>, Method, R>{};

// constメンバ関数を関数オブジェクト化する
template<class R, class C , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12>
struct functor<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12) const>{
	typedef R result_type; typedef C* arg1_type; typedef A0 arg2_type; typedef A1 arg3_type; typedef A2 arg4_type; typedef A3 arg5_type; typedef A4 arg6_type; typedef A5 arg7_type; typedef A6 arg8_type; typedef A7 arg9_type; typedef A8 arg10_type; typedef A9 arg11_type; typedef A10 arg12_type; typedef A11 arg13_type; typedef A12 arg14_type; 
	typedef R (C::*fun_type)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12) const;
	enum{ arity = 14};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret, C* self , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12) const{
		(self->*fun_)(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12), rcast<R>(ret);
	}
};

////

// 関数を関数オブジェクト化する
template<class R , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, R (*fun_)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12)>
struct static_functor<R (*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12), fun_>{
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; typedef A2 arg3_type; typedef A3 arg4_type; typedef A4 arg5_type; typedef A5 arg6_type; typedef A6 arg7_type; typedef A7 arg8_type; typedef A8 arg9_type; typedef A9 arg10_type; typedef A10 arg11_type; typedef A11 arg12_type; typedef A12 arg13_type; 
	enum{ arity = 13};

	void operator()(FunctorParam& ret , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12) const{
		fun_(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12), rcast<R>(ret);
	}
};

// メンバ関数を関数オブジェクト化する
template<class R, class C , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, R (C::*fun_)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12)>
struct static_functor<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12), fun_>{
	typedef R result_type; typedef C* arg1_type; typedef A0 arg2_type; typedef A1 arg3_type; typedef A2 arg4_type; typedef A3 arg5_type; typedef A4 arg6_type; typedef A5 arg7_type; typedef A6 arg8_type; typedef A7 arg9_type; typedef A8 arg10_type; typedef A9 arg11_type; typedef A10 arg12_type; typedef A11 arg13_type; typedef A12 arg14_type; 
	enum{ arity = 14};

	void operator()(FunctorParam& ret, C* self , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12) const{
		(self->*fun_)(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12), rcast<R>(ret);
	}
};

// constメンバ関数を関数オブジェクト化する
template<class R, class C , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, R (C::*fun_)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12) const>
struct static_functor<R (C::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12) const, fun_>{
	typedef R result_type; typedef C* arg1_type; typedef A0 arg2_type; typedef A1 arg3_type; typedef A2 arg4_type; typedef A3 arg5_type; typedef A4 arg6_type; typedef A5 arg7_type; typedef A6 arg8_type; typedef A7 arg9_type; typedef A8 arg10_type; typedef A9 arg11_type; typedef A10 arg12_type; typedef A11 arg13_type; typedef A12 arg14_type; 
	enum{ arity = 14};

	void operator()(FunctorParam& ret, C* self , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12) const{
		(self->*fun_)(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12), rcast<R>(ret);
	}
};

// コンストラクタを関数オブジェクト化する
template<class T , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12>
struct ctor_functor<T , A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12>{
	typedef SmartPtr<T> R;
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; typedef A2 arg3_type; typedef A3 arg4_type; typedef A4 arg5_type; typedef A5 arg6_type; typedef A6 arg7_type; typedef A7 arg8_type; typedef A8 arg9_type; typedef A9 arg10_type; typedef A10 arg11_type; typedef A11 arg12_type; typedef A12 arg13_type; 
	enum{ arity = 13};

	void operator()(FunctorParam& ret , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12) const{
		xnew<T>(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12), rcast<R>(ret);
	}
};

// stdcall版
#if defined(_WIN32) && defined(_M_IX86)

template<int Method, class R , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12>
struct nfun<R (__stdcall *)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12), Method>
	: nfun_base<13, functor<R (__stdcall *)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12)>, Method, R>{};

// 関数を関数オブジェクト化する
template<class R , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12>
struct functor<R (__stdcall *)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12)>{
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; typedef A2 arg3_type; typedef A3 arg4_type; typedef A4 arg5_type; typedef A5 arg6_type; typedef A6 arg7_type; typedef A7 arg8_type; typedef A8 arg9_type; typedef A9 arg10_type; typedef A10 arg11_type; typedef A11 arg12_type; typedef A12 arg13_type; 
	typedef R (__stdcall *fun_type)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12);
	enum{ arity = 13};

	fun_type fun_;
	functor(fun_type fun):fun_(fun){}

	void operator()(FunctorParam& ret , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12) const{
		fun_(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12), rcast<R>(ret);
	}
};

// 関数を関数オブジェクト化する
template<class R , class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, R (__stdcall *fun_)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12)>
struct static_functor<R (__stdcall *)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12), fun_>{
	typedef R result_type; typedef A0 arg1_type; typedef A1 arg2_type; typedef A2 arg3_type; typedef A3 arg4_type; typedef A4 arg5_type; typedef A5 arg6_type; typedef A6 arg7_type; typedef A7 arg8_type; typedef A8 arg9_type; typedef A9 arg10_type; typedef A10 arg11_type; typedef A11 arg12_type; typedef A12 arg13_type; 
	enum{ arity = 13};

	void operator()(FunctorParam& ret , A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12) const{
		fun_(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12), rcast<R>(ret);
	}
};

#endif


//}}REPEAT}


///////////////////////////////////////////////////////

template<class C, class T>
struct getter_functor{
	typedef T& R;
	typedef R result_type; typedef C* arg1_type;
	enum{ arity = 1 };
	typedef T C::* fun_t;

	fun_t fun_;
	getter_functor(fun_t fun): fun_(fun){}

	void operator()(FunctorParam& ret, C* a0){
		T& t = a0->*fun_;
		t, rcast<R>(ret);
	}
};

template<class C, class T>
struct setter_functor{
	typedef T& R;
	typedef R result_type; typedef C* arg1_type; typedef const T& arg2_type;
	enum{ arity = 2 };
	typedef T C::* fun_t;

	fun_t fun_;
	setter_functor(fun_t fun): fun_(fun){}

	void operator()(FunctorParam& ret, C* a0, const T& a1){
		T& t = a0->*fun_;
		t = a1;
		t, rcast<R>(ret);
	}
};

template<class TFun, TFun fun_>
struct static_getter_functor;

template<class TFun, TFun fun_>
struct static_setter_functor;

template<class C, class T, T C::* fun_>
struct static_getter_functor<T C::*, fun_>{
	typedef T& R;
	typedef R result_type; typedef C* arg1_type;
	enum{ arity = 1 };

	void operator()(FunctorParam& ret, C* a0){
		T& t = a0->*fun_;
		t, rcast<R>(ret);
	}
};

template<class C, class T, T C::* fun_>
struct static_setter_functor<T C::*, fun_>{
	typedef T& R;
	typedef R result_type; typedef C* arg1_type; typedef const T& arg2_type;
	enum{ arity = 2 };

	void operator()(FunctorParam& ret, C* a0, const T& a1){
		T& t = a0->*fun_;
		t = a1;
		t, rcast<R>(ret);
	}
};

//////////////////////////////////////////

#if defined(_MSC_VER) && _MSC_VER<=1300

#define Xdef_method(fun) it->def_method(XTAL_L(#fun), fun)
#define Xdef_method2(fun, secondary_key) it->def_method(XTAL_L(#fun), secondary_key, &Self::fun)
#define Xdef_method_alias(fun, impl) it->def_method(XTAL_L(#fun), impl)
#define Xdef_method_alias2(fun, impl, secondary_key) it->def_method(XTAL_L(#fun), secondary_key, impl)

#define Xdef_fun(fun) it->def_fun(XTAL_L(#fun), &Self::fun)
#define Xdef_fun2(fun, secondary_key) it->def_fun(XTAL_L(#fun), secondary_key, &Self::fun)
#define Xdef_fun_alias(fun, impl) it->def_fun(XTAL_L(#fun), impl)
#define Xdef_fun_alias2(fun, impl, secondary_key) it->def_fun(XTAL_L(#fun), secondary_key, impl)

#define Xdef_getter(fun) it->def_getter(XTAL_L(#fun), &Self::fun)
#define Xdef_setter(fun) it->def_setter(XTAL_L("set_" #fun), &Self::fun)

#else

template<class TFun> struct static_cfun_meker{ 
	template<TFun fun> static const param_types_holder_n& inner(){ 
		return fun_param_holder<dfun<static_functor<TFun, fun> > >::value; 
	} 
};

template<class TFun> inline static_cfun_meker<TFun> generate_static_cfun(TFun){ 
	return static_cfun_meker<TFun>(); 
}

template<class TFun> struct static_cmemfun_meker{ 
	template<TFun fun> static const param_types_holder_n& inner(){ 
		return fun_param_holder<dmemfun<static_functor<TFun, fun> > >::value;
	} 
};

template<class TFun> inline static_cmemfun_meker<TFun> generate_static_cmemfun(TFun){ 
	return static_cmemfun_meker<TFun>(); 
}


template<class TFun> struct static_getter_meker{ 
	template<TFun fun> static const param_types_holder_n& inner(){ 
		return fun_param_holder<dmemfun<static_getter_functor<TFun, fun> > >::value;
	} 
};

template<class TFun> inline static_getter_meker<TFun> generate_static_getter(TFun){ 
	return static_getter_meker<TFun>(); 
}

template<class TFun> struct static_setter_meker{ 
	template<TFun fun> static const param_types_holder_n& inner(){ 
		return fun_param_holder<dmemfun<static_setter_functor<TFun, fun> > >::value;
	} 
};

template<class TFun> inline static_setter_meker<TFun> generate_static_setter(TFun){ 
	return static_setter_meker<TFun>(); 
}


#define XTAL_FUN_PARAM(fun) ::xtal::generate_static_cfun(fun).inner<fun>()
#define XTAL_METHOD_PARAM(fun) ::xtal::generate_static_cmemfun(fun).inner<fun>()
#define XTAL_GETTER_PARAM(fun) ::xtal::generate_static_getter(fun).inner<fun>()
#define XTAL_SETTER_PARAM(fun) ::xtal::generate_static_setter(fun).inner<fun>()

#define Xdef_method(fun) it->define(XTAL_L(#fun), XTAL_METHOD_PARAM(&Self::fun))
#define Xdef_method2(fun, secondary_key) it->define(XTAL_L(#fun), secondary_key, XTAL_METHOD_PARAM(&Self::fun))
#define Xdef_method_alias(fun, impl) it->define(XTAL_L(#fun), XTAL_METHOD_PARAM(impl))
#define Xdef_method_alias2(fun, impl, secondary_key) it->define(XTAL_L(#fun), secondary_key, XTAL_METHOD_PARAM(impl))

#define Xdef_fun(fun) it->define(XTAL_L(#fun), XTAL_FUN_PARAM(&Self::fun))
#define Xdef_fun2(fun, secondary_key) it->define(XTAL_L(#fun), secondary_key, XTAL_FUN_PARAM(&Self::fun))
#define Xdef_fun_alias(fun, impl) it->define(XTAL_L(#fun), XTAL_FUN_PARAM(impl))
#define Xdef_fun_alias2(fun, impl, secondary_key) it->define(XTAL_L(#fun), secondary_key, XTAL_FUN_PARAM(impl))

#define Xdef_getter(fun) it->define(XTAL_L(#fun), XTAL_GETTER_PARAM(&Self::fun))
#define Xdef_setter(fun) it->define(XTAL_L("set_" #fun), XTAL_SETTER_PARAM(&Self::fun))

#endif

#define Xdef_var(fun) Xdef_getter(fun), Xdef_setter(fun)

#define Xparam(name, default_value) it->define_param(XTAL_L(#name), default_value)

#define Xdef(name, value) it->define(XTAL_L(#name), value)
#define Xdef2(name, value, secondary_key) it->define(XTAL_L(#name), value, secondary_key)

#define Xdef_const(name) it->define(XTAL_L(#name), (int_t)Self::name)

//{REPEAT{{
/*
#define Xdef_ctor`n`(#REPEAT_COMMA#A`i`#) it->def_ctor`n`<Self #COMMA_REPEAT#A`i`#>()
*/

#define Xdef_ctor0() it->def_ctor0<Self >()

#define Xdef_ctor1(A0) it->def_ctor1<Self , A0>()

#define Xdef_ctor2(A0, A1) it->def_ctor2<Self , A0, A1>()

#define Xdef_ctor3(A0, A1, A2) it->def_ctor3<Self , A0, A1, A2>()

#define Xdef_ctor4(A0, A1, A2, A3) it->def_ctor4<Self , A0, A1, A2, A3>()

#define Xdef_ctor5(A0, A1, A2, A3, A4) it->def_ctor5<Self , A0, A1, A2, A3, A4>()

#define Xdef_ctor6(A0, A1, A2, A3, A4, A5) it->def_ctor6<Self , A0, A1, A2, A3, A4, A5>()

#define Xdef_ctor7(A0, A1, A2, A3, A4, A5, A6) it->def_ctor7<Self , A0, A1, A2, A3, A4, A5, A6>()

#define Xdef_ctor8(A0, A1, A2, A3, A4, A5, A6, A7) it->def_ctor8<Self , A0, A1, A2, A3, A4, A5, A6, A7>()

#define Xdef_ctor9(A0, A1, A2, A3, A4, A5, A6, A7, A8) it->def_ctor9<Self , A0, A1, A2, A3, A4, A5, A6, A7, A8>()

#define Xdef_ctor10(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9) it->def_ctor10<Self , A0, A1, A2, A3, A4, A5, A6, A7, A8, A9>()

#define Xdef_ctor11(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10) it->def_ctor11<Self , A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10>()

#define Xdef_ctor12(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11) it->def_ctor12<Self , A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11>()

#define Xdef_ctor13(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12) it->def_ctor13<Self , A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12>()

//}}REPEAT}

}

#endif
