
#pragma once

#include "xtal_any.h"
#include "xtal_string.h"

namespace xtal{

void InitArray();

class ArrayImpl;

/**
* @brief �z��
*
*/
class Array : public Any{
public:
	
	/**
	* @brief size�̒����̔z��𐶐����� 
	*
	*/
	explicit Array(int_t size = 0);

	explicit Array(check_xtype<int>::type size);
	
	/**
	* @brief �z��𐶐������Anull������
	*
	*/
	Array(const Null&)
		:Any(null){}

	explicit Array(ArrayImpl* p)
		:Any((AnyImpl*)p){}

	explicit Array(const ArrayImpl* p)
		:Any((AnyImpl*)p){}
	
	/**
	* @brief �z��̒�����Ԃ�
	*
	*/
	int_t size() const;

	/**
	* @brief �z��̒�����ύX����
	*/
	void resize(int_t sz) const;
	
	/**
	* @brief �z��̒�����Ԃ�
	*
	*/
	int_t length() const;
	
	/**
	* @brief i�Ԗڂ̗v�f��Ԃ�
	*
	*/
	const Any& at(int_t i) const;
	
	/**
	* @brief i�Ԗڂ̗v�f��ݒ肷��
	*
	*/
	void set_at(int_t i, const Any& v) const;

	/**
	* @brief �擪�ɗv�f��ǉ�����
	*
	*/
	void push_front(const Any& v) const;

	/**
	* @brief �擪�̗v�f���폜����
	*
	*/
	void pop_front() const;

	/**
	* @brief �����ɗv�f��ǉ�����
	*
	*/
	void push_back(const Any& v) const;

	/**
	* @brief �����̗v�f���폜����
	*
	*/
	void pop_back() const;

	/**
	* @brief first����last�܂ł̕����z���Ԃ�
	*
	*/
	Array slice(int_t first, int_t last) const;

	/**
	* @brief i�Ԗڂ̗v�f���폜����
	*
	*/
	void erase(int_t i) const;

	/**
	* @brief i�Ԗڂɗv�f��ǉ�����
	*
	*/
	void insert(int_t i, const Any& v) const;

	/**
	* @brief �v�f�𕶎���Ƃ��ĘA���������ʂ�Ԃ�
	*
	* @param sep �v�f�Ɨv�f�̋�؂蕶����
	*/
	String join(const String& sep) const;

	/**
	* @brief ���̔z��̕�����\����Ԃ�
	*
	*/
	String to_s() const;

	/**
	* @brief ���g��Ԃ�
	*
	*/
	Array to_a() const;
	
	/**
	* @brief �󂢃R�s�[��Ԃ�
	*
	*/
	Array clone() const;

	/**
	* @brief �A�������z���Ԃ�
	*
	*/
	Array cat(const Array& a) const;

	/**
	* @brief �A�������z���Ԃ�
	*
	*/
	Array cat_assign(const Array& a) const;

	/**
	* @brief �v�f�����񂷂�Iterator��Ԃ�
	*
	*/
	Any each() const;
	
	/**
	* @brief �v�f��S�č폜����
	*
	*/
	void clear() const;

	/**
	* @brief �󂩒��ׂ�
	*
	*/
	bool empty() const;

	/**
	* @brief �ŏ��̗v�f���擾����
	*
	*/
	const Any& front() const;

	/**
	* @brief �Ō�̗v�f���擾����
	*
	*/
	const Any& back() const;

	/**
	* @brief �z��̗v�f��S�đ��l�Ƃ��ĕԂ�
	*
	*/
	void values(const VMachine& vm) const;

	ArrayImpl* impl() const{ return (ArrayImpl*)Any::impl(); }

	const Any& operator [] (int_t i){
		return at(i);
	}

};

template<class T>
class TArray : public Array{
public:

	TArray(int_t size = 0)
		:Array(size){}
	
	TArray(const Null&)
		:Array(null){}

	explicit TArray(ArrayImpl* p)
		:Array((AnyImpl*)p){}

	explicit TArray(const ArrayImpl* p)
		:Array((AnyImpl*)p){}

	const T& at(int_t i) const{
		return (const T&)Array::at(i);
	}
	
	void set_at(int_t i, const T& v) const{
		Array::set_at(i, v);
	}

	void push_front(const T& v) const{
		Array::push_front(v);
	}

	void push_back(const T& v) const{
		Array::push_back(v);
	}

	TArray slice(int_t first, int_t last) const{
		return Array::slice(first, last).impl();
	}

	void insert(int_t i, const T& v) const{
		Array::insert(i, v);
	}

	TArray cat(const TArray<T>& a) const{ 
		Array::cat(a); 
		return *this;
	}

	const T& operator [] (int_t i){ 
		return (const T&)at(i); 
	}
};

}//namespace

