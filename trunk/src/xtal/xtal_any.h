
#pragma once

namespace xtal{

/**
* @brief �C�m�Z���X
*
* ��ʃ��[�U�[�͂���𒼐ڎg�p���邱�Ƃ͖���
*/
class Innocence{
protected:

	Innocence(const char_t* str);
	Innocence(const avoid<char>::type* str);

public:

	Innocence(){ type_ = TYPE_NULL; pvalue_ = 0; }
	Innocence(u8 v){ set_i(v); }
	Innocence(u16 v){ set_i(v); }
	Innocence(i8 v){ set_i(v); }
	Innocence(i16 v){ set_i(v); }
	Innocence(int_t v){ set_i(v); }
	Innocence(float_t v){ set_f(v); }
	Innocence(Base* v){ set_p(v); }
	Innocence(bool b){ set_b(b); }
	Innocence(avoid<int>::type v){ set_i(v); }
	Innocence(avoid<float>::type v){ set_f(v); }
	
	Innocence(PrimitiveType type){
		type_ = type;
		value_ = 0;
	}

	struct noinit_t{};
	Innocence(noinit_t){}
	
protected:

	void set_null(){
		type_ = TYPE_NULL;
		pvalue_ = 0;
	}

	void set_p(Base* p){
		XTAL_ASSERT(p!=0);
		type_ = TYPE_BASE;
		pvalue_ = p;
	}
	
	void set_p(const Base* p){
		XTAL_ASSERT(p!=0);
		type_ = TYPE_BASE;
		pvalue_ = (Base*)p;
	}

	void set_i(int_t v){
		type_ = TYPE_INT;
		value_ = v;
	}

	void set_f(float_t v){
		type_ = TYPE_FLOAT;
		*(float_t*)fvalue_bytes = v;
	}

	void set_b(bool b){
		type_ = TYPE_FALSE + (int)b;
		value_ = 0;
	}

	void set_small_string(){
		type_ = TYPE_SMALL_STRING;
		value_ = 0;
	}

public:

	friend int_t type(const Innocence& v);
	friend int_t ivalue(const Innocence& v);
	friend float_t fvalue(const Innocence& v);
	friend Base* pvalue(const Innocence& v);
	friend uint_t rawvalue(const Innocence& v);
	friend bool raweq(const Innocence& a, const Innocence& b);
	friend bool rawne(const Innocence& a, const Innocence& b);
	friend bool rawlt(const Innocence& a, const Innocence& b);
	friend void swap(Innocence& a, Innocence& b);
	friend void set_null_force(Innocence& v);
	friend void set_undefined_force(Innocence& v);
	friend void copy_innocence(Innocence& v, const Innocence& u);

public:

	enum{
		SMALL_STRING_MAX = sizeof(int_t) / sizeof(char_t)
	};

protected:

	struct SmallString{
		char_t buf[SMALL_STRING_MAX];

		operator char_t*(){
			return buf;
		}
	};

	int_t type_;

	union{
		int_t value_;
		byte_t fvalue_bytes[sizeof(float_t)];
		float_t fvalue_;
		Base* pvalue_;
		SmallString svalue_;
	};
};

inline int_t type(const Innocence& v){ 
	return v.type_ & TYPE_MASK; 
}

inline int_t ivalue(const Innocence& v){ 
	XTAL_ASSERT(type(v)==TYPE_INT);
	return v.value_; 
}

inline float_t fvalue(const Innocence& v){ 
	XTAL_ASSERT(type(v)==TYPE_FLOAT); 
	return *(float_t*)v.fvalue_bytes; 
}

inline Base* pvalue(const Innocence& v){ 
	XTAL_ASSERT(type(v)==TYPE_BASE || type(v)==TYPE_NULL); 
	return v.pvalue_; 
}

inline uint_t rawvalue(const Innocence& v){
	return (uint_t)(v.value_);
}

inline bool raweq(const Innocence& a, const Innocence& b){
	return type(a)==type(b) && a.value_==b.value_;
}

inline bool rawne(const Innocence& a, const Innocence& b){
	return !raweq(a, b);
}

inline bool rawlt(const Innocence& a, const Innocence& b){
	if(type(a)<type(b))
		return true;
	if(type(b)<type(a))
		return false;
	return a.value_<b.value_;
}

inline void set_null_force(Innocence& v){
	v.type_ = TYPE_NULL;
	v.value_ = 0;
}

inline void set_undefined_force(Innocence& v){
	v.type_ = TYPE_UNDEFINED;
	v.value_ = 0;
}

inline void copy_innocence(Innocence& v, const Innocence& u){
	v = u;
}

/**
* @brief any
*
*/
class Any : public Innocence{
protected:

	// ���� Any����邱�Ƃ͏o���Ȃ�

	Any(){}
		
	Any(noinit_t n):Innocence(n){}

	Any(const Any& v):Innocence(v){}
	
	~Any(){}

public:

	/**
	* @brief �֐��I�u�W�F�N�g�Ƃ݂Ȃ��A�֐��Ăяo��������B
	*
	* ������߂�l��vm��ʂ��Ă���肷��B
	*/
	void rawcall(const VMachinePtr& vm) const;
	
	/**
	* @brief name���\�b�h�Ăяo��������
	*
	* ������߂�l��vm��ʂ��Ă���肷��B
	*/
	void rawsend(const VMachinePtr& vm, const IDPtr& primary_key, const AnyPtr& secondary_key = (const AnyPtr&)null, const AnyPtr& self = (const AnyPtr&)null, bool inherited_too = true) const;

	/**
	* @brief name�����o���擾����B
	* �G�����l�����������o�擾
	*
	* @retval undefined ���̃����o�͑��݂��Ȃ�
	* @retval ��undefined name�ɑΉ����������o  
	*/
	const AnyPtr& member(const IDPtr& primary_key, const AnyPtr& secondary_key = (const AnyPtr&)null, const AnyPtr& self = (const AnyPtr&)null, bool inherited_too = true) const;

	/**
	* @brief name�����o�������lvalue�Œ�`����B
	*
	*/
	void def(const IDPtr& primary_key, const AnyPtr& value, const AnyPtr& secondary_key = (const AnyPtr&)null, int_t accessibility = 0) const;

	/**
	* @brief ���̃I�u�W�F�N�g����������N���X��Ԃ��B
	*
	*/
	const ClassPtr& get_class() const;

	/**
	* @brief �����ɕϊ����ĕԂ��B
	*
	*/
	int_t to_i() const;
	
	/**
	* @brief ���������_���ɕϊ����ĕԂ��B
	*
	*/
	float_t to_f() const;
	
	/**
	* @brief ������ɕϊ����ĕԂ��B
	*
	*/
	StringPtr to_s() const;

	/**
	* @brief �z��ɕϊ����ĕԂ��B
	*
	*/
	ArrayPtr to_a() const;

	/**
	* @brief �A�z�z��ɕϊ����ĕԂ��B
	*
	*/
	MapPtr to_m() const;
	
	/**
	* @brief ���̃I�u�W�F�N�g�ɕt����ꂽ���O��Ԃ��B
	*
	*/
	StringPtr object_name(int_t depth = -1) const;

	/**
	* @brief klass�N���X�̃C���X�^���X�����ׂ�B
	*
	*/
	bool is(const AnyPtr& klass) const;
		
	/**
	* @brief klass�N���X���p�����Ă��邩���ׂ�
	*
	*/
	bool is_inherited(const AnyPtr& klass) const;

	/**
	* @brief ���̃I�u�W�F�N�g�ɕt����ꂽ���O�̋�����Ԃ��B
	*
	*/
	int_t object_name_force() const;
	
	/**
	* @brief ���̃I�u�W�F�N�g�ɖ��O������B
	*
	* ���O�����ĂȂ��I�u�W�F�N�g��A�O�ɕt����ꂽ���O�̕��������ꍇ���������B
	* @param name ���閼�O
	* @param force ���O�̋���
	* @param parent �e
	*/
	void set_object_name(const StringPtr& name, int_t force, const AnyPtr& parent) const;

	/**
	* @brief �n�b�V���l��Ԃ�
	*
	*/
	uint_t hashcode() const;

	/**
	* @brief ���g�𕶎��񉻂���println����B
	* @return ���g��Ԃ��B
	*/
	AnyPtr p() const;


	AnyPtr s_save() const;

	void s_load(const AnyPtr& v) const;

	AnyPtr serial_save(const ClassPtr& cls) const;

	void serial_load(const ClassPtr& cls, const AnyPtr& v) const;

	/**
	* @brief ���g��Ԃ��B
	*
	*/
	const AnyPtr& self() const{
		return (const AnyPtr&)*this;
	}

	MultiValuePtr to_mv() const;

	MultiValuePtr flatten_mv() const;

	MultiValuePtr flatten_all_mv() const;
	
public:

	/**
	* @brief primary_key���\�b�h���Ăяo��
	*/
	AnyPtr send(const IDPtr& primary_key) const;
	AnyPtr send(const IDPtr& primary_key, const Param& a0) const;
	AnyPtr send(const IDPtr& primary_key, const Param& a0, const Param& a1) const;
	AnyPtr send(const IDPtr& primary_key, const Param& a0, const Param& a1, const Param& a2) const;
	AnyPtr send(const IDPtr& primary_key, const Param& a0, const Param& a1, const Param& a2, const Param& a3) const;
	AnyPtr send(const IDPtr& primary_key, const Param& a0, const Param& a1, const Param& a2, const Param& a3, const Param& a4) const;
	
public:

	AnyPtr send2(const IDPtr& primary_key, const AnyPtr& secondary_key) const;	
	AnyPtr send2(const IDPtr& primary_key, const AnyPtr& secondary_key, const Param& a0) const;
	AnyPtr send2(const IDPtr& primary_key, const AnyPtr& secondary_key, const Param& a0, const Param& a1) const;
	AnyPtr send2(const IDPtr& primary_key, const AnyPtr& secondary_key, const Param& a0, const Param& a1, const Param& a2) const;
	AnyPtr send2(const IDPtr& primary_key, const AnyPtr& secondary_key, const Param& a0, const Param& a1, const Param& a2, const Param& a3) const;
	AnyPtr send2(const IDPtr& primary_key, const AnyPtr& secondary_key, const Param& a0, const Param& a1, const Param& a2, const Param& a3, const Param& a4) const;
	
public:

	AnyPtr call() const;
	AnyPtr call(const Param& a0) const;
	AnyPtr call(const Param& a0, const Param& a1) const;
	AnyPtr call(const Param& a0, const Param& a1, const Param& a2) const;
	AnyPtr call(const Param& a0, const Param& a1, const Param& a2, const Param& a3) const;
	AnyPtr call(const Param& a0, const Param& a1, const Param& a2, const Param& a3, const Param& a4) const;

private:

	// call(VMachinePtr)���R���p�C���G���[�ƂȂ�悤��
	struct aaa{ aaa(const VMachinePtr& vm); };
	void call(aaa) const;

};

AnyPtr operator +(const AnyPtr& a);
AnyPtr operator -(const AnyPtr& a);
AnyPtr operator ~(const AnyPtr& a);

AnyPtr operator +(const AnyPtr& a, const AnyPtr& b);
AnyPtr operator -(const AnyPtr& a, const AnyPtr& b);
AnyPtr operator *(const AnyPtr& a, const AnyPtr& b);
AnyPtr operator /(const AnyPtr& a, const AnyPtr& b);
AnyPtr operator %(const AnyPtr& a, const AnyPtr& b);
AnyPtr operator |(const AnyPtr& a, const AnyPtr& b);
AnyPtr operator &(const AnyPtr& a, const AnyPtr& b);
AnyPtr operator ^(const AnyPtr& a, const AnyPtr& b);
AnyPtr operator >>(const AnyPtr& a, const AnyPtr& b);
AnyPtr operator <<(const AnyPtr& a, const AnyPtr& b);

bool operator ==(const AnyPtr& a, const AnyPtr& b);
bool operator !=(const AnyPtr& a, const AnyPtr& b);
bool operator <(const AnyPtr& a, const AnyPtr& b);
bool operator >=(const AnyPtr& a, const AnyPtr& b);
bool operator >(const AnyPtr& a, const AnyPtr& b);
bool operator <=(const AnyPtr& a, const AnyPtr& b);

AnyPtr& operator +=(AnyPtr& a, const AnyPtr& b);
AnyPtr& operator -=(AnyPtr& a, const AnyPtr& b);
AnyPtr& operator *=(AnyPtr& a, const AnyPtr& b);
AnyPtr& operator /=(AnyPtr& a, const AnyPtr& b);
AnyPtr& operator %=(AnyPtr& a, const AnyPtr& b);
AnyPtr& operator |=(AnyPtr& a, const AnyPtr& b);
AnyPtr& operator &=(AnyPtr& a, const AnyPtr& b);
AnyPtr& operator ^=(AnyPtr& a, const AnyPtr& b);
AnyPtr& operator >>=(AnyPtr& a, const AnyPtr& b);
AnyPtr& operator <<=(AnyPtr& a, const AnyPtr& b);

}
