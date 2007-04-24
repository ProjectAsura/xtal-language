
#pragma once

#include <malloc.h>
#include <stddef.h>
#include <string>

namespace xtal{

/** @addtogroup memory */
/*@{*/

/**
* @brief ���[�U�[���o�^�����������A���P�[�g�֐����g���ă������m�ۂ���B
*
* �������m�ێ��s�͗�O�ŕԂ����B
*/
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
void user_free(void* p, size_t size);

/**
* @brief �g�p���郁�����A���P�[�g�֐���ݒ肷��B
*
*/
void set_user_malloc(void* (*malloc)(size_t), void (*free)(void*));


/**
* @brief xtal�Ŏg�p���郁�����[��ݒ肷��B
*
*/
void set_memory(void* memory, size_t size);

/**
* ���I�ȁA�|�C���^�̔z����쐬�A�g������֐��B
*
* ��ԍŏ��̍쐬���́A�����S�Ă�null�ł���K�v������B
* @param begin �������̐擪
* @param end �������̍Ō�̈��
* @param current �g�p���̗v�f�̈��
*/
void expand_simple_dynamic_pointer_array(void**& begin, void**& end, void**& current, int addsize=1024);

/**
* expand_simple_dynamic_pointer_array�Ő��������z����A�g���Ă�����ۂ̃T�C�Y�܂ŏk������B
*
* �v�f����������Ȃ�(current==begin�Ȃ�)���S�ɉ�������B
* @param begin �������̐擪
* @param end �������̍Ō�̈��
* @param current �g�p���̗v�f�̈��
*/
void fit_simple_dynamic_pointer_array(void**& begin, void**& end, void**& current);

/*@}*/


/**
* @brief user_malloc, user_free���g���ASTL�̗v���ɓK�������A���P�[�^�N���X�B
*
*/
template<class T>
struct Alloc{

    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T &reference;
    typedef const T &const_reference;
    typedef T value_type;

	template<class U>
	struct rebind{
		typedef Alloc<U> other;
    };

    Alloc(){}

	template<class U>
	Alloc(const Alloc<U>&){}

	template<class U>
	Alloc<T>& operator=(const Alloc<U>&){
		return* this;
	}

	Alloc(const Alloc<T>&){}

    Alloc<T>& operator=(const Alloc<T>&){
		return* this;
	}

    pointer address(reference x) const{
		return &x;
	}

    const_pointer address(const_reference x) const{
		return &x;
	}

    pointer allocate(size_type n, const void* hint = 0){
		return static_cast<pointer>(user_malloc(sizeof(T)*n));
	}

    void deallocate(pointer p, size_type n){
		user_free(p, sizeof(T)*n);
    }
	
	void construct(pointer p, const T& val){
		new(p) T(val);
	}

    void destroy(pointer p){
		p->~T();
	}
	
    size_type max_size() const{
		return 0xffffffffU/sizeof(T);
	}

};

template<class T, class U> 
inline bool operator==(const Alloc<T>&, const Alloc<U>&){	
	return true;
}

template<class T, class U> 
inline bool operator!=(const Alloc<T>&, const Alloc<U>&){	
	return false;
}

template<>
struct Alloc<void> {
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef void* pointer;
    typedef const void* const_pointer;
    typedef void value_type;

	template<class U>
	struct rebind{
		typedef Alloc<U> other;
    };

    Alloc(){}

	Alloc(const Alloc<void> &){}

    Alloc<void>& operator=(const Alloc<void>&){
		return* this;
	}

	template<class U>
	Alloc(const Alloc<U>&){}

	template<class U>
	Alloc<void>& operator=(const Alloc<U>&){
		return* this;
	}
};

/*
* �X�^�b�N�^�̃������A���P�[�^�B
* STL�̃A���P�[�^�ɂ͓K�����Ȃ��B
*/
class RegionAlloc{
	char* begin_;
	char* pos_;
	char* end_;
	size_t alloced_size_;
public:

	RegionAlloc(size_t first_buffer_size = 1024);

	~RegionAlloc();

	void* allocate(size_t size);

	void release();

private:

	void add_chunk(size_t minsize);

private:

	RegionAlloc(const RegionAlloc&);
	RegionAlloc& operator =(const RegionAlloc&);

};

/**
* @brief �ƂĂ��V���v���ȃ������Ǘ��@�\
*
*/
class SimpleMemoryManager{
public:
	
	struct Chunk{
		Chunk* next;
		Chunk* prev;
		int used;
		
		size_t size(){ return (char*)next - (char*)buf(); }
		void* buf(){ return this+1; }
	};

	SimpleMemoryManager(){
		head_ = begin_ = end_ = 0;
	}
	
	void init(void* begin, void* end);
	
	void* malloc(size_t size);
	
	void free(void* p);

	Chunk* begin(){
		return begin_;
	}
	
	Chunk* end(){
		return end_;
	}

	Chunk* to_chunk(void* p){
		return (Chunk*)p-1;
	}

	void add_ref(void* p){
		to_chunk(p)->used++;
	}
	
private:
	Chunk* head_;
	Chunk* begin_;
	Chunk* end_;
};

}//namespace 
