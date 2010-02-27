#ifndef EVALEXPRVIEW_H
#define EVALEXPRVIEW_H

#include <QtGui>

#include "../src/xtal/xtal.h"
#include "../src/xtal/xtal_macro.h"
using namespace xtal;

/**
  * \brief �ϐ��̕\���c���[�r���[
  */
class EvalExprView : public QTreeView{
	Q_OBJECT
public:

	EvalExprView(QWidget *parent);

public slots:

	void dataChanged(QStandardItem* item);

signals:

	void exprChanged(int i, const QString& expr);

public:

	void setExpr(int n, const QString& expr);

	QString item(int n);

	void setExprResult(int n, const ArrayPtr& value);

	void setChild(QStandardItem* item, int n, const QString& key, const ArrayPtr& value);

	void setChild(QStandardItem* item, const AnyPtr& children);

	QStandardItem* makeItem(const QString& text, bool editable = false);

private:
	QStandardItemModel* model_;
	bool dataChanged_;
};

#endif // EVALEXPRVIEW_H
