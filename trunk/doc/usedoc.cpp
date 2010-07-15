
/** \page usepage C++�g�ݍ��݃T���v��
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

/** \page usemain
Lua�Ȃǂ̃X�N���v�g����́AC/C++�Ƃ̂���肪�ώG�ł�����̂������B\n
���̂��ߌ�������҈ȊO�ɃX�N���v�g�����C++�Ƃ̊Ԃ���莝�A�u�o�C���_�v�ƌĂ΂����̂��悭�����B\n
\n
Xtal�ł͍ŏ�����X�N���v�g����Ɩ��ڂ����o�C���_��������Ă��邽�߁A\n
�킴�킴�o�C���_��T�����Ƃ��A�܂��I���W�i���̃o�C���_�����K�v�������A�����ɑg�ݍ��ނ��Ƃ��ł���B\n
*/

/** \page useinitialize Xtal�̏�����
�����ł͗�Ƃ���Windows�ł̏��������@�������B\n
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

	{
	    // �����ŃX�N���v�g�̎��s���s��
	}
	
    // Xtal��j��
    uninitialize();

    return 0;
}
\endcode

Xtal�ł͊��ˑ��̋@�\�͊ȒP�Ɏ��ւ��邱�Ƃ��ł���悤�ɂȂ��Ă���B\n
Windows��Linux�ɂ��ẮA�ŏ�����@�\���p�ӂ���Ă��邽�߁A������g�����Ƃ��ł���B\n
�e������xtal_lib�f�B���N�g�����ɃN���X�Œ񋟂���Ă���B\n
�g�������@�\��include���Ainitialize����uninitialize�܂Ő�������ϐ��Ƃ��Ē�`���A\n
Setting�̊e�����o�ɂ��̃|�C���^�������Ainitailize�֐��ɓn�����ƁB\n
\n
bind_error_message�ŃG���[���b�Z�[�W�̃o�C���h���ł���B\n
����ɂ��AXRE1001�Ƃ������G���[���b�Z�[�W���A�Ӗ��̂���e�L�X�g�Ƃ��ē�����悤�ɂȂ�B\n
�����[�X���ȂǁA�G���[���b�Z�[�W���K�v�Ȃ��̂ł���΂�����Ăяo���Ȃ����ƂŎ኱�̃������ߖ�ɂȂ�B\n
\n
uninitialize���ɎQ�ƃJ�E���g��͂񂾂܂܂̃I�u�W�F�N�g�������assert�Œ�~���邽�߁A\n
�X�N���v�g�̎��s�̕����̓u���b�N�ň͂ނ��A�ʊ֐��ōs���A���[�J���ϐ��Œ�`����AnyPtr�Ȃǂ��m���Ƀf�X�g���N�^����Ă���悤�ɂ��悤�B\n
*/



/** \page usehelloworld �t�@�C���ɏ�����Ă���Xtal�����s
���̂悤��Hello, World���o�͂���X�N���v�g�AHelloWorld.xtal������Ƃ���\n
\code
// HelloWorld.xtal
println("Hello, World");
\endcode
�����C++����Ăяo���ɂ�load�֐����g���B\n
\code
// C++
load(XTAL_STRING("HelloWorld.xtal"));

// xtal_macro.h��include���Ă���ꍇ�A���̂悤�ɋL�q���Ă��悢
// load(Xs("HelloWorld.xtal"))

// �R���p�C���G���[����s���G���[����������ߑ�����B
XTAL_CATCH_EXCEPT(e){
    stderr_stream()->println(e); // stderr�ɗ�O�I�u�W�F�N�g���o�͂���
}
\endcode
*/

/** \page useexcept Xtal�Ŕ���������O��ߑ�����
XTAL_CATCH_EXCEPT(e)�}�N�����g�����ƂŁAXtal�����n�Ŕ���������O��⑫���邱�Ƃ��ł���B\n
\code
any->call();

XTAL_CATCH_EXCEPT(e){
    // call���ŗ�O���Z�b�g���ꂽ�炱����ʂ�
    // e�ɗ�O�I�u�W�F�N�g���Z�b�g�����B
	stderr_stream()->println(e); // stderr�ɗ�O�I�u�W�F�N�g���o�͂���
}
else{
    // ��O���������Ă��Ȃ��Ȃ炱����ʂ�
}
\endcode
*/

/** \page usestring �������Xtal�\�[�X�����s
�t�@�C���Ƃ��Ăł͂Ȃ��A������Ƃ��ă\�[�X��ێ����Ă��Ă�������s�������ꍇ�́Acompile�֐����g���A���ʂ��Ăяo���B \n
\code
const char* source = " println(\"Hello, World\"); ";

// �R���p�C���G���[������΁Acode��null���Ԃ�
if(CodePtr code = compile(source)){
    code->call(); // �R���p�C�������R�[�h�����s����
}

XTAL_CATCH_EXCEPT(e){
    stderr_stream()->println(e); // stderr�ɗ�O�I�u�W�F�N�g���o�͂���
}
\endcode
*/

/** \page useanyptr AnyPtr
AnyPtr�͂�����Xtal�̃I�u�W�F�N�g��ێ��ł���A�X�}�[�g�|�C���^�^�ł���B \n   
AnyPtr�́A���m�ɂ�SmartPtr<Any>�^��typedef�ƂȂ��Ă���B \n

\section int2anyptr �����╂�������_���^��AnyPtr�𑊌ݕϊ����� 
AnyPtr�͑S�Ă̐����╂�������_�����󂯎��R���X�g���N�^����`����Ă���̂ŁAC++�̐�������AnyPtr�ւ̕ϊ��͎����I�ɍs����B\n
\code
AnyPtr any = 100;
AnyPtr value = 10.0f;
\endcode
�t��AnyPtr�^�ɓ��ꂽ���̂𐮐��ɕϊ��������ꍇ�AAny::to_i�����o�֐���Any::to_f�����o�֐����g���B\n
\code
int i = any->to_i();
float f = value->to_f();
\endcode
����́A�I�u�W�F�N�g�ɂ���ẮAXtal���x����to_i���\�b�h���Ă΂�邽�߁A��O���������邩������Ȃ����Ƃɒ��ӂ���B\n

\section str2anyptr �������AnyPtr�𑊌ݕϊ����� 
AnyPtr��const char_t*���󂯎��R���X�g���N�^����`����Ă��邽�߁A�����񃊃e��������AnyPtr�ւ̕ϊ��͎����I�ɍs����B\n
�������AUNICODE�Ȃǂ̉��������߂邽�߂ɁAXTAL_STRING�}�N���ň͂ޕ����]�܂����B\n
\code
AnyPtr str = "string";
AnyPtr str2 = XTAL_STRING("string");
\endcode
�t��AnyPtr����C++�̕�����ɒ����ɂ́AAny::to_s�����o�֐����g���܂��B\n
to_s��StringPtr��Ԃ��Ă���̂ŁAStringPtr�Ŏ󂯎��܂��B\n
StringPtr��SmartPtr<String>��typedef�ł��B\n    
\code
StringPtr s = str->to_s();
\endcode
�����āAString::c_str�֐��ŁAconst char_t*�Ƃ��Ď󂯎��܂��B\n
\code
const char* ccp = s->c_str();
\endcode

\section anyptr2any AnyPtr�^�𑼂̌^�ɕϊ�����
String��ێ����Ă���AnyPtr��StringPtr�^�ɕϊ�����ꍇ�Ato_s���\�b�h���g���Ƃ������Ƃ�����������A
���̑��ɂ�ptr_cast�֐����g�����Ƃ�String�^�ɕϊ����邱�Ƃ��ł���B\n
ptr_cast�֐��͎��̂悤�Ȋ֐��ł���B    \n

\code
template<class T>
const SmartPtr<T>& ptr_cast(const AnyPtr& from);
\endcode
dynamic_cast����C++�̃L���X�g�Ɠ����`���ŌĂяo���悤�Ƀf�U�C������Ă���B\n
\code
AnyPtr astr = XTAL_STRING("string");
StringPtr str = ptr_cast<String>(astr);
\endcode
�����L���X�g�Ɏ��s������Anull��Ԃ��B\n  
\n
��΂ɂ����StringPtr���A�Ɗm�肵�Ă���ꍇ�Aunchecked_ptr_cast���g����B\n
ptr_cast�͌p���֌W�𒲂ׂ邽�ߎ኱���Ԃ������邪�Aunchecked_ptr_cast�͍����ɓ��삷��B\n
\code
AnyPtr astr = XTAL_STRING("string");
StringPtr str = unchecked_ptr_cast<String>(astr);
\endcode
*/

/** \page usenew C++�̃I�u�W�F�N�g��Xtal���Ǘ��ł���I�u�W�F�N�g�Ƃ��č쐬����
xnew<T>�e���v���[�g�֐����g���ƁAC++�̃I�u�W�F�N�g��Xtal�ł�������I�u�W�F�N�g�Ƃ��č쐬�ł���B\n  
xnew<T>�֐��́ASmartPtr<T>�^��Ԃ��܂��B\n
\n
�Ⴆ�΁A�g�ݍ��݂̔z���Array�N���X��C++�ŋL�q����Ă��邪�A�����C++�Ő�������ɂ͎��̂悤�ɏ����B\n
\code
// ArrayPtr �� SmartPtr<Array> ��typedef
ArrayPtr ary = xnew<Array>(10); //����10�̔z��𐶐�
ary->push_back(10);
\endcode
 
���[�U�[����`�����N���X��xnew�Ő����ł���B\n
\code
class Foo{
pubic:
    void bar(){}
};
SmartPtr<Foo> foo = xnew<Foo>();
foo->bar();
\endcode
�����̃I�u�W�F�N�g�́A���ׂẴX�}�[�g�|�C���^���Q�Ƃ��Ȃ��Ȃ�΁A\n
�����I�ɃK�[�x�[�W�R���N�V�����ō폜�����̂ŁA�����I��delete�͕K�v�����B\n
*/

/** \page usefuncall �֐��̌Ăяo��
AnyPtr�Ɋi�[����Ă���̂�C++�̊֐���Xtal�̊֐����Ɋւ�炸�AAny::call���g���B\n
\code
// foo�Ɋi�[����Ă���֐�������(100, 200)�ŌĂяo��
AnyPtr ret = foo->call(100, 200);
\endcode
���O�������̌Ăяo�������̂悤�Ɏ�y�ɋL�q�ł���B\n
\code
// foo�Ɋi�[����Ă���֐�������(10, hoge:50)�ŌĂяo��
AnyPtr ret = foo->call(10, Xnamed(hoge, 50));
\endcode
*/

/** \page usesend ���\�b�h�Ăяo��
AnyPtr�Ɋi�[����Ă���̂�C++�̃I�u�W�F�N�g��Xtal�̃I�u�W�F�N�g���Ɋւ�炸�AAny::send���g���B\n
\code
int len = obj->send(Xid(length))->to_i();
AnyPtr ret = obj->send(Xid(slice), 0, 2);
printf("%s\n", ret->to_s()->c_str());
\endcode
Xid�Ƃ����̂́AXtal��intern�ςݕ�������ȒP�ɐ������邽�߂̃}�N���ł���B\n
\n
�Z�J���_���L�[�t�ŌĂяo���ɂ�Any::send2���g���B\n
*/

/** \page useiter �C�e���[�^�̏���
�z���A�z�z��A�܂��̓C�e���[�^�����񂷂�ꍇ�AXfor�}�N�����g���B\n
\code
Xfor(val, array){
    val.p;
}

Xfor2(key, val, map){
    key.p;
    val.p;
}
\endcode
����Xfor�̒��ł͕��ʂ�break�ȂǂŔ����o�����Ƃ��ł���B\n
�܂��Afirst_step�Ƃ����A���[�v�̈�ԍŏ����ǂ��������߂����[�J���ϐ�����`����Ă��Ďg�����Ƃ��ł���B\n
\n
�Z�J���_���L�[�t�ŌĂяo���ɂ�Any::send2���g���B\n
*/


/** \page userefmember �����o�̎擾
����ɂ�Any::member�����o�֐����g���܂��B\n
�擾�����������o�̖��O��������Ƃ��ēn���B\n    
�����擾�����������o�������ꍇ�Aundefined���Ԃ�B\n
�����o�̎擾�Ɋւ��Ă�C++���x���ł͗�O�̓Z�b�g����Ȃ��B\n  
\code 
// �N���X��foo�����o�����o��
AnyPtr foo = cls->member(Xid(foo));

// �N���X��bar�����o�����o��
AnyPtr bar = lib()->member(Xid(bar)):
\endcode
*/

/** \page useat �z��A�A�z�z��̗v�f�擾�A�ݒ�
Array::at, Map::at���g���āA�v�f�̎擾���s���B\n
\code
ret = ary->at(0);
ret = map->at("key");
\endcode
 
�l�̐ݒ�́AArray::set_at, Map::set_at���s���B\n
\code
any->set_at(0, 10);
map->set_at("test", 5);
\endcode
*/

/** \page usereturn Xtal����I�u�W�F�N�g���󂯎��
Xtal����l��C++�ɕԂ��ɂ̓g�b�v���x����return�����g���B\n
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

����return���������ꍇ�Atoplevel�I�u�W�F�N�g�������I�ɕԂ����B\n
\code
// test.xtal
hoo: 100;

class Vec{
	public _x; 
	public _y;
}

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
	// toplevel��hoo���擾����
	int value = ret->member(Xid(hoo))->to_i();
    printf("%d\n", value);
}
\endcode
*/

/** \page usecppclass C++�̃N���X���o�C���h����
\section secvec2d 2�����̃x�N�g���N���X��Xtal�Ŏg����悤�ɂ����
\code
// test.cpp
class Vector2D{
public:
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

// XTAL_PREBIND�̒��Ōp���֌W�̓o�^�A�R���X�g���N�^�̓o�^�A�������閼�O��Ԃ��w�肷��
XTAL_PREBIND(Vector2D){
	Xregister(Lib); // lib��Vector2D�Ƃ������O�œo�^����
    
    // �R���X�g���N�^�̓o�^
	Xdef_ctor2(float, float);
		Xparam(x, 0); // �I�v�V���i������x
		Xparam(y, 0); // �I�v�V���i������y
}

// XTAL_BIND�̒��Ń����o�֐��̓o�^���s��
XTAL_BIND(Vector2D){
    // it��ClassPtr�ł���B
    // it->��Class�N���X�̃����o�֐����Ăׂ�

    Xdef_var(x); // �����o�ϐ�x�̃Z�b�^�A�Q�b�^��o�^
    Xdef_var(y); // �����o�ϐ�y�̃Z�b�^�A�Q�b�^��o�^
    Xdef_method(length); // �����o�֐�length��o�^
    Xdef_method(normalize); // �����o�֐�length��o�^
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
	Xregister(Lib); // lib��Foo�Ƃ������O�œo�^����

    Xdef_ctor1(int);
		Xparam(value, 0);
}

XTAL_BIND(Foo){
    Xdef_method(add);
}

XTAL_PREBIND(SubFoo){
 	Xregister(SubFoo); // lib��Foo�Ƃ������O�œo�^����
	
   // Xinherit�Ōp���֌W������
    Xinherit(Foo);
	
	// �R���X�g���N�^���`����
    Xdef_ctor0();
}

void test(){
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

