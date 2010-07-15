/** \file src/xtal/xtal_lib.h
* \brief src/xtal/xtal_lib.h
*/

#ifndef XTAL_LIB_H_INCLUDE_GUARD
#define XTAL_LIB_H_INCLUDE_GUARD

#pragma once

namespace xtal{

/**
* \xbind lib::builtin
* \brief �����o�ɃA�N�Z�X����ƁA���O�ɑΉ��������C�u�����t�@�C����ǂݍ��ދ@�\���������N���X�̈��
*/
class AutoLoader : public Class{
public:

	AutoLoader();
	
	const AnyPtr& on_rawmember(const IDPtr& primary_key, const AnyPtr& secondary_key, bool inherited_too, int_t& accessibility, bool& nocache);

	/**
	* \xbind
	* \brief ���[�h�p�X��ǉ�����
	*/
	void append_load_path(const StringPtr& path){
		load_path_list_->push_back(path);
	}

	void on_visit_members(Visitor& m){
		Class::on_visit_members(m);
		m & load_path_list_ & path_map_;
	}

private:
	ArrayPtr load_path_list_;
	MapPtr path_map_;
};

/**
* \xbind lib::builtin
* \brief ���C�u�����̓o�^�ȂǂɎg���N���X�̈��
*/
class Lib : public AutoLoader{
public:
	Lib();
};

class Global : public Class{
public:
	void on_def(const IDPtr& primary_key, const AnyPtr& value, const AnyPtr& secondary_key, int_t accessibility);
};

}


#endif // XTAL_LIB_H_INCLUDE_GUARD
