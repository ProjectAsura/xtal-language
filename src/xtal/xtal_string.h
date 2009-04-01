#ifndef XTAL_STRING_H_INCLUDE_GUARD
#define XTAL_STRING_H_INCLUDE_GUARD

#pragma once

namespace xtal{

/**
* \brief ������
*/
class String : public Any{
public:

	/**
	* \brief �󕶎�����\�z����
	*/
	String();

	/**
	* \brief NUL�I�[��C�����񂩂�\�z����
	*
	* \param str NULL�I�[������
	*/
	String(const char_t* str);

	/**
	* \brief NUL�I�[��C�����񂩂�\�z����
	*
	* \param str NULL�I�[������
	*/
	String(const char8_t* str);

	/**
	* \brief C�����񂩂�size���̒��������o���\�z����
	*
	*/
	String(const char_t* str, uint_t size);

	/**
	* \brief C�����񃊃e��������\�z����
	*
	*/
	String(const StringLiteral& str);

	/**
	* \brief begin����last�܂ł̕�����ō\�z����
	*
	* [begin, last)
	*/
	String(const char_t* begin, const char_t* last);

	/**
	* \brief ���C�����񂩂�\�z����
	*
	*/
	String(const char_t* str1, uint_t size1, const char_t* str2, uint_t size2);

	/**
	* \brief 1�̕�������\�z����
	*/
	String(char_t a);

	/**
	* \brief 2�̕�������\�z����
	*/
	String(char_t a, char_t b);

	/**
	* \brief 3�̕�������\�z����
	*/
	String(char_t a, char_t b, char_t c);

public:

	struct make_t{};
	String(const char_t* str, uint_t size, make_t);
	
	String& operator= (const String& s);

	String(const String& s);

protected:

	String(noinit_t n)
		:Any(n){}

public:

	/**
	* \brief 0�I�[�̕�����擪�̃|�C���^��Ԃ��B
	*
	*/
	const char_t* c_str();

	/**
	* \brief ������擪�̃|�C���^��Ԃ��B
	*
	* �����0�I�[�����񂪕Ԃ����Ƃ͌���Ȃ��B
	*/
	const char_t* data();

	/**
	* \brief �f�[�^�T�C�Y��Ԃ��B
	*
	* �}���`�o�C�g�������l�����Ȃ��B
	*/
	uint_t data_size();

	/**
	* \brief ������̒�����Ԃ��B
	*
	* �}���`�o�C�g�������l������B
	*/
	uint_t length();

	/*
	* \brief �󂢃R�s�[��Ԃ��B
	*
	*/
	StringPtr clone();

	/**
	* \brief ��Ӊ������������Ԃ��B
	*
	*/
	const IDPtr& intern();

	/**
	* \brief ��Ӊ�����Ă��邩�Ԃ��B
	*/
	bool is_interned();

	/**
	* \brief �����ɕϊ��������ʂ�Ԃ��B
	*
	*/ 
	int_t to_i();
	
	/**
	* \brief ���������_���ɕϊ��������ʂ�Ԃ��B
	*
	*/ 
	float_t to_f();
	
	/**
	* \brief �������g��Ԃ��B
	*
	*/
	StringPtr to_s();

	/**
	* \brief �ꕶ���Â̕������v�f�Ƃ���Iterator��Ԃ��B
	*
	*/
	AnyPtr each();

	/**
	* \brief �A������
	*
	*/
	StringPtr cat(const StringPtr& v);

public:

	bool is_ch();

	int_t ascii();

	bool op_in(const ChRangePtr& range);

public:

	ChRangePtr op_range(const StringPtr& right, int_t kind);
	
	StringPtr op_cat(const StringPtr& v);
	
	bool op_eq(const StringPtr& v);

	bool op_lt(const StringPtr& v);

private:
	void init_string(const char_t* str, uint_t size);
};

class StringData : public RefCountingBase{
	enum{
		INTERNED = 1<<0,
		SIZE_SHIFT = 1
	};

	XTAL_DEBUG_ONLY(char_t* buf_;)

	uint_t data_size_;
public:

	StringData(uint_t size){
		set_pvalue(*this, TYPE_STRING, this);
		data_size_ = size<<SIZE_SHIFT;
		buf()[size] = 0;
		XTAL_DEBUG_ONLY(buf_ = buf();)
	}

	~StringData(){}

	uint_t data_size(){
		return data_size_>>SIZE_SHIFT;
	}

	char_t* buf(){ 
		return (char_t*)(this+1); 
	}

	bool is_interned(){
		return (data_size_&INTERNED)!=0;
	}

	void set_interned(){
		data_size_ |= INTERNED;
	}

	static uint_t calc_size(uint_t sz){
		return sizeof(StringData)+(sz+1)*sizeof(char_t);
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
	* \brief 1�̕�������\�z����
	*/
	ID(char_t a);

	/**
	* \brief 2�̕�������\�z����
	*/
	ID(char_t a, char_t b);

	/**
	* \brief 3�̕�������\�z����
	*/
	ID(char_t a, char_t b, char_t c);

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
		:Range(left, right, CLOSED){}

public:

	const StringPtr& left(){ return unchecked_ptr_cast<String>(left_); }

	const StringPtr& right(){ return unchecked_ptr_cast<String>(right_); }

	AnyPtr each();
};

class StringEachIter : public Base{
	StringStreamPtr ss_;

	virtual void visit_members(Visitor& m);

public:

	StringEachIter(const StringPtr& str);

	void block_next(const VMachinePtr& vm);
};

class ChRangeIter : public Base{
public:

	ChRangeIter(const ChRangePtr& range)
		:it_(range->left()), end_(range->right()){}

	void block_next(const VMachinePtr& vm);
private:

	virtual void visit_members(Visitor& m);

	StringPtr it_, end_;
};

/**
* \brief �֐��Ăяo���ŁA���O�t�������Ƃ��ēn�����߂̃N���X
*
*/
struct Named{
	IDPtr name;
	AnyPtr value;

	/**
	* \brief ���O�ƒl���w�肵�č\�z����B
	*/
	Named(const IDPtr& name, const AnyPtr& value)
		:name(name), value(value){}

	/**
	* \brief ��ȏ�ԂŐ�������
	*/
	Named()
		:name(null), value(undefined){}
};

inline void visit_members(Visitor& m, const Named& p){
	m & p.name & p.value;
}

}

#endif // XTAL_STRING_H_INCLUDE_GUARD
