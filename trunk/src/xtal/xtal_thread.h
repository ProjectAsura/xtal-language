/** \file src/xtal/xtal_thread.h
* \brief src/xtal/xtal_thread.h
*/

#ifndef XTAL_THREAD_H_INCLUDE_GUARD
#define XTAL_THREAD_H_INCLUDE_GUARD

#pragma once

namespace xtal{

class ThreadSpace;

/**
* \xbind
* \xinherit lib::builtin::Any
* \brief �X���b�h
*/
class Thread : public Base{
public:

	/**
	* \brief �X���b�h�I�u�W�F�N�g�𐶐�����
	*/
	Thread();

	~Thread();

public:

	/**
	* \brief �X���b�h���J�n����
	*/
	void start(const AnyPtr& callback);

	/**
	* \brief �X���b�h���I���܂őҋ@����
	*/
	void join();

public:

	/**
	* \brief �X���b�h��؂�ւ���
	*/
	static void yield();
	
	/**
	* \brief �J�����g�X���b�h��sec�b���点��
	*/
	static void sleep(float_t sec);

protected:

	static void trampoline(void* data);

	void begin_thread();

protected:

	virtual void visit_members(Visitor& m);

	AnyPtr callback_;
	void* impl_;
	Environment* env_;
};

/**
* \xbind
* \xinherit lib::builtin::Any
* \brief �~���[�e�b�N�X
*/
class Mutex : public Base{
public:

	/**
	* \brief �~���[�e�b�N�X�I�u�W�F�N�g�𐶐�����
	*/
	Mutex();

	~Mutex();

	/**
	* \brief ���b�N����
	*/
	void lock();

	/**
	* \brief �A�����b�N����
	*/
	void unlock();

	void rawlock();

public:

	void* impl(){
		return impl_;
	}

private:
	void* impl_;
};

void yield_thread();
void sleep_thread(float_t sec);

}

#endif // XTAL_THREAD_H_INCLUDE_GUARD
