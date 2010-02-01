
#pragma once

namespace xtal{

inline void bind_error_message(){
	const StringLiteral messages[] = {
		XTAL_STRING("XCE1001"), XTAL_STRING("XCE1001:�\���G���[�ł��B"),
		XTAL_STRING("XCE1002"), XTAL_STRING("XCE1002:'%(required)s'�����҂��܂�����'%(char)s'�����o����܂����B"),
		XTAL_STRING("XCE1003"), XTAL_STRING("XCE1003:';' ������܂���B"),
		XTAL_STRING("XCE1004"), XTAL_STRING("XCE1004:�s���Ȋ֐��̉������ł��B"),
		XTAL_STRING("XCE1005"), XTAL_STRING("XCE1005:�񖼑O�t�����������O�t�������̌�ɂ���܂��B"),
		XTAL_STRING("XCE1006"), XTAL_STRING("XCE1006:�s����break���A�܂���continue���ł��B"),
		XTAL_STRING("XCE1008"), XTAL_STRING("XCE1008:�s���ȑ��d������ł��B"),
		XTAL_STRING("XCE1009"), XTAL_STRING("XCE1009:��`����Ă��Ȃ��ϐ� '%(name)s' �ɑ�����悤�Ƃ��܂��� �B"),
		XTAL_STRING("XCE1010"), XTAL_STRING("XCE1010:�s���Ȑ������e�����̃T�t�B�b�N�X�ł��B"),
		XTAL_STRING("XCE1011"), XTAL_STRING("XCE1011:�����񃊃e�����̓r���Ńt�@�C�����I���܂����B"),
		XTAL_STRING("XCE1012"), XTAL_STRING("XCE1012:�s���ȑ�����̍��ӂł��B"),
		XTAL_STRING("XCE1013"), XTAL_STRING("XCE1013:��r���Z���̌��ʂ����Z���悤�Ƃ��Ă��܂��B"),
		XTAL_STRING("XCE1014"), XTAL_STRING("XCE1014:�s���ȕ��������_�����e�����ł��B"),
		XTAL_STRING("XCE1015"), XTAL_STRING("XCE1015:�s����%(n)d�i���l���e�����̃T�t�B�b�N�X�ł��B"),
		XTAL_STRING("XCE1016"), XTAL_STRING("XCE1016:assert���̈����̐����s���ł��B"),
		XTAL_STRING("XCE1017"), XTAL_STRING("XCE1017:�s����%%�L�@���e�����ł��B"),
		XTAL_STRING("XCE1018"), XTAL_STRING("XCE1018:default�߂��d����`����܂����B"),
		XTAL_STRING("XCE1019"), XTAL_STRING("XCE1019:'%(name)s'�͑���s�\�ł��B"),
		XTAL_STRING("XCE1021"), XTAL_STRING("XCE1021:�R�����g�̓r���Ńt�@�C�����I���܂����B"),
		XTAL_STRING("XCE1022"), XTAL_STRING("XCE1022:�֐�����Ԃ��鑽�l�̍ő��255�ł��B"),
		XTAL_STRING("XCE1023"), XTAL_STRING("XCE1023:��`����Ă��Ȃ��C���X�^���X�ϐ��� '%(name)s' ���Q�Ƃ��Ă��܂��B"),
		XTAL_STRING("XCE1024"), XTAL_STRING("XCE1024:�����̃C���X�^���X�ϐ��� '%(name)s' �����ɒ�`����Ă��܂��B"),
		XTAL_STRING("XCE1025"), XTAL_STRING("XCE1025:��r���Z���̌��ʂ��Ĕ�r���悤�Ƃ��Ă��܂��B"),
		XTAL_STRING("XCE1026"), XTAL_STRING("XCE1026:�����X�R�[�v���ŁA�����ϐ��� '%(name)s' �����ɒ�`����Ă��܂��B"),
		XTAL_STRING("XCE1027"), XTAL_STRING("XCE1027:�R�[�h���傫�����āA�o�C�g�R�[�h�̐����Ɏ��s���܂����B"),
		XTAL_STRING("XCE1028"), XTAL_STRING("XCE1028:���Z�q�̑O��̋󔒂Ɖ��Z�q�̗D�揇�ʂ���v���Ă��܂���B�z�肵�Ă���D�揇�ʂƈقȂ��Ă���\��������܂��B"),
		XTAL_STRING("XCE1029"), XTAL_STRING("XCE1029:a&1�Ƃ����悤�ɁAbitwise and���������Ƃ��邱�Ƃ͈��S�̂��ߋ֎~����Ă��܂��B(a&1)==0�Ƃ����`�Ŕ�r���Ă��������B"),
		
		XTAL_STRING("XRE1001"), XTAL_STRING("XRE1001:'%(object)s' �֐��Ăяo���� '%(no)s'�Ԗڂ̈����̌^���s���ł��B'%(required)s'�^��v�����Ă��܂����A'%(type)s'�^�̒l���n����܂����B"),
		XTAL_STRING("XRE1002"), XTAL_STRING("XRE1002:�\�[�X�̃R���p�C�����A�R���p�C���G���[���������܂����B"),
		XTAL_STRING("XRE1003"), XTAL_STRING("XRE1003:�s���ȃC���X�^���X�ϐ��̎Q�Ƃł��B"),
		XTAL_STRING("XRE1004"), XTAL_STRING("XRE1004:�^�G���[�ł��B '%(required)s'�^��v�����Ă��܂����A'%(type)s'�^�̒l���n����܂����B"),
		XTAL_STRING("XRE1005"), XTAL_STRING("XRE1005:'%(object)s' �֐��Ăяo���̈����̐����s���ł��B'%(min)s'�ȏ�̈������󂯎��֐��ɁA%(value)s�̈�����n���܂����B"),
		XTAL_STRING("XRE1006"), XTAL_STRING("XRE1006:'%(object)s' �֐��Ăяo���̈����̐����s���ł��B'%(min)s'�ȏ�A'%(max)s'�ȉ��̈������󂯎��֐��ɁA'%(value)s'�̈�����n���܂����B"),
		XTAL_STRING("XRE1007"), XTAL_STRING("XRE1007:'%(object)s' �֐��Ăяo���̈����̐����s���ł��B���������Ȃ��֐��ɁA'%(value)s'�̈�����n���܂����B"),
		XTAL_STRING("XRE1008"), XTAL_STRING("XRE1008:'%(object)s'�̓V���A���C�Y�ł��܂���B"),
		XTAL_STRING("XRE1009"), XTAL_STRING("XRE1009:�s���ȃR���p�C���ς�Xtal�t�@�C���ł��B"),
		XTAL_STRING("XRE1010"), XTAL_STRING("XRE1010:�R���p�C���G���[���������܂����B"),
		XTAL_STRING("XRE1011"), XTAL_STRING("XRE1011:%(object)s :: '%(name)s' �͊��ɒ�`����Ă��܂��B"),
		XTAL_STRING("XRE1012"), XTAL_STRING("XRE1012:yield��fiber�̔���s���Ɏ��s����܂����B"),
		XTAL_STRING("XRE1013"), XTAL_STRING("XRE1013:%(object)s �ɃR���X�g���N�^���o�^����Ă��Ȃ����߁A�C���X�^���X�𐶐��ł��܂���B"),
		XTAL_STRING("XRE1014"), XTAL_STRING("XRE1014:�t�@�C�� '%(name)s' ���J���܂���B"),
		XTAL_STRING("XRE1015"), XTAL_STRING("XRE1015:%(object)s �͒�`����Ă��܂���B"),
		XTAL_STRING("XRE1016"), XTAL_STRING("XRE1016:�t�@�C�� '%(name)s' �̃R���p�C�����A�R���p�C���G���[���������܂����B"),
		XTAL_STRING("XRE1017"), XTAL_STRING("XRE1017:%(object)s :: %(primary_key)s # %(secondary_key)s�� %(accessibility)s �ł��B"),
		XTAL_STRING("XRE1018"), XTAL_STRING("XRE1018:���ɕ���ꂽ�X�g���[���ł��B"),
		XTAL_STRING("XRE1019"), XTAL_STRING("XRE1019:C++�Œ�`���ꂽ�N���X�̑��d�p���͏o���܂���B"),
		XTAL_STRING("XRE1020"), XTAL_STRING("XRE1020:�z��͈̔͊O�A�N�Z�X�ł��B"),
		XTAL_STRING("XRE1021"), XTAL_STRING("XRE1021:%(object)s �͒�`����Ă��܂���B'%(pick)s'�ƊԈႦ�Ă���\��������܂��B"),
		XTAL_STRING("XRE1023"), XTAL_STRING("XRE1023:1��蒷��������͔͈͉��Z�q�Ɏw��ł��܂���B"),
		XTAL_STRING("XRE1024"), XTAL_STRING("XRE1024:0���Z�G���[�ł��B"),
		XTAL_STRING("XRE1025"), XTAL_STRING("XRE1025:ChRange�͕�Ԃł���K�v������܂��B"),
		XTAL_STRING("XRE1026"), XTAL_STRING("XRE1026:xpeg�v�f�ɕϊ��ł��܂���B"),
		XTAL_STRING("XRE1027"), XTAL_STRING("XRE1027:cap�֐��̈������s���ł��Bcap(name: value)�Ƃ����悤�ɖ��O�t�������ɂ��邩�Acap(\"name\"), value)�Ƃ����悤�ɌĂ�ł��������B"),
		XTAL_STRING("XRE1028"), XTAL_STRING("XRE1028:final�}�[�N���t����ꂽ�N���X'%(name)s'���p�����悤�Ƃ��܂����B"),
		XTAL_STRING("XRE1029"), XTAL_STRING("XRE1029:C++�Œ�`���ꂽ�N���X'%(name)s'�́A�N���X�������̂݌p�����\�ł��B"),
		XTAL_STRING("XRE1030"), XTAL_STRING("XRE1030:�Öق̕ϐ��Q�Ƃ�����܂��B%(name)s"),
		XTAL_STRING("XRE1031"), XTAL_STRING("XRE1031:�V���O���g���N���X�̓V���O���g���N���X�łȂ��ƌp���ł��܂���B"),
		XTAL_STRING("XRE1032"), XTAL_STRING("XRE1032:�t�@�C��'%(name)s'���J���܂���B"),
		XTAL_STRING("XRE1033"), XTAL_STRING("XRE1033:�X�g���[���̏I�[�ȍ~��ǂݎ�낤�Ƃ��܂����B"),
		XTAL_STRING("XRE1034"), XTAL_STRING("XRE1034:�������[�v����������\��������xpeg�v�f�����s���悤�Ƃ��܂���"),	};
	
	for(int i=0; i<sizeof(messages)/sizeof(*messages)/2; ++i){
		IDPtr key(messages[i*2+0]);
		StringPtr value(messages[i*2+1]);
		text_map()->set_at(key, value);
	}
}
	
}
