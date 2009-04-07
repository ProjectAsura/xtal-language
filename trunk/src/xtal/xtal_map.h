/** \file src/xtal/xtal_map.h
* \brief src/xtal/xtal_map.h
*/

#ifndef XTAL_MAP_H_INCLUDE_GUARD
#define XTAL_MAP_H_INCLUDE_GUARD

#pragma once

namespace xtal{

/**
* \xbind
* \brief �A�z�z��
*/
class Map : public Base{
public:

	/**
	* \xbind
	* \brief ��̘A�z�z��I�u�W�F�N�g�𐶐�
	*/
	Map()
		:default_value_(undefined){}
		
	/**
	* \brief key�ɑΉ�����v�f��Ԃ�
	*
	* \param key �����̂��߂̃L�[ 
	*/
	const AnyPtr& at(const AnyPtr& key);
	
	/**
	* \brief key�ɑΉ�����v�f��ݒ肷��
	*
	* \param key �����̂��߂̃L�[ 
	* \param value key�ɑΉ�����l
	*/	
	void set_at(const AnyPtr& key, const AnyPtr& value){
		insert(key, value);
	}

	/**
	* \xbind
	* \brief key�ɑΉ�����v�f��ݒ肷��
	*
	* \param key �����̂��߂̃L�[ 
	* \param value key�ɑΉ�����l
	*/	
	void insert(const AnyPtr& key, const AnyPtr& value){
		const AnyPtr& akey = calc_key(key);
		table_.insert(akey, value);
	}

	/**
	* \xbind
	* \brief key�ɑΉ�����l���폜����
	*
	* \param key �����̂��߂̃L�[ 
	*/
	void erase(const AnyPtr& key){
		const AnyPtr& akey = calc_key(key);
		table_.erase(akey);
	}

	/**
	* \xbind
	* \brief �A�z�z��ɓo�^���ꂽ�v�f�̐���Ԃ�
	*
	* \return �A�z�z��ɓo�^���ꂽ�v�f�̐�
	*/
	uint_t size(){
		return table_.size();
	}
	
	/**
	* \xbind
	* \brief �A�z�z��ɓo�^���ꂽ�v�f�̐���Ԃ�
	*
	* \return �A�z�z��ɓo�^���ꂽ�v�f�̐�
	*/
	uint_t length(){
		return table_.size();
	}

	/**
	* \xbind
	* \brief �󂩒��ׂ�
	*
	* \retval true ��
	* \retval false ���
	*/
	bool empty(){
		return table_.empty();
	}

	/**
	* \xbind
	* \brief �󂩒��ׂ�
	*
	* \retval true ��
	* \retval false ���
	*/
	bool is_empty(){
		return table_.empty();
	}

	/**
	* \brief �A�������A�z�z���Ԃ�
	*
	*/
	MapPtr cat(const MapPtr& a);

	/**
	* \brief ���g�ƘA�����A���g��Ԃ�
	*
	*/
	MapPtr cat_assign(const MapPtr& a);
		
	/**
	* \xbind
	* \brief (key, value)��v�f�Ƃ���AIterator��Ԃ�
	*
	*/
	AnyPtr pairs();
	
	/**
	* \xbind
	* \brief key��v�f�Ƃ���AIterator��Ԃ�
	*
	*/
	AnyPtr keys();
	
	/**
	* \xbind
	* \brief value��v�f�Ƃ���AIterator��Ԃ�
	*
	*/
	AnyPtr values();

	/**
	* \xbind
	* \brief (key, value)��v�f�Ƃ���AIterator��Ԃ�
	*
	* pairs�Ɠ���
	*/
	AnyPtr each(){
		return pairs();
	}
	
	/**
	* \xbind
	* \brief �󂢃R�s�[��Ԃ�
	*
	*/
	MapPtr clone();

	/**
	* \xbind
	* \brief �v�f��S�č폜����
	*
	*/
	void clear(){
		table_.clear();
	}
	
	MapPtr to_m(){
		return to_smartptr(this);
	}

	/**
	* \xbind
	* \brief ���g��iterator�Ŏ擾�ł���v�f�ɒu��������
	*/
	void assign(const AnyPtr& iterator);

	void concat(const AnyPtr& iterator);

	void push_all(const VMachinePtr& vm);

	/**
	* \xbind
	* \brief �f�t�H���g�l�Ƃ��Đݒ肳��Ă���I�u�W�F�N�g�����o��
	*
	* \return �f�t�H���g�l
	*/
	const AnyPtr& default_value(){
		return default_value_;
	}

	/**
	* \xbind
	* \brief �f�t�H���g�l��ݒ肷��
	*
	* \param default_value �f�t�H���g�l
	*/
	void set_default_value(const AnyPtr& default_value){
		default_value_ = default_value;
	}

protected:

	struct Fun{
		static uint_t hash(const AnyPtr& key){
			return (rawvalue(key).uvalue ^ type(key) ^ (rawvalue(key).uvalue>>3));
		}

		static bool eq(const AnyPtr& a, const AnyPtr& b){
			return raweq(a, b);
		}
	};

	typedef OrderedHashtable<AnyPtr, AnyPtr, Fun> table_t;

	const AnyPtr& calc_key(const AnyPtr& key);

public:

	typedef table_t::iterator iterator;

	iterator begin(){
		return table_.begin();
	}

	iterator end(){
		return table_.end();
	}
	
protected:

	table_t table_;
	AnyPtr default_value_;

	virtual void visit_members(Visitor& m);
};

class MapIter : public Base{
public:

	MapIter(const MapPtr& m, int_t type);
	
	void block_next(const VMachinePtr& vm);

public:

	bool block_next_direct(AnyPtr& rkey, AnyPtr& rval);

private:
	MapPtr map_;
	Map::iterator node_;
	int_t type_;

	virtual void visit_members(Visitor& m);
};

class Set : public Map{
public:

	/**
	* \brief value���^��key��v�f�Ƃ���Iterator��Ԃ�
	*
	*/
	AnyPtr each();
};

}//namespace


#endif // XTAL_MAP_H_INCLUDE_GUARD
