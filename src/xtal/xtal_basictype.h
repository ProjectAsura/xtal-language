/** \file src/xtal/xtal_basictype.h
* \brief src/xtal/xtal_basictype.h
*/

#ifndef XTAL_BASICTYPE_H_INCLUDE_GUARD
#define XTAL_BASICTYPE_H_INCLUDE_GUARD

#pragma once

namespace xtal{

/**
* \xbind lib::builtin
* \brief �k���l
*/
class Null : public Any{
public:
	Null():Any(TYPE_NULL){} 
};

/**
* \xbind lib::builtin
* \brief ����`�l
*/
class Undefined : public Any{ 
public: 
	Undefined():Any(TYPE_UNDEFINED){} 
};

/**
* \xbind lib::builtin
* \brief �����l
*/
class Int : public Any{
public:

	Int(int_t val = 0)
		:Any(val){}

public:
	
	int_t to_i(){
		return ivalue(*this);
	}

	float_t to_f(){
		return (float_t)ivalue(*this);
	}

	StringPtr to_s(){
		return Any::to_s();
	}

	bool op_in(const IntRangePtr& range);

	bool op_in(const FloatRangePtr& range);

	IntRangePtr op_range(int_t right, int_t kind);

	FloatRangePtr op_range(float_t right, int_t kind);
};

/**
* \xbind lib::builtin
* \brief ���������_�l
*/
class Float : public Any{
public:

	Float(float_t val = 0)
		:Any(val){}

public:

	int_t to_i(){
		return (int_t)fvalue(*this);
	}

	float_t to_f(){
		return fvalue(*this);
	}

	StringPtr to_s(){
		return Any::to_s();
	}

	bool op_in(const IntRangePtr& range);

	bool op_in(const FloatRangePtr& range);

	FloatRangePtr op_range(int_t right, int_t kind);

	FloatRangePtr op_range(float_t right, int_t kind);
};

/**
* \xbind lib::builtin
* \brief �^�U�l
*/
class Bool : public Any{
public: 
	Bool(bool b):Any(b){} 
};

/**
* \xbind lib::builtin
* \brief ���
*/
class Range : public Base{
public:

	Range(const AnyPtr& left, const AnyPtr& right, int_t kind = RANGE_CLOSED)
		:left_(left), right_(right), kind_(kind){}

	/**
	* \xbind
	* \breif ��Ԃ̍��̗v�f��Ԃ�
	*/
	const AnyPtr& left(){ return left_; }

	/**
	* \xbind
	* \breif ��Ԃ̉E�̗v�f��Ԃ�
	*/
	const AnyPtr& right(){ return right_; }

	/**
	* \xbind
	* \breif ��Ԃ̎�ނ�Ԃ�
	*/
	int_t kind(){ return kind_; }

	/**
	* \xbind
	* \breif ����������Ԃ��Ԃ�
	*/
	bool is_left_closed(){ return (kind_&(1<<1))==0; }

	/**
	* \xbind
	* \breif �E��������Ԃ��Ԃ�
	*/
	bool is_right_closed(){ return (kind_&(1<<0))==0; }

protected:

	virtual void visit_members(Visitor& m){
		Base::visit_members(m);
		m & left_ & right_;
	}

	AnyPtr left_;
	AnyPtr right_;
	int_t kind_;
};

/**
* \xbind lib::builtin
* \brief ���
*/
class IntRange : public Range{
public:

	IntRange(int_t left, int_t right, int_t kind = RANGE_CLOSED)
		:Range(left, right, kind){}

public:

	/**
	* \xbind
	* \brief �͈͂̊J�n��Ԃ�
	*
	* begin�͍��E�J��� [begin, end) �œ��邱�Ƃ��o���� 
	*/
	int_t begin(){ return is_left_closed() ? left() : left()+1; }

	/**
	* \xbind
	* \brief �͈͂̏I�[��Ԃ�
	*
	* end�͍��E�J��� [begin, end) �œ��邱�Ƃ��o���� 
	*/
	int_t end(){ return is_right_closed() ? right()+1 : right(); }

	/**
	* \xbind
	* \breif ��Ԃ̍��̗v�f��Ԃ�
	*/
	int_t left(){ return ivalue(left_); }

	/**
	* \xbind
	* \breif ��Ԃ̍��̗v�f��Ԃ�
	*/
	int_t right(){ return ivalue(right_); }

	AnyPtr each();
};

class IntRangeIter : public Base{
public:

	IntRangeIter(const IntRangePtr& range)
		:it_(range->begin()), end_(range->end()){
	}

	void block_next(const VMachinePtr& vm);

private:
	int_t it_, end_;
};

/**
* \xbind lib::builtin
* \brief ���
*/
class FloatRange : public Range{
public:

	FloatRange(float_t left, float_t right, int_t kind = RANGE_CLOSED)
		:Range(left, right, kind){}

public:

	/**
	* \xbind
	* \breif ��Ԃ̍��̗v�f��Ԃ�
	*/
	float_t left(){ return fvalue(left_); }

	/**
	* \xbind
	* \breif ��Ԃ̍��̗v�f��Ԃ�
	*/
	float_t right(){ return fvalue(right_); }

	AnyPtr each();
};

/**
* \brief �X�R�[�v�I�Ȑe�����N���X
*/
class HaveParent : public Base{
public:

	HaveParent()
		:parent_(0){}

	HaveParent(const HaveParent& a);

	HaveParent& operator=(const HaveParent& a);

	~HaveParent();

	virtual const ClassPtr& object_parent();

	virtual void set_object_parent(const ClassPtr& parent);

protected:

	Class* parent_;

	virtual void visit_members(Visitor& m);
};

/**
* \brief �X�R�[�v�I�Ȑe�����N���X
*/
class RefCountingHaveParent : public RefCountingBase{
public:

	RefCountingHaveParent()
		:parent_(0){}

	RefCountingHaveParent(const RefCountingHaveParent& a);

	RefCountingHaveParent& operator=(const RefCountingHaveParent& a);

	~RefCountingHaveParent();

	const ClassPtr& object_parent();

	void set_object_parent(const ClassPtr& parent);

protected:

	Class* parent_;

	void visit_members(Visitor& m);
};

/**
* \brief GC���ɒʒm���󂯎��N���X
*/
class GCObserver : public Base{
public:
	GCObserver();
	GCObserver(const GCObserver& v);
	virtual ~GCObserver();
	virtual void before_gc(){}
	virtual void after_gc(){}
};


}

#endif // XTAL_BASICTYPE_H_INCLUDE_GUARD
