
#pragma once

//#define XTAL_ENFORCE_64_BIT
//#define XTAL_USE_THREAD_MODEL_2
//#define XTAL_USE_COMPILED_EMB

#ifdef XTAL_NO_PARSER
#	define XTAL_USE_COMPILED_EMB
#endif

#if !defined(NDEBUG) && (defined(_DEBUG) || defined(DEBUG))
#	define XTAL_DEBUG
#endif

#ifdef XTAL_DEBUG
#	define XTAL_ASSERT(expr) assert(expr)
#else
#	define XTAL_ASSERT(expr)
#endif

#ifdef XTAL_DEBUG
#	define XTAL_NODEFAULT default: XTAL_ASSERT(false); break
#else
#	ifdef _MSC_VER
#		define XTAL_NODEFAULT default: __assume(0)
#	else
#		define XTAL_NODEFAULT
#	endif
#endif

#define XTAL_DISALLOW_COPY_AND_ASSIGN(ClassName) ClassName(const ClassName&); void operator=(const ClassName&)

#define XTAL_DEFAULT default:
#define XTAL_CASE(key) break; case key:
#define XTAL_CASE1(key) break; case key:
#define XTAL_CASE2(key, key2) break; case key:case key2:
#define XTAL_CASE3(key, key2, key3) break; case key:case key2:case key3:
#define XTAL_CASE4(key, key2, key3, key4) break; case key:case key2:case key3:case key4:

#ifdef XTAL_NO_THREAD
#	define XTAL_GLOBAL_INTERPRETER_LOCK
#	define XTAL_GLOBAL_INTERPRETER_UNLOCK 
#	define XTAL_UNLOCK 
#else
#	define XTAL_GLOBAL_INTERPRETER_LOCK
#	define XTAL_GLOBAL_INTERPRETER_UNLOCK
#	define XTAL_UNLOCK if(const ::xtal::XUnlock& xunlock = 0)
#endif

/**
* @brief 例外を設定する
*/
#define XTAL_SET_EXCEPT(e) ::xtal::vmachine()->set_except(e)

/**
* @brief 例外が送出されているなら取り出す
*/
#define XTAL_CATCH_EXCEPT(e) if(const ::xtal::AnyPtr& e = ::xtal::unchecked_ptr_cast<Exception>(::xtal::vmachine()->catch_except()))

/**
* @brief 例外が送出されているか調べる
*/
#define XTAL_CHECK_EXCEPT(e) if(const ::xtal::AnyPtr& e = ::xtal::unchecked_ptr_cast<Exception>(::xtal::vmachine()->except()))


#ifdef __GNUC__
#	define XTAL_NOINLINE __attribute__((noinline)) 
#else
#	define XTAL_NOINLINE
#endif

#if defined(_MSC_VER) && _MSC_VER>=1400
#	pragma warning(disable: 4819)
#endif

#ifdef XTAL_USE_WCHAR
#	define XTAL_STRING(x) L##x
#else 
#	define XTAL_STRING(x) x
#endif

#define XTAL_ID(text) (::xtal::intern_literal(XTAL_STRING(#text)))

#if defined(_MSC_VER) || defined(__MINGW__) || defined(__MINGW32__)
#	define XTAL_INT_FMT (sizeof(int_t)==8 ? XTAL_STRING("I64") : XTAL_STRING(""))
#else
#	define XTAL_INT_FMT (sizeof(int_t)==8 ? XTAL_STRING("ll") : XTAL_STRING(""))
#endif

#ifdef XTAL_USE_WCHAR

#	if defined(_MSC_VER) && _MSC_VER>=1400
#		define XTAL_SPRINTF(buffer, data_size, format, value) swprintf_s(buffer, data_size, format, value)
#	else
#		define XTAL_SPRINTF(buffer, data_size, format, value) std::swprintf(buffer, format, value)
#	endif

#else

#	if defined(_MSC_VER) && _MSC_VER>=1400
#		define XTAL_SPRINTF(buffer, data_size, format, value) sprintf_s(buffer, data_size, format, value)
#	else
#		define XTAL_SPRINTF(buffer, data_size, format, value) std::sprintf(buffer, format, value)
#	endif

#endif



namespace xtal{

template<class T>
inline T align(T v, int N){
	return (v+(N-1)) & ~(N-1);
}

template<class T>
inline T* align_p(T* v, int N){
	return (T*)align((unsigned long)v, N);
}

template<class T>
inline T align_2(T v){
	v-=1;
	v|=v>>1;
	v|=v>>2;
	v|=v>>4;
	v|=v>>8;
	v|=v>>16;
	v|=v>>32;
	return v+1;
}

template<int N>
class static_count_bits{
	enum{
		N1 = (N & 0x55555555) + (N >> 1 & 0x55555555),
		N2 = (N1 & 0x33333333) + (N1 >> 2 & 0x33333333),
		N3 = (N2 & 0x0f0f0f0f) + (N2 >> 4 & 0x0f0f0f0f),
		N4 = (N3 & 0x00ff00ff) + (N3 >> 8 & 0x00ff00ff)
	};
public:	
	enum{
		value = (N4 & 0x0000ffff) + (N4>>16 & 0x0000ffff)	
	};
};

template<int N>
struct static_ntz{
	enum{
		value = static_count_bits<((N&(-N))-1)>::value
	};
};

// 最低限のメタプログラミング下地

template<bool>
struct IfHelper{
	template<class T, class U>
	struct inner{
		typedef T type;
	};
};

template<>
struct IfHelper<false>{
	template<class T, class U>
	struct inner{
		typedef U type;
	};
};

template<bool N, class T, class U>
struct If{
	typedef typename IfHelper<N>::template inner<T, U>::type type;
};


template<int>
struct TypeIntType{};

template<class T, class U>
struct Convertible{
	typedef char (&yes)[2];
	typedef char (&no)[1];
	static yes test(U);
	static no test(...);
	static T makeT();

	enum{ value = sizeof(test(makeT()))==sizeof(yes) };
};

template<class T, class U>
struct IsInherited{
	typedef char (&yes)[2];
	typedef char (&no)[1];
	static yes test(const U*);
	static no test(...);
	static T* makeT();

	enum{ value = sizeof(test(makeT()))==sizeof(yes) };
};

template<int N>
struct I2T{
	enum{ value = N };
};

template<class T>
struct T2T{
	typedef T type;
};

struct Other{
	template<class T>
	Other(const T&){}
};

template<class T>
struct IsConst{
	typedef char (&yes)[2];
	typedef char (&no)[1];
	template<class U>
	static yes test(const U (*)());
	static no test(...);

	enum{ value = sizeof(test((T (*)())0))==sizeof(yes) };
};

template<class T>
struct IsReference{
	typedef char (&yes)[2];
	typedef char (&no)[1];
	template<class U>
	static yes test(U& (*)());
	static no test(...);

	enum{ value = sizeof(test((T (*)())0))==sizeof(yes) };
};

template<class T>
struct IsPointer{
	typedef char (&yes)[2];
	typedef char (&no)[1];
	template<class U>
	static yes test(U* (*)());
	static no test(...);

	enum{ value = sizeof(test((T (*)())0))==sizeof(yes) };
};

template<class T, class U>
struct IsSame{
	typedef char (&yes)[2];
	typedef char (&no)[1];
	static yes test(U (*)());
	static no test(...);

	enum{ value = sizeof(test((T (*)())0))==sizeof(yes) };
};

template<class T>
struct IsVoid{ enum{ value = 0 }; };
template<>
struct IsVoid<void>{ enum{ value = 1 }; };

template<class T>
struct IsNotVoid{ enum{ value = 1 }; };
template<>
struct IsNotVoid<void>{ enum{ value = 0 }; };

template<class T>
struct Ref{
	T& ref;
	Ref(T& ref):ref(ref){};
	operator T&() const{ return ref; }
};

template<class T>
inline Ref<T> ref(T& r){
	return Ref<T>(r);
}

template<class T, class U>
struct NumericCalcResultType{
	typedef typename If<1, T, U>::type type;
};

template<int N>
struct SelectType{
	typedef typename If<sizeof(signed char)==N,
		signed char,
		typename If<sizeof(signed short)==N, 
			signed short int,
			typename If<sizeof(signed int)==N,
				signed int,
				typename If<sizeof(signed long)==N,
					signed long int,
					typename If<sizeof(signed long long)==N,
						signed long long int,
						void
					>::type
				>::type
			>::type
		>::type
	>::type int_t;

	typedef typename If<sizeof(unsigned char)==N,
		unsigned char,
		typename If<sizeof(unsigned short)==N, 
			unsigned short int,
			typename If<sizeof(unsigned int)==N,
				unsigned int,
				typename If<sizeof(unsigned long)==N,
					unsigned long int,
					typename If<sizeof(unsigned long long)==N,
						unsigned long long int,
						void
					>::type
				>::type
			>::type
		>::type
	>::type uint_t;

	typedef typename If<sizeof(float)==N,
		float,
		typename If<sizeof(double)==N, 
			double,
			void
		>::type
	>::type float_t;
};

}
