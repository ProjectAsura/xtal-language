#ifndef XTAL_FRAME_H_INCLUDE_GUARD
#define XTAL_FRAME_H_INCLUDE_GUARD

#pragma once

namespace xtal{

class Frame : public HaveParent{
public:
	
	Frame(const FramePtr& outer, const CodePtr& code, ScopeInfo* info);
	
	Frame();

	Frame(const Frame& frame);

	Frame& operator=(const Frame& frame);
		
	~Frame();

public:
	
	/**
	* @brief �O���̃X�R�[�v��\��Frame�I�u�W�F�N�g��Ԃ��B
	*
	*/
	const FramePtr& outer(){ 
		return outer_; 
	}

	const CodePtr& code(){ 
		return code_; 
	}

	/**
	* @brief ���e�������ɒ�`���ꂽ�v�f�̐���Ԃ��B
	*
	*/
	int_t block_size(){ 
		return scope_info_->variable_size; 
	}

	/**
	* @brief i�Ԗڂ̃����o�[���_�C���N�g�Ɏ擾�B
	*
	*/
	AnyPtr& member_direct(int_t i){
		return (AnyPtr&)members_.at(i);
	}

	/**
	* @brief i�Ԗڂ̃����o�[���_�C���N�g�ɐݒ�B
	*
	*/
	void set_member_direct(int_t i, const AnyPtr& value){
		members_.set_at(i, value);
	}
		
public:

	/**
	* @brief �����o���i�[���ꂽ�AIterator��Ԃ�
	* �u���b�N�p�����[�^��(primary_key, secondary_key, value)
	*/
	AnyPtr members();

protected:

	void make_map_members();

	friend class MembersIter;

	FramePtr outer_;
	CodePtr code_;
	ScopeInfo* scope_info_;
	
	Array members_;

	struct Key{
		IDPtr primary_key;
		AnyPtr secondary_key;

		friend void visit_members(Visitor& m, const Key& a){
			m & a.primary_key & a.secondary_key;
		}
	};

	struct Value{
		u16 num;
		u16 flags;

		friend void visit_members(Visitor& m, const Value&){}
	};

	struct Fun{
		static uint_t hash(const Key& key){
			return (rawvalue(key.primary_key).uvalue>>3) ^ rawvalue(key.secondary_key).uvalue;
		}

		static bool eq(const Key& a, const Key& b){
			return raweq(a.primary_key, b.primary_key) && raweq(a.secondary_key, b.secondary_key);
		}
	};

	typedef Hashtable<Key, Value, Fun> map_t; 
	//map_t table_;

	map_t* map_members_;


	virtual void visit_members(Visitor& m){
		HaveParent::visit_members(m);
		m & outer_ & code_;

		for(uint_t i=0; i<members_.size(); ++i){
			m & members_.at(i);
		}

		if(map_members_){
			m & *map_members_;
		}
	}
};

class MembersIter : public Base{
	FramePtr frame_;
	Frame::map_t::iterator it_;

	virtual void visit_members(Visitor& m);

public:

	MembersIter(const FramePtr& a)
		:frame_(a), it_(frame_->map_members_->begin()){
	}

	void block_next(const VMachinePtr& vm);
};

}

#endif // XTAL_FRAME_H_INCLUDE_GUARD
