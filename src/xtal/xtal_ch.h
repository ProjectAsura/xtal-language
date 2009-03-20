
#pragma once

namespace xtal{
	
/**
* @brief �擪�o�C�g�����āA���̃}���`�o�C�g���������������𒲂ׂ�B
*
* �}�C�i�X�̒l���Ԃ��ꂽ�ꍇ�A�Œᕶ������Ԃ��B
* -2�̏ꍇ�A�Œ�2�����ȏ�̕����ŁA�{���̒�����2�����ڂ�ǂ܂Ȃ��Ɣ��f�ł��Ȃ��A�Ƃ����Ӗ��ƂȂ�B
*/
int_t ch_len(char_t lead);

/**
* @brief �}���`�o�C�g���������������𒲂ׂ�B
*
* int_t ch_len(char_t lead)���Ă΂ꂽ��A�}�C�i�X�̒l��Ԃ����ꍇ�ɑ����ČĂԁB
* ch_len��-2�̒l��Ԃ�����́Astr�̐�ɂ͍Œ�2�o�C�g���̃f�[�^���i�[���邱�ƁB
*/
int_t ch_len2(const char_t* str);


/**
* @brief ���̕�����Ԃ�
*
* �Ⴆ�� a ��n�����ꍇ�Ab ���Ԃ�
*/
StringPtr ch_inc(const char_t* data, int_t data_size);

/**
* @brief �����̑召����
*
* ���̒l a �̕����̕���b�̕�����菬����
* 0�̒l ������
* ���̒l b�̕����̕���a�̕�����菬����
*/
int_t ch_cmp(const char_t* a, uint_t asize, const char_t* b, uint_t bsize);

uint_t edit_distance(const void* data1, uint_t size1, const void* data2, uint_t size2);

/**
* @brief �}���`�o�C�g������g�ݗ��Ă邽�߂̃��[�e�B���e�B�N���X
*/
class ChMaker{
public:

	ChMaker(){
		pos_ = 0;
		len_ = -1;
	}

	bool is_completed(){
		return pos_==len_;
	}

	void add(char_t ch){
		buf_[pos_++] = ch;
		if(pos_==1){
			len_ = ch_len(ch);
		}
		else if(pos_ == -len_){
			len_ = ch_len2(buf_);
		}
	}

	const IDPtr& to_s(){
		return temp_ = xnew<ID>(&buf_[0], pos_);
	}

	int_t pos(){
		return pos_;
	}

	char_t at(int_t i){
		return buf_[i];
	}

	const char_t* data(){
		return buf_;
	}

	void clear(){
		pos_ = 0;
		len_ = -1;
	}

private:

	int_t pos_;
	int_t len_;
	char_t buf_[8];
	IDPtr temp_;
};

}
