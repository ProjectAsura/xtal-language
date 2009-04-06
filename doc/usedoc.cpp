
/** \page usepage C++�g�ݍ���
- \subpage useinitialize
- \subpage useexcept
- \subpage usehelloworld
- \subpage usestring
- \subpage useanyptr
- \subpage usefun
- \subpage usefuncall
- \subpage usesend
- \subpage usenew
- \subpage userefmember
- \subpage usedefmember
- \subpage useat
- \subpage usereturn
- \subpage useimport
- \subpage usecppclass
- \subpage usebytecode
*/

/** \page useinitialize Xtal�̏�����
��Ƃ��āAWindows�ł̏��������@��������܂��B\n
\code
#include <xtal.h>
#include <xtal_macro.h> // Xid�ȂǕ֗��ȃ}�N������`����Ă���

#include <xtal_lib/xtal_cstdiostream.h> // CStdioStdStreamLib�̂���
#include <xtal_lib/xtal_winthread.h> // WinThreadLib�̂���
#include <xtal_lib/xtal_winfilesystem.h> // WinFilesystemLib�̂���
#include <xtal_lib/xtal_chcode.h> // SJISChCodeLib�̂���
#include <xtal_lib/xtal_errormessage.h> // bind_error_message()�̂���

int main(int argc, char** argv){
	using namespace xtal;

	CStdioStdStreamLib cstd_std_stream_lib; // stdin, stdout, stderr��C�̕W�����C�u�������g��
	WinThreadLib win_thread_lib; // Windows�̃X���b�h���g��
	WinFilesystemLib win_filesystem_lib; // Windows�̃t�@�C���V�X�e�����g�� 
	SJISChCodeLib sjis_ch_code_lib; // SJIS���g��

	// ���ˑ��ł���@�\�ɂ��Ăǂ���g������ݒ�
	Setting setting; 
	setting.thread_lib = &win_thread_lib;
	setting.std_stream_lib = &cstd_std_stream_lib;
	setting.filesystem_lib = &win_filesystem_lib;
	setting.ch_code_lib = &sjis_ch_code_lib;
	
	// �����Ŏw�肵��thread_lib�Ȃǂ̃|�C���^��������̃I�u�W�F�N�g�́A
	// uninitialize���Ăяo���܂ő��݂��Ă���K�v������܂��B

	// Xtal��������
	initialize(setting);

	// �G���[���b�Z�[�W���o�C���h
	bind_error_message();

	// �����ŃX�N���v�g�̎��s���s��

	// Xtal��j��
	uninitialize();

	return 0;
}
\endcode

Xtal�͊��ˑ��ł���@�\�́A�ȒP�Ɏ�ւ����ł���悤�ɂȂ��Ă��܂��B\n
*/

/** \page usehelloworld �t�@�C���ɏ�����Ă���Xtal�����s
���̂悤��Hello, World���o�͂���X�N���v�g�AHelloWorld.xtal������Ƃ��܂��B\n
\code
// HelloWorld.xtal
println("Hello, World");
\endcode
�����C++����Ăяo���ɂ�load�֐����g���܂��B\n
\code
// C++
load("HelloWirld.xtal");

// �R���p�C���G���[����s���G���[����������ߑ�����B
XTAL_CATCH_EXCEPT(e){
	stderr_stream()->println(e); // stderr�ɗ�O�I�u�W�F�N�g���o�͂���
}

\endcode
load�֐��͌Ă΂�邽�т�HelloWorld���R���p�C�����Ď��s���܂��B\n   
*/

/** \page useexcept Xtal�Ŕ���������O��ߑ�����
XTAL_CATCH_EXCEPT(e)���g���܂��B\n
\code
any->call();

XTAL_CATCH_EXCEPT(e){
	// call���ŗ�O���Z�b�g���ꂽ�炱����ʂ�
	// e�ɗ�O�I�u�W�F�N�g���Z�b�g�����B
}
else{
	// ��O���������Ă��Ȃ��Ȃ炱����ʂ�
}
\endcode

*/

/** \page usestring �������Xtal�\�[�X�����s
�t�@�C���Ƃ��Ăł͂Ȃ��A������Ƃ��ă\�[�X��ێ����Ă��Ă�������s�������ꍇ�́Acompile�֐����g���A���ʂ��Ăяo���܂��B \n
\code
const char* source = " println(\"Hello, World\"); ";

// �R���p�C���G���[������΁Acode��null���Ԃ�
if(CodePtr code = compile(source)){
	code->call();
}

XTAL_CATCH_EXCEPT(e){
	stderr_stream()->println(e); // stderr�ɗ�O�I�u�W�F�N�g���o�͂���
}
\endcode
*/

/** \page useanyptr AnyPtr
AnyPtr�͂�����Xtal�̃I�u�W�F�N�g��ێ��ł���A�X�}�[�g�|�C���^�^�ł��B \n   
AnyPtr�́A���m�ɂ�SmartPtr<Any>�^��typedef�ł��B \n

\section int2anyptr �����╂�������_���^��AnyPtr�𑊌ݕϊ����� 
AnyPtr�͑S�Ă̐����╂�������_�����󂯎��R���X�g���N�^����`����Ă���̂ŁAC++�̐�������AnyPtr�ւ̕ϊ��͎����I�ɍs���܂��B\n
\code
AnyPtr any = 100;
AnyPtr value = 10.0f;
\endcode
�t��AnyPtr�^�ɓ��ꂽ���̂𐮐��ɕϊ��������ꍇ�AAny::to_i�����o�֐���Any::to_f�����o�֐����g���܂��B\n
\code
int i = any->to_i();
float f = value->to_f();
\endcode

\section str2anyptr �������AnyPtr�𑊌ݕϊ����� 
AnyPtr��const char*���󂯎��R���X�g���N�^����`����Ă��邽�߁A�����񃊃e����������AnyPtr�ւ̕ϊ��͎����I�ɍs���܂��B\n
\code
AnyPtr str = "string";
\endcode
�t��AnyPtr����C++�̕�����ɒ����ɂ́AAny::to_s�����o�֐����g���܂��B\n
to_s��StringPtr��Ԃ��Ă���̂ŁAStringPtr�Ŏ󂯎��܂��B\n
StringPtr��SmartPtr<String>��typedef�ł��B\n    
\code
StringPtr s = str->to_s();
\endcode
�����āAString::c_str�֐��ŁAconst char*�Ƃ��Ď󂯎��܂��B\n
\code
const char* ccp = s->c_str();
\endcode

\section anyptr2any AnyPtr�^�𑼂̌^�ɕϊ�����
�Ⴆ�΁AString��ێ����Ă���AnyPtr��StringPtr�^�ɕϊ�����ꍇ�AAnyPtr::to_s()���g���܂����A���̑��ɂ�ptr_cast�֐����g�����Ƃ�String�^�ɕϊ��ł��܂��B\n
ptr_cast�֐��͎��̂悤�Ȋ֐��ł��B    \n

\code
template<class T>
SmartPtr<T> ptr_cast(const AnyPtr& from);
\endcode
dynamic_cast����C++�̃L���X�g�Ɠ����`���ŌĂяo���܂��B    \n
\code
AnyPtr astr = "string";
StringPtr str = ptr_cast<String>(astr);
\endcode
�����L���X�g�Ɏ��s������Anull��Ԃ��܂��B\n  
\n
��΂ɂ����StringPtr���A�Ɗm�肵�Ă���ꍇ�Aunchecked_ptr_cast���g���܂��B\n
ptr_cast�͌p���֌W�𒲂ׂ邽�ߎ኱���Ԃ�������܂����Aunchecked_ptr_cast�͍����ł��B\n
\code
AnyPtr astr = "string";
StringPtr str = unchecked_ptr_cast<String>(astr);
\endcode
*/

/** \page usefun C++�̊֐���Xtal����Ăׂ�悤�ɕϊ�����
C++�̊֐���Xtal�̊֐�����Ăׂ�`���ɕϊ�����ɂ́Afun�֐����g���܂��B\n 
fun�֐����ȒP�Ɍ����ƁAC++�̊֐��|�C���^��n���΁AXtal�ň�����I�u�W�F�N�g������ĕԂ��A�Ƃ����֐��ł��B\n
\n
fun�֐��͎��̂悤�Ȍ`���ł��B \n
\code
NativeFunPtr fun(R (*pointer_to_function)());
NativeFunPtr fun(R (*pointer_to_function)(A0));
NativeFunPtr fun(R (*pointer_to_function)(A0, A1));
NativeFunPtr fun(R (*pointer_to_function)(A0, A1, A2));
NativeFunPtr fun(R (*pointer_to_function)(A0, A1, A2, A3));
NativeFunPtr fun(R (*pointer_to_function)(A0, A1, A2, A3, A4));
\endcode
R��A0�́A�֐��̖߂�l�A�������������肳��Č��܂�܂��B\n
\code
void foo(int a, int b){
    printf("%d\n", a+b);
}

void bar(){
    printf("%s\n", "bar");
}

void test(){
	NativeFunPtr f = fun(&foo);
	NativeFunPtr b = fun(&bar);
}
\endcode

���O�t�������Ƃ��̃f�t�H���g�l���w�肵�����ꍇ�Aparam�����o�֐����g���܂��B    
\code
void foo(int key1, int key2){
    printf("%d\n", key1+key2);
}

void test(){
	// ��ڂ̈�����key1�Ɩ��Â��A�f�t�H���g�l��50��
	// ��ڂ̈�����key2�Ɩ��Â��A�f�t�H���g�l��100�ɂ���
	NativeFunPtr f = fun(&foo)->param(1, Xid(key1), 50)->param(2, Xid(key2), 100);
}
\endcode
*/

/** \page usefuncall �֐��̌Ăяo��
AnyPtr�Ɋi�[����Ă���̂�C++�̊֐���Xtal�̊֐����Ɋւ�炸�AAny::call���g���܂��B\n
\code
void add(int a, int b){
    printf("%d\n", a+b);
}
void test(){
	AnyPtr add = fun(&add);
	AnyPtr ret = add->call(100, 200);
}
\endcode
��AnyPtr�^�̕ϐ���()��t���Ĉ�����n���Ƃ����ƂĂ������I�Ȋ֐��̌Ăяo�����ł��܂��B\n
���O�������̌Ăяo�������̂悤�Ɏ�y�ɋL�q�ł��܂��B\n
\code
void add(int key1, int key2){
     printf("%d\n", key1+key2);
}
void test(){
	AnyPtr add = fun(&add)->param(1, Xid(key1), 10)->param(2, Xid(key2), 20);
	AnyPtr ret = add->call(Named(Xid(key2), 50)); // => 60
}
\endcode
*/

/** \page usesend ���\�b�h�Ăяo��
AnyPtr�Ɋi�[����Ă���̂�C++�̃I�u�W�F�N�g��Xtal�̃I�u�W�F�N�g���Ɋւ�炸�AAny::send���g���܂��B\n
\code
int len = obj->send(Xid(length))->to_i();
AnyPtr ret = obj->send(Xid(slice), 0, 2);
printf("%s\n", ret->to_s()->c_str());
\endcode
*/

/** \page usenew C++�̃I�u�W�F�N�g��new����
xnew<T>�e���v���[�g�֐����g���ƁAC++�̃I�u�W�F�N�g���AXtal�ł�������I�u�W�F�N�g�Ƃ��č쐬�ł��܂��B\n  
xnew<T>�֐��́ASmartPtr<T>�^��Ԃ��܂��B\n
\n
�Ⴆ�΁A�g�ݍ��݂̔z���Array�N���X��C++�ŋL�q����Ă��܂����A�����C++�Ő�������ɂ͎��̂悤�ɏ����܂��B\n
\code
// ArrayPtr �� SmartPtr<Array> ��typedef
ArrayPtr ary = xnew<Array>(10); //����10�̔z��𐶐�
ary->push_back(10);
\endcode
 
���[�U�[����`�����N���X��xnew�Ő����o���܂��B\n
\code
class Foo{
pubic:
    void bar(){}
};
SmartPtr<Foo> foo = xnew<Foo>();
foo->bar();
\endcode
�����̃I�u�W�F�N�g�́A���ׂẴX�}�[�g�|�C���^���Q�Ƃ��Ȃ��Ȃ�΁A�����I�ɃK�[�x�[�W�R���N�V�����ō폜�����̂ŁA�����I��delete�͕K�v����܂���\n
*/

/** \page userefmember �����o�̎擾
Xtal�ł́A�N���X�Alib�I�u�W�F�N�g�Ȃǂ̃����o���擾����̂ɁA�uInt::foo�v�Ə����܂����A�����C++�ŏ������@�ł��B\n
\n
����ɂ�Any::member�����o�֐����g���܂��B\n
�擾�����������o�̖��O��������Ƃ��ēn���܂��B\n    
�����擾�����������o�������ꍇ�Anull���Ԃ�܂��B\n  
\code 
AnyPtr foo = cls->member(Xid(foo));
AnyPtr bar = lib()->member(Xid(bar)):
\endcode
*/

/** \page usedefmember �����o�̒�`
C++����N���X�⃂�W���[���Alib�I�u�W�F�N�g�̃����o��ǉ���`������@�ł��B�uInt::foo : 100;�v�����ł��B

����ɂ�Any::def�����o�֐����g���܂��B    
�������ɒ�`���A�������ɒ�`����l�����܂��B   

 
cls->def("foo", 100);
lib()->def("bar", fun(&add));
*/


/** \page useat �z��A�A�z�z��̗v�f�擾�A�ݒ�
Any::at���g���āA�v�f�̎擾���s���܂��B\n
\code
ret = ary->at(0);
ret = map->at("key");
\endcode
 
�l�̐ݒ�́AAny::set_at���g���܂��B\n
\code
any->set_at(0, 10);
map->set_at("test", 5);
\endcode
*/

/** \page usereturn Xtal����I�u�W�F�N�g���󂯎��
Xtal����l��C++�ɕԂ��ɂ̓g�b�v���x����return�����g���܂��B\n
\code
// test.xtal
return 100 + 20;
\endcode
 
\code
// C++
// test.xtal�t�@�C�������s���Areturn���ꂽ�I�u�W�F�N�g�𓾂�
AnyPtr ret = load("test.xtal");

// ��O���������Ă��Ȃ����`�F�b�N
XTAL_CATCH_EXCEPT(e){
	stderr_stream()->println(e);
}
else{
	int value = ret->to_i();
	printf("%d\n", value);
}
\endcode
*/

/** \page useimport Xtal�փI�u�W�F�N�g��n��
���C�u�������Ǘ�����lib�I�u�W�F�N�g�̃����o�Ƃ��Ē�`���Ă�������@������܂��B\n
\code
// C++
void cpp_fun(){
    puts("cpp_fun");
}

void test(){
	// lib�I�u�W�F�N�g�ɓo�^
	lib()->def(Xid(cpp_value), fun(&cpp_fun));
	load("test.xtal");
}
\endcode

\code
// test.xtal
lib::cpp_value(); // => cpp_fun
\endcode
�����o�͊�{�I�ɍĒ�`�s�\�Ȃ̂ŁA�Ăяo���̂��тɐݒ肷��I�u�W�F�N�g��ς������ȂǂƂ������ꍇ�ɁA���̕��@�ł͑Ή��ł��܂���B\n
\n
���Ɏ��s���Ɉ����Ƃ��ēn�����@������܂��B\n

\code
// C++
void test(){
	// �R���p�C�����āA�����call�Ŏ��s����B
	if(CodePtr code = compile("test.xtal")){
		code->call(100, 200);
	}
}
\endcode

\code
// test.xtal
args: ...; // �g�b�v���x����...�̓X�N���v�g���s����ۂɓn���ꂽ�����������Ă���B
args[0].p; //=> 100
args[1].p; //=> 200
\endcode

Code::filelocal�ł��̃R�[�h��filelocal�����o���āA�ϐ����`���邱�Ƃ��ł��܂��B\n
\code
// C++
void test(){
	// �R���p�C�����āA�����call�Ŏ��s����B
	if(CodePtr code = compile("test.xtal")){
		code->def(Xid(foo), 100);
		code->call();
	}
}
\endcode

\code
// test.xtal
foo.p; //=> 100
\endcode
*/

/** \page usecppclass C++�̃N���X���o�C���h����
\section secvec2d 2�����̃x�N�g���N���X��Xtal�Ŏg����悤�ɂ����
\code
// test.cpp
class Vector2D{
	float x, y;
	
	Vector2D(float x = 0, float y = 0)
		:x(x), y(y){}
	
	float length() const{
		return sqrt(x*x + y*y);
	}
	
	void normalize(){
		float len = length();
		x /= len;
		y /= len;
	}
};

// XTAL_PREBIND�̒��Ōp���֌W�̓o�^�A�R���X�g���N�^�̓o�^���s��
XTAL_PREBIND(Vector2D){
	// it��ClassPtr�ł���B
	// it->��Class�N���X�̃����o�֐����Ăׂ�
	
	// �R���X�g���N�^�̓o�^
	it->def_ctor2<Vector2D, float, float>()->param(1, Xid(x), 0)->param(2, Xid(y), 0);
}

// XTAL_BIND�̒��Ń����o�֐��̓o�^���s��
XTAL_BIND(Vector2D){
	// it��ClassPtr�ł���B
	// it->��Class�N���X�̃����o�֐����Ăׂ�

	it->def_var(Xid(x), &Vector2D::x); // �����o�ϐ�x�̃Z�b�^�A�Q�b�^��o�^
	it->def_var(Xid(y), &Vector2D::y); // �����o�ϐ�y�̃Z�b�^�A�Q�b�^��o�^
	it->def_method(Xid(length), &Vector2D::length); // �����o�֐�length��o�^
	it->def_method(Xid(normalize), &Vector2D::normalize); // �����o�֐�length��o�^
}

void test(){
	// lib�I�u�W�F�N�g�ɓo�^
	lib()->def(Xid(Vector), cpp_class<Vector2D>());
}
\endcode

\code
// test.xtal
vec: lib::Vector2D(10, 20);
vec.length.p;
vec.normalize;
vec.length.p;
\endcode

\section secfoo �p���֌W������N���X���o�C���h����
C++�̃N���X�Ɍp���֌W������ꍇ�AClass::inherit���g���āA�p���֌W��o�^����K�v������܂��B\n
��������Ȃ���΁A�L���X�g�Ɏ��s���܂��B\n
\code
class Foo{
public:
    int a;
    Foo(int value = 0){ a = value; }
    int add(int b){ return a+=b; }
};

class SubFoo : public Foo{
public:
    SubFoo(){}
};

XTAL_PREBIND(Foo){
	it->def_ctor1<Foo>()->param(1, Xid(value), 0);
}

XTAL_BIND(Foo){
	it->def_method(Xid(add), &Foo::add);
}

XTAL_PREBIND(SubFoo){
	// inherit�Ōp���֌W������
	// cpp_class<Foo>()��Foo�N���X�̃N���X�I�u�W�F�N�g���擾�ł���
	it->inherit(cpp_class<Foo>());
	it->def_ctor0<SubFoo>();
}

void test(){
    // lib�I�u�W�F�N�g�ɓo�^����
    lib()->def(Xid(Foo), cpp_class<Foo>());
    lib()->def(Xid(SubFoo), cpp_class<SubFoo>());

    // ���s���Č��ʂ��󂯎��
	AnyPtr ret = load("test.xtal");
    
    // ������ret�ɂ�SubFoo�N���X�̃C���X�^���X�������Ă���
    
    // ptr_cast��SubFoo�Ƃ��Ď��o����
    SmartPtr<SubFoo> subfooref = ptr_cast<SubFoo>(ret);
    
    // SubFoo�ƌp���֌W������Foo�Ƃ��Ă����o����
    SmartPtr<Foo> fooref = ptr_cast<Foo>(ret);
}
\endcode

\code
// test.xtal
// lib�I�u�W�F�N�g�ɓo�^���ꂽ�ASubFoo�N���X�����o���ăC���X�^���X�𐶐�����B
subfoo: lib::SubFoo(); 
return subfoo; // subfoo��return����
\endcode
*/

/** \page usebytecode �o�C�g�R�[�h�ɃR���p�C������
\code
// �t�@�C�����R���p�C������
if(CodePtr code = compile_file("test.xtal")){
	// test.xtalc�Ƀo�C�g�R�[�h��ۑ�����
	FileStreamPtr fs = xnew<FileStream>("test.xtalc", "w");
	fs->serialize(code);
}
\endcode

\code
// �o�C�g�R�[�h��ǂݏo��
FileStreamPtr fs = xnew<FileStream>("test.xtalc", "r");
if(CodePtr code = ptr_cast<Code>(fs->deserialize())){
	// ���s����
	code->call();
}
\endcode
*/

/** \page
�֐�����R����ꍇ�́A������Class�Ƃ��ēZ�߁A�����n���ƃX�}�[�g�ł��B    
Class�N���X���Ŋ��ł�AnyPtr���p�����Ă��܂��B���̂��߁AAnyPtr�Ɏ����ϊ��\�ł��B    
    
Class�N���X�͊֐��̓o�^�ɕ֗���def_fun�����o�֐��������Ă��܂��B    
Class::def_fun�� any->def("foo", fun(&foo)) �̃V���[�g�J�b�g�ł��B    

include <xtal.h>
using namespace xtal;

int add(int a, int b){ return a+b; }
int sub(int a, int b){ return a-b; }
int mul(int a, int b){ return a*b; }
int div(int a, int b){ return a/b; }

void test(){
    // Xtal�̏�����
    initialize(); 
    
    try{

        ClassPtr ops = xnew<Class>("ops"); // ops�N���X�����
        ops->def_fun("add", &add); // add�Ƃ������O�̃����o�Ƃ���add�֐���o�^
        // ops->def("add", fun(&add)); // ����Ə�͓���
    
        ops->def_fun("sub", &sub);
        ops->def_fun("mul", &mul);
        
        // params�Ŗ��O�t��������t������
        ops->fun("div", &div)->params("a", 0, "b", 1); 
    
        // lib�I�u�W�F�N�g�ɓo�^����
        lib()->def("ops", ops);
    
        // test.xtal�����[�h���A���s����
        load("test.xtal");
        
    }catch(AnyPtr e){
         fprintf(stderr, "%s\n", e->to_s()->c_str());
    }
}
*/