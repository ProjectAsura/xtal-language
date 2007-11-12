
#pragma once

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
#define Xfor(var, tar) \
	if(::xtal::BlockValueHolder<1> block_value_holder = tar)\
	for(::xtal::AnyPtr &var = block_value_holder.values[0]; block_value_holder;)\
	for(::xtal::block_next(block_value_holder, true); block_value_holder; ::xtal::block_next(block_value_holder, false))

/**
* @brief foreach���ȒP�ɋL�q���邽�߂̃}�N��
*
* @code
* Xfor(key, value, map){
*   // use key and value
* }
* @endcode
*/
#define Xfor2(var1, var2, tar) \
	if(::xtal::BlockValueHolder<2> block_value_holder = tar)\
	for(::xtal::AnyPtr &var1 = block_value_holder.values[0], &var2 = block_value_holder.values[1]; block_value_holder;)\
	for(::xtal::block_next(block_value_holder, true); block_value_holder; ::xtal::block_next(block_value_holder, false))

/**
* @brief foreach���ȒP�ɋL�q���邽�߂̃}�N��
*
* @code
* Xfor(v1, v2, v3, hoge.send("each3")){
*   // use v1, v2 and v3
* }
* @endcode
*/
#define Xfor3(var1, var2, var3, tar) \
	if(::xtal::BlockValueHolder<3> block_value_holder = tar)\
	for(::xtal::AnyPtr &var1 = block_value_holder.values[0], &var2 = block_value_holder.values[1], &var3 = block_value_holder.values[2]; block_value_holder;)\
	for(::xtal::block_next(block_value_holder, true); block_value_holder; ::xtal::block_next(block_value_holder, false))


/**
* @brief text���ȒP�ɋL�q���邽�߂̃}�N��
*
* @code
* AnyPtr text = Xt("Text %d %s")(10, "test");
* @endcode
*/
#define Xt(txt) ::xtal::text(txt) 

/**
* @brief format���ȒP�ɋL�q���邽�߂̃}�N��
*
* @code
* AnyPtr fmt = Xf("Text %d %s")(10, "test");
* @endcode
*/
#define Xf(txt) ::xtal::format(txt) 

/**
* @brief Xtal�̃\�[�X���ȒP�ɋL�q���邽�߂̃}�N��
*
* @code
* AnyPtr src = Xsrc((
*   return [0, 2, 3, 4];
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
* IDPtr id = Xid(test);
* @endcode
*/
#define Xid(string) ::xtal::IDPtr(#string, sizeof(#string)-1)

#else

#define Xid(string) ((const ::xtal::IDPtr&) ::xtal::id::id_list[::xtal::id::id##string])

#endif
