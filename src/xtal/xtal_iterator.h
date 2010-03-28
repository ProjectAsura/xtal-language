/** \file src/xtal/xtal_iterator.h
* \brief src/xtal/xtal_iterator.h
*/

#ifndef XTAL_ITERATOR_H_INCLUDE_GUARD
#define XTAL_ITERATOR_H_INCLUDE_GUARD

#pragma once

namespace xtal{

class DelegateToIterator : public Base{
	IDPtr member_;
public:
	
	DelegateToIterator(const IDPtr& name)
		:member_(name){}

	void on_rawcall(const VMachinePtr& vm);
};

/**
* \xbind lib::builtin
* \brief �C�e���[�^�֗̕����\�b�h��񋟂��邽�߂̃N���X
*/
class Iterator{
public:

	//void scan(pattern);

	/**
	* \xbind
	* \brief �v�f��n�f�o�b�O�v�����g����
	* ����̃C�e���[�^��Ԃ��B
	*/
	AnyPtr ip(int_t n = 3);

	/**
	* \xbind
	* \brief �v�f��Z�߂Ĕz��ɂ��ĕԂ�
	*/
	ArrayPtr op_to_array();

	/**
	* \xbind
	* \brief �v�f��Z�߂ĘA�z�z��ɂ��ĕԂ�
	* ��ȏ�̒l��񋓂���C�e���[�^�ł���K�v������
	*/
	MapPtr op_to_map();

	/**
	* \xbind
	* \brief �v�f�𕶎��񉻂��A����ɂ�����sep�ŘA�������������Ԃ�
	* \code
	* [1, 2, 3].join("::").p;
	* //=> 1::2::3
	* \endcode
	*/
	StringPtr join(const StringPtr& sep = XTAL_STRING(""));

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
	AnyPtr with_index(int_t start = 0);

	/**
	* \xbind
	* \brief �v�f��conv�֐��ŕϊ������v�f��Ԃ��C�e���[�^��Ԃ�
	* map���\�b�h�Ɠ����Ӗ��ł���
	*/
	AnyPtr collect(const AnyPtr& conv);

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
	AnyPtr map(const AnyPtr& conv);

	/**
	* \xbind
	* \brief �I�ʂ��ꂽ�v�f��Ԃ��C�e���[�^��Ԃ�
	* filter���\�b�h�Ɠ���̈Ӗ��ł���
	*/
	AnyPtr select(const AnyPtr& pred);

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
	AnyPtr filter(const AnyPtr& pred);

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
	AnyPtr break_if(const AnyPtr& pred);

	/**
	* \xbind
	* \brief times��C�e���[�g����C�e���[�^��Ԃ�
	* \code
	* [5, 3, 7].cycle.take(5).join(",").p;
	* //=> 5,3,7,5,3
	* \endcode
	*/
	AnyPtr take(int_t times);

	/**
	* \xbind
	* \brief ����ɃC�e���[�g����C�e���[�^��Ԃ�
	*/
	AnyPtr zip(...);

	/**
	* \xbind
	* \brief ����ɃC�e���[�g����C�e���[�^��Ԃ�
	*/
	AnyPtr chain(...);

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
	AnyPtr cycle();

	/**
	* \xbind
	* \brief �C�e���[�g����v�f�̍ő�̒l��Ԃ�
	* \param pred ����v�f�����肷��q��֐��I�u�W�F�N�g
	* ��̈������󂯎��A��ڂ���ڂ̕����傫���Ȃ�true��Ԃ��֐���n�����ƁB
	* null���w�肷��� < ���Z�q�Ŕ��肳���B
	*/
	AnyPtr max_element(const AnyPtr& pred = null);

	/**
	* \xbind
	* \brief �C�e���[�g����v�f�̍ŏ��̒l��Ԃ�
	* \param pred ����v�f�����肷��q��֐��I�u�W�F�N�g
	* ��̈������󂯎��A��ڂ���ڂ̕����������Ȃ�true��Ԃ��֐���n�����ƁB
	* null���w�肷��� > ���Z�q�Ŕ��肳���B
	*/
	AnyPtr min_element(const AnyPtr& pred = null);

	/**
	* \xbind
	* \brief �C�e���[�g����v�f��pred�֐���true��Ԃ��֐���Ԃ�
	* \param pred �T���Ă���v�f���𔻒肷��q��֐��I�u�W�F�N�g
	* ��̈������󂯎��A�T���Ă���v�f�Ȃ�true��Ԃ��֐���n�����ƁB
	*/
	AnyPtr find(const AnyPtr& pred);

	/**
	* \xbind
	* \brief inject
	*/
	AnyPtr inject(const AnyPtr& init, const AnyPtr& fn);

	/**
	* \xbind
	* \brief (�O��̗v�f, ����̗v�f)��v�f������C�e���[�^��Ԃ�
	* �ŏ��̈��̑O��̗v�f�ɂ�undefined������
	*/
	AnyPtr with_prev();

};

/**
* \xbind lib::builtin
* \brief �C�e���[�g�\�ȃR���e�i�̂��߂̎�����񋟂��邽�߂̃N���X�B
* �����inherit�����N���X�̃I�u�W�F�N�g�́Aeach���\�b�h���o�R����lib::builtin::Iterator�������\�b�h���Ăяo����B
*/
class Iterable{};

class ZipIter : public Base{
public:

	ZipIter(const VMachinePtr& vm);

	void common(const VMachinePtr& vm, const IDPtr& id);

	void block_first(const VMachinePtr& vm);
	
	void block_next(const VMachinePtr& vm);

	void block_break(const VMachinePtr& vm);

	void on_visit_members(Visitor& m);

	ArrayPtr next_;
};

struct BlockValueHolder1{
	
	BlockValueHolder1(const AnyPtr& tar, bool& not_end);
	BlockValueHolder1(const ArrayPtr& tar, bool& not_end);
	~BlockValueHolder1();

	AnyPtr target;
	AnyPtr values[1];

	SmartPtr<ArrayIter> it;
};

struct BlockValueHolder2{
	
	BlockValueHolder2(const AnyPtr& tar, bool& not_end);
	BlockValueHolder2(const MapPtr& tar, bool& not_end);
	~BlockValueHolder2();

	AnyPtr target;
	AnyPtr values[2];

	SmartPtr<MapIter> it;
};

struct BlockValueHolder3{
	BlockValueHolder3(const AnyPtr& tar, bool& not_end);
	~BlockValueHolder3();

	AnyPtr target;
	AnyPtr values[3];
};

bool block_next(BlockValueHolder1& holder, bool first);
bool block_next(BlockValueHolder2& holder, bool first);
bool block_next(BlockValueHolder3& holder, bool first);
void block_break(AnyPtr& target);

}

#endif // XTAL_ITERATOR_H_INCLUDE_GUARD
