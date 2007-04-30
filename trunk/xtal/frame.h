
#pragma once

#include "any.h"
#include "code.h"
#include "vmachine.h"
#include "cfun.h"
#include "utilimpl.h"

namespace xtal{

void InitClass();

// fwd decl
class ModuleImpl;
class ClassImpl;
class InstanceImpl;

/**
* @briefブロックを表すクラス
*
*/
class Frame : public Any{
public:
		
	Frame();
	
	Frame(const Frame& outer, const Code& code, FrameCore* core);
	
	Frame(FrameImpl* p)
		:Any((AnyImpl*)p){}
	
	Frame(const Null&)
		:Any(null){}
	
public:
	
	/**
	* @brief 外側のスコープを表すFrameオブジェクトを返す。
	*
	*/
	const Frame& outer() const;

	/**
	* @brief リテラル時に定義された要素の数を返す。
	*
	*/
	int_t block_size() const;

	/**
	* @brief i番目のメンバーをダイレクトに取得。
	*
	*/
	const Any& member_direct(int_t i) const;

	/**
	* @brief i番目のメンバーをダイレクトに設定。
	*
	*/
	void set_member_direct(int_t i, const Any& value) const;
	
	/**
	* @brief Xtalで定義されているならtrueを返す。
	*
	*/
	bool is_defined_by_xtal() const;
	
	FrameImpl* impl() const{ return (FrameImpl*)Any::impl(); }

};

/**
* @briefクラス
*
*/ 
class Class : public Frame{
public:

	/**
	* @brief 名前を与えて構築する
	*
	*/	
	Class(const char* = 0);
	
	/**
	* @brief クラスを生成せず、nullを入れる
	*
	*/
	Class(const Null&)
		:Frame(null){}
	
	Class(const Frame& outer, const Code& code, FrameCore* core);

	explicit Class(ClassImpl* p)
		:Frame((FrameImpl*)p){}

public:

	/**
	* @brief メンバを取り出す
	*
	* @param name
	*/
	const Any& member(const ID& name) const;

	/**
	* @brief Mix-inする
	*
	* @param md Mix-inするクラスオブジェクト
	*/
	void inherit(const Any& md) const;

	/**
	* @brief Mix-inされているか調べる
	*
	* @param md Mix-inされている調べたいクラスオブジェクト
	*/
	bool is_inherited(const Any& md) const;

	/**
	* @brief メンバを順次取り出すIteratorを返す
	*
	* @code
	* Xfor2(key, value, frame.members()){
	*   puts(Xf("%s %s")(key, value).to_s().c_str());
	* }
	* @endcode
	*/
	Any members() const;

public:

	void marshal_new(const VMachine& vm);

	const Any& member(const ID& name, int_t*& mutate_count) const;

	void init_instance(HaveInstanceVariables* inst, const VMachine& vm, const Any& self) const;

	void mutate() const;

	ClassImpl* impl() const{ return (ClassImpl*)Any::impl(); }

protected:

	CFun def_and_return(const ID& name, const CFun& cfun) const{
		def(name, cfun);
		return cfun;
	}

public:

	/**
	* @brief 関数を定義する
	*
	* cls.fun("name", &foo); は cls.def("name", xtal::fun(&foo)); と同一
	*/
	template<class Fun, class Policy>
	CFun fun(const ID& name, Fun fun, const Policy& policy) const{
		return def_and_return(name, xtal::fun(fun, policy));
	}

	/**
	* @brief 関数を定義する
	*
	* cls.fun("name", &foo); は cls.def("name", xtal::fun(&foo)); と同一
	*/
	template<class Fun>
	CFun fun(const ID& name, Fun f) const{
		return fun(name, f, result);
	}

	/**
	* @brief 関数を定義する
	*
	* cls.method("name", &foo); は cls.def("name", xtal::method(&foo)); と同一
	*/
	template<class Fun, class Policy>
	CFun method(const ID& name, Fun fun, const Policy& policy) const{
		return def_and_return(name, xtal::method(fun, policy));
	}

	/**
	* @brief 関数を定義する
	*
	* cls.method("name", &foo); は cls.def("name", xtal::method(&foo)); と同一
	*/
	template<class Fun>
	CFun method(const ID& name, Fun fun) const{
		return method(name, fun, result);
	}
	
protected:

	struct init_tag{};
	
	static void make_place(Any*& p);

	static Class& make_impl(Any*& p);

	Class(const char* name, Any*& p, init_tag);

};

/**
* @brief C++のクラスに対応したクラス
*
* 一度構築されると、実行中ずっと保持される。
* TClass<Foo>::get()関数でそれを取得できる。
*/
template<class C>
class TClass : public Class{
public:

	/**
	* @brief 名前を与えて構築する
	*
	*/	
	TClass(const char* name = "")
		:Class(name, pinst_, init_tag()){}
	
	/**
	* @brief クラスを生成せず、nullを入れる
	*
	*/
	TClass(const Null&)
		:Class(null){}
				
	TClass(ClassImpl* p)
		:Class(p){}

private:

	static Any* pinst_;
	
	static TClass<C>& inst(){ 
		return *(TClass<C>*)pinst_;
	}

public:

	/**
	* @brief このクラスが既に構築されているか調べる
	*
	*/
	static bool exists(){
		return pinst_ != 0 && *pinst_;
	}

	/**
	* @brief 構築されたオブジェクトを取得する
	*
	*/
	static const TClass<C>& get(){
		XTAL_ASSERT(exists());
		return inst();
	}

	static const TClass<C>& get_uncheck(){
		return inst();
	}
	
	static void set(const TClass<C>& v){
		make_place(pinst_);
		inst() = v;
	}
	
	/**
	* @brief 指定したクラスと同じモノを設定する
	*
	*/
	static void conform_to(const Class& v){
		make_place(pinst_);
		inst() = (const TClass<C>&)v;
	}
	
public:
	
	/**
	* @brief メンバ変数へのポインタからゲッターを生成し、定義する
	*
	*/
	template<class T, class U, class Policy>
	CFun getter(const ID& name, T U::* v, const Policy&) const{
		typedef detail::getter<C, T> getter;
		getter data(v);
		return def_and_return(name, CFun(&detail::method0<getter, C*, const T&, Policy>::f, &data, sizeof(data), 0));
	}
	
	/**
	* @brief メンバ変数へのポインタからセッターを生成し、定義する
	*
	* Xtalでは、obj.name = 10; とするにはset_nameとset_を前置したメソッドを定義する必要があるため、
	* 単純なセッターを定義したい場合、set_xxxとすることを忘れないこと。
	*/
	template<class T, class U, class Policy>
	CFun setter(const ID& name, T U::* v, const Policy&) const{
		typedef detail::setter<C, T> setter;
		setter data(v);
		return def_and_return(name, CFun(&detail::method1<setter, C*, const T&, const T&, Policy>::f, &data, sizeof(data), 1));
	}
	
	/**
	* @brief メンバ変数へのポインタからゲッター、セッターを両方生成し、定義する
	*
	* cls.getter(name, var, policy);
	* cls.setter(String("set_").cat(name), v, policy);
	* と等しい	
	*/	
	template<class T, class U, class Policy>
	void var(const ID& name, T U::* v, const Policy& policy) const{
		getter(name, v, policy);
		setter(String("set_").cat(name), v, policy);
	}
	
	/**
	* @brief メンバ変数へのポインタからゲッターを生成し、定義する
	*
	*/
	template<class T, class U>
	CFun getter(const ID& name, T U::* v) const{
		return getter(name, v, result);
	}
	
	/**
	* @brief メンバ変数へのポインタからセッターを生成し、定義する
	*
	*/
	template<class T, class U>
	CFun setter(const ID& name, T U::* v) const{
		return setter(name, v, result);
	}
	
	/**
	* @brief メンバ変数へのポインタからゲッター、セッターを両方生成し、定義する
	*
	* cls.getter(name, v);
	* cls.setter(String("set_").cat(name), v);
	* と等しい	
	*/	
	template<class T, class U>
	void var(const ID& name, T U::* v) const{
		var(name, v, result);
	}
};

template<class C>
Any* TClass<C>::pinst_ = 0;

Class new_xclass(const Frame& outer, const Code& code, FrameCore* core);

class Instance : public Any{
public:
	
	Instance(const Class& c);
	
	Instance(InstanceImpl* p)
		:Any((AnyImpl*)p){}
	
	Instance(const Null&)
		:Any(null){}
	
	InstanceImpl* impl() const{ return (InstanceImpl*)Any::impl(); }
};

}
