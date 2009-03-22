#include "xtal.h"
#include "xtal_macro.h"

namespace xtal{ namespace xpeg{

/**
* @brief �ꕶ���Âǂ�ŏ������Ă����̂ɓK�������\�b�h��񋟂���N���X
*/
class Scanner : public Base{

	enum{
		ONE_BLOCK_SHIFT = 8,
		ONE_BLOCK_SIZE = 1<<ONE_BLOCK_SHIFT,
		ONE_BLOCK_MASK = ONE_BLOCK_SIZE-1
	};

public:

	Scanner();

	~Scanner();

	typedef Executor::State State;

	/**
	* @brief �}�[�N������
	*/
	State save(){
		State state;
		state.lineno = lineno_;
		state.pos = pos_;
		return state;
	}

	/**
	* @brief �}�[�N��t�����ʒu�ɖ߂�
	*/
	void load(const State& state){
		pos_ = state.pos;
		lineno_ = state.lineno;
	}

	/**
	* @brief ���݂̈ʒu��Ԃ�
	*/
	uint_t pos(){
		return pos_;
	}

	/**
	* @brief ���݂̍s����Ԃ�
	*/
	uint_t lineno(){
		return lineno_;
	}

	/**
	* @brief n��̗v�f��`������
	*/
	const AnyPtr& peek(uint_t n = 0);
	
	/**
	* @brief �ЂƂǂݎ��
	*/
	const AnyPtr& read();

	bool bos(){
		return pos()==0;
	}

	bool eos(){
		return raweq(peek(), undefined);
	}

	bool bol(){
		if(pos_==0){
			return true;
		}

		const AnyPtr& ch = access(pos_-1);
		return raweq(ch, n_ch_) || raweq(ch, r_ch_);
	}

	bool eol(){
		const AnyPtr& ch = peek();
		return raweq(ch, r_ch_) || raweq(ch, n_ch_);
	}

	void skip(uint_t n){
		for(uint_t i=0; i<n; ++i){
			read();
		}
	}

	void skip_eol(){
		const AnyPtr& ch = peek();
		if(raweq(ch, r_ch_)){
			if(raweq(peek(1), n_ch_)){
				skip(2);
			}
			else{
				skip(1);
			}
		}
		else if(raweq(ch, n_ch_)){
			skip(1);
		}
	}

public:

	ArrayPtr capture_values(int_t begin, int_t end);
	
	ArrayPtr capture_values(int_t begin);
	
	StringPtr capture(int_t begin, int_t end);

	StringPtr capture(int_t begin);

	bool eat_capture(int_t begin, int_t end);

protected:

	virtual int_t do_read(AnyPtr* buffer, int_t max) = 0;

	virtual void visit_members(Visitor& m){
		Base::visit_members(m);
		m & mm_;
	}

	void expand();

	AnyPtr& access(uint_t pos){
		return begin_[pos>>ONE_BLOCK_SHIFT][pos&ONE_BLOCK_MASK];
	}

private:

	IDPtr n_ch_;
	IDPtr r_ch_;
	
	MemoryStreamPtr mm_;
	AnyPtr** begin_;
	uint_t num_;
	uint_t pos_;
	uint_t read_;
	uint_t lineno_;
};

class StreamScanner : public Scanner{
public:

	StreamScanner(const StreamPtr& stream)
		:stream_(stream){}

	virtual int_t do_read(AnyPtr* buffer, int_t max){
		return stream_->read_charactors(buffer, max);
	}

private:
	StreamPtr stream_;

	virtual void visit_members(Visitor& m){
		Scanner::visit_members(m);
		m & stream_;
	}
};

class IteratorScanner : public Scanner{
public:

	IteratorScanner(const AnyPtr& iter);

	virtual int_t do_read(AnyPtr* buffer, int_t max);

private:
	AnyPtr iter_;

	virtual void visit_members(Visitor& m){
		Scanner::visit_members(m);
		m & iter_;
	}
};

Scanner::Scanner(){
	num_ = 0;
	begin_ = 0;

	mm_ = xnew<MemoryStream>();
	pos_ = 0;
	read_ = 0;

	n_ch_ = XTAL_STRING("\n");
	r_ch_ = XTAL_STRING("\r");

	lineno_ = 1;

	expand();
}

Scanner::~Scanner(){
	for(uint_t i=0; i<num_; ++i){
		xfree(begin_[i], sizeof(AnyPtr)*ONE_BLOCK_SIZE);
	}
	xfree(begin_, sizeof(AnyPtr*)*num_);
}

const AnyPtr& Scanner::peek(uint_t n){
	while(pos_+n >= read_){
		uint_t now_read = 0;

		if((read_>>ONE_BLOCK_SHIFT)==num_){
			expand();
		}

		now_read = do_read(&access(read_), ONE_BLOCK_SIZE-(read_&ONE_BLOCK_MASK));

		if(now_read==0){
			return undefined;
		}

		read_ += now_read;
	}
	
	return access(pos_+n);
}

const AnyPtr& Scanner::read(){
	const AnyPtr& ret = peek();
	if(raweq(ret, r_ch_)){
		if(rawne(peek(1), n_ch_)){
			lineno_++;
		}
	}
	else if(raweq(ret, n_ch_)){
		lineno_++;
	}

	pos_ += 1;
	return  ret;
}

ArrayPtr Scanner::capture_values(int_t begin, int_t end){
	ArrayPtr ret = xnew<Array>();
	for(int_t i=begin; i<end; ++i){
		ret->push_back(access(i));
	}
	return ret;
}

ArrayPtr Scanner::capture_values(int_t begin){
	ArrayPtr ret = xnew<Array>();
	int_t saved = pos_;
	pos_ = begin;
	while(!eos()){
		ret->push_back(read());
	}
	pos_ = saved;
	return ret;
}
	
StringPtr Scanner::capture(int_t begin, int_t end){
	mm_->clear();
	for(int_t i=begin; i<end; ++i){
		mm_->put_s(access(i)->to_s());
	}
	return mm_->to_s();
}

StringPtr Scanner::capture(int_t begin){
	mm_->clear();
	int_t saved = pos_;
	pos_ = begin;
	while(!eos()){
		mm_->put_s(read()->to_s());
	}
	pos_ = saved;
	return mm_->to_s();
}

bool Scanner::eat_capture(int_t begin, int_t end){
	for(int_t i=begin; i<end; ++i){
		if(rawne(peek(i-begin), access(i))){
			return false;
		}
	}
	skip(end-begin);
	return true;
}

void Scanner::expand(){
	uint_t newnum = num_ + 1;
	AnyPtr** newp = (AnyPtr**)xmalloc(sizeof(AnyPtr*)*newnum);

	if(begin_){
		std::memcpy(newp, begin_, sizeof(AnyPtr*)*num_);
	}

	newp[num_] = (AnyPtr*)xmalloc(sizeof(AnyPtr)*ONE_BLOCK_SIZE);
	std::memset(newp[num_], 0, sizeof(AnyPtr)*ONE_BLOCK_SIZE);

	xfree(begin_, sizeof(AnyPtr*)*num_);
	begin_ = newp;
	num_ = newnum;
}


IteratorScanner::IteratorScanner(const AnyPtr& iter)
	:iter_(iter->send(Xid(each))){}

int_t IteratorScanner::do_read(AnyPtr* buffer, int_t max){
	if(!iter_){
		return 0;
	}

	const VMachinePtr& vm = vmachine();
	for(int_t i=0; i<max; ++i){
		vm->setup_call(2);
		iter_->rawsend(vm, Xid(block_next));
		iter_ = vm->result(0);
		if(!iter_){
			vm->cleanup_call();
			return i;
		}
		buffer[i] = vm->result(1);
		vm->cleanup_call();
	}
	return max;
}








AnyPtr concat(const AnyPtr&, const AnyPtr&);
ElementPtr elem(const AnyPtr& a);



////////////////////////////////////////////////////////////////////////

struct Element : public Base{

	enum Type{
		TYPE_INVALID, // ��
		TYPE_ANY, // �I�������ȊO
		TYPE_BOS, // beginning of stream
		TYPE_EOS, // end of stream
		TYPE_BOL, // beginning of line
		TYPE_EOL, // end of line
		TYPE_BACKREF, // ����Q��

		// �ȉ�param1��Any
		TYPE_EQL,
		TYPE_PRED,
		TYPE_CALL,
		TYPE_RANGE,

		// �ȉ�param1��Set�ł�����
		TYPE_CH_SET,

		// �ȉ�param1��Element�ł�����
		TYPE_GREED,
		TYPE_LOOKAHEAD,
		TYPE_LOOKBEHIND,
		TYPE_LEAF,
		TYPE_NODE,
		TYPE_ERROR,

		////////////////////////////////

		TYPE_CONCAT, // >>
		TYPE_OR, // |
		TYPE_MORE0, // *0
		TYPE_MORE1, // *1
		TYPE_01,  // *-1
		TYPE_EMPTY, // ��
		TYPE_CAP, // �L���v�`��
		TYPE_DECL, // �錾
	};

	Type type;
	AnyPtr param1;
	AnyPtr param2;
	int_t param3;
	bool inv;

	Element(Type type, const AnyPtr& param1 = null, const AnyPtr& param2 = null, int_t param3 = 0);

	virtual void visit_members(Visitor& m){
		Base::visit_members(m);
		m & param1 & param2;
	}
};

Element::Element(Type type, const AnyPtr& param1, const AnyPtr& param2, int_t param3)
	:type(type), param1(param1), param2(param2), param3(param3), inv(false){}

////////////////////////////////////////////////////////////////////////

struct Trans : public Base{
	ElementPtr ch;
	int to;
	SmartPtr<Trans> next;

	virtual void visit_members(Visitor& m){
		Base::visit_members(m);
		m & ch & next;
	}
};	

////////////////////////////////////////////////////////////////////////

struct NFA : public Base{

	NFA(const ElementPtr& node);

	void add_transition(int from, const AnyPtr& ch, int to);

	void gen_nfa(int entry, const AnyPtr& t, int exit, int depth);

	void add_e_transition(int from, int to){
		add_transition(from, e, to);
	}

	void printn(const char* str, int depth){
		//for(int i=0; i<depth; ++i){
		//	printf("%s", " ");
		//}
		//printf("%s\n", str);
	}
	
	struct State{
		TransPtr trans;
		int_t capture_kind;
		IDPtr capture_name;
	};

	int gen_state(){
		State state;
		state.capture_kind = 0;
		states.push_back(state);
		return states.size() - 1;
	}

	ElementPtr e;
	ElementPtr root_node;
	ArrayList<State> states;
	uint_t cap_max_;
	ArrayPtr cap_list_;

	enum{
		CAPTURE_NONE = 0,
		CAPTURE_BEGIN = 1,
		CAPTURE_END = 2,
	};
};
	
enum{ NFA_STATE_START = 0, NFA_STATE_FINAL = 1 };

NFA::NFA(const ElementPtr& node){
	e = xnew<Element>(Element::TYPE_INVALID);

	root_node = node;
	cap_max_ = 0;
	cap_list_ = xnew<Array>();

	gen_state(); // NFA_STATE_START
	gen_state(); // NFA_STATE_FINAL
	gen_nfa(NFA_STATE_START, node, NFA_STATE_FINAL, 0);
}

void NFA::add_transition(int from, const AnyPtr& ch, int to){
	TransPtr x = xnew<Trans>();
	x->to = to;
	x->ch = ptr_cast<Element>(ch);
	x->next = states[from].trans;
	states[from].trans = x;
}

void NFA::gen_nfa(int entry, const AnyPtr& a, int exit, int depth){
	const ElementPtr& t = unchecked_ptr_cast<Element>(a);

	switch(t->type){
		XTAL_DEFAULT{
			printn("DEFAULT", depth);
			//         ch
			//  entry -----> exit
			add_transition(entry, t, exit);
		}

		XTAL_CASE(Element::TYPE_CONCAT){
			printn("CONCAT", depth);
			//         left         right
			//  entry ------> step -------> exit

			int step = gen_state();
			gen_nfa(entry, t->param1, step, depth+1);
			gen_nfa(step, t->param2, exit, depth+1);
		}

		XTAL_CASE(Element::TYPE_OR){
			printn("OR", depth);
			//               left
			//        ----------------->
			//  entry -----> step -----> exit
			//          e         right

			int step = gen_state();
			gen_nfa(entry, t->param1, exit, depth+1);
			add_e_transition(entry, step);
			gen_nfa(step, t->param2, exit, depth+1);
		}

		XTAL_CASE2(Element::TYPE_MORE0, Element::TYPE_MORE1){
			printn("MORE", depth);
			//                       e
			//         e          <------        e
			//  entry ---> before ------> after ---> exit
			//    |                left                ^
			//    >------->------------------->------>-|
			//                      e
			//----------------------------------------------
			//                       e
			//         e          <------        e
			//  entry ---> before ------> after ---> exit
			//                     left
			int before = gen_state();
			int after = gen_state();
			
			if(t->param3==1 || t->param3==2){
				// exit�Ɍ����������D��
				if(t->type == Element::TYPE_MORE0){ add_e_transition(entry, exit); }
				add_e_transition(entry, before);

				// exit�Ɍ����������D��
				add_e_transition(after, exit);
				add_e_transition(after, before);
			}
			else{
				// before�Ɍ����������D��
				add_e_transition(entry, before);
				if(t->type == Element::TYPE_MORE0){ add_e_transition(entry, exit); }

				// before�Ɍ����������D��
				add_e_transition(after, before);
				add_e_transition(after, exit);
			}

			// before����after�ւ̑J�� 
			gen_nfa(before, t->param1, after, depth+1);
		}

		XTAL_CASE(Element::TYPE_01){
			printn("01", depth);
			//           e
			//        ------>
			//  entry ------> exit
			//         left

			if(t->param3==1){
				// e���o�R��������D��
				add_e_transition(entry, exit);
				gen_nfa(entry, t->param1, exit, depth+1);
			}
			else{
				// left���o�R��������D��
				gen_nfa(entry, t->param1, exit, depth+1);
				add_e_transition(entry, exit);
			}
		}

		XTAL_CASE(Element::TYPE_EMPTY){
			printn("EMPTY", depth);
			//         e
			//  entry ---> exit
			add_e_transition(entry, exit);
		}

		XTAL_CASE(Element::TYPE_CAP){
			printn("CAP", depth);
			int before = gen_state();
			int after = gen_state();

			states[before].capture_kind = CAPTURE_BEGIN;
			states[after].capture_kind = CAPTURE_END;
			states[before].capture_name = unchecked_ptr_cast<ID>(t->param2);
			states[after].capture_name = unchecked_ptr_cast<ID>(t->param2);
			cap_list_->push_back(t->param2);
			cap_max_++;

			add_e_transition(entry, before);
			gen_nfa(before, t->param1, after, depth+1);
			add_e_transition(after, exit);
		}

		XTAL_CASE(Element::TYPE_DECL){
			printn("DECL", depth);
			gen_nfa(entry, t->param1, exit, depth+1);
		}
	}
}

////////////////////////////////////////////////////////////////////////

const NFAPtr& Executor::fetch_nfa(const ElementPtr& node){
	if(!nfa_map_){
		nfa_map_ = xnew<Map>();	
	}
	
	const AnyPtr& temp = nfa_map_->at(node);
	if(temp){
		return unchecked_ptr_cast<NFA>(temp);
	}
	else{
		nfa_map_->set_at(node, xnew<NFA>(node));
		return unchecked_ptr_cast<NFA>(nfa_map_->at(node));
	}
}

void Executor::reset(const AnyPtr& stream_or_iterator){
	if(stream_or_iterator->is(cpp_class<Stream>())){
		scanner_ = xnew<StreamScanner>(ptr_cast<Stream>(stream_or_iterator));
	}
	else if(stream_or_iterator->is(cpp_class<String>())){
		scanner_ = xnew<StreamScanner>(xnew<StringStream>(ptr_cast<String>(stream_or_iterator)));
	}
	else{
		scanner_ = xnew<IteratorScanner>(stream_or_iterator);
	}

	cap_ = xnew<Map>();
	tree_ = xnew<TreeNode>();
	errors_ = null;
	begin_ = 0;
	match_begin_ = 0;
	match_end_ = 0;
}

bool Executor::match(const AnyPtr& pattern){
	const NFAPtr& nfa = fetch_nfa(elem(pattern));
	begin_ = scanner_->pos();
	for(;;){
		match_begin_ = scanner_->pos();
		if(match_inner(nfa)){
			match_end_ = scanner_->pos();
			return !errors_;
		}

		if(scanner_->eos()){
			return false;
		}

		scanner_->read();
	}
}

bool Executor::parse(const AnyPtr& pattern){
	return match_inner(fetch_nfa(elem(pattern))) && errors_->empty();
}

AnyPtr Executor::captures(){
	MapPtr ret = xnew<Map>();

	ret->set_at(empty_id, at(empty_string));
	Xfor2(k, v, cap_){
		XTAL_UNUSED_VAR(v);
		const StringPtr& k2 = unchecked_ptr_cast<String>(k);
		ret->set_at(k2, at(k2));
	}

	return ret->each();
}

AnyPtr Executor::captures_values(){
	MapPtr ret = xnew<Map>();

	ret->set_at(empty_id, at(empty_string));
	Xfor2(k, v, cap_){
		XTAL_UNUSED_VAR(v);
		const StringPtr& k2 = unchecked_ptr_cast<String>(k);
		ret->set_at(k2, call(k2));
	}

	return ret->each();
}

StringPtr Executor::at(const StringPtr& key){
	if(raweq(key, empty_id)){
		return unchecked_ptr_cast<Scanner>(scanner_)->capture(match_begin_, match_end_);
	}
	else{
		const SmartPtr<Cap>& temp = unchecked_ptr_cast<Cap>(cap_->at(key));

		if(temp->end>=0 && temp->end-temp->begin>0){
			return scanner_->capture(temp->begin, temp->end);
		}
		else{
			if(temp->end==temp->begin){
				return empty_string;
			}
			else{
				return null;
			}
		}
	}
}

AnyPtr Executor::call(const StringPtr& key){
	if(raweq(key, empty_id)){
		return unchecked_ptr_cast<Scanner>(scanner_)->capture_values(match_begin_, match_end_);
	}
	else{		
		const SmartPtr<Cap>& temp = unchecked_ptr_cast<Cap>(cap_->at(key));

		if(temp->end>=0 && temp->end-temp->begin>0){
			return scanner_->capture_values(temp->begin, temp->end);
		}
		else{
			if(temp->end==temp->begin){
				return xnew<Array>();
			}
			else{
				return null;
			}
		}
	}
}

StringPtr Executor::prefix(){
	return unchecked_ptr_cast<Scanner>(scanner_)->capture(begin_, match_begin_);
}

StringPtr Executor::suffix(){
	return unchecked_ptr_cast<Scanner>(scanner_)->capture(match_end_);
}

AnyPtr Executor::prefix_values(){
	return unchecked_ptr_cast<Scanner>(scanner_)->capture_values(begin_, match_begin_)->each();
}

AnyPtr Executor::suffix_values(){
	return unchecked_ptr_cast<Scanner>(scanner_)->capture_values(match_end_)->each();
}

const AnyPtr& Executor::read(){
	return scanner_->read();
}

const AnyPtr& Executor::peek(uint_t n){
	return scanner_->peek(n);
}

const StringPtr& Executor::peek_s(uint_t n){
	const AnyPtr& ret = peek(n);
	if(raweq(ret, undefined)){
		return empty_string;
	}
	return unchecked_ptr_cast<String>(ret);
}

int_t Executor::peek_ascii(uint_t n){
	const AnyPtr& ret = peek(n);
	if(raweq(ret, undefined)){
		return -1;
	}
	return unchecked_ptr_cast<String>(ret)->ascii();
}

const StringPtr& Executor::read_s(){
	const AnyPtr& ret = read();
	if(raweq(ret, undefined)){
		return empty_string;
	}
	return unchecked_ptr_cast<String>(ret);
}

int_t Executor::read_ascii(){
	const AnyPtr& ret = read();
	if(raweq(ret, undefined)){
		return -1;
	}
	return unchecked_ptr_cast<String>(ret)->ascii();		
}

uint_t Executor::lineno(){
	return scanner_->lineno();
}

bool Executor::bos(){
	return scanner_->bos();
}

bool Executor::eos(){
	return scanner_->eos();
}

bool Executor::bol(){
	return scanner_->bol();
}

bool Executor::eol(){
	return scanner_->eol();
}

bool Executor::eat(const AnyPtr& v){
	if(raweq(peek(), v)){
		skip();
		return true;
	}
	return false;
}

bool Executor::eat_ascii(int_t ch){
	if(peek_s()->ascii()==ch){
		skip();
		return true;
	}
	return false;
}

void Executor::skip_eol(){
	return scanner_->skip_eol();
}

void Executor::skip(uint_t n){
	scanner_->skip(n);
}

void Executor::skip(){
	scanner_->read();
}

void Executor::error(const AnyPtr& message, int_t line){
	if(!errors_){
		errors_ = xnew<Array>();
	}

	if(errors_->size()<10){
		errors_->push_back(Xf("%(lineno)d:%(message)s")->call(
			Named(Xid(lineno), line==0 ? lineno() : line),
			Named(Xid(message), message)
		));
	}
}

void Executor::push(uint_t mins, uint_t cur_state, uint_t nodes, const State& pos){
	for(uint_t i=mins, sz=stack_.size(); i<sz; ++i){
		if(stack_[i].pos.pos != pos.pos){
			break;
		}
		else if(stack_[i].state == cur_state){
			return;
		}
	}

	StackInfo temp = {cur_state, nodes, pos};
	stack_.push(temp);
}

bool Executor::match_inner(const AnyPtr& anfa){
	const NFAPtr& nfa = unchecked_ptr_cast<NFA>(anfa);

	int_t nodenum = tree_->size();
	uint_t mins = stack_.size();

	for(uint_t i=0, sz=nfa->cap_list_->size(); i<sz; ++i){
		cap_->set_at(nfa->cap_list_->at(i), xnew<Cap>());
	}

	bool match = false;
	State match_pos = {0, 0};
	State first_pos = scanner_->save();

	push(mins, NFA_STATE_START, nodenum, first_pos);

	while(stack_.size()>mins){
		StackInfo& se = stack_.pop();
		int cur_state = se.state;
		
		State pos = se.pos;
		NFA::State& state = nfa->states[cur_state];

		if(cur_state == NFA_STATE_FINAL && match_pos.pos <= pos.pos){
			match_pos = pos;
			match = true;
		}

		bool fail = true;
		for(const TransPtr* tr=&state.trans; *tr; tr=&(*tr)->next){
			scanner_->load(pos);

			if(se.nodes<tree_->size()){
				tree_->resize(se.nodes);
			}

			if(test((*tr)->ch)){
				push(mins, (*tr)->to, tree_->size(), scanner_->save());
				fail = false;
			}
		}

		if(fail){
			if(match){
				break;
			}
		}
		else{
			switch(state.capture_kind){
				XTAL_NODEFAULT;
				XTAL_CASE(NFA::CAPTURE_NONE){}

				XTAL_CASE(NFA::CAPTURE_BEGIN){
					const SmartPtr<Cap>& temp = unchecked_ptr_cast<Cap>(cap_->at(state.capture_name));
					temp->begin = pos.pos;
					temp->end = -1;
				}

				XTAL_CASE(NFA::CAPTURE_END){
					const SmartPtr<Cap>& temp = unchecked_ptr_cast<Cap>(cap_->at(state.capture_name));
					temp->end = pos.pos;
				}
			}
		}
	}

	stack_.downsize_n(mins);

	if(match){
		scanner_->load(match_pos);
		return true;
	}

	tree_->resize(nodenum);

	scanner_->load(first_pos);
	return false;
}

bool Executor::test(const AnyPtr& ae){
	const ElementPtr& e = unchecked_ptr_cast<Element>(ae);

	switch(e->type){
		XTAL_NODEFAULT;

		case Element::TYPE_CONCAT:
		case Element::TYPE_OR:
		case Element::TYPE_MORE0:
		case Element::TYPE_MORE1:
		case Element::TYPE_01:
		case Element::TYPE_EMPTY:
		case Element::TYPE_CAP:
		case Element::TYPE_DECL:
			XTAL_ASSERT(false);
			break;

		XTAL_CASE(Element::TYPE_INVALID){
			return !e->inv;
		}

		XTAL_CASE(Element::TYPE_ANY){
			if(scanner_->eos()){ return e->inv; }
			scanner_->read();
			return !e->inv;
		}

		XTAL_CASE(Element::TYPE_BOS){
			return scanner_->bos()!=e->inv;
		}

		XTAL_CASE(Element::TYPE_EOS){
			return scanner_->eos()!=e->inv;
		}

		XTAL_CASE(Element::TYPE_BOL){
			return scanner_->bol()!=e->inv;
		}

		XTAL_CASE(Element::TYPE_EOL){
			if(!scanner_->eol()){ return e->inv; }
			scanner_->skip_eol();
			return !e->inv;
		}

		XTAL_CASE(Element::TYPE_EQL){
			if(raweq(scanner_->read(), e->param1)){ return !e->inv; }
			return e->inv;
		}

		XTAL_CASE(Element::TYPE_RANGE){
			
		}
		
		XTAL_CASE(Element::TYPE_PRED){
			if(scanner_->eos()){ return false; }
			if(e->param1->call(scanner_->read())){ return !e->inv; }
			return e->inv;
		}

		XTAL_CASE(Element::TYPE_CH_SET){
			const MapPtr& data = unchecked_ptr_cast<Map>(e->param1);
			if(data->at(scanner_->read())){ return !e->inv; }
			return e->inv;
		}

		XTAL_CASE(Element::TYPE_CALL){
			if(scanner_->eos()){ return false; }
			AnyPtr ret = e->param1->call(to_smartptr(this));
			return (ret || raweq(ret, undefined))!=e->inv;
		}

		XTAL_CASE(Element::TYPE_GREED){
			const NFAPtr& nfa = fetch_nfa(unchecked_ptr_cast<Element>(e->param1));
			return match_inner(nfa)!=e->inv;
		}

		XTAL_CASE(Element::TYPE_LOOKAHEAD){
			const NFAPtr& nfa = fetch_nfa(unchecked_ptr_cast<Element>(e->param1));
			Scanner::State state = scanner_->save();
			bool ret = match_inner(nfa);
			scanner_->load(state);
			return ret!=e->inv;
		}

		XTAL_CASE(Element::TYPE_LOOKBEHIND){
			const NFAPtr& nfa = fetch_nfa(unchecked_ptr_cast<Element>(e->param1));
			Scanner::State state = scanner_->save();
			Scanner::State fict_state = state;
			fict_state.pos = fict_state.pos > (uint_t)e->param3 ? fict_state.pos-e->param3 : 0;
			scanner_->load(fict_state);
			bool ret = match_inner(nfa);
			scanner_->load(state);
			return ret!=e->inv;
		}

		XTAL_CASE(Element::TYPE_LEAF){
			const NFAPtr& nfa = fetch_nfa(unchecked_ptr_cast<Element>(e->param1));
			int_t pos = scanner_->pos();
			if(match_inner(nfa)){
				if(tree_){
					if(e->param3!=0){
						tree_->push_back(scanner_->capture_values(pos, scanner_->pos()));
					}
					else{
						tree_->push_back(scanner_->capture(pos, scanner_->pos()));
					}
				}
				return !e->inv;
			}
			return e->inv;
		}

		XTAL_CASE(Element::TYPE_NODE){
			const NFAPtr& nfa = fetch_nfa(unchecked_ptr_cast<Element>(e->param1));
			//int_t pos = scanner_->pos();
			if(tree_){
				int_t nodenum = tree_->size() - e->param3;
				if(nodenum<0){ nodenum = 0; }

				if(match_inner(nfa)){
					TreeNodePtr node = xnew<TreeNode>();
					node->set_tag(e->param2->to_s()->intern());
					node->set_lineno(scanner_->lineno());
					node->assign(tree_->splice(nodenum, tree_->size()-nodenum));
					tree_->push_back(node);
					return !e->inv;
				}
			}
			else{
				if(match_inner(nfa)){
					return !e->inv;
				}
			}
			return e->inv;
		}

		XTAL_CASE(Element::TYPE_BACKREF){
			const SmartPtr<Cap>& temp = unchecked_ptr_cast<Cap>(cap_->at(e->param1));
			if(temp && temp->end>=0 && temp->end-temp->begin>0){
				return (scanner_->eat_capture(temp->begin, temp->end))!=e->inv;
			}
			return e->inv;
		}

		XTAL_CASE(Element::TYPE_ERROR){
			if(errors_){
				errors_->push_back(e->param1->call(Named(Xid(line), scanner_->lineno())));
			}
			return !e->inv;
		}
	}

	return false;
}

////////////////////////////////////////////////////////////////////////

ElementPtr elem(const AnyPtr& a){
	if(const ElementPtr& p = ptr_cast<Element>(a)){
		return p;
	}

	if(const ChRangePtr& p = ptr_cast<ChRange>(a)){
		SetPtr chset = xnew<Set>();
		Xfor(v, p){
			chset->set_at(v, true);
		}
		return xnew<Element>(Element::TYPE_CH_SET, chset);
	}

	if(const StringPtr& p = ptr_cast<String>(a)){
		if(p->length()==0){
			return xnew<Element>(Element::TYPE_EMPTY);
		}
		
		if(p->length()==1){
			return xnew<Element>(Element::TYPE_EQL, p);
		}

		AnyPtr str = null;
		Xfor(v, p->each()){
			if(str){
				str = concat(str, v);
			}
			else{
				str = v;
			}
		}
		
		return elem(str);
	}

	if(const FunPtr& p = ptr_cast<Fun>(a)){
		return xnew<Element>(Element::TYPE_CALL, p);
	}

	XTAL_SET_EXCEPT(cpp_class<RuntimeError>()->call(Xt("Xtal Runtime Error 1026")));
	return null;
}

AnyPtr set(const StringPtr& str){
	SetPtr chset = xnew<Set>();
	Xfor(v, str){
		chset->set_at(v, true);
	}
	return xnew<Element>(Element::TYPE_CH_SET, chset);
}

AnyPtr call(const AnyPtr& fun){
	return xnew<Element>(Element::TYPE_CALL, fun);
}

AnyPtr select(const AnyPtr& left, const AnyPtr& right){
	ElementPtr eleft = elem(left);
	ElementPtr eright = elem(right);

	if((eleft->type==Element::TYPE_EQL || eleft->type==Element::TYPE_CH_SET) && 
		(eright->type==Element::TYPE_EQL || eright->type==Element::TYPE_CH_SET)){

		SetPtr chset = xnew<Set>();

		if(eleft->type==Element::TYPE_EQL){
			chset->set_at(eleft->param1, true);
		}

		if(eleft->type==Element::TYPE_CH_SET){
			Xfor(v, eleft->param1){
				chset->set_at(v, true);
			}
		}

		if(eright->type==Element::TYPE_EQL){
			chset->set_at(eright->param1, true);
		}

		if(eright->type==Element::TYPE_CH_SET){
			Xfor(v, eright->param1){
				chset->set_at(v, true);
			}
		}
		return xnew<Element>(Element::TYPE_CH_SET, chset);
	}

	return xnew<Element>(Element::TYPE_OR, eleft, eright); 
}

AnyPtr concat(const AnyPtr& left, const AnyPtr& right){ 
	return xnew<Element>(Element::TYPE_CONCAT, elem(left), elem(right)); 
}

AnyPtr more_Int(const AnyPtr& left, int_t n, int_t kind = 0){
	if(n==0){ return xnew<Element>(Element::TYPE_MORE0, elem(left), null, kind); }
	else if(n==1){ return xnew<Element>(Element::TYPE_MORE1, elem(left), null, kind); }
	else if(n==-1){ return xnew<Element>(Element::TYPE_01, elem(left), null, kind); }

	if(n>0){ return concat(left, more_Int(left, n-1, kind)); }
	else{ return concat(more_Int(left, -1, kind), more_Int(left, n+1, kind)); }
}

AnyPtr more_IntRange(const AnyPtr& left, const IntRangePtr& range, int_t kind = 0){
	if(range->begin()<=0){
		int n = -(range->end()-1);
		return n < 0 ? more_Int(left, n, kind) : xnew<Element>(Element::TYPE_EMPTY);
	}

	return concat(left, more_IntRange(left, xnew<IntRange>(range->begin()-1, range->end()-1, RANGE_LEFT_CLOSED_RIGHT_OPEN), kind));
}

AnyPtr more_normal_Int(const AnyPtr& left, int_t n){ return more_Int(left, n, 0); }
AnyPtr more_shortest_Int(const AnyPtr& left, int_t n){ return more_Int(left, n, 1); }
//AnyPtr more_greed_Int(const AnyPtr& left, int_t n){ return more_Int(left, n, 2); }
AnyPtr more_greed_Int(const AnyPtr& left, int_t n){ return xnew<Element>(Element::TYPE_GREED, more_normal_Int(left, n)); }
AnyPtr more_normal_IntRange(const AnyPtr& left, const IntRangePtr& range){ return more_IntRange(left, range, 0); }
AnyPtr more_shortest_IntRange(const AnyPtr& left, const IntRangePtr& range){ return more_IntRange(left, range, 1); }
//AnyPtr more_greed_IntRange(const AnyPtr& left, const IntRangePtr& range){ return more_IntRange(left, range, 2); }
AnyPtr more_greed_IntRange(const AnyPtr& left, const IntRangePtr& range){ return xnew<Element>(Element::TYPE_GREED, more_normal_IntRange(left, range)); }

AnyPtr inv(const AnyPtr& left){
	ElementPtr e = elem(left);
	ElementPtr ret = xnew<Element>(e->type, e->param1, e->param2, e->param3);
	ret->inv = !e->inv;
	return ret;
}

AnyPtr lookahead(const AnyPtr& left){ return xnew<Element>(Element::TYPE_LOOKAHEAD, elem(left)); }
AnyPtr lookbehind(const AnyPtr& left, int_t back){ return xnew<Element>(Element::TYPE_LOOKBEHIND, elem(left), null, back); }

AnyPtr cap(const IDPtr& name, const AnyPtr& left){ return xnew<Element>(Element::TYPE_CAP, elem(left), name, 1); }

void cap_vm(const VMachinePtr& vm){
	if(vm->named_arg_count()==1 && vm->ordered_arg_count()==0){ 
		vm->return_result(cap(vm->arg_name(0), vm->arg(vm->arg_name(0)))); 
		return;
	}
	
	if(vm->ordered_arg_count()==2 && vm->named_arg_count()==0){ 
		vm->return_result(cap(ptr_cast<ID>(vm->arg(0)), vm->arg(1)));
		return;
	}

	XTAL_SET_EXCEPT(cpp_class<ArgumentError>()->call(Xt("Xtal Runtime Error 1027")));
}

AnyPtr node(const AnyPtr& left){ return xnew<Element>(Element::TYPE_NODE, elem(left)); }
AnyPtr node(const IDPtr& name, const AnyPtr& left){ return xnew<Element>(Element::TYPE_NODE, elem(left), name); }

void node_vm(const VMachinePtr& vm){
	if(vm->named_arg_count()!=0){ vm->return_result(node(vm->arg_name(0), vm->arg(vm->arg_name(0)))); }
	else{ 
		if(vm->ordered_arg_count()==2){ vm->return_result(node(ptr_cast<ID>(vm->arg(0)), vm->arg(1))); }
		else{ vm->return_result(node(vm->arg(0))); }
	}
}

AnyPtr splice_node(int_t num, const AnyPtr& left){ return xnew<Element>(Element::TYPE_NODE, elem(left), null, num); }
AnyPtr splice_node(int_t num, const IDPtr& name, const AnyPtr& left){ return xnew<Element>(Element::TYPE_NODE, elem(left), name, num); }

void splice_node_vm(const VMachinePtr& vm){
	if(vm->named_arg_count()!=0){ vm->return_result(splice_node(vm->arg(0)->to_i(), vm->arg_name(0), vm->arg(vm->arg_name(0)))); }
	else{ 
		if(vm->ordered_arg_count()==3){ vm->return_result(splice_node(vm->arg(0)->to_i(), ptr_cast<ID>(vm->arg(1)), vm->arg(2))); }
		else{ vm->return_result(splice_node(vm->arg(0)->to_i(), vm->arg(0))); }
	}
}

AnyPtr leaf(const AnyPtr& left){ return xnew<Element>(Element::TYPE_LEAF, elem(left)); }
AnyPtr leafs(const AnyPtr& left){ return xnew<Element>(Element::TYPE_LEAF, elem(left), null, 1); }
AnyPtr back_ref(const AnyPtr& n){ return xnew<Element>(Element::TYPE_BACKREF, n); }

AnyPtr decl(){ return xnew<Element>(Element::TYPE_DECL); }
void set_body(const ElementPtr& x, const AnyPtr& term){ if(x->type==Element::TYPE_DECL) x->param1 = elem(term); }

//AnyPtr bound(const AnyPtr& body, const AnyPtr& sep){ return lookbehind(sep, 1) >> body >> lookahead(sep); }
AnyPtr error(const AnyPtr& fn){ return xnew<Element>(Element::TYPE_ERROR, fn); }
AnyPtr pred(const AnyPtr& e){ return xnew<Element>(Element::TYPE_PRED, e); }
	
}

void bind_xpeg(const ClassPtr& xpeg){
	using namespace xpeg;

	{
		ClassPtr p = cpp_class<Executor>();
		p->set_object_name(Xid(Executor));
		p->def_ctor(ctor<Executor, const AnyPtr&>()->param(1, Xid(stream_or_iterator), empty_string));
		p->def_method(Xid(reset), &Executor::reset);
		p->def_method(Xid(parse), &Executor::parse);
		p->def_method(Xid(match), &Executor::match);

		p->def_method(Xid(captures), &Executor::captures);
		p->def_method(Xid(captures_values), &Executor::captures_values);		
		p->def_method(Xid(op_at), &Executor::at, cpp_class<String>());
		p->def_method(Xid(op_call), &Executor::call, cpp_class<String>());
		p->def_method(Xid(prefix), &Executor::prefix);
		p->def_method(Xid(suffix), &Executor::suffix);
		p->def_method(Xid(prefix_values), &Executor::prefix_values);
		p->def_method(Xid(suffix_values), &Executor::suffix_values);
		p->def_method(Xid(errors), &Executor::errors);
		p->def_method(Xid(read), &Executor::read);
		p->def_method(Xid(peek), &Executor::peek)->param(1, Xid(n), 0);
		p->def_method(Xid(tree), &Executor::tree);
	}

	{
		ClassPtr p = cpp_class<Element>();
		p->set_object_name(Xid(Element));
		p->def_method(Xid(set_body), &set_body);
	}

	{
		ClassPtr p = xnew<Class>();
		p->def_method(Xid(op_mod), &more_shortest_Int, cpp_class<Int>());
		p->def_method(Xid(op_mod), &more_shortest_IntRange, cpp_class<IntRange>());
		p->def_method(Xid(op_div), &more_normal_Int, cpp_class<Int>());
		p->def_method(Xid(op_div), &more_normal_IntRange, cpp_class<IntRange>());
		p->def_method(Xid(op_mul), &more_greed_Int, cpp_class<Int>());
		p->def_method(Xid(op_mul), &more_greed_IntRange, cpp_class<IntRange>());
		p->def_method(Xid(op_com), &inv);
		
		p->def_method(Xid(op_or), &select, cpp_class<Element>());
		p->def_method(Xid(op_or), &select, cpp_class<String>());
		p->def_method(Xid(op_or), &select, cpp_class<ChRange>());
		p->def_method(Xid(op_or), &select, cpp_class<Fun>());
		p->def_method(Xid(op_shr), &concat, cpp_class<Element>());
		p->def_method(Xid(op_shr), &concat, cpp_class<String>());
		p->def_method(Xid(op_shr), &concat, cpp_class<ChRange>());
		p->def_method(Xid(op_shr), &concat, cpp_class<Fun>());

		ClassPtr classes[4] = {cpp_class<Element>(), cpp_class<ChRange>(), cpp_class<String>(), cpp_class<Fun>()};
		for(int i=0; i<4; ++i){
			classes[i]->inherit(p);
		}
	}

	AnyPtr any = xnew<Element>(Element::TYPE_ANY);
	AnyPtr bos = xnew<Element>(Element::TYPE_BOS);
	AnyPtr eos = xnew<Element>(Element::TYPE_EOS);
	AnyPtr bol = xnew<Element>(Element::TYPE_BOL);
	AnyPtr eol = xnew<Element>(Element::TYPE_EOL);
	AnyPtr empty = xnew<Element>(Element::TYPE_EMPTY);
	//AnyPtr degit = elem(AnyPtr("0")->send(Xid(op_range), "9", RANGE_CLOSED));
	//AnyPtr lalpha = elem(AnyPtr(Xid(a))->send(Xid(op_range), Xid(z), RANGE_CLOSED));
	//AnyPtr ualpha = elem(AnyPtr(Xid(A))->send(Xid(op_range), Xid(Z), RANGE_CLOSED));
	//AnyPtr alpha = lalpha | ualpha;
	//AnyPtr word = alpha | degit | Xid(_);
	//AnyPtr ascii = elem(xnew<String>((char_t)1)->send(Xid(op_range), xnew<String>((char_t)127), RANGE_CLOSED));

	xpeg->def(Xid(any), any);
	xpeg->def(Xid(bos), bos);
	xpeg->def(Xid(eos), eos);
	xpeg->def(Xid(bol), bol);
	xpeg->def(Xid(eol), eol);
	xpeg->def(Xid(empty), empty);
	//xpeg->def(Xid(degit), degit);
	//xpeg->def(Xid(lalpha), lalpha);
	//xpeg->def(Xid(ualpha), ualpha);
	//xpeg->def(Xid(alpha), alpha);
	//xpeg->def(Xid(word), word);
	//xpeg->def(Xid(ascii), ascii);
	
	xpeg->def_fun(Xid(set), &set);
	xpeg->def_fun(Xid(back_ref), &back_ref);
	xpeg->def_fun(Xid(lookahead), &lookahead);
	xpeg->def_fun(Xid(lookbehind), &lookbehind);
	xpeg->def_fun(Xid(leaf), &leaf);
	xpeg->def_fun(Xid(node), &node_vm);
	xpeg->def_fun(Xid(splice_node), &splice_node_vm);
	xpeg->def_fun(Xid(cap), &cap_vm);
	//xpeg->def_fun(Xid(bound), &bound);
	xpeg->def_fun(Xid(pred), &pred);
	xpeg->def_fun(Xid(error), &error);

	xpeg->def_fun(Xid(decl), &decl);

	xpeg->def(Xid(Executor), cpp_class<Executor>());
}

void initialize_xpeg(){
	using namespace xpeg;

	ClassPtr xpeg = xnew<Singleton>(Xid(xpeg));
	//bind_xpeg(xpeg);
	xpeg->set_binder(&bind_xpeg);

	{
		ClassPtr p = cpp_class<TreeNode>();
		p->set_final();
		p->inherit(cpp_class<Array>());
		p->def_method(Xid(tag), &TreeNode::tag);
		p->def_method(Xid(lineno), &TreeNode::lineno);
		p->def_method(Xid(set_tag), &TreeNode::set_tag);
		p->def_method(Xid(set_lineno), &TreeNode::set_lineno);
	}

	builtin()->def(Xid(xpeg), xpeg);
}


}
