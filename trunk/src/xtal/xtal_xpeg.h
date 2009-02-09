
#pragma once

#ifndef XTAL_NO_XPEG

namespace xtal{ namespace xpeg{

class MatchResult;
typedef SmartPtr<MatchResult> MatchResultPtr;

class TreeNode;
typedef SmartPtr<TreeNode> TreeNodePtr;

class Scanner;
typedef SmartPtr<Scanner> ScannerPtr;

class Executor;
typedef SmartPtr<Executor> ExecutorPtr;

class Scanner;
typedef SmartPtr<Scanner> ScannerPtr;

class StreamScanner;
typedef SmartPtr<StreamScanner> StreamScannerPtr;

class IteratorScanner;
typedef SmartPtr<IteratorScanner> IteratorScannerPtr;

struct Element;
typedef SmartPtr<Element> ElementPtr;

struct Trans;
typedef SmartPtr<Trans> TransPtr;

struct NFA;
typedef SmartPtr<NFA> NFAPtr;
	
/**
* @brief �\���؂̃m�[�h
*/
class TreeNode : public Array{
public:

	TreeNode(const AnyPtr& tag=null, int_t lineno=0){
		tag_ = tag;
		lineno_ = lineno;
	}

	const AnyPtr& tag(){
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
* @brief PEG�����s����
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

public:

	/**
	* @brief �L���v�`�����ꂽ�������񋓂���C�e���[�^���擾����B
	*/
	AnyPtr captures();

	/**
	* @brief �L���v�`�����ꂽ������𓾂�B
	*/
	StringPtr at(const StringPtr& key);
	
	/**
	* @brief �}�b�`������������O�̕�������擾����B
	*/
	StringPtr prefix();

	/**
	* @brief �}�b�`�������������̕�������擾����B
	*/
	StringPtr suffix();
	
public:

	/**
	* @brief �L���v�`�����ꂽ�l�̔z��̃C�e���[�^���擾����B
	*/
	AnyPtr captures_values();

	/**
	* @brief �L���v�`�����ꂽ�l�̔z��𓾂�B
	*/
	AnyPtr call(const StringPtr& key);

	/**
	* @brief �}�b�`������������O�̒l�̔z��̃C�e���[�^���擾����B
	*/
	AnyPtr prefix_values();

	/**
	* @brief �}�b�`�������������̒l�̔z��̃C�e���[�^���擾����B
	*/
	AnyPtr suffix_values();

public:

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
	
	const NFAPtr& fetch_nfa(const ElementPtr& node);

	bool match_inner(const AnyPtr& nfa);

	bool test(const AnyPtr& elem);

	void push(uint_t mins, uint_t st, uint_t nodes, const SState& pos);

	struct StackInfo{ 
		uint_t state;
		uint_t nodes;
		SState pos; 
	};

	typedef PODStack<StackInfo> stack_t;

	struct Cap{
		int_t begin, end;
	};

	stack_t stack_;
	
	MapPtr nfa_map_;

	MapPtr cap_;

	TreeNodePtr tree_;
	ArrayPtr errors_;
	ScannerPtr scanner_;

	int_t begin_;
	int_t match_begin_;
	int_t match_end_;

	virtual void visit_members(Visitor& m){
		Base::visit_members(m);
		m & nfa_map_ & tree_ & errors_ & cap_;
	}
};

AnyPtr lookahead(const AnyPtr& elem);

AnyPtr lookbehind(const AnyPtr& elem, int_t back);

AnyPtr bound(const AnyPtr& body, const AnyPtr& sep);

AnyPtr pred(const AnyPtr& elem);

/**
* @brief ����Q��
*/
AnyPtr back_ref(const AnyPtr& no);

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
AnyPtr leafs(const AnyPtr& left);

}}

#endif
