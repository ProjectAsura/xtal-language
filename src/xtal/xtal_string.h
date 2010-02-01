/** \file src/xtal/xtal_string.h
* \brief src/xtal/xtal_string.h
*/

#ifndef XTAL_STRING_H_INCLUDE_GUARD
#define XTAL_STRING_H_INCLUDE_GUARD

#pragma once

namespace xtal{

class StringData;

/**
* \xbind lib::builtin
* \xinherit lib::builtin::Any lib::builtin::Iterable
* \brief ������̃N���X
*/
class String : public Any{
public:

	/**
	* \xbind
	* \brief �󕶎�����\�z����
	*/
	String();

	/**
	* \brief NUL�I�[��C�����񂩂�\�z����
	* \param str NUL�I�[������
	*/
	String(const char_t* str);

	/**
	* \brief NUL�I�[��C�����񂩂�\�z����
	* \param str NUL�I�[������
	*/
	String(const char8_t* str);

	/**
	* \brief C�����񂩂�size���̒��������o���\�z����
	*/
	String(const char_t* str, uint_t size);

	/**
	* \brief C�����񃊃e��������\�z����
	*/
	String(const StringLiteral& str);

	/**
	* \brief begin����last�܂ł̕�����ō\�z����
	* [begin, last)
	*/
	String(const char_t* begin, const char_t* last);

	/**
	* \brief ���C�����񂩂�\�z����
	*/
	String(const char_t* str1, uint_t size1, const char_t* str2, uint_t size2);

public:

	struct intern_t{};
	String(const char_t* str, uint_t size, intern_t);
	String(const StringLiteral& str, intern_t);
	
	String& operator= (const String& s);

	String(const String& s);

protected:

	String(noinit_t){}

public:

	/**
	* \brief 0�I�[�̕�����擪�̃|�C���^��Ԃ��B
	* data()��data_size()�ő�p�\�Ȃ炻������g���Ă��������B
	*/
	const char_t* c_str() const;

	/**
	* \brief ������擪�̃|�C���^��Ԃ��B
	* �����0�I�[�����񂪕Ԃ����Ƃ͌���Ȃ��B
	*/
	const char_t* data() const;

	/**
	* \xbind
	* \brief �f�[�^�T�C�Y��Ԃ��B
	* �}���`�o�C�g�������l�����Ȃ��B
	*/
	uint_t data_size() const;

	/**
	* \xbind
	* \brief ������̒�����Ԃ��B
	* �}���`�o�C�g�������l������B
	*/
	uint_t length() const;

	/*
	* \brief �󂢃R�s�[��Ԃ��B
	*/
	StringPtr clone() const;

	/**
	* \xbind
	* \brief ��Ӊ������������Ԃ��B
	*/
	const IDPtr& intern() const;

	/**
	* \xbind
	* \brief ��Ӊ�����Ă��邩�Ԃ��B
	*/
	bool is_interned() const;

	/**
	* \xbind
	* \brief �����ɕϊ��������ʂ�Ԃ��B
	*/ 
	int_t to_i() const;
	
	/**
	* \xbind
	* \brief ���������_���ɕϊ��������ʂ�Ԃ��B
	*/ 
	float_t to_f() const;
	
	/**
	* \xbind
	* \brief �������g��Ԃ��B
	*/
	StringPtr to_s() const;

	/**
	* \xbind
	* \brief �ꕶ���Â̕������v�f�Ƃ���Iterator��Ԃ��B
	* \return �ꕶ���Â̕������v�f�Ƃ���Iterator
	*/
	AnyPtr each() const;

	/**
	* \xbind
	* \brief �A������
	* \return �A�����ꂽ�V�����I�u�W�F�N�g
	*/
	StringPtr cat(const StringPtr& v) const;

public:

	/**
	* \xbind
	* \brief �ꕶ���̕����񂩂ǂ���
	*/
	bool is_ch() const;

	/**
	* \xbind
	* \brief ��̕����񂩂ǂ���
	*/
	bool is_empty() const;
	bool empty() const{ return is_empty(); }

	/**
	* \xbind
	* \brief �ꕶ���̕�����̏ꍇ�A����ascii�R�[�h��Ԃ�
	*/
	int_t ascii() const;

	/**
	* \xbind
	* \brief �����͈̔̓I�u�W�F�N�g�͈͓̔����ǂ���
	*/
	bool op_in(const ChRangePtr& range) const;

public:

	/**
	* \xbind
	* \brief �͈̓I�u�W�F�N�g�𐶐�����
	*/
	ChRangePtr op_range(const StringPtr& right, int_t kind) const;
	
	/**
	* \xbind
	* \brief �A������
	*/
	StringPtr op_cat(const StringPtr& v) const;
	
	/**
	* \xbind
	* \brief �l������������ׂ�
	*/
	bool op_eq(const StringPtr& v) const;

	/**
	* \xbind
	* \brief ��菬��������ׂ�
	*/
	bool op_lt(const StringPtr& v) const;

public:

	/**
	* \xbind
	* \brief ��������X�L��������
	*/
	AnyPtr scan(const AnyPtr& pattern) const;

	/**
	* \xbind
	* \brief ������𕪊����A���̕����������v�f�Ƃ���Iterator��Ԃ�
	*/
	AnyPtr split(const AnyPtr& pattern) const;

	/**
	* \xbind
	* \brief ������𕪊����A���̕����������v�f�Ƃ���Iterator��Ԃ�
	*/	
	bool match(const AnyPtr& pattern) const;

	/**
	* \xbind
	* \brief �}�b�`���镔����u���������V�����������Ԃ�
	*/	
	StringPtr gsub(const AnyPtr& pattern, const AnyPtr& fn) const;

	/**
	* \xbind
	* \brief �ŏ��Ƀ}�b�`���镔����u���������V�����������Ԃ�
	*/	
	StringPtr sub(const AnyPtr& pattern, const AnyPtr& fn) const;

private:
	void init_string(const char_t* str, uint_t size);
	StringData* new_string_data(uint_t size);

public:

	class iterator{
	public:
		
		iterator(const char_t* p)
			:p_(p){}
		
		char_t operator *() const{
			return *p_;
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
		const char_t* p_;
	};

	iterator begin() const;

	iterator end() const;
};

class StringData : public RefCountingBase{
	enum{
		INTERNED = 1<<0,
		SIZE_SHIFT = 1
	};

	char_t* buf_;
	uint_t data_size_;
public:

	enum{
		TYPE = TYPE_STRING
	};

	StringData(uint_t size);

	~StringData();

	uint_t data_size(){
		return data_size_>>SIZE_SHIFT;
	}

	char_t* buf(){ 
		return buf_; 
	}

	bool is_interned(){
		return (data_size_&INTERNED)!=0;
	}

	void set_interned(){
		data_size_ |= INTERNED;
	}

private:
	
	XTAL_DISALLOW_COPY_AND_ASSIGN(StringData);
};


/**
* \brief Intern�ς݂�String
*
* �����C++�̌^�V�X�e���̂��߂ɑ��݂���B
* Xtal�ɂ�����Intern�ς�String��String�^�ł���B
*/
class ID : public String{
public:

	/**
	* \brief NUL�I�[��C�����񂩂�\�z����
	*
	* \param str NULL�I�[������
	*/
	ID(const char_t* str);

	/**
	* \brief NUL�I�[��C�����񂩂�\�z����
	*
	* \param str NULL�I�[������
	*/
	ID(const char8_t* str);

	/**
	* \brief C�����񂩂�size���̒��������o���\�z����
	*
	*/
	ID(const char_t* str, uint_t size);
	
	/**
	* \brief C�����񃊃e��������\�z����
	*
	*/
	ID(const StringLiteral& str);

	/**
	* \brief begin����last�܂ł̕�����ō\�z����
	*
	* [begin, last)
	*/
	ID(const char_t* begin, const char_t* last);

	/**
	* \brief String����\�z����
	*
	*/
	ID(const StringPtr& name);		
};

inline bool operator ==(const IDPtr& a, const IDPtr& b){ return raweq(a, b); }
inline bool operator !=(const IDPtr& a, const IDPtr& b){ return rawne(a, b); }

AnyPtr interned_strings();
int_t edit_distance(const StringPtr& str1, const StringPtr& str2);
uint_t string_hashcode(const char_t* str, uint_t size);
void string_data_size_and_hashcode(const char_t* str, uint_t& size, uint_t& hash);
uint_t string_length(const char_t* str);
uint_t string_data_size(const char_t* str);
int_t string_compare(const char_t* a, uint_t asize, const char_t* b, uint_t bsize);
void string_copy(char_t* a, const char_t* b, uint_t size);
bool string_is_ch(const char_t* str, uint_t size);

class ChRange : public Range{
public:

	ChRange(const StringPtr& left, const StringPtr& right)
		:Range(left, right, RANGE_CLOSED){}

public:

	const StringPtr& left(){ return unchecked_ptr_cast<String>(left_); }

	const StringPtr& right(){ return unchecked_ptr_cast<String>(right_); }

	AnyPtr each();
};

class StringEachIter : public Base{
public:

	StringEachIter(const StringPtr& str);

	void block_next(const VMachinePtr& vm);

	void on_visit_members(Visitor& m);


private:
	StringStreamPtr ss_;
};

class ChRangeIter : public Base{
public:

	ChRangeIter(const ChRangePtr& range)
		:it_(range->left()), end_(range->right()){}

	void block_next(const VMachinePtr& vm);

private:
	StringPtr it_, end_;
};

}

#endif // XTAL_STRING_H_INCLUDE_GUARD
