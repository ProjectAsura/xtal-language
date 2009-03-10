
#pragma once

namespace xtal{

inline void bind_error_message(){
	const char_t* messages[] = {
		XTAL_STRING("Xtal Compile Error 1001"), XTAL_STRING("�\���G���[�ł��B"),
		XTAL_STRING("Xtal Compile Error 1002"), XTAL_STRING("�\�����ʕ��� '%(char)s' �����o����܂����B"),
		XTAL_STRING("Xtal Compile Error 1003"), XTAL_STRING("';' ������܂���B"),
		XTAL_STRING("Xtal Compile Error 1004"), XTAL_STRING("�s���Ȋ֐��̉������ł��B"),
		XTAL_STRING("Xtal Compile Error 1005"), XTAL_STRING("�񖼑O�t�����������O�t�������̌�ɂ���܂��B"),
		XTAL_STRING("Xtal Compile Error 1006"), XTAL_STRING("�s����break���A�܂���continue���ł��B"),
		XTAL_STRING("Xtal Compile Error 1008"), XTAL_STRING("�s���ȑ��d������ł��B"),
		XTAL_STRING("Xtal Compile Error 1009"), XTAL_STRING("��`����Ă��Ȃ��ϐ� '%(name)s' �ɑ�����悤�Ƃ��܂��� �B"),
		XTAL_STRING("Xtal Compile Error 1010"), XTAL_STRING("�s���Ȑ������e�����̃T�t�B�b�N�X�ł��B"),
		XTAL_STRING("Xtal Compile Error 1011"), XTAL_STRING("�����񃊃e�����̓r���Ńt�@�C�����I���܂����B"),
		XTAL_STRING("Xtal Compile Error 1012"), XTAL_STRING("�s���ȑ�����̍��ӂł��B"),
		XTAL_STRING("Xtal Compile Error 1013"), XTAL_STRING("��r���Z���̌��ʂ����Z���悤�Ƃ��Ă��܂��B"),
		XTAL_STRING("Xtal Compile Error 1014"), XTAL_STRING("�s���ȕ��������_�����e�����ł��B"),
		XTAL_STRING("Xtal Compile Error 1015"), XTAL_STRING("�s����%(n)d�i���l���e�����̃T�t�B�b�N�X�ł��B"),
		XTAL_STRING("Xtal Compile Error 1016"), XTAL_STRING("assert���̈����̐����s���ł��B"),
		XTAL_STRING("Xtal Compile Error 1017"), XTAL_STRING("�s����%%�L�@���e�����ł��B"),
		XTAL_STRING("Xtal Compile Error 1018"), XTAL_STRING("default�߂��d����`����܂����B"),
		XTAL_STRING("Xtal Compile Error 1019"), XTAL_STRING("'%(name)s'�͑���s�\�ł��B"),
		XTAL_STRING("Xtal Compile Error 1021"), XTAL_STRING("�R�����g�̓r���Ńt�@�C�����I���܂����B"),
		XTAL_STRING("Xtal Compile Error 1022"), XTAL_STRING("�֐�����Ԃ��鑽�l�̍ő��255�ł��B"),
		XTAL_STRING("Xtal Compile Error 1023"), XTAL_STRING("��`����Ă��Ȃ��C���X�^���X�ϐ��� '%(name)s' ���Q�Ƃ��Ă��܂��B"),
		XTAL_STRING("Xtal Compile Error 1024"), XTAL_STRING("�����̃C���X�^���X�ϐ��� '%(name)s' �����ɒ�`����Ă��܂��B"),
		XTAL_STRING("Xtal Compile Error 1025"), XTAL_STRING("��r���Z���̌��ʂ��Ŕ�r���悤�Ƃ��Ă��܂��B"),
		XTAL_STRING("Xtal Compile Error 1026"), XTAL_STRING("�����X�R�[�v���ŁA�����ϐ��� '%(name)s' �����ɒ�`����Ă��܂��B"),
		XTAL_STRING("Xtal Compile Error 1027"), XTAL_STRING("�R�[�h���傫�����āA�o�C�g�R�[�h�̐����Ɏ��s���܂����B"),
		XTAL_STRING("Xtal Compile Error 1028"), XTAL_STRING("���Z�q�̑O��̋󔒂Ɖ��Z�q�̗D�揇�ʂ���v���Ă��܂���B�z�肵�Ă���D�揇�ʂƈقȂ��Ă���\��������܂��B"),
		
		XTAL_STRING("Xtal Runtime Error 1001"), XTAL_STRING("'%(object)s' �֐��Ăяo���� '%(no)s'�Ԗڂ̈����̌^���s���ł��B'%(required)s'�^��v�����Ă��܂����A'%(type)s'�^�̒l���n����܂����B"),
		XTAL_STRING("Xtal Runtime Error 1002"), XTAL_STRING("eval�ɓn���ꂽ�\�[�X�̃R���p�C�����A�R���p�C���G���[���������܂����B"),
		XTAL_STRING("Xtal Runtime Error 1003"), XTAL_STRING("�s���ȃC���X�^���X�ϐ��̎Q�Ƃł��B"),
		XTAL_STRING("Xtal Runtime Error 1004"), XTAL_STRING("�^�G���[�ł��B '%(required)s'�^��v�����Ă��܂����A'%(type)s'�^�̒l���n����܂����B"),
		XTAL_STRING("Xtal Runtime Error 1005"), XTAL_STRING("'%(object)s' �֐��Ăяo���̈����̐����s���ł��B'%(min)s'�ȏ�̈������󂯎��֐��ɁA%(value)s�̈�����n���܂����B"),
		XTAL_STRING("Xtal Runtime Error 1006"), XTAL_STRING("'%(object)s' �֐��Ăяo���̈����̐����s���ł��B'%(min)s'�ȏ�A'%(max)s'�ȉ��̈������󂯎��֐��ɁA'%(value)s'�̈�����n���܂����B"),
		XTAL_STRING("Xtal Runtime Error 1007"), XTAL_STRING("'%(object)s' �֐��Ăяo���̈����̐����s���ł��B���������Ȃ��֐��ɁA'%(value)s'�̈�����n���܂����B"),
		XTAL_STRING("Xtal Runtime Error 1008"), XTAL_STRING("'%(object)s'�̓V���A���C�Y�ł��܂���B"),
		XTAL_STRING("Xtal Runtime Error 1009"), XTAL_STRING("�s���ȃR���p�C���ς�Xtal�t�@�C���ł��B"),
		XTAL_STRING("Xtal Runtime Error 1010"), XTAL_STRING("�R���p�C���G���[���������܂����B"),
		XTAL_STRING("Xtal Runtime Error 1011"), XTAL_STRING("%(object)s :: '%(name)s' �͊��ɒ�`����Ă��܂��B"),
		XTAL_STRING("Xtal Runtime Error 1012"), XTAL_STRING("yield��fiber�̔���s���Ɏ��s����܂����B"),
		XTAL_STRING("Xtal Runtime Error 1013"), XTAL_STRING("%(object)s :: new �֐����o�^����Ă��Ȃ����߁A�C���X�^���X�𐶐��ł��܂���B"),
		XTAL_STRING("Xtal Runtime Error 1014"), XTAL_STRING("�t�@�C�� '%(name)s' ���J���܂���B"),
		XTAL_STRING("Xtal Runtime Error 1015"), XTAL_STRING("%(object)s �͒�`����Ă��܂���B"),
		XTAL_STRING("Xtal Runtime Error 1016"), XTAL_STRING("�t�@�C�� '%(name)s' �̃R���p�C�����A�R���p�C���G���[���������܂����B"),
		XTAL_STRING("Xtal Runtime Error 1017"), XTAL_STRING("%(object)s :: %(primary_key)s # %(secondary_key)s�� %(accessibility)s �ł��B"),
		XTAL_STRING("Xtal Runtime Error 1018"), XTAL_STRING("���ɕ���ꂽ�X�g���[���ł��B"),
		XTAL_STRING("Xtal Runtime Error 1019"), XTAL_STRING("C++�Œ�`���ꂽ�N���X�̑��d�p���͏o���܂���B"),
		XTAL_STRING("Xtal Runtime Error 1020"), XTAL_STRING("�z��͈̔͊O�A�N�Z�X�ł��B"),
		XTAL_STRING("Xtal Runtime Error 1021"), XTAL_STRING("%(object)s �͒�`����Ă��܂���B'%(pick)s'�ƊԈႦ�Ă���\��������܂��B"),
		XTAL_STRING("Xtal Runtime Error 1023"), XTAL_STRING("1��蒷��������͔͈͉��Z�q�Ɏw��ł��܂���B"),
		XTAL_STRING("Xtal Runtime Error 1024"), XTAL_STRING("0���Z�G���[�ł��B"),
		XTAL_STRING("Xtal Runtime Error 1025"), XTAL_STRING("ChRange�͕�Ԃł���K�v������܂��B"),
		XTAL_STRING("Xtal Runtime Error 1026"), XTAL_STRING("Xeg�v�f�ɕϊ��ł��܂���B"),
		XTAL_STRING("Xtal Runtime Error 1027"), XTAL_STRING("cap�֐��̈������s���ł��Bcap(name: value)�Ƃ����悤�ɖ��O�t�������ɂ��邩�Acap(\"name\"), value)�Ƃ����悤�ɌĂ�ł��������B"),
		XTAL_STRING("Xtal Runtime Error 1028"), XTAL_STRING("final�}�[�N���t����ꂽ�N���X'%(name)s'���p�����悤�Ƃ��܂����B"),
		XTAL_STRING("Xtal Runtime Error 1029"), XTAL_STRING("C++�Œ�`���ꂽ�N���X'%(name)s'�́A�N���X�������̂݌p�����\�ł��B"),
		XTAL_STRING("Xtal Runtime Error 1030"), XTAL_STRING("�Öق̕ϐ��Q�Ƃ�����܂��B%(name)s"),
	};
	
	for(int i=0; i<sizeof(messages)/sizeof(*messages)/2; ++i){
		text_map()->set_at(messages[i*2+0], messages[i*2+1]);
	}
}
	
}
