
#pragma once

namespace xtal{
	
enum{
	KIND_BLOCK,
	KIND_CLASS
};

enum{
	KIND_FUN,
	KIND_METHOD,
	KIND_FIBER,
	KIND_THREAD
};

enum{
	KIND_STRING,
	KIND_TEXT,
	KIND_FORMAT
};

enum{
	RESULT_DISCARD = 0<<2,
	RESULT_TO_ARRAY = 1<<2,
	RESULT_COVER_NULL = 0<<3,
	RESULT_COVER_FROM_ARRAY = 1<<3
};

/// �o�C�g�R�[�h�̎���ID
enum CodeType{

/**
* @brief �������Ȃ��B
* 
* format op
* stack [] -> []
*/
CODE_NOP,
	
/**
* @brief �X�^�b�N��null�l���v�b�V������B
* 
* format op
* stack [] -> [value]
*/
CODE_PUSH_NULL,

/**
* @brief �X�^�b�N��true�l���v�b�V������B
* 
* format op
* stack [] -> [value]
*/
CODE_PUSH_TRUE,

/**
* @brief �X�^�b�N��nop�l���v�b�V������B
* 
* format op
* stack [] -> [value]
*/
CODE_PUSH_NOP,

/**
* @brief �X�^�b�N��int�l���v�b�V������B
* 
* format op
* stack [] -> [value]
*/
CODE_PUSH_INT_0,

/**
* @brief �X�^�b�N��int�l���v�b�V������B
* 
* format op
* stack [] -> [value]
*/
CODE_PUSH_INT_1,

/**
* @brief �X�^�b�N��int�l���v�b�V������B
* 
* format op
* stack [] -> [value]
*/
CODE_PUSH_INT_2,

/**
* @brief �X�^�b�N��int�l���v�b�V������B
* 
* format op
* stack [] -> [value]
*/
CODE_PUSH_INT_3,

/**
* @brief �X�^�b�N��int�l���v�b�V������B
* 
* format op
* stack [] -> [value]
*/
CODE_PUSH_INT_4,

/**
* @brief �X�^�b�N��int�l���v�b�V������B
* 
* format op
* stack [] -> [value]
*/
CODE_PUSH_INT_5,

/**
* @brief �X�^�b�N��int�l���v�b�V������B
* 
* format op, value
* stack [] -> [value]
*/
CODE_PUSH_INT_1BYTE,

/**
* @brief �X�^�b�N��int�l���v�b�V������B
* 
* format op, value1, value2
* stack [] -> [value]
*/
CODE_PUSH_INT_2BYTE,

/**
* @brief �X�^�b�N��float�l���v�b�V������B
* 
* format op
* stack [] -> [value]
*/
CODE_PUSH_FLOAT_0,

/**
* @brief �X�^�b�N��float�l���v�b�V������B
* 
* format op
* stack [] -> [value]
*/
CODE_PUSH_FLOAT_0_25,

/**
* @brief �X�^�b�N��float�l���v�b�V������B
* 
* format op
* stack [] -> [value]
*/
CODE_PUSH_FLOAT_0_5,

/**
* @brief �X�^�b�N��float�l���v�b�V������B
* 
* format op
* stack [] -> [value]
*/
CODE_PUSH_FLOAT_1,

/**
* @brief �X�^�b�N��float�l���v�b�V������B
* 
* format op
* stack [] -> [value]
*/
CODE_PUSH_FLOAT_2,

/**
* @brief �X�^�b�N��float�l���v�b�V������B
* 
* format op
* stack [] -> [value]
*/
CODE_PUSH_FLOAT_3,

/**
* @brief �z������B
* 
* format op, count
* stack [] -> [value]
*/
CODE_PUSH_ARRAY,

/**
* @brief �z��ɗv�f��ǉ�����B
* 
* format op
* stack [arrya, value] -> [array]
*/
CODE_ARRAY_APPEND,

/**
* @brief �A�z�z������B
* 
* format op, count
* stack [] -> [value]
*/
CODE_PUSH_MAP,

/**
* @brief �A�z�z��ɗv�f��ǉ�����B
* 
* format op
* stack [map, key, value] -> [map]
*/
CODE_MAP_APPEND,

/**
* @brief �֐������B
* 
* format op, type, num1, num2
* stack [] -> [value]
*/
CODE_PUSH_FUN,

/**
* @brief ���݂̌Ă΂�Ă���֐����g���X�^�b�N�ɐςށB
* 
* format op
* stack [] -> [value]
*/
CODE_PUSH_CALLEE,

/**
* @brief ���݂̎c������I�u�W�F�N�g���X�^�b�N�ɐςށB
* 
* format op
* stack [] -> [value]
*/
CODE_PUSH_ARGS,

/**
* @brief ���݂�this���X�^�b�N�ɐςށB
* 
* format op
* stack [] -> [value]
*/
CODE_PUSH_THIS,

/**
* @brief ���݂̃t���[�����X�^�b�N�ɐςށB
* 
* format op
* stack [] -> [value]
*/
CODE_PUSH_CURRENT_CONTEXT,

/**
* @brief �\���B
* 
* format op
* stack [expr, expr_String, message] -> []
*/
CODE_ASSERT,

/**
* @brief �X�^�b�N�g�b�v�̒l���|�b�v����B
* 
* format op
* stack [value] -> []
*/
CODE_POP,

/**
* @brief �X�^�b�N�g�b�v�̒l���v�b�V������B
* 
* format op
* stack [value] -> [value, value]
*/
CODE_DUP,

/**
* @brief �X�^�b�N�g�b�v�̒l����O�ɓ����B
* 
* format op
* stack [value1, value2] -> [value2, value1]
*/
CODE_INSERT_1,

/**
* @brief �X�^�b�N�g�b�v�̒l���O�ɓ����B
* 
* format op
* stack [value1, value2, value3] -> [value3, value1, value2]
*/
CODE_INSERT_2,

/**
* @brief �X�^�b�N�g�b�v�̒l���O�O�ɓ����B
* 
* format op
* stack [value1, value2, value3, value4] -> [value4, value1, value2, value3]
*/
CODE_INSERT_3,

/**
* @brief ���O������
* 
* format op, size1, size2
* stack [value] -> [value]
*/
CODE_SET_NAME,

/**
* @brief �u���b�N���J�n����B
* 
* format op, size1, size2
* stack [] -> []
*/
CODE_BLOCK_BEGIN,

/**
* @brief �u���b�N�����B
* 
* format op
* stack [] -> []
*/
CODE_BLOCK_END,

/**
* @brief �q�[�v�ɏ��Ȃ��ƐÓI�Ɋm�肵�Ă���u���b�N�����B
* 
* format op
* stack [] -> []
*/
CODE_BLOCK_END_NOT_ON_HEAP,

/**
* @brief �t���[���̊J�n
* 
* format op, type, core1, core2
* stack [] -> []
*/
CODE_FRAME_BEGIN,

/**
* @brief �t���[�������
* 
* format op
* stack [] -> [value]
*/
CODE_FRAME_END,

/**
* @brief ���[�J���ϐ������o���B
* 
* format op
* stack [] -> [value]
*/
CODE_LOCAL_0, 

/**
* @brief ���[�J���ϐ������o���B
* 
* format op
* stack [] -> [value]
*/
CODE_LOCAL_1, 

/**
* @brief ���[�J���ϐ������o���B
* 
* format op
* stack [] -> [value]
*/
CODE_LOCAL_2, 

/**
* @brief ���[�J���ϐ������o���B
* 
* format op
* stack [] -> [value]
*/
CODE_LOCAL_3, 

/**
* @brief ���[�J���ϐ������o���B
* 
* format op, pos
* stack [] -> [value]
*/
CODE_LOCAL, 

/**
* @brief �q�[�v�ɏ��Ȃ��ƐÓI�Ɋm�肵�Ă��郍�[�J���ϐ������o���B
* 
* format op, pos
* stack [] -> [value]
*/
CODE_LOCAL_NOT_ON_HEAP, 

/**
* @brief ���[�J���ϐ��ɒl��ݒ肷��B
* 
* format op, pos
* stack [] -> [value]
*/
CODE_SET_LOCAL_0, 

/**
* @brief ���[�J���ϐ��ɒl��ݒ肷��B
* 
* format op, pos
* stack [] -> [value]
*/
CODE_SET_LOCAL_1, 

/**
* @brief ���[�J���ϐ��ɒl��ݒ肷��B
* 
* format op, pos
* stack [] -> [value]
*/
CODE_SET_LOCAL_2, 

/**
* @brief ���[�J���ϐ��ɒl��ݒ肷��B
* 
* format op, pos
* stack [] -> [value]
*/
CODE_SET_LOCAL_3, 

/**
* @brief ���[�J���ϐ��ɒl��ݒ肷��B
* 
* format op, pos
* stack [] -> [value]
*/
CODE_SET_LOCAL, 

/**
* @brief �q�[�v�ɏ��Ȃ��ƐÓI�Ɋm�肵�Ă��郍�[�J���ϐ��ɒl��ݒ肷��B
* 
* format op, pos
* stack [] -> [value]
*/
CODE_SET_LOCAL_NOT_ON_HEAP, 

/**
* @brief ���[�J���ϐ������o���B
* 
* format op, pos1, pos2
* stack [] -> [value]
*/
CODE_LOCAL_W, 

/**
* @brief ���[�J���ϐ��ɒl��ݒ肷��B
* 
* format op, pos1, pos2
* stack [] -> [value]
*/
CODE_SET_LOCAL_W, 

/**
* @brief �O���[�o���ϐ������o���B
* 
* format op, symbol1, symbol2
* stack [] -> [value]
*/
CODE_GLOBAL, 

/**
* @brief �I�u�W�F�N�g�̃����o�����o���B
* 
* format op, symbol1, symbol2
* stack [object] -> [result]
*/
CODE_MEMBER,

/**
* @brief �I�u�W�F�N�g�̃����o�����o���B
* 
* format op, symbol1, symbol2
* stack [object] -> [result]
*/
CODE_MEMBER_IF_DEFINED,

/**
* @brief �I�u�W�F�N�g�̃����o���`����B
* 
* format op, symbol1, symbol2
* stack [object, value] -> []
*/
CODE_DEFINE_MEMBER,

/**
* @brief �C���X�^���X�ϐ������o���B
* 
* format op, symbol1, symbol2
* stack [object] -> [result]
*/
CODE_INSTANCE_VARIABLE,

/**
* @brief �C���X�^���X�ϐ��ɒl��ݒ肷��B
* 
* format op, symbol1, symbol2
* stack [object, value] -> []
*/
CODE_SET_INSTANCE_VARIABLE,

/**
* @brief ��������
* 
* format op, goto1, goto2
* stack [value] -> []
*/
CODE_IF,

/**
* @brief ��������
* 
* format op, goto1, goto2
* stack [value] -> []
*/
CODE_UNLESS,


/**
* @brief ����������
* 
* format op, goto1, goto2
* stack [] -> []
*/
CODE_GOTO,

/**
* @brief �X�^�b�N�ɃW�����v�ʒu�𖄂ߍ���
* 
* format op, goto1, goto2
* stack [] -> [address]
*/
CODE_PUSH_GOTO,

/**
* @brief �X�^�b�N����|�b�v�����A�h���X�ɃW�����v����
* 
* format op
* stack [] -> []
*/
CODE_POP_GOTO,

/**
* @brief once���Z�q
* 
* format op, goto1, goto2, value1, value2
* stack [] -> []
*/
CODE_ONCE,

/**
* @brief �֐��Ăяo���̌�n��������
* 
* format op
* stack [] -> []
*/
CODE_CLEANUP_CALL,

/**
* @brief �֐����甲����
* 
* format op
* stack [] -> []
*/
CODE_RETURN_0,

/**
* @brief �֐����甲����
* 
* format op
* stack [value1] -> []
*/
CODE_RETURN_1,

/**
* @brief �֐����甲����
* 
* format op
* stack [value1, value2] -> []
*/
CODE_RETURN_2,

/**
* @brief �֐����甲����
* 
* format op, N
* stack [value1, value2, ... valueN] -> []
*/
CODE_RETURN_N,

/**
* @brief fiber�̎��s���ꎞ���f����
format; op, N
* stack [value1, value2, ... valueN] -> []
*/
CODE_YIELD,

/**
* @brief ���z�}�V���̃��[�v����E�o����B
* 
* format op
* stack [] -> []
*/
CODE_EXIT,

/**
* @brief ��OUnsupportedError�𓊂���B
* 
* format op
* stack [] -> []
*/
CODE_THROW_UNSUPPORTED_ERROR,

/**
* @brief �I�u�W�F�N�g�e�[�u������l�����o���B
* 
* format op, pos1, pos2
* stack [] -> [result]
*/
CODE_GET_VALUE,

/**
* @brief �I�u�W�F�N�g�e�[�u���ɒl��ݒ肷��B
* 
* format op, pos1, pos2
* stack [value] -> []
*/
CODE_SET_VALUE,

/**
* @brief ���O�̃����o�Q�Ƃ��L�����`�F�b�N����B
* 
* format op
* stack [value] -> [result]
*/
CODE_CHECK_UNSUPPORTED,

/**
* @brief ���\�b�h�Ăяo��
* 
* format op, sym, ...
* stack [target] -> [result 0..num]
*/
CODE_SEND,

/**
* @brief ���\�b�h�Ăяo��
* 
* format op, sym, ...
* stack [target] -> [result 0..num]
*/
CODE_SEND_IF_DEFINED,

/**
* @brief �֐��Ăяo��
* 
* format op, ...
* stack [target] -> [result 0..num]
*/
CODE_CALL,

/**
* @brief �֐��Ăяo��
* 
* format op, ...
* stack [target] -> [result 0..num]
*/
CODE_CALLEE,

/**
* @brief ��O�t���[�����J�n
* 
* format op, catch1, catch2, finally1, finally2, end1, end2 
* stack [] -> []
*/
CODE_TRY_BEGIN,

/**
* @brief ��O�t���[�����I��
* 
* format op
* stack [] -> []
*/
CODE_TRY_END,

/**
* @brief ��O�𓊂���
* 
* format op
* stack [value] -> []
*/
CODE_THROW,

/**
* @brief �P��+�̉��Z���s���B
* 
* format op
* stack [value] -> [result]
*/
CODE_POS,

/**
* @brief �P��-�̉��Z���s���B
* 
* format op
* stack [value] -> [result]
*/
CODE_NEG,

/**
* @brief �P��~�̉��Z���s���B
* 
* format op
* stack [value] -> [result]
*/
CODE_COM,

/**
* @brief �P��!�̉��Z���s���B
* 
* format op
* stack [value] -> [result]
*/
CODE_NOT,

/**
* @brief �z��̗v�f�����o���B
* 
* format op
* stack [object, index] -> [result]
*/
CODE_AT,

/**
* @brief �z��̗v�f��ݒ肷��B
* 
* format op
* stack [object, index, value] -> []
*/
CODE_SET_AT, 

/**
* @brief ��+�̉��Z���s���B
* 
* format op
* stack [value1, value2] -> [result]
*/
CODE_ADD,

/**
* @brief ��-�̉��Z���s���B
* 
* format op
* stack [value1, value2] -> [result]
*/
CODE_SUB,

/**
* @brief ��~�̉��Z���s���B
* 
* format op
* stack [value1, value2] -> [result]
*/
CODE_CAT,

/**
* @brief ��*�̉��Z���s���B
* 
* format op
* stack [value1, value2] -> [result]
*/
CODE_MUL,

/**
* @brief ��/�̉��Z���s���B
* 
* format op
* stack [value1, value2] -> [result]
*/
CODE_DIV,

/**
* @brief ��%�̉��Z���s���B
* 
* format op
* stack [value1, value2] -> [result]
*/
CODE_MOD,

/**
* @brief ��&�̉��Z���s���B
* 
* format op
* stack [value1, value2] -> [result]
*/
CODE_AND,

/**
* @brief ��&�̉��Z���s���B
* 
* format op
* stack [value1, value2] -> [result]
*/
CODE_OR,

/**
* @brief ��^�̉��Z���s���B
* 
* format op
* stack [value1, value2] -> [result]
*/
CODE_XOR,

/**
* @brief ��<<�̉��Z���s���B
* 
* format op
* stack [value1, value2] -> [result]
*/
CODE_SHL,

/**
* @brief ��>>�̉��Z���s���B
* 
* format op
* stack [value1, value2] -> [result]
*/
CODE_SHR,

/**
* @brief ��>>>�̉��Z���s���B
* 
* format op
* stack [value1, value2] -> [result]
*/
CODE_USHR,

/**
* @brief ���[�J���ϐ����C���N�������g����
* 
* format op, variable1, variable2
* stack [] -> []
*/
CODE_LOCAL_NOT_ON_HEAP_INC,

/**
* @brief ���[�J���ϐ����f�N�������g����
* 
* format op, variable1, variable2
* stack [] -> []
*/
CODE_LOCAL_NOT_ON_HEAP_DEC,

/**
* @brief ���[�J���ϐ����C���N�������g����
* 
* format op
* stack [value] -> [result]
*/
CODE_INC,

/**
* @brief ���[�J���ϐ����f�N�������g����
* 
* format op
* stack [value] -> [result]
*/
CODE_DEC,

/**
* @brief �N���[���𐶐�����
* 
* format op
* stack [value] -> [result]
*/
CODE_CLONE,

/**
* @brief ��==�̉��Z���s���A�������򂷂�B
* 
* format op, goto1, goto2
* stack [value1, value2] -> [result]
*/
CODE_EQ_IF,
CODE_NE_IF,
CODE_LT_IF,
CODE_LE_IF,
CODE_GT_IF,
CODE_GE_IF,

/**
* @brief ��==�̉��Z���s���B
* 
* format op
* stack [value1, value2] -> [result]
*/
CODE_EQ,
CODE_NE,
CODE_LT,
CODE_LE,
CODE_GT,
CODE_GE,
CODE_RAW_EQ,
CODE_RAW_NE,
CODE_IS,
CODE_NIS,


/**
* @brief ��+�̉��Z���s���B
* 
* format op
* stack [value1, value2] -> [result]
*/
CODE_ADD_ASSIGN,

/**
* @brief ��-�̉��Z���s���B
* 
* format op
* stack [value1, value2] -> [result]
*/
CODE_SUB_ASSIGN,

/**
* @brief ��~�̉��Z���s���B
* 
* format op
* stack [value1, value2] -> [result]
*/
CODE_CAT_ASSIGN,

/**
* @brief ��*�̉��Z���s���B
* 
* format op
* stack [value1, value2] -> [result]
*/
CODE_MUL_ASSIGN,

/**
* @brief ��/�̉��Z���s���B
* 
* format op
* stack [value1, value2] -> [result]
*/
CODE_DIV_ASSIGN,

/**
* @brief ��%�̉��Z���s���B
* 
* format op
* stack [value1, value2] -> [result]
*/
CODE_MOD_ASSIGN,

/**
* @brief ��&�̉��Z���s���B
* 
* format op
* stack [value1, value2] -> [result]
*/
CODE_AND_ASSIGN,

/**
* @brief ��&�̉��Z���s���B
* 
* format op
* stack [value1, value2] -> [result]
*/
CODE_OR_ASSIGN,

/**
* @brief ��^�̉��Z���s���B
* 
* format op
* stack [value1, value2] -> [result]
*/
CODE_XOR_ASSIGN,

/**
* @brief ��<<�̉��Z���s���B
* 
* format op
* stack [value1, value2] -> [result]
*/
CODE_SHL_ASSIGN,

/**
* @brief ��>>�̉��Z���s���B
* 
* format op
* stack [value1, value2] -> [result]
*/
CODE_SHR_ASSIGN,

/**
* @brief ��>>>�̉��Z���s���B
* 
* format op
* stack [value1, value2] -> [result]
*/
CODE_USHR_ASSIGN,


CODE_MAX

};

}

