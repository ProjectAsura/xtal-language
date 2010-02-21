/** \file src/xtal/xtal_array.h
* \brief src/xtal/xtal_array.h
*/

#ifndef XTAL_ARRAY_H_INCLUDE_GUARD
#define XTAL_ARRAY_H_INCLUDE_GUARD

#pragma once

namespace xtal{

/**
* \brief �z��
*/
class xarray{
public:

	/**
	* \brief size�̒����̔z��𐶐����� 
	*/
	xarray(uint_t size = 0);

	xarray(const AnyPtr* first, const AnyPtr* end);

	/**
	* \brief �R�s�[�R���X�g���N�^�������
	*/
	xarray(const xarray& v);

	/**
	* \brief ������Z�q�������
	*/
	xarray& operator =(const xarray& v);

	/**
	* \brief �f�X�g���N�^
	*/
	~xarray();

	/**
	* \brief �z��̒�����Ԃ�
	*/
	uint_t length() const{
		return size_;
	}

	/**
	* \brief �z��̒�����Ԃ�
	*/
	uint_t size() const{
		return size_;
	}

	/**
	* \brief �z��̒�����ύX����
	*/
	void resize(uint_t sz);

	/**
	* \xbind
	* \brief �z���sz����������
	*/
	void upsize(uint_t sz);

	/**
	* \brief �z���sz���Z������
	*/
	void downsize(uint_t sz);

	/**
	* \brief i�Ԗڂ̗v�f��Ԃ�
	*/
	const AnyPtr& at(int_t i) const{
		XTAL_ASSERT(0<=i && (uint_t)i<size_);
		return values_[i];
	}

	/**
	* \brief i�Ԗڂ̗v�f��ݒ肷��
	*/
	void set_at(int_t i, const AnyPtr& v){
		XTAL_ASSERT(0<=i && (uint_t)i<size_);
		values_[i] = v;
	}

	/**
	* \xbind
	* \brief �擪�ɗv�f��ǉ�����
	*/
	void push_front(const AnyPtr& v){
		insert(0, v);
	}

	/**
	* \xbind
	* \brief �擪�̗v�f���폜����
	*/
	void pop_front(){
		erase(0);
	}

	/**
	* \xbind
	* \brief �����ɗv�f��ǉ�����
	*/
	void push_back(const AnyPtr& v);

	/**
	* \xbind
	* \brief �����̗v�f���폜����
	*/
	void pop_back();

	/**
	* \xbind
	* \brief �擪�̗v�f��Ԃ�
	*/
	const AnyPtr& front() const{
		return at(0);
	}

	/**
	* \xbind
	* \brief �����̗v�f��Ԃ�
	*/
	const AnyPtr& back() const{
		return at(size()-1);
	}

	/**
	* \xbind
	* \brief i�Ԗڂ�n�̗v�f���폜����
	*/
	void erase(int_t i, int_t n = 1);

	/**
	* \xbind
	* \brief i�Ԗڂɗv�f��ǉ�����
	*/
	void insert(int_t i, const AnyPtr& v);

	/**
	* \xbind
	* \brief �󂩒��ׂ�
	*/
	bool empty() const{
		return size_ == 0;
	}

	/**
	* \xbind
	* \brief �󂩒��ׂ�
	*/
	bool is_empty() const{
		return size_ == 0;
	}

	/**
	* \xbind
	* \brief �v�f��S�č폜����
	*/
	void clear();

	void shrink_to_fit();

public:

	void on_visit_members(Visitor& m);

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
			return temp;
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

	const AnyPtr* data(){
		return values_;
	}

	void attach(AnyPtr* data, uint_t size){
		values_ = data;
		size_ = size;
		capa_ = size;
	}

	void detach(){
		values_ = 0;
		size_ = 0;
		capa_ = 0;
	}

	void reflesh(){
		AnyPtr* newp = (AnyPtr*)xmalloc(sizeof(AnyPtr)*size_);
		std::memcpy(&newp[0], &values_[0], sizeof(AnyPtr)*size_);
		capa_ = size_;
		values_ = newp;
	}

	void set_at_unref(int_t i, const Any& value){
		(Any&)values_[i] = value;
	}

	void upsize_unref(uint_t size);

	void clear_unref();

	void move_unref(int_t dest, int_t src, int_t n );

	friend void swap(xarray& a, xarray& b){
		std::swap(a.values_, b.values_);
		std::swap(a.size_, b.size_);
		std::swap(a.capa_, b.capa_);
	}

	void init(const AnyPtr* values, uint_t size);

	void destroy();

protected:

	AnyPtr* values_;
	uint_t size_;
	uint_t capa_;
};

void visit_members(Visitor& m, const xarray& values);


/**
* \xbind lib::builtin
* \xinherit lib::builtin::Any lib::builtin::Iterable
* \brief �z��
*/
class Array : public RefCountingBase{
public:
	enum{ TYPE = TYPE_ARRAY };

	/**
	* \xbind
	* \brief size�̒����̔z��𐶐����� 
	*/
	Array(uint_t size = 0);

	Array(const AnyPtr* first, const AnyPtr* end);

public:

	/**
	* \xbind
	* \brief �z��̒�����Ԃ�
	*/
	uint_t length(){
		return values_.length();
	}

	/**
	* \xbind
	* \brief �z��̒�����Ԃ�
	*/
	uint_t size(){
		return values_.size();
	}

	/**
	* \xbind
	* \brief �z��̒�����ύX����
	*/
	void resize(uint_t sz){
		values_.resize(sz);
	}

	/**
	* \xbind
	* \brief �z���sz����������
	*/
	void upsize(uint_t sz){
		values_.upsize(sz);
	}

	/**
	* \xbind
	* \brief �z���sz���Z������
	*/
	void downsize(uint_t sz){
		values_.downsize(sz);
	}

	/**
	* \brief i�Ԗڂ̗v�f��Ԃ�
	*/
	const AnyPtr& at(int_t i){
		return values_.at(i);
	}

	/**
	* \brief i�Ԗڂ̗v�f��ݒ肷��
	*/
	void set_at(int_t i, const AnyPtr& v){
		values_.set_at(i, v);
	}

	/**
	* \xbind
	* \brief i�Ԗڂ̗v�f��Ԃ�
	*/
	const AnyPtr& op_at(int_t i);

	/**
	* \xbind
	* \brief i�Ԗڂ̗v�f��ݒ肷��
	*/
	void op_set_at(int_t i, const AnyPtr& v);

	/**
	* \xbind
	* \brief �擪�ɗv�f��ǉ�����
	*/
	void push_front(const AnyPtr& v){
		insert(0, v);
	}

	/**
	* \xbind
	* \brief �擪�̗v�f���폜����
	*/
	void pop_front(){
		erase(0);
	}

	/**
	* \xbind
	* \brief �����ɗv�f��ǉ�����
	*/
	void push_back(const AnyPtr& v);

	/**
	* \xbind
	* \brief �����̗v�f���폜����
	*/
	void pop_back();

	/**
	* \xbind
	* \brief �擪�̗v�f��Ԃ�
	*/
	const AnyPtr& front(){
		return op_at(0);
	}

	/**
	* \xbind
	* \brief �����̗v�f��Ԃ�
	*/
	const AnyPtr& back(){
		return op_at(size()-1);
	}

	/**
	* \xbind
	* \brief i�Ԗڂ���n�̕����z���Ԃ�
	*/
	ArrayPtr slice(int_t i, int_t n = 1);
	
	/**
	* \xbind
	* \brief index����n�̕����z����폜���A���̕����z���Ԃ�
	*/
	ArrayPtr splice(int_t i, int_t n = 1);

	/**
	* \xbind
	* \brief i�Ԗڂ�n�̗v�f���폜����
	*/
	void erase(int_t i, int_t n = 1);

	/**
	* \xbind
	* \brief i�Ԗڂɗv�f��ǉ�����
	*/
	void insert(int_t i, const AnyPtr& v);

	/**
	* \xbind
	* \brief �z��̗v�f���t���ɂ���C�e���[�^��Ԃ�
	*/
	AnyPtr reverse();
	
	/**
	* \xbind
	* \brief �󂢃R�s�[��Ԃ�
	*/
	ArrayPtr clone();

	/**
	* \brief �A�������z���Ԃ�
	*/
	ArrayPtr op_cat(const ArrayPtr& a);

	/**
	* \brief ���g��A�����A���g��Ԃ�
	*/
	const ArrayPtr& op_cat_assign(const ArrayPtr& a);
	
	/**
	* \xbind
	* \brief �v�f�𕶎���Ƃ��ĘA���������ʂ�Ԃ�
	* \param sep �v�f�Ɨv�f�̋�؂蕶����
	*/
	StringPtr join(const StringPtr& sep);

	/**
	* \xbind
	* \brief ���g��Ԃ�
	*/
	const ArrayPtr& op_to_array(){
		return to_smartptr(this);
	}

	/**
	* \xbind
	* \brief �l�������������ׂ�
	*/
	bool op_eq(const ArrayPtr& other);

	/**
	* \xbind
	* \brief �󂩒��ׂ�
	*/
	bool empty(){
		return values_.empty();
	}

	/**
	* \xbind
	* \brief �󂩒��ׂ�
	*/
	bool is_empty(){
		return values_.is_empty();
	}

	/**
	* \xbind
	* \brief �v�f��S�č폜����
	*/
	void clear(){
		values_.clear();
	}

	/**
	* \xbind
	* \brief �v�f���ŏ����甽���ł���Iterator��Ԃ�
	*/
	AnyPtr each();

	/**
	* \xbind
	* \brief ���g��iterator�Ŏ擾�ł���v�f�ɒu��������
	*/
	void assign(const AnyPtr& iterator);

	/**
	* \xbind
	* \brief iterator�Ŏ擾�ł���v�f��ǉ�����
	*/
	void append(const AnyPtr& iterator);

	StringPtr to_s();

public:

	void block_first(const VMachinePtr& vm);

	void on_visit_members(Visitor& m);

	typedef xarray::iterator iterator;

	iterator begin(){
		return values_.begin();
	}

	iterator end(){
		return values_.end();
	}

	const AnyPtr* data(){
		return values_.data();
	}

	void attach(AnyPtr* data, uint_t size){
		values_.attach(data, size);
	}

	void detach(){
		values_.detach();
	}

	void set_at_unref(int_t i, const Any& value){
		values_.set_at_unref(i, value);
	}

	void upsize_unref(uint_t size){
		values_.upsize_unref(size);
	}

	void clear_unref(){
		values_.clear_unref();
	}

	void reflesh(){
		values_.reflesh();
	}

protected:

	void throw_index_error();

	xarray values_;

private:
	XTAL_DISALLOW_COPY_AND_ASSIGN(Array);
};

class ArrayIter : public Base{
public:

	ArrayIter(const AnyPtr& a, xarray* v, bool reverse = false);
			
	void block_next(const VMachinePtr& vm);

public:

	bool block_next_direct(AnyPtr& ret);

	void on_visit_members(Visitor& m);

private:
	AnyPtr ref_;
	xarray* values_;
	uint_t index_;
	bool reverse_;
};

template<>
struct XNew<Array> : XXNew<Array>{
	XNew(uint_t size = 0);
	XNew(const AnyPtr* first, const AnyPtr* end);
};

}

#endif // XTAL_ARRAY_H_INCLUDE_GUARD
