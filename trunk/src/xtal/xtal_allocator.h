
#pragma once

#include <map>

namespace xtal{

void* user_malloc(size_t size);

/**
* @brief ���[�U�[���o�^�����������A���P�[�g�֐����g���ă������m�ۂ���B
*
* �������m�ێ��s��NULL�l�ŕԂ����B
*/
void* user_malloc_nothrow(size_t size);

/**
* @brief ���[�U�[���o�^�����������f�A���P�[�g�֐����g���ă������������B
*
*/
void user_free(void* p);

/**
* @brief �������I�u�W�F�N�g�p�Ƀ��������A���P�[�g����B
*/
void* so_malloc(size_t size);

/**
* @brief �������I�u�W�F�N�g�p�̃��������������B
*/
void so_free(void* p, size_t size);

/**
* @brief ���I�ȃ|�C���^�̔z����쐬�A�g������֐��B
*
* ��ԍŏ��̍쐬���́A�����S�Ă�null�ł���K�v������B
* @param begin �������̐擪
* @param end �������̍Ō�̈��
* @param current �g�p���̗v�f�̈��
*/
void expand_simple_dynamic_pointer_array(void**& begin, void**& end, void**& current, int addsize=1024);

/**
* @brief expand_simple_dynamic_pointer_array�Ő��������z����A�g���Ă�����ۂ̃T�C�Y�܂ŏk������B
*
* �v�f����������Ȃ�(current==begin�Ȃ�)���S�ɉ�������B
* @param begin �������̐擪
* @param end �������̍Ō�̈��
* @param current �g�p���̗v�f�̈��
*/
void fit_simple_dynamic_pointer_array(void**& begin, void**& end, void**& current);

/**
* @brief �������m�ۂ��X�R�[�v�ɕ����߂邽�߂̃��[�e�B���e�B�N���X
*/
struct UserMallocGuard{
	UserMallocGuard():p(0){}
	UserMallocGuard(uint_t size):p(user_malloc(size)){}
	~UserMallocGuard(){ user_free(p); }
	
	void malloc(size_t size){ user_free(p); p = user_malloc(size); }

	void* get(){ return p; }

	void* release(){ void* ret = p; p = 0; return ret; }
private:
	void* p;

	XTAL_DISALLOW_COPY_AND_ASSIGN(UserMallocGuard);
};

/**
* @brief �������m�ۂ��X�R�[�v�ɕ����߂邽�߂̃��[�e�B���e�B�N���X
*/
struct SOMallocGuard{
	SOMallocGuard():p(0){}
	SOMallocGuard(uint_t size):p(so_malloc(size)), sz(size){}
	~SOMallocGuard(){ so_free(p, sz); }
	
	void malloc(size_t size){ so_free(p, sz); p = so_malloc(size); sz = size; }

	void* get(){ return p; }

	void* release(){ void* ret = p; p = 0; return ret; }

	uint_t size(){ return sz; }
private:
	void* p;
	uint_t sz;

	XTAL_DISALLOW_COPY_AND_ASSIGN(SOMallocGuard);
};

class FixedAllocator{

	struct Chunk{

		typedef void* data_t;

		uint_t blocks_;
		uint_t blocks_available_;
		data_t* first_available_block_;
		Chunk* next_;
		//data_t buf_[blocks_];

		void init(uint_t blocks,uint_t block_size);

		void* malloc();

		void free(void* p);

		data_t* buf(){
			return reinterpret_cast<data_t*>(this+1);
		}
	};

public:
	
	typedef Chunk::data_t data_t;

private:

	int_t blocks_;
	data_t* free_data_;
	Chunk* first_chunk_;
	Chunk* last_chunk_;

public:

	FixedAllocator();

	void init(size_t block_size);

	void* malloc(size_t block_size);

	void free(void* p, size_t block_size);

	void release(size_t block_size);

private:

	void add_chunk(size_t block_size);

	void* malloc_impl(size_t block_size);

	void free_impl(void* p, size_t block_size);

	XTAL_DISALLOW_COPY_AND_ASSIGN(FixedAllocator);
};

class SmallObjectAllocator{	

	typedef FixedAllocator::data_t data_t;

public:

	enum{
		POOL_SIZE = 32,
		HANDLE_MAX_SIZE = POOL_SIZE*sizeof(data_t)
	};

public:

	void init();
	
	void* malloc(size_t size);

	void free(void* p, size_t size);

	void release();

private:

	FixedAllocator pool_[POOL_SIZE];
};

class AllocatorLib{
public:
	virtual ~AllocatorLib(){}
	virtual void initialize(){}
	virtual void* malloc(std::size_t size){ return std::malloc(size); }
	virtual void free(void* p){ std::free(p); }
};

}//namespace 
