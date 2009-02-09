
#pragma once

namespace xtal{

inline void* user_malloc(size_t size);

/**
* @brief ���[�U�[���o�^�����������A���P�[�g�֐����g���ă������m�ۂ���B
*
* �������m�ێ��s��NULL�l�ŕԂ����B
*/
inline void* user_malloc_nothrow(size_t size);
/**
* @brief ���[�U�[���o�^�����������f�A���P�[�g�֐����g���ă������������B
*
*/
inline void user_free(void* p);

/**
* @brief �������I�u�W�F�N�g�p�Ƀ��������A���P�[�g����B
*/
inline void* so_malloc(size_t size);

/**
* @brief �������I�u�W�F�N�g�p�̃��������������B
*/
inline void so_free(void* p, size_t size);

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
	struct rebind{ typedef Alloc<U> other; };

    Alloc(){}
	template<class U>
	Alloc(const Alloc<U>&){}
	template<class U>
	Alloc<T>& operator=(const Alloc<U>&){ return* this; }
	Alloc(const Alloc<T>&){}
    Alloc<T>& operator=(const Alloc<T>&){ return* this; }

    pointer address(reference x) const{ return &x; }
    const_pointer address(const_reference x) const{ return &x; }

    pointer allocate(size_type n, const void* = 0){ return static_cast<pointer>(user_malloc(sizeof(T)*n)); }
    void deallocate(pointer p, size_type n){ user_free(p); }
	
	void construct(pointer p, const T& val){ new(p) T(val); }
    void destroy(pointer p){ p->~T(); p = 0; }
	
    size_type max_size() const{ return 0xffffffffU/sizeof(T); }
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
	struct rebind{ typedef Alloc<U> other; };

    Alloc(){}
	Alloc(const Alloc<void> &){}
    Alloc<void>& operator=(const Alloc<void>&){ return* this; }
	template<class U>
	Alloc(const Alloc<U>&){}
	template<class U>
	Alloc<void>& operator=(const Alloc<U>&){ return* this; }
};

struct UserMallocGuard{
	void* p;
	UserMallocGuard():p(0){}
	UserMallocGuard(uint_t size):p(user_malloc(size)){}
	~UserMallocGuard(){ user_free(p); }
	
	void malloc(size_t size){ user_free(p); p = user_malloc(size); }
	void* get(){ return p; }
	void* release(){ void* ret = p; p = 0; return ret; }
private:
	UserMallocGuard(const UserMallocGuard&);
	void operator =(const UserMallocGuard&);
};

namespace detail{
	struct AC_default{};

	template<class>
	struct AC_If{
		template<class T, class U>
		struct inner{ typedef U type; };
	};
	
	template<>
	struct AC_If<AC_default>{
		template<class T, class U>
		struct inner{ typedef T type; };
	};
	
	template<class T, class Then, class Else>
	struct AC_IfDefault{
		typedef typename AC_If<T>::template inner<Then, Else>::type type;
	};
}


/**
* Alloc�N���X���g����STL�R���e�i���g���₷�����邽�߂̃��[�e�B���e�B
* 
* Alloc-Container �̗�
* 
* AC<int>::vector �� std::vector<int, Alloc<int> > �Ɠ���
* AC<int, float>::map �� std::map<int, float, std::less<int>, Alloc<std::pair<const int, float> > > �Ɠ���
* AC<int, float, Comp>::map �� std::map<int, float, Comp, Alloc<std::pair<const int, float> > > �Ɠ���
*/
template<class FIRST, class SECOND = detail::AC_default, class THIRD = detail::AC_default>
struct AC{
	typedef std::vector<FIRST, Alloc<FIRST> > vector;
	typedef std::deque<FIRST, Alloc<FIRST> > deque;
	typedef std::list<FIRST, Alloc<FIRST> > list;
	typedef typename detail::AC_IfDefault<SECOND,
		std::set<FIRST, std::less<FIRST>, Alloc<FIRST> >,
		std::set<FIRST, SECOND, Alloc<FIRST> >
		>::type set;
	typedef typename detail::AC_IfDefault<THIRD,
		std::map<FIRST, SECOND, std::less<FIRST>, Alloc<std::pair<const FIRST, SECOND> > >,
		std::map<FIRST, SECOND, THIRD, Alloc<std::pair<const FIRST, SECOND> > >
		>::type map;
	typedef typename detail::AC_IfDefault<THIRD,
		std::multimap<FIRST, SECOND, std::less<FIRST>, Alloc<std::pair<const FIRST, SECOND> > >,
		std::multimap<FIRST, SECOND, THIRD, Alloc<std::pair<const FIRST, SECOND> > >
		>::type multimap;
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
	virtual void initialize() = 0;
	virtual void* malloc(std::size_t size) = 0;
	virtual void free(void* p) = 0;
};

class CStdAllocatorLib : public AllocatorLib{
public:
	virtual ~CStdAllocatorLib(){}
	virtual void initialize(){}
	virtual void* malloc(std::size_t size){ return std::malloc(size); }
	virtual void free(void* p){ std::free(p); }
};

}//namespace 
