
#pragma once

namespace xtal{
	
/**
* @brief cast関数、as関数の戻り値の型を決定するためのヘルパーテンプレートクラス
*
* ほとんどの場合、CastResult<T>::typeはT自身を返す。
* 異なる場合としては、例えばCastResult<const int&>::type はintを返す。
*/
template<class T>
struct CastResult{ typedef T type; };

template<class T> 
inline typename CastResult<T>::type as(const AnyPtr& a);
	
template<class T>
inline typename CastResult<T>::type cast(const AnyPtr& a);
	
template<class T>
inline bool can_cast(const AnyPtr& a);

template<class T>
typename CastResult<T>::type unchecked_cast(const AnyPtr& a);

/////////////////////////////////////////////////////////////////////////////

const void* cast_helper_helper_smartptr(const AnyPtr& a, const ClassPtr& cls);
const void* cast_helper_helper_base(const AnyPtr& a, const ClassPtr& cls);
const void* cast_helper_helper_innocence(const AnyPtr& a, const ClassPtr& cls);
const void* cast_helper_helper_other(const AnyPtr& a, const ClassPtr& cls);

// 変換後の型がSmartPtrの場合
template<class U, class V>
inline const void* cast_helper_helper(const AnyPtr& a, const SmartPtr<U>*, const V&){
	return cast_helper_helper_smartptr(a, get_cpp_class<U>()); 
}

// 変換後の型がBaseを継承した型の場合
template<class U>
inline const void* cast_helper_helper(const AnyPtr& a, const Base*, const U*){
	return cast_helper_helper_base(a, get_cpp_class<U>()); 
}
	
// 変換後の型がAnyを継承した型の場合
template<class U>
inline const void* cast_helper_helper(const AnyPtr& a, const Any*, const U*){
	return cast_helper_helper_innocence(a, get_cpp_class<U>()); 
}
	
// 変換後の型がAnyやBaseを継承していない型の場合
template<class U>
inline const void* cast_helper_helper(const AnyPtr& a, const void*, const U*){
	return cast_helper_helper_other(a, get_cpp_class<U>()); 
}

/////////////////////////////////////////////////////////////////////////////

// 変換後の型がSmartPtrの場合
template<class U, class V>
inline bool can_cast_helper_helper(const AnyPtr& a, const SmartPtr<U>*, const V&){
	return a->is(get_cpp_class<U>());
}

// 変換後の型がBaseを継承した型の場合
template<class U>
inline bool can_cast_helper_helper(const AnyPtr& a, const Base*, const U*){
	return a->is(get_cpp_class<U>());
}

// 変換後の型がAnyを継承した型の場合
template<class U>
inline bool can_cast_helper_helper(const AnyPtr& a, const Any*, const U*){
	return a->is(get_cpp_class<U>());
}

// 変換後の型がAnyやBaseを継承していない型の場合
template<class U>
inline bool can_cast_helper_helper(const AnyPtr& a, const void*, const U*){
	return a->is(get_cpp_class<U>());
}

/////////////////////////////////////////////////////////////////////////////

// 変換後の型がSmartPtrの場合
template<class U, class V>
inline const void* unchecked_cast_helper_helper(const AnyPtr& a, const SmartPtr<U>*, const V&){
	return &a;
}

// 変換後の型がBaseを継承した型の場合
template<class U>
inline const void* unchecked_cast_helper_helper(const AnyPtr& a, const Base*, const U*){
	return pvalue(a);
}

// 変換後の型がAnyを継承した型の場合
template<class U>
inline const void* unchecked_cast_helper_helper(const AnyPtr& a, const Any*, const U*){
	return &a;
}

// 変換後の型がAnyやBaseを継承していない型の場合
template<class U>
inline const void* unchecked_cast_helper_helper(const AnyPtr& a, const void*, const U*){
	return ((SmartPtr<U>&)a).get();
}

/////////////////////////////////////////////////////////////////////////////

template<class T>
struct CastHelper{

	// 変換後の型が参照でもポインタでもない場合、ポインタ型としてキャストしたあと実体にする
	static T as(const AnyPtr& a){ 
		if(can_cast(a)){ return unchecked_cast(a); }else{ return *(const T*)&null;} }
		
	static T cast(const AnyPtr& a){ 
		return *xtal::cast<const T*>(a); }
		
	static bool can_cast(const AnyPtr& a){ 
		return xtal::can_cast<const T*>(a); }

	static T unchecked_cast(const AnyPtr& a){ 
		return *xtal::unchecked_cast<const T*>(a); }
};

template<class T>
struct CastHelper<T*>{

	// 変換後の型がポインタの場合
	static T* as(const AnyPtr& a){ 
		if(can_cast(a)){ return unchecked_cast(a); }else{ return 0;} }
		
	static T* cast(const AnyPtr& a){ 
		return (T*)cast_helper_helper(a, (T*)0, (T*)0); }	
		
	static bool can_cast(const AnyPtr& a){ 
		return can_cast_helper_helper(a, (T*)0, (T*)0); }	

	static T* unchecked_cast(const AnyPtr& a){ 
		return (T*)unchecked_cast_helper_helper(a, (T*)0, (T*)0); }	
};

template<class T>
struct CastHelper<T&>{
	
	// 変換後の型が参照の場合、ポインタ型としてキャストしたあと参照にする
	static T& as(const AnyPtr& a){ 
		if(can_cast(a)){ return unchecked_cast(a); }else{ return *(T*)&null;} }
		
	static T& cast(const AnyPtr& a){ 
		return *xtal::cast<T*>(a); }
		
	static bool can_cast(const AnyPtr& a){ 
		return xtal::can_cast<T*>(a); }

	static T& unchecked_cast(const AnyPtr& a){ 
		return *xtal::unchecked_cast<T*>(a); }
};

//////////////////////////////////////////////////////////////////////////////

/**
* @brief T型に変換する。
*
* Tに変換できない場合、
* Tがポインタ型ならNULLを返す。
* Tが値か参照で、AnyPtrを継承した型ならxtal::nullを返す。
* それ以外の型の場合は未定義。
*/
template<class T> 
inline typename CastResult<T>::type 
as(const AnyPtr& a){
	return CastHelper<T>::as(a);
}

/**
* @brief T型に変換する。
*
* T型に変換できない場合、builtin()->member("CastError")が投げられる
*/
template<class T>
inline typename CastResult<T>::type 
cast(const AnyPtr& a){
	return CastHelper<T>::cast(a);
}

/**
* @brief T型に変換できるか調べる。
*
*/
template<class T>
inline bool can_cast(const AnyPtr& a){
	return CastHelper<T>::can_cast(a);
}

/**
* @brief T型にチェック無しで変換する。
*
*/
template<class T>
inline typename CastResult<T>::type 
unchecked_cast(const AnyPtr& a){
	return CastHelper<T>::unchecked_cast(a);
}

/**
* @brief SmartPtr<T>型に変換する。
*
* Tに変換できない場合xtal::nullを返す。
*/
template<class T> 
inline const SmartPtr<T>&
ptr_as(const AnyPtr& a){
	return CastHelper<const SmartPtr<T>&>::as(a);
}

/**
* @brief SmartPtr<T>型に変換する。
*
* T型に変換できない場合、builtin()->member("CastError")が投げられる
*/
template<class T>
inline const SmartPtr<T>&
ptr_cast(const AnyPtr& a){
	return CastHelper<const SmartPtr<T>&>::cast(a);
}

/**
* @brief SmartPtr<T>型に、実際の型がどうであるかを無視して強制変換する。
*/
template<class T>
inline const SmartPtr<T>&
unchecked_ptr_cast(const AnyPtr& a){
	return *(const SmartPtr<T>*)&a;
}

template<class T>
inline typename CastResult<T>::type 
tricky_cast(const AnyPtr& a, void (*f)(T)){
	return cast<T>(a);
}

template<class T>
inline typename CastResult<T>::type 
tricky_as(const AnyPtr& a, void (*f)(T)){
	return as<T>(a);
}

/////////////////////////////////////////////////////////////////////////////

template<>
struct CastHelper<AnyPtr*>{
	static AnyPtr* as(const AnyPtr& a){ return (AnyPtr*)&a; }
	static AnyPtr* cast(const AnyPtr& a){ return (AnyPtr*)&a; }
	static bool can_cast(const AnyPtr& a){ return true; }
	static AnyPtr* unchecked_cast(const AnyPtr& a){ return (AnyPtr*)&a; }
};

template<>
struct CastHelper<const AnyPtr*>{
	static const AnyPtr* as(const AnyPtr& a){ return (AnyPtr*)&a; }
	static const AnyPtr* cast(const AnyPtr& a){ return (AnyPtr*)&a; }
	static bool can_cast(const AnyPtr& a){ return true; }
	static AnyPtr* unchecked_cast(const AnyPtr& a){ return (AnyPtr*)&a; }
};

template<>
struct CastHelper<const AnyPtr&>{
	static const AnyPtr& as(const AnyPtr& a){ return (AnyPtr&)a; }
	static const AnyPtr& cast(const AnyPtr& a){ return (AnyPtr&)a; }
	static bool can_cast(const AnyPtr& a){ return true; }
	static const AnyPtr& unchecked_cast(const AnyPtr& a){ return (AnyPtr&)a; }
};

template<>
struct CastHelper<Any*>{
	static Any* as(const AnyPtr& a){ return (Any*)&a; }
	static Any* cast(const AnyPtr& a){ return (Any*)&a; }
	static bool can_cast(const AnyPtr& a){ return true; }
	static Any* unchecked_cast(const AnyPtr& a){ return (Any*)&a; }
};

template<>
struct CastHelper<const Any*>{
	static const Any* as(const AnyPtr& a){ return (Any*)&a; }
	static const Any* cast(const AnyPtr& a){ return (Any*)&a; }
	static bool can_cast(const AnyPtr& a){ return true; }
	static const Any* unchecked_cast(const AnyPtr& a){ return (Any*)&a; }
};


template<>
struct CastHelper<const Any&>{
	static Any& as(const AnyPtr& a){ return *(Any*)&a; }
	static Any& cast(const AnyPtr& a){ return *(Any*)&a; }
	static bool can_cast(const AnyPtr& a){ return true; }
	static Any& unchecked_cast(const AnyPtr& a){ return *(Any*)&a; }
};


template<>
struct CastHelper<const IDPtr*>{
	static const IDPtr* as(const AnyPtr& a);
	static const IDPtr* cast(const AnyPtr& a);
	static bool can_cast(const AnyPtr& a);
	static const IDPtr* unchecked_cast(const AnyPtr& a);
};

template<>
struct CastHelper<const char_t*>{
	static const char_t* as(const AnyPtr& a);
	static const char_t* cast(const AnyPtr& a);
	static bool can_cast(const AnyPtr& a);
	static const char_t* unchecked_cast(const AnyPtr& a);
};


template<>
struct CastHelper<int_t>{
	static int_t as(const AnyPtr& a);
	static int_t cast(const AnyPtr& a);
	static bool can_cast(const AnyPtr& a);
	static int_t unchecked_cast(const AnyPtr& a);
};

template<>
struct CastHelper<float_t>{
	static float_t as(const AnyPtr& a);
	static float_t cast(const AnyPtr& a);
	static bool can_cast(const AnyPtr& a);
	static float_t unchecked_cast(const AnyPtr& a);
};

template<>
struct CastHelper<bool>{
	static bool as(const AnyPtr& a){ return a; }
	static bool cast(const AnyPtr& a){ return a; }
	static bool can_cast(const AnyPtr& a){ return true; }
	static bool unchecked_cast(const AnyPtr& a){ return a; }
};

#define XTAL_CAST_HELPER(Type) \
template<> struct CastResult<const Type&>{ typedef Type type; };\
template<>\
struct CastHelper<const Type&>{\
	static Type as(const AnyPtr& a){ return xtal::as<Type>(a); }\
	static Type cast(const AnyPtr& a){ return xtal::cast<Type>(a); }\
	static bool can_cast(const AnyPtr& a){ return xtal::can_cast<Type>(a); }\
	static Type unchecked_cast(const AnyPtr& a){ return xtal::unchecked_cast<Type>(a); }\
}

XTAL_CAST_HELPER(int_t);
XTAL_CAST_HELPER(float_t);
XTAL_CAST_HELPER(bool);

#undef XTAL_CAST_HELPER

#define XTAL_CAST_HELPER(Type, Type2) \
template<>\
struct CastHelper<avoid<Type>::type>{\
	static Type as(const AnyPtr& a){ return (Type)xtal::CastHelper<Type2>::as(a); }\
	static Type cast(const AnyPtr& a){ return (Type)xtal::CastHelper<Type2>::cast(a); }\
	static bool can_cast(const AnyPtr& a){ return xtal::CastHelper<Type2>::can_cast(a); }\
	static Type unchecked_cast(const AnyPtr& a){ return (Type)xtal::CastHelper<Type2>::unchecked_cast(a); }\
};\
template<> struct CastResult<avoid<const Type&> >{ typedef Type type; };\
template<>\
struct CastHelper<avoid<const Type&> >{\
	static Type as(const AnyPtr& a){ return xtal::as<Type>(a); }\
	static Type cast(const AnyPtr& a){ return xtal::cast<Type>(a); }\
	static bool can_cast(const AnyPtr& a){ return xtal::can_cast<Type>(a); }\
	static Type unchecked_cast(const AnyPtr& a){ return (Type)xtal::unchecked_cast<Type2>(a); }\
}

XTAL_CAST_HELPER(int, int_t);
XTAL_CAST_HELPER(unsigned int, int_t);
XTAL_CAST_HELPER(long, int_t);
XTAL_CAST_HELPER(unsigned long, int_t);
XTAL_CAST_HELPER(short, int_t);
XTAL_CAST_HELPER(unsigned short, int_t);
XTAL_CAST_HELPER(char, int_t);
XTAL_CAST_HELPER(signed char, int_t);
XTAL_CAST_HELPER(unsigned char, int_t);
XTAL_CAST_HELPER(float, float_t);
XTAL_CAST_HELPER(double, float_t);
XTAL_CAST_HELPER(long double, float_t);

#undef XTAL_CAST_HELPER

}
