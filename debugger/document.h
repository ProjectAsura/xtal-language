#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QtGui>
#include <QPlainTextEdit>
#include <QObject>

struct FileInfo{
	QString path;
	QMap<int, QString> breakpoints;
};

/**
  * \brief �v���W�F�N�g�̏���ێ�����N���X
�@ * �\�[�X�p�X�A�u���[�N�|�C���g�̈ʒu��ێ����Ă���
  */
class Document{
public:

	void init();

	bool save(const QString& filename);

	bool load(const QString& filename);

public:

	/**
	  * \brief i�Ԗڂ̃t�@�C���������o��
	  */
	FileInfo* file(int i);

	/**
	  * \brief �t�@�C����񂪉����邩�Ԃ�
	  */
	int fileCount();

	/**
	  * \brief �v���W�F�N�g��file��ǉ�����
	  */
	bool addFile(const QString& file);

	bool removeFile(const QString& file);

	/**
	  * \brief ������file�Ƀ}�b�`����t�@�C���������o��
	  */
	FileInfo* findFile(const QString& file);

	/**
	  * \brief ����������file�Ƀ}�b�`����t�@�C���������o��
	  */
	FileInfo* findFileAbout(const QString& file);

public:

	void setEvalExpr(int n, const QString& expr){
		if(n>=evalExprs_.size()){
			evalExprs_.resize(n+1);
		}

		evalExprs_[n] = expr;
	}

	int evalExprCount(){
		return evalExprs_.size();
	}

	QString evalExpr(int n){
		return evalExprs_[n];
	}

	void removeEvalExpr(int n);

	void insertEvaExpr(int n);

private:

	QVector<FileInfo> files_;
	QVector<QString> evalExprs_;
};


#endif // DOCUMENT_H
