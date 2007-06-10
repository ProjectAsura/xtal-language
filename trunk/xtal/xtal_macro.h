
#pragma once

#include "xtal_lib.h"

/** @addtogroup xmacro */
/*@{*/

/**
* @brief foreach���ȒP�ɋL�q���邽�߂̃}�N��
*
* @code
* Xfor(value, array){
*   // use value
* }
* @endcode
*/
#define Xfor(var, target) \
	if(::xtal::Any var = 1)\
	if(::xtal::IterBreaker tar = target)\
	for(::xtal::iter_next(tar, var, true); tar; ::xtal::iter_next(tar, var, false))

/**
* @brief foreach���ȒP�ɋL�q���邽�߂̃}�N��
*
* @code
* Xfor(key, value, map.send("each_pair")){
*   // use key and value
* }
* @endcode
*/
#define Xfor2(var1, var2, target) \
	if(::xtal::Any var1 = 1)\
	if(::xtal::Any var2 = 1)\
	if(::xtal::IterBreaker tar = target)\
	for(::xtal::iter_next(tar, var1, var2, true); tar; ::xtal::iter_next(tar, var1, var2, false))

/**
* @brief foreach���ȒP�ɋL�q���邽�߂̃}�N��
*
* @code
* Xfor(v1, v2, v3, hoge.send("each3")){
*   // use v1, v2 and v3
* }
* @endcode
*/
#define Xfor3(var1, var2, var3, target) \
	if(::xtal::Any var1 = 1)\
	if(::xtal::Any var2 = 1)\
	if(::xtal::Any var3 = 1)\
	if(::xtal::IterBreaker tar = target)\
	for(::xtal::iter_next(tar, var1, var2, var3, true); tar; ::xtal::iter_next(tar, var1, var2, var3, false))


/**
* @brief get_text���ȒP�ɋL�q���邽�߂̃}�N��
*
* @code
* Any text = Xt("Text %d %s")(10, "test");
* @endcode
*/
#define Xt(text) ::xtal::get_text(text) 

/**
* @brief format���ȒP�ɋL�q���邽�߂̃}�N��
*
* @code
* Any fmt = Xf("Text %d %s")(10, "test");
* @endcode
*/
#define Xf(text) ::xtal::format(text) 

/**
* @brief Xtal�̃\�[�X���ȒP�ɋL�q���邽�߂̃}�N��
*
* @code
* Any src = Xsrc((
*   export [0, 2, 3, 4];
* ));
* @endcode
*/
#define Xsrc(text) ::xtal::source(#text+1, sizeof(#text)-3, __FILE__)

/*@}*/


#ifndef XTAL_USE_PREDEFINED_ID

/*
* @brief �C���^�[�����ꂽ��������ȒP�ɋL�q���邽�߂̃}�N��
* XTAL_USE_PREDEFINED_ID ����`����Ă���ꍇ�A::xtal::id::id##string �Ƃ������O�̕ϐ��̒��ڃA�N�Z�X�ƂȂ�B
* ���鎖��ɂ��A����̓��[�U�[���g���Ă͂Ȃ�Ȃ��}�N���ƂȂ����B
* �����͂܂��g����悤�ɂȂ�������邩������Ȃ��B
* 
* @code
* ID id = Xid(test);
* @endcode
*/
#define Xid(string) ::xtal::ID(#string, sizeof(#string)-1)

#else

#define Xid(string) ::xtal::id::id##string

#endif
