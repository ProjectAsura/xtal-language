
#pragma once

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
void user_free(void* p);

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
	typedef typename detail::AC_IfDefault<SECOND,
		std::basic_string<FIRST, std::char_traits<FIRST>, Alloc<FIRST> >,
		std::basic_string<FIRST, SECOND, Alloc<FIRST> >
		>::type string;
	typedef typename detail::AC_IfDefault<THIRD,
		std::map<FIRST, SECOND, std::less<FIRST>, Alloc<std::pair<const FIRST, SECOND> > >,
		std::map<FIRST, SECOND, THIRD, Alloc<std::pair<const FIRST, SECOND> > >
		>::type map;
	typedef typename detail::AC_IfDefault<THIRD,
		std::multimap<FIRST, SECOND, std::less<FIRST>, Alloc<std::pair<const FIRST, SECOND> > >,
		std::multimap<FIRST, SECOND, THIRD, Alloc<std::pair<const FIRST, SECOND> > >
		>::type multimap;
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
		
		size_t size(){ return (u8*)next - (u8*)buf(); }
		void* buf(){ return this+1; }
	};

	SimpleMemoryManager(){ head_ = begin_ = end_ = 0; }
	
	void init(void* begin, void* end);

	void* malloc(size_t size);
	void free(void* p);

	Chunk* begin(){ return begin_; }
	Chunk* end(){ return end_; }

	Chunk* to_chunk(void* p){ return (Chunk*)p-1; }
	void add_ref(void* p){ to_chunk(p)->used++; }
	
private:
	Chunk* head_;
	Chunk* begin_;
	Chunk* end_;
};

/*@}*/


}//namespace 
