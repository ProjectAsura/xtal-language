
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
	if(::xtal::BlockValueHolder<1> block_value_holder = AnyPtr(tar))\
	for(::xtal::AnyPtr &var = block_value_holder.values[0]; block_value_holder;)\
	for(::xtal::block_next(block_value_holder, true); block_value_holder; ::xtal::block_next(block_value_holder, false))

/**
* @brief foreach���ȒP�ɋL�q���邽�߂̃}�N��
*
* @code
* Xfor2(key, value, map){
*   // use key and value
* }
* @endcode
*/
#define Xfor2(var1, var2, tar) \
	if(::xtal::BlockValueHolder<2> block_value_holder = AnyPtr(tar))\
	for(::xtal::AnyPtr &var1 = block_value_holder.values[0], &var2 = block_value_holder.values[1]; block_value_holder;)\
	for(::xtal::block_next(block_value_holder, true); block_value_holder; ::xtal::block_next(block_value_holder, false))

/**
* @brief foreach���ȒP�ɋL�q���邽�߂̃}�N��
*
* @code
* Xfor3(v1, v2, v3, hoge.send("each3")){
*   // use v1, v2 and v3
* }
* @endcode
*/
#define Xfor3(var1, var2, var3, tar) \
	if(::xtal::BlockValueHolder<3> block_value_holder = tar)\
	for(::xtal::AnyPtr &var1 = block_value_holder.values[0], &var2 = block_value_holder.values[1], &var3 = block_value_holder.values[2]; block_value_holder;)\
	for(::xtal::block_next(block_value_holder, true); block_value_holder; ::xtal::block_next(block_value_holder, false))


/**
* @brief foreach���ȒP�ɋL�q���邽�߂̃}�N��
*
* �e�v�f���󂯎��ϐ��Ɍ^�����邱�Ƃ��o����B
* @code
* Xfor_cast(AnyPtr& value, array){
*   // use value
* }
* @endcode
*/
#define Xfor_cast(var, tar) \
	if(::xtal::BlockValueHolder<1> block_value_holder = AnyPtr(tar))\
	for(var = ::xtal::tricky_cast(block_value_holder.values[0], (void (*)(var##e))0); block_value_holder;)\
	for(::xtal::block_next(block_value_holder, true); block_value_holder; ::xtal::block_next(block_value_holder, false))

/**
* @brief foreach���ȒP�ɋL�q���邽�߂̃}�N��
*
* �e�v�f���󂯎��ϐ��Ɍ^�����邱�Ƃ��o����B
* @code
* Xfor2_cast(AnyPtr& key, AnyPtr& value, map){
*   // use key and value
* }
* @endcode
*/
#define Xfor2_cast(var1, var2, tar) \
	if(::xtal::BlockValueHolder<2> block_value_holder = AnyPtr(tar))\
	for(var1 = ::xtal::tricky_cast(block_value_holder.values[0], (void (*)(var1##e))0); block_value_holder;)\
	for(var2 = ::xtal::tricky_cast(block_value_holder.values[1], (void (*)(var2##e))0); block_value_holder;)\
	for(::xtal::block_next(block_value_holder, true); block_value_holder; ::xtal::block_next(block_value_holder, false))

/**
* @brief foreach���ȒP�ɋL�q���邽�߂̃}�N��
*
* �e�v�f���󂯎��ϐ��Ɍ^�����邱�Ƃ��o����B
* @code
* Xfor3_cast(AnyPtr& v1, AnyPtr& v2, AnyPtr& v3, hoge.send("each3")){
*   // use v1, v2 and v3
* }
* @endcode
*/
#define Xfor3_cast(var1, var2, var3, tar) \
	if(::xtal::BlockValueHolder<3> block_value_holder = AnyPtr(tar))\
	for(var1 = ::xtal::tricky_cast(block_value_holder.values[0], (void (*)(var1##e))0); block_value_holder;)\
	for(var2 = ::xtal::tricky_cast(block_value_holder.values[1], (void (*)(var2##e))0); block_value_holder;)\
	for(var3 = ::xtal::tricky_cast(block_value_holder.values[2], (void (*)(var3##e))0); block_value_holder;)\
	for(::xtal::block_next(block_value_holder, true); block_value_holder; ::xtal::block_next(block_value_holder, false))

/**
* @brief foreach���ȒP�ɋL�q���邽�߂̃}�N��
*
* �e�v�f���󂯎��ϐ��Ɍ^�����邱�Ƃ��o����B
* @code
* Xfor_t(AnyPtr& value, array){
*   // use value
* }
* @endcode
*/
#define Xfor_as(var, tar) \
	if(::xtal::BlockValueHolder<1> block_value_holder = tar)\
	for(::xtal::block_next(block_value_holder, true); block_value_holder; ::xtal::block_next(block_value_holder, false))\
	if(var = ::xtal::tricky_as(block_value_holder.values[0], (void (*)(var##e))0))

/**
* @brief text���ȒP�ɋL�q���邽�߂̃}�N��
*
* @code
* AnyPtr text = Xt("Text %d %s")(10, "test");
* @endcode
*/
#define Xt(txt) ::xtal::text(XTAL_STRING(txt)) 

/**
* @brief format���ȒP�ɋL�q���邽�߂̃}�N��
*
* @code
* AnyPtr fmt = Xf("Text %d %s")(10, "test");
* @endcode
*/
#define Xf(txt) ::xtal::format(XTAL_STRING(txt)) 

/**
* @brief Xtal�̃\�[�X���ȒP�ɋL�q���邽�߂̃}�N��
*
* @code
* AnyPtr src = Xsrc((
*   return [0, 2, 3, 4];
* ));
* @endcode
*/
#define Xsrc(text) ::xtal::source(XTAL_STRING(#text)+1, sizeof(XTAL_STRING(#text))/sizeof(char_t)-3, __FILE__)

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
