

#pragma once

#include "xtal_any.h"
#include "xtal_string.h"

namespace xtal{

void InitMap();

class MapImpl;

/**
* @brief �A�z�z��
*
*/
class Map : public Any{
public:

	/**
	* @brief ��̘A�z�z��𐶐����� 
	*
	*/
	Map();

	/**
	* @brief �A�z�z��𐶐������Anull������
	*
	*/
	Map(const Null&)
		:Any(null){}

	explicit Map(MapImpl* p)
		:Any((AnyImpl*)p){}

	explicit Map(const MapImpl* p)
		:Any((AnyImpl*)p){}
		
	/**
	* @brief �A�z�z��̗e�ʂ�Ԃ�
	*
	*/
	int_t size() const;

	/**
	* @brief �A�z�z��̗e�ʂ�Ԃ�
	*
	*/
	int_t length() const;

	/**
	* @brief i�ɑΉ�����v�f��Ԃ�
	*
	*/
	const Any& at(const Any& i) const;
	
	/**
	* @brief i�ɑΉ�����v�f��ݒ肷��
	*
	*/
	void set_at(const Any& i, const Any& v) const;
		
	/**
	* @brief �󂢃R�s�[��Ԃ�
	*
	*/
	Map clone() const;
	
	/**
	* @brief ���̔z��̕�����\����Ԃ�
	*
	*/
	String to_s() const;
	
	/**
	* @brief key��value���u���b�N�p�����[�^�Ƃ���Iterator��Ԃ�
	*
	*/
	Any each_pair() const;

	/**
	* @brief key���u���b�N�p�����[�^�Ƃ���Iterator��Ԃ�
	*
	*/
	Any each_key() const;

	/**
	* @brief value���u���b�N�p�����[�^�Ƃ���Iterator��Ԃ�
	*
	*/
	Any each_value() const;

	/**
	* @brief key��value���u���b�N�p�����[�^�Ƃ���Iterator��Ԃ�
	*
	* each_pair�Ɠ���
	*/
	Any each() const{ return each_pair(); }

	/**
	* @brief key�ɑΉ�����l���폜����
	*
	*/
	void erase(const Any& key) const;
	
	/**
	* @brief �A�������A�z�z���Ԃ�
	*
	*/
	Map cat(const Map& a) const;

	/**
	* @brief �A�������A�z�z���Ԃ�
	*
	*/
	Map cat_assign(const Map& a) const;

	/**
	* @brief �󂩒��ׂ�
	*
	*/
	bool empty() const;


	MapImpl* impl() const{ return (MapImpl*)Any::impl(); }

	const Any operator [](const Any& key) const{
		return at(key);
	}
};

}//namespace

