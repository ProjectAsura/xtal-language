
#pragma once

namespace xtal{ namespace xeg{

class MatchResult;
typedef SmartPtr<MatchResult> MatchResultPtr;

class TreeNode;
typedef SmartPtr<TreeNode> TreeNodePtr;

class Scanner;
typedef SmartPtr<Scanner> ScannerPtr;

class Executor;
typedef SmartPtr<Executor> ExecutorPtr;

/**
* @brief �\���؂̃m�[�h
*/
class TreeNode : public Array{
public:

	TreeNode(const AnyPtr& tag=null, int_t lineno=0){
		tag_ = tag;
		lineno_ = lineno;
	}

	AnyPtr tag(){
		return tag_;
	}

	void set_tag(const AnyPtr& tag){
		tag_ = tag;
	}
	
	int_t lineno(){
		return lineno_;
	}

	void set_lineno(int_t lineno){
		lineno_ = lineno;
	}

private:
	AnyPtr tag_;
	int_t lineno_;
};

/**
* @brief �g�����K�\�������s����
*/
class Executor : public Base{
public:

	Executor(const AnyPtr& stream_or_iterator = null){
		reset(stream_or_iterator);
	}

	/**
	* @brief �ݒ�����Z�b�g����B
	*/
	void reset(const AnyPtr& stream_or_iterator);

	/**
	* @brief �n���ꂽ�p�^�[�����}�b�`���邩���ׂ�B
	*/
	bool match(const AnyPtr& pattern);

	/**
	* @brief �n���ꂽ�p�^�[���Ńp�[�X����B
	*/
	bool parse(const AnyPtr& pattern);

	/**
	* @brief �L���v�`�����ꂽ�l�̃C�e���[�^���擾����B
	*/
	AnyPtr captures(){
		return cap_values_->each();
	}

	/**
	* @brief ���O���L���v�`�����ꂽ�l�̃C�e���[�^���擾����B
	*/
	AnyPtr named_captures(){
		return named_cap_values_->each();
	}

	/**
	* @brief �L���v�`�����ꂽ�l�𓾂�
	* 0�̓}�b�`����������S�̂��擾�ł���B
	* 1�`��cap�֐��ŃL���v�`��������������擾�ł���B
	*/
	AnyPtr at(int_t key);
	
	/**
	* @brief ���O���L���v�`�����ꂽ�l�𓾂�B
	*/
	AnyPtr at(const StringPtr& key){
		return  named_cap_values_->at(key);
	}

	/**
	* @brief �}�b�`������������O�̕�������擾����B
	*/
	StringPtr prefix();

	/**
	* @brief �}�b�`�������������̕�������擾����B
	*/
	StringPtr suffix();

	/**
	* @brief ���������G���[�̃C�e���[�^���擾����B
	*/
	AnyPtr errors(){
		return errors_->each();
	}

	/**
	* @brief ���������\���؂��擾����B
	*/
	TreeNodePtr tree(){
		return tree_;
	}

	/**
	* @brief �ꕶ���擾����B
	*/
	const AnyPtr& read();

	/**
	* @brief n��������̂�������B
	*/
	const AnyPtr& peek(uint_t n = 0);

public:

	struct SState{
		uint_t lineno;
		uint_t pos;
	};

private:

	bool match_inner(const AnyPtr& nfa);

	bool test(const AnyPtr& elem);

	void push(uint_t mins, uint_t st, uint_t nodes, const SState& pos);

	struct StackInfo{ 
		uint_t state;
		uint_t nodes;
		SState pos; 
	};

	typedef Stack<StackInfo> stack_t;

	struct Cap{
		int_t begin, end;
	};

	stack_t stack_;

	ArrayPtr cap_;
	MapPtr named_cap_;

	ArrayPtr cap_values_;
	MapPtr named_cap_values_;

	TreeNodePtr tree_;
	ArrayPtr errors_;
	ScannerPtr scanner_;

	int_t begin_;
	int_t match_begin_;
	int_t match_end_;

	virtual void visit_members(Visitor& m){
		Base::visit_members(m);
		m & tree_ & errors_ & cap_ & named_cap_ & cap_values_ & named_cap_values_;
	}
};

AnyPtr before(const AnyPtr& elem);

AnyPtr after(const AnyPtr& elem, int_t back);

AnyPtr eq(const AnyPtr& elem);

AnyPtr eql(const AnyPtr& elem);

/**
* @brief ����Q��
*/
AnyPtr back_ref(const AnyPtr& no);

/**
* @brief �L���v�`��
*/
AnyPtr cap(const AnyPtr& elem);

/**
* @brief ���O���L���v�`��
*/
AnyPtr cap(const IDPtr& name, const AnyPtr& elem);

AnyPtr error(const AnyPtr& fn);

AnyPtr node(const AnyPtr& elem);
AnyPtr node(const IDPtr& name, const AnyPtr& elem);
AnyPtr splice_node(int_t num, const AnyPtr& elem);
AnyPtr splice_node(int_t num, const IDPtr& name, const AnyPtr& elem);
AnyPtr leaf(const AnyPtr& left);

extern AnyPtr any;
extern AnyPtr bos;
extern AnyPtr eos;
extern AnyPtr bol;
extern AnyPtr eol;
extern AnyPtr empty;
extern AnyPtr alpha;
extern AnyPtr degit;
extern AnyPtr lower;
extern AnyPtr upper;
extern AnyPtr word;
extern AnyPtr ascii;

}}

