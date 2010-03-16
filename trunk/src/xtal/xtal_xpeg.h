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
	Executor(const AnyPtr& source = null, const StringPtr& source_name = empty_string){
		reset(source, source_name);
	}

	~Executor();

	/**
	* \brief �ݒ�����Z�b�g����B
	*/
	void reset(const AnyPtr& source, const StringPtr& source_name = empty_string);

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
	AnyPtr errors();

	void error(const AnyPtr& message, int_t lineno = 0);

	void clear_errors();

	bool has_error();

public:

	/**
	* \brief ���������\���؂��擾����B
	*/
	const TreeNodePtr& tree(){
		return tree_;
	}

	/**
	* \brief �\���؂ɗv�f����ǉ�����
	*/
	void tree_push_back(const AnyPtr& a){
		tree_->push_back(a);
	}

	/**
	* \brief �\���؂���v�f�����菜��
	*/
	AnyPtr tree_pop_back(){
		AnyPtr ret = tree_->back();
		tree_->pop_back();
		return ret;
	}

	/**
	* \brief �\���؂̍Ō�̗v�f���擾����
	*/
	const AnyPtr& tree_back(){
		if(tree_->empty()){ return undefined; }
		return tree_->back();
	}

	void tree_insert(int_t n, const AnyPtr& v){
		tree_->insert(tree_->size()-n, v);
	}

	struct TreeNodeState{
		int_t lineno;
		int_t pos;
	};

	TreeNodeState tree_node_begin(){
		TreeNodeState state = {lineno_, tree_->size()};
		return state;
	}

	void tree_node_end(const AnyPtr& tag, const TreeNodeState& state){
		tree_splice(tag, tree_->size()-state.pos, state.lineno);
	}

	void tree_splice(int_t itag, int_t num);
	
	void tree_splice(const AnyPtr& tag, int_t num);

	void tree_splice(const AnyPtr& tag, int_t num, int_t lineno);

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
	const AnyPtr& peek(int_t n = 0);

	const StringPtr& peek_s(int_t n = 0);

	int_t peek_ascii(int_t n = 0);
	
	struct State{
		uint_t lineno;
		uint_t pos;
	};

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
	* \brief ��ԍŏ��̈ʒu�ɂ��邩���ׂ�
	*/
	bool bos(){
		return pos()==0;
	}

	/**
	* \brief �I�����Ă��邩���ׂ�
	*/
	bool eos(){
		return is_undefined(peek());
	}

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
	
	bool match_inner(const ElementPtr& nfa);

	bool test(const ElementPtr& elem);

	struct StackInfo{ 
		uint_t state;
		uint_t nodes;
		State pos; 
	};

	typedef FastStack<StackInfo> stack_t;
	stack_t stack_;

	void push(uint_t mins, uint_t cur_state, uint_t nodes, const State& pos){
		StackInfo temp = {cur_state, nodes, pos};
		stack_.push(temp);
	}

	struct Cap : public Base{
		int_t begin, end;
	};

	MapPtr cap_;

	TreeNodePtr tree_;
	ArrayPtr errors_;

	int_t pos_begin_;
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
		m & tree_ & errors_ & cap_;
		m & mm_;
		for(uint_t i=base_, sz=num_; i<sz; ++i){
			for(int j=0; j<ONE_BLOCK_SIZE; ++j){
				m & begin_[i-base_][j];
			}
		}
	}

private:

	typedef Hashtable<Key, Value, Fun> memotable_t;
	memotable_t memotable_;

private:
	enum{
		ONE_BLOCK_SHIFT = 5,
		ONE_BLOCK_SIZE = 1<<ONE_BLOCK_SHIFT,
		ONE_BLOCK_MASK = ONE_BLOCK_SIZE-1
	};

public:

	void bin();

public:

	ArrayPtr capture_values(int_t begin, int_t end);
	
	ArrayPtr capture_values(int_t begin);
	
	StringPtr capture(int_t begin, int_t end);

	StringPtr capture(int_t begin);

	bool eat_capture(int_t begin, int_t end);

public:

	/**
	* \brief ������̋L�^���J�n����
	*/
	void begin_record();

	/**
	* \brief ������̋L�^���I�����āA�����Ԃ��B
	*/
	StringPtr end_record();

protected:

	void expand();

	AnyPtr& access(int_t pos){
		if(pos<base_*ONE_BLOCK_SIZE){ 
			return undefined; 
		}
		return begin_[(pos>>ONE_BLOCK_SHIFT)-base_][pos&ONE_BLOCK_MASK];
	}

protected:
	StreamPtr stream_;
	StringPtr source_name_;

	IDPtr n_ch_;
	IDPtr r_ch_;
	
	MemoryStreamPtr mm_;
	AnyPtr** begin_;

	uint_t num_;
	uint_t max_;

	int_t pos_;
	int_t read_;
	int_t base_;

	uint_t lineno_;
	int_t record_pos_;
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

	u8 type;
	bool inv;
	AnyPtr param1;
	AnyPtr param2;
	int_t param3;

	NFAPtr nfa;

	Element(int_t type, const AnyPtr& param1 = null, const AnyPtr& param2 = null, int_t param3 = 0);

	~Element();

	ElementPtr op_com() const;

	void on_visit_members(Visitor& m){
		Base::on_visit_members(m);
		m & param1 & param2 & nfa;
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
	
	struct State{
		TransPtr trans;
		int_t capture_kind;
		IDPtr capture_name;
	};

	int gen_state();

	ElementPtr e_;
	TArray<State> states_;
	uint_t cap_max_;
	ArrayPtr cap_list_;

	void on_visit_members(Visitor& m){
		Base::on_visit_members(m);
		for(uint_t i=0; i<states_.size(); ++i){
			m & states_[i].trans;
		}
	}

	enum{
		CAPTURE_NONE = 0,
		CAPTURE_BEGIN = 1,
		CAPTURE_END = 2
	};
};

ElementPtr elem(const AnyPtr& a);

}

}

#endif // XTAL_XPEG_H_INCLUDE_GUARD
