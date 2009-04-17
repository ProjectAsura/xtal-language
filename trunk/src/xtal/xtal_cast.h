/** \file src/xtal/xtal_cast.h
* \brief src/xtal/xtal_cast.h
*/

#ifndef XTAL_CAST_H_INCLUDE_GUARD
#define XTAL_CAST_H_INCLUDE_GUARD

#pragma once

namespace xtal{
	

struct ParamInfo;
struct VMAndData;

template<class T>
struct ConvertibleToAnyPtr{
	enum{ value = 0 };
};

typedef void (*bind_class_fun_t)(const ClassPtr&);

struct CppClassSymbolData{ 
	CppClassSymbolData();

	unsigned int value;
	CppClassSymbolData* prev;
	bind_class_fun_t prebind;
	bind_class_fun_t bind;
	const char_t* name;
};

template<class T>
struct CppClassSymbol{
	static CppClassSymbolData* value;
	static CppClassSymbolData* make();
};

template<class T>
CppClassSymbolData* CppClassSymbol<T>::make(){
	static CppClassSymbolData data;
	return &data;
}

template<class T>
CppClassSymbolData* CppClassSymbol<T>::value = CppClassSymbol<T>::make();

template<class T> struct CppClassSymbol<T&> : public CppClassSymbol<T>{};
template<class T> struct CppClassSymbol<T*> : public CppClassSymbol<T>{};
template<class T> struct CppClassSymbol<const T> : public CppClassSymbol<T>{};
template<class T> struct CppClassSymbol<volatile T> : public CppClassSymbol<T>{};
template<class T> struct CppClassSymbol<SmartPtr<T> > : public CppClassSymbol<T>{};

template<> struct CppClassSymbol<Base> : public CppClassSymbol<Any>{};
template<> struct CppClassSymbol<ID> : public CppClassSymbol<String>{};

struct CppClassBindTemp{
	CppClassBindTemp(bind_class_fun_t& dest, bind_class_fun_t src, const char_t*& name, const char_t* given);
	char dummy;
};

template<class T>
struct CppClassBindFun{
	static void prebind(const ClassPtr&);
	static void bind(const ClassPtr&);

	static volatile CppClassBindTemp bind_temp;
	static volatile CppClassBindTemp prebind_temp;
};

#define XTAL_BIND(ClassName) \
	template<> void ::xtal::CppClassBindFun<ClassName>::bind(const ::xtal::ClassPtr&);\
	template<> volatile ::xtal::CppClassBindTemp xtal::CppClassBindFun<ClassName>::bind_temp(\
		::xtal::CppClassSymbol<ClassName>::make()->bind, &::xtal::CppClassBindFun<ClassName>::bind, ::xtal::CppClassSymbol<ClassName>::make()->name, XTAL_STRING(#ClassName));\
	template<> void ::xtal::CppClassBindFun<ClassName>::bind(const ::xtal::ClassPtr& it)

#define XTAL_PREBIND(ClassName) \
	template<> void ::xtal::CppClassBindFun<ClassName>::prebind(const ::xtal::ClassPtr&);\
	template<> volatile ::xtal::CppClassBindTemp xtal::CppClassBindFun<ClassName>::prebind_temp(\
		::xtal::CppClassSymbol<ClassName>::make()->prebind, &::xtal::CppClassBindFun<ClassName>::prebind, ::xtal::CppClassSymbol<ClassName>::make()->name, XTAL_STRING(#ClassName));\
	template<> void ::xtal::CppClassBindFun<ClassName>::prebind(const ::xtal::ClassPtr& it)


struct CppVarSymbolData{ 
	CppVarSymbolData(){
		static unsigned int counter = 1;
		value = counter++;
	}

	unsigned int value;
};

template<class T>
struct CppVarSymbol{
	static CppVarSymbolData value;
};

template<class T>
CppVarSymbolData CppVarSymbol<T>::value;

struct IdentifierData{ 
	IdentifierData(){
		static unsigned int counter = 0;
		value = counter++;
	}

	unsigned int value;
};

template<class T>
struct Identifier{
	static IdentifierData value;
};

template<class T>
IdentifierData Identifier<T>::value;

#define XTAL_DECL_ID(x) class xtal_id_##x
#define XTAL_ID2(x) ::xtal::intern_literal(XTAL_STRING(#x), &::xtal::Identifier<typename x>::value)

inline const IDPtr& intern(const StringLiteral& str);

#define XTAL_ID(x) ::xtal::intern(XTAL_STRING(#x))


/**
* \internal
* brief cast�֐��Aas�֐��̖߂�l�̌^�����肷�邽�߂̃w���p�[�e���v���[�g�N���X
*
* �قƂ�ǂ̏ꍇ�ACastResult<T>::type��T���g��Ԃ��B
* �قȂ�ꍇ�Ƃ��ẮA�Ⴆ��CastResult<const int&>::type ��int��Ԃ��B
*/
template<class T>
struct CastResult{ typedef T type; };

template<class T>
inline typename CastResult<T>::type cast(const AnyPtr& a);
	
template<class T>
inline bool can_cast(const AnyPtr& a);

template<class T>
inline typename CastResult<T>::type unchecked_cast(const AnyPtr& a);

template<class T>
const ClassPtr& cpp_class();

/////////////////////////////////////////////////////////////////////////////

// �ϊ���̌^��SmartPtr�̏ꍇ
template<class U, class V>
inline const void* unchecked_cast_helper(const AnyPtr& a, const SmartPtr<U>*, const V&){
	return &a;
}

// �ϊ���̌^��Base���p�������^�̏ꍇ
template<class U>
inline const void* unchecked_cast_helper(const AnyPtr& a, const Base*, const U*){
	return pvalue(a);
}

// �ϊ���̌^��RefCountingBaseBase���p�������^�̏ꍇ
template<class U>
inline const void* unchecked_cast_helper(const AnyPtr& a, const RefCountingBase*, const U*){
	return rcpvalue(a);
}

// �ϊ���̌^��Any���p�������^�̏ꍇ
template<class U>
inline const void* unchecked_cast_helper(const AnyPtr& a, const Any*, const U*){
	return &a;
}

// �ϊ���̌^��Any��Base���p�����Ă��Ȃ��^�̏ꍇ
template<class U>
inline const void* unchecked_cast_helper(const AnyPtr& a, const void*, const U*){
	return ((SmartPtr<U>&)a).get();
}

/////////////////////////////////////////////////////////////////////////////

// �ϊ���̌^��SmartPtr�̏ꍇ
template<class U, class V>
inline const void* get_null_helper(const SmartPtr<U>*, const V&){
	return &null;
}

// �ϊ���̌^��Base���p�������^�̏ꍇ
template<class U>
inline const void* get_null_helper(const Base*, const U*){
	return 0;
}

// �ϊ���̌^��RefCountingBase���p�������^�̏ꍇ
template<class U>
inline const void* get_null_helper(const RefCountingBase*, const U*){
	return 0;
}

// �ϊ���̌^��Any���p�������^�̏ꍇ
template<class U>
inline const void* get_null_helper(const Any*, const U*){
	return &null;
}

// �ϊ���̌^��Any��Base���p�����Ă��Ȃ��^�̏ꍇ
template<class U>
inline const void* get_null_helper(const void*, const U*){
	return U();
}

/////////////////////////////////////////////////////////////////////////////

template<class T>
struct CastHelper{
	// �ϊ���̌^���Q�Ƃł��|�C���^�ł��Ȃ��ꍇ�A�|�C���^�^�Ƃ��ăL���X�g�������Ǝ��̂ɂ���
	
	static bool can_cast(const AnyPtr& a){ 
		return a->is(cpp_class<T>());
	}

	static T unchecked_cast(const AnyPtr& a){ 
		return *CastHelper<const T*>::unchecked_cast(a); 
	}
	
	static T get_null(){ 
		return *CastHelper<const T*>::get_null();
	}
};

template<class T>
struct CastHelper<T&>{
	// �ϊ���̌^���Q�Ƃ̏ꍇ�A�|�C���^�^�Ƃ��ăL���X�g�������ƎQ�Ƃɂ���
	
	static bool can_cast(const AnyPtr& a){ 
		return a->is(cpp_class<T>());
	}
	
	static T& unchecked_cast(const AnyPtr& a){ 
		return *CastHelper<const T*>::unchecked_cast(a); 
	}

	static T& get_null(){ 
		return *CastHelper<const T*>::get_null();
	}
};

template<class T>
struct CastHelper<T*>{
	// �ϊ���̌^���|�C���^�̏ꍇ

	static bool can_cast(const AnyPtr& a){ 
		return a->is(cpp_class<T>());
	}

	static T* unchecked_cast(const AnyPtr& a){ 
		return (T*)unchecked_cast_helper(a, (T*)0, (T*)0); 
	}	

	static T* get_null(){ 
		return (T*)get_null_helper((T*)0, (T*)0);
	}
};

template<class T>
struct CastHelperHelper{
	static T cast(const AnyPtr& a){ 
		if(can_cast(a)){
			return unchecked_cast(a);
		}
		else{
			return get_null();
		}
	}
		
	static bool can_cast(const AnyPtr& a){ 
		return CastHelper<T>::can_cast(a); 
	}

	static T unchecked_cast(const AnyPtr& a){ 
		return CastHelper<T>::unchecked_cast(a); 
	}
	
	static T get_null(){ 
		return CastHelper<T>::get_null();
	}
};

/////////////////////////////////////////////////////////////////////////////

template<>
struct CastHelper<const AnyPtr*>{
	static bool can_cast(const AnyPtr&){ return true; }
	static const AnyPtr* unchecked_cast(const AnyPtr& a){ return (AnyPtr*)&a; }
	static const AnyPtr* get_null(){ return (AnyPtr*)&null; }
};

template<>
struct CastHelper<const Any*>{
	static bool can_cast(const AnyPtr&){ return true; }
	static const Any* unchecked_cast(const AnyPtr& a){ return (Any*)&a; }
	static const Any* get_null(){ return (Any*)&null; }
};

template<>
struct CastHelper<const char_t*>{
	static bool can_cast(const AnyPtr& a){ return a->is(cpp_class<String>()); }
	static const char_t* unchecked_cast(const AnyPtr& a);
	static const Any* get_null(){ return 0; }
};

template<>
struct CastHelper<const IDPtr*>{
	static bool can_cast(const AnyPtr& a);
	static const IDPtr* unchecked_cast(const AnyPtr& a);
	static const IDPtr* get_null(){ return (IDPtr*)&null; }
};


template<>
struct CastHelper<const Int*>{
	static bool can_cast(const AnyPtr& a){ return type(a)==TYPE_INT; }
	static const Int* unchecked_cast(const AnyPtr& a){ return (const Int*)&a; }
	static const Int* get_null(){ return (Int*)&null; }
};

template<>
struct CastHelper<const Float*>{
	static bool can_cast(const AnyPtr& a){ return type(a)==TYPE_FLOAT; }
	static const Float* unchecked_cast(const AnyPtr& a){ return (const Float*)&a; }
	static const Float* get_null(){ return (Float*)&null; }
};

template<>
struct CastHelper<const Bool*>{
	static bool can_cast(const AnyPtr& a){ return type(a)==TYPE_TRUE || type(a)==TYPE_FALSE; }
	static const Bool* unchecked_cast(const AnyPtr& a){ return (const Bool*)&a; }
	static const Bool* get_null(){ return (Bool*)&null; }
};

template<>
struct CastHelper<bool>{
	static bool can_cast(const AnyPtr&){ return true; }
	static bool unchecked_cast(const AnyPtr& a){ return a; }
	static bool get_null(){ return false; }
};

bool Int_can_cast(const AnyPtr& a);
int_t Int_unchecked_cast(const AnyPtr& a);

bool Float_can_cast(const AnyPtr& a);
float_t Float_unchecked_cast(const AnyPtr& a);


#undef XTAL_CAST_HELPER

#define XTAL_CAST_HELPER(Type, XType) \
template<>\
struct CastHelper<Type>{\
	static bool can_cast(const AnyPtr& a){ return XType##_can_cast(a); }\
	static Type unchecked_cast(const AnyPtr& a){ return XType##_unchecked_cast(a); }\
	static Type get_null(){ return 0; }\
};\
template<> struct CppClassSymbol<Type> : public CppClassSymbol<XType>{}


XTAL_CAST_HELPER(char, Int);
XTAL_CAST_HELPER(signed char, Int);
XTAL_CAST_HELPER(unsigned char, Int);
XTAL_CAST_HELPER(short, Int);
XTAL_CAST_HELPER(unsigned short, Int);
XTAL_CAST_HELPER(int, Int);
XTAL_CAST_HELPER(unsigned int, Int);
XTAL_CAST_HELPER(long, Int);
XTAL_CAST_HELPER(unsigned long, Int);

XTAL_CAST_HELPER(float, Float);
XTAL_CAST_HELPER(double, Float);
XTAL_CAST_HELPER(long double, Float);

#undef XTAL_CAST_HELPER

//////////////////////////////////////////////////////////////////////////////

/// \name �^�ϊ�
//@{

/**
* \brief SmartPtr<T>�^�ɕϊ�����B
*
* T�ɕϊ��ł��Ȃ��ꍇxtal::null��Ԃ��B
*/
template<class T>
inline const SmartPtr<T>&
ptr_cast(const AnyPtr& a){
	return CastHelperHelper<const SmartPtr<T>&>::cast(a);
}

/**
* \brief SmartPtr<T>�^�ɁA���ۂ̌^���ǂ��ł��邩�𖳎����ċ����ϊ�����B
*/
template<class T>
inline const SmartPtr<T>&
unchecked_ptr_cast(const AnyPtr& a){
	return *(const SmartPtr<T>*)&a;
}

/**
* \brief T�^�ɕϊ�����B
*
* T�ɕϊ��ł��Ȃ��ꍇ�A
* T���|�C���^�^�Ȃ�NULL��Ԃ��B
* T���l���Q�ƂŁAAnyPtr���p�������^�Ȃ�xtal::null��Ԃ��B
* ����ȊO�̌^�̏ꍇ�͖���`�B
*/
template<class T>
inline typename CastResult<T>::type 
cast(const AnyPtr& a){
	return CastHelperHelper<T>::cast(a);
}

/**
* \brief T�^�ɕϊ��ł��邩���ׂ�B
*
*/
template<class T>
inline bool can_cast(const AnyPtr& a){
	return CastHelperHelper<T>::can_cast(a);
}

/**
* \brief T�^�Ƀ`�F�b�N�����ŕϊ�����B
*
*/
template<class T>
inline typename CastResult<T>::type 
unchecked_cast(const AnyPtr& a){
	return CastHelperHelper<T>::unchecked_cast(a);
}

//@}

//////////////////////////////////////////

template<class T>
inline typename CastResult<T>::type 
tricky_cast(const AnyPtr& a, void (*f)(T)){
	return CastHelperHelper<T>::cast(a);
}

}

#endif // XTAL_CAST_H_INCLUDE_GUARD
