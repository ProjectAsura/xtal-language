
#pragma once

namespace xtal{

class ChCodeLib{
public:
	virtual ~ChCodeLib(){}
	virtual void initialize(){}
	virtual int_t ch_len(char_t lead){ return 1; }
	virtual int_t ch_len2(const char_t* str){ return ch_len(*str); }
	virtual StringPtr ch_inc(const char_t* data, int_t data_size);
	virtual int_t ch_cmp(const char_t* a, int_t asize, const char_t* b, int_t bsize);
};

class ThreadLib{
public:
	virtual ~ThreadLib(){}
	virtual void initialize(){}
	virtual ThreadPtr new_thread(){ return ThreadPtr(); }
	virtual MutexPtr new_mutex(){ return xnew<Mutex>(); }
	virtual void yield(){}
	virtual void sleep(float_t sec){}
};

class StreamLib{
public:
	virtual ~StreamLib(){}
	virtual void initialize(){}

	virtual StreamPtr new_stdin_stream(){ return StreamPtr(); }
	virtual StreamPtr new_stdout_stream(){ return StreamPtr(); }
	virtual StreamPtr new_stderr_stream(){ return StreamPtr(); }
};

class FilesystemLib{
public:
	virtual ~FilesystemLib(){}
	virtual void initialize(){}
	
	virtual AnyPtr entries(const StringPtr& path){ return AnyPtr(); }
	virtual StreamPtr open(const StringPtr& path, const StringPtr& flags){ return StreamPtr(); } 
	virtual bool is_directory(const StringPtr& path){ return false; }
};

class AllocatorLib{
public:
	virtual ~AllocatorLib(){}
	virtual void initialize(){}
	virtual void* malloc(std::size_t size){ return std::malloc(size); }
	virtual void free(void* p, std::size_t size){ std::free(p); }
};

struct Setting{
	ThreadLib* thread_lib;
	StreamLib* stream_lib;
	FilesystemLib* filesystem_lib;
	AllocatorLib* allocator_lib;
	ChCodeLib* chcode_lib;

	Setting();
};

/**
* @brief Xtal���s��������������B
*/
void initialize(const Setting& setting);

/**
* @brief Xtal���s����j������B
*/
void uninitialize();

/**
* @brief ���݂̃J�����g��Xtal���s�����擾����B
*/
Environment* environment();

/**
* @brief �J�����g��Xtal���s����ݒ肷��B
*/
void set_environment(Environment* e);

/////////////////////////////////////////////////////

/**
* @brief ���[�U�[���o�^�����������A���P�[�g�֐����g���ă������m�ۂ���B
*
*/
void* xmalloc(size_t size);

/**
* @brief ���[�U�[���o�^�����������f�A���P�[�g�֐����g���ă������������B
*
*/
void xfree(void* p, size_t size);

/**
* @brief �������I�u�W�F�N�g�p�Ƀ��������A���P�[�g����B
*/
void* so_malloc(size_t size);

/**
* @brief �������I�u�W�F�N�g�p�̃��������������B
*/
void so_free(void* p, size_t size);

/**
* @brief �������m�ۂ��X�R�[�v�ɕ����߂邽�߂̃��[�e�B���e�B�N���X
*/
struct UserMallocGuard{
	UserMallocGuard():p(0){}
	UserMallocGuard(uint_t size):p(xmalloc(size)),size(size){}
	~UserMallocGuard(){ xfree(p, size); }
	
	void malloc(size_t sz){ xfree(p, size); p = xmalloc(sz); size = sz; }

	void* get(){ return p; }

	void* release(){ void* ret = p; p = 0; size = 0; return ret; }
private:
	void* p;
	uint_t size;

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

/////////////////////////////////////////////////////

/**
* @brief �K�[�x�W�R���N�V���������s����
*
* ���قǎ��Ԃ͂�����Ȃ����A���S�ɃS�~������ł��Ȃ��K�[�x�W�R���N�g�֐�
* �Ⴆ�Ώz�Q�Ƃ͂���ł͌��m�ł��Ȃ��B
*/
void gc();

/**
* @brief �z�I�u�W�F�N�g���������t���K�[�x�W�R���N�V���������s����
*
* ���Ԃ͂����邪�A���݃S�~�ƂȂ��Ă�����̂͂Ȃ�ׂ��S�ĉ������K�[�x�W�R���N�g�֐�
* �z�Q�Ƃ����m�ł���B
*/
void full_gc();

/**
* @brief �K�[�x�W�R���N�V�����𖳌�������
*
* gc��full_gc�̌Ăяo���𖳌�������֐��B
* �����ł��ꂪ����Ăяo���ꂽ���L������Ă���A�Ăяo������enable_gc���ĂтȂ��ƃK�[�x�W�R���N�V�����͗L���ɂȂ�Ȃ�
*/
void disable_gc();

/**
* @brief �K�[�x�W�R���N�V������L��������
*
* disable_gc���Ă΂ꂽ�񐔂Ɠ��������Ăяo���ƃK�[�x�W�R���N�V�������L���ɂȂ�
*/
void enable_gc();

/////////////////////////////////////////////////////

/**
* @brief key�ɑΉ�����C++�̃N���X�̃N���X�I�u�W�F�N�g��Ԃ��B
*/
const ClassPtr& cpp_class(CppClassSymbolData* key);

/**
* @brief key�ɑΉ�����C++�̃N���X�̃N���X�I�u�W�F�N�g�𐶐����A�Ԃ��B
*
* ���ɐ�������Ă���ꍇ�A�����ς݂̃N���X��Ԃ��B
*/
const ClassPtr& new_cpp_class(CppClassSymbolData* key);

/**
* @brief ����key�ɑΉ�����C++�̃N���X�̃N���X�I�u�W�F�N�g����������Ă��邩��Ԃ��B
*/
bool exists_cpp_class(CppClassSymbolData* key);

/**
* @brief key�ɑΉ�����C++�̃N���X�̃N���X�I�u�W�F�N�g��ݒ肷��B�B
*/
void set_cpp_class(const ClassPtr& cls, CppClassSymbolData* key);

/**
* @brief T�`��xtal�ň�����N���X�𐶐����A�Ԃ��B
* ���ɐ�������Ă���ꍇ�A�����ς݂̃N���X��Ԃ��B
*/
template<class T>
inline const ClassPtr& new_cpp_class(){
	return new_cpp_class(&CppClassSymbol<T>::value);
}

/**
* @brief T�`��xtal�ň�����N���X�𐶐����A�Ԃ��B
* ���ɐ�������Ă���ꍇ�A�����ς݂̃N���X��Ԃ��B
* @param name �I�u�W�F�N�g�̖��O
*/
template<class T>
inline const ClassPtr& new_cpp_class(const StringPtr& name){
	const ClassPtr& ret = new_cpp_class(&CppClassSymbol<T>::value);
	ret->set_object_name(name);
	return ret;
}

/**
* @brief ����new_cpp_class<T>()�Ő���������Ă��邩��Ԃ��B
*/
template<class T>
inline bool exists_cpp_class(){
	return exists_cpp_class(&CppClassSymbol<T>::value);
}

/**
* @brief new_cpp_class<T>()�Ő������ꂽ�N���X���擾����B
*/
template<class T>
inline const ClassPtr& cpp_class(){
	return cpp_class(&CppClassSymbol<T>::value);
}

/**
* @brief cpp_class<T>�ȂǂŕԂ����N���X��ݒ肷��B
*/
template<class T>
inline void set_cpp_class(const ClassPtr& cls){
	return set_cpp_class(cls, &CppClassSymbol<T>::value);
}

/**
* @brief T�`��xtal�ň�����N���X�𐶐����A�o�^����B
* ���ɐ�������Ă���ꍇ�A�����ς݂̃N���X��Ԃ��B
*/
template<class T>
const SmartPtr<T>& new_cpp_singleton(){
	if(exists_cpp_class<T>()){
		return unchecked_ptr_cast<T>(cpp_class<T>());
	}
	set_cpp_class<T>(xnew<T>());
	return unchecked_ptr_cast<T>(cpp_class<T>());
}

/////////////////////////////////////////////////////

/**
* @brief �N���X�̃����o�����o���B
*/
const AnyPtr& cache_member(const AnyPtr& target_class, const IDPtr& primary_key, const AnyPtr& secondary_key, int_t& accessibility);

/**
* @brief �N���X�̌p���֌W�𒲂ׂ�B
*/
bool cache_is(const AnyPtr& target_class, const AnyPtr& klass);

/**
* @brief �����o�[�̃L���b�V���e�[�u���ɓo�^����Ă���f�[�^�𖳌��ɂ���B
*/
void invalidate_cache_member();

/**
* @brief �p���֌W�̃L���b�V���e�[�u���ɓo�^����Ă���f�[�^�𖳌��ɂ���B
*/
void invalidate_cache_is();

/////////////////////////////////////////////////////

/**
* @brief VMachine�C���X�^���X�������^������B
*/
VMachinePtr vmachine_take_over();

/**
* @brief VMachine�C���X�^���X��ԋp����B
*/
void vmachine_take_back(const VMachinePtr& vm);

/////////////////////////////////////////////////////

/**
* @brief Iterator�N���X��Ԃ�
*/
const ClassPtr& Iterator();

/**
* @brief Iterable�N���X��Ԃ�
*/
const ClassPtr& Iterable();

/**
* @brief builtin�V���O���g���N���X��Ԃ�
*/
const ClassPtr& builtin();

/**
* @brief lib�I�u�W�F�N�g��Ԃ�
*/
const LibPtr& lib();

/**
* @brief stdin�X�g���[���I�u�W�F�N�g��Ԃ�
*/
const StreamPtr& stdin_stream();

/**
* @brief stdout�X�g���[���I�u�W�F�N�g��Ԃ�
*/
const StreamPtr& stdout_stream();

/**
* @brief stderr�X�g���[���I�u�W�F�N�g��Ԃ�
*/
const StreamPtr& stderr_stream();

/**
* @brief RuntimeError�N���X��Ԃ�
*/
const ClassPtr& RuntimeError();

/**
* @brief CompileError�N���X��Ԃ�
*/
const ClassPtr& CompileError();

/**
* @brief UnsupportedError�N���X��Ԃ�
*/
const ClassPtr& UnsupportedError();

/**
* @brief RuntimeError�N���X��Ԃ�
*/
const ClassPtr& ArgumentError();

/**
* @brief filesystem�V���O���g���I�u�W�F�N�g��Ԃ�
*/
const SmartPtr<Filesystem>& filesystem();

/**
* @brief debug�V���O���g���I�u�W�F�N�g��Ԃ�
*/
const SmartPtr<Debug>& debug();

/**
* @brief �f�o�b�O�@�\��L���ɂ���
* �f�o�b�O�@�\�̓f�t�H���g�ł͖����ɂȂ��Ă���B
*/
void enable_debug();

/**
* @brief �f�o�b�O�@�\�𖳌��ɂ���
*/
void disable_debug();

/**
* @brief �����񃊃e�������C���^�[���ς݃I�u�W�F�N�g�ɕϊ�����
*/
const IDPtr& intern_literal(const char_t* str, IdentifierData* iddata);

/**
* @brief ��������C���^�[���ς݃I�u�W�F�N�g�ɕϊ�����
*/
const IDPtr& intern(const char_t* str);

/**
* @brief ��������C���^�[���ς݃I�u�W�F�N�g�ɕϊ�����
*/
const IDPtr& intern(const char_t* str, uint_t data_size);

AnyPtr interned_strings();

bool thread_enabled();

void yield_thread();

void sleep_thread(float_t sec);

ThreadPtr new_thread(const AnyPtr& callback_fun);

MutexPtr new_mutex();

void lock_mutex(const MutexPtr& p);

/**
* @brief �������b�N����
*/
void xlock();

/**
* @brief �����A�����b�N����
*/
void xunlock();

struct XUnlock{
	XUnlock(int){ xunlock(); }
	~XUnlock(){ xlock(); }
	operator bool() const{ return true; }
private:
	XTAL_DISALLOW_COPY_AND_ASSIGN(XUnlock);
};

/**
* @brief VMachinePtr�I�u�W�F�N�g��Ԃ�
*
* �O���[�o����VMachinePtr�I�u�W�F�N�g��Ԃ��B
* �X���b�h���ɂ��̃O���[�o��VMachinePtr�I�u�W�F�N�g�͑��݂���B
*/
const VMachinePtr& vmachine();

/**
* @brief �e�L�X�g�}�b�v��Ԃ�
*/
const MapPtr& text_map();

/**
* @brief �擪�o�C�g�����āA���̃}���`�o�C�g���������������𒲂ׂ�B
*
* �}�C�i�X�̒l���Ԃ��ꂽ�ꍇ�A�Œᕶ������Ԃ��B
* -2�̏ꍇ�A�Œ�2�����ȏ�̕����ŁA�{���̒�����2�����ڂ�ǂ܂Ȃ��Ɣ��f�ł��Ȃ��A�Ƃ����Ӗ��ƂȂ�B
*/
int_t ch_len(char_t lead);

/**
* @brief �}���`�o�C�g���������������𒲂ׂ�B
*
* int_t ch_len(char_t lead)���Ă΂ꂽ��A�}�C�i�X�̒l��Ԃ����ꍇ�ɑ����ČĂԁB
* ch_len��-2�̒l��Ԃ�����́Astr�̐�ɂ͍Œ�2�o�C�g���̃f�[�^���i�[���邱�ƁB
*/
int_t ch_len2(const char_t* str);


/**
* @brief ���̕�����Ԃ�
*
* �Ⴆ�� a ��n�����ꍇ�Ab ���Ԃ�
*/
StringPtr ch_inc(const char_t* data, int_t data_size);

/**
* @brief �����̑召����
*
* ���̒l a �̕����̕���b�̕�����菬����
* 0�̒l ������
* ���̒l b�̕����̕���a�̕�����菬����
*/
int_t ch_cmp(const char_t* a, uint_t asize, const char_t* b, uint_t bsize);

/**
* @biref ���Z�q�̖��O������킷������̔z���Ԃ�
*/
const IDPtr* id_op_list();


#ifndef XTAL_NO_PARSER

/**
* @brief file_name�t�@�C�����R���p�C������B
*
* @param file_name Xtal�X�N���v�g���L�q���ꂽ�t�@�C���̖��O
* @return ���s�ł���֐��I�u�W�F�N�g
* ���̖߂�l��serialize����ƁA�o�C�g�R�[�h�`���ŕۑ������B
*/
CodePtr compile_file(const StringPtr& file_name);

/**
* @brief source��������R���p�C������B
*
* @param source Xtal�X�N���v�g���L�q���ꂽ������
* @return ���s�ł���֐��I�u�W�F�N�g
* ���̖߂�l��serialize����ƁA�o�C�g�R�[�h�`���ŕۑ������B
*/
CodePtr compile(const StringPtr& source);

/**
* @brief file_name�t�@�C�����R���p�C�����Ď��s����B
*
* @param file_name Xtal�X�N���v�g���L�q���ꂽ�t�@�C���̖��O
* @return �X�N���v�g����return���ꂽ�l
*/
AnyPtr load(const StringPtr& file_name);

/**
* @brief file_name�t�@�C�����R���p�C�����ăR���p�C���ς݃\�[�X��ۑ����A���s����B
*
* @param file_name Xtal�X�N���v�g���L�q���ꂽ�t�@�C���̖��O
* @return �X�N���v�g����return���ꂽ�l
*/
AnyPtr load_and_save(const StringPtr& file_name);

CodePtr source(const char_t* src, int_t size, const char* file);

#endif

CodePtr compiled_source(const void* src, int_t size, const char* file);

}
