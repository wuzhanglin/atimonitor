#include "QTBackgroundWidget.h"

#include <QResizeEvent>
#include <QPixmap>
#include <QBitmap>

const static QColor defaultColor(200, 200, 200, 80);

QTBackgroundWidget::QTBackgroundWidget(QWidget* parent /* = NULL */)
	:QWidget(parent)
	, m_color(defaultColor)
	, m_maskImagePath("")
{

}

QTBackgroundWidget::~QTBackgroundWidget()
{

}

void
QTBackgroundWidget::backGroundColor(const QColor& color)
{
	m_color = color;
	setColorStyle(m_color);
}

const QColor& 
QTBackgroundWidget::backGroundColor() const
{
	return m_color;
}

void 
QTBackgroundWidget::maskImage(const QString& maskImage)
{
	m_maskImagePath = maskImage;
	setMaskImage(this->rect().size());
}

void 
QTBackgroundWidget::init()
{

}

void
QTBackgroundWidget::resizeEvent(QResizeEvent * resizeEvent)
{
	setMaskImage(resizeEvent->size());
}

void 
QTBackgroundWidget::setColorStyle(const QColor& color)
{

	QVariant red(m_color.red());
	QVariant green(m_color.green());
	QVariant blue(m_color.blue());
	QVariant alpha(m_color.alpha());
	QString colorStyle = "background-color:rgba(" + red.toString() + ", " + green.toString() + ", " + blue.toString() + ", "
						+ alpha.toString() + ")";
	  
	setStyleSheet(colorStyle);
	update();
}

void 
QTBackgroundWidget::setMaskImage(const QSize& size)
{
	QPixmap maskImage(m_maskImagePath);
	setMask(maskImage.createMaskFromColor(Qt::white));
	update();
}