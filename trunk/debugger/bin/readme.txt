���̃v���O������Qt4��LGPL�ł��g�p���Ă��܂��B
http://qt.nokia.com/title-jp?set_language=ja&cl=ja
���o�[�X�G���W�j�A�����O�������܂��B


/////////////////////////
�g�p���@

debugger.exe�𗧂��グ�܂��B
���̃f�o�b�K��TCP�ŃN���C�A���g�ƃf�o�b�O��������肵�܂��̂�
�l�b�g���[�N�g�p�̌x�����o��ꍇ�͋����Ă��������B


�E���j���[��File -> New Project�ŐV�����v���W�F�N�g���쐬���܂��B

�E����Project�Ƃ����c���[�r���[�ɃG�N�X�v���[���[����t�@�C�����h���b�v�A���h�h���b�O���Ēǉ����܂��B

�EProject�̃c���[�r���[�̃t�@�C�������_�u���N���b�N����ƁA���̃t�@�C����^�񒆂̃R�[�h�G�f�B�^�����ŎQ�Ƃł��܂��B
�@�ȒP�ȕҏW���ł��܂����A�F�Â��������ȊO�̓��������x���ł��B
�@���̃R�[�h�G�f�B�^�̍s�ԍ��̍��̕������N���b�N����ƁA�u���[�N�|�C���g��ݒu�ł��܂��B

�E�E��Expr�c���[�r���[�ŕ]�������������L�q�ł��܂��B

�E�E��CallStack�c���[�r���[�Ŋ֐��Ăяo���������Q�Ƃł��܂��B


/////////////////////////
�N���C�A���g���A�܂�f�o�b�O�������v���O�������̏���

#include "../src/xtal/xtal.h"
#include "../src/xtal/xtal_macro.h"

#include "../src/xtal/xtal_lib/xtal_winthread.h"
#include "../src/xtal/xtal_lib/xtal_cstdiostream.h"
#include "../src/xtal/xtal_lib/xtal_winfilesystem.h"
#include "../src/xtal/xtal_lib/xtal_chcode.h"
#include "../src/xtal/xtal_lib/xtal_errormessage.h"
#include "../src/xtal/xtal_lib/xtal_debugger.h" // �f�o�b�K���C�u����

int main(int argc, char** argv){
	CStdioStdStreamLib cstd_std_stream_lib;
	WinThreadLib win_thread_lib;
	WinFilesystemLib win_filesystem_lib;
	SJISChCodeLib sjis_ch_code_lib;

	Setting setting;
	setting.thread_lib = &win_thread_lib;
	setting.std_stream_lib = &cstd_std_stream_lib;
	setting.filesystem_lib = &win_filesystem_lib;
	setting.ch_code_lib = &sjis_ch_code_lib;

	initialize(setting);

	{
		Debugger debugger; // �f�o�b�K�Ƃ��Ƃ肷��N���X
		debugger.attach(xnew<DebugStream>("127.0.0.1", "13245")); // �ڑ�����

		require("test"); // �f�o�b�K��text.xtal���o�^����Ă���Ȃ�΁A������R���p�C�����Ď��s����
		// �o�^����Ă��Ȃ���΁Aload�Ɠ�������������

		// ��͒���I��debugger.update();���Ăяo������
		// �Q�[���ł���Ζ��t���[���Ăяo������
	}
		
	uninitialize();

	return 0
}