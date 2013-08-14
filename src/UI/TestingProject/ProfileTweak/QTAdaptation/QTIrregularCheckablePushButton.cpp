#include "QTIrregularCheckablePushButton.h"

#include <QPainter>

QTIrregularCheckablePushButton::QTIrregularCheckablePushButton(QWidget* parent /* = NULL */)
    : QTCheckablePushButton(parent)
{
    init();
}

QTIrregularCheckablePushButton::QTIrregularCheckablePushButton(const QString& text, QWidget* parent /* = NULL */)
    : QTCheckablePushButton(text, parent)
{
    init();
}

QTIrregularCheckablePushButton::QTIrregularCheckablePushButton(const QIcon& icon, const QString& text, QWidget* parent /* = NULL */)
    : QTCheckablePushButton(icon, text, parent)
{
    init();
}

QTIrregularCheckablePushButton::~QTIrregularCheckablePushButton()
{

}

void 
QTIrregularCheckablePushButton::init()
{

}

void 
QTIrregularCheckablePushButton::resizeEvent(QResizeEvent* pEvent)
{
    QTCheckablePushButton::resizeEvent(pEvent);
}

void 
QTIrregularCheckablePushButton::paintEvent(QPaintEvent* pEvent)
{
    QPainter painter(this);
    QPen pen(Qt::black);
	pen.setWidth(2);
    painter.setPen(pen);
    painter.drawRect(rect());

    if (this->isChecked())
    {
        painter.fillRect(rect(), Qt::red);
    }
    

    QTCheckablePushButton::paintEvent(pEvent);
}