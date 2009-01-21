
#pragma once

namespace xtal{
	
/**
* @brief cast�֐��Aas�֐��̖߂�l�̌^�����肷�邽�߂̃w���p�[�e���v���[�g�N���X
*
* �قƂ�ǂ̏ꍇ�ACastResult<T>::type��T���g��Ԃ��B
* �قȂ�ꍇ�Ƃ��ẮA�Ⴆ��CastResult<const int&>::type ��int��Ԃ��B
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

// �ϊ���̌^��SmartPtr�̏ꍇ
template<class U, class V>
inline const void* cast_helper_helper(const AnyPtr& a, const SmartPtr<U>*, const V&){
	return cast_helper_helper_smartptr(a, get_cpp_class<U>()); 
}

// �ϊ���̌^��Base���p�������^�̏ꍇ
template<class U>
inline const void* cast_helper_helper(const AnyPtr& a, const Base*, const U*){
	return cast_helper_helper_base(a, get_cpp_class<U>()); 
}
	
// �ϊ���̌^��Innocence���p�������^�̏ꍇ
template<class U>
inline const void* cast_helper_helper(const AnyPtr& a, const Innocence*, const U*){
	return cast_helper_helper_innocence(a, get_cpp_class<U>()); 
}
	
// �ϊ���̌^��AnyPtr��Base���p�����Ă��Ȃ��^�̏ꍇ
template<class U>
inline const void* cast_helper_helper(const AnyPtr& a, const void*, const U*){
	return cast_helper_helper_other(a, get_cpp_class<U>()); 
}

/////////////////////////////////////////////////////////////////////////////

// �ϊ���̌^��SmartPtr�̏ꍇ
template<class U, class V>
inline bool can_cast_helper_helper(const AnyPtr& a, const SmartPtr<U>*, const V&){
	return a->is(get_cpp_class<U>());
}

// �ϊ���̌^��Base���p�������^�̏ꍇ
template<class U>
inline bool can_cast_helper_helper(const AnyPtr& a, const Base*, const U*){
	return a->is(get_cpp_class<U>());
}

// �ϊ���̌^��Innocence���p�������^�̏ꍇ
template<class U>
inline bool can_cast_helper_helper(const AnyPtr& a, const Innocence*, const U*){
	return a->is(get_cpp_class<U>());
}

// �ϊ���̌^��Innocence��Base���p�����Ă��Ȃ��^�̏ꍇ
template<class U>
inline bool can_cast_helper_helper(const AnyPtr& a, const void*, const U*){
	return a->is(get_cpp_class<U>());
}

/////////////////////////////////////////////////////////////////////////////

// �ϊ���̌^��SmartPtr�̏ꍇ
template<class U, class V>
inline const void* unchecked_cast_helper_helper(const AnyPtr& a, const SmartPtr<U>*, const V&){
	return &a;
}

// �ϊ���̌^��Base���p�������^�̏ꍇ
template<class U>
inline const void* unchecked_cast_helper_helper(const AnyPtr& a, const Base*, const U*){
	return pvalue(a);
}

// �ϊ���̌^��Innocence���p�������^�̏ꍇ
template<class U>
inline const void* unchecked_cast_helper_helper(const AnyPtr& a, const Innocence*, const U*){
	return &a;
}

// �ϊ���̌^��Innocence��Base���p�����Ă��Ȃ��^�̏ꍇ
template<class U>
inline const void* unchecked_cast_helper_helper(const AnyPtr& a, const void*, const U*){
	return ((SmartPtr<U>&)a).get();
}

/////////////////////////////////////////////////////////////////////////////

#ifdef XTAL_NO_TEMPLATE_PARTIAL_SPECIALIZATION

template<class T>
struct CastHelper{

	// �ϊ���̌^���|�C���^�̏ꍇ
	template<class U> static T as_inner(const AnyPtr& a, U* (*)()){ 
		return (T)as_helper_helper(a, (U*)0, (U*)0); }
		
	template<class U> static T cast_inner(const AnyPtr& a, U* (*)()){ 
		return (T)cast_helper_helper(a, (U*)0, (U*)0); }	
		
	
	// �ϊ���̌^���Q�Ƃ̏ꍇ�A�|�C���^�^�Ƃ��ăL���X�g�������ƎQ�Ƃɂ���
	template<class U> static T as_inner(const AnyPtr& a, U& (*)()){ 
		if(U* ret = xtal::as<U*>(a)){ return *ret; }else{ return *(U*)&null;} }
		
	template<class U> static T cast_inner(const AnyPtr& a, U& (*)()){ 
		return *xtal::cast<U*>(a); }
		

	// �ϊ���̌^���Q�Ƃł��|�C���^�ł��Ȃ��ꍇ�A�|�C���^�^�Ƃ��ăL���X�g�������Ǝ��̂ɂ���
	static T as_inner(const AnyPtr& a, ...){ 
		if(const T* ret = xtal::as<const T*>(a)){ return *ret; }else{ return *(const T*)&null;} }
		
	static T cast_inner(const AnyPtr& a, ...){ 
		return *xtal::cast<const T*>(a); }
		


	static T as(const AnyPtr& a){ 
		return as_inner(a, (T (*)())0); }
		
	static T cast(const AnyPtr& a){ 
		return cast_inner(a, (T (*)())0); }
		
};

#else

template<class T>
struct CastHelper{

	// �ϊ���̌^���Q�Ƃł��|�C���^�ł��Ȃ��ꍇ�A�|�C���^�^�Ƃ��ăL���X�g�������Ǝ��̂ɂ���
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

	// �ϊ���̌^���|�C���^�̏ꍇ
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
	
	// �ϊ���̌^���Q�Ƃ̏ꍇ�A�|�C���^�^�Ƃ��ăL���X�g�������ƎQ�Ƃɂ���
	static T& as(const AnyPtr& a){ 
		if(can_cast(a)){ return unchecked_cast(a); }else{ return *(T*)&null;} }
		
	static T& cast(const AnyPtr& a){ 
		return *xtal::cast<T*>(a); }
		
	static bool can_cast(const AnyPtr& a){ 
		return xtal::can_cast<T*>(a); }

	static T& unchecked_cast(const AnyPtr& a){ 
		return *xtal::unchecked_cast<T*>(a); }
};


#endif

//////////////////////////////////////////////////////////////////////////////

/**
* @brief T�^�ɕϊ�����B
*
* T�ɕϊ��ł��Ȃ��ꍇ�A
* T���|�C���^�^�Ȃ�NULL��Ԃ��B
* T���l���Q�ƂŁAAnyPtr���p�������^�Ȃ�xtal::null��Ԃ��B
* ����ȊO�̌^�̏ꍇ�͖���`�B
*/
template<class T> 
inline typename CastResult<T>::type 
as(const AnyPtr& a){
	return CastHelper<T>::as(a);
}

/**
* @brief T�^�ɕϊ�����B
*
* T�^�ɕϊ��ł��Ȃ��ꍇ�Abuiltin()->member("CastError")����������
*/
template<class T>
inline typename CastResult<T>::type 
cast(const AnyPtr& a){
	return CastHelper<T>::cast(a);
}

/**
* @brief T�^�ɕϊ��ł��邩���ׂ�B
*
*/
template<class T>
inline bool can_cast(const AnyPtr& a){
	return CastHelper<T>::can_cast(a);
}

/**
* @brief T�^�Ƀ`�F�b�N�����ŕϊ�����B
*
*/
template<class T>
inline typename CastResult<T>::type 
unchecked_cast(const AnyPtr& a){
	return CastHelper<T>::unchecked_cast(a);
}

/**
* @brief SmartPtr<T>�^�ɕϊ�����B
*
* T�ɕϊ��ł��Ȃ��ꍇxtal::null��Ԃ��B
*/
template<class T> 
inline const SmartPtr<T>&
ptr_as(const AnyPtr& a){
	return CastHelper<const SmartPtr<T>&>::as(a);
}

/**
* @brief SmartPtr<T>�^�ɕϊ�����B
*
* T�^�ɕϊ��ł��Ȃ��ꍇ�Abuiltin()->member("CastError")����������
*/
template<class T>
inline const SmartPtr<T>&
ptr_cast(const AnyPtr& a){
	return CastHelper<const SmartPtr<T>&>::cast(a);
}

/**
* @brief SmartPtr<T>�^�ɁA���ۂ̌^���ǂ��ł��邩�𖳎����ċ����ϊ�����B
*/
template<class T>
inline const SmartPtr<T>&
static_ptr_cast(const AnyPtr& a){
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
