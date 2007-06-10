
#pragma once

#include "any.h"

namespace xtal{

void InitString(); 
	
// fwd decl
class StringImpl;

/**
* @brief ������
*
*/
class String : public Any{
public:

	/**
	* @brief NUL�I�[��C�����񂩂�\�z����
	*
	* @param str NULL�I�[������
	*/
	String(const char* str = "");

	/**
	* @brief STL�̕����񂩂�\�z����
	*
	*/
	String(const string_t& str);

	/**
	* @brief C�����񂩂�size���̒��������o���\�z����
	*
	*/
	String(const char* str, int_t size);
	
	/**
	* @brief begin����last�܂ł̕�����ō\�z����
	*
	* [begin, last)
	*/
	String(const char* begin, const char* last);

	/**
	* @brief ���C�����񂩂�\�z����
	*
	*/
	String(const char* str1, int_t size1, const char* str2, int_t size2);


	struct delegate_memory_t{};

	/**
	* @brief user_malloc�Ŋl���������������Ϗ����č\�z����B
	*
	* @param str NULL�I�[������
	* @param size ������̒���
	* @param buffer_size �m�ۂ����o�b�t�@�̃T�C�Y
	*/
	String(char* str, int_t size, int_t buffer_size, delegate_memory_t);

	explicit String(StringImpl* p)
		:Any((AnyImpl*)p){}

	explicit String(const StringImpl* p)
		:Any((AnyImpl*)p){}

	/**
	* @brief ������𐶐������Anull������
	*
	*/
	String(const Null&)
		:Any(null){}

public:

	/**
	* @brief 0�I�[�̕�����擪�̃|�C���^��Ԃ��B
	*
	*/
	const char* c_str() const;

	/**
	* @brief ������̒�����Ԃ��B
	*
	*/
	int_t size() const;

	/**
	* @brief ������̒�����Ԃ��B
	*
	*/
	int_t length() const;

	/**
	* @brief ��������������o���B
	*
	*/
	String slice(int_t first, int_t last) const;

	/*
	* @brief �󂢃R�s�[��Ԃ��B
	*
	*/
	String clone() const;

	/**
	* @brief ��Ӊ������������Ԃ��B
	*
	*/
	ID intern() const;

	/**
	* @brief ��Ӊ�����Ă��邩�Ԃ��B
	*/
	bool is_interned() const;

	/**
	* @brief �����ɕϊ��������ʂ�Ԃ��B
	*
	*/ 
	int_t to_i() const;
	
	/**
	* @brief ���������_���ɕϊ��������ʂ�Ԃ��B
	*
	*/ 
	float_t to_f() const;
	
	/**
	* @brief �������g��Ԃ��B
	*
	*/
	String to_s() const;

	/**
	* @brief sep�ŋ�؂���������𓾂���C�e���[�^��Ԃ��B
	*
	*/ 
	Any split(const String& sep) const;

	/**
	* @brief �A������
	*
	*/
	String cat(const String& v) const;

public:

	String op_cat_String(const String& v) const;
	String op_mul_Int(int_t v) const;

	void op_cat(const VMachine& vm) const;
	void op_eq(const VMachine& vm) const;
	void op_lt(const VMachine& vm) const;

	String op_cat_r_String(const String& v) const;
	bool op_eq_r_String(const String& v) const;
	bool op_lt_r_String(const String& v) const;

	StringImpl* impl() const{ return (StringImpl*)Any::impl(); }
};

/**
* @brief �K���C���^�[���ς݂̕������ێ����邽�߂̃N���X
*
*/
class ID : public String{
public:
	
	/**
	* @brief NUL�I�[��C�����񂩂�\�z����
	*
	*/	
	ID(const char* name = "");
	
	/**
	* @brief C�����񂩂�size���̒��������o���\�z����
	*
	*/
	ID(const char* name, int_t size);

	/**
	* @brief String����\�z����
	*
	*/
	ID(const String& name);
		
	/**
	* @brief ������𐶐������Anull������
	*
	*/
	ID(const Null&)
		:String(null){}
};

inline bool operator ==(const ID& a, const ID& b){ return a.raweq(b); }
inline bool operator !=(const ID& a, const ID& b){ return !a.raweq(b); }

struct Named2;

/**
* @brief ���O�t�������̃g���b�N�̂��߂̃N���X
*
*/
struct Named2{
	ID name;
	Any value;

	Named2(const char* name)
		:name(name){}

	Named2(const ID& name)
		:name(name), value(null){}

	Named2(const ID& name, const Any& value)
		:name(name), value(value){}

	Named2()
		:name(null), value(null){}

	Named2(const Null&)
		:name(null), value(null){}
};

/**
* @brief ���O�t�������̃g���b�N�̂��߂̃N���X
*
*/
struct Named : public Named2{

	Named(const ID& name)
		:Named2(name){}

	Named(const ID& name, const Any& value)
		:Named2(name, value){}

	Named(){}

	Named(const Null&){}
};

/*
* @brief ���O�t�������̃g���b�N�̂��߂̃N���X
*
*/
struct Key : public ID{
	
	/**
	* @brief ID����\�z����
	*
	*/
	Key(const ID& name)
		:ID(name){}
	
	/**
	* @brief Key("key")=10�Ƃ��������̂��߂̑�����Z�q
	*
	*/
	Named operator =(const Any& value){
		return Named(*this, value);
	}
};


template<class Ch, class T>
std::basic_ostream<Ch, T>& operator << (std::basic_ostream<Ch, T>& os, const Any& a){
	String str = a.to_s(); 
	os << str.c_str();
	return os;
}
	
#ifdef XTAL_USE_PREDEFINED_ID

//{ID{{
namespace id{
extern ID id__ARGS__;
extern ID idop_or_assign;
extern ID idop_add_assign;
extern ID idop_shr;
extern ID idop_ushr_assign;
extern ID idop_call;
extern ID idop_sub_assign;
extern ID idop_lt;
extern ID idop_eq;
extern ID idop_mul;
extern ID idop_neg;
extern ID idmarshal_new;
extern ID iditer_next;
extern ID iditer_first;
extern ID idtrue;
extern ID idmarshal_dump;
extern ID idop_and_assign;
extern ID idop_mod_assign;
extern ID idop_div_assign;
extern ID idop_or;
extern ID idop_div;
extern ID idlib;
extern ID idop_cat_assign;
extern ID idop_cat;
extern ID idIOError;
extern ID idmarshal_load;
extern ID idfalse;
extern ID idop_add;
extern ID idop_cat_r_String;
extern ID idop_dec;
extern ID idop_inc;
extern ID idop_ushr;
extern ID idop_pos;
extern ID idop_shr_assign;
extern ID idop_mod;
extern ID iditer_break;
extern ID idop_eq_r_String;
extern ID idstring;
extern ID idinitialize;
extern ID idop_set_at;
extern ID idop_lt_r_String;
extern ID idtest;
extern ID idop_at;
extern ID idop_shl_assign;
extern ID idop_sub;
extern ID idvalue;
extern ID idop_clone;
extern ID idop_com;
extern ID idnew;
extern ID idop_shl;
extern ID idop_xor;
extern ID idop_and;
extern ID idsize;
extern ID idop_xor_assign;
extern ID idop_mul_assign;
}
//}}ID}



#else

#endif

}
