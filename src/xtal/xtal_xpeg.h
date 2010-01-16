/** \file src/xtal/xtal_xpeg.h
* rief src/xtal/xtal_xpeg.h
*/

#ifndef XTAL_XPEG_H_INCLUDE_GUARD
#define XTAL_XPEG_H_INCLUDE_GUARD

#pragma once

namespace xtal{ 

/**
* @brief PEG���C�u����
*/
namespace xpeg{

class MatchResult;
typedef SmartPtr<MatchResult> MatchResultPtr;

class Executor;
typedef SmartPtr<Executor> ExecutorPtr;

struct Element;
typedef SmartPtr<Element> ElementPtr;

struct Trans;
typedef SmartPtr<Trans> TransPtr;

struct NFA;
typedef SmartPtr<NFA> NFAPtr;

class Scanner;
typedef SmartPtr<Scanner> ScannerPtr;

/**
* \xbind lib::builtin::xpeg
* \xinherit lib::builtin::Any
* \brief PEG�����s����
*/
class Executor : public Base{
public:

	/**
	* \xbind
	* \brief �X�g���[�����C�e���[�^���󂯎��\�z����
	*/
	Executor(const AnyPtr& stream_or_iterator = null){
		reset(stream_or_iterator);
	}

	/**
	* \brief �ݒ�����Z�b�g����B
	*/
	void reset(const AnyPtr& stream_or_iterator);

	/**
	* \brief �n���ꂽ�p�^�[�����}�b�`���邩���ׂ�B
	*/
	bool match(const AnyPtr& pattern);

	/**
	* \brief �n���ꂽ�p�^�[���Ńp�[�X����B
	*/
	bool parse(const AnyPtr& pattern);

public:

	/**
	* \brief �L���v�`�����ꂽ�������񋓂���C�e���[�^���擾����B
	*/
	AnyPtr captures();

	/**
	* \brief �L���v�`�����ꂽ������𓾂�B
	*/
	StringPtr at(const StringPtr& key);
	
	/**
	* \brief �}�b�`������������O�̕�������擾����B
	*/
	StringPtr prefix();

	/**
	* \brief �}�b�`�������������̕�������擾����B
	*/
	StringPtr suffix();
	
public:

	/**
	* \brief �L���v�`�����ꂽ�l�̔z��̃C�e���[�^���擾����B
	*/
	AnyPtr captures_values();

	/**
	* \brief �L���v�`�����ꂽ�l�̔z��𓾂�B
	*/
	AnyPtr call(const StringPtr& key);

	/**
	* \brief �}�b�`������������O�̒l�̔z��̃C�e���[�^���擾����B
	*/
	AnyPtr prefix_values();

	/**
	* \brief �}�b�`�������������̒l�̔z��̃C�e���[�^���擾����B
	*/
	AnyPtr suffix_values();

public:

	/**
	* \brief ���������G���[�̃C�e���[�^���擾����B
	*/
	AnyPtr errors(){
		if(!errors_) return null;
		return errors_->each();
	}

	void error(const AnyPtr& message, int_t lineno = 0);

	/**
	* \brief ���������\���؂��擾����B
	*/
	TreeNodePtr tree(){
		return tree_;
	}

	/**
	* \brief �\���؂ɗv�f��ǉ�����
	*/
	void push_result(const AnyPtr& a){
		tree_->push_back(a);
	}

	AnyPtr pop_result(){
		AnyPtr ret = tree_->back();
		tree_->pop_back();
		return ret;
	}

	const AnyPtr& back_result(){
		return tree_->back();
	}

public:

	/**
	* \brief �ꕶ���擾����B
	*/
	const AnyPtr& read();

	const StringPtr& read_s();

	int_t read_ascii();

	/**
	* \brief n��������̂�������B
	*/
	const AnyPtr& peek(uint_t n = 0);

	const StringPtr& peek_s(uint_t n = 0);

	int_t peek_ascii(uint_t n = 0);

	struct State{
		uint_t lineno;
		uint_t pos;
	};

	/**
	* \brief �}�[�N������
	*/
	State save();

	/**
	* \brief �}�[�N��t�����ʒu�ɖ߂�
	*/
	void load(const State& state);

	/**
	* \brief ���݂̈ʒu��Ԃ�
	*/
	uint_t pos();

	/**
	* \brief ���݂̍s����Ԃ�
	*/
	uint_t lineno();

	/**
	* \brief ��ԍŏ��̈ʒu�ɂ��邩���ׂ�
	*/
	bool bos();

	/**
	* \brief �I�����Ă��邩���ׂ�
	*/
	bool eos();

	/**
	* \brief �s�������ׂ�
	*/
	bool bol();

	/**
	* \brief �s�������ׂ�
	*/
	bool eol();

	/**
	* \brief n�v�f�ǂݔ�΂�
	*/
	void skip(uint_t n);

	void skip();

	/**
	* \brief �s����ǂݔ�΂�
	*/
	void skip_eol();

	bool eat(const AnyPtr& v);

	bool eat_ascii(int_t ch);

private:
	
	bool match_inner(const AnyPtr& nfa);

	bool test(const AnyPtr& elem);

	void push(uint_t mins, uint_t st, uint_t nodes, const State& pos);

	struct StackInfo{ 
		uint_t state;
		uint_t nodes;
		State pos; 
	};

	typedef PODStack<StackInfo> stack_t;

	struct Cap : public Base{
		int_t begin, end;
	};

	stack_t stack_;
	MapPtr cap_;

	TreeNodePtr tree_;
	ArrayPtr errors_;
	ScannerPtr scanner_;

	int_t begin_;
	int_t match_begin_;
	int_t match_end_;

public:

	struct Key{
		uint_t pos;
		void* ptr;
	};

	struct Fun{
		static uint_t hash(const Key& key){
			return key.pos ^ (uint_t)key.ptr;
		}

		static bool eq(const Key& a, const Key& b){
			return a.pos==b.pos && a.ptr==b.ptr;
		}
	};

	struct Value{
		State state;
		ArrayPtr tree;
	};

	void on_visit_members(Visitor& m){
		Base::on_visit_members(m);
		m & tree_ & errors_ & cap_ & scanner_;
	}

private:

	typedef Hashtable<Key, Value, Fun> memotable_t;
	memotable_t memotable_;
};

/*
* \brief �ꕶ���Âǂ�ŏ������Ă����̂ɓK�������\�b�h��񋟂���N���X
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
	* \brief ���݂̈ʒu��Ԃ��擾����
	*/
	State save(){
		State state;
		state.lineno = lineno_;
		state.pos = pos_;
		return state;
	}

	/**
	* \brief �w�肵���ʒu��Ԃɖ߂�
	*/
	void load(const State& state){
		pos_ = state.pos;
		lineno_ = state.lineno;
	}

	/**
	* \brief ���݂̈ʒu��Ԃ�
	*/
	uint_t pos(){
		return pos_;
	}

	/**
	* \brief ���݂̍s����Ԃ�
	*/
	uint_t lineno(){
		return lineno_;
	}

	/**
	* \brief n��̗v�f��`������
	*/
	const AnyPtr& peek(uint_t n = 0);
	
	/**
	* \brief �ЂƂǂݎ��
	*/
	const AnyPtr& read();

	bool bos(){
		return pos()==0;
	}

	bool eos(){
		return raweq(peek(), undefined);
	}

	bool bol();

	bool eol();

	void skip(uint_t n);

	void skip_eol();

	void bin();

public:

	ArrayPtr capture_values(int_t begin, int_t end);
	
	ArrayPtr capture_values(int_t begin);
	
	StringPtr capture(int_t begin, int_t end);

	StringPtr capture(int_t begin);

	bool eat_capture(int_t begin, int_t end);

public:

	int_t peek_ascii(uint_t n = 0){
		const AnyPtr& ch = peek(n);
		return chvalue(ch);
	}
	
	int_t read_ascii(){
		const AnyPtr& ch = read();
		return chvalue(ch);
	}

	/**
	* \brief ������̋L�^���J�n����
	*/
	void begin_record();

	/**
	* \brief ������̋L�^���I�����āA�����Ԃ��B
	*/
	StringPtr end_record();

	bool eat_ascii(int_t ch){
		if(peek_ascii()==ch){
			read_ascii();
			return true;
		}
		return false;
	}

protected:

	virtual int_t do_read(AnyPtr* buffer, int_t max) = 0;

	void on_visit_members(Visitor& m){
		Base::on_visit_members(m);
		m & mm_;
		for(uint_t i=base_, sz=num_; i<sz; ++i){
			for(int j=0; j<ONE_BLOCK_SIZE; ++j){
				m & begin_[i-base_][j];
			}
		}
	}

	void expand();

	AnyPtr& access(uint_t pos){
		if(pos<base_*ONE_BLOCK_SIZE){ 
			return undefined; 
		}
		return begin_[(pos>>ONE_BLOCK_SHIFT)-base_][pos&ONE_BLOCK_MASK];
	}

private:

	IDPtr n_ch_;
	IDPtr r_ch_;
	
	MemoryStreamPtr mm_;
	AnyPtr** begin_;
	uint_t num_;
	uint_t max_;
	uint_t pos_;
	uint_t read_;
	uint_t base_;
	uint_t lineno_;
	uint_t record_pos_;
};

class StreamScanner : public Scanner{
public:

	StreamScanner(const StreamPtr& stream)
		:stream_(stream){}

	virtual int_t do_read(AnyPtr* buffer, int_t max){
		return stream_->read_charactors(buffer, max);
	}

	void on_visit_members(Visitor& m){
		Scanner::on_visit_members(m);
		m & stream_;
	}

private:
	StreamPtr stream_;
};

class IteratorScanner : public Scanner{
public:

	IteratorScanner(const AnyPtr& iter);

	virtual int_t do_read(AnyPtr* buffer, int_t max);

	void on_visit_members(Visitor& m){
		Scanner::on_visit_members(m);
		m & iter_;
	}
private:
	AnyPtr iter_;
};

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
		TYPE_INT_RANGE,
		TYPE_FLOAT_RANGE,
		TYPE_CH_RANGE,

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
		TYPE_DECL // �錾
	};

	Type type;
	AnyPtr param1;
	AnyPtr param2;
	int_t param3;
	bool inv;

	Element(Type type, const AnyPtr& param1 = null, const AnyPtr& param2 = null, int_t param3 = 0)
		:type(type), param1(param1), param2(param2), param3(param3), inv(false){}

	void on_visit_members(Visitor& m){
		Base::on_visit_members(m);
		m & param1 & param2;
	}
};

////////////////////////////////////////////////////////////////////////

struct Trans : public Base{
	ElementPtr ch;
	int to;
	SmartPtr<Trans> next;

	void on_visit_members(Visitor& m){
		Base::on_visit_members(m);
		m & ch & next;
	}
};	

////////////////////////////////////////////////////////////////////////

struct NFA : public Base{

	NFA(const ElementPtr& node);

	void add_transition(int from, const AnyPtr& ch, int to);

	void gen_nfa(int entry, const AnyPtr& t, int exit, int depth);

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

	int gen_state();

	ElementPtr e_;
	ElementPtr root_node_;
	ArrayList<State> states_;
	uint_t cap_max_;
	ArrayPtr cap_list_;

	enum{
		CAPTURE_NONE = 0,
		CAPTURE_BEGIN = 1,
		CAPTURE_END = 2
	};
};

const NFAPtr& fetch_nfa(const ElementPtr& node);

ElementPtr elem(const AnyPtr& a);
AnyPtr set(const StringPtr& str);
AnyPtr call(const AnyPtr& fun);
AnyPtr select(const AnyPtr& left, const AnyPtr& right);
AnyPtr concat(const AnyPtr& left, const AnyPtr& right);
AnyPtr more_Int(const AnyPtr& left, int_t n, int_t kind = 0);
AnyPtr more_IntRange(const AnyPtr& left, const IntRangePtr& range, int_t kind = 0);
AnyPtr more_normal_Int(const AnyPtr& left, int_t n);
AnyPtr more_shortest_Int(const AnyPtr& left, int_t n);
AnyPtr more_greed_Int(const AnyPtr& left, int_t n);
AnyPtr more_normal_IntRange(const AnyPtr& left, const IntRangePtr& range);
AnyPtr more_shortest_IntRange(const AnyPtr& left, const IntRangePtr& range);
AnyPtr more_greed_IntRange(const AnyPtr& left, const IntRangePtr& range);
AnyPtr inv(const AnyPtr& left);
AnyPtr lookahead(const AnyPtr& left);
AnyPtr lookbehind(const AnyPtr& left, int_t back);
AnyPtr cap(const IDPtr& name, const AnyPtr& left);
void cap_vm(const VMachinePtr& vm);
AnyPtr node(const AnyPtr& left);
AnyPtr node(const IDPtr& name, const AnyPtr& left);
void node_vm(const VMachinePtr& vm);
AnyPtr splice_node(int_t num, const AnyPtr& left);
AnyPtr splice_node(int_t num, const IDPtr& name, const AnyPtr& left);
void splice_node_vm(const VMachinePtr& vm);
AnyPtr leaf(const AnyPtr& left);
AnyPtr leafs(const AnyPtr& left);
AnyPtr back_ref(const AnyPtr& n);
AnyPtr decl();
void set_body(const ElementPtr& x, const AnyPtr& term);
AnyPtr bound(const AnyPtr& body, const AnyPtr& sep);
AnyPtr error(const AnyPtr& fn);
AnyPtr pred(const AnyPtr& e);

}}


#endif // XTAL_XPEG_H_INCLUDE_GUARD
