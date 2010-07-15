#include "xtal.h"
#include "xtal_macro.h"

#include "xtal_parser.h"

#ifndef XTAL_NO_PARSER

namespace xtal{

#define c2(C1, C2) ((C2)<<8 | (C1))
#define c3(C1, C2, C3) ((C3)<<16 | (C2)<<8 | (C1))
#define c4(C1, C2, C3, C4) ((C4)<<24 | (C3)<<16 | (C2)<<8 | (C1))

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
	return test_alpha((char_t)ch) || ch_len((char_t)ch)>1 || ch>255;
}

inline bool test_ident_rest(int ch){
	return test_ident_first(ch) || test_digit(ch) || ch=='_';
}

struct KeywordIntPair{
	const char_t* key;
	int value;
};


Parser::Parser(){
	token_read_ = 0;
	token_pos_ = 0;

	ms_ = XNew<MemoryStream>();

	identifier_map_ = XNew<Map>();

	static KeywordIntPair keywords[] = {
		{ XTAL_L("if"), (int_t)Token::KEYWORD_IF}, 
		{ XTAL_L("for"), (int_t)Token::KEYWORD_FOR}, 
		{ XTAL_L("else"), (int_t)Token::KEYWORD_ELSE}, 
		{ XTAL_L("fun"), (int_t)Token::KEYWORD_FUN}, 
		{ XTAL_L("method"), (int_t)Token::KEYWORD_METHOD}, 
		{ XTAL_L("do"), (int_t)Token::KEYWORD_DO}, 
		{ XTAL_L("while"), (int_t)Token::KEYWORD_WHILE}, 
		{ XTAL_L("continue"), (int_t)Token::KEYWORD_CONTINUE}, 
		{ XTAL_L("break"), (int_t)Token::KEYWORD_BREAK}, 
		{ XTAL_L("fiber"), (int_t)Token::KEYWORD_FIBER}, 
		{ XTAL_L("yield"), (int_t)Token::KEYWORD_YIELD}, 
		{ XTAL_L("return"), (int_t)Token::KEYWORD_RETURN}, 
		{ XTAL_L("once"), (int_t)Token::KEYWORD_ONCE}, 
		{ XTAL_L("null"), (int_t)Token::KEYWORD_NULL}, 
		{ XTAL_L("undefined"), (int_t)Token::KEYWORD_UNDEFINED}, 
		{ XTAL_L("false"), (int_t)Token::KEYWORD_FALSE}, 
		{ XTAL_L("true"), (int_t)Token::KEYWORD_TRUE}, 
		{ XTAL_L("xtal"), (int_t)Token::KEYWORD_XTAL}, 
		{ XTAL_L("try"), (int_t)Token::KEYWORD_TRY}, 
		{ XTAL_L("catch"), (int_t)Token::KEYWORD_CATCH}, 
		{ XTAL_L("finally"), (int_t)Token::KEYWORD_FINALLY}, 
		{ XTAL_L("throw"), (int_t)Token::KEYWORD_THROW}, 
		{ XTAL_L("class"), (int_t)Token::KEYWORD_CLASS}, 
		{ XTAL_L("callee"), (int_t)Token::KEYWORD_CALLEE}, 
		{ XTAL_L("this"), (int_t)Token::KEYWORD_THIS}, 
		{ XTAL_L("dofun"), (int_t)Token::KEYWORD_DOFUN}, 
		{ XTAL_L("is"), (int_t)Token::KEYWORD_IS}, 
		{ XTAL_L("in"), (int_t)Token::KEYWORD_IN}, 
		{ XTAL_L("assert"), (int_t)Token::KEYWORD_ASSERT}, 
		{ XTAL_L("nobreak"), (int_t)Token::KEYWORD_NOBREAK}, 
		{ XTAL_L("switch"), (int_t)Token::KEYWORD_SWITCH}, 
		{ XTAL_L("case"), (int_t)Token::KEYWORD_CASE}, 
		{ XTAL_L("default"), (int_t)Token::KEYWORD_DEFAULT}, 
		{ XTAL_L("singleton"), (int_t)Token::KEYWORD_SINGLETON}, 
		{ XTAL_L("public"), (int_t)Token::KEYWORD_PUBLIC}, 
		{ XTAL_L("protected"), (int_t)Token::KEYWORD_PROTECTED}, 
		{ XTAL_L("private"), (int_t)Token::KEYWORD_PRIVATE}, 
	};

	identifiers_ = XNew<Array>(Token::KEYWORD_MAX);
	for(uint_t i=0; i<sizeof(keywords)/sizeof(*keywords); ++i){
		IDPtr id = intern(*(LongLivedString*)(keywords[i].key));
		identifier_map_->set_at(id, keywords[i].value);
		identifiers_->set_at(keywords[i].value, id);
	}

	/*
	">>>=",
	"<..<",
	">>>",
	"<<=",
	"<..",
	"===",
	"!==",
	"!is",
	"!in",
	"...",
	"..<",
	"::?",
	"++",
	"+=",
	"--",
	"-=",
	"~=",
	"*=",
	"/=",
	"^=",
	"%=",
	"&=",
	"&&",
	"|=",
	"||",
	">>",
	">=",
	"<<",
	"<=",
	"==",
	"!=",
	"..",
	".?",
	"::",
	"+",
	"-",
	"~",
	"*",
	"/",
	"#",
	"^",
	"%",
	"&",
	"|",
	">",
	"<",
	"=",
	"!",
	".",
	":",
	"[",
	"]",
	"(",
	")",
	"#",
	"\"",
	"'",
	";",
	"{",
	"}",
	"?"
	*/
}	

const Token& Parser::read_token(){
	const Token& ret = peek_token();
	++token_pos_;
	return ret;
}

const Token& Parser::peek_token(int_t n){
	while(token_pos_+n >= token_read_){
		int_t prev = token_read_;
		tokenize();
		if(token_read_==prev){
			static Token end(Token::TYPE_TOKEN, (int_t)0, (int_t)0);
			return end;
		}
	}
	return token_buf_[(token_pos_+n) & TOKEN_BUF_MASK];
}

void Parser::push_token(int_t v){
	token_buf_[token_read_ & TOKEN_BUF_MASK] = Token(Token::TYPE_TOKEN, left_space_ | test_right_space(executor_->peek_ascii()), v);
	token_read_++;
}
	
void Parser::push_int_token(int_t v){
	token_buf_[token_read_ & TOKEN_BUF_MASK] = Token(Token::TYPE_INT, left_space_ | test_right_space(executor_->peek_ascii()), v);
	token_read_++;
}

void Parser::push_float_token(float_t v){
	token_buf_[token_read_ & TOKEN_BUF_MASK] = Token(Token::TYPE_FLOAT, left_space_ | test_right_space(executor_->peek_ascii()), v);
	token_read_++;
}
	
void Parser::push_keyword_token(int_t num){
	token_buf_[token_read_ & TOKEN_BUF_MASK] = Token(Token::TYPE_KEYWORD, left_space_ | test_right_space(executor_->peek_ascii()), num);
	token_read_++;
}
	
void Parser::push_identifier_token(int_t num){
	token_buf_[token_read_ & TOKEN_BUF_MASK] = Token(Token::TYPE_IDENTIFIER, left_space_ | test_right_space(executor_->peek_ascii()), num);
	token_read_++;
}

void Parser::putback_token(){
	token_pos_--;
}

void Parser::putback_token(const Token& ch){
	token_pos_--;
	token_buf_[token_pos_ & TOKEN_BUF_MASK] = ch;
}

float_t Parser::read_finteger(){
	float_t ret = 0;
	for(;;){
		if(test_digit(executor_->peek_ascii())){
			ret *= 10;
			ret += executor_->read_ascii()-'0';
		}
		else if(executor_->peek_ascii()=='_'){
			executor_->skip();
		}
		else{
			break;
		}
	}
	return ret;
}

int_t Parser::read_integer(int_t base){
	int_t ret = 0;
	for(;;){
		int_t num = 0;
		if(test_digit(executor_->peek_ascii())){
			num = executor_->read_ascii()-'0';
		}
		else if(test_range(executor_->peek_ascii(), 'a', 'z')){
			num = executor_->read_ascii()-'a' + 10;
		}
		else if(test_range(executor_->peek_ascii(), 'A', 'Z')){
			num = executor_->read_ascii()-'A' + 10;
		}
		else if(executor_->peek_ascii()=='_'){
			executor_->skip();
			continue;
		}
		else{
			break;
		}

		if(num>=base){
			break;
		}

		ret *= base;
		ret += num;
	}

	if(test_ident_rest(executor_->peek_ascii())){
		executor_->error(Xt("XCE1015")->call(Named(Xid(n), base)));
	}

	return ret;		
}

bool Parser::is_integer_literal(){
	int_t i = 0;
	while(test_digit(executor_->peek_ascii(i)) || executor_->peek_ascii(i)=='_'){
		i++;
	}

	if(executor_->peek_ascii(i)=='f' || executor_->peek_ascii(i)=='F'){
		return false;
	}

	if(executor_->peek_ascii(i)=='.' && test_digit(executor_->peek_ascii(i+1))){
		return false;
	}

	return true;
}

void Parser::tokenize_number(){
	if(executor_->eat_ascii('0')){
		if(executor_->eat_ascii('x') || executor_->eat_ascii('X')){
			push_int_token(read_integer(16));
			return;
		}
		else if(executor_->eat_ascii('o')){
			push_int_token(read_integer(8));
			return;
		}
		else if(executor_->eat_ascii('b') || executor_->eat_ascii('B')){
			push_int_token(read_integer(2));
			return;
		}
	}
	
	if(is_integer_literal()){
		push_int_token(read_integer(10));
		return;		
	}

	float_t ival = read_finteger();
	
	executor_->skip(); // skip '.'

	float_t scale = 1;
	float_t fval = 0;
	for(;;){
		if(test_digit(executor_->peek_ascii())){
			scale /= 10;
			fval += (executor_->read_ascii()-'0')*scale;
		}
		else if(executor_->peek_ascii()=='_'){
			executor_->skip();
		}
		else{
			break;
		}
	}

	fval += ival;
	if(executor_->eat_ascii('e') || executor_->eat_ascii('E')){
		int_t e = 1;
		if(executor_->eat_ascii('-')){
			e = -1;
		}
		else{
			executor_->eat_ascii('+');
		}

		if(!test_digit(executor_->peek_ascii())){
			executor_->error(Xt("XCE1014"));
		}

		e *= read_integer(10);

		{
			using namespace std;
			fval *= (float_t)pow((float_t)10, (float_t)e);
		}
	}

	if(!executor_->eat_ascii('f')){
		executor_->eat_ascii('F');
	}
	
	if(test_ident_rest(executor_->peek_ascii())){
		executor_->error(Xt("XCE1010"));
	}

	push_float_token(fval);
}
	
//////////////////////////////////////////

void Parser::tokenize(){
	left_space_ = 0;
	
	do{

		int_t ch = executor_->peek_ascii();
		
		switch(ch){

			XTAL_DEFAULT{

				if(ch!=0 && test_ident_first(ch)){
					ms_->clear();
					ms_->put_s(executor_->read());
					while(test_ident_rest(executor_->peek_ascii())){
						ms_->put_s(executor_->read());
					}
					IDPtr identifier = ms_->to_s()->intern();
					if(const AnyPtr& key = identifier_map_->at(identifier)){
						int_t n = XTAL_detail_ivalue(key);
						if(n<Token::KEYWORD_MAX){
							push_keyword_token(n);
						}
						else{
							push_identifier_token(n);
						}
					}
					else{
						int_t n = identifiers_->size();
						identifier_map_->set_at(identifier, n);
						identifiers_->push_back(identifier);
						push_identifier_token(n);
					}
				}
				else if(test_digit(ch)){
					tokenize_number();
					return;
				}
				else{
					executor_->skip();
					push_token(ch);
				}
			}
			
			XTAL_CASE('+'){ 
				executor_->skip();
				if(executor_->eat_ascii('+')){ push_token(c2('+', '+')); }
				else if(executor_->eat_ascii('=')){ push_token(c2('+', '=')); }
				else{ push_token('+'); }
			}
			
			XTAL_CASE('-'){ 
				executor_->skip();
				if(executor_->eat_ascii('-')){ push_token(c2('-', '-')); }
				else if(executor_->eat_ascii('=')){ push_token(c2('-', '=')); }
				else{ push_token('-'); }
			}
			
			XTAL_CASE('~'){ 
				executor_->skip();
				if(executor_->eat_ascii('=')){ push_token(c2('~', '=')); }
				else{ push_token('~'); }
			}
			
			XTAL_CASE('*'){ 
				executor_->skip();
				if(executor_->eat_ascii('=')){ push_token(c2('*', '=')); }
				else{ push_token('*'); }
			}
			
			XTAL_CASE('/'){ 
				executor_->skip();
				if(executor_->eat_ascii('=')){
					push_token(c2('/', '='));
				}
				else if(executor_->eat_ascii('/')){
					for(;;){
						int_t ch = executor_->read_ascii();
						if(ch=='\r'){
							executor_->eat_ascii('\n');
							left_space_ = Token::FLAG_LEFT_SPACE;
							break;
						}
						else if(ch=='\n'){
							left_space_ = Token::FLAG_LEFT_SPACE;
							break;
						}
						else if(ch==0){
							break;
						}
					}
					continue;
				}
				else if(executor_->eat_ascii('*')){
					for(;;){
						int_t ch = executor_->read_ascii();
						if(ch=='*'){
							if(executor_->eat_ascii('/')){
								left_space_ = Token::FLAG_LEFT_SPACE;
								break;
							}
						}
						else if(ch==0){
							executor_->error(Xt("XCE1021"));
							break;
						}
					}
					continue;
				}
				else{
					push_token('/');
				}
			}			
			
			XTAL_CASE('#'){
				executor_->skip();
				if(executor_->eat_ascii('!')){
					for(;;){
						int_t ch = executor_->read_ascii();
						if(ch=='\r'){
							executor_->eat_ascii('\n');
							left_space_ = Token::FLAG_LEFT_SPACE;
							break;
						}
						else if(ch=='\n'){
							left_space_ = Token::FLAG_LEFT_SPACE;
							break;
						}
						else if(ch==0){
							break;
						}
					}
					continue;
				}
				else{
					push_token('#');
				}
			}			
				
			XTAL_CASE('^'){ 
				executor_->skip();
				if(executor_->eat_ascii('=')){ push_token(c2('^', '=')); }
				else{ push_token('^'); }
			}

			XTAL_CASE('%'){ 
				executor_->skip();
				if(executor_->eat_ascii('=')){ push_token(c2('%', '=')); }
				else{ push_token('%'); }
			}
			
			XTAL_CASE('&'){ 
				executor_->skip();
				if(executor_->eat_ascii('=')){ push_token(c2('&', '=')); }
				else if(executor_->eat_ascii('&')){ push_token(c2('&', '&')); }
				else{ push_token('&'); }
			}
			
			XTAL_CASE('|'){ 
				executor_->skip();
				if(executor_->eat_ascii('=')){ push_token(c2('|', '=')); }
				else if(executor_->eat_ascii('|')){ push_token(c2('|', '|')); }
				else{ push_token('|'); }
			}
						
			XTAL_CASE('>'){ 
				executor_->skip();
				if(executor_->eat_ascii('>')){
					if(executor_->eat_ascii('>')){
						if(executor_->eat_ascii('=')){
							push_token(c4('>','>','>','='));
						}
						else{
							push_token(c3('>','>','>'));
						}
					}
					else{
						push_token(c2('>','>'));
					}
				}
				else if(executor_->eat_ascii('=')){
					push_token(c2('>', '='));
				}
				else{
					push_token('>');
				}
			}
			
			XTAL_CASE('<'){ 
				executor_->skip();
				if(executor_->eat_ascii('<')){
					if(executor_->eat_ascii('=')){
						push_token(c3('<','<','='));
					}
					else{
						push_token(c2('<','<'));
					}
				}
				else if(executor_->eat_ascii('=')){
					push_token(c2('<', '='));
				}
				else if(executor_->eat_ascii('.')){
					if(!executor_->eat_ascii('.')){
						executor_->error(Xt("XCE1001"));					
					}

					if(executor_->eat_ascii('<')){
						push_token(c4('<', '.', '.', '<'));
					}
					else{
						push_token(c3('<', '.', '.'));
					}
				}
				else{
					push_token('<');
				}
			}
			
			XTAL_CASE('='){ 
				executor_->skip();
				if(executor_->eat_ascii('=')){
					if(executor_->eat_ascii('=')){
						push_token(c3('=', '=', '='));
					}
					else{
						push_token(c2('=', '='));
					}
				}
				else{
					push_token('=');
				}
			}
			
			XTAL_CASE('!'){ 
				executor_->skip();
				if(executor_->eat_ascii('=')){
					if(executor_->eat_ascii('=')){
						push_token(c3('!', '=', '='));
					}
					else{
						push_token(c2('!', '='));
					}
				}
				else if(executor_->peek_ascii()=='i'){
					if(executor_->peek_ascii(1)=='s'){
						if(!test_ident_rest(executor_->peek_ascii(2))){
							executor_->skip();
							executor_->skip();
							push_token(c3('!', 'i', 's'));
						}
						else{
							push_token('!');
						}
					}
					else if(executor_->peek_ascii(1)=='n'){
						if(!test_ident_rest(executor_->peek_ascii(2))){
							executor_->skip();
							executor_->skip();
							push_token(c3('!', 'i', 'n'));
						}
						else{
							push_token('!');
						}
					}
					else{
						push_token('!');
					}
				}
				else{
					push_token('!');
				}
			}
			
			XTAL_CASE('.'){ 
				if(test_digit(executor_->peek_ascii(1))){
					tokenize_number();
					return;
				}
				
				executor_->skip();
				if(executor_->eat_ascii('.')){
					if(executor_->eat_ascii('.')){ push_token(c3('.', '.', '.')); }
					else if(executor_->eat_ascii('<')){ push_token(c3('.', '.', '<')); }
					else{ push_token(c2('.', '.')); }
				}
				else if(executor_->eat_ascii('?')){ push_token(c2('.', '?')); }
				else{ push_token('.'); }
			}
			
			XTAL_CASE(':'){ 
				executor_->skip();
				if(executor_->eat_ascii(':')){
					if(executor_->eat_ascii('?')){ push_token(c3(':', ':', '?')); }
					else{ push_token(c2(':', ':')); }
				}
				else{ push_token(':'); }
			}

			XTAL_CASE('\''){ 
				executor_->skip();
				IDPtr identifier = read_string('\'', '\'')->intern();

				if(const AnyPtr& key = identifier_map_->at(identifier)){
					int_t n = XTAL_detail_ivalue(key);
					push_identifier_token(n);
				}
				else{
					int_t n = identifiers_->size();
					identifier_map_->set_at(identifier, n);
					identifiers_->push_back(identifier);
					push_identifier_token(n);
				}
			}

			XTAL_CASE4(' ', '\t', '\r', '\n'){
				deplete_space();
				left_space_ = Token::FLAG_LEFT_SPACE;
				continue;
			}

#ifdef XTAL_USE_WCHAR

			XTAL_CASE((uchar_t)0xFEFF){
				executor_->skip();
				continue;
			}

			XTAL_CASE((uchar_t)0xFFFE){
				executor_->skip();
				continue;
			}

#else
			XTAL_CASE((uchar_t)239){
				if((uchar_t)executor_->peek_ascii(1)==(uchar_t)187 && (uchar_t)executor_->peek_ascii(2)==(uchar_t)191){
					executor_->skip();
					executor_->skip();
					executor_->skip();
					continue;
				}
				push_token(ch);
			}
#endif

			XTAL_CASE(0){
				push_token(0);
			}
		}
			
		break;
	}while(true);

}

void Parser::deplete_space(){
	for(;;){
		int_t ch = executor_->peek_ascii();
		if(ch=='\r'){
			executor_->skip();
			executor_->eat_ascii('\n');
		}
		else if(ch=='\n'){
			executor_->skip();
		}
		else if(ch==' ' || ch=='\t'){
			executor_->skip();
		}
		else{
			return;
		}
	}
}

int_t Parser::test_right_space(int_t ch){
	if(test_space(ch)){
		return Token::FLAG_RIGHT_SPACE;
	}
	return 0;
}

StringPtr Parser::read_string(int_t open, int_t close){
	ms_->clear();

	int_t depth = 1;
	for(;;){

		AnyPtr ach = executor_->read();
		int_t ch = XTAL_detail_chvalue(ach);
		if(ch==close){
			--depth;
			if(depth==0){
				break;
			}
		}

		if(ch==open){
			++depth;
		}

		if(ch==0){
			executor_->error(Xt("XCE1011"));
			break;
		}

		if(ch=='\\'){
			char_t chs[2];
			int_t n = 0;
			switch(executor_->peek_ascii()){
				XTAL_DEFAULT{ 
					chs[n++] = '\\';
					chs[n++] = (char_t)executor_->peek_ascii();
				}
				
				XTAL_CASE('n'){ chs[n++] = '\n'; }
				XTAL_CASE('r'){ chs[n++] = '\r'; }
				XTAL_CASE('t'){ chs[n++] = '\t'; }
				XTAL_CASE('f'){ chs[n++] = '\f'; }
				XTAL_CASE('b'){ chs[n++] = '\b'; }
				XTAL_CASE('\\'){ chs[n++] = '\\'; }
				XTAL_CASE('"'){ chs[n++] = '"'; } 
				
				XTAL_CASE('\r'){ 
					if(executor_->peek_ascii()=='\n'){
						executor_->skip();
					}

					chs[n++] = '\r';
					chs[n++] = '\n';
				}
				
				XTAL_CASE('\n'){ 
					chs[n++] = '\n';
				}
			}
			ms_->write(chs, n*sizeof(char_t));
			executor_->skip();
		}
		else{
			if(ch=='\r'){
				if(executor_->peek_ascii()=='\n'){
					executor_->skip();
				}
				char_t chs[2];
				int_t n = 0;
				chs[n++] = '\r';
				chs[n++] = '\n';
				ms_->write(chs, n*sizeof(char_t));
			}
			else if(ch=='\n'){
				char_t chs[2];
				int_t n = 0;
				chs[n++] = '\n';
				ms_->write(chs, n*sizeof(char_t));
			}
			else{
				const StringPtr& str = (StringPtr&)ach;
				ms_->write(str->data(), str->data_size()*sizeof(char_t));
			}
		}	
	}

	return ms_->to_s();
}


enum{//Expressions priority
	
	PRI_BEGIN_ = 0x1000,

	PRI_LOOP,

	PRI_CATCH,

	PRI_Q,

	PRI_OROR,
	PRI_ANDAND,

	PRI_OR,
	PRI_XOR,
	PRI_AND,

	PRI_EQ,
		PRI_NE = PRI_EQ,
		PRI_LT = PRI_EQ,
		PRI_GT = PRI_EQ,
		PRI_LE = PRI_EQ,
		PRI_GE = PRI_EQ,
		PRI_RAWEQ = PRI_EQ,
		PRI_RAWNE = PRI_EQ,
		PRI_IN = PRI_EQ,
		PRI_NIN = PRI_EQ,
		PRI_IS = PRI_EQ,
		PRI_NIS = PRI_EQ,

	PRI_SHL,
		PRI_SHR = PRI_SHL,
		PRI_USHR = PRI_SHL,

	PRI_ADD, 
		PRI_SUB = PRI_ADD, 
		PRI_CAT = PRI_ADD,
	
	PRI_MUL, 
		PRI_DIV = PRI_MUL, 
		PRI_MOD = PRI_MUL,

	PRI_NEG,
		PRI_POS = PRI_NEG,
		PRI_COM = PRI_NEG,
		PRI_NOT = PRI_NEG,

	PRI_AT,
		PRI_SEND = PRI_AT,
		PRI_CALL = PRI_AT,
		PRI_RANGE = PRI_AT,

	PRI_MEMBER,
		PRI_NS = PRI_MEMBER,

	PRI_ONCE,

	PRI_END_,

	PRI_MAX = PRI_END_-PRI_BEGIN_
};



void Parser::parse(const xpeg::ExecutorPtr& executor){
	executor_ = executor;
	parse_toplevel();
}

void Parser::parse_eval(const xpeg::ExecutorPtr& executor){
	executor_ = executor;
	parse_stmt();
}

StringPtr Parser::token_to_string(const Token& ch){
	if(ch.type()==Token::TYPE_IDENTIFIER || ch.type()==Token::TYPE_KEYWORD){
		return identifier(ch.identifier_number());
	}
	else if(ch.type()==Token::TYPE_INT || ch.type()==Token::TYPE_FLOAT){
		return XTAL_STRING("<number>");
	}
	else{
		int_t n = ch.ivalue();
		char_t buf[] = {((n>>0)&0xff), ((n>>8)&0xff), ((n>>16)&0xff), ((n>>24)&0xff), 0};

		if(buf[0]==0){
			return XTAL_STRING("<end of stream>");			
		}

		return xnew<String>(buf);
	}
}

void Parser::expect(int_t ach){
	if(eat(ach)){
		executor_->bin();
		return;
	}

	const Token& ch = peek_token();
	Token rch(Token::TYPE_TOKEN, 0, ach);
	executor_->error(Xt("XCE1002")->call(Named(Xid(required), token_to_string(rch)), Named(Xid(char), token_to_string(ch))));
}

bool Parser::eat(int_t ch){
	const Token& n = peek_token();
	if(n.type() == Token::TYPE_TOKEN){
		if(n.ivalue()==ch){
			read_token();
			return true;
		}
	}
	return false;
}

bool Parser::eat(Token::Keyword kw){
	const Token& n = peek_token();
	if(n.type() == Token::TYPE_KEYWORD){
		if(n.keyword_number()==kw){
			read_token();
			return true;
		}
	}
	return false;
}

bool Parser::parse_term(){
	const Token& ch = read_token();
	int_t r_space = ch.right_space() ? PRI_MAX : 0;

	switch(ch.type()){
		XTAL_NODEFAULT;

		XTAL_CASE(Token::TYPE_TOKEN){
			switch(ch.ivalue()){

				XTAL_DEFAULT{}

				XTAL_CASE('('){ 
					if(parse_expr()){
						if(eat(',')){
							parse_exprs(true);
							executor_->tree_splice(EXPR_VALUES, 1);
						}
						else{
							if(ep(executor_->tree_back())->itag()==EXPR_PROPERTY){
								executor_->tree_splice(EXPR_BRACKET, 1);
							}	
						}
					}
					else{
						executor_->tree_splice(EXPR_UNDEFINED, 0);
					}
					expect(')'); 
					return true; 
				}

				XTAL_CASE('['){ parse_array();  return true; }
				XTAL_CASE('|'){ parse_lambda(); return true; }
				XTAL_CASE(c2('|', '|')){ parse_lambda(true); return true; }

				XTAL_CASE('_'){ expect_parse_identifier(); executor_->tree_splice(EXPR_IVAR, 1); return true; }

				XTAL_CASE('"'){ 
					executor_->tree_push_back(KIND_STRING);
					executor_->tree_push_back(read_string('"', '"'));
					executor_->tree_splice(EXPR_STRING, 2);
					return true; 
				}
				
				XTAL_CASE('%'){
					int_t ch = executor_->read_ascii();
					int_t kind = KIND_STRING;

					if(ch=='t'){
						kind = KIND_TEXT;
						ch = executor_->read_ascii();
					}
					else if(ch=='f'){
						kind = KIND_FORMAT;
						ch = executor_->read_ascii();
					}

					int_t open = ch;
					int_t close = 0;

					switch(open){
						case '!': case '?': case '"': case '&': //"
						case '#': case '\'':case '|': case ':':
						case '^': case '+': case '-': case '*':
						case '/': case '@': case '$': case '.':
						case '=': case '~': case '`': case ';':
							close = open; break;

						case '(': close = ')'; break;
						case '<': close = '>'; break;
						case '{': close = '}'; break;
						case '[': close = ']'; break;

						default:
							close = open;
							executor_->error(Xt("XCE1017"));
							break;
					}

					executor_->tree_push_back(kind);
					executor_->tree_push_back(read_string(open, close));
					executor_->tree_splice(EXPR_STRING, 2);
					return true; 
				}
				
////////////////////////////////////////////////////////////////////////////////////////

				XTAL_CASE('+'){ expect_parse_expr(PRI_POS, r_space); executor_->tree_splice(EXPR_POS, 1); return true; }
				XTAL_CASE('-'){ expect_parse_expr(PRI_NEG, r_space); executor_->tree_splice(EXPR_NEG, 1); return true; }
				XTAL_CASE('~'){ expect_parse_expr(PRI_COM, r_space); executor_->tree_splice(EXPR_COM, 1); return true; }
				XTAL_CASE('!'){ expect_parse_expr(PRI_NOT, r_space); executor_->tree_splice(EXPR_NOT, 1); return true; }
			}
		}

		XTAL_CASE(Token::TYPE_KEYWORD){
			switch(ch.keyword_number()){

				XTAL_DEFAULT{}
				
				XTAL_CASE(Token::KEYWORD_ONCE){ expect_parse_expr(PRI_ONCE - r_space*2, 0); executor_->tree_splice(EXPR_ONCE, 1); return true; }
				XTAL_CASE(Token::KEYWORD_CLASS){ parse_class(KIND_CLASS); return true; }
				XTAL_CASE(Token::KEYWORD_SINGLETON){ parse_class(KIND_SINGLETON); return true; }
				XTAL_CASE(Token::KEYWORD_FUN){ parse_fun(KIND_FUN); return true; }
				XTAL_CASE(Token::KEYWORD_METHOD){ parse_fun(KIND_METHOD); return true; }
				XTAL_CASE(Token::KEYWORD_FIBER){ parse_fun(KIND_FIBER); return true; }
				XTAL_CASE(Token::KEYWORD_CALLEE){ executor_->tree_splice(EXPR_CALLEE, 0); return true; }
				XTAL_CASE(Token::KEYWORD_NULL){ executor_->tree_splice(EXPR_NULL, 0); return true; }
				XTAL_CASE(Token::KEYWORD_UNDEFINED){ executor_->tree_splice(EXPR_UNDEFINED, 0); return true; }
				XTAL_CASE(Token::KEYWORD_TRUE){ executor_->tree_splice(EXPR_TRUE, 0); return true; }
				XTAL_CASE(Token::KEYWORD_FALSE){ executor_->tree_splice(EXPR_FALSE, 0); return true; }
				XTAL_CASE(Token::KEYWORD_THIS){ executor_->tree_splice(EXPR_THIS, 0); return true; }
				XTAL_CASE(Token::KEYWORD_YIELD){ parse_exprs(); executor_->tree_splice(EXPR_YIELD, 1); return true; }

				XTAL_CASE(Token::KEYWORD_DOFUN){ 
					parse_fun(KIND_FUN);
					executor_->tree_push_back(null);
					executor_->tree_push_back(null);
					executor_->tree_splice(EXPR_CALL, 3);
					return true; 
				}
			}
		}
		
		XTAL_CASE(Token::TYPE_INT){ executor_->tree_push_back(ch.ivalue()); executor_->tree_splice(EXPR_NUMBER, 1); return true; }
		XTAL_CASE(Token::TYPE_FLOAT){ executor_->tree_push_back(ch.fvalue()); executor_->tree_splice(EXPR_NUMBER, 1); return true; }
		XTAL_CASE(Token::TYPE_IDENTIFIER){ executor_->tree_push_back(identifier(ch.identifier_number())); executor_->tree_splice(EXPR_LVAR, 1); return true; }
	}

	putback_token(ch);
	return false;
}

bool Parser::cmp_pri(int_t pri, int_t op, int_t l_space, int_t r_space){
	bool one = pri < op;
	bool two = pri-l_space < op-r_space;
	if(one!=two){
		executor_->error(Xt("XCE1028"));
	}
	return one;
}

bool Parser::expr_end(){
	const Token& prevch = peek_token(-1);
	return prevch.type()==Token::TYPE_TOKEN && prevch.ivalue()=='}';
}

bool Parser::make_bin_expr(const Token& ch, int_t space, int_t pri, int_t PRI, int_t EXPR){
	int_t r_space = (ch.right_space()) ? PRI_MAX : 0;
	int_t l_space = (ch.left_space()) ? PRI_MAX : 0;
	if(cmp_pri(pri, PRI, space, l_space)){ 
		expect_parse_expr(PRI, r_space); 
		executor_->tree_splice(EXPR, 2); 
		return true; 
	}
	putback_token(ch);
	return false;
}

bool Parser::parse_post(int_t pri, int_t space){
	if(expr_end()){
		const Token& ch = peek_token();

		if(ch.type()==Token::TYPE_TOKEN && (ch.ivalue()=='.' || ch.ivalue()==c2('.','?'))){
		
		}
		else{
			return false;
		}
	}

	Token ch = read_token();
	int_t r_space = (ch.right_space()) ? PRI_MAX : 0;
	int_t l_space = (ch.left_space()) ? PRI_MAX : 0;
	switch(ch.type()){
	
		XTAL_DEFAULT{}
		
		XTAL_CASE(Token::TYPE_KEYWORD){
			switch(ch.keyword_number()){
				XTAL_DEFAULT{}
				
				XTAL_CASE(Token::KEYWORD_IS){ return make_bin_expr(ch, space, pri, PRI_IS, EXPR_IS); }
				XTAL_CASE(Token::KEYWORD_IN){ return make_bin_expr(ch, space, pri, PRI_IN, EXPR_IN); }
				XTAL_CASE(Token::KEYWORD_CATCH){ 
					if(cmp_pri(pri, PRI_CATCH, space, l_space)){
						expect('(');
						expect_parse_identifier();
						expect(')');
						expect_parse_expr(PRI_CATCH, r_space); 
						executor_->tree_splice(EXPR_CATCH, 3);
						return true; 
					} 
				}
			}
		}
		
		XTAL_CASE(Token::TYPE_TOKEN){
			switch(ch.ivalue()){

				XTAL_DEFAULT{}
			
				XTAL_CASE('+'){ return make_bin_expr(ch, space, pri, PRI_ADD, EXPR_ADD); }
				XTAL_CASE('-'){ return make_bin_expr(ch, space, pri, PRI_SUB, EXPR_SUB); }
				XTAL_CASE('~'){ return make_bin_expr(ch, space, pri, PRI_CAT, EXPR_CAT); }
				XTAL_CASE('*'){ return make_bin_expr(ch, space, pri, PRI_MUL, EXPR_MUL); }
				XTAL_CASE('/'){ return make_bin_expr(ch, space, pri, PRI_DIV, EXPR_DIV); }
				XTAL_CASE('%'){ return make_bin_expr(ch, space, pri, PRI_MOD, EXPR_MOD); }
				XTAL_CASE('^'){ return make_bin_expr(ch, space, pri, PRI_XOR, EXPR_XOR); }
				XTAL_CASE(c2('&','&')){ return make_bin_expr(ch, space, pri, PRI_ANDAND, EXPR_ANDAND); }
				XTAL_CASE('&'){ return make_bin_expr(ch, space, pri, PRI_AND, EXPR_AND); }
				XTAL_CASE(c2('|','|')){ return make_bin_expr(ch, space, pri, PRI_OROR, EXPR_OROR); }
				XTAL_CASE('|'){ return make_bin_expr(ch, space, pri, PRI_OR, EXPR_OR); }
				XTAL_CASE(c2('<','<')){ return make_bin_expr(ch, space, pri, PRI_SHL, EXPR_SHL); }
				XTAL_CASE(c2('>','>')){ return make_bin_expr(ch, space, pri, PRI_SHR, EXPR_SHR); }
				XTAL_CASE(c3('>','>','>')){ return make_bin_expr(ch, space, pri, PRI_USHR, EXPR_USHR); }
				XTAL_CASE(c2('<','=')){ return make_bin_expr(ch, space, pri, PRI_LE, EXPR_LE); }
				XTAL_CASE('<'){ return make_bin_expr(ch, space, pri, PRI_LT, EXPR_LT); }
				XTAL_CASE(c2('>','=')){ return make_bin_expr(ch, space, pri, PRI_GE, EXPR_GE); }
				XTAL_CASE('>'){ return make_bin_expr(ch, space, pri, PRI_GT, EXPR_GT); }
				XTAL_CASE(c2('=','=')){ return make_bin_expr(ch, space, pri, PRI_EQ, EXPR_EQ); }
				XTAL_CASE(c2('!','=')){ return make_bin_expr(ch, space, pri, PRI_NE, EXPR_NE); }
				XTAL_CASE(c3('=','=','=')){ return make_bin_expr(ch, space, pri, PRI_RAWEQ, EXPR_RAWEQ); }
				XTAL_CASE(c3('!','=','=')){ return make_bin_expr(ch, space, pri, PRI_RAWNE, EXPR_RAWNE); }
				XTAL_CASE(c3('!','i','s')){ return make_bin_expr(ch, space, pri, PRI_NIS, EXPR_NIS); }
				XTAL_CASE(c3('!','i','n')){ return make_bin_expr(ch, space, pri, PRI_NIN, EXPR_NIN); }
				
				XTAL_CASE4(c2(':',':'), '.', c3(':',':','?'), c2('.', '?')){
					if(cmp_pri(pri, PRI_MEMBER, space, l_space)){
						if(eat('(')){
							expect_parse_expr();
							expect(')');
						}
						else{
							parse_identifier_or_keyword();
						}

						int_t r_space = (peek_token().right_space() || peek_token().left_space()) ? PRI_MAX : 0;
						if(eat('#')){
							expect_parse_expr(PRI_NS, r_space);
						}
						else{
							executor_->tree_push_back(null);
						}

						switch(ch.ivalue()){
							XTAL_NODEFAULT;
							XTAL_CASE(c2(':',':')){ executor_->tree_splice(EXPR_MEMBER, 3); }
							XTAL_CASE('.'){ executor_->tree_splice(EXPR_PROPERTY, 3); }
							XTAL_CASE(c3(':',':','?')){ executor_->tree_splice(EXPR_MEMBER_Q, 3); }
							XTAL_CASE(c2('.', '?')){ executor_->tree_splice(EXPR_PROPERTY_Q, 3); }
						}
						return true;
					}
				}

				XTAL_CASE('?'){
					if(cmp_pri(pri, PRI_Q, space, l_space)){
						expect_parse_expr();
						expect(':');
						expect_parse_expr();
						executor_->tree_splice(EXPR_Q, 3);
						return true;
					}
				}
				
				XTAL_CASE4(c2('.', '.'), c3('.', '.', '<'), c3('<', '.', '.'), c4('<', '.', '.', '<')){
					if(cmp_pri(pri, PRI_RANGE, space, l_space)){
						expect_parse_expr(PRI_RANGE, r_space);
						switch(ch.ivalue()){
							XTAL_NODEFAULT;
							XTAL_CASE(c2('.', '.')){ executor_->tree_insert(2, RANGE_CLOSED); }
							XTAL_CASE(c3('.', '.', '<')){ executor_->tree_insert(2, RANGE_LEFT_CLOSED_RIGHT_OPEN); }
							XTAL_CASE(c3('<', '.', '.')){ executor_->tree_insert(2, RANGE_LEFT_OPEN_RIGHT_CLOSED); }
							XTAL_CASE(c4('<', '.', '.', '<')){ executor_->tree_insert(2, RANGE_OPEN); }
						}
						executor_->tree_splice(EXPR_RANGE, 3);
						return true;
					}
				}

				XTAL_CASE('('){
					if(cmp_pri(pri, PRI_CALL, space, l_space)){
						parse_call();
						return true;
					}
				}

				XTAL_CASE('['){
					if(cmp_pri(pri, PRI_AT, space, l_space)){
						if(eat(':')){
							expect(']');
							executor_->tree_push_back(Xid(op_to_map));
							executor_->tree_push_back(null);
							executor_->tree_splice(EXPR_PROPERTY, 3);
						}
						else if(eat(']')){
							executor_->tree_push_back(Xid(op_to_array));
							executor_->tree_push_back(null);
							executor_->tree_splice(EXPR_PROPERTY, 3);
						}
						else{
							expect_parse_expr();
							executor_->tree_splice(EXPR_AT, 2);
							expect(']');
						}
						return true;
					}
				}
			}
		}
	}

	putback_token(ch);
	return false;
}

void Parser::parse_else_or_nobreak(){
	if(eat(Token::KEYWORD_ELSE)){
		expect_parse_stmt();
		executor_->tree_push_back(null);
	}
	else if(eat(Token::KEYWORD_NOBREAK)){
		executor_->tree_push_back(null);
		expect_parse_stmt();
	}
	else{
		executor_->tree_push_back(null);
		executor_->tree_push_back(null);
	}
}

void Parser::parse_each(){
	ExprPtr lhs = ep(executor_->tree_pop_back());
	IDPtr label = ptr_cast<ID>(executor_->tree_pop_back());

	ExprPtr params = xnew<Expr>();

	executor_->tree_push_back(Xid(iterator));
	executor_->tree_splice(EXPR_LVAR, 1);
	params->push_back(executor_->tree_pop_back());

	if(eat('|')){ // ブロックパラメータ
		for(;;){
			const Token& ch = peek_token();
			if(ch.type()==ch.TYPE_IDENTIFIER){
				read_token();
				executor_->tree_push_back(identifier(ch.identifier_number()));
				executor_->tree_splice(EXPR_LVAR, 1);
				params->push_back(executor_->tree_pop_back());
				if(!eat(',')){
					expect('|');
					break;
				}
			}
			else{
				expect('|');
				break;
			}
		}
	}
	
	if(params->size()==1){
		executor_->tree_push_back(Xid(it));
		executor_->tree_splice(EXPR_LVAR, 1);
		params->push_back(executor_->tree_pop_back());
	}

	ExprPtr scope = xnew<Expr>();
	
	{
		executor_->tree_push_back(params); // 多重代入の左辺

		executor_->tree_push_back(lhs);
		executor_->tree_push_back(Xid(block_first));
		executor_->tree_push_back(null);
		executor_->tree_splice(EXPR_PROPERTY, 3);
		executor_->tree_splice(0, 1); // 多重代入の右辺

		executor_->tree_splice(EXPR_MDEFINE, 2);
	}

	scope->push_back(executor_->tree_pop_back());

	{
		executor_->tree_push_back(label);

		executor_->tree_push_back(null);

		{
			executor_->tree_push_back(Xid(iterator));
			executor_->tree_splice(EXPR_LVAR, 1);
		}

		{
			executor_->tree_push_back(params);
			executor_->tree_push_back(Xid(iterator));
			executor_->tree_splice(EXPR_LVAR, 1);
			executor_->tree_push_back(Xid(block_next));
			executor_->tree_push_back(null);
			executor_->tree_splice(EXPR_PROPERTY, 3);
			executor_->tree_splice(0, 1);
			executor_->tree_splice(EXPR_MASSIGN, 2);
		}

		parse_scope();

		parse_else_or_nobreak();

		executor_->tree_splice(EXPR_FOR, 7);
	}

	ExprPtr loop = ep(executor_->tree_pop_back());

	{
		executor_->tree_push_back(Xid(iterator));
		executor_->tree_splice(EXPR_LVAR, 1);
		executor_->tree_push_back(Xid(block_catch));
		executor_->tree_push_back(null);
		executor_->tree_splice(EXPR_PROPERTY_Q, 3);

		executor_->tree_push_back(null);
		executor_->tree_push_back(Xid(e));
		executor_->tree_splice(EXPR_LVAR, 1);
		executor_->tree_splice(0, 2);
		executor_->tree_splice(0, 1);
		executor_->tree_push_back(null);
		executor_->tree_splice(EXPR_CALL, 3);
		executor_->tree_splice(EXPR_NOT, 1);

		executor_->tree_push_back(Xid(e));
		executor_->tree_splice(EXPR_LVAR, 1);
		executor_->tree_splice(EXPR_THROW, 1);

		executor_->tree_push_back(null);

		executor_->tree_splice(EXPR_IF, 3);
	}

	ExprPtr block_catch = ep(executor_->tree_pop_back());

	executor_->tree_push_back(loop);

	executor_->tree_push_back(Xid(e));
	executor_->tree_push_back(block_catch);

	executor_->tree_push_back(Xid(iterator));
	executor_->tree_splice(EXPR_LVAR, 1);
	executor_->tree_push_back(Xid(block_break));
	executor_->tree_push_back(null);
	executor_->tree_splice(EXPR_PROPERTY_Q, 3);

	executor_->tree_splice(EXPR_TRY, 4);
	
	scope->push_back(executor_->tree_pop_back());
	executor_->tree_push_back(scope);
	executor_->tree_splice(EXPR_SCOPE, 1);
}

void Parser::parse_for(){
	expect('(');
	if(!parse_assign_stmt()) executor_->tree_push_back(null);
	expect(';');

	if(!parse_expr()) executor_->tree_push_back(null);
	expect(';');

	if(!parse_assign_stmt()) executor_->tree_push_back(null);
	expect(')');

	expect_parse_stmt();

	parse_else_or_nobreak();

	executor_->tree_splice(EXPR_FOR, 7);
}

void Parser::parse_while(){
	executor_->tree_push_back(null);
	expect('(');

	expect_parse_expr();
	expect(')');

	executor_->tree_push_back(null);
	
	expect_parse_stmt();
	
	parse_else_or_nobreak();

	executor_->tree_splice(EXPR_FOR, 7);
}

bool Parser::parse_loop(){
	// label: while(true){ // というパターンかをチェック
	if(parse_var()){
		const Token& ch = read_token(); // :の次を読み取る
		if(ch.type()==Token::TYPE_KEYWORD){
			switch(ch.keyword_number()){
				XTAL_DEFAULT{}
				XTAL_CASE(Token::KEYWORD_FOR){ parse_for(); return true; }
				XTAL_CASE(Token::KEYWORD_WHILE){ parse_while(); return true; }
			}
		}

		putback_token(ch);
		if(parse_expr()){
			if(!expr_end() && eat('{')){
				parse_each();
				return true;
			}
			else{
				// 変数定義文だった
				AnyPtr temp = executor_->tree_pop_back();
				executor_->tree_splice(EXPR_LVAR, 1);
				executor_->tree_push_back(temp);
				executor_->tree_splice(EXPR_DEFINE, 2);
				return true;
			}
		}

		putback_token();
		putback_token();
	}

	return false;
}

bool Parser::parse_assign_stmt(){
	{
		const Token& ch = read_token();

		switch(ch.type()){
			XTAL_DEFAULT;

			XTAL_CASE(Token::TYPE_TOKEN){
				switch(ch.ivalue()){
					XTAL_DEFAULT{}
					XTAL_CASE(c2('+','+')){ expect_parse_expr(); executor_->tree_splice(EXPR_INC, 1); return true; }
					XTAL_CASE(c2('-','-')){ expect_parse_expr(); executor_->tree_splice(EXPR_DEC, 1); return true; }
				}
			}

			XTAL_CASE(Token::TYPE_KEYWORD){
				switch(ch.keyword_number()){
					XTAL_DEFAULT{}
					XTAL_CASE(Token::KEYWORD_METHOD){
						expect_parse_expr(PRI_CALL, 0);
						parse_fun(KIND_METHOD);
						executor_->tree_splice(EXPR_DEFINE, 2);
						return true;
					}

					XTAL_CASE(Token::KEYWORD_FUN){
						expect_parse_expr(PRI_CALL, 0);
						parse_fun(KIND_FUN);
						executor_->tree_splice(EXPR_DEFINE, 2);
						return true;
					}

					XTAL_CASE(Token::KEYWORD_FIBER){
						expect_parse_expr(PRI_CALL, 0);
						parse_fun(KIND_FIBER);
						executor_->tree_splice(EXPR_DEFINE, 2);
						return true;
					}

					XTAL_CASE(Token::KEYWORD_CLASS){
						expect_parse_expr(PRI_CALL, 0);
						parse_class(KIND_CLASS);
						executor_->tree_splice(EXPR_DEFINE, 2);
						return true;
					}

					XTAL_CASE(Token::KEYWORD_SINGLETON){
						expect_parse_expr(PRI_CALL, 0);
						parse_class(KIND_SINGLETON);
						executor_->tree_splice(EXPR_DEFINE, 2);
						return true;
					}
				}
			}
		}

		putback_token();
	}

	if(parse_expr()){
		if(expr_end()){
			return true;
		}
		
		const Token& ch = read_token();

		switch(ch.type()){
			XTAL_DEFAULT{}
			
			XTAL_CASE(Token::TYPE_TOKEN){
				switch(ch.ivalue()){

					XTAL_DEFAULT{
						putback_token();
						return true; 
					}

					XTAL_CASE(','){
						parse_exprs(true);
						
						if(eat('=')){
							parse_exprs();
							executor_->tree_splice(EXPR_MASSIGN, 2);
							return true;
						}
						else if(eat(':')){
							parse_exprs();
							executor_->tree_splice(EXPR_MDEFINE, 2);
							return true;
						}
						else{
							executor_->error(Xt("XCE1001"));
						}
						
						return true;
					}

					XTAL_CASE('='){ expect_parse_expr(); executor_->tree_splice(EXPR_ASSIGN, 2); return true; }
					XTAL_CASE(':'){ expect_parse_expr(); executor_->tree_splice(EXPR_DEFINE, 2); return true; }

					XTAL_CASE(c2('+','+')){ executor_->tree_splice(EXPR_INC, 1); return true; }
					XTAL_CASE(c2('-','-')){ executor_->tree_splice(EXPR_DEC, 1); return true; }
					
					XTAL_CASE(c2('+','=')){ expect_parse_expr(); executor_->tree_splice(EXPR_ADD_ASSIGN, 2); return true; }
					XTAL_CASE(c2('-','=')){ expect_parse_expr(); executor_->tree_splice(EXPR_SUB_ASSIGN, 2); return true; }
					XTAL_CASE(c2('~','=')){ expect_parse_expr(); executor_->tree_splice(EXPR_CAT_ASSIGN, 2); return true; }
					XTAL_CASE(c2('*','=')){ expect_parse_expr(); executor_->tree_splice(EXPR_MUL_ASSIGN, 2); return true; }
					XTAL_CASE(c2('/','=')){ expect_parse_expr(); executor_->tree_splice(EXPR_DIV_ASSIGN, 2); return true; }
					XTAL_CASE(c2('%','=')){ expect_parse_expr(); executor_->tree_splice(EXPR_MOD_ASSIGN, 2); return true; }
					XTAL_CASE(c2('^','=')){ expect_parse_expr(); executor_->tree_splice(EXPR_XOR_ASSIGN, 2); return true; }
					XTAL_CASE(c2('|','=')){ expect_parse_expr(); executor_->tree_splice(EXPR_OR_ASSIGN, 2); return true; }
					XTAL_CASE(c2('&','=')){ expect_parse_expr(); executor_->tree_splice(EXPR_AND_ASSIGN, 2); return true; }
					XTAL_CASE(c3('<','<','=')){ expect_parse_expr(); executor_->tree_splice(EXPR_SHL_ASSIGN, 2); return true; }
					XTAL_CASE(c3('>','>','=')){ expect_parse_expr(); executor_->tree_splice(EXPR_SHR_ASSIGN, 2); return true; }
					XTAL_CASE(c4('>','>','>','=')){ expect_parse_expr(); executor_->tree_splice(EXPR_USHR_ASSIGN, 2); return true; }

					XTAL_CASE('{'){
						executor_->tree_insert(1, null);
						parse_each();
						return true;
					}
				}
			}
		}

		putback_token();
		return true;
	}

	return false;
}

void Parser::expect_stmt_end(){
	if(!expr_end()){
		if(!executor_->eos()){
			expect(';');
		}
	}
}

bool Parser::parse_stmt(){
	if(parse_loop()){
		expect_stmt_end();
		return true;
	}

	const Token& ch = read_token();

	switch(ch.type()){
		XTAL_DEFAULT{}

		XTAL_CASE(Token::TYPE_KEYWORD){
			switch(ch.keyword_number()){
				XTAL_DEFAULT{}
		
				XTAL_CASE(Token::KEYWORD_WHILE){ executor_->tree_push_back(null); parse_while(); return true; }
				XTAL_CASE(Token::KEYWORD_FOR){ executor_->tree_push_back(null); parse_for(); return true; }
				XTAL_CASE(Token::KEYWORD_SWITCH){ parse_switch(); return true; }
				XTAL_CASE(Token::KEYWORD_IF){ parse_if(); return true; }
				XTAL_CASE(Token::KEYWORD_TRY){ parse_try(); return true; }

				XTAL_CASE(Token::KEYWORD_THROW){ 
					expect_parse_expr(); 
					executor_->tree_splice(EXPR_THROW, 1);
					expect_stmt_end(); 
					return true; 
				}	

				XTAL_CASE(Token::KEYWORD_ASSERT){ 
					parse_assert(); 
					expect_stmt_end(); 
					return true; 
				}

				XTAL_CASE(Token::KEYWORD_RETURN){ 
					parse_exprs(); 
					executor_->tree_splice(EXPR_RETURN, 1); 
					expect_stmt_end(); 
					return true; 
				}
				
				XTAL_CASE(Token::KEYWORD_CONTINUE){ 
					if(!parse_identifier()){
						executor_->tree_push_back(null); 
					}
					executor_->tree_splice(EXPR_CONTINUE, 1); 
					expect_stmt_end();
					return true; 
				}

				XTAL_CASE(Token::KEYWORD_BREAK){ 
					if(!parse_identifier()){
						executor_->tree_push_back(null); 
					}
					executor_->tree_splice(EXPR_BREAK, 1); 
					expect_stmt_end();
					return true; 
				}

			}
		}
		
		XTAL_CASE(Token::TYPE_TOKEN){
			switch(ch.ivalue()){
				XTAL_DEFAULT{}
				XTAL_CASE('{'){ parse_scope(); return true; }
				XTAL_CASE(';'){ executor_->tree_splice(EXPR_NULL, 0); return true; }
			}
		}
	}
	
	putback_token();
	if(parse_assign_stmt()){
		expect_stmt_end();
		return true;
	}

	return false;
}

void Parser::expect_parse_stmt(){
	if(!parse_stmt()){
		executor_->error(Xt("XCE1001"));
		executor_->tree_push_back(null);
	}
}

void Parser::parse_assert(){
	executor_->begin_record();
	if(parse_expr()){
		StringPtr ref_str = executor_->end_record();
		executor_->tree_push_back(KIND_STRING);
		executor_->tree_push_back(ref_str);
		executor_->tree_splice(EXPR_STRING, 2);
		if(!eat(',') || !parse_expr()){
			executor_->tree_push_back(null);
		}
	}
	else{
		executor_->tree_push_back(null);
		executor_->tree_push_back(null);
		executor_->tree_push_back(null);
		executor_->end_record();
	}

	executor_->tree_splice(EXPR_ASSERT, 3);
}
	
void Parser::parse_exprs(bool one){
	xpeg::Executor::TreeNodeState state = executor_->tree_node_begin();
	if(one){
		state.pos--;
	}

	for(;;){
		if(!parse_expr() || !eat(',')){
			break;
		}
	}
	executor_->tree_node_end(0, state);
}

void Parser::parse_stmts(){
	xpeg::Executor::TreeNodeState state = executor_->tree_node_begin();
	while(parse_stmt()){}
	executor_->tree_node_end(0, state);
}

void Parser::expect_parse_identifier(){
	if(!parse_identifier()){
		executor_->error(Xt("XCE1001"));
		executor_->tree_push_back(null);
	}
}

bool Parser::parse_identifier(){
	if(peek_token().type()==Token::TYPE_IDENTIFIER){
		executor_->tree_push_back(identifier(read_token().identifier_number()));
		return true;
	}
	return false;
}

void Parser::parse_identifier_or_keyword(){
	if(peek_token().type()==Token::TYPE_IDENTIFIER){
		executor_->tree_push_back(identifier(read_token().identifier_number()));
	}
	else if(peek_token().type()==Token::TYPE_KEYWORD){
		executor_->tree_push_back(identifier(read_token().identifier_number()));
	}
	else{
		expect('i');
	}
}

bool Parser::parse_var(){
	if(parse_identifier()){
		if(eat(':')){ 
			return true; 
		}
		else{
			executor_->tree_pop_back();
			putback_token();
		}
	}
	return false;
}
	
void Parser::parse_toplevel(){
	xpeg::Executor::TreeNodeState state = executor_->tree_node_begin();
	parse_stmts();
	executor_->tree_node_end(EXPR_TOPLEVEL, state);
}

void Parser::parse_scope(){
	xpeg::Executor::TreeNodeState state = executor_->tree_node_begin();
	parse_stmts();
	executor_->tree_node_end(EXPR_SCOPE, state);
	expect('}');
}

void Parser::parse_secondary_key(){
	if(eat('#')){ 
		expect_parse_expr(PRI_NS, 0); 
	}
	else{ 
		executor_->tree_push_back(null); 
	}
}

void Parser::parse_fun2(int_t kind){
	expect_parse_identifier();
	parse_secondary_key();
	parse_fun(kind);
	executor_->tree_splice(EXPR_CDEFINE_MEMBER, 4);
	expect_stmt_end();
}

void Parser::parse_class2(int_t kind){
	expect_parse_identifier();
	parse_secondary_key();
	parse_class(kind);
	executor_->tree_splice(EXPR_CDEFINE_MEMBER, 4);
	expect_stmt_end();
}

void Parser::parse_class(int_t kind){
	executor_->tree_push_back(kind);

	if(eat('(')){
		parse_exprs();
		expect(')');
	}
	else{
		executor_->tree_push_back(null);
	}

	xpeg::Executor::TreeNodeState state = executor_->tree_node_begin();

	expect('{');
	for(;;){
		
		if(eat('#') || eat(Token::KEYWORD_PROTECTED)){// 可触性 protected 指定
			executor_->tree_push_back(KIND_PROTECTED);
		}
		else if(eat('-') || eat(Token::KEYWORD_PRIVATE)){// 可触性 private 指定
			executor_->tree_push_back(KIND_PRIVATE);
		}
		else if(eat('+') || eat(Token::KEYWORD_PUBLIC)){// 可触性 public 指定
			executor_->tree_push_back(KIND_PUBLIC);
		}
		else{
			executor_->tree_push_back(null);
		}

		if(eat(Token::KEYWORD_METHOD)){
			parse_fun2(KIND_METHOD);
		}
		else if(eat(Token::KEYWORD_FUN)){
			parse_fun2(KIND_FUN);
		}
		else if(eat(Token::KEYWORD_FIBER)){
			parse_fun2(KIND_FIBER);
		}
		else if(eat(Token::KEYWORD_CLASS)){
			parse_class2(KIND_CLASS);
		}
		else if(eat(Token::KEYWORD_SINGLETON)){
			parse_class2(KIND_SINGLETON);
		}
		else if(parse_identifier()){ // メンバ定義
			parse_secondary_key();

			if(eat(':')){
				expect_parse_expr();
			}
			else{
				parse_fun(KIND_METHOD);
			}

			executor_->tree_splice(EXPR_CDEFINE_MEMBER, 4);
			expect_stmt_end();
		}
		else if(eat('_')){// インスタンス変数定義
			if(parse_identifier()){
				if(eat(':')){ // 初期値込み
					expect_parse_expr();
				}
				else{
					executor_->tree_push_back(null);
				}
				executor_->tree_splice(EXPR_CDEFINE_IVAR, 3);
				expect_stmt_end();
			}
			else{
				executor_->tree_pop_back();
				executor_->error(Xt("XCE1001"));
			}
		}
		else{
			executor_->tree_pop_back();
			break;
		}
	}

	executor_->tree_node_end(0, state);
	executor_->tree_splice(EXPR_CLASS, 3);

	expect('}');
}

void Parser::parse_try(){	
	expect_parse_stmt();
	
	if(eat(Token::KEYWORD_CATCH)){
		expect('(');
		expect_parse_identifier();
		expect(')');
		expect_parse_stmt();
	}
	else{
		executor_->tree_push_back(null);
		executor_->tree_push_back(null);
	}

	if(eat(Token::KEYWORD_FINALLY)){
		expect_parse_stmt();
	}
	else{
		executor_->tree_push_back(null);
	}

	executor_->tree_splice(EXPR_TRY, 4);
}

void Parser::parse_lambda(bool noparam){
	executor_->tree_push_back(KIND_LAMBDA);

	if(noparam){
		executor_->tree_push_back(null);
	}
	else{
		xpeg::Executor::TreeNodeState state = executor_->tree_node_begin();
		for(;;){
			if(parse_identifier()){
				executor_->tree_splice(EXPR_LVAR, 1);
				executor_->tree_push_back(null);
				executor_->tree_splice(0, 2);
			}
			else{
				break;
			}

			if(!eat(',')){
				break;
			}
		}
		eat(',');
		expect('|');
		executor_->tree_node_end(0, state);
	}

	executor_->tree_push_back(null);

	if(eat('{')){
		parse_scope();
	}
	else{
		parse_exprs();
		executor_->tree_splice(EXPR_RETURN, 1);
	}

	executor_->tree_splice(EXPR_FUN, 4);
}

void Parser::parse_fun(int_t kind){
	executor_->tree_push_back(kind);
	
	if(eat('(')){

		xpeg::Executor::TreeNodeState state = executor_->tree_node_begin();
		for(;;){
			if(eat(c3('.','.','.'))){ // extendable
				putback_token();
				break;
			}
			else{
				if(parse_expr()){
					if(eat(':')){
						expect_parse_expr();
					}
					else{
						executor_->tree_push_back(null);
					}
					executor_->tree_splice(0, 2);
				}
				else{
					break;
				}
			}

			if(!eat(',')){
				break;
			}
		}
		executor_->tree_node_end(0, state);

		if(eat(c3('.','.','.'))){ // extendable
			expect_parse_identifier();
		}
		else{
			executor_->tree_push_back(null);
		}

		eat(',');
		expect(')');
	}
	else{
		executor_->tree_push_back(null);
		executor_->tree_push_back(null);
	}

	if(eat('{')){
		parse_scope();
	}
	else{
		parse_exprs();
		executor_->tree_splice(EXPR_RETURN, 1);
	}

	executor_->tree_splice(EXPR_FUN, 4);
}

void Parser::parse_call(){
	// 順番引数のループ
	xpeg::Executor::TreeNodeState state = executor_->tree_node_begin();
	for(;;){
		if(eat(c3('.','.','.'))){ // extendable
			putback_token();
			break;
		}
		else{
			if(parse_expr()){
				if(eat(':')){
					expect_parse_expr();
				}
				else{
					executor_->tree_insert(1, null);
				}
				executor_->tree_splice(0, 2);
			}
			else{
				break;
			}
		}

		if(!eat(',')){
			break;
		}
	}
	executor_->tree_node_end(0, state);

	if(eat(c3('.','.','.'))){ // extendable
		expect_parse_expr();
	}
	else{
		executor_->tree_push_back(null);
	}

	eat(',');
	expect(')');

	executor_->tree_splice(EXPR_CALL, 3);
}

bool Parser::parse_expr(int_t pri, int_t space){
	if(!parse_term()){
		return false;
	}
	
	while(parse_post(pri, space)){}
	return true;
}

bool Parser::parse_expr(){
	return parse_expr(0, 0);
}

void Parser::expect_parse_expr(int_t pri, int_t space){
	if(!parse_expr(pri, space)){
		executor_->error(Xt("XCE1001"));
		executor_->tree_push_back(null);
	}
}

void Parser::expect_parse_expr(){
	expect_parse_expr(0, 0);

}

void Parser::parse_if(){
	expect('(');

	if(parse_var()){
		executor_->tree_splice(EXPR_LVAR, 1);
		expect_parse_expr();
		executor_->tree_splice(EXPR_DEFINE, 2);
	}
	else{
		expect_parse_expr();
	}

	expect(')');
	expect_parse_stmt();
	if(eat(Token::KEYWORD_ELSE)){
		expect_parse_stmt();
	}
	else{
		executor_->tree_push_back(null);
	}
	executor_->tree_splice(EXPR_IF, 3);
}

void Parser::parse_switch(){
	expect('(');

	if(parse_var()){
		executor_->tree_splice(EXPR_LVAR, 1);
		expect_parse_expr();
		executor_->tree_splice(EXPR_DEFINE, 2);
	}
	else{
		expect_parse_expr();
	}
	
	expect(')');
	expect('{');
	
	ExprPtr cases = xnew<Expr>(EXPR_LIST);
	ExprPtr default_case;
	for(;;){
		if(eat(Token::KEYWORD_CASE)){
			expect('(');
			parse_exprs();
			expect(')');
			expect_parse_stmt();
			executor_->tree_splice(EXPR_LIST, 2);
			cases->push_back(executor_->tree_pop_back());
		}
		else if(eat(Token::KEYWORD_DEFAULT)){
			expect_parse_stmt();
			default_case = ep(executor_->tree_pop_back());
		}
		else{
			expect('}');
			break;
		}
	}

	executor_->tree_push_back(cases);
	executor_->tree_push_back(default_case);
	executor_->tree_splice(EXPR_SWITCH, 3);
}

void Parser::parse_array(){	
	if(eat(']')){//empty array
		executor_->tree_splice(EXPR_ARRAY, 0);
		return;
	}
	
	if(eat(':')){//empty map
		expect(']');
		executor_->tree_splice(EXPR_MAP, 0);
		return;
	}
	
	xpeg::Executor::TreeNodeState state = executor_->tree_node_begin();
	expect_parse_expr();
	if(eat(':')){//map
		expect_parse_expr();
		executor_->tree_splice(0, 2);

		if(eat(',')){
			for(;;){
				if(parse_expr()){
					expect(':');
					expect_parse_expr();
					executor_->tree_splice(0, 2);
					
					if(!eat(',')){
						break;
					}
				}
				else{
					break;
				}
			}
		}

		expect(']');
		executor_->tree_node_end(0, state);
		executor_->tree_splice(EXPR_MAP, 1);
	}
	else{//array
		if(eat(',')){
			for(;;){
				if(parse_expr()){
					if(!eat(',')){
						break;
					}
				}
				else{
					break;
				}
			}
		}

		expect(']');
		executor_->tree_node_end(0, state);
		executor_->tree_splice(EXPR_ARRAY, 1);
	}
}

}

#endif

