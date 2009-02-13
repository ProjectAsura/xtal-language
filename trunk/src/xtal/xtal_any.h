
#pragma once

namespace xtal{

/**
* @brief any
*
*/
class Any{
public:

	Any(){ type_ = TYPE_NULL; pvalue_ = 0; }
	Any(int_t v){ set_i(v); }
	Any(float_t v){ set_f(v); }
	Any(Base* v){ set_p(v); }
	Any(bool b){ set_b(b); }

	// ��{�^�̐����A���������_������\�z����R���X�g���N�^
	Any(avoid<int>::type v){ set_i((int_t)v); }
	Any(avoid<long>::type v){ set_i((int_t)v); }
	Any(avoid<short>::type v){ set_i((int_t)v); }
	Any(avoid<char>::type v){ set_i((int_t)v); }
	Any(avoid<unsigned int>::type v){ set_i((int_t)v); }
	Any(avoid<unsigned long>::type v){ set_i((int_t)v); }
	Any(avoid<unsigned short>::type v){ set_i((int_t)v); }
	Any(avoid<unsigned char>::type v){ set_i((int_t)v); }
	Any(avoid<signed char>::type v){ set_i((int_t)v); }
	Any(avoid<float>::type v){ set_f((float_t)v); }
	Any(avoid<double>::type v){ set_f((float_t)v); }
	Any(avoid<long double>::type v){ set_f((float_t)v); }
	
	Any(PrimitiveType type){
		type_ = type;
		value_ = 0;
	}

	struct noinit_t{};
	Any(noinit_t){}
	
public:

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

	friend int_t type(const Any& v);
	friend int_t ivalue(const Any& v);
	friend float_t fvalue(const Any& v);
	friend Base* pvalue(const Any& v);
	friend uint_t rawtype(const Any& v);
	friend uint_t rawvalue(const Any& v);
	friend bool raweq(const Any& a, const Any& b);
	friend bool rawne(const Any& a, const Any& b);
	friend bool rawlt(const Any& a, const Any& b);
	friend void swap(Any& a, Any& b);
	friend void set_null_force(Any& v);
	friend void set_undefined_force(Any& v);
	friend void copy_innocence(Any& v, const Any& u);

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
	void rawsend(const VMachinePtr& vm, const IDPtr& primary_key, const AnyPtr& secondary_key, const AnyPtr& self = (const AnyPtr&)null, bool inherited_too = true) const;
	void rawsend(const VMachinePtr& vm, const IDPtr& primary_key) const;

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

	ArrayPtr object_name_list() const;
	
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

	/// @brief primary_key���\�b�h���Ăяo��
	AnyPtr send(const IDPtr& primary_key) const;

	/// @brief primary_key#secondary_key���\�b�h���Ăяo��
	AnyPtr send2(const IDPtr& primary_key, const AnyPtr& secondary_key) const;

	/// @brief �֐����Ăяo��
	AnyPtr call() const;

//{REPEAT{{
/*
	/// @brief primary_key���\�b�h���Ăяo��
	template<class A0 #COMMA_REPEAT#class A`i+1`#>
	AnyPtr send(const IDPtr& primary_key, const A0& a0 #COMMA_REPEAT#const A`i+1`& a`i+1`#) const;

	/// @brief primary_key#secondary_key���\�b�h���Ăяo��
	template<class A0 #COMMA_REPEAT#class A`i+1`#>
	AnyPtr send2(const IDPtr& primary_key, const AnyPtr& secondary_key, const A0& a0 #COMMA_REPEAT#const A`i+1`& a`i+1`#) const;

	/// @brief �֐����Ăяo��
	template<class A0 #COMMA_REPEAT#class A`i+1`#>
	AnyPtr call(const A0& a0 #COMMA_REPEAT#const A`i+1`& a`i+1`#) const;
*/

	/// @brief primary_key���\�b�h���Ăяo��
	template<class A0 >
	AnyPtr send(const IDPtr& primary_key, const A0& a0 ) const;

	/// @brief primary_key#secondary_key���\�b�h���Ăяo��
	template<class A0 >
	AnyPtr send2(const IDPtr& primary_key, const AnyPtr& secondary_key, const A0& a0 ) const;

	/// @brief �֐����Ăяo��
	template<class A0 >
	AnyPtr call(const A0& a0 ) const;

	/// @brief primary_key���\�b�h���Ăяo��
	template<class A0 , class A1>
	AnyPtr send(const IDPtr& primary_key, const A0& a0 , const A1& a1) const;

	/// @brief primary_key#secondary_key���\�b�h���Ăяo��
	template<class A0 , class A1>
	AnyPtr send2(const IDPtr& primary_key, const AnyPtr& secondary_key, const A0& a0 , const A1& a1) const;

	/// @brief �֐����Ăяo��
	template<class A0 , class A1>
	AnyPtr call(const A0& a0 , const A1& a1) const;

	/// @brief primary_key���\�b�h���Ăяo��
	template<class A0 , class A1, class A2>
	AnyPtr send(const IDPtr& primary_key, const A0& a0 , const A1& a1, const A2& a2) const;

	/// @brief primary_key#secondary_key���\�b�h���Ăяo��
	template<class A0 , class A1, class A2>
	AnyPtr send2(const IDPtr& primary_key, const AnyPtr& secondary_key, const A0& a0 , const A1& a1, const A2& a2) const;

	/// @brief �֐����Ăяo��
	template<class A0 , class A1, class A2>
	AnyPtr call(const A0& a0 , const A1& a1, const A2& a2) const;

	/// @brief primary_key���\�b�h���Ăяo��
	template<class A0 , class A1, class A2, class A3>
	AnyPtr send(const IDPtr& primary_key, const A0& a0 , const A1& a1, const A2& a2, const A3& a3) const;

	/// @brief primary_key#secondary_key���\�b�h���Ăяo��
	template<class A0 , class A1, class A2, class A3>
	AnyPtr send2(const IDPtr& primary_key, const AnyPtr& secondary_key, const A0& a0 , const A1& a1, const A2& a2, const A3& a3) const;

	/// @brief �֐����Ăяo��
	template<class A0 , class A1, class A2, class A3>
	AnyPtr call(const A0& a0 , const A1& a1, const A2& a2, const A3& a3) const;

	/// @brief primary_key���\�b�h���Ăяo��
	template<class A0 , class A1, class A2, class A3, class A4>
	AnyPtr send(const IDPtr& primary_key, const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4) const;

	/// @brief primary_key#secondary_key���\�b�h���Ăяo��
	template<class A0 , class A1, class A2, class A3, class A4>
	AnyPtr send2(const IDPtr& primary_key, const AnyPtr& secondary_key, const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4) const;

	/// @brief �֐����Ăяo��
	template<class A0 , class A1, class A2, class A3, class A4>
	AnyPtr call(const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4) const;

	/// @brief primary_key���\�b�h���Ăяo��
	template<class A0 , class A1, class A2, class A3, class A4, class A5>
	AnyPtr send(const IDPtr& primary_key, const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5) const;

	/// @brief primary_key#secondary_key���\�b�h���Ăяo��
	template<class A0 , class A1, class A2, class A3, class A4, class A5>
	AnyPtr send2(const IDPtr& primary_key, const AnyPtr& secondary_key, const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5) const;

	/// @brief �֐����Ăяo��
	template<class A0 , class A1, class A2, class A3, class A4, class A5>
	AnyPtr call(const A0& a0 , const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5) const;

//}}REPEAT}

private:

	// call(VMachinePtr)���R���p�C���G���[�ƂȂ�悤��
	struct cmpitle_error{ cmpitle_error(const VMachinePtr& vm); };
	void call(cmpitle_error) const;

};

inline int_t type(const Any& v){ 
	return v.type_ & TYPE_MASK; 
}

inline int_t ivalue(const Any& v){ 
	XTAL_ASSERT(type(v)==TYPE_INT);
	return v.value_; 
}

inline float_t fvalue(const Any& v){ 
	XTAL_ASSERT(type(v)==TYPE_FLOAT); 
	return *(float_t*)v.fvalue_bytes; 
}

inline Base* pvalue(const Any& v){ 
	XTAL_ASSERT(type(v)==TYPE_BASE || type(v)==TYPE_NULL); 
	return v.pvalue_; 
}

inline uint_t rawtype(const Any& v){
	return (uint_t)(v.type_);
}

inline uint_t rawvalue(const Any& v){
	return (uint_t)(v.value_);
}

inline bool raweq(const Any& a, const Any& b){
	return type(a)==type(b) && a.value_==b.value_;
}

inline bool rawne(const Any& a, const Any& b){
	return !raweq(a, b);
}

inline bool rawlt(const Any& a, const Any& b){
	if(type(a)<type(b))
		return true;
	if(type(b)<type(a))
		return false;
	return a.value_<b.value_;
}

inline void set_null_force(Any& v){
	v.type_ = TYPE_NULL;
	v.value_ = 0;
}

inline void set_undefined_force(Any& v){
	v.type_ = TYPE_UNDEFINED;
	v.value_ = 0;
}

inline void copy_innocence(Any& v, const Any& u){
	v = u;
}

}
