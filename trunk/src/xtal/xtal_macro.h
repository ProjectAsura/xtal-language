#ifndef XTAL_MACRO_H_INCLUDE_GUARD
#define XTAL_MACRO_H_INCLUDE_GUARD

#pragma once

/** @addtogroup xmacro */
/*@{*/

/**
* \brief foreach���ȒP�ɋL�q���邽�߂̃}�N��
*
* \hideinitializer
* \code
* Xfor(value, array){
*   // use value
* }
* \endcode
*/
#define Xfor(var, target) \
	if(bool not_end = true)\
	for(::xtal::BlockValueHolder1 block_value_holder(target, not_end); not_end; not_end=false)\
	for(const ::xtal::AnyPtr& var = block_value_holder.values[0]; not_end; not_end=false)\
	for(bool first_step=not_end=::xtal::block_next(block_value_holder, true); not_end; not_end=::xtal::block_next(block_value_holder, false), first_step=false)

/**
* \brief foreach���ȒP�ɋL�q���邽�߂̃}�N��
*
* \hideinitializer
* \code
* Xfor2(key, value, map){
*   // use key and value
* }
* \endcode
*/
#define Xfor2(var1, var2, target) \
	if(bool not_end = true)\
	for(::xtal::BlockValueHolder2 block_value_holder(target, not_end); not_end; not_end=false)\
	for(const ::xtal::AnyPtr& var1 = block_value_holder.values[0], &var2 = block_value_holder.values[1]; not_end; not_end=false)\
	for(bool first_step=not_end=::xtal::block_next(block_value_holder, true); not_end; not_end=::xtal::block_next(block_value_holder, false), first_step=false)

/**
* \brief foreach���ȒP�ɋL�q���邽�߂̃}�N��
*
* \hideinitializer
* \code
* Xfor3(v1, v2, v3, hoge.send("each3")){
*   // use v1, v2 and v3
* }
* \endcode
*/
#define Xfor3(var1, var2, var3, target) \
	if(bool not_end = true)\
	for(::xtal::BlockValueHolder3 block_value_holder(target, not_end); not_end; not_end=false)\
	for(const ::xtal::AnyPtr& var1 = block_value_holder.values[0], &var2 = block_value_holder.values[1], &var3 = block_value_holder.values[2]; not_end; not_end=false)\
	for(bool first_step=not_end=::xtal::block_next(block_value_holder, true); not_end; not_end=::xtal::block_next(block_value_holder, false), first_step=false)


/**
* \brief foreach���ȒP�ɋL�q���邽�߂̃}�N��
*
* �e�v�f���󂯎��ϐ��Ɍ^�����邱�Ƃ��o����B
* \hideinitializer
* \code
* Xfor_cast(const StringPtr& value, array){
*   // value��StringPtr�ɃL���X�g����Ă���
* }
* else{
*   // else������ƁA�L���X�g�Ɏ��s��������s�����
* }
* \endcode
*/
#define Xfor_cast(var, target) \
	if(bool not_end = true)\
	for(::xtal::BlockValueHolder1 block_value_holder(target, not_end); not_end; not_end=false)\
	for(bool first_step=not_end=::xtal::block_next(block_value_holder, true); not_end; not_end=::xtal::block_next(block_value_holder, false), first_step=false)\
	if(var = ::xtal::tricky_cast(block_value_holder.values[0], (void (*)(var##e))0))

/**
* \brief text���ȒP�ɋL�q���邽�߂̃}�N��
*
* \hideinitializer
* \code
* AnyPtr text = Xt("Text %d %s")(10, "test");
* \endcode
*/
#define Xt(txt) ::xtal::text(XTAL_STRING(txt)) 

/**
* \brief format���ȒP�ɋL�q���邽�߂̃}�N��
*
* \hideinitializer
* \code
* AnyPtr fmt = Xf("Text %d %s")(10, "test");
* \endcode
*/
#define Xf(txt) ::xtal::format(XTAL_STRING(txt)) 

#ifndef XTAL_NO_PARSER

/**
* \brief Xtal�̃\�[�X���ȒP�ɋL�q���邽�߂̃}�N��
*
* \hideinitializer
* \code
* AnyPtr src = Xsrc((
*   return [0, 2, 3, 4];
* ));
* \endcode
*/
#define Xsrc(text) ::xtal::source(XTAL_STRING(#text)+1, sizeof(#text)-3)

#endif

#ifdef XTAL_USE_COMPILED_EMB
#define Xemb(text, compiled_text) \
	if(::xtal::CodePtr code = ::xtal::compiled_source(compiled_text, sizeof(compiled_text)-1)){\
		code->call();\
	}\
	else{\
		XTAL_CATCH_EXCEPT(e){\
			::xtal::stderr_stream()->println(e);\
		}\
	}
#else
#define Xemb(text, compiled_text) \
	if(::xtal::CodePtr code = ::xtal::source(XTAL_STRING(#text)+1, sizeof(#text)-3)){\
		code->call();\
	}\
	else{\
		XTAL_CATCH_EXCEPT(e){\
			::xtal::stderr_stream()->println(e);\
		}\
	}
#endif

/*
* \brief �C���^�[�����ꂽ��������ȒP�ɋL�q���邽�߂̃}�N��
*
* \hideinitializer
* \code
* IDPtr id = Xid(test);
* \endcode
*/
#define Xid(x) ::xtal::intern(XTAL_STRING(#x))

/*@}*/

#endif // XTAL_MACRO_H_INCLUDE_GUARD
