
#pragma once

#include "fwd.h"
#include "utility.h"

namespace xtal{


#ifdef XTAL_USE_COMPRESSED_ANY

/**
* @brief �Q�ƃJ�E���g�����Ȃ�Any
*
* ��ʃ��[�U�[�͂���𒼐ڎg�p���邱�Ƃ͖���
*/
class UncountedAny{
public:

	UncountedAny(){ value_ = TYPE_NULL; }
	UncountedAny(int_t v){ set_i(v); }
	UncountedAny(float_t v){ set_f(v); }
	UncountedAny(AnyImpl* v){ set_p(v); }
	UncountedAny(bool b){ set_b(b); }
	UncountedAny(check_xtype<int>::type v){ set_i(v); }
	UncountedAny(check_xtype<float>::type v){ set_f(v); }
	UncountedAny(PrimitiveType type){ value_ = type; }
	
	struct noinit_t{};
	UncountedAny(noinit_t){}

protected:

	void set_null(){
		value_ = TYPE_NULL;
	}

	void set_p(AnyImpl* p){
		XTAL_ASSERT(p!=0);
		union{
			int_t value;
			AnyImpl* pvalue;
		} u;
		u.pvalue = p;
		u.value |= TYPE_BASE;
		value_ = u.value;
	}
	
	void set_p(const AnyImpl* p){
		set_p((AnyImpl*)p);
	}

	void set_i(int_t v){
		value_ = (v<<TYPE_SHIFT) | TYPE_INT;
	}

	void set_f(float_t v){
		union{
			int_t value;
			float_t fvalue;
		} u;
		u.fvalue = v;
		u.value = (u.value & ~TYPE_MASK) | TYPE_FLOAT;
		value_ = u.value;
	}

	void set_b(bool b){
		value_ = TYPE_FALSE + (int)b;
	}

public:

	const Any& cref() const{
		return (const Any&)*this;
	}

	int_t type() const{
		return value_ & TYPE_MASK; 
	}
	
	int_t ivalue() const{ 
		XTAL_ASSERT(type()==TYPE_INT);
		return value_ >> TYPE_SHIFT; 
	}
	
	float_t fvalue() const{ 
		XTAL_ASSERT(type()==TYPE_FLOAT);
		union{
			int_t value;
			float_t fvalue;
		} u;
		u.value = (value_ & ~TYPE_MASK);
		return u.fvalue;
	}
	
	AnyImpl* impl() const{
		XTAL_ASSERT(type()==TYPE_BASE || type()==TYPE_NULL);
		union{
			int_t value;
			AnyImpl* pvalue;
		} u;
		u.value = (value_ & ~TYPE_MASK);
		return u.pvalue; 
	}

	int_t rawvalue() const{
		return value_;
	}

public:

	bool raweq(const UncountedAny& a) const{
		return value_==a.value_;
	}

	bool rawne(const UncountedAny& a) const{
		return !raweq(a);
	}
	
	bool rawlt(const UncountedAny& a) const{
		return value_<a.value_;
	}

	void swap(UncountedAny& a){
		std::swap(value_, a.value_);
	}

private:

	union{
		int_t value_;
		float_t fvalue_;
		AnyImpl* pvalue_;
	};
	
};
	
#else
	
/**
* @brief �Q�ƃJ�E���g�����Ȃ�Any
*
* ��ʃ��[�U�[�͂���𒼐ڎg�p���邱�Ƃ͖���
*/
class UncountedAny{
public:

	UncountedAny(){ type_ = TYPE_NULL; pvalue_ = 0; }
	UncountedAny(int_t v){ set_i(v); }
	UncountedAny(float_t v){ set_f(v); }
	UncountedAny(AnyImpl* v){ set_p(v); }
	UncountedAny(bool b){ set_b(b); }
	UncountedAny(check_xtype<int>::type v){ set_i(v); }
	UncountedAny(check_xtype<float>::type v){ set_f(v); }
	
	UncountedAny(PrimitiveType type){
		type_ = type;
		value_ = 0;
	}

	struct noinit_t{};
	UncountedAny(noinit_t){}
	
protected:

	void set_null(){
		type_ = TYPE_NULL;
		pvalue_ = 0;
	}

	void set_p(AnyImpl* p){
		XTAL_ASSERT(p!=0);
		type_ = TYPE_BASE;
		pvalue_ = p;
	}
	
	void set_p(const AnyImpl* p){
		XTAL_ASSERT(p!=0);
		type_ = TYPE_BASE;
		pvalue_ = (AnyImpl*)p;
	}

	void set_i(int_t v){
		type_ = TYPE_INT;
		value_ = v;
	}

	void set_f(float_t v){
		type_ = TYPE_FLOAT;
		fvalue_ = v;
	}

	void set_b(bool b){
		type_ = TYPE_FALSE + (int)b;
		value_ = 0;
	}

public:

	const Any& cref() const{
		return (const Any&)*this;
	}

	int_t type() const{ 
		return type_; 
	}
	
	int_t ivalue() const{ 
		XTAL_ASSERT(type()==TYPE_INT);
		return value_; 
	}
	
	float_t fvalue() const{ 
		XTAL_ASSERT(type()==TYPE_FLOAT); 
		return fvalue_; 
	}
	
	AnyImpl* impl() const { 
		XTAL_ASSERT(type()==TYPE_BASE || type()==TYPE_NULL); 
		return pvalue_; 
	}

	uint_t rawvalue() const{
		return (uint_t)value_;
	}
	
public:

	bool raweq(const UncountedAny& a) const{
		return type_==a.type_ && value_==a.value_;
	}

	bool rawne(const UncountedAny& a) const{
		return !raweq(a);
	}
	
	bool rawlt(const UncountedAny& a) const{
		if(type_<a.type_)
			return true;
		if(a.type_<type_)
			return false;
		return value_<a.value_;
	}

	void swap(UncountedAny& a){
		std::swap(type_, a.type_);
		std::swap(value_, a.value_);
	}

private:

	int_t type_;
	
	union{
		int_t value_;
		float_t fvalue_;
		AnyImpl* pvalue_;
	};
	
};
	
#endif
	
/**
* @brief Xtal�̒l��ێ����邽�߂̌^
*
*/
class Any : public UncountedAny{	
public:

	/**
	* @brief �f�t�H���g�R���X�g���N�^�Bnull���i�[�����B
	*
	*/
	Any(){ set_null(); }
	
	/**
	* @brief �����l����\�z����R���X�g���N�^�B
	*
	*/
	Any(int_t v){ set_i(v); }
	
	/**
	* @brief ���������_���l����\�z����R���X�g���N�^�B
	*
	*/
	Any(float_t v){ set_f(v); }
	
	/**
	* @brief �����񂩂�\�z����R���X�g���N�^�B
	*
	*/
	Any(bool b){ set_b(b); }

	/**
	* @brief �����񂩂�\�z����R���X�g���N�^�B
	*
	*/
	Any(const char* str);

	// ��{�^�̐����A���������_������\�z����R���X�g���N�^
	Any(check_xtype<int>::type v){ set_i((int_t)v); }
	Any(check_xtype<long>::type v){ set_i((int_t)v); }
	Any(check_xtype<short>::type v){ set_i((int_t)v); }
	Any(check_xtype<char>::type v){ set_i((int_t)v); }
	Any(check_xtype<unsigned int>::type v){ set_i((int_t)v); }
	Any(check_xtype<unsigned long>::type v){ set_i((int_t)v); }
	Any(check_xtype<unsigned short>::type v){ set_i((int_t)v); }
	Any(check_xtype<unsigned char>::type v){ set_i((int_t)v); }
	Any(check_xtype<signed char>::type v){ set_i((int_t)v); }
	Any(check_xtype<float>::type v){ set_f((float_t)v); }
	Any(check_xtype<double>::type v){ set_f((float_t)v); }
	Any(check_xtype<long double>::type v){ set_f((float_t)v); }
	
public:

	Any(AnyImpl* v);
	
	Any(const AnyImpl* v);

	Any(const Any& v){
		UncountedAny::operator =(v);
		inc_ref_count();
	}

	Any& operator =(const Any& v);

	Any& operator =(AnyImpl* v);
	
	Any& operator =(const AnyImpl* v);

	Any& operator =(int_t v);
	
	Any& operator =(float_t v);

	Any& operator =(bool v);

	Any& operator =(const Null&);

	~Any(){ 
		dec_ref_count();
	}
	
private:

	// AnyImpl���p�����Ă��Ȃ��|�C���^�^���n���ꂽ�Ƃ��A
	// Any(bool)���g����̂�j�~���邽�߂̃R���X�g���N�^
	// �����͖����B
	Any(void*);

public:
	
	/**
	* @brief �v���~�e�B�u�Ȍ^�ԍ���p����Any���\�z����B
	*
	* ��ʃ��[�U�[�͂�����Q�Ƃ���K�v�͂قƂ�ǂȂ��B
	*/
	Any(PrimitiveType type):UncountedAny(type){}

	/**
	* @brief �v���~�e�B�u�Ȍ^�ԍ���Ԃ��B
	*
	* ��ʃ��[�U�[�͂�����Q�Ƃ���K�v�͂قƂ�ǂȂ��B
	*/
	int_t type() const{ return UncountedAny::type(); }
	
	/**
	* @brief �v���~�e�B�u�Ȑ����l��Ԃ��B
	*
	* ��ʃ��[�U�[�͂�����Ato_i()���g�������悢�B
	*/
	int_t ivalue() const{ return UncountedAny::ivalue(); }
	
	/**
	* @brief �v���~�e�B�u�ȕ��������_���l��Ԃ��B
	*
	* ��ʃ��[�U�[�͂�����Ato_f()���g�������悢�B
	*/
	float_t fvalue() const{ return UncountedAny::fvalue(); }
	
	/**
	* @brief �v���~�e�B�u�ȃI�u�W�F�N�g�̃|�C���^�l��Ԃ��B
	*
	* ��ʃ��[�U�[�͂�����Q�Ƃ���K�v�͂قƂ�ǂȂ��B
	*/
	AnyImpl* impl() const{ return UncountedAny::impl(); }
	
public:
	
	/**
	* @brief �֐��I�u�W�F�N�g�Ƃ݂Ȃ��A�֐��Ăяo��������B
	*
	* ������߂�l��vm��ʂ��Ă���肷��B
	*/
	void call(const VMachine& vm) const;
	
	/**
	* @brief name���\�b�h�Ăяo��������
	*
	* ������߂�l��vm��ʂ��Ă���肷��B
	*/
	void send(const ID& name, const VMachine& vm) const;

	/**
	* @brief name�����o���擾����B
	*
	* @retval null ���̃����o�[�͑��݂��Ȃ�
	* @retval ��null name�ɑΉ����������o  
	*/
	const Any& member(const ID& name) const;
	
	/**
	* @brief name�����o�������lvalue�Œ�`����B
	*
	*/
	void def(const ID& name, const Any& value) const;

	/**
	* @brief ���̃I�u�W�F�N�g����������N���X��Ԃ��B
	*
	*/
	const Class& get_class() const;

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
	String to_s() const;
	
	/**
	* @brief �^�U�l�ɕϊ����ĕԂ��B
	*
	*/
	bool to_b() const{
		return type()>TYPE_FALSE;
	}
	
	/**
	* @brief ���̃I�u�W�F�N�g�ɕt����ꂽ���O��Ԃ��B
	*
	*/
	String object_name() const;

	/**
	* @brief cls�N���X�̃C���X�^���X�����ׂ�B
	*
	*/
	bool is(const Any& cls) const;
		
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
	void set_object_name(const String& name, int_t force, const Any& parent) const;

	/**
	* @brief �n�b�V���l��Ԃ�
	*
	*/
	uint_t hashcode() const;

	/**
	* @brief ���g�𕶎��񉻂���println����B
	* @return ���g��Ԃ��B
	*/
	Any p() const;
	
	/**
	* @brief ���g��null���Ԃ�
	*/ 
	bool is_null() const{ return type()==TYPE_NULL; }

public:

	// �֐��Ăяo���B5�܂ł̈������󂯎��o�[�W��������`����Ă���B
	Any operator()() const;
	Any operator()(const Any& a0) const;
	Any operator()(const Any& a0, const Any& a1) const;
	Any operator()(const Any& a0, const Any& a1, const Any& a2) const;
	Any operator()(const Any& a0, const Any& a1, const Any& a2, const Any& a3) const;
	Any operator()(const Any& a0, const Any& a1, const Any& a2, const Any& a3, const Any& a4) const;
	Any operator()(const Named& a0) const;
	Any operator()(const Any& a0, const Named& a1) const;
	Any operator()(const Any& a0, const Any& a1, const Named& a2) const;
	Any operator()(const Any& a0, const Any& a1, const Any& a2, const Named& a3) const;
	Any operator()(const Any& a0, const Any& a1, const Any& a2, const Any& a3, const Named& a4) const;
	Any operator()(const Named& a0, const Named& a1) const;
	Any operator()(const Any& a0, const Named& a1, const Named& a2) const;
	Any operator()(const Any& a0, const Any& a1, const Named& a2, const Named& a3) const;
	Any operator()(const Any& a0, const Any& a1, const Any& a2, const Named& a3, const Named& a4) const;
	Any operator()(const Named& a0, const Named& a1, const Named& a2) const;
	Any operator()(const Any& a0, const Named& a1, const Named& a2, const Named& a3) const;
	Any operator()(const Any& a0, const Any& a1, const Named& a2, const Named& a3, const Named& a4) const;
	Any operator()(const Named& a0, const Named& a1, const Named& a2, const Named& a3) const;
	Any operator()(const Any& a0, const Named& a1, const Named& a2, const Named& a3, const Named& a4) const;
	Any operator()(const Named& a0, const Named& a1, const Named& a2, const Named& a3, const Named& a4) const;

	// ���\�b�h�Ăяo���B5�܂ł̈������󂯎��o�[�W��������`����Ă���B
	Any send(const ID& name) const;
	Any send(const ID& name, const Any& a0) const;
	Any send(const ID& name, const Any& a0, const Any& a1) const;
	Any send(const ID& name, const Any& a0, const Any& a1, const Any& a2) const;
	Any send(const ID& name, const Any& a0, const Any& a1, const Any& a2, const Any& a3) const;
	Any send(const ID& name, const Any& a0, const Any& a1, const Any& a2, const Any& a3, const Any& a4) const;
	Any send(const ID& name, const Named& a0) const;
	Any send(const ID& name, const Any& a0, const Named& a1) const;
	Any send(const ID& name, const Any& a0, const Any& a1, const Named& a2) const;
	Any send(const ID& name, const Any& a0, const Any& a1, const Any& a2, const Named& a3) const;
	Any send(const ID& name, const Any& a0, const Any& a1, const Any& a2, const Any& a3, const Named& a4) const;
	Any send(const ID& name, const Named& a0, const Named& a1) const;
	Any send(const ID& name, const Any& a0, const Named& a1, const Named& a2) const;
	Any send(const ID& name, const Any& a0, const Any& a1, const Named& a2, const Named& a3) const;
	Any send(const ID& name, const Any& a0, const Any& a1, const Any& a2, const Named& a3, const Named& a4) const;
	Any send(const ID& name, const Named& a0, const Named& a1, const Named& a2) const;
	Any send(const ID& name, const Any& a0, const Named& a1, const Named& a2, const Named& a3) const;
	Any send(const ID& name, const Any& a0, const Any& a1, const Named& a2, const Named& a3, const Named& a4) const;
	Any send(const ID& name, const Named& a0, const Named& a1, const Named& a2, const Named& a3) const;
	Any send(const ID& name, const Any& a0, const Named& a1, const Named& a2, const Named& a3, const Named& a4) const;
	Any send(const ID& name, const Named& a0, const Named& a1, const Named& a2, const Named& a3, const Named& a4) const;

public:

	/**
	* @brief �A������
	*
	* send("op_cat", v)�Ɠ�����
	*/
	Any cat(const Any& v) const;

	/**
	* @brief �z��̗v�f��Ԃ�
	*
	* send("op_at", index)�Ɠ�����
	*/	
	const Any at(const Any& index) const;
	
	/**
	* @brief �z��̗v�f��ݒ肷��
	*
	* send("op_set_at", index, value)�Ɠ�����
	*/	
	void set_at(const Any& index, const Any& value) const;
		
	/**
	* @brief �z��̒������擾����
	*
	* send("size").to_i()�Ɠ�����
	*/
	int_t size() const;

	/**
	* @brief �z��̗v�f��Ԃ�
	*
	* send("op_at", index)�Ɠ�����
	*/
	const Any operator[](const Any& index) const;

	/**
	* @brief ����̃I�u�W�F�N�g�����ׂ�
	*
	*/
	bool raweq(const Any& a) const{ return UncountedAny::raweq(a); }

	/**
	* @brief ����̃I�u�W�F�N�g�ł͂Ȃ������ׂ�
	*
	*/
	bool rawne(const Any& a) const{ return UncountedAny::rawne(a); }
	
	/**
	* @brief �I�u�W�F�N�g�̃A�h���X���ł�菬���������߂�
	*
	*/
	bool rawlt(const Any& a) const{ return UncountedAny::rawlt(a); }

protected:

	void inc_ref_count() const;

	void dec_ref_count() const;	

	const Any& cref() const{
		return (const Any&)*this;
	}

private:

	struct dummy_bool_tag{ void safe_true(dummy_bool_tag){} };
	typedef void (dummy_bool_tag::*safe_bool)(dummy_bool_tag);

public:
	
	/**
	* @brief bool�^�Ɏ����ϊ�����B
	*
	*/
	operator safe_bool() const{
		return to_b() ? &dummy_bool_tag::safe_true : (safe_bool)0;
	}
};

/**
* @brief ����
*
* a.send("op_add", b)�Ɠ�����
*/	
Any operator +(const Any& a, const Any& b);

/**
* @brief ����
*
* a.send("op_sub", b)�Ɠ�����
*/	
Any operator -(const Any& a, const Any& b);

/**
* @brief �|����
*
* a.send("op_mul", b)�Ɠ�����
*/	
Any operator *(const Any& a, const Any& b);

/**
* @brief ����
*
* a.send("op_div", b)�Ɠ�����
*/	
Any operator /(const Any& a, const Any& b);

/**
* @brief �]������߂�
*
* a.send("op_mod", b)�Ɠ�����
*/	
Any operator %(const Any& a, const Any& b);

/**
* @brief bitwise OR
*
* a.send("op_or", b)�Ɠ�����
*/	
Any operator |(const Any& a, const Any& b);

/**
* @brief bitwise AND
*
* a.send("op_and", b)�Ɠ�����
*/	
Any operator &(const Any& a, const Any& b);

/**
* @brief bitwise XOR
* a.send("op_xor", b)�Ɠ�����
*/	
Any operator ^(const Any& a, const Any& b);

/**
* @brief �E�V�t�g
*
* a.send("op_shr", b)�Ɠ�����
*/	
Any operator >>(const Any& a, const Any& b);

/**
* @brief ���V�t�g
*
* a.send("op_shl", b)�Ɠ�����
*/	
Any operator <<(const Any& a, const Any& b);

/**
* @brief ��������
*
* a.send("op_eq", b)�Ɠ�����
*/	
Any operator ==(const Any& a, const Any& b);

/**
* @brief �������Ȃ���
*
* !a.send("op_eq", b)�Ɠ�����
*/	
Any operator !=(const Any& a, const Any& b);

/**
* @brief ��菬������
*
* a.send("op_lt", b)�Ɠ�����
*/	
Any operator <(const Any& a, const Any& b);

/**
* @brief ���傫����
*
* b.send("op_lt", a)�Ɠ�����
*/	
Any operator >(const Any& a, const Any& b);

/**
* @brief �ȏォ
*
* !b.send("op_lt", a)�Ɠ�����
*/	
Any operator <=(const Any& a, const Any& b);

/**
* @brief �ȉ���
* !a.send("op_lt", b)�Ɠ�����
*/	
Any operator >=(const Any& a, const Any& b);

/**
* @brief �������킹��
*
* a = a.send("op_add_assign", b)�Ɠ�����
*/	
Any& operator +=(Any& a, const Any& b);

/**
* @brief �������킹��
*
* a = a.send("op_sub_assign", b)�Ɠ�����
*/	
Any& operator -=(Any& a, const Any& b);

/**
* @brief �|�����킹��
*
* a = a.send("op_mod_assign", b)�Ɠ�����
*/	
Any& operator *=(Any& a, const Any& b);

/**
* @brief ���荇�킹��
*
* a = a.send("op_div_assign", b)�Ɠ�����
*/	
Any& operator /=(Any& a, const Any& b);

/**
* @brief �]������ߍ��킹��
*
* a = a.send("op_mod_assign", b)�Ɠ�����
*/	
Any& operator %=(Any& a, const Any& b);

/**
* @brief bitwise OR���đ������
*
* a = a.send("op_or_assign", b)�Ɠ�����
*/	
Any& operator |=(Any& a, const Any& b);

/**
* @brief bitwise AND���đ������
*
* a = a.send("op_and_assign", b)�Ɠ�����
*/	
Any& operator &=(Any& a, const Any& b);

/**
* @brief bitwise XOR���đ������
*
* a = a.send("op_xor_assign", b)�Ɠ�����
*/	
Any& operator ^=(Any& a, const Any& b);

/**
* @brief �E�V�t�g���đ������
*
* a = a.send("op_shr_assign", b)�Ɠ�����
*/	
Any& operator >>=(Any& a, const Any& b);

/**
* @brief ���V�t�g���đ������
*
* a = a.send("op_shl_assign", b)�Ɠ�����
*/	
Any& operator <<=(Any& a, const Any& b);


// Any�̎���
class AnyImpl{
public:
	
	AnyImpl()
		:class_(UncountedAny::noinit_t()){}

	AnyImpl(const AnyImpl& b)
		:class_(b.class_){}

	virtual ~AnyImpl(){}
	
public:

	struct noinit_t{};
	AnyImpl(noinit_t)
		:class_(UncountedAny::noinit_t()){}
		
public:
	
	static void* operator new(size_t size);
	static void operator delete(void* p, size_t size);
	
	static void* operator new(size_t size, Any& guard);
	static void operator delete(void* p, Any& guard);

	static void* operator new(size_t, void* p){ return p; }
	static void operator delete(void*, void*){}

public:

	uint_t ref_count(){ return ref_count_; }
	void add_ref_count(int_t rc){ ref_count_+=rc; }
	void inc_ref_count(){ ++ref_count_; }
	void dec_ref_count(){ --ref_count_; }
	void set_ref_count(uint_t rc){ ref_count_ = rc; }
	const Class& get_class(){ return *(const Class*)&class_; }
	void set_class(const Class& c);
	
public:

	virtual void visit_members(Visitor& m);
	virtual void call(const VMachine& vm);
	virtual const Any& member(const ID& name);
	virtual void def(const ID& name, const Any& value);
	virtual HaveInstanceVariables* have_instance_variables();
	virtual String object_name();
	virtual int_t object_name_force();
	virtual void set_object_name(const String& name, int_t force, const Any& parent);
	virtual uint_t hashcode();

private:

	uint_t ref_count_;
	UncountedAny class_;
	
private:

	friend void gc();
	friend void full_gc();
};


class Null : public Any{};
class Nop : public Any{ public: Nop():Any(TYPE_NOP){} };
class True : public Any{ public: True():Any(TYPE_TRUE){} };
class False : public Any{ public: False():Any(TYPE_FALSE){} };

inline bool operator ==(const Any& a, const Null&){ return !a; }
inline bool operator !=(const Any& a, const Null&){ return a; }
inline bool operator ==(const Null&, const Any& a){ return !a; }
inline bool operator !=(const Null&, const Any& a){ return a; }

inline void Any::inc_ref_count() const{
	if(type()==TYPE_BASE){ impl()->inc_ref_count(); }
}

inline void Any::dec_ref_count() const{
	if(type()==TYPE_BASE){ impl()->dec_ref_count(); }
}

}
