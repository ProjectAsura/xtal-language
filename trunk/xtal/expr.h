
#pragma once

#include "codeimpl.h"
#include "constant.h"

namespace xtal{


/*

巡回サンプル

for(TList<Any>::Node* p = values.head; p; p = p->next){
	//p->value;
}

*/
template <class T>
struct TList{

	struct Node{
		T value;

		Node* next;
		Node* prev;

		Node(const T &val = T())
			:value(val), next(0), prev(0){}

		void *operator new(size_t size, RegionAlloc* r){ return r->allocate(size); }
		void operator delete(void *, RegionAlloc*){}
	};

	Node* head;
	Node* tail;
	int size;
	RegionAlloc* alloc;

	TList(RegionAlloc* alloc = 0)
		:head(0), tail(0), alloc(alloc), size(0){}

	void push_front(const T& v);

	void push_back(const T &v);

	void pop_back();
};

template <class T>
void TList<T>::push_front(const T &v){
	if(head){
		Node* p = new(alloc) Node(v);
		p->next = head;
		head->prev = p;
		head = p;
	}else{
		head = tail = new(alloc) Node(v);
	}
	size++;
}

template <class T>
void TList<T>::push_back(const T &v){
	if(head){
		Node* p = new(alloc) Node(v);
		p->prev = tail;
		tail->next = p;
		tail = p;
	}else{
		head = tail = new(alloc) Node(v);
	}
	size++;
}

template <class T>
void TList<T>::pop_back(){
	if(head){
		if(head==tail){
			head = tail = 0;
		}else{
			tail = tail->prev;
			tail->next = 0;
		}
		size--;
	}
}

template <class Key, class T>
struct TPairList{

	struct Node{
		Key key;
		T value;

		Node* next;
		Node* prev;

		Node(const Key &key = Key(), const T &val = T())
			:key(key), value(val), next(0), prev(0){}

		void *operator new(size_t size, RegionAlloc* r){ return r->allocate(size); }
		void operator delete(void *, RegionAlloc*){}
	};

	Node* head;
	Node* tail;
	int size;
	RegionAlloc* alloc;

	TPairList(RegionAlloc* alloc = 0)
		:head(0), tail(0), alloc(alloc), size(0){}

	void push_back(const Key& k, const T &v);

	void pop_back();
};

template <class Key, class T>
void TPairList<Key, T>::push_back(const Key& k, const T &v){
	if(head){
		Node* p = new(alloc) Node(k, v);
		p->prev = tail;
		tail->next = p;
		tail = p;
	}else{
		head = tail = new(alloc) Node(k, v);
	}
	size++;
}

template <class Key, class T>
void TPairList<Key, T>::pop_back(){
	if(head){
		if(head==tail){
			head = tail = 0;
		}else{
			tail = tail->prev;
			tail->next = 0;
		}
		size--;
	}
}

// 値を返す文法要素
struct Expr{	
	enum{ TYPE = __LINE__ };
	
	int_t type;
	int_t line;
	RegionAlloc* alloc;
	
	Expr(int_t type, int_t line)
		:type(type), line(line){}

	void *operator new(size_t size, RegionAlloc* a){ 
		void* p = a->allocate(size);
		((Expr*)p)->alloc = a;
		return p; 
	}
	
	void operator delete(void *, RegionAlloc*){}

	operator Expr*(){ return this; }
};

template<class T>
inline T* expr_cast(Expr* p){
	if(p && T::TYPE==p->type){
		return (T*)p;
	}
	return 0;
}

// 値を返さない文法要素
struct Stmt{
	enum{ TYPE = __LINE__ };
	
	int_t type;
	int_t line;
	RegionAlloc* alloc;

	Stmt(int_t type, int_t line)
		:type(type), line(line){}

	void *operator new(size_t size, RegionAlloc* a){ 
		void* p = a->allocate(size);
		((Expr*)p)->alloc = a;
		return p; 
	}
	
	void operator delete(void *, RegionAlloc*){}
	
	operator Stmt*(){ return this; }
};

template<class T>
inline T* stmt_cast(Stmt* p){
	if(p && T::TYPE==p->type){
		return (T*)p;
	}
	return 0;
}

struct ExprStmt : public Stmt{
	enum{ TYPE = __LINE__ };
	Expr* expr;
	ExprStmt(int_t line, Expr* expr)
		:Stmt(TYPE, line), expr(expr){}
};

struct PseudoVariableExpr : public Expr{
	enum{ TYPE = __LINE__ };
	int_t code;
	PseudoVariableExpr(int_t line, int_t code)
		:Expr(TYPE, line), code(code){}
};

struct CalleeExpr : public PseudoVariableExpr{
	enum{ TYPE = __LINE__ };
	CalleeExpr(int_t line)
		:PseudoVariableExpr(line, CODE_PUSH_CALLEE){ type = TYPE; }
};

struct ArgsExpr : public Expr{
	enum{ TYPE = __LINE__ };
	ArgsExpr(int_t line):Expr(TYPE, line){}
};

struct IntExpr : public Expr{
	enum{ TYPE = __LINE__ };
	int_t value;	
	IntExpr(int_t line, int_t value)
		:Expr(TYPE, line), value(value){}
};

struct FloatExpr : public Expr{
	enum{ TYPE = __LINE__ };
	float_t value;	
	FloatExpr(int_t line, float_t value)
		:Expr(TYPE, line), value(value){}
};

struct StringExpr : public Expr{ 
	enum{ TYPE = __LINE__ };
	int_t value;
	int_t kind;
	StringExpr(int_t line, int_t value, int_t kind = KIND_STRING)
		:Expr(TYPE, line), value(value), kind(kind){}
}; 

struct ArrayExpr : public Expr{
	enum{ TYPE = __LINE__ };
	TList<Expr*> values;
	ArrayExpr(int_t line):Expr(TYPE, line), values(alloc){}
};

struct MapExpr : public Expr{
	enum{ TYPE = __LINE__ };
	TPairList<Expr*, Expr*> values;
	MapExpr(int_t line):Expr(TYPE, line), values(alloc){}
};

struct BinExpr : public Expr{ 
	enum{ TYPE = __LINE__ };
	int_t code; 
	Expr* lhs; 
	Expr* rhs;	
	BinExpr(int_t line, int_t code, Expr* lhs = 0, Expr* rhs = 0)
		:Expr(TYPE, line), code(code), lhs(lhs), rhs(rhs){}
};

struct BinCompExpr : public BinExpr{ 
	enum{ TYPE = __LINE__ };
	BinCompExpr(int_t line, int_t code, Expr* lhs = 0, Expr* rhs = 0)
		:BinExpr(line, code, lhs, rhs){ type = TYPE; }
};

struct AndAndExpr : public Expr{
	enum{ TYPE = __LINE__ };
	Expr* lhs; 
	Expr* rhs;
	AndAndExpr(int_t line, Expr* lhs = 0, Expr* rhs = 0)
		:Expr(TYPE, line), lhs(lhs), rhs(rhs){}
};

struct OrOrExpr : public Expr{
	enum{ TYPE = __LINE__ };
	Expr* lhs; 
	Expr* rhs;
	OrOrExpr(int_t line, Expr* lhs = 0, Expr* rhs = 0)
		:Expr(TYPE, line), lhs(lhs), rhs(rhs){}
};

struct UnaExpr : public Expr{ 
	enum{ TYPE = __LINE__ };
	int_t code;
	Expr* expr;
	UnaExpr(int_t line, int_t code = 0, Expr* expr = 0)
		:Expr(TYPE, line), code(code), expr(expr){}
};

struct UnaStmt : public Stmt{ 
	enum{ TYPE = __LINE__ };
	int_t code;
	Expr* expr;
	UnaStmt(int_t line, int_t code = 0, Expr* expr = 0)
		:Stmt(TYPE, line), code(code), expr(expr){}
};

struct TerExpr : public Expr{ 
	enum{ TYPE = __LINE__ };
	Expr* first;
	Expr* second;
	Expr* third;
	TerExpr(int_t line, Expr* first = 0)
		:Expr(TYPE, line), first(first), second(0), third(0){}
};

struct ReturnStmt : public Stmt{
	enum{ TYPE = __LINE__ };
	TList<Expr*> exprs;
	ReturnStmt(int_t line)
		:Stmt(TYPE, line), exprs(alloc){}
};

struct YieldStmt : public Stmt{
	enum{ TYPE = __LINE__ };
	TList<Expr*> exprs;
	YieldStmt(int_t line)
		:Stmt(TYPE, line), exprs(alloc){}
};

struct AssertStmt : public Stmt{
	enum{ TYPE = __LINE__ };
	TList<Expr*> exprs;
	AssertStmt(int_t line)
		:Stmt(TYPE, line), exprs(alloc){}
};

struct OnceExpr : public Expr{
	enum{ TYPE = __LINE__ };
	Expr* expr;
	OnceExpr(int_t line, Expr* expr = 0)
		:Expr(TYPE, line), expr(expr){}
};

struct TryStmt : public Stmt{ 
	enum{ TYPE = __LINE__ };
	Stmt* try_stmt; 
	TList<int_t> catch_vars;
	bool on_heap;
	Stmt* catch_stmt; 
	Stmt* finally_stmt;	
	TryStmt(int_t line, Stmt* try_stmt = 0, Stmt* catch_stmt = 0, Stmt* finally_stmt = 0)
		:Stmt(TYPE, line), try_stmt(try_stmt), catch_vars(alloc), catch_stmt(catch_stmt), finally_stmt(finally_stmt){}
};

struct IfStmt : public Stmt{
	enum{ TYPE = __LINE__ };
	Expr* cond_expr; 
	Stmt* body_stmt; 
	Stmt* else_stmt;
	IfStmt(int_t line, Expr* cond_expr = 0, Stmt* body_stmt = 0, Stmt* else_stmt = 0)
		:Stmt(TYPE, line), cond_expr(cond_expr), body_stmt(body_stmt), else_stmt(else_stmt){}
};

struct WhileStmt : public Stmt{
	enum{ TYPE = __LINE__ };
	int_t label;
	Expr* cond_expr; 
	Stmt* body_stmt; 
	Stmt* next_stmt;
	Stmt* else_stmt;
	Stmt* nobreak_stmt;
	WhileStmt(int_t line, Expr* cond_expr = 0, Stmt* body_stmt = 0, Stmt* else_stmt = 0, Stmt* nobreak_stmt = 0)
		:Stmt(TYPE, line), label(0), cond_expr(cond_expr), body_stmt(body_stmt), else_stmt(else_stmt), nobreak_stmt(nobreak_stmt), next_stmt(0){}
};

struct FunExpr : public Expr{
	enum{ TYPE = __LINE__ };
	int_t kind;
	bool have_args;
	Stmt* stmt;
	TList<int_t> vars;
	bool on_heap;
	TPairList<int_t, Expr*> params;
	FunExpr(int_t line, int_t kind, Stmt* stmt = 0)
		:Expr(TYPE, line), kind(kind), stmt(stmt), vars(alloc), have_args(false), params(alloc){}
};

struct MultipleAssignStmt : public Stmt{
	enum{ TYPE = __LINE__ };
	bool define;
	TList<Expr*> lhs;
	TList<Expr*> rhs;
	MultipleAssignStmt(int_t line)
		:Stmt(TYPE, line), define(false), lhs(alloc), rhs(alloc){}
};

struct IncStmt : public Stmt{ 
	enum{ TYPE = __LINE__ };
	int_t code;
	Expr* lhs;
	IncStmt(int_t line, int_t code, Expr* lhs = 0)
		:Stmt(TYPE, line), lhs(lhs), code(code){}
};
	
struct InstanceVariableExpr : public Expr{
	enum{ TYPE = __LINE__ };
	int_t var; 
	InstanceVariableExpr(int_t line, int_t var = 0)
		:Expr(TYPE, line), var(var){}
};

struct MemberExpr : public Expr{
	enum{ TYPE = __LINE__ };
	Expr* lhs;
	int_t var;
	bool if_defined;
	MemberExpr(int_t line, Expr* lhs = 0, int_t var = 0)
		:Expr(TYPE, line), lhs(lhs), var(var), if_defined(false){}
};

struct CallExpr : public Expr{ 
	enum{ TYPE = __LINE__ };
	Expr* expr; 
	bool tail;
	TList<Expr*> ordered; 
	TPairList<int_t, Expr*> named;
	int_t result_flag;
	CallExpr(int_t line, Expr* expr = 0)
		:Expr(TYPE, line), expr(expr), tail(false), ordered(alloc), named(alloc), result_flag(0){}
};

struct SendExpr : public Expr{
	enum{ TYPE = __LINE__ };
	Expr* lhs;
	int_t var;
	bool tail;
	bool if_defined;
	int_t result_flag;
	SendExpr(int_t line, Expr* lhs = 0, int_t var = 0)
		:Expr(TYPE, line), lhs(lhs), var(var), tail(false), if_defined(false), result_flag(0){}
};

struct AssignStmt : public Stmt{
	enum{ TYPE = __LINE__ };
	Expr* lhs;
	Expr* rhs;
	AssignStmt(int_t line, Expr* lhs = 0, Expr* rhs = 0)
		:Stmt(TYPE, line), lhs(lhs), rhs(rhs){}
};
	
struct OpAssignStmt : public Stmt{
	enum{ TYPE = __LINE__ };
	int_t code;
	Expr* lhs;
	Expr* rhs;
	OpAssignStmt(int_t line, int_t code, Expr* lhs = 0, Expr* rhs = 0)
		:Stmt(TYPE, line), code(code), lhs(lhs), rhs(rhs){}
};

struct LocalExpr : public Expr{
	enum{ TYPE = __LINE__ };
	int_t var; 
	LocalExpr(int_t line, int_t var = 0)
		:Expr(TYPE, line), var(var){}
};

struct PushStmt : public Stmt{
	enum{ TYPE = __LINE__ };
	Expr* expr;
	PushStmt(int_t line, Expr* expr = 0)
		:Stmt(TYPE, line), expr(expr){}
};

struct PopExpr : public Expr{
	enum{ TYPE = __LINE__ }; 
	PopExpr(int_t line)
		:Expr(TYPE, line){}
};

struct DefineLocalStmt : public Stmt{
	enum{ TYPE = __LINE__ };
	int_t var; 
	Expr* rhs;
	bool set_object_name;
	DefineLocalStmt(int_t line, int_t var = 0, Expr* rhs = 0, bool set_object_name = false)
		:Stmt(TYPE, line), var(var), rhs(rhs), set_object_name(set_object_name){}
};

struct DefineMemberStmt : public Stmt{
	enum{ TYPE = __LINE__ };
	Expr* lhs;
	int_t  var; 
	Expr* rhs;
	DefineMemberStmt(int_t line, Expr* lhs = 0, int_t var = 0, Expr* rhs = 0)
		:Stmt(TYPE, line), lhs(lhs), var(var), rhs(rhs){}
};

struct AtExpr : public Expr{
	enum{ TYPE = __LINE__ };
	Expr* lhs;
	Expr* index;
	AtExpr(int_t line, Expr* lhs = 0, Expr* index = 0)
		:Expr(TYPE, line), lhs(lhs), index(index){}
};
	
struct BreakStmt : public Stmt{
	enum{ TYPE = __LINE__ };
	int_t var; 
	BreakStmt(int_t line, int_t var = 0)
		:Stmt(TYPE, line), var(var){}
};

struct ContinueStmt : public Stmt{
	enum{ TYPE = __LINE__ };
	int_t var; 
	ContinueStmt(int_t line, int_t var = 0)
		:Stmt(TYPE, line), var(var){}
};

struct BlockStmt : public Stmt{
	enum{ TYPE = __LINE__ };
	TList<int_t> vars;
	bool on_heap;
	TList<Stmt*> stmts;
	BlockStmt(int_t line)
		:Stmt(TYPE, line), vars(alloc), stmts(alloc){}
};

struct FrameExpr : public Expr{
	enum{ TYPE = __LINE__ };
	TList<int_t> vars;
	bool on_heap;
	TList<Stmt*> stmts;
	int_t kind;
	FrameExpr(int_t line, int_t kind)
		:Expr(TYPE, line), vars(alloc), stmts(alloc), kind(kind){}
};

struct ClassExpr : public FrameExpr{
	enum{ TYPE = __LINE__ };
	TList<int_t> inst_vars;
	TList<Expr*> mixins;
	ClassExpr(int_t line)
		:FrameExpr(line, KIND_CLASS), inst_vars(alloc), mixins(alloc){ type = TYPE; }
};

struct TopLevelStmt : public Stmt{
	enum{ TYPE = __LINE__ };
	TList<int_t> vars;
	bool on_heap;
	TList<Stmt*> stmts;
	Expr* export_expr;
	Stmt* unittest_stmt;
	TopLevelStmt(int_t line)
		:Stmt(TYPE, line), vars(alloc), stmts(alloc), export_expr(0), unittest_stmt(0){}
};

}
