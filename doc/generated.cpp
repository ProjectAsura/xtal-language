namespace lib{namespace builtin{
/**
* \xbind lib::builtin
* \brief すべてのクラスの基底クラス
*/
class Any{
public:
	/**
	* \xbind
	* \brief このオブジェクトが所属するクラスを返す。
	*/
	 Class get_class();

	/**
	* \xbind
	* \brief オブジェクトの名前を返す
	*/
	String object_name();

	/**
	* \xbind
	* \brief オブジェクトの名前のリストを返す
	* 一番最上位の親からの名前のリストを返す
	*/
	Array object_name_list();

	/**
	* \xbind
	* \brief 自身を文字列化してprintlnする。
	* \return 自身を返す。
	*/
	Any p();

};
}}
namespace lib{namespace builtin{
/**
* \xbind lib::builtin
* \xinherit lib::builtin::Any lib::builtin::Iterable
* \brief 配列
*/
class Array: public lib::builtin::Any, public lib::builtin::Iterable{
public:
	/**
	* \xbind
	* \brief sizeの長さの配列を生成する 
	*/
	 Array(uint size = 0);

	/**
	* \xbind
	* \brief 配列の長さを返す
	*/
	uint length();

	/**
	* \xbind
	* \brief 配列の長さを返す
	*/
	uint size();

	/**
	* \xbind
	* \brief 配列の長さを変更する
	*/
	void resize(uint sz);

	/**
	* \xbind
	* \brief 配列をsz分長くする
	*/
	void upsize(uint sz);

	/**
	* \xbind
	* \brief 配列をsz分短くする
	*/
	void downsize(uint sz);

	/**
	* \xbind
	* \brief i番目の要素を返す
	*/
	 Any op_at(int i);

	/**
	* \xbind
	* \brief i番目の要素を設定する
	*/
	void op_set_at(int i,  Any v);

	/**
	* \xbind
	* \brief 先頭に要素を追加する
	*/
	void push_front( Any v);

	/**
	* \xbind
	* \brief 先頭の要素を削除する
	*/
	void pop_front();

	/**
	* \xbind
	* \brief 末尾に要素を追加する
	*/
	void push_back( Any v);

	/**
	* \xbind
	* \brief 末尾の要素を削除する
	*/
	void pop_back();

	/**
	* \xbind
	* \brief 先頭の要素を返す
	*/
	 Any front();

	/**
	* \xbind
	* \brief 末尾の要素を返す
	*/
	 Any back();

	/**
	* \xbind
	* \brief i番目からn個の部分配列を返す
	*/
	Array slice(int i, int n = 1);

	/**
	* \xbind
	* \brief indexからn個の部分配列を削除し、その部分配列を返す
	*/
	Array splice(int i, int n = 1);

	/**
	* \xbind
	* \brief i番目のn個の要素を削除する
	*/
	void erase(int i, int n = 1);

	/**
	* \xbind
	* \brief i番目に要素を追加する
	*/
	void insert(int i,  Any v);

	/**
	* \xbind
	* \brief 配列の要素を逆順にするイテレータを返す
	*/
	Any reverse();

	/**
	* \xbind
	* \brief 浅いコピーを返す
	*/
	Array clone();

	/**
	* \xbind
	* \brief 要素を文字列として連結した結果を返す
	* \param sep 要素と要素の区切り文字列
	*/
	String join( String sep);

	/**
	* \xbind
	* \brief 自身を返す
	*/
	Array op_to_array();

	/**
	* \xbind
	* \brief 空か調べる
	*/
	bool empty();

	/**
	* \xbind
	* \brief 空か調べる
	*/
	bool is_empty();

	/**
	* \xbind
	* \brief 要素を全て削除する
	*/
	void clear();

	/**
	* \xbind
	* \brief 要素を最初から反復できるIteratorを返す
	*/
	Any each();

	/**
	* \xbind
	* \brief 中身をiteratorで取得できる要素に置き換える
	*/
	void assign( Any iterator);

	/**
	* \xbind
	* \brief iteratorで取得できる要素を追加する
	*/
	void append( Any iterator);

};
}}
namespace lib{namespace builtin{
/**
* \xbind lib::builtin
* \xinherit lib::builtin::Frame
* \brief クラス
*/
class Class: public lib::builtin::Frame{
public:
	/**
	* \xbind
	* \brief 継承
	* \param cls 継承するクラスオブジェクト
	*/
	void inherit( Class cls);

	/**
	* \xbind
	* \brief 継承されているクラスを列挙するIteratorを返す
	*/
	Any inherited_classes();

	/**
	* \xbind
	* \brief 祖先クラスを列挙するIteratorを返す
	*/
	Any ancestors();

};
}}

/**
* \xbind
* \brief デバッグ機能を有効にする
* デバッグ機能はデフォルトでは無効になっている。
*/
	void enable();



/**
* \xbind
* \brief デバッグ機能を無効にする
*/
	void disable();



/**
* \xbind
* \brief デバッグ機能を強制的に有効にする
* デバッグ機能はデフォルトでは無効になっている。
*/
	void enable_force(int count);



/**
* \xbind
* \brief デバッグ機能を強制的に無効にする
*/
	int disable_force();



/**
* \xbind
* \brief デバッグ機能が有効かどうか
*/
	bool is_enabled();



/**
* \xbind
* \brief ブレークポイントがある度に呼び出されるフック関数を登録する
* \param hook 登録するフック関数
*/
	void set_break_point_hook( Any hook);



/**
* \xbind
* \brief 関数呼び出しされる度に呼び出されるフック関数を登録する
* \param hook 登録するフック関数
*/
	void set_call_hook( Any hook);



/**
* \xbind
* \brief 関数からreturnされる度に呼び出されるフック関数を登録する
* \param hook 登録するフック関数
*/
	void set_return_hook( Any hook);



/**
* \xbind
* \brief 例外かthrowされる度に呼び出されるフック関数を登録する
* \param hook 登録するフック関数
*/
	void set_throw_hook( Any hook);



/**
* \xbind
* \brief アサートが失敗される度に呼び出されるフック関数を登録する
* \param hook 登録するフック関数
*/
	void set_assert_hook( Any hook);



/**
* \xbind
* \brief set_break_point_hook関数で登録した関数を取得する
*/
	 Any break_point_hook();



/**
* \xbind
* \brief set_call_hook関数で登録した関数を取得する
*/
	 Any call_hook();



/**
* \xbind
* \brief set_return_hook関数で登録した関数を取得する
*/
	 Any return_hook();



/**
* \xbind
* \brief set_throw_hook関数で登録した関数を取得する
*/
	 Any throw_hook();



/**
* \xbind
* \brief set_assert_hook関数で登録した関数を取得する
*/
	 Any assert_hook();


namespace lib{namespace builtin{
/**
* \xbind lib::builtin
* \brief ガーベジコレクションを実行する
*
* さほど時間はかからないが、完全にゴミを解放できないガーベジコレクト関数
* 例えば循環参照はこれでは検知できない。
*/
	void gc();

}}
namespace lib{namespace builtin{
/**
* \xbind lib::builtin
* \brief 循環オブジェクトも解放するフルガーベジコレクションを実行する
*
* 時間はかかるが、現在ゴミとなっているものはなるべく全て解放するガーベジコレクト関数
* 循環参照も検知できる。
*/
	void full_gc();

}}
namespace lib{namespace builtin{
/**
* \xbind lib::builtin
* \brief ガーベジコレクションを無効化する
*
* gcやfull_gcの呼び出しを無効化する関数。
* 内部でこれが何回呼び出されたか記憶されており、呼び出した回数enable_gcを呼びないとガーベジコレクションは有効にならない
*/
	void disable_gc();

}}
namespace lib{namespace builtin{
/**
* \xbind lib::builtin
* \brief ガーベジコレクションを有効化する

* disable_gcが呼ばれた回数と同じだけ呼び出すとガーベジコレクションが有効になる
*/
	void enable_gc();

}}
namespace lib{namespace builtin{
/**
* \xbind lib::builtin
* \brief 例外
*/
class Exception{
public:
};
}}
namespace lib{namespace builtin{namespace filesystem{
/**
* \xbind lib::builtin::filesystem
* \brief ファイルオープン
*/
	Stream open( String file_name,  String flags);

}}}
namespace lib{namespace builtin{namespace filesystem{
/**
* \xbind lib::builtin::filesystem
* \brief ディレクトリかどうか
*/
	bool is_directory( String path);

}}}
namespace lib{namespace builtin{namespace filesystem{
/**
* \xbind lib::builtin::filesystem
* \brief path以下のエントリを列挙するIteratorを返す
*/
	Any entries( String path);

}}}
namespace lib{namespace builtin{
/**
* \xbind lib::builtin
* \xinherit lib::builtin::Any
* \brief フレーム
*/
class Frame: public lib::builtin::Any{
public:
	/**
	* \xbind
	* \brief 外側のスコープを表すFrameオブジェクトを返す。
	*/
	 Frame outer();

};
}}
namespace lib{namespace builtin{
/**
* \xbind lib::builtin
* \brief イテレータの便利メソッドを提供するためのクラス
*/
class Iterator{
public:
	/**
	* \xbind
	* \brief 要素をn個デバッグプリントする
	* 代わりのイテレータを返す。
	*/
	Any ip(int n = 3);

	/**
	* \xbind
	* \brief 要素を纏めて配列にして返す
	*/
	Array op_to_array();

	/**
	* \xbind
	* \brief 要素を纏めて連想配列にして返す
	* 二つ以上の値を列挙するイテレータである必要がある
	*/
	Map op_to_map();

	/**
	* \xbind
	* \brief 要素を文字列化し、さらにそれらをsepで連結した文字列を返す
	*/
	String join( String sep = "");

	/**
	* \xbind
	* \brief (index, value)を返すイテレータを返す
	* ループごとにindexはインクリメントされる。
	*/
	Any with_index(int start = 0);

	/**
	* \xbind
	* \brief 要素をconv関数で変換した要素を返すイテレータを返す
	*/
	Any collect( Any conv);

	/**
	* \xbind
	* \brief 要素をconv関数で変換した要素を返すイテレータを返す
	*/
	Any map( Any conv);

	/**
	* \xbind
	* \brief 選別された要素を返すイテレータを返す
	*/
	Any select( Any pred);

	/**
	* \xbind
	* \brief 選別された要素を返すイテレータを返す
	*/
	Any filter( Any pred);

	/**
	* \xbind
	* \brief pred関数がtrueを返すまでイテレートするイテレータを返す
	*/
	Any break_if( Any pred);

	/**
	* \xbind
	* \brief times回イテレートするイテレータを返す
	*/
	Any take(int times);

	/**
	* \xbind
	* \brief 並列にイテレートするイテレータを返す
	*/
	Any zip(...);

	/**
	* \xbind
	* \brief 直列にイテレートするイテレータを返す
	*/
	Any chain(...);

	/**
	* \xbind
	* \brief イテレートする要素がなくなったら、最初から繰り返すイテレータを返す
	*/
	Any cycle();

	/**
	* \xbind
	* \brief イテレートする要素の最大の値を返す
	*/
	Any max_element( Any pred = null);

	/**
	* \xbind
	* \brief イテレートする要素の最小の値を返す
	*/
	Any min_element( Any pred = null);

	/**
	* \xbind
	* \brief イテレートする要素のpred関数がtrueを返す関数を返す
	*/
	Any find( Any pred);

	/**
	* \xbind
	* \brief inject
	*/
	Any inject( Any init,  Any fn);

	/**
	* \xbind
	* \brief (前回の要素, 今回の要素)を要素をするイテレータを返す
	* 最初の一回の前回の要素にはundefinedが入る
	*/
	Any with_prev();

};
}}
namespace lib{namespace builtin{
/**
* \xbind lib::builtin
* \brief イテレート可能なコンテナのための実装を提供するためのクラス
* これをinheritしたクラスのオブジェクトは、eachメソッドを経由してlib::builtin::Iteratorが持つメソッドを呼び出せる
*/
class Iterable{
public:
};
}}
namespace lib{namespace builtin{
/**
* \xbind lib::builtin
* \xinherit lib::builtin::Any lib::builtin::Iterable
* \brief 連想配列
*/
class Map: public lib::builtin::Any, public lib::builtin::Iterable{
public:
	/**
	* \xbind
	* \brief 空の連想配列オブジェクトを生成
	*/
	 Map();

	/**
	* \xbind
	* \brief keyに対応する要素を返す
	* \param key 検索のためのキー 
	*/
	 Any op_at( Any key);

	/**
	* \xbind
	* \brief keyに対応する要素を設定する
	* \param key 検索のためのキー 
	* \param value keyに対応する値
	*/
	void op_set_at( Any key,  Any value);

	/**
	* \xbind
	* \brief keyに対応する要素を設定する
	* \param key 検索のためのキー 
	* \param value keyに対応する値
	*/
	void insert( Any key,  Any value);

	/**
	* \xbind
	* \brief keyに対応する値を削除する
	* \param key 検索のためのキー 
	*/
	void erase( Any key);

	/**
	* \xbind
	* \brief 連想配列に登録された要素の数を返す
	* \return 連想配列に登録された要素の数
	*/
	uint size();

	/**
	* \xbind
	* \brief 連想配列に登録された要素の数を返す
	* \return 連想配列に登録された要素の数
	*/
	uint length();

	/**
	* \xbind
	* \brief 空か調べる
	* \retval true 空
	* \retval false 非空
	*/
	bool empty();

	/**
	* \xbind
	* \brief 空か調べる
	* \retval true 空
	* \retval false 非空
	*/
	bool is_empty();

	/**
	* \xbind
	* \brief 連結した連想配列を返す
	*/
	Map op_cat( Map a);

	/**
	* \xbind
	* \brief 自身と連結し、自身を返す
	*/
	Map op_cat_assign( Map a);

	/**
	* \xbind
	* \brief (key, value)を要素とする、Iteratorを返す
	*/
	Any pairs();

	/**
	* \xbind
	* \brief keyを要素とする、Iteratorを返す
	*/
	Any keys();

	/**
	* \xbind
	* \brief valueを要素とする、Iteratorを返す
	*/
	Any values();

	/**
	* \xbind
	* \brief (key, value)を要素とする、Iteratorを返す
	* pairsと同じ
	*/
	Any each();

	/**
	* \xbind
	* \brief 浅いコピーを返す
	*/
	Map clone();

	/**
	* \xbind
	* \brief 要素を全て削除する
	*/
	void clear();

	/**
	* \xbind
	* \brief 自身を返す
	*/
	Map op_to_map();

	/**
	* \xbind
	* \brief 中身をiteratorで取得できる要素に置き換える
	*/
	void assign( Any iterator);

	/**
	* \xbind
	* \brief iteratorで取得できる要素を追加する
	*/
	void append( Any iterator);

	/**
	* \xbind
	* \brief デフォルト値として設定されているオブジェクトを取り出す
	* \return デフォルト値
	*/
	 Any default_value();

	/**
	* \xbind
	* \brief デフォルト値を設定する
	* \param default_value デフォルト値
	*/
	void set_default_value( Any default_value);

};
}}
namespace lib{namespace builtin{
/**
* \xbind lib::builtin
* \brief ストリーム
*/
class Stream{
public:
	/**
	* \xbind
	* \brief 文字列strをストリームに流す
	*/
	void put_s( String str);

	/**
	* \xbind
	* \brief length文字分ストリームから取り出し、文字列として返す。
	*/
	 String get_s(uint length);

	/**
	* \xbind
	* \brief オブジェクトを直列化してストリームに書き込む
	*
	* \param obj 直列化して保存したいオブジェクト
	*/
	void serialize( Any obj);

	/**
	* \xbind
	* \brief 直列化されたオブジェクトをストリームから読み出す
	*
	* \return 復元されたオブジェクト
	*/
	Any deserialize();

	/**
	* \xbind
	* \brief 符号付整数8-bitをストリームに書き込む
	*/
	void put_i8(i8 v);

	/**
	* \xbind
	* \brief 符号付整数16-bitをストリームに書き込む
	*/
	void put_i16be(i16 v);

	/**
	* \xbind
	* \brief 符号付整数16-bitをストリームに書き込む
	*/
	void put_i16le(i16 v);

	/**
	* \xbind
	* \brief 符号付整数32-bitをストリームに書き込む
	*/
	void put_i32be(i32 v);

	/**
	* \xbind
	* \brief 符号付整数32-bitをストリームに書き込む
	*/
	void put_i32le(i32 v);

	/**
	* \xbind
	* \brief 符号付整数64-bitをストリームに書き込む
	*/
	void put_i64be(i64 v);

	/**
	* \xbind
	* \brief 符号無整数8-bitをストリームに書き込む
	*/
	void put_u8(u8 v);

	/**
	* \xbind
	* \brief 符号無整数16-bitをストリームに書き込む
	*/
	void put_u16be(u16 v);

	/**
	* \xbind
	* \brief 符号無整数16-bitをストリームに書き込む
	*/
	void put_u16le(u16 v);

	/**
	* \xbind
	* \brief 符号無整数32-bitをストリームに書き込む
	*/
	void put_u32be(u32 v);

	/**
	* \xbind
	* \brief 符号無整数32-bitをストリームに書き込む
	*/
	void put_u32le(u32 v);

};
}}
namespace lib{namespace builtin{
/**
* \xbind lib::builtin
* \brief メモリーストリーム
*/
class MemoryStream{
public:
};
}}
namespace lib{namespace builtin{
/**
* \xbind lib::builtin
* \brief 文字列ストリーム
* 文字列を読み取るためのストリーム。書き込み不可。
*/
class StringStream{
public:
};
}}
namespace lib{namespace builtin{
/**
* \xbind lib::builtin
* \brief ファイルストリーム
*/
class FileStream{
public:
};
}}
namespace lib{namespace builtin{
/**
* \xbind lib::builtin
* \xinherit lib::builtin::Any lib::builtin::Iterable
* \brief 文字列のクラス
*/
class String: public lib::builtin::Any, public lib::builtin::Iterable{
public:
	/**
	* \xbind
	* \brief 空文字列を構築する
	*/
	 String();

	/**
	* \xbind
	* \brief データサイズを返す。
	* マルチバイト文字を考慮しない。
	*/
	uint data_size();

	/**
	* \xbind
	* \brief 文字列の長さを返す。
	* マルチバイト文字を考慮する。
	*/
	uint length();

	/**
	* \xbind
	* \brief 一意化した文字列を返す。
	*/
	 ID intern();

	/**
	* \xbind
	* \brief 一意化されているか返す。
	*/
	bool is_interned();

	/**
	* \xbind
	* \brief 整数に変換した結果を返す。
	*/
	int to_i();

	/**
	* \xbind
	* \brief 浮動小数点数に変換した結果を返す。
	*/
	float to_f();

	/**
	* \xbind
	* \brief 自分自身を返す。
	*/
	String to_s();

	/**
	* \xbind
	* \brief 一文字づつの文字列を要素とするIteratorを返す。
	* \return 一文字づつの文字列を要素とするIterator
	*/
	Any each();

	/**
	* \xbind
	* \brief 連結する
	* \return 連結された新しいオブジェクト
	*/
	String cat( String v);

	/**
	* \xbind
	* \brief 一文字の文字列かどうか
	*/
	bool is_ch();

	/**
	* \xbind
	* \brief 一文字の文字列の場合、そのasciiコードを返す
	*/
	int ascii();

	/**
	* \xbind
	* \brief 文字の範囲オブジェクトの範囲内かどうか
	*/
	bool op_in( ChRange range);

	/**
	* \xbind
	* \brief 範囲オブジェクトを生成する
	*/
	ChRange op_range( String right, int kind);

	/**
	* \xbind
	* \brief 連結する
	*/
	String op_cat( String v);

	/**
	* \xbind
	* \brief 値が等しいか比べる
	*/
	bool op_eq( String v);

	/**
	* \xbind
	* \brief より小さいか比べる
	*/
	bool op_lt( String v);

	/**
	* \xbind
	* \brief 文字列をスキャンする
	*/
	Any scan( Any pattern);

	/**
	* \xbind
	* \brief 文字列を分割し、その部分文字列を要素とするIteratorを返す
	*/
	Any split( Any pattern);

	/**
	* \xbind
	* \brief 文字列を分割し、その部分文字列を要素とするIteratorを返す
	*/
	bool match( Any pattern);

	/**
	* \xbind
	* \brief マッチする部分を置き換えた新しい文字列を返す
	*/
	String gsub( Any pattern,  Any fn);

	/**
	* \xbind
	* \brief 最初にマッチする部分を置き換えた新しい文字列を返す
	*/
	String sub( Any pattern,  Any fn);

};
}}
