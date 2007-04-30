

#pragma once

#include "xtal.h"
#include "stream.h"

namespace xtal{

inline bool test_range(int ch, int begin, int end){
	return begin<=ch && ch<=end;
}

inline bool test_digit(int ch){
	return test_range(ch, '0', '9');
}

inline bool test_lalpha(int ch){
	return test_range(ch, 'a', 'z');
}

inline bool test_ualpha(int ch){
	return test_range(ch, 'A', 'Z');
}

inline bool test_alpha(int ch){
	return test_lalpha(ch) || test_ualpha(ch);
}

inline bool test_space(int ch){
	return ch==' ' || ch=='\t' || ch=='\n' || ch=='\r';
}

inline bool test_ident_first(int ch){
	return test_alpha(ch) || ch=='_';
}

inline bool test_ident_rest(int ch){
	return test_alpha(ch) || test_digit(ch) || ch=='_';
}

inline bool test_delim(int ch){
	return ch==';' || ch==':' || ch=='}' || ch==']' || ch==')' || ch==',';
}

inline bool test_xml_tag_name(int ch){
	return ch==';' || ch==':' || ch=='}' || ch==']' || ch==')' || ch==',';
}

inline int to_lalpha(int ch){
	using namespace std;
	return tolower(ch);
}

class Token{
public:

	enum Flag{
		FLAG_LEFT_SPACE = 1<<0,
		FLAG_RIGHT_SPACE = 1<<1
	};
	
	enum Type{	
		TYPE_TOKEN = 0,
		TYPE_INT = 1,
		TYPE_FLOAT = 2,
		TYPE_IDENT = 3,
		TYPE_KEYWORD = 4,
	};
	
	enum Keyword{
		KEYWORD_NONE,
		
		KEYWORD_IF,
		KEYWORD_FOR,
		KEYWORD_ELSE,
		KEYWORD_SWITCH,
		KEYWORD_FUN,
		KEYWORD_METHOD,
		KEYWORD_DO,
		KEYWORD_WHILE,
		KEYWORD_CONTINUE,
		KEYWORD_BREAK,
		KEYWORD_FIBER,
		KEYWORD_YIELD,
		KEYWORD_RETURN,
		KEYWORD_ONCE,
		KEYWORD_NULL,
		KEYWORD_FALSE,
		KEYWORD_TRUE,
		KEYWORD_NOP,
		KEYWORD_XTAL,
		KEYWORD_DEBUG,
		KEYWORD_TRY,
		KEYWORD_CATCH,
		KEYWORD_FINALLY,
		KEYWORD_THROW,
		KEYWORD_CLASS,
		KEYWORD_IMPORT,
		KEYWORD_CALLEE,
		KEYWORD_THIS,
		KEYWORD_CURRENT_COUNTEXT,
		KEYWORD_DOFUN,
		KEYWORD_IS,
		KEYWORD_EXPORT,
		KEYWORD_UNITTEST,
		KEYWORD_ASSERT,
		KEYWORD_PURE,
		KEYWORD_NOBREAK,
	
		KEYWORD_MAX
	};

	Token(){}
	
	Token(int_t type, int_t value, int_t flags)
		:type_(type), flags_(flags), ivalue_(value){}

	Token(int_t type, float_t value, int_t flags)
		:type_(type), flags_(flags), fvalue_(value){}

	int_t type() const{
		return type_;
	}

	bool left_space() const{
		return (flags_ & FLAG_LEFT_SPACE) != 0;
	}
	
	bool right_space() const{
		return (flags_ & FLAG_RIGHT_SPACE) != 0;
	}

	int_t ivalue() const{
		return ivalue_;
	}

	float_t fvalue() const{
		return fvalue_;
	}

private:

	u8 type_;
	u8 flags_;
	union{
		int_t ivalue_;
		float_t fvalue_;
	};
	
};

struct LPCCommon{

	LPCCommon();
		
	void init(const String& file_name);

	void error(int_t line, const Any& message);
	
	int_t register_ident(const ID& ident);

	int_t register_value(const Any& v);

	int_t append_ident(const ID& ident);

	int_t append_value(const Any& v);
	
	Array errors;
	Array ident_table;
	Map ident_map;
	Array value_table;
	String source_file_name;
};

class Reader{
public:

	Reader();

	void set_stream(const Stream& stream){
		stream_ = stream;
	}

	/**
	* �ǂݐi�߂�B
	*/
	int_t read();

	/**
	* ���̗v�f��ǂށB
	*/
	int_t peek();

	/**
	* ���̗v�f������ch�Ɠ�����������ǂݐi�߂�B
	* @param ch ���̒l�Ǝ��̗v�f���������ꍇ�ɓǂݐi�߂�B
	* @retval true ���̗v�f��ch�Ɠ����ŁA�ǂݐi�߂��B
	* @retval false ���̗v�f��ch�ƈقȂ�A�ǂݐi�߂Ȃ������B
	*/
	bool eat(int_t ch);

	/**
	* �v�f����߂��B
	*/
	void putback(int_t ch);
	
	/**
	* �|�W�V�����̎擾�B
	*/
	int_t position();
	
	/**
	* �|�W�V������pos�̈ʒu�ɖ߂��B
	*/
	void set_position(int_t pos);

private:

	enum{ BUF_SIZE = 1024, BUF_MASK = BUF_SIZE-1 };

	Stream stream_;

	char buf_[BUF_SIZE];

	uint_t pos_;
	uint_t read_;
	uint_t marked_;
	int_t line_;
};
	

/*
* XTAL�v���O�����\�[�X���g�[�N����ɕϊ����Ď��o��
*/
class Lexer{
public:

	Lexer();
	
	/**
	* ������
	*/
	void init(const Stream& stream, const String& source_file_name);
	
	/**
	* �ǂݐi�߂�
	*/
	Token read();

	/**
	* ���̗v�f��ǂ�
	*/
	Token peek();

	/**
	* �ǂݍ��񂾗v�f����߂�
	*/
	void putback();
	
	/**
	* �w�肵���g�[�N������߂�
	* ����read��peek�ł́A����Ŗ߂����l��������
	*/
	void putback(const Token& ch);
	
	/**
	* ������𒼐ړǂރ��[�h�ɕύX����
	*/
	void set_string_mode();
	
	/**
	* ��������g�[�N���ŕԂ����[�h�ɕύX����
	*/
	void set_normal_mode();

	/**
	* ���݂̍s����Ԃ�
	*/
	int_t line(){ return line_; }
	
	/**
	* �g�[�N����ǂ߂�`�̕�����ɕϊ�����
	*/
	String token2str(const Token& t);
	
	/**
	* �L�[���[�h��ID�ɕϊ�����
	*/
	ID keyword2id(int_t v);

	/**
	* Lexer, Parser, CodeBuilder�����ʂ��Ď���LPCCommon�I�u�W�F�N�g��Ԃ�
	*/
	LPCCommon common();
	
	/**
	* ������̋L�^���J�n����
	*/
	void begin_record();

	/**
	* ������̋L�^���I�����āA�����Ԃ��B
	*/
	string_t end_record();

	/**
	* �����Ŏg�p���Ă��郁�����ȂǑS�ĉ������
	*/
	void release();
	
private:

	void error(const Any&);
	
	void do_read();

	void push(int_t v);
	
	void push_int(int_t v);
	
	void push_float(float_t v);
	
	void push_keyword(int_t v);
	
	void push_ident(int_t v);

	void push_direct(int_t v);

	void deplete_space();

	int_t parse_ident();

	int_t parse_integer();

	int_t parse_hex();

	int_t parse_bin();

	void parse_number_suffix(int_t val);
	
	void parse_number_suffix(float_t val);

	void parse_number();
	
	int_t test_right_space(int_t ch);

	int_t read_from_reader();

	bool eat_from_reader(int_t ch);

	void putback_to_reader(int_t ch);

private:

	Reader reader_;
	
	LPCCommon com_;
	Map keyword_map_;

	string_t recorded_string_;
	bool recording_;

	enum{ BUF_SIZE = 1024, BUF_MASK = BUF_SIZE-1 };
	Token buf_[BUF_SIZE];

	uint_t pos_;
	uint_t read_;
	int_t line_;
	int_t left_space_;
	
	enum{ NORMAL_MODE, STRING_MODE };
	int_t mode_;
};

}
