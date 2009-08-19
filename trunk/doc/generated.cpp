namespace lib{namespace builtin{
/**
* \xbind lib::builtin
* \brief ���ׂẴN���X�̊��N���X
*/
class Any{
public:
	/**
	* \xbind
	* \brief ���̃I�u�W�F�N�g����������N���X��Ԃ��B
	*/
	 Class get_class();

	/**
	* \xbind
	* \brief �I�u�W�F�N�g�̖��O��Ԃ��B
	*/
	String object_name();

	/**
	* \xbind
	* \brief �I�u�W�F�N�g�̖��O�̃��X�g��Ԃ�
	* ��ԍŏ�ʂ̐e����̖��O�̃��X�g��Ԃ�
	*/
	Array object_name_list();

	/**
	* \xbind
	* \brief ���g�𕶎��񉻂���println����B
	* �����񉻂ɂ�to_s���\�b�h���Ă΂��B
	* \return ���g��Ԃ��B
	*/
	Any p();

};
}}

/**
	* \xbind
	* \brief �z���sz����������
	*/
	void upsize(uint sz);



/**
	* \xbind
	* \brief �擪�ɗv�f��ǉ�����
	*/
	void push_front( Any v);



/**
	* \xbind
	* \brief �擪�̗v�f���폜����
	*/
	void pop_front();



/**
	* \xbind
	* \brief �����ɗv�f��ǉ�����
	*/
	void push_back( Any v);



/**
	* \xbind
	* \brief �����̗v�f���폜����
	*/
	void pop_back();



/**
	* \xbind
	* \brief �擪�̗v�f��Ԃ�
	*/
	 Any front();



/**
	* \xbind
	* \brief �����̗v�f��Ԃ�
	*/
	 Any back();



/**
	* \xbind
	* \brief i�Ԗڂ�n�̗v�f���폜����
	*/
	void erase(int i, int n = 1);



/**
	* \xbind
	* \brief i�Ԗڂɗv�f��ǉ�����
	*/
	void insert(int i,  Any v);



/**
	* \xbind
	* \brief �󂩒��ׂ�
	*/
	bool empty();



/**
	* \xbind
	* \brief �󂩒��ׂ�
	*/
	bool is_empty();



/**
	* \xbind
	* \brief �v�f��S�č폜����
	*/
	void clear();


namespace lib{namespace builtin{
/**
* \xbind lib::builtin
* \xinherit lib::builtin::Any lib::builtin::Iterable
* \brief �z��
*/
class Array: public lib::builtin::Any, public lib::builtin::Iterable{
public:
	/**
	* \xbind
	* \brief size�̒����̔z��𐶐����� 
	*/
	 Array(uint size = 0);

	/**
	* \xbind
	* \brief �z��̒�����Ԃ�
	*/
	uint length();

	/**
	* \xbind
	* \brief �z��̒�����Ԃ�
	*/
	uint size();

	/**
	* \xbind
	* \brief �z��̒�����ύX����
	*/
	void resize(uint sz);

	/**
	* \xbind
	* \brief �z���sz����������
	*/
	void upsize(uint sz);

	/**
	* \xbind
	* \brief �z���sz���Z������
	*/
	void downsize(uint sz);

	/**
	* \xbind
	* \brief i�Ԗڂ̗v�f��Ԃ�
	*/
	 Any op_at(int i);

	/**
	* \xbind
	* \brief i�Ԗڂ̗v�f��ݒ肷��
	*/
	void op_set_at(int i,  Any v);

	/**
	* \xbind
	* \brief �擪�ɗv�f��ǉ�����
	*/
	void push_front( Any v);

	/**
	* \xbind
	* \brief �擪�̗v�f���폜����
	*/
	void pop_front();

	/**
	* \xbind
	* \brief �����ɗv�f��ǉ�����
	*/
	void push_back( Any v);

	/**
	* \xbind
	* \brief �����̗v�f���폜����
	*/
	void pop_back();

	/**
	* \xbind
	* \brief �擪�̗v�f��Ԃ�
	*/
	 Any front();

	/**
	* \xbind
	* \brief �����̗v�f��Ԃ�
	*/
	 Any back();

	/**
	* \xbind
	* \brief i�Ԗڂ���n�̕����z���Ԃ�
	*/
	Array slice(int i, int n = 1);

	/**
	* \xbind
	* \brief index����n�̕����z����폜���A���̕����z���Ԃ�
	*/
	Array splice(int i, int n = 1);

	/**
	* \xbind
	* \brief i�Ԗڂ�n�̗v�f���폜����
	*/
	void erase(int i, int n = 1);

	/**
	* \xbind
	* \brief i�Ԗڂɗv�f��ǉ�����
	*/
	void insert(int i,  Any v);

	/**
	* \xbind
	* \brief �z��̗v�f���t���ɂ���C�e���[�^��Ԃ�
	*/
	Any reverse();

	/**
	* \xbind
	* \brief �󂢃R�s�[��Ԃ�
	*/
	Array clone();

	/**
	* \xbind
	* \brief �v�f�𕶎���Ƃ��ĘA���������ʂ�Ԃ�
	* \param sep �v�f�Ɨv�f�̋�؂蕶����
	*/
	String join( String sep);

	/**
	* \xbind
	* \brief ���g��Ԃ�
	*/
	Array op_to_array();

	/**
	* \xbind
	* \brief �l�������������ׂ�
	*/
	bool op_eq( Array other);

	/**
	* \xbind
	* \brief �󂩒��ׂ�
	*/
	bool empty();

	/**
	* \xbind
	* \brief �󂩒��ׂ�
	*/
	bool is_empty();

	/**
	* \xbind
	* \brief �v�f��S�č폜����
	*/
	void clear();

	/**
	* \xbind
	* \brief �v�f���ŏ����甽���ł���Iterator��Ԃ�
	*/
	Any each();

	/**
	* \xbind
	* \brief ���g��iterator�Ŏ擾�ł���v�f�ɒu��������
	*/
	void assign( Any iterator);

	/**
	* \xbind
	* \brief iterator�Ŏ擾�ł���v�f��ǉ�����
	*/
	void append( Any iterator);

};
}}
namespace lib{namespace builtin{
/**
* \xbind lib::builtin
* \brief �k���l
*/
class Null{
public:
};
}}
namespace lib{namespace builtin{
/**
* \xbind lib::builtin
* \brief ����`�l
*/
class Undefined{
public:
};
}}
namespace lib{namespace builtin{
/**
* \xbind lib::builtin
* \brief �����l
*/
class Int{
public:
};
}}
namespace lib{namespace builtin{
/**
* \xbind lib::builtin
* \brief ���������_�l
*/
class Float{
public:
};
}}
namespace lib{namespace builtin{
/**
* \xbind lib::builtin
* \brief �^�U�l
*/
class Bool{
public:
};
}}
namespace lib{namespace builtin{
/**
* \xbind lib::builtin
* \brief ���
*/
class Range{
public:
	/**
	* \xbind
	* \brief ��Ԃ̍��̗v�f��Ԃ�
	*/
	 Any left();

	/**
	* \xbind
	* \brief ��Ԃ̉E�̗v�f��Ԃ�
	*/
	 Any right();

	/**
	* \xbind
	* \brief ��Ԃ̎�ނ�Ԃ�
	*/
	int kind();

	/**
	* \xbind
	* \brief ����������Ԃ��Ԃ�
	*/
	bool is_left_closed();

	/**
	* \xbind
	* \brief �E��������Ԃ��Ԃ�
	*/
	bool is_right_closed();

};
}}
namespace lib{namespace builtin{
/**
* \xbind lib::builtin
* \brief ���
*/
class IntRange{
public:
	/**
	* \xbind
	* \brief �͈͂̊J�n��Ԃ�
	*
	* begin�͍��E�J��� [begin, end) �œ��邱�Ƃ��o���� 
	*/
	int begin();

	/**
	* \xbind
	* \brief �͈͂̏I�[��Ԃ�
	*
	* end�͍��E�J��� [begin, end) �œ��邱�Ƃ��o���� 
	*/
	int end();

	/**
	* \xbind
	* \brief ��Ԃ̍��̗v�f��Ԃ�
	*/
	int left();

	/**
	* \xbind
	* \brief ��Ԃ̍��̗v�f��Ԃ�
	*/
	int right();

};
}}
namespace lib{namespace builtin{
/**
* \xbind lib::builtin
* \brief ���
*/
class FloatRange{
public:
	/**
	* \xbind
	* \brief ��Ԃ̍��̗v�f��Ԃ�
	*/
	float left();

	/**
	* \xbind
	* \brief ��Ԃ̍��̗v�f��Ԃ�
	*/
	float right();

};
}}

/**
	* \xbind
	* \brief �l�������������ׂ�
	*/
	bool op_eq( Values other);


namespace lib{namespace builtin{
/**
* \xbind lib::builtin
* \xinherit lib::builtin::Frame
* \brief �N���X
*/
class Class: public lib::builtin::Frame{
public:
	/**
	* \xbind
	* \brief �p��
	* \param cls �p������N���X�I�u�W�F�N�g
	*/
	void inherit( Class cls);

	/**
	* \xbind
	* \brief �p������Ă���N���X��񋓂���Iterator��Ԃ�
	*/
	Any inherited_classes();

	/**
	* \xbind
	* \brief �c��N���X��񋓂���Iterator��Ԃ�
	*/
	Any ancestors();

};
}}

/**
	* \xbind
	* \brief �Ăяo���ꏊ�̍s����Ԃ�
	*/
	int line();



/**
	* \xbind
	* \brief �Ăяo���ꏊ�̃t�@�C������Ԃ�
	*/
	 String file_name();



/**
	* \xbind
	* \brief �Ăяo���ꏊ�̊֐�����Ԃ�
	*/
	 String fun_name();



/**
	* \xbind
	* \brief �Ăяo���ꏊ�̕ϐ��t���[���I�u�W�F�N�g��Ԃ�
	*/
	 Frame variables_frame();


namespace lib{namespace builtin{namespace debug{
/**
* \xbind lib::builtin::debug
* \xinherit lib::builtin::Any
* \brief �f�o�b�O�t�b�N�֐��œn�����I�u�W�F�N�g
*/
class HookInfo: public lib::builtin::Any{
public:
	/**
	* \xbind
	* \brief �t�b�N�̎�ނ�Ԃ�
	*/
	int kind();

	/**
	* \xbind
	* \brief �t�b�N���ꂽ�ꏊ�̍s����Ԃ�
	*/
	int line();

	/**
	* \xbind
	* \brief �t�b�N���ꂽ�ꏊ�̃t�@�C������Ԃ�
	*/
	 String file_name();

	/**
	* \xbind
	* \brief �t�b�N���ꂽ�ꏊ�̊֐�����Ԃ�
	*/
	 String fun_name();

	/**
	* \xbind
	* \brief assertion�̃��b�Z�[�W��Ԃ�
	*/
	 String assertion_message();

	/**
	* \xbind
	* \brief ��O�I�u�W�F�N�g��Ԃ�
	*/
	 Any exception();

	/**
	* \xbind
	* \brief �t�b�N���ꂽ�ꏊ�̕ϐ��t���[���I�u�W�F�N�g��Ԃ�
	*/
	 Frame variables_frame();

	/**
	* \xbind
	* \brief �N���[�������
	* DebugInfo�I�u�W�F�N�g�͎g���܂킳��邽�߁A����ێ��������ꍇ�A�N���[�������K�v������B
	*/
	HookInfo clone();

};
}}}
namespace lib{namespace builtin{namespace debug{
/**
* \xbind lib::builtin::debug
* \brief �f�o�b�O�@�\��L���ɂ���
* �f�o�b�O�@�\�̓f�t�H���g�ł͖����ɂȂ��Ă���B
*/
	void enable();

}}}
namespace lib{namespace builtin{namespace debug{
/**
* \xbind lib::builtin::debug
* \brief �f�o�b�O�@�\�𖳌��ɂ���
*/
	void disable();

}}}
namespace lib{namespace builtin{namespace debug{
/**
* \xbind lib::builtin::debug
* \brief �f�o�b�O�@�\�������I�ɗL���ɂ���
* �f�o�b�O�@�\�̓f�t�H���g�ł͖����ɂȂ��Ă���B
*/
	void enable_force(int count);

}}}
namespace lib{namespace builtin{namespace debug{
/**
* \xbind lib::builtin::debug
* \brief �f�o�b�O�@�\�������I�ɖ����ɂ���
*/
	int disable_force();

}}}
namespace lib{namespace builtin{namespace debug{
/**
* \xbind lib::builtin::debug
* \brief �f�o�b�O�@�\���L�����ǂ���
*/
	bool is_enabled();

}}}
namespace lib{namespace builtin{namespace debug{
/**
* \xbind lib::builtin::debug
* \brief �s���ς�邽�тɌĂяo�����t�b�N�֐���o�^����
* \param hook �o�^����t�b�N�֐�
*/
	void set_line_hook( Any hook);

}}}
namespace lib{namespace builtin{namespace debug{
/**
* \xbind lib::builtin::debug
* \brief �֐��Ăяo�������x�ɌĂяo�����t�b�N�֐���o�^����
* \param hook �o�^����t�b�N�֐�
*/
	void set_call_hook( Any hook);

}}}
namespace lib{namespace builtin{namespace debug{
/**
* \xbind lib::builtin::debug
* \brief �֐�����return�����x�ɌĂяo�����t�b�N�֐���o�^����
* \param hook �o�^����t�b�N�֐�
*/
	void set_return_hook( Any hook);

}}}
namespace lib{namespace builtin{namespace debug{
/**
* \xbind lib::builtin::debug
* \brief ��O��throw�����x�ɌĂяo�����t�b�N�֐���o�^����
* \param hook �o�^����t�b�N�֐�
*/
	void set_throw_hook( Any hook);

}}}
namespace lib{namespace builtin{namespace debug{
/**
* \xbind lib::builtin::debug
* \brief �A�T�[�g�����s�����x�ɌĂяo�����t�b�N�֐���o�^����
* \param hook �o�^����t�b�N�֐�
*/
	void set_assert_hook( Any hook);

}}}
namespace lib{namespace builtin{namespace debug{
/**
* \xbind lib::builtin::debug
* \brief set_line_hook�֐��œo�^�����֐����擾����
*/
	 Any line_hook();

}}}
namespace lib{namespace builtin{namespace debug{
/**
* \xbind lib::builtin::debug
* \brief set_call_hook�֐��œo�^�����֐����擾����
*/
	 Any call_hook();

}}}
namespace lib{namespace builtin{namespace debug{
/**
* \xbind lib::builtin::debug
* \brief set_return_hook�֐��œo�^�����֐����擾����
*/
	 Any return_hook();

}}}
namespace lib{namespace builtin{namespace debug{
/**
* \xbind lib::builtin::debug
* \brief set_throw_hook�֐��œo�^�����֐����擾����
*/
	 Any throw_hook();

}}}
namespace lib{namespace builtin{namespace debug{
/**
* \xbind lib::builtin::debug
* \brief set_assert_hook�֐��œo�^�����֐����擾����
*/
	 Any assert_hook();

}}}
namespace lib{namespace builtin{
/**
* \xbind lib::builtin
* \brief �K�[�x�W�R���N�V���������s����
*
* ���قǎ��Ԃ͂�����Ȃ����A���S�ɃS�~������ł��Ȃ��K�[�x�W�R���N�g�֐�
* �Ⴆ�Ώz�Q�Ƃ͂���ł͌��m�ł��Ȃ��B
*/
	void gc();

}}
namespace lib{namespace builtin{
/**
* \xbind lib::builtin
* \brief �z�I�u�W�F�N�g���������t���K�[�x�W�R���N�V���������s����
*
* ���Ԃ͂����邪�A���݃S�~�ƂȂ��Ă�����̂͂Ȃ�ׂ��S�ĉ������K�[�x�W�R���N�g�֐�
* �z�Q�Ƃ����m�ł���B
*/
	void full_gc();

}}
namespace lib{namespace builtin{
/**
* \xbind lib::builtin
* \brief �K�[�x�W�R���N�V�����𖳌�������
*
* gc��full_gc�̌Ăяo���𖳌�������֐��B
* �����ł��ꂪ����Ăяo���ꂽ���L������Ă���A�Ăяo������enable_gc���ĂтȂ��ƃK�[�x�W�R���N�V�����͗L���ɂȂ�Ȃ�
*/
	void disable_gc();

}}
namespace lib{namespace builtin{
/**
* \xbind lib::builtin
* \brief �K�[�x�W�R���N�V������L��������

* disable_gc���Ă΂ꂽ�񐔂Ɠ��������Ăяo���ƃK�[�x�W�R���N�V�������L���ɂȂ�
*/
	void enable_gc();

}}
namespace lib{namespace builtin{
/**
* \xbind lib::builtin
* \brief file_name�t�@�C�����R���p�C������B
* ���̖߂�l��serialize����ƁA�o�C�g�R�[�h�`���ŕۑ������B
* \param file_name Xtal�X�N���v�g���L�q���ꂽ�t�@�C���̖��O
* \return ���s�ł���֐��I�u�W�F�N�g
*/
	Code compile_file( String file_name);

}}
namespace lib{namespace builtin{
/**
* \xbind lib::builtin
* \brief source��������R���p�C������B
* ���̖߂�l��serialize����ƁA�o�C�g�R�[�h�`���ŕۑ������B
* \param source Xtal�X�N���v�g���L�q���ꂽ������
* \return ���s�ł���֐��I�u�W�F�N�g
*/
	Code compile( String source);

}}
namespace lib{namespace builtin{
/**
* \xbind lib::builtin
* \brief file_name�t�@�C�����R���p�C�����Ď��s����B
* \param file_name Xtal�X�N���v�g���L�q���ꂽ�t�@�C���̖��O
* \return �X�N���v�g����return���ꂽ�l
*/
	Any load( String file_name);

}}
namespace lib{namespace builtin{
/**
* \xbind lib::builtin
* \brief file_name�t�@�C�����R���p�C�����ăR���p�C���ς݃\�[�X��ۑ����A���s����B
* \param file_name Xtal�X�N���v�g���L�q���ꂽ�t�@�C���̖��O
* \return �X�N���v�g����return���ꂽ�l
*/
	Any load_and_save( String file_name);

}}
namespace lib{namespace builtin{
/**
* \xbind lib::builtin
* \brief ��O
*/
class Exception{
public:
	/**
	* \xbind
	* \brief ����������
	*/
	void initialize( Any message = empty_string);

	/**
	* \xbind
	* \brief �o�b�N�g���[�X��ǉ�����
	*/
	void append_backtrace( Any file, int line,  Any function_name = empty_string);

	/**
	* \xbind
	* \brief �����񉻂���
	*/
	String to_s();

	/**
	* \xbind
	* \brief ���b�Z�[�W��Ԃ�
	*/
	String message();

	/**
	* \xbind
	* \brief �o�b�N�g���[�X�̏���v�f�Ƃ���Iterator��Ԃ�
	*/
	Any backtrace();

};
}}
namespace lib{namespace builtin{namespace filesystem{
/**
* \xbind lib::builtin::filesystem
* \brief �t�@�C���I�[�v��
*/
	Stream open( String file_name,  String flags);

}}}
namespace lib{namespace builtin{namespace filesystem{
/**
* \xbind lib::builtin::filesystem
* \brief �f�B���N�g�����ǂ���
*/
	bool is_directory( String path);

}}}
namespace lib{namespace builtin{namespace filesystem{
/**
* \xbind lib::builtin::filesystem
* \brief path�ȉ��̃G���g����񋓂���Iterator��Ԃ�
*/
	Any entries( String path);

}}}
namespace lib{namespace builtin{
/**
* \xbind lib::builtin
* \xinherit lib::builtin::Any
* \brief �t���[��
*/
class Frame: public lib::builtin::Any{
public:
	/**
	* \xbind
	* \brief �O���̃X�R�[�v��\��Frame�I�u�W�F�N�g��Ԃ��B
	*/
	 Frame outer();

	/**
	* \xbind
	* \brief �����o���i�[���ꂽ�AIterator��Ԃ�
	* �u���b�N�p�����[�^��(primary_key, secondary_key, value)
	*/
	Any members();

};
}}
namespace lib{namespace builtin{
/**
* \xbind lib::builtin
* \xinherit lib::builtin::Any
* \brief �����I�u�W�F�N�g
*/
class Arguments: public lib::builtin::Any{
public:
	/**
	* \xbind
	* \brief ���Ԏw������A���O�t��������n���Ĉ����I�u�W�F�N�g���\�z����
	*/
	 Arguments( Any ordered = undefined,  Any named = undefined);

	/**
	* \xbind
	* \brief key�ɑΉ����������Ԃ�
	* key�������ł���΁A���Ԏw������A������ł���Ζ��O�t��������Ԃ�
	*/
	 Any op_at( Any key);

	/**
	* \xbind
	* \brief ���Ԏw������̐���Ԃ�
	*/
	uint length();

	/**
	* \xbind
	* \brief ���Ԏw�������񋓂��邽�߂̃C�e���[�^��Ԃ�
	*/
	Any ordered_arguments();

	/**
	* \xbind
	* \brief ���O�t��������񋓂��邽�߂̃C�e���[�^��Ԃ�
	*/
	Any named_arguments();

};
}}
namespace lib{namespace builtin{
/**
* \xbind lib::builtin
* \xinherit lib::builtin::Any
* \brief ���\�b�h�I�u�W�F�N�g
*/
class Method: public lib::builtin::Any{
public:
};
}}
namespace lib{namespace builtin{
/**
* \xbind lib::builtin
* \xinherit lib::builtin::Method
* \brief �֐��I�u�W�F�N�g
*/
class Fun: public lib::builtin::Method{
public:
};
}}
namespace lib{namespace builtin{
/**
* \xbind lib::builtin
* \xinherit lib::builtin::Fun
* \brief �����_�I�u�W�F�N�g
*/
class Lambda: public lib::builtin::Fun{
public:
};
}}
namespace lib{namespace builtin{
/**
* \xbind lib::builtin
* \xinherit lib::builtin::Fun
* \brief �t�@�C�o�[�I�u�W�F�N�g
*/
class Fiber: public lib::builtin::Fun{
public:
};
}}
namespace lib{namespace builtin{
/**
* \xbind lib::builtin
* \brief �C�e���[�^�֗̕����\�b�h��񋟂��邽�߂̃N���X
*/
class Iterator{
public:
	/**
	* \xbind
	* \brief �v�f��n�f�o�b�O�v�����g����
	* ����̃C�e���[�^��Ԃ��B
	*/
	Any ip(int n = 3);

	/**
	* \xbind
	* \brief �v�f��Z�߂Ĕz��ɂ��ĕԂ�
	*/
	Array op_to_array();

	/**
	* \xbind
	* \brief �v�f��Z�߂ĘA�z�z��ɂ��ĕԂ�
	* ��ȏ�̒l��񋓂���C�e���[�^�ł���K�v������
	*/
	Map op_to_map();

	/**
	* \xbind
	* \brief �v�f�𕶎��񉻂��A����ɂ�����sep�ŘA�������������Ԃ�
	* \code
	* [1, 2, 3].join("::").p;
	* //=> 1::2::3
	* \endcode
	*/
	String join( String sep = "");

	/**
	* \xbind
	* \brief (index, value)��Ԃ��C�e���[�^��Ԃ�
	* ���[�v���Ƃ�index�̓C���N�������g�����B
	* \code
	* [45, 12, 33].with_index{ |index, value|
	*     %f(%d-%d)(index, value).p;
	* }
	* //=> 0-45
	* //=> 1-12
	* //=> 2-33
	* \endcode
	*/
	Any with_index(int start = 0);

	/**
	* \xbind
	* \brief �v�f��conv�֐��ŕϊ������v�f��Ԃ��C�e���[�^��Ԃ�
	* map���\�b�h�Ɠ����Ӗ��ł���
	*/
	Any collect( Any conv);

	/**
	* \xbind
	* \brief �v�f��conv�֐��ŕϊ������v�f��Ԃ��C�e���[�^��Ԃ�
	* \code
	* [10, 20, 30].map(|x| x*2){
    *	it.p;
	* }
	* //=> 20
	* //=> 40
	* //=> 60
	* \endcode
	*/
	Any map( Any conv);

	/**
	* \xbind
	* \brief �I�ʂ��ꂽ�v�f��Ԃ��C�e���[�^��Ԃ�
	* filter���\�b�h�Ɠ���̈Ӗ��ł���
	*/
	Any select( Any pred);

	/**
	* \xbind
	* \brief �I�ʂ��ꂽ�v�f��Ԃ��C�e���[�^��Ԃ�
	* \code
	* [1, 2, 3].filter(|x| x%2==1){
	*	it.p;
	* }
	* //=> 1
	* //=> 3
	* \endcode
	*/
	Any filter( Any pred);

	/**
	* \xbind
	* \brief pred�֐���true��Ԃ��܂ŃC�e���[�g����C�e���[�^��Ԃ�
	* \code
	* [7, 5, 3, 2, 1, 3].break_if(|x| x%2!=1){
	*     it.p;
	* }
	* //=> 7
	* //=> 5
	* //=> 3
	* \endcode
	*/
	Any break_if( Any pred);

	/**
	* \xbind
	* \brief times��C�e���[�g����C�e���[�^��Ԃ�
	* \code
	* [5, 3, 7].cycle.take(5).join(",").p;
	* //=> 5,3,7,5,3
	* \endcode
	*/
	Any take(int times);

	/**
	* \xbind
	* \brief ����ɃC�e���[�g����C�e���[�^��Ԃ�
	*/
	Any zip(...);

	/**
	* \xbind
	* \brief ����ɃC�e���[�g����C�e���[�^��Ԃ�
	*/
	Any chain(...);

	/**
	* \xbind
	* \brief �C�e���[�g����v�f���Ȃ��Ȃ�����A�ŏ�����J��Ԃ��C�e���[�^��Ԃ�
	* \code
	* [4, 8, 11].map(|x| x*3).cycle{
	*    it.p;
	* }
	* //=> 12
	* //=> 24
	* //=> 33
	* //=> 12
	* //=> 24
	* //=> 33
	* // �ȉ��J��Ԃ�
	* \endcode
	*/
	Any cycle();

	/**
	* \xbind
	* \brief �C�e���[�g����v�f�̍ő�̒l��Ԃ�
	* \param pred ����v�f�����肷��q��֐��I�u�W�F�N�g
	* ��̈������󂯎��A��ڂ���ڂ̕����傫���Ȃ�true��Ԃ��֐���n�����ƁB
	* null���w�肷��� < ���Z�q�Ŕ��肳���B
	*/
	Any max_element( Any pred = null);

	/**
	* \xbind
	* \brief �C�e���[�g����v�f�̍ŏ��̒l��Ԃ�
	* \param pred ����v�f�����肷��q��֐��I�u�W�F�N�g
	* ��̈������󂯎��A��ڂ���ڂ̕����������Ȃ�true��Ԃ��֐���n�����ƁB
	* null���w�肷��� > ���Z�q�Ŕ��肳���B
	*/
	Any min_element( Any pred = null);

	/**
	* \xbind
	* \brief �C�e���[�g����v�f��pred�֐���true��Ԃ��֐���Ԃ�
	* \param pred �T���Ă���v�f���𔻒肷��q��֐��I�u�W�F�N�g
	* ��̈������󂯎��A�T���Ă���v�f�Ȃ�true��Ԃ��֐���n�����ƁB
	*/
	Any find( Any pred);

	/**
	* \xbind
	* \brief inject
	*/
	Any inject( Any init,  Any fn);

	/**
	* \xbind
	* \brief (�O��̗v�f, ����̗v�f)��v�f������C�e���[�^��Ԃ�
	* �ŏ��̈��̑O��̗v�f�ɂ�undefined������
	*/
	Any with_prev();

};
}}
namespace lib{namespace builtin{
/**
* \xbind lib::builtin
* \brief �C�e���[�g�\�ȃR���e�i�̂��߂̎�����񋟂��邽�߂̃N���X�B
* �����inherit�����N���X�̃I�u�W�F�N�g�́Aeach���\�b�h���o�R����lib::builtin::Iterator�������\�b�h���Ăяo����B
*/
class Iterable{
public:
};
}}
namespace lib{namespace builtin{
/**
* \xbind lib::builtin
* \brief ���C�u�����̓o�^�ȂǂɎg���N���X�̈��
*/
class Lib{
public:
	/**
	* \xbind
	* \brief �R���X�g���N�^
	*/
	 Lib();

	/**
	* \xbind
	* \brief ���[�h�p�X��ǉ�����
	*/
	void append_load_path( String path);

};
}}
namespace lib{namespace builtin{
/**
* \xbind lib::builtin
* \xinherit lib::builtin::Any lib::builtin::Iterable
* \brief �A�z�z��
*/
class Map: public lib::builtin::Any, public lib::builtin::Iterable{
public:
	/**
	* \xbind
	* \brief ��̘A�z�z��I�u�W�F�N�g�𐶐�
	*/
	 Map();

	/**
	* \xbind
	* \brief key�ɑΉ�����v�f��Ԃ�
	* \param key �����̂��߂̃L�[ 
	*/
	 Any op_at( Any key);

	/**
	* \xbind
	* \brief key�ɑΉ�����v�f��ݒ肷��
	* \param key �����̂��߂̃L�[ 
	* \param value key�ɑΉ�����l
	*/
	void op_set_at( Any key,  Any value);

	/**
	* \xbind
	* \brief key�ɑΉ�����v�f��ݒ肷��
	* \param key �����̂��߂̃L�[ 
	* \param value key�ɑΉ�����l
	*/
	void insert( Any key,  Any value);

	/**
	* \xbind
	* \brief key�ɑΉ�����l���폜����
	* \param key �����̂��߂̃L�[ 
	*/
	void erase( Any key);

	/**
	* \xbind
	* \brief �A�z�z��ɓo�^���ꂽ�v�f�̐���Ԃ�
	* \return �A�z�z��ɓo�^���ꂽ�v�f�̐�
	*/
	uint size();

	/**
	* \xbind
	* \brief �A�z�z��ɓo�^���ꂽ�v�f�̐���Ԃ�
	* \return �A�z�z��ɓo�^���ꂽ�v�f�̐�
	*/
	uint length();

	/**
	* \xbind
	* \brief �󂩒��ׂ�
	* \retval true ��
	* \retval false ���
	*/
	bool empty();

	/**
	* \xbind
	* \brief �󂩒��ׂ�
	* \retval true ��
	* \retval false ���
	*/
	bool is_empty();

	/**
	* \xbind
	* \brief �A�������A�z�z���Ԃ�
	*/
	Map op_cat( Map a);

	/**
	* \xbind
	* \brief ���g�ƘA�����A���g��Ԃ�
	*/
	Map op_cat_assign( Map a);

	/**
	* \xbind
	* \brief (key, value)��v�f�Ƃ���AIterator��Ԃ�
	*/
	Any pairs();

	/**
	* \xbind
	* \brief key��v�f�Ƃ���AIterator��Ԃ�
	*/
	Any keys();

	/**
	* \xbind
	* \brief value��v�f�Ƃ���AIterator��Ԃ�
	*/
	Any values();

	/**
	* \xbind
	* \brief (key, value)��v�f�Ƃ���AIterator��Ԃ�
	* pairs�Ɠ���
	*/
	Any each();

	/**
	* \xbind
	* \brief �󂢃R�s�[��Ԃ�
	*/
	Map clone();

	/**
	* \xbind
	* \brief �v�f��S�č폜����
	*/
	void clear();

	/**
	* \xbind
	* \brief ���g��Ԃ�
	*/
	Map op_to_map();

	/**
	* \xbind
	* \brief ���g��iterator�Ŏ擾�ł���v�f�ɒu��������
	*/
	void assign( Any iterator);

	/**
	* \xbind
	* \brief iterator�Ŏ擾�ł���v�f��ǉ�����
	*/
	void append( Any iterator);

	/**
	* \xbind
	* \brief �f�t�H���g�l�Ƃ��Đݒ肳��Ă���I�u�W�F�N�g�����o��
	* \return �f�t�H���g�l
	*/
	 Any default_value();

	/**
	* \xbind
	* \brief �f�t�H���g�l��ݒ肷��
	* \param default_value �f�t�H���g�l
	*/
	void set_default_value( Any default_value);

};
}}
namespace lib{namespace builtin{
/**
* \xbind lib::builtin
* \xinherit lib::builtin::Any
* \brief �X�g���[��
*/
class Stream: public lib::builtin::Any{
public:
	/**
	* \xbind
	* \brief ������str���X�g���[���ɗ���
	*/
	void put_s( String str);

	/**
	* \xbind
	* \brief length�������X�g���[��������o���A������Ƃ��ĕԂ��B
	*/
	 String get_s(uint length);

	/**
	* \xbind
	* \brief �X�g���[�����炷�ׂĂ̕��������o���A������Ƃ��ĕԂ�
	*/
	 String get_s_all();

	/**
	* \xbind
	* \brief value�𕶎��񉻂��ăv�����g����
	*/
	uint print( Any value);

	/**
	* \xbind
	* \brief value�𕶎��񉻂��A���s�������ăv�����g����
	*/
	void println( Any value);

	/**
	* \xbind
	* \brief �X�g���[���̐擪����̈ʒu��Ԃ�
	*/
	 uint tell();

	/**
	* \xbind
	* \brief �X�g���[���̐擪����offset�̈ʒu�Ɉړ�����
	*/
	 void seek(uint offset);

	/**
	* \xbind
	* \brief �X�g���[�����N���[�Y����
	*/
	 void close();

	/**
	* \xbind
	* \brief �X�g���[�����t���b�V������
	*/
	 void flush();

	/**
	* \xbind
	* \brief �X�g���[������X�g���[����size�o�C�g�������� 
	*/
	 uint pour( Stream in_stream, uint size);

	/**
	* \xbind
	* \brief �X�g���[������X�g���[���ɂ��ׂė������� 
	*/
	 uint pour_all( Stream in_stream);

	/**
	* \xbind
	* \brief �X�g���[���̑S�T�C�Y��Ԃ�
	* �X�g���[���̎�ނɂ���ẮA�T�C�Y�𓾂邱�Ƃ͕s�\�ł���B
	*/
	 uint size();

	/**
	* \xbind
	* \brief �X�g���[�����I����Ă��邩�Ԃ�
	*/
	 bool eos();

	/**
	* \xbind
	* \brief �I�u�W�F�N�g�𒼗񉻂��ăX�g���[���ɏ�������
	*
	* \param obj ���񉻂��ĕۑ��������I�u�W�F�N�g
	*/
	void serialize( Any obj);

	/**
	* \xbind
	* \brief ���񉻂��ꂽ�I�u�W�F�N�g���X�g���[������ǂݏo��
	*
	* \return �������ꂽ�I�u�W�F�N�g
	*/
	Any deserialize();

	/**
	* \xbind
	* \brief �����t����8-bit���X�g���[���ɏ�������
	*/
	void put_i8(i8 v);

	/**
	* \xbind
	* \brief �����t����16-bit���X�g���[���ɏ�������
	*/
	void put_i16be(i16 v);

	/**
	* \xbind
	* \brief �����t����16-bit���X�g���[���ɏ�������
	*/
	void put_i16le(i16 v);

	/**
	* \xbind
	* \brief �����t����32-bit���X�g���[���ɏ�������
	*/
	void put_i32be(i32 v);

	/**
	* \xbind
	* \brief �����t����32-bit���X�g���[���ɏ�������
	*/
	void put_i32le(i32 v);

	/**
	* \xbind
	* \brief �����t����64-bit���X�g���[���ɏ�������
	*/
	void put_i64be(i64 v);

	/**
	* \xbind
	* \brief ����������8-bit���X�g���[���ɏ�������
	*/
	void put_u8(u8 v);

	/**
	* \xbind
	* \brief ����������16-bit���X�g���[���ɏ�������
	*/
	void put_u16be(u16 v);

	/**
	* \xbind
	* \brief ����������16-bit���X�g���[���ɏ�������
	*/
	void put_u16le(u16 v);

	/**
	* \xbind
	* \brief ����������32-bit���X�g���[���ɏ�������
	*/
	void put_u32be(u32 v);

	/**
	* \xbind
	* \brief ����������32-bit���X�g���[���ɏ�������
	*/
	void put_u32le(u32 v);

	/**
	* \xbind
	* \brief �����t����8-bit���X�g���[��������o��
	*/
	i8 get_i8();

	/**
	* \xbind
	* \brief �����t����16-bit���X�g���[��������o��
	*/
	i16 get_i16be();

	/**
	* \xbind
	* \brief �����t����16-bit���X�g���[��������o��
	*/
	i16 get_i16le();

	/**
	* \xbind
	* \brief �����t����32-bit���X�g���[��������o��
	*/
	i32 get_i32be();

	/**
	* \xbind
	* \brief �����t����32-bit���X�g���[��������o��
	*/
	i32 get_i32le();

	/**
	* \xbind
	* \brief ����������8-bit���X�g���[��������o��
	*/
	u8 get_u8();

	/**
	* \xbind
	* \brief ����������16-bit���X�g���[��������o��
	*/
	u16 get_u16be();

	/**
	* \xbind
	* \brief ����������16-bit���X�g���[��������o��
	*/
	u16 get_u16le();

	/**
	* \xbind
	* \brief ����������32-bit���X�g���[��������o��
	*/
	u32 get_u32be();

	/**
	* \xbind
	* \brief ����������32-bit���X�g���[��������o��
	*/
	u32 get_u32le();

	/**
	* \xbind
	* \brief ���������_��32-bit���X�g���[���ɏ�������
	*/
	void put_f32be(f32 v);

	/**
	* \xbind
	* \brief ���������_��32-bit���X�g���[���ɏ�������
	*/
	void put_f32le(f32 v);

	/**
	* \xbind
	* \brief ���������_��32-bit���X�g���[��������o��
	*/
	f32 get_f32be();

	/**
	* \xbind
	* \brief ���������_��32-bit���X�g���[��������o��
	*/
	f32 get_f32le();

};
}}
namespace lib{namespace builtin{
/**
* \xbind lib::builtin
* \xinherit lib::builtin::Stream
* \brief �������[�X�g���[��
*/
class MemoryStream: public lib::builtin::Stream{
public:
};
}}
namespace lib{namespace builtin{
/**
* \xbind lib::builtin
* \xinherit lib::builtin::Stream
* \brief ������X�g���[��
* �������ǂݎ�邽�߂̃X�g���[���B�������ݕs�B
*/
class StringStream: public lib::builtin::Stream{
public:
};
}}
namespace lib{namespace builtin{
/**
* \xbind lib::builtin
* \xinherit lib::builtin::Stream
* \brief �t�@�C���X�g���[��
*/
class FileStream: public lib::builtin::Stream{
public:
};
}}
namespace lib{namespace builtin{
/**
* \xbind lib::builtin
* \xinherit lib::builtin::Any lib::builtin::Iterable
* \brief ������̃N���X
*/
class String: public lib::builtin::Any, public lib::builtin::Iterable{
public:
	/**
	* \xbind
	* \brief �󕶎�����\�z����
	*/
	 String();

	/**
	* \xbind
	* \brief �f�[�^�T�C�Y��Ԃ��B
	* �}���`�o�C�g�������l�����Ȃ��B
	*/
	uint data_size();

	/**
	* \xbind
	* \brief ������̒�����Ԃ��B
	* �}���`�o�C�g�������l������B
	*/
	uint length();

	/**
	* \xbind
	* \brief ��Ӊ������������Ԃ��B
	*/
	 ID intern();

	/**
	* \xbind
	* \brief ��Ӊ�����Ă��邩�Ԃ��B
	*/
	bool is_interned();

	/**
	* \xbind
	* \brief �����ɕϊ��������ʂ�Ԃ��B
	*/
	int to_i();

	/**
	* \xbind
	* \brief ���������_���ɕϊ��������ʂ�Ԃ��B
	*/
	float to_f();

	/**
	* \xbind
	* \brief �������g��Ԃ��B
	*/
	String to_s();

	/**
	* \xbind
	* \brief �ꕶ���Â̕������v�f�Ƃ���Iterator��Ԃ��B
	* \return �ꕶ���Â̕������v�f�Ƃ���Iterator
	*/
	Any each();

	/**
	* \xbind
	* \brief �A������
	* \return �A�����ꂽ�V�����I�u�W�F�N�g
	*/
	String cat( String v);

	/**
	* \xbind
	* \brief �ꕶ���̕����񂩂ǂ���
	*/
	bool is_ch();

	/**
	* \xbind
	* \brief �ꕶ���̕�����̏ꍇ�A����ascii�R�[�h��Ԃ�
	*/
	int ascii();

	/**
	* \xbind
	* \brief �����͈̔̓I�u�W�F�N�g�͈͓̔����ǂ���
	*/
	bool op_in( ChRange range);

	/**
	* \xbind
	* \brief �͈̓I�u�W�F�N�g�𐶐�����
	*/
	ChRange op_range( String right, int kind);

	/**
	* \xbind
	* \brief �A������
	*/
	String op_cat( String v);

	/**
	* \xbind
	* \brief �l������������ׂ�
	*/
	bool op_eq( String v);

	/**
	* \xbind
	* \brief ��菬��������ׂ�
	*/
	bool op_lt( String v);

	/**
	* \xbind
	* \brief ��������X�L��������
	*/
	Any scan( Any pattern);

	/**
	* \xbind
	* \brief ������𕪊����A���̕����������v�f�Ƃ���Iterator��Ԃ�
	*/
	Any split( Any pattern);

	/**
	* \xbind
	* \brief ������𕪊����A���̕����������v�f�Ƃ���Iterator��Ԃ�
	*/
	bool match( Any pattern);

	/**
	* \xbind
	* \brief �}�b�`���镔����u���������V�����������Ԃ�
	*/
	String gsub( Any pattern,  Any fn);

	/**
	* \xbind
	* \brief �ŏ��Ƀ}�b�`���镔����u���������V�����������Ԃ�
	*/
	String sub( Any pattern,  Any fn);

};
}}

/**
* \xbind
* \xinherit lib::builtin::Any
* \brief �X���b�h
*/
class Thread: public lib::builtin::Any{
public:
};


/**
* \xbind
* \xinherit lib::builtin::Any
* \brief �~���[�e�b�N�X
*/
class Mutex: public lib::builtin::Any{
public:
};

namespace lib{namespace builtin{namespace xpeg{
/**
* \xbind lib::builtin::xpeg
* \xinherit lib::builtin::Any
* \brief PEG�����s����
*/
class Executor: public lib::builtin::Any{
public:
	/**
	* \xbind
	* \brief �X�g���[�����C�e���[�^���󂯎��\�z����
	*/
	 Executor( Any stream_or_iterator = null);

};
}}}
