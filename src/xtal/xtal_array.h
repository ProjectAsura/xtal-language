
#pragma once

namespace xtal{

/**
* @brief �z��
*
*/
class Array : public RefCountingBase{
public:
	enum{ TYPE = TYPE_ARRAY };

	/**
	* @brief size�̒����̔z��𐶐����� 
	*
	*/
	Array(uint_t size = 0);

	Array(const AnyPtr* first, const AnyPtr* end);

	/**
	* @brief �R�s�[�R���X�g���N�^�������
	*/
	Array(const Array& v);

	/**
	* @brief ������Z�q�������
	*/
	Array& operator =(const Array& v);

	/**
	* @brief �f�X�g���N�^
	*/
	~Array();


	/**
	* @brief �z��̒�����Ԃ�
	*
	*/
	uint_t length(){
		return size_;
	}

	/**
	* @brief �z��̒�����Ԃ�
	*
	*/
	uint_t size(){
		return size_;
	}

	/**
	* @brief �z��̒�����ύX����
	*/
	void resize(uint_t sz);

	/**
	* @brief �z���sz����������
	*/
	void upsize(uint_t sz);

	/**
	* @brief �z���sz���Z������
	*/
	void downsize(uint_t sz);

	/**
	* @brief i�Ԗڂ̗v�f��Ԃ�
	*
	*/
	const AnyPtr& at(int_t i){
		XTAL_ASSERT(0<=i && (uint_t)i<size_);
		return values_[i];
	}

	/**
	* @brief i�Ԗڂ̗v�f��ݒ肷��
	*
	*/
	void set_at(int_t i, const AnyPtr& v){
		XTAL_ASSERT(0<=i && (uint_t)i<size_);
		values_[i] = v;
	}

	/**
	* @brief i�Ԗڂ̗v�f��Ԃ�
	*
	*/
	const AnyPtr& op_at(int_t i);

	/**
	* @brief i�Ԗڂ̗v�f��ݒ肷��
	*
	*/
	void op_set_at(int_t i, const AnyPtr& v);

	/**
	* @brief �擪�ɗv�f��ǉ�����
	*
	*/
	void push_front(const AnyPtr& v){
		insert(0, v);
	}

	/**
	* @brief �擪�̗v�f���폜����
	*
	*/
	void pop_front(){
		erase(0);
	}

	/**
	* @brief �����ɗv�f��ǉ�����
	*
	*/
	void push_back(const AnyPtr& v);

	/**
	* @brief �����̗v�f���폜����
	*
	*/
	void pop_back();

	/**
	* @brief �擪�̗v�f��Ԃ�
	*
	*/
	const AnyPtr& front(){
		return op_at(0);
	}

	/**
	* @brief �����̗v�f��Ԃ�
	*
	*/
	const AnyPtr& back(){
		return op_at(size()-1);
	}

	/**
	* @brief i�Ԗڂ���n�̕����z���Ԃ�
	*
	*/
	ArrayPtr slice(int_t i, int_t n = 1);
	
	/**
	* @brief index����n�̕����z����폜���A���̕����z���Ԃ�
	*
	*/
	ArrayPtr splice(int_t i, int_t n = 1);

	/**
	* @brief i�Ԗڂ�n�̗v�f���폜����
	*
	*/
	void erase(int_t i, int_t n = 1);

	/**
	* @brief i�Ԗڂɗv�f��ǉ�����
	*
	*/
	void insert(int_t i, const AnyPtr& v);

	/**
	* @brief �z��̗v�f���t���ɂ���C�e���[�^��Ԃ�
	*
	*/
	AnyPtr reverse();
	
	/**
	* @brief �󂢃R�s�[��Ԃ�
	*
	*/
	ArrayPtr clone();

	/**
	* @brief �A�������z���Ԃ�
	*
	*/
	ArrayPtr cat(const ArrayPtr& a);

	/**
	* @brief ���g��A�����A���g��Ԃ�
	*
	*/
	ArrayPtr cat_assign(const ArrayPtr& a);
	
	/**
	* @brief �v�f�𕶎���Ƃ��ĘA���������ʂ�Ԃ�
	*
	* @param sep �v�f�Ɨv�f�̋�؂蕶����
	*/
	StringPtr join(const StringPtr& sep);

	/**
	* @brief ���g��Ԃ�
	*
	*/
	ArrayPtr to_a(){
		return to_smartptr(this);
	}

	bool op_eq(const ArrayPtr& other);

	/**
	* @brief �󂩒��ׂ�
	*
	*/
	bool empty(){
		return size_ == 0;
	}

	/**
	* @brief �󂩒��ׂ�
	*
	*/
	bool is_empty(){
		return size_ == 0;
	}

	/**
	* @brief �v�f��S�č폜����
	*
	*/
	void clear();

	/**
	* @brief �v�f���ŏ����甽���ł���Iterator��Ԃ�
	*
	*/
	AnyPtr each();

	/**
	* @brief ���g��iterator�Ŏ擾�ł���v�f�ɒu��������
	*/
	void assign(const AnyPtr& iterator);

	void concat(const AnyPtr& iterator);

public:

	void visit_members(Visitor& m);

	class iterator{
	public:
		
		iterator(AnyPtr* p = 0)
			:p_(p){}
		
		AnyPtr& operator *() const{
			return *p_;
		}

		AnyPtr* operator ->() const{
			return p_;
		}

		iterator& operator ++(){
			++p_;
			return *this;
		}

		iterator operator ++(int){
			iterator temp(*this);
			++p_;
			return *this;
		}

		friend bool operator ==(iterator a, iterator b){
			return a.p_ == b.p_;
		}

		friend bool operator !=(iterator a, iterator b){
			return a.p_ != b.p_;
		}

	private:
		AnyPtr* p_;
	};

	iterator begin(){
		return iterator(values_);
	}

	iterator end(){
		return iterator(values_ + size_);
	}


protected:

	int_t calc_offset(int_t i);
	void throw_index_error();

	AnyPtr* values_;
	uint_t size_;
	uint_t capa_;
};

class ArrayIter : public Base{
public:

	ArrayIter(const ArrayPtr& a, bool reverse = false);
			
	void block_next(const VMachinePtr& vm);

public:

	bool block_next_direct(AnyPtr& ret);

private:
	ArrayPtr array_;
	uint_t index_;
	bool reverse_;

	virtual void visit_members(Visitor& m);
};

class MultiValue : public RefCountingBase{
public:
	enum{ TYPE = TYPE_MULTI_VALUE };

	MultiValue(const AnyPtr& head, const MultiValuePtr& tail = null)
		:head_(head), tail_(tail){
		set_pvalue(*this, TYPE, this);
	}

	const AnyPtr& head(){
		return head_;
	}

	const MultiValuePtr& tail(){
		return tail_;
	}

	void block_next(const VMachinePtr& vm);

	int_t size();

	const AnyPtr& at(int_t i);

	void visit_members(Visitor& m){
		m & head_ & tail_;
	}

public:

	void set(const AnyPtr& head, const MultiValuePtr& tail = null){
		head_ = head;
		tail_ = tail;
	}

private:
	AnyPtr head_;
	MultiValuePtr tail_;
};

void bind(MultiValue*);

inline MultiValuePtr mv(const AnyPtr& v1, const AnyPtr& v2){
	return xnew<MultiValue>(v1, xnew<MultiValue>(v2));
}

}
