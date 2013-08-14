#ifndef QT_LINEEDIT_H
#define QT_LINEEDIT_H

#include <QWidget>
#include <QLineEdit>

class QExtendLineEdit : public QLineEdit
{
public:
	QExtendLineEdit(QWidget* parent = NULL);
	~QExtendLineEdit();

protected:
	virtual void paintEvent(QPaintEvent* event);
};

class QTLineEdit : public QWidget
{
public:
    QTLineEdit(QWidget* parent = NULL);
    ~QTLineEdit();

protected:
    virtual void resizeEvent(QResizeEvent* event);
    virtual void paintEvent(QPaintEvent* event);

private:
    void init();

private:
    QExtendLineEdit* m_pLineEdit;
};

#endif