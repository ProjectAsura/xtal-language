
#pragma once

#include "xtal_any.h"

namespace xtal{

class ThreadImpl : public AnyImpl{
public:

	ThreadImpl(void (*fun)(const Any&), const Any& value);

	virtual void join() = 0;
	
	Any value() const{
		return value_;
	}

protected:

	void begin_thread();

protected:

	virtual void visit_members(Visitor& m);

	void (*fun_)(const Any&);
	Any value_;
};

class MutexImpl : public AnyImpl{
public:

	MutexImpl();

	virtual void lock() = 0;
	virtual void unlock() = 0;
};

class ThreadLib{
public:
	virtual ~ThreadLib();
	virtual ThreadImpl* create_thread(void (*fun)(const Any&), const Any& value) = 0;
	virtual MutexImpl* create_mutex() = 0;
	virtual void sleep(uint_t millisec) = 0;
	virtual uint_t current_thread_id() = 0;
};

class Thread : public Any{
public:

	Thread(const Any& fun);

	Thread(const Null&)
		:Any(null){}

	explicit Thread(ThreadImpl* p)
		:Any((AnyImpl*)p){}

	explicit Thread(const ThreadImpl* p)
		:Any((AnyImpl*)p){}

	void join() const;
	
	static void sleep(uint_t millisec);

	static uint_t current_thread_id();


	ThreadImpl* impl() const{
		return (ThreadImpl*)Any::impl();
	}
};

class Mutex : public Any{
public:

	Mutex();

	Mutex(const Null&)
		:Any(null){}

	explicit Mutex(MutexImpl* p)
		:Any((AnyImpl*)p){}

	explicit Mutex(const MutexImpl* p)
		:Any((AnyImpl*)p){}

	void lock() const;

	void unlock() const;
		
	MutexImpl* impl() const{
		return (MutexImpl*)Any::impl();
	}
};

void InitThread();
void UninitThread();

void set_thread(ThreadLib& lib);

void set_thread();

bool stop_the_world();
void restart_the_world();

void global_interpreter_lock();
void global_interpreter_unlock();

void xlock();
void xunlock();


extern bool thread_enabled_;
extern int thread_counter_;

inline int yield_thread(){
	thread_counter_ = 0;
	Thread::sleep(0);
	return 1;
}

struct GlobalInterpreterLock{
	GlobalInterpreterLock(int){ if(thread_enabled_)global_interpreter_lock(); }
	~GlobalInterpreterLock(){ if(thread_enabled_)global_interpreter_unlock(); }
	operator bool() const{ return true; }
};

struct GlobalInterpreterUnlock{
	GlobalInterpreterUnlock(int){ if(thread_enabled_)global_interpreter_unlock(); }
	~GlobalInterpreterUnlock(){ if(thread_enabled_)global_interpreter_lock(); }
	operator bool() const{ return true; }
};

struct XUnlock{
	XUnlock(int){ if(thread_enabled_)xunlock(); }
	~XUnlock(){ if(thread_enabled_)xlock(); }
	operator bool() const{ return true; }
};

}