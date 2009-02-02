
#pragma once

namespace xtal{

class Map : public Base{
public:

	Map()
		:default_value_(undefined){}
		
	/**
	* @brief i�ɑΉ�����v�f��Ԃ�
	*
	*/
	const AnyPtr& at(const AnyPtr& key);
	
	/**
	* @brief i�ɑΉ�����v�f��ݒ肷��
	*
	*/	
	void set_at(const AnyPtr& key, const AnyPtr& value){
		insert(key, value);
	}

	/**
	* @brief i�ɑΉ�����v�f��ݒ肷��
	*
	*/	
	void insert(const AnyPtr& akey, const AnyPtr& value){
		const AnyPtr& key = calc_key(akey);
		table_.insert(key, value);
	}

	/**
	* @brief key�ɑΉ�����l���폜����
	*
	*/
	void erase(const AnyPtr& akey){
		const AnyPtr& key = calc_key(akey);
		table_.erase(key);
	}

	/**
	* @brief �A�z�z��̗e�ʂ�Ԃ�
	*
	*/
	int_t size(){
		return table_.size();
	}
	
	/**
	* @brief �A�z�z��̗e�ʂ�Ԃ�
	*
	*/
	int_t length(){
		return table_.size();
	}

	/**
	* @brief �󂩒��ׂ�
	*
	*/
	bool empty(){
		return table_.empty();
	}

	/**
	* @brief �A�������A�z�z���Ԃ�
	*
	*/
	MapPtr cat(const MapPtr& a);

	/**
	* @brief ���g�ƘA�����A���g��Ԃ�
	*
	*/
	MapPtr cat_assign(const MapPtr& a);

	/**
	* @brief == �̍Ē�`
	*/
	bool op_eq(const MapPtr& other);
		
	/**
	* @brief [key, value]��v�f�Ƃ���AIterator��Ԃ�
	*
	*/
	AnyPtr pairs();
	
	/**
	* @brief key��v�f�Ƃ���AIterator��Ԃ�
	*
	*/
	AnyPtr keys();
	
	/**
	* @brief value��v�f�Ƃ���AIterator��Ԃ�
	*
	*/
	AnyPtr values();

	/**
	* @brief [key, value]��v�f�Ƃ���AIterator��Ԃ�
	*
	* pairs�Ɠ���
	*/
	AnyPtr each(){
		return pairs();
	}
	
	/**
	* @brief �󂢃R�s�[��Ԃ�
	*
	*/
	MapPtr clone();

	/**
	* @brief �v�f��S�č폜����
	*
	*/
	void clear(){
		table_.clear();
	}
	
	MapPtr to_m(){
		return from_this(this);
	}

	/**
	* @brief ���g��iterator�Ŏ擾�ł���v�f�ɒu��������
	*/
	void assign(const AnyPtr& iterator);

	void concat(const AnyPtr& iterator);

	void push_all(const VMachinePtr& vm);

	const AnyPtr& default_value(){
		return default_value_;
	}

	void set_default_value(const AnyPtr& default_value){
		default_value_ = default_value;
	}

protected:

	struct Fun{
		static uint_t hash(const AnyPtr& key){
			return (rawvalue(key) ^ type(key) ^ (rawvalue(key)>>3));
		}

		static bool eq(const AnyPtr& a, const AnyPtr& b){
			return raweq(a, b);
		}
	};

	typedef Hashtable<AnyPtr, AnyPtr, Fun> table_t;

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
	* @brief value���^��key��v�f�Ƃ���Iterator��Ԃ�
	*
	*/
	AnyPtr each();
};

}//namespace

