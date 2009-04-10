
/**
* \biref xtal�̃��C�u����
*/
namespace lib{

	/**
	* \brief �r���g�C���̃N���X��֐�
	*/
	namespace builtin{
	
		/**
		* \brief �t�@�C���V�X�e���̃N���X��֐�
		*/
		namespace filesystem{}
		
		/**
		* \brief �f�o�b�O�̃N���X��֐�
		*/
		namespace debug{}
		
		/**
		* \brief xpeg�̃N���X��֐�
		*/
		namespace xpeg{}
	}
}




/** \mainpage Programing Xtal
Xtal�́A��ɃQ�[������p�r�̂��߂ɁAC++�ɑg�ݍ��݁A�A�g�����Ďg�����߂ɊJ�����ꂽ����ł��B\n
��{�I��Xtal��P�̂Ŏg�����Ƃ͖����AC++�Ƒg�ݍ��킹�Ďg���܂��B\n
���̃h�L�������g���AC++���g�p�ł��邱�Ƃ�O��ɋL�q����Ă��܂��B\n
\n
Xtal��Ruby, Python, D, Lua, NewtonScript, ECMAScript���A�ƂĂ������̌�����Q�l�ɂ��č���܂����B\n
\n

\section feature ����

- �N���X�x�[�X�I�u�W�F�N�g�w�� 
- C++ like�ȍ\�� 
- C++�ɗe�Ղɑg�ݍ��߂� 
- ���I�Ȍ^ 
- �N���[�W�� 
- �t�@�C�o�[ (�R���[�`���A�}�C�N���X���b�h) 
- byte code�ɂ�鉼�z�}�V���쓮 
- native thread�Ή� 
- MultiVM 

\section xindexsec Xtal
- \subpage tutorial
- \subpage syntax
- \subpage xtalapis
\section cppindexsec C++
- \subpage cppapis
- \subpage usepage
*/

/** \page xtalapis Xtal�̕W���N���X��֐�
�ȉ����Q�Ƃ��Ă��������B\n
- \link lib::builtin Xtal�̕W���N���X��֐� \endlink
*/

/** \page cppapis C++��API
�ȉ����Q�Ƃ��Ă��������B\n
- \link xtal C++��API \endlink
*/

/** \page syntax Xtal����\��
- \subpage comment
- \subpage identifier
- \subpage reserved
- \subpage defvar
- \subpage expr
- \subpage sentence
- \subpage overloadable_operator
*/

/** \page expr ��
- \subpage pseudovar
- \subpage numberlit
- \subpage string
- \subpage array_map
- \subpage fun
- \subpage method
- \subpage lambda
- \subpage fiber
- \subpage class
- \subpage singleton
- \subpage operator
*/

/** \page operator ���Z�q
- \subpage call
- \subpage method_call
- \subpage refmember
- \subpage secondary_key
- \subpage basic_operator
- \subpage cmp_operator
- \subpage etc_operator
- \subpage operator_priority
*/

/** \page sentence ��
- \subpage expr_sentence
- \subpage assign
- \subpage op_assign
- \subpage branch
- \subpage loop
- \subpage except
*/

/** \page tutorial Xtal����N�C�b�N�`���[�g���A��
\section secdebugprint �f�o�b�O�v�����g
\code
100.p;
"test".p;
\endcode
\section secvar �ϐ�
\code
foo: 100;
bar: 200;
(foo - bar).p; //=> -100
foo = 10;
bar = 20;
(foo - bar).p; //=> -10
\endcode

\section secmvar ���d��`�E���d���
\code
foo, bar: 100, 200;
(foo - bar).p; //=> -100
foo, bar = 10, 20;
(foo - bar).p; //=> -10
\endcode

\section secarray �z��
\code
array: [];
array.push_back(100);
array.push_back(200);
array.p; //=> [100, 200]
\endcode

\section secmap �A�z�z��
\code
map: [:];
map["test"] = 100;
map["test"].p; //=> 100
\endcode

\section secblock �u���b�N
\code
array: [10, 20, 30];
array{
    it.p;
}
//=> 10
//=> 20
//=> 30
\endcode

\section secfun �֐�
\code
fun foo(a, b){
    return a - b;
}
foo(15, 5).p; //=> 10
\endcode

\section seclambda �����_
\code
lambda: |a, b| a + b;
lambda(10, 20); //=> 30
\endcode

\section secclass �N���X
\code
class Bar{
    _boo;
    
    initialize(boo){
        _boo = boo;
    }

    say{
        _boo.p;
    }
}

bar: Bar("boo!");
bar.say; //=> boo! 
\endcode

*/


/** \page comment �R�����g
�R�����g��C++�Ɠ���̋L�q���\�ł��B\n
\n
����ɉ����A\#!�Ŏn�߂��s�R�����g���\�ł��B\n
\code
#! this is comment
\endcode
#�P�̂ł̓R�����g�ƂȂ�Ȃ����Ƃɒ��ӂ��Ă��������B\n
*/

/** \page identifier ���ʎq
�ϐ����̓A���t�@�x�b�g�A�����A�A���_�[�X�R�A���g���܂��B �����������Ŏn�܂�ϐ����͔F�߂��܂���B\n
�����R�[�h�̐ݒ肪�K�؂ł���΁A���{����g�p���邱�Ƃ��ł��܂��B\n
�A���_�[�X�R�A�Ŏn�܂閼�O�̓C���X�^���X�ϐ��ɂ����g���܂���B\n
�\���Ɠ������ʎq�͎g�p���邱�Ƃ��o���܂���B\n
\n
�������A.���Z�q��::���Z�q�̒���̏ꍇ�́A�\���ł��g�p���邱�Ƃ��o���܂��B\n

\code
test: 100; // ok
foo123: 200; // ok
alpha_0_test: 300; // ok
\endcode

\code
class: 400; // bad! class�͗\���
if: 500; // bad! if�͗\���
\endcode

\code
100.class; // ok .���Z�q�̌�Ȃ̂ŗ\��ꂪ�g����
Int::if: 600; // ok ::���Z�q�̌�Ȃ̂ŗ\��ꂪ�g����
\endcode

�܂��A�����R�[�h�̐ݒ肪�������s���Ă���Ȃ�΁A���{��̎��ʎq���g�����Ƃ��o���܂��B \n

\code
������: 100; // ok
\endcode

*/

/** \page reserved �\���
�\���̈ꗗ�ł��B \n

- if 
- for 
- else 
- fun 
- method 
- do 
- while 
- continue 
- break 
- fiber 
- yield 
- return 
- once 
- null 
- undefined 
- false 
- true 
- xtal 
- try 
- catch 
- finally 
- throw 
- class 
- callee 
- this 
- current_context 
- dofun 
- is 
- in 
- assert 
- nobreak 
- switch 
- case 
- default 
- singleton 
- debug 
- public 
- protected 
- private
*/

/** \page defvar �ϐ���`
\section local ���[�J���ϐ��̒�`

���݂̃X�R�[�v�ɕϐ����`���镶�ł��B\n
�����l�𔺂�Ȃ��ϐ��̒�`�͏o���܂���B\n 
�ϐ��ɂ͐ÓI�Ȍ^�͂Ȃ��A�Ȃ�̎�ނ̃f�[�^�̎Q�Ƃł��ێ��o���܂��B\n 
\code
foo: 111;
bar: "test";
foobar: null;
\endcode

\section defmultivar ���[�J���ϐ��̑��d��` 

�E�ӂɑ��l��Ԃ���������ꍇ�A������΂炵�Ď󂯎�邽�߂ɁA���[�J���ϐ��̑��d��`���ł��܂��B\n
�����E�ӂ̒l�̕��������ꍇ�A���ӍŌ�̕ϐ��ɑ��l�Ƃ��đ������܂��B\n
�E�ӂ̒l�̕������Ȃ��ꍇ�Aundefined�Ŗ��߂��܂��B\n
\code
{
    a, b: 0, 1;
    a.p; //=> 0
    b.p; //=> 1
}

{
    foo: fun(){
        return 5, 10;
    }
    a, b: foo();
    a.p; //=> 5
    b.p; //=> 10
}
\endcode
*/

/** \page pseudovar �[���ϐ�
�ϐ��Q�Ƃ̂悤�Ɉ�����I�u�W�F�N�g�ł��B

\section null 
�����������Ƃ�\���I�u�W�F�N�g�ł��B\n
if���Ȃǂ̏������ŁAnull�́u�U�v�ƂȂ�܂��B\n

\section true 
�u�^�v��\���I�u�W�F�N�g�ł��B\n
�������Anull��false��undefined�ȊO�̑S�ẴI�u�W�F�N�g�́u�^�v�ł���̂ŁA���ɓK���Ȓl�������ꍇ�ɂ���������g�p���邱�ƂɂȂ�ł��傤�B\n

\section false 
�u�U�v��\���I�u�W�F�N�g�ł��B \n
if���Ȃǂ̏������ŁAfalse�́u�U�v�ƂȂ�܂��B \n

\section undefined 
���l��\���I�u�W�F�N�g�ł��B
�Ⴆ�� ::?���Z�q �� .?���Z�q �ŁA���݂��Ȃ������o�����o�����Ƃ����Ƃ��ɕԂ����I�u�W�F�N�g�ł��B\n
if���Ȃǂ̏������ŁAundefined�́u�U�v�ƂȂ�܂��B\n

\section callee 
�����s���Ă���֐����g���w���Ă܂��B ����Ď��̂悤�ɂ��邱�ƂōċA�Ăяo�����\�ł��B\n
\code
callee();
\endcode

\section lib 
���C�u�����̃��[�h�A�o�^���i��V���O���g���N���X�I�u�W�F�N�g�ł��B\n
lib::foo �Ƃ���ƁAfoo.xtal�t�@�C�����������A�R���p�C���A���s���āA���̃t�@�C����return���ꂽ�l��ۑ����܂��B\n
��x�ڈȍ~�̃A�N�Z�X�͂��̕ۑ����ꂽ�l���Ԃ���܂��B\n
\code
// foo.xtal��ǂݍ��݁Areturn���ꂽ�l��foo�ϐ����`
foo: lib::foo; 

// ����foo.xtal�͓ǂݍ��܂�Ă���̂ŁA�ۑ����ꂽ�l��hoge�ϐ����`����B
hoge: lib::foo; 
\endcode

��̂悤�ȃt�@�C���ǂݍ��݈ȊO�ɂ��Alib�I�u�W�F�N�g�Ƀ����o�𒼐ڒ�`���邱�Ƃ��\�ł��B\n
\code
lib::foo: "foo!";
lib::foo.p; //=> foo!
\endcode

append_load_path���\�b�h���g���ƁA�����p�X�̒ǉ����o���܂��B\n
\code
lib.append_load_path("library")
\endcode

\section filelocal
���̃t�@�C���ŗL�̂̃g�b�v���x�����w�����O��ԓI�Ɉ�����V���O���g���N���X�I�u�W�F�N�g�ł��B \n
�ÓI�Ɍ�����Ȃ��ϐ��Q�Ƃ́Afilelocal���猟������܂��B\n
�܂��Afilelocal��builtin�I�u�W�F�N�g��inherit���Ă���̂ŁAbuiltin�ɒ�`����Ă���֐��܂��̓N���X�������I�Ɍ����ΏۂƂȂ�܂��B\n
\code
println(foo); // filelocal::println(filelocal::foo); �Ɠ��`
\endcode
*/

/*
\section defmember �����o��`�� 

����:
\code
�N���X��Ԃ��� :: ���ʎq : �� ; 
\endcode

�����̃N���X�Ƀ��\�b�h�Ȃǂ��`����\���ł��B\n
��:
\code
// �����̃N���X�Ɏ��g��2�{�̐���Ԃ����\�b�h��ǉ�
Integer::x2: method(){
    return this*2;
}
100.x2.p; //=> 200
\endcode

���ɓ����̃����o����`����Ă���ꍇ�A��O���������܂��B \n
*/

/* \page numberlit ���l���e����
\section integer �������e���� 
�����𐶐����鎮�͎��̂悤�ɋL�q���܂��B\n
\code
0
123
58325
\endcode
���₷���悤�ɓr���ɃA���_�[�o�[�����邱�Ƃ��o���܂��B\n
\code
1_234_567
\endcode

\subsection hex 16�i���������e���� 
\code
0x3f
0Xfd_2A
\endcode

\subsection bin 2�i���������e����
\code
0b1111
0B1111_0011
\endcode

\section float ���������_�����e����
���������_���𐶐����鎮�͎��̂悤�ɋL�q���܂��B\n

\code
12.3
0.56
\endcode

e�܂���E���g���A10���Ƃ���w���\�L���o���܂��B e�͑啶������������܂���B\n
�܂��A�s���I�h(.)�̒����e��u�����Ƃ͏o���܂���B \n
����̓����o�Q�Ɖ��Z�q�Ƃ��ăp�[�X����܂��B e�̑O��0��u���Ă��������B\n

\code
50.0e-5
15.5E+2
56.0e10
\endcode

\section suffix �T�t�B�b�N�X
�������e�����ƕ��������_�����e�����͎��̃T�t�B�b�N�X�����邱�Ƃ��o���܂��B\n
- f ���������_�����e�����Ƃ��Ĉ����� 
- F ���� 

\code
10.5f
255f
\endcode

���l�͂ǂ���ύX�s�\�I�u�W�F�N�g�ł��B \n
���̂��� += ���Z�q�Ȃǂ� a = a + b; �Ɠ����Ӗ��ƂȂ�܂��B\n
*/

/** \page string �����񃊃e����
������𐶐����鎮�̓_�u���N�H�[�g(")�ŕ����������ŋL�q���܂��B\n
\code
"String"
\endcode

�g�p�ł���G�X�P�[�v�V�[�P���X�͈ȉ��̂Ƃ���ł��B\n
- \\b �o�b�N�X�y�[�X 
- \\f ���y�[�W 
- \\n ���s 
- \\r ���A 
- \\t �����^�u 
- \\v �����^�u 
- \\\\ �o�b�N�X���b�V�� (�~�L��) 
- \\" ���p�� 

������͕ύX�s�\�I�u�W�F�N�g�ł��B \n
���̂��� a ~= b; �Ƃ����A��������Z�q�́A a = a ~ b; �Ɠ����Ӗ��ƂȂ�܂��B\n
\n
�����͈ꕶ���̕�������g���ĕ\���܂��B�������e�����͑��݂��܂���B\n

\section parcent %�L�@ 

���Ƀ_�u���R�[�e�[�V�������܂ޕ�������V���v���ɋL�q�ł���悤�ɁARuby�̂悤��%�L�@�����݂��܂��B\n
\code
%!This is a "pen"! // "This is a \"pen\"" �Ɠ�����
\endcode

!�̕����ɂ͍D����ASCII�̋L���������g�p�ł��܂��B\n
�n�܂�̋L�������Ƃ��āA[ ( < { �̂ǂꂩ���g�����ꍇ�A�I��̋L���ɑΉ����� ] > ) } ���g���܂��B\n
���ʂ��g�p�����ꍇ�A�����ł܂��������ʂ�����ƃl�X�g���܂��B\n

\code
%[ai[u]eo] // "ai[u]eo" �Ɠ�����
\endcode

�܂��A%�L�@�ł́A%�Ǝn�܂�̋L�������̊Ԃ̕����ɂ���ē��ʂȈӖ����t�^����܂��B\n
- f �t�H�[�}�b�g������ 
- t get text������ 

\subsection �t�H�[�}�b�g������ 
%�̌�� f ������ƁA����̓t�H�[�}�b�g������ƂȂ�܂��B\n

\code
format_object: %f!This %s a %s.!;
// format_object�͓�̒l���󂯎��֐��ƂȂ�

format_object("is", "pen").p; // This is a pen. 
\endcode

Python�̂悤�ɁA%(name)s�Ƃ������ɋL�q���邱�ƂŁA���O�t���ɂ��邱�Ƃ��o���܂��B\n
\code
format_object: %f[x=%(x)d, y=%(y)d];
format_object(y: 10, x: 20).p; // x=20, y=10
\endcode

\subsection text get text������ 
%�̌�� t ������ƁA�����get text������ƂȂ�܂��B\n

*/


/** \page array_map

\section secarray �z�񐶐��� 
�z��𐶐����鎮�͎��̂悤�ɋL�q���܂��B\n
\code
[]
[0, 1, 2]
["str", 5, 5.6, ]
\endcode
�J���}�ɋ�؂�ꂽ�l��v�f�Ƃ����z��I�u�W�F�N�g�𐶐����܂��B \n
�z��̗v�f�͂ǂ�ȃf�[�^�����݂��Ă����܂��܂���B \n
�Ō�̃J���}�͕t���Ă��t���Ȃ��Ă����܂��܂���B\n

\section secmap �A�z�z�񐶐��� 
�A�z�z��𐶐����鎮�͎��̂悤�ɋL�q���܂��B\n
\code
[:]
["key":"value", 5:100]
["one":1, "two":2, ]
\endcode
�L�[�ƒl��:�ŋ�؂������̂��J���}(,)��؂�ɂ���ƘA�z�z��I�u�W�F�N�g�̐����ƂȂ�܂��B\n 
�Ō�̃J���}�͕t���Ă��t���Ȃ��Ă����܂��܂���B\n
\n
�z��A�A�z�z��͂ǂ���ύX�\�I�u�W�F�N�g�ł��B \n
���̂��� += ���Z�q�Ȃǂ�a��j��I�ɕύX���܂��B\n
*/

/** \page fun �֐�������
�֐��𐶐����鎮�͎��̂悤�ɋL�q���܂��B\n
\code
foo: fun(name1, name2){    
    return name1 + name2;
}
foo(10, 20).p; //=> 30
\endcode

fun()�̌���u���b�N�ł͂Ȃ������L�q�����ꍇ�A�����I�ɂ��̎��̌��ʂ�Ԃ��֐��ƂȂ�܂��B\n
\code
foo: fun(name1, name2) name1 + name2;
foo(10, 20).p; //=> 30
\endcode

fun, method, fiber, class, singleton�ł́A�ϐ���`�Ɠ����ɐ������ŏ��������������ꍇ�A\n
\code
foo: fun(){}
bar: class{}
\endcode
���̂悤�ȋL�q���AC++�Ɏ����L�q�ƂȂ鎟�̂悤�ȏ�������������܂��B\n
\code
fun foo(){}
class bar{}
\endcode

2�̒l�̂����A�傫������Ԃ��֐�max�͎��̂悤�ɏ����܂��B\n
\code
fun max(a, b){
    if(a<b){
        return b;
    }else{
        return a;
    }
}

// �܂���
// fun max(a, b) a<b ? b : a;
\endcode

������������Ȃ��ꍇ�A()�͏ȗ����邱�Ƃ��\�ł��B\n
\code
foo: fun{
    "foo!".p;
}

fun bar{
    "bar!".p;
}
\endcode

\section arguments �f�t�H���g�����E���O�t������ 
������:�l �Ƃ��������Ńf�t�H���g�l�̎w�肪�o���܂��B\n
�f�t�H���g������t�����������͎����I�ɖ��O�t�������ƂȂ�A�Ăяo���Ƃ��Ɉ�����:�l�Ǝw�肵�܂��B\n
\code
foo foo_with_default_value(a: 0, b: 10){
    (a + b).p;
}

foo_with_default_value(); //=> 10
foo_with_default_value(a: 50); //=> 60
\endcode

\section argarg �ψ��� 
�֐��̈����̍Ō��...�Ƃ���ƁA�ψ��������֐���`�ƂȂ�܂��B\n
\code
foo foo(a, ...){
    a.p;
    ...[0].p; // �֐����� ... �́A���݂̊֐��̉ψ����I�u�W�F�N�g��\���Ă��܂��B
    ...["named"].p;
    bar(...); // bar�֐��ɉψ��������S�Ă�n��
}

foo(5, 10, 20, named:"test"); 
//=> a 5
//=> 0 10
//=> named test
\endcode

�ψ����I�u�W�F�N�g��Arguments�N���X�̃C���X�^���X�ł���AArguments�N���X�̃��\�b�h���ĂԂ��Ƃ��o���܂��B
\code
fun foo(...){
    // ���Ԏw�������S�ăv�����g����
    ....each_ordered{
        it.p;
    }
}
\endcode

�ψ�������x�ϐ��ɑ�����Ă��܂��ƁA������֐��̈����Ƃ��Ă����Arguments�I�u�W�F�N�g��n�������ƂɂȂ�A���҂�������ƂȂ�܂���B\n
Arguments�I�u�W�F�N�g���σp�����[�^�Ƃ��ēn�������ꍇ�A...args�̂悤�ɋL�q���܂��B\n
\code
fun foo(...){
    args: ...;
    bar(args); // bar(...) �Ɠ��삪�Ⴄ
    bar(...args); // bar(...) �Ɠ�������
}
\endcode

*/

/** \page lambda �����_������
lambda���͈����̎󂯎��������d����Ɠ������[���̊֐��������ł��B\n
\code
bar: |a, b| { return a + b; }
bar(10, 20); //=> 30

foo: |a, b| a + b;
foo(10, 20).p; //=> 30


// �n���ق������Ȃ��ꍇ�A���d����̂悤�ɁA�Ō�̑��l���W�J�����B
hoge: |a, b| a + b;
hoge( (5, 6) ).p; //=> 30 

// �n���ق��������ꍇ�A���d����̂悤�ɁA���l�ɂ܂Ƃ߂���B
bar: |a| a;
bar(7, 8).p; //=> (7, 8)
\endcode

lambda���͂��̓�����A�Ȃ�тɍ\���̓s����A�f�t�H���g�����L�[���[�h�����������Ƃ͏o���܂���B\n
*/

/** \page method ���\�b�h������
���\�b�h�𐶐����鎮�̏����́A�֐���������fun�̕�����method�ɕς��邾���ł��B\n
\code
m: method(name1, name2){
    return name1 + name2;
}
m(10, 20).p; //=> 30
\endcode

�N���X�̃X�R�[�v�̒��ł́A���\�b�h�̒�`�͂��Ȃ�ȗ��������L�q���\�ł��B\n
\code
class Foo{
    bar(a, b){
        
    }
    
    // ����͉��Ɠ�����
    
    // bar: method(a, b){
    //    
    // }
}
\endcode

fun�Ŋ֐��𐶐����邱�Ƃ̈Ⴂ�́A�[���ϐ�this�̈����������ł��B \n
fun�̏ꍇthis�́A���̊O���̃X�R�[�v��this�����̂܂܎g���܂��B \n
������method�̏ꍇ�Athis�������w�����́A�Ăяo�����Ō��肳��܂��B\n
method�� obj.foo() �`���ŌĂяo���ꂽ�Ƃ��Athis��obj�ƂȂ�܂��B \n
�����łȂ��A���� foo() �ƌĂ΂ꂽ�Ƃ��́A���̌Ăяo�����֐���this�����̂܂�this�Ƃ��Ďg���܂��B\n

\code
class Foo{
    return_fun{
        return fun{
            this.boo();
        }
    }

    return_method{
        return method{
            this.boo();
        }
    }

    boo{
        "boo!".p;
    }
}

// Foo�N���X���C���X�^���X��
foo: Foo();

// return_fun���\�b�h���Ԃ��֐���f�ɓ����
f: foo.return_fun();

// ������f���Ăяo���� boo! �ƕ\�������B
f();

// ���̂悤�ɁAfun�͊֐����������ꂽ�Ƃ���this���L�����Ă���̂ŁA
// method����Ԃ��ꂽ�ꍇ�ł��Athis���������I�u�W�F�N�g���w���Ă��܂��B


// method��Ԃ��ꍇ�ǂ��Ȃ邩

// return_method���\�b�h���Ԃ��֐���m�ɓ����
m: foo.return_method();

// ������f���Ăяo���Ɨ�O�����o�����B
f();

// �Ȃ��Ȃ�Amethod�͊֐������ꂽ�ꏊ��this���L�������A�Ăяo������this���g�p���邽�߂ł��B
// �g�b�v���x���ł�this�́Afilelocal�ł��̂ŁAfilelocal��this�Ƃ��ēn����Ă��邱�ƂɂȂ�܂��B
\endcode
*/

/** \page fiber �t�@�C�o�[������
�t�@�C�o�[�𐶐����鎮�̏����́A�֐���������fun�̕�����fiber�ɕς��邾���ł��B \n
�t�@�C�o�[��yield���g�����ƂŁA���s���ꎞ���f���āA�܂��r������Ď��s���o�������Ȋ֐��ł��B \n
\n
���̌���ł̓R���[�`���A�}�C�N���X���b�h�Ȃǂƌď̂���Ă�����̂ł��B\n
\code
fib: fiber(){
    1.p;
    yield;
    2.p;
}

fib(); //=> 1
fib(); //=> 2
\endcode

yield�Œl��Ԃ����Ƃ��o���܂��B
\code
fib: fiber(){
    yield 10;
    yield 20;
    yield 30;
}

fib().p; //=> 10
fib().p; //=> 20
fib().p; //=> 30
\endcode

fiber��this�̈�������fun�Ɠ����ł��B\n
\n
�܂��Afiber��Iterator�I�u�W�F�N�g�Ƃ��Ă������܂��B �܂�A�u���b�N���̓K�p���\�ł��B\n
\code
fib{ |val|
    val.p;
}
\endcode

�t�@�C�o�[�͐e�q�֌W�����m�ɑ��݂��Ă���A�X���b�h�̂悤�ȕ���̊֌W�������Ƃ͏o���Ȃ��A�Ǝv����������܂���B\n
�������A���̂悤�ȋ@�\�������΁A����̊֌W���������邱�Ƃ��\�ł��B\n
\code
class FiberScheduler{
    _fibers: [];

    step{
        for(i: 0; i<_fibers.length; ++i){
            it: _fibers[i];
            it();
            if(it.is_finished()){
                _fibers.erase(i);
                i--;
            }
        }
    }

    run{
        while(!_fibers.is_empty())
            step();
    }

    register(f){
        _fibers.push_back(f);
    }
}

fs: FiberScheduler();

fs.register(fiber{
    i: 0;
    while(i<10){
        i.p;
        i++;
        yield;
    }
});

fs.register(fiber{
    i: 0;
    while(i<10){
        i+5 .p;
        i++;
        yield;
    }
});

fs.run;
\endcode
*/

/** \page expr_sentence ����
���̌��;(�Z�~�R����)��u���ƕ��ƂȂ�܂��B\n

\code
100;
foo.bar;
println(10);
\endcode

�֐���������N���X�������ȂǁA��������}�ŏI��鎮�́A}�̌��;�����邩�̂悤�ɓ��삵�܂��B\n
���������āA}�ŏI��鎮�́A���̌��;�͕K�v����܂���B\n
���̑���A�E�Ɏ��𑱂��ď������Ƃ��o���܂���B\n
\code
foo: class{ 
    foo: fun(){
    
    }
}::foo(); // �R���p�C���G���[
\endcode
*/

/** \page class �N���X������
class�𐶐����鎮�ł��B\n
\code
// TestClass�Ƃ����ϐ��ɃN���X������
TestClass: class{
// �������class TestClass �Ƃ������������������
    
    // �C���X�^���X�ϐ��� _ (�A���_�[�X�R�A) �Ŏn�߂Ȃ���΂Ȃ�Ȃ��B
    _value; // �C���X�^���X�ϐ�_value��錾
    _test: 100; // ���̂悤�ȏ������̎d�����\�B

    // initialize�Ƃ������O�̃��\�b�h�̓C���X�^���X�������ɌĂяo�����
    initialize{ 
        _value = 0; // �C���X�^���X�ϐ�_value��0�ŏ�����
    }
    
    add(val){ // ���\�b�hadd���`
        _value += val; // �C���X�^���X�ϐ�_value��val�𑫂�
    }

    print{
        println(_value);
    }
}

// class�I�u�W�F�N�g�ɑ΂��A�֐��Ăяo�������g���Ƃ��̃C���X�^���X�𐶐��ł���
t: TestClass(); 
t.add(10);
t.print(); // 10���o�͂����
\endcode
    
�C���X�^���X�ϐ��͊O������Q�Ƃ��邱�Ƃ��o���܂���B\n
\code
t._value
\endcode
�Ƃ������͕s���ł��B\n

�܂��A�C���X�^���X�ϐ��́A����class�������̃X�R�[�v�̒��ɂ��郁�\�b�h���炵���A�N�Z�X���邱�Ƃ��o���܂���B \n
�܂�A�T�u�N���X�̒�����ł��p�����̃C���X�^���X�ϐ��͕s���ł��B\n
\n
�܂��AXtal�ł�class�̒�`��Ƀ��\�b�h��ǉ����邱�Ƃ��\�ł����A ���̒��ł��C���X�^���X�ϐ��ɐG�邱�Ƃ͏o���܂���B\n
\code
method TestClass::access(){
    _value = 10; // �G���[�I
}
\endcode
���̂��ߌp����ɓ����̃C���X�^���X�ϐ����������Ƃ��Ă��������邱�Ƃ͂���܂���B �����͊��S�ɕʂ̃��m�Ƃ��Ĉ����܂��B\n

\section �G��

�����o��`�̍ہA\n
�������Ȃ����܂���public�������public�����o\n
protected�������protected�����o\n
private��t�����private�����o�ƂȂ�܂��B\n
\code
class Foo{
  // public
  test0{}
  public test1{}

  // protected
  protected test2{}
    
  // private
  private test3{}
}
\endcode
public�͂ǂ�����ł��A�N�Z�X�ł��郁���o\n
protected�͎��g�̃N���X���܂��͌p����̃N���X�̃��\�b�h���炵���A�N�Z�X�ł��Ȃ������o\n
private�͎��g�̃N���X���炵���A�N�Z�X�ł��Ȃ������o�ł��B\n


\section propety �v���p�e�B

���������Ȃ����\�b�h�Ăяo����()���ȗ��ł��邽�߁A�l�̎擾�Ɋւ��Ă͂���()���Ȃ������ł��B
\code
obj.foo;
\endcode

�l�̐ݒ�� obj.foo = 100; �Ə����܂��B����� obj.set_foo(100) �̃V���^�b�N�X�V���K�[�ł��B \n
�܂�A���̂悤�Ƀ��\�b�h���`����΁A�v���p�e�B�̎������o���܂��B\n

class Foo{
    _hoge;

    hoge{
        return _hoge;
    }

    set_hoge(v){
        _hoge = v;
    }
}

foo: Foo();
foo.hoge = 100;
foo.hoge.p; //=> 100

foo.hoge += 10;
foo.hoge.p; //=> 110
\endcode

�P���ɃC���X�^���X�ϐ���Ԃ�����A�C���X�^���X�ϐ��ɐݒ肵���肷�邾���Ȃ�A���̂悤�ȊȈՓI�ȋL�q���o���܂��B\n
\code
class Foo{
    public _hoge;
}

foo: Foo();
foo.hoge = 100;
foo.hoge.p; //=> 100

foo.hoge += 10;
foo.hoge.p; //=> 110
\endcode
�C���X�^���X�ϐ���`���ŁA�G���̏C���q������ƁA�R���p�C����hoge���\�b�h�ƁAset_hoge���\�b�h���A���̉G���Œ�`���܂��B\n
getter��setter�ŉG����ς������ꍇ�A���\�b�h�������Œ�`���Ă��������B\n

\section adddef �N���X��`��̒ǉ������o��`
�N���X�̒�`��ł������o�̒ǉ���`���\�ł��B\n
\code
class Foo{}
Foo::hoge: 10;
\endcode
Foo�N���X��hoge�����o��ǉ���`���܂��B\n
���ɓ����̃����o������ꍇ�A�G���[�ƂȂ�܂��B\n

������œ��I�ɖ��O�����肷�邱�Ƃ��ł��܂��B\n
\code
name: "test"
Foo::("set_" ~ name): method(v){

}
\endcode

\section inherit �p��
class�̌p���͎��̂悤�ɏ����܂��B\n
\code
class A{
    foo{

    }
}

class B(A){
    bar{

    }
}

\section minherit ���d�p�� 
Xtal�ł�class�̑��d�p�����T�|�[�g���܂��B�J���}�ŋ�؂��Ďw�肵�܂��B\n
\code
class C(Foo, Bar){

}
\endcode
*/

/** \page singleton �V���O���g���N���X������
�V���O���g���N���X�Ƃ́A�B��̃C���X�^���X���������g�ƂȂ���ʂȃN���X�̂��Ƃł��B\n
���g���N���X�ł��邽�߁A�����o�̊֐��� object::member() �ł��Aobject.member �ł��Ăяo�����Ƃ��\�ł��B \n
\code
foo: singleton{
    bar{
        callee.p;
    }
}

(foo.class===foo).p; //=> true
foo::bar(); //=> foo::bar
foo.bar(); //=> foo::bar
\endcode
Xtal�ł́AC++�̖��O��ԂƓ����悤�ȗp�r�ɂ́A���̃V���O���g���N���X���g���܂��B\n
*/

/* \page assign �����
�ϐ��̎Q�Ɛ��ς���̂͑�������g���܂��B\n

\code
// ����:
ident = expr ; 

// ��:
name: "key";
name.p; //=> key
name = "test";
name.p; //=> test
\endcode

Xtal�ł͑���͕��ŁA�l��Ԃ��Ȃ����߁A\n
\code
if(name = 0){}
\endcode
�Ƃ����L�q�̓R���p�C���G���[�ƂȂ�܂��B\n

\section massign ���d����� 
Xtal�͑��d�ϐ�������T�|�[�g���܂��B
\code
a, b = 0, 1;
\endcode

���̂悤�ɋL�q����΁A�ϐ��̃X���b�v���ł��܂��B\n
\code
a, b = b, a;
\endcode
*/

/** \page op_assign ���Z�����
\section inc �C���N�������g�� �f�N�������g�� 
\code
i++;
++i;
\endcode
i���C���N�������g���܂��B\n
�C���N�������g���́A���̌`���̃V���^�b�N�X�V���K�[�ł��B\n
\code
i = i.op_inc();
\endcode

\section dec �f�N�������g�� 
\code
i--;
--i;
\endcode
i���f�N�������g���܂��B\n
�f�N�������g���́A���̌`���̃V���^�b�N�X�V���K�[�ł��B\n
\code
i = i.op_dec();
\endcode

\section add_assign ���Z����� 
\code
a += b
\endcode
a��b�����Z�������ʂ�a�ɑ�����܂��B\n
����́Aa = a.op_add_assign(b)�̏ȗ��`�ł��B\n

\section sub_assign ���Z����� 
\code
a -= b
\endcode
a����b�����Z�������ʂ�a�ɑ�����܂��B\n
����́Aa = a.op_sub_assign(b)�̏ȗ��`�ł��B\n

\section cat_assign �A������� 
\code
a ~= b
\endcode
a��b��A���������ʂ�a�ɑ�����܂��B\n
����́Aa = a.op_cat_assign(b)�̏ȗ��`�ł��B\n

\section mul_assign ��Z����� 
\code
a *= b
\endcode
a��b���|�����킹�܂��B\n
����́Aa = a.op_mul_assign(b)�̏ȗ��`�ł��B\n

\section div_assign ���Z����� 
\code
a /= b
\endcode
a��b�ŏ��Z�������ʂ�a�ɑ�����܂��B\n
����́Aa = a.op_div_assign(b)�̏ȗ��`�ł��B\n

\section mod_assign ��]����� 
\code
a %= b
\endcode
a��b�Ŋ��������܂��a�ɑ�����܂��B\n
����́Aa = a.op_mod_assign(b)�̏ȗ��`�ł��B\n

\section and_assign bitwise and����� 
\code
a &= b
\endcode
a��b��bitwise and�������ʂ�a�ɑ�����܂��B\n
����́Aa = a.op_and_assign(b)�̏ȗ��`�ł��B\n

\section or_assign bitwise or����� 
\code
a |= b
\endcode
a��b��bitwise or�������ʂ�a�ɑ�����܂��B\n
����́Aa = a.op_or_assign(b)�̏ȗ��`�ł��B\n

\section xor_assign bitwise xor����� 
\code
a ^= b
\endcode
a��b��bitwise xor�������ʂ�a�ɑ�����܂��B\n
����́Aa = a.op_xor_assign(b)�̏ȗ��`�ł��B\n

\section shl_assign ���V�t�g����� 
\code
a <<= b
\endcode
a��b�r�b�g���V�t�g�������ʂ�a�ɑ�����܂��B\n
����́Aa = a.op_shl_assign(b)�̏ȗ��`�ł��B\n

\section shr_assign �Z�p�E�V�t�g����� 
\code
a >>= b
\endcode
a��b�r�b�g�E�V�t�g�������ʂ�a�ɑ�����܂��B\n
����́Aa = a.op_shr_assign(b)�̏ȗ��`�ł��B\n

\section ushr_assign �_���I�E�V�t�g����� 
\code
a >>>= b
\endcode
a��b�r�b�g�_���I�E�V�t�g�������ʂ�a�ɑ�����܂��B\n
����́Aa = a.op_ushr_assign(b)�̏ȗ��`�ł��B\n

*/

/** \page overloadable_operator �Ē�`�\�ȉ��Z�q�̈ꗗ

\section secassign ���Z�q�n
<TABLE>
<TR><TD>���Z�q</TD><TD>�Ӗ�</TD></TR>
<TR><TD>+a</TD><TD>a.op_pos()</TD></TR>
<TR><TD>-a</TD><TD>a.op_neg()</TD></TR>
<TR><TD>~a</TD><TD>a.op_com()</TD></TR>
<TR><TD>a[]</TD><TD>a.op_to_array()</TD></TR>
<TR><TD>a[:]</TD><TD>a.op_to_map()</TD></TR>
<TR><TD>a + b</TD><TD>a.op_add(b)</TD></TR>
<TR><TD>a - b</TD><TD>a.op_sub(b)</TD></TR>
<TR><TD>a ~ b</TD><TD>a.op_cat(b)</TD></TR>
<TR><TD>a * b</TD><TD>a.op_mul(b)</TD></TR>
<TR><TD>a / b</TD><TD>a.op_div(b)</TD></TR>
<TR><TD>a % b</TD><TD>a.op_mod(b)</TD></TR>
<TR><TD>a & b</TD><TD>a.op_and(b)</TD></TR>
<TR><TD>a | b</TD><TD>a.op_or(b)</TD></TR>
<TR><TD>a ^ b</TD><TD>a.op_xor(b)</TD></TR>
<TR><TD>a << b</TD><TD>a.op_shl(b)</TD></TR>
<TR><TD>a >> b</TD><TD>a.op_shr(b)</TD></TR>
<TR><TD>a >>> b</TD><TD>a.op_ushr(b)</TD></TR>
<TR><TD>a[b]</TD><TD>a.op_at(b)</TD></TR>
<TR><TD>a .. b</TD><TD>!a.op_range(b, Range::CLOSED)</TD></TR>
<TR><TD>a ..< b</TD><TD>!a.op_range(b, Range::LEFT_CLOSED_RIGHT_OPEN)</TD></TR>
<TR><TD>a <.. b</TD><TD>!a.op_range(b, Range::LEFT_OPEN_RIGHT_CLOSED)</TD></TR>
<TR><TD>a <..< b</TD><TD>!a.op_range(b, Range::OPEN)</TD></TR>
<TR><TD>a == b</TD><TD>a.op_eq(b)</TD></TR>
<TR><TD>a != b</TD><TD>!a.op_eq(b)</TD></TR>
<TR><TD>a < b</TD><TD>a.op_lt(b)</TD></TR>
<TR><TD>a > b</TD><TD>b.op_lt(a)</TD></TR>
<TR><TD>a <= b</TD><TD>!b.op_lt(a)</TD></TR>
<TR><TD>a >= b</TD><TD>!a.op_lt(b)</TD></TR>
<TR><TD>a in b</TD><TD>a.op_in(b)</TD></TR>
<TR><TD>a !in b</TD><TD>!a.op_in(b)</TD></TR>
</TABLE>

\section secassign ������Z���n
<TABLE>
<TR><TD>���Z�q</TD><TD>�Ӗ�</TD></TR>
<TR><TD>i++;</TD><TD>i = i.op_inc();</TD></TR>
<TR><TD>i--;</TD><TD>i = i.op_dec();</TD></TR>
<TR><TD>a[b] += c;</TD><TD>a = a.op_set_at(b, c);</TD></TR>
<TR><TD>a += b;</TD><TD>a = a.op_add_assign(b);</TD></TR>
<TR><TD>a -= b;</TD><TD>a = a.op_sub_assign(b);</TD></TR>
<TR><TD>a ~= b;</TD><TD>a = a.op_cat_assign(b);</TD></TR>
<TR><TD>a *= b;</TD><TD>a = a.op_mul_assign(b);</TD></TR>
<TR><TD>a /= b;</TD><TD>a = a.op_div_assign(b);</TD></TR>
<TR><TD>a %= b;</TD><TD>a = a.op_mod_assign(b);</TD></TR>
<TR><TD>a &= b;</TD><TD>a = a.op_and_assign(b);</TD></TR>
<TR><TD>a |= b;</TD><TD>a = a.op_or_assign(b);</TD></TR>
<TR><TD>a ^= b;</TD><TD>a = a.op_xor_assign(b);</TD></TR>
<TR><TD>a <<= b;</TD><TD>a = a.op_shl_assign(b);</TD></TR>
<TR><TD>a >>= b;</TD><TD>a = a.op_shr_assign(b);</TD></TR>
<TR><TD>a >>>= b;</TD><TD>a = a.op_ushr_assign(b);</TD></TR>
</TABLE>

*/

/** \page branch ���򐧌䕶
\section if if��
\code
if(a.is_empty){
    a.p;
}

if(i < 5){
    "true".p;
}
else{
    "false".p;
}
\endcode

�������̒��ŕϐ����`���邱�Ƃ��o���܂��B
\code
if(val: foo()){
    val.p;
}
\endcode

\section switch switch��
switch��C����Ə����\�����قȂ�܂��B
xtal��switch�͎��̂悤�Ȍ`�ƂȂ�܂��B

\code
switch(value){
    // value��"test"�Ɠ������ꍇ�Ɏ��s�����
    case("test"){
        "test".p; 
    }

    // value��10�Ɠ������A�܂���20�Ɠ������ꍇ�Ɏ��s�����
    case(10, 20){
        10.p;
    }
    
    // �ǂ�case�Ƃ��������Ȃ��ꍇ�Ɏ��s�����
    default{
        "default".p;
    }
}
\endcode
���̂悤��C����ł�case�������ucase 10:�v�Ƃ������ɂȂ�܂����AXtal�ł́ucase(10){}�v�ƂȂ�܂��B\n
�܂�switch����break��switch�𔲂��o���Ӗ��Ƃ͂Ȃ�܂���B\n
\n
case���Ɏw�肵���I�u�W�F�N�g�͓��ꉉ�Z�q�Ŕ�r����܂��B\n

\code
while(true){
    switch(value){
        case("test"){
            break; // �O����while�𔲂��o��
        }
    }
}
\endcode

*/

/** \page loop �J��Ԃ����䕶
\section for for��
\code
for(i: 0; i<10; ++i){
    println(i);
}
\endcode

\section while while��
i: 0;
while(i < 5){
    i++;
}

while����if���Ɠ����悤�ɏ������̒��ŕϐ����`���邱�Ƃ��o���܂��B
\code
while(i: foo()){
    println(i);
}
\endcode

\section block �u���b�N��
\code 
ary: [5, 4, 3];
ary.each{ |value|
    println(value);
}
\endcode

ary.each�͎��g�̓��e�𔽕�����Iterator�I�u�W�F�N�g��Ԃ����\�b�h�ł��B\n
Iterator�I�u�W�F�N�g�ɑ΂��u���b�N{}��K�p����ƃu���b�N���ƂȂ�܂��B\n
{ �̌�� |value, value2| �Ə����ƁAIterator�����������v�f�����X�ɑ������܂��B}\n
\n
�u���b�N���̒��ł́A�ÖٓI�� it �Ƃ������O�̕ϐ�����`�����̂ŁA������g�����Ƃ��o���܂��B\n
\code
ary: [5, 4, 3];
ary.each{
    println(it);
}
\endcode

�u���b�N���͎��̂悤�ɏ����̂Ɠ��`�ł��B\n
\code
ary: [5, 4, 3];
_has_next, value: ary.each.iter_first();
try{
    while(_has_next){
        println(value);
        _has_next, value = _has_next.iter_next();
    }
}
finally{
    _has_next.?iter_break();
}
\endcode

�܂��A�z��̂悤��block_first���\�b�h�����ꍇ�Aeach��Iterator���擾����܂ł��Ȃ��u���b�N���K�p�ł��܂��B�܂�\n
\code
ary: [5, 4, 3];
ary.each{
    it.p;
}
\endcode
�͎��̂悤�ɏ����Ă�OK�ł��B\n
\code
ary: [5, 4, 3];
ary{ 
    it.p;
}
\endcode


\section else else��
�e���[�v���ɂ�else�߂����邱�Ƃ��o���܂��B\n
else�߂́A����������x���^�ƂȂ�Ȃ������ꍇ�ɒʂ�܂��B\n
\code
for(i: 10; i<5; i++){

}
else{
    // ���i<5�͈�x���^�ƂȂ�Ȃ��̂ŁA������ʂ�
}
\endcode

\section nibreak nobreak��
�e���[�v���ɂ�nobreak�߂����邱�Ƃ��o���܂��B\n
nobreak�߂́Abreak�Œ��~���Ȃ������ꍇ�ɒʂ�܂��B\n
����������x���^�ƂȂ�Ȃ��ꍇ�����l�ɒʂ�܂��B\n
\code
for(i: 0; i<10; ++i){
    if(foo())
        break;
}
nobreak{
    // foo()��true��Ԃ��Ȃ���΁A������ʂ�

}
\endcode
    
else�߂�nobreak�߂͂ǂ��炩��������邱�Ƃ��\�ł��B\n


\section break break��
���[�v������r���ŒE�o�ł��܂��B\n
\code
while(true){
    break; // ���f���Ĕ�����
}
\endcode

���x�����g���A�����̃��[�v�������C�ɒE�o���邱�Ƃ��ł��܂��B\n
\code
outer: while(true){
    array.each{
        break outer; // �O���̃��[�v���甲���o���B
    }
}
\endcode

\section continue continue��
���[�v���̎c��̕������X�L�b�v���܂��B\n
\code
for(i: 0; i<10; i++){
    if(i%2 == 1){
        continue;
    }
    i.p;
}
\endcode
��̗�͊�������o�͂��܂��B\n
    \n
break�Ɠ����悤�ɁA���x���𗘗p���āA����̃��[�v���ɑ΂��ď������邱�Ƃ��o���܂��B\n
\code
outer: for(i: 0; i<10; i++){
    for(j: 0; j<10; j++){
        if(i%2 == 1){
            continue outer; 
        }
        i.p;
    }
}
\endcode
    
\section first_step first_step
�e���[�v���̓����ł́Afirst_step�Ƃ����ϐ�����`����܂��B\n
first_step�͍ŏ��̃X�e�b�v����true�A����ȍ~�̃X�e�b�v�ł�false�ƂȂ�܂��B\n
\code
for(i: 0; i<3; ++i){
    if(!first_step){
        print(",");
    }
    print(i);
}
//=> 0, 1, 2
\endcode
*/
    
/** \page basic_operator ��{�I�ȉ��Z�q

\section pos �P��+���Z�q
\code
+a
\endcode
����́Aa.op_pos()�̏ȗ��`�ł��B\n

\section pos �P��-���Z�q
\code
-a
\endcode
�����𔽓]���܂��B\n
����́Aa.op_neg()�̏ȗ��`�ł��B\n

\section pos �P��~���Z�q
\code
-a
\endcode
�r�b�g�𔽓]���܂��B\n
����́Aa.op_com()�̏ȗ��`�ł��B\n

\section add ���Z���Z�q
\code
a + b
\endcode
a��b�����Z���܂��B\n
����́Aa.op_add(b)�̏ȗ��`�ł��B\n

\section sub ���Z���Z�q
\code
a - b
\endcode
a����b�����Z���܂��B\n
����́Aa.op_sub(b)�̏ȗ��`�ł��B\n

\section cat �A�����Z�q
\code
a ~ b
\endcode
a��b��A�����܂��B\n
����́Aa.op_cat(b)�̏ȗ��`�ł��B\n

\section mul ��Z���Z�q
\code
a * b
\endcode
a��b���|�����킹�܂��B\n
����́Aa.op_mul(b)�̏ȗ��`�ł��B\n

\section div ���Z���Z�q
\code
a / b
\endcode
a��b�ŏ��Z���܂��B\n
����́Aa.op_div(b)�̏ȗ��`�ł��B\n

\section mod ��]���Z�q
\code
a % b
\endcode
a��b�Ŋ��������܂��a�ɑ�����܂��B\n
����́Aa.op_mod(b)�̏ȗ��`�ł��B\n

\section and bitwise and���Z�q
\code
a & b
\endcode
a��b��bitwise and���܂��B\n
����́Aa.op_and(b)�̏ȗ��`�ł��B\n

\section or bitwise or���Z�q
\code
a | b
\endcode
a��b��bitwise or���܂��B\n
����́Aa.op_or(b)�̏ȗ��`�ł��B\n

\section xor bitwise xor���Z�q
\code
a ^ b
\endcode
a��b��bitwise xor���܂��B\n
����́Aa.op_xor(b)�̏ȗ��`�ł��B\n

\section shl ���V�t�g���Z�q
\code
a << b
\endcode
a��b�r�b�g���V�t�g���܂��B\n
����́Aa.op_shl(b)�̏ȗ��`�ł��B\n

\section shr �E�V�t�g���Z�q
\code
a >> b
\endcode
a��b�r�b�g�E�V�t�g���܂��B\n
����́Aa.op_shr(b)�̏ȗ��`�ł��B\n

\section ushr �_���I�E�V�t�g���Z�q
\code
a >>> b
\endcode
a��b�r�b�g�_���I�E�V�t�g���܂��B\n
����́Aa.op_ushr(b)�̏ȗ��`�ł��B\n
*/

    
/** \page cmp_operator ��r���Z�q
\section pos �P��!���Z�q
\code
-a
\endcode
�^�l��false�ɁA�U�l��true�ɕϊ����܂��B\n

\section eq ==���Z�q
\code
a == b
\endcode
a��b�������������ׂ܂��B\n
����́Aa.op_eq(b)�̏ȗ��`�ł��B\n
    
\section ne !=���Z�q
\code
a != b
\endcode
==���Z�q�̔ے�ł��B\n
����́A!a.op_eq(b)�̏ȗ��`�ł��B\n

\section lt <���Z�q
\code
a < b
\endcode
a��b���������ׂ܂��B\n
����́Aa.op_lt(b)�̏ȗ��`�ł��B\n

\section gt >���Z�q
\code
a > b
\endcode
a���b���傫���l�����ׂ܂��B\n
����́Ab.op_lt(a)�̏ȗ��`�ł��B\n

\section gt <=���Z�q
\code
a <= b
\endcode
a��b�ȉ������ׂ܂��B\n
����́A!b.op_lt(a)�̏ȗ��`�ł��B\n
    
\section gt >=���Z�q
\code
a >= b
\endcode
a��b�ȏォ���ׂ܂��B\n
����́A!a.op_lt(b)�̏ȗ��`�ł��B\n

\section eql ===���Z�q
\code
a === b
\endcode
a��b������̃I�u�W�F�N�g�ł��邩���ׂ܂��B\n
    
\section neq !==���Z�q
\code
a !== b
\endcode
===���Z�q�̔ے�ł��B\n
    
\section is is���Z�q
\code
a is b
\endcode
a�̂�b�̃N���X�̃C���X�^���X�����ׂ܂��B\n
    
\section nis !is���Z�q
\code
a !is b
\endcode
is���Z�q�̔ے�ł��B\n
    
\section in in���Z�q
\code
a in b
\endcode
b��a���܂�ł��邩���ׂ܂��B\n
�����a.op_in(b)�̏ȗ��n�ł��B
    
\section nin !in���Z�q
\code
a !in b
\endcode
in���Z�q�̔ے�ł��B\n
�����!a.op_in(b)�̏ȗ��n�ł��B

*/

/** \page call �֐��Ăяo�����Z�q
\code
foo(a, b, c)
\endcode
�֐��Ăяo����foo.op_call(a, b, c)�̏ȗ��`�ł��B\n

�֐��Ăяo���͈����������Ƃ��Ă��A���ʂ��ȗ����邱�Ƃ͂ł��܂���B \n
���ʂ��ȗ������ꍇ�A�P�Ȃ�ϐ��̎Q�ƂɂȂ�܂��B\n

Xtal�̓L�[���[�h�������Ή����Ă��܂��B
\code
foo(key: "value", key2: 100);
\endcode
*/
    
/** \page method_call ���\�b�h�Ăяo�����Z�q
\code
obj.member();
obj.member(100);
\endcode
�����̓n�����́A�֐��Ăяo�����Z�q�Ɠ����ł��B\n
\n
���\�b�h�Ăяo�����Z�q�́A�v���p�e�B�T�|�[�g�̂��߁A���\�b�h�Ăяo���͈����������Ƃ��A���ʂ��ȗ����邱�Ƃ��ł��܂��B\n 
\code
obj.member;
\endcode
�v���p�e�B�̒l�ݒ�̕��͎��̂悤�ɏ����܂��B\n
\code
obj.member = 100;
\endcode
����� obj.set_member(100); �̂悤�ɃR���p�C������܂��B\n

���\�b�h�Ăяo������.��.?�Ƃ���ƁA���̃��\�b�h�����݂���ꍇ�����Ăяo���Ƃ�������ɂȂ�܂��B \n
�������݂��Ȃ������ꍇ�A���̒l��undefined�I�u�W�F�N�g�ƂȂ�܂��B\n
\code
obj.?member;
obj.?member(100);
\endcode
    
\section dynamic_method_call ���I���\�b�h�Ăяo��
\code
obj.("test" ~ "2");
name: "aaaa";
obj.(name)(100);
ojb.?("key");
\endcode
���ʎq�̕����𓮓I�ȕ�����ɂĎw�肷�邱�Ƃ��ł��܂��B\n
*/

/** \page refmember �����o�擾���Z�q
\code
class Foo{
    roo: 100;
}

Foo::roo.p; //=> 100
\endcode

�N���X�I�u�W�F�N�g�ɒ�`����Ă��郁���o�����o�����Z�q�ł��B\n
::? �̕����g���ƁA���̃����o�����݂��Ȃ��ꍇ�Aundefined�I�u�W�F�N�g���Ԃ鉉�Z�q�ł��B\n
\code
if(Foo::?hoge === undefined){
  // Foo::hoge�������Ȃ炱����ʂ�
}else{
  // Foo::hoge������Ȃ炱����ʂ�
}
\endcode

\section dynamic_refmeber ���I�����o�擾���Z�q
\code
class Foo{
    roo: 100;
}

Foo::("ro" ~ "o").p; //=>100
Foo::?("key").p; //=> undefined
\endcode
���ʎq�̕����𓮓I�Ɍ��肵�܂��B\n
*/

/** \page secondary_key �Z�J���_���L�[
�����o�̒�`�A�擾�ȂǂɁA�C�ӂ̃I�u�W�F�N�g���Z�J���_���L�[�Ƃ��Ďg�����Ƃ��ł��܂��B\n
\code
class Foo{
    // ���ʎqhoge���v���C�}���L�[
    // ����555���Z�J���_���L�[��
    bar#555: 100;
    
    // ���ʎqhoge���v���C�}���L�[
    // �N���X�I�u�W�F�N�gString���Z�J���_���L�[��
    hoge#String{
        "hoge#String".p;
    }
}

Foo::bar#555.p; //=> 100

f: Foo();
f.hoge#String; //=> hoge#String
\endcode

�N���X�I�u�W�F�N�g���Z�J���_���L�[�ɂ����ꍇ�A���̃N���X�̃T�u�N���X�ł��������q�b�g���܂��B\n
\code
class A{}
class B(A){}

class Foo{
    bar#A{
        "bar#A".p;
    }
}

f: Foo();
f.bar#B; //=> "bar#A"
\endcode
*/
    
/** \page etc_operator ���̑��̉��Z�q

\section �v�f�擾���Z�q
\code
a[index]
\endcode
index�ɑΉ�����v�f��Ԃ��܂��B\n
����́Aa.op_at(index)�̏ȗ��`�ł��B\n

\section �v�f�ݒ艉�Z�q
\code
a[index] = value
\endcode
index�ɑΉ�����v�f��ݒ肵�܂��B\n
����́Aa.op_set_at(index, value)�̏ȗ��`�ł��B\n

\section �z�񉻉��Z�q
\code
a[]
\endcode
a��z��ɓZ�߂����ʂ�Ԃ��܂��B\n
����́Aa.op_to_array�̏ȗ��`�ł��B\n

\section �A�z�z�񉻉��Z�q
\code 
a[:]
\endcode
a��A�z�z��ɓZ�߂����ʂ�Ԃ��܂��B\n
����́Aa.op_to_map�̏ȗ��`�ł��B\n

\section oror �_���a���Z�q
\code
a || b
\endcode
a��]�����āA���ꂪ�U�łȂ��Ȃ獶�ӂ̒l��Ԃ��܂��B �U�Ȃ�E�ӂ�Ԃ��܂��B\n

\section andand �_���ω��Z�q 
\code
a && b
\endcode
a��]�����āA���ꂪ�U�łȂ��Ȃ�A�E�ӂ�Ԃ��܂��B �U�Ȃ炻�̂܂܍��ӂ�Ԃ��܂��B\n

\section _3term �O�����Z�q
�l��Ԃ�if���ł��B\n
\code
a<10 ? 1: 2
\endcode

\section once once���Z�q 
once���Z�q�́A���̕]�����ŏ��̈�x�������鉉�Z�q�ł��B\n
\code
fun foo(){
    return once [0, 1, 2, 3];
}
\endcode
����once��t���Ȃ��ꍇ�A���̊֐��͌Ăяo�����тɈႤ�z��I�u�W�F�N�g�𐶐����ĕԂ��܂����A once�ň�x�����]�����Ȃ��Ƃ��Ă��邽�߁A���x�Ăяo���Ă������z��I�u�W�F�N�g��Ԃ��܂��B\n

\section range �͈͐������Z�q
�͈̓I�u�W�F�N�g�𐶐����܂��B\n
\code
a .. b  // �͈�[expr, expr]
a ..< b  // �͈�[expr, expr)
a <.. b  // �͈�(expr, expr]
a <..< b  // �͈�(expr, expr)
\endcode
����́Aa.op_range(b, kind)�̏ȗ��n�ł��B\n
���ӂ̎��������̏ꍇ�AIntRange�N���X�̃I�u�W�F�N�g���A\n
���������_���̏ꍇ�AFloatRange�N���X�̃I�u�W�F�N�g���A\n
����1�̕�����̏ꍇ�AChRange�N���X�̃I�u�W�F�N�g����������܂��B\n
*/

/** \page operator_priority ���Z�q�̗D�揇��
- �D  ��  ���Z�q  �Ӗ� 
- 15  ��  a.b  �I�u�W�F�N�g�����o�A�N�Z�X 
- 15  ��  a[b]  �z��v�f�A�N�Z�X 
- 15  ��  a()  �֐��Ăяo�� 
- 15  ��  a..b  �͈͉��Z�q 
- 15  ��  a[]  �z�񉻉��Z�q
- 15  ��  a[:]  �A�z�z�񉻉��Z�q
- 14  �E  +a   
- 14  �E  -a  �������] 
- 14  �E  ~a  �r�b�g�P�ʂ̔��] 
- 14  �E  !a  �_���ے� 
- 13  ��  a*b  ��Z 
- 13  ��  a/b  ���Z 
- 13  ��  a%b  �]�� 
- 12  ��  a+b  ���Z 
- 12  ��  a-b  ���Z 
- 11  ��  a<<b  ���V�t�g 
- 11  ��  a>>b  �����t�E�V�t�g 
- 11  ��  a>>>b  �������E�V�t�g 
- 10  ��  a==b  ������ 
- 10  ��  a!=b  �������Ȃ� 
- 10  ��  a===b  ���� 
- 10  ��  a!==b  ����ł͂Ȃ� 
- 10  ��  a is b  a��b�N���X�̃C���X�^���X�� 
- 10  ��  a !is b  a��b�N���X�̃C���X�^���X�ł͂Ȃ��� 
- 10  ��  a<b  ��菬���� 
- 10  ��  a>b  ���傫�� 
- 10  ��  a<=b  ��菬������������ 
- 10  ��  a>=b  ���傫���������� 
- 09  ��  a&b  �r�b�g�P�ʂ̘_���� 
- 08  ��  a^b  �r�b�g�P�ʂ̔r���I�_���a 
- 07  ��  a|b  �r�b�g�P�ʂ̘_���a 
- 06  ��  a&&b  �_���� 
- 05  ��  a||b  �_���a 
- 00  �E  once a  �ŏ��̈�x�����]�����Ȃ� 

Xtal�͗D�揇�ʂƋ󔒂��}�b�`���Ă��Ȃ��ꍇ�A�R���p�C���G���[�Ƃ��܂��B\n
\code
10 + 5*6 // ok
10+5*6 // ok
10+5 * 6 // error +���*�̕����D�揇�ʂ������̂ɁA�����ڂ͂����Ȃ��Ă��Ȃ��B
\endcode

\subsection sppri ���ʂȗD�揇��0�̉��Z�q 
once�Ȃǂ̗D�揇��0�̉��Z�q���������ċL�q�����ꍇ�A �D�揇�ʂ���ԍ����Ȃ�A�Ƃ������[�����K�p����܂��B\n
�Ⴆ��\n
\code
once(10)+10
\endcode
��\n
\code
((once 10) + 10)
\endcode
�ƂȂ�܂��B\n
\code
once (10)+10
\endcode
�Ɨ�����\n
\code
(once (10 + 10))
\endcode
�ƂȂ�܂��B\n
*/
    
    
/** \page except ��O���䕶
\section try_catch try catch��
\code
try{
    hoge();
    // ...
}
catch(e){ // try�߂ŗ�O�����������ꍇ�Ɏ��s������
   // �ϐ�e�ɗ�O�I�u�W�F�N�g����������
}
\endcode

try�߂̒��ő��o���ꂽ��O��߂܂���\���ł��B \n

\section try_finally try finally��
\code
try{

}
finally{

}
\endcode
try�߂��甲���o�����Ƃ��ɕK��finally�߂ɏ����ꂽ�߂����s����\���ł��B\n
����͕��ʂ�{}�̒��𔲂��o�����Ƃ��͂������A\n
break�Acontinue�Areturn�Athrow�ȂǂŔ����o�����Ƃ��ɂ����s����܂��B\n

\section try try catch finally�� 
\code
try{

}
catch(e){

}
finally{

}
\endcode
try catch����try finally���̕������ł��B\n

\section throw throw��
\code
throw "error";
\endcode
��O�𑗏o���܂��B\n
��������I�u�W�F�N�g�́A�����񉻉\�ȃI�u�W�F�N�g���AExcetion�N���X�����̃T�u�N���X�̃C���X�^���X�I�u�W�F�N�g�ł���K�v������܂��B\n
*/
