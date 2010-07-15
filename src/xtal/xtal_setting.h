/** \file src/xtal/xtal_setting.h
* \brief src/xtal/xtal_setting.h
*/

#ifndef XTAL_SETTING_H_INCLUDE_GUARD
#define XTAL_SETTING_H_INCLUDE_GUARD

#pragma once

/**
* \brief �p�[�T�g�poff
*/
//#define XTAL_NO_PARSER

/**
* \brief wchar_t�g�pon
*/
//#define XTAL_USE_WCHAR

/**
* \brief �X���b�h�g�poff
*/
#define XTAL_NO_THREAD

/**
* \brief Xtal�X���b�h���f��2���g�p����
* ����Environment�ɏ�������VMachine���m�ł�����Ɏ��s���邱�Ƃ��\�ɂ��邪�A
* �ׂ����r�����䂪���邽�ߕ���Ɏ��s���Ȃ��ꍇ�x���Ȃ�B
*/
//#define XTAL_USE_THREAD_MODEL2

/**
* \brief pthread�̃X���b�h���[�J���X�g���[�W���g��
*/
//#define XTAL_USE_PTHREAD_TLS

/**
* \brief �������T�C�Y�̃������m�ۂ�Xtal�Ǝ��̃A���P�[�^���g��Ȃ�
*/
//#define XTAL_NO_SMALL_ALLOCATOR


//#define XTAL_CHECK_REF_COUNT

#endif // XTAL_SETTING_H_INCLUDE_GUARD
