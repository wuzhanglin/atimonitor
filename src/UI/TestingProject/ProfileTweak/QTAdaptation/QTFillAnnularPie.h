#ifndef QT_FILL_ANNULAR_PIE_H
#define QT_FILL_ANNULAR_PIE_H

#include <QWidget>

class QTFillAnnularPie : public QWidget
{
public:
	QTFillAnnularPie(QWidget* parent = NULL);
	~QTFillAnnularPie();

protected:
	virtual void resizeEvent(QResizeEvent * event);
	virtual void paintEvent(QPaintEvent * event);

private:
	void init();
};

#endif