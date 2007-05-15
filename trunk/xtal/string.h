
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

/**
* @brief ���O�t�������̃g���b�N�̂��߂̃N���X
*
*/
struct Named{

	ID name;
	Any value;

	Named(const ID& n, const Any& v = null)
		:name(n), value(v){}

	Named()
		:name(null), value(null){}

	Named(const Null&)
		:name(null), value(null){}

};


/**
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
	
//{{{
//}}}

}
