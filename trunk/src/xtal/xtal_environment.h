
#pragma once

namespace xtal{

struct Setting{
	ThreadLib* thread_lib;
	StreamLib* stream_lib;
	FilesystemLib* filesystem_lib;
	AllocatorLib* allocator_lib;
	ChCodeLib* chcode_lib;

	Setting();
};

class Environment;

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
	
void debug_print();

void print_alive_objects();

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
* @brief �������I�u�W�F�N�g�p�Ƀ��������A���P�[�g����B
*/
void* so_malloc(size_t size);

/**
* @brief �������I�u�W�F�N�g�p�̃��������������B
*/
void so_free(void* p, size_t size);

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

void register_gc(RefCountingBase* p);

void register_gc_observer(GCObserver* p);

void unregister_gc_observer(GCObserver* p);

const ClassPtr& cpp_class(CppClassSymbolData* key);

const ClassPtr& new_cpp_class(const StringPtr& name, CppClassSymbolData* key);

bool exists_cpp_class(CppClassSymbolData* key);

const ClassPtr& cpp_class(CppClassSymbolData* key);

void set_cpp_class(const ClassPtr& cls, CppClassSymbolData* key);

/**
* @brief T�`��xtal�ň�����N���X�𐶐����A�o�^����B
* ���ɐ�������Ă���ꍇ�A�����ς݂̃N���X��Ԃ��B
*/
template<class T>
inline const ClassPtr& new_cpp_class(const StringPtr& name){
	return new_cpp_class(name, &CppClassSymbol<T>::value);
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

/**
* @brief ����new_cpp_class<T>()�Ő���������Ă��邩���ׂ�B
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

/**
* @brief VMachine�C���X�^���X�������^������B
*/
VMachinePtr vmachine_take_over();

/**
* @brief VMachine�C���X�^���X��ԋp����B
*/
void vmachine_take_back(const VMachinePtr& vm);

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
* @brief lib�N���X��Ԃ�
*/
const LibPtr& lib();

const StreamPtr& stdin_stream();

const StreamPtr& stdout_stream();

const StreamPtr& stderr_stream();

const ClassPtr& RuntimeError();

const ClassPtr& CompileError();

const ClassPtr& UnsupportedError();

const ClassPtr& ArgumentError();

const IDPtr& intern_literal(const char_t* str);

const IDPtr& intern(const char_t* str);

const IDPtr& intern(const char_t* str, uint_t data_size);

const IDPtr& intern(const char_t* str, uint_t data_size, uint_t hash);

AnyPtr interned_strings();

bool thread_enabled();

void yield_thread();

void sleep_thread(float_t sec);

ThreadPtr new_thread(const AnyPtr& callback_fun);

MutexPtr new_mutex();

void lock_mutex(const MutexPtr& p);

/**
* @brief VMachinePtr�I�u�W�F�N�g��Ԃ�
*
* �O���[�o����VMachinePtr�I�u�W�F�N�g��Ԃ��B
* �X���b�h���ɂ��̃O���[�o��VMachinePtr�I�u�W�F�N�g�͑��݂���B
*/
const VMachinePtr& vmachine();


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
