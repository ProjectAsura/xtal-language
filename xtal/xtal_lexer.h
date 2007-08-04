
#pragma once

#ifndef XTAL_NO_PARSER

#include "xtal.h"
#include "xtal_stream.h"
#include "xtal_ch.h"

namespace xtal{

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
		KEYWORD_TRY,
		KEYWORD_CATCH,
		KEYWORD_FINALLY,
		KEYWORD_THROW,
		KEYWORD_CLASS,
		KEYWORD_IMPORT,
		KEYWORD_CALLEE,
		KEYWORD_THIS,
		KEYWORD_CURRENT_CONTEXT,
		KEYWORD_DOFUN,
		KEYWORD_IS,
		KEYWORD_EXPORT,
		KEYWORD_UNITTEST,
		KEYWORD_ASSERT,
		KEYWORD_PURE,
		KEYWORD_NOBREAK,
		KEYWORD_SWITCH,
		KEYWORD_CASE,
		KEYWORD_DEFAULT,
	
		KEYWORD_MAX
	};

	Token(){}
	
	Token(int_t type, int_t value, int_t flags)
		:type_((u8)type), flags_((u8)flags), ivalue_(value){}

	Token(int_t type, float_t value, int_t flags)
		:type_((u8)type), flags_((u8)flags), fvalue_(value){}

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

class LPCCommon{
public:

	LPCCommon();
		
	void init(const StringPtr& file_name);

	void error(int_t line, const AnyPtr& message);
	
	int_t register_ident(const InternedStringPtr& ident);
	int_t register_value(const AnyPtr& v);
	int_t append_ident(const InternedStringPtr& ident);
	int_t append_value(const AnyPtr& v);
	int_t append_once();
	
	int_t line;
	ArrayPtr errors;
	ArrayPtr ident_table;
	MapPtr ident_map;
	ArrayPtr value_table;
	ArrayPtr once_table;
	StringPtr source_file_name;
};

class Reader{
public:

	Reader();

	void set_stream(const StreamPtr& stream){
		stream_ = stream;
	}

	/**
	* @brief 読み進める。
	*/
	int_t read();

	/**
	* @brief 次の要素を読む。
	*/
	int_t peek();

	/**
	* @brief 次の要素が引数chと同じだったら読み進める。
	* @param ch この値と次の要素が等しい場合に読み進める。
	* @retval true 次の要素はchと同じで、読み進めた。
	* @retval false 次の要素はchと異なり、読み進めなかった。
	*/
	bool eat(int_t ch);

	/**
	* @brief 要素を一つ戻す。
	*/
	void putback(int_t ch);
	
	/**
	* @brief ポジションの取得。
	*/
	int_t position();
	
	/**
	* @brief ポジションをposの位置に戻す。
	*/
	void set_position(int_t pos);

private:

	enum{ BUF_SIZE = 1024, BUF_MASK = BUF_SIZE-1 };

	StreamPtr stream_;

	char buf_[BUF_SIZE];

	uint_t pos_;
	uint_t read_;
	uint_t marked_;
};
	

/*
* XTALプログラムソースをトークン列に変換して取り出す
*/
class Lexer{
public:

	Lexer();
	
	/**
	* @brief 初期化
	*/
	void init(const StreamPtr& stream, const StringPtr& source_file_name);
	
	/**
	* @brief 読み進める
	*/
	Token read();

	/**
	* @brief 次の要素を読む
	*/
	Token peek();

	/**
	* @brief 読み込んだ要素を一つ戻す
	*/
	void putback();
	
	/**
	* @brief 指定したトークンを一つ戻す
	* 次のreadやpeekでは、これで戻した値が得られる
	*/
	void putback(const Token& ch);
	
	/**
	* @brief 文字列を直接読むモードに変更する
	*/
	void set_string_mode();
	
	/**
	* @brief 文字列をトークンで返すモードに変更する
	*/
	void set_normal_mode();

	/**
	* @brief 現在の行数を返す
	*/
	int_t line(){ return com_.line; }
	
	/**
	* @brief 現在の行数を設定する
	*/
	void set_line(int_t v){ com_.line = v; }
	
	/**
	* @brief トークンを読める形の文字列に変換する
	*/
	StringPtr token2str(const Token& t);
	
	/**
	* @brief キーワードをInternedStringPtrに変換する
	*/
	InternedStringPtr keyword2id(int_t v);

	/**
	* @brief Lexer, Parser, CodeBuilderが共通して持つLPCCommonオブジェクトを返す
	*/
	LPCCommon* common();
	
	/**
	* @brief 文字列の記録を開始する
	*/
	void begin_record();

	/**
	* @brief 文字列の記録を終了して、それを返す。
	*/
	string_t end_record();

	/**
	* @brief 内部で使用しているメモリなど全て解放する
	*/
	void release();
	
private:

	void error(const AnyPtr&);
	
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
	MapPtr keyword_map_;

	string_t recorded_string_;
	bool recording_;

	enum{ BUF_SIZE = 1024, BUF_MASK = BUF_SIZE-1 };
	Token buf_[BUF_SIZE];

	uint_t pos_;
	uint_t read_;
	int_t left_space_;
	
	enum{ NORMAL_MODE, STRING_MODE };
	int_t mode_;
};

}

#endif
