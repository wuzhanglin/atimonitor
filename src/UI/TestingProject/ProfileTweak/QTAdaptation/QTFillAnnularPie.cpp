#include "QTFillAnnularPie.h"

#include <QPolygon>
#include <QRegion>
#include <QResizeEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QVBoxLayout>
#include <QProgressBar>
#include <QtMath>
#include <QBitmap>
#include <QStyleOption>
#include <QStylePainter>

const static int Offset_X = 20;
const static int Offset_Y = 5;
const static int nDefaultWidth = 800;
const static int nDefaultHeight = 600;

QTFillAnnularPie::QTFillAnnularPie(QWidget* parent /* = NULL */)
	:QWidget(parent)
{
	init();
}

QTFillAnnularPie::~QTFillAnnularPie()
{

}

void 
QTFillAnnularPie::init()
{
	resize(nDefaultWidth, nDefaultHeight);

    this->setStyleSheet("background-color:rgba(100, 10, 10, 100)");
}

void 
QTFillAnnularPie::resizeEvent(QResizeEvent* event)
{
	QWidget::resizeEvent(event);

	QRect editRect(Offset_X, 0, rect().width() - 2 * Offset_X, rect().height());

	//m_pLineEdit->setGeometry(editRect);

	int nWidth = event->size().width();
	int nHeight = event->size().height();

	// Create region polygon
	/*QPolygon regionPolygon;
	regionPolygon.setPoints(7, Offset_X, 0,
	nWidth, 0,
	nWidth, Offset_Y,
	nWidth - Offset_X, nHeight,
	0, nHeight,
	0, nHeight - Offset_Y,
	Offset_X, 0);

	QRegion widgetRegion(regionPolygon);

	this->setMask(widgetRegion);*/

    QPixmap pixmap(event->size());
    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillRect(pixmap.rect(), Qt::white);
    painter.setBrush(Qt::black);
    painter.drawRoundedRect(pixmap.rect(), 30, 30);
    setMask(pixmap.createMaskFromColor(Qt::white));
    update();
}

const int centerX = 400;
const int centerY = 400;
const int innerRadius = 400;
const int outerRadius = 370;
qreal startAngle = 155;
qreal sweepAngle = 50;

void 
QTFillAnnularPie::paintEvent(QPaintEvent* event)
{
	//QWidget::paintEvent(event);

    QStylePainter p(this);

    // Draw the background and border according to the style.
    QStyleOption opt;
    opt.initFrom(this);
    p.drawPrimitive(QStyle::PE_Widget, opt);


	QPainterPath path;

	// inner arc
	int innerX = centerX - innerRadius;
	int innerY = centerY - innerRadius;
	int innerW = 2 * innerRadius;
	int innerH = 2 * innerRadius;

	path.arcMoveTo(innerX, innerY, innerW, innerH, startAngle);
	path.arcTo(innerX, innerY, innerW, innerH, startAngle, sweepAngle);
	//path.arcMoveTo(innerX, innerY, innerW, innerH, startAngle);

	int outerStartX = centerX + outerRadius * qCos(qDegreesToRadians(startAngle + sweepAngle));
	int outerStartY = centerY - outerRadius * qSin(qDegreesToRadians(startAngle + sweepAngle));

	////path.moveTo(centerX, centerY);
	path.lineTo(outerStartX, outerStartY);

	int outerX = centerX - outerRadius;
	int outerY = centerY - outerRadius;
	int outerW = 2 * outerRadius;
	int outerH = 2 * outerRadius;

	//path.arcMoveTo(outerX, outerY, outerW, outerH, startAngle);
	path.arcTo(outerX, outerY, outerW, outerH, startAngle + sweepAngle, -sweepAngle);

	int innerEndX = centerX + innerRadius * qCos(qDegreesToRadians(startAngle));
	int innerEndY = centerY - innerRadius * qSin(qDegreesToRadians(startAngle));

	path.lineTo(innerEndX, innerEndY);

	//path.arcMoveTo(innerX, innerY, innerW, innerH, startAngle);

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	QPen pen(QColor(255, 0, 0, 100));
	pen.setWidthF(3);
	painter.setPen(pen);
	painter.setRenderHint(QPainter::Antialiasing);

	painter.fillPath(path, QBrush(QColor(255, 0, 0, 255)));
	painter.drawPath(path);

	painter.save();
	painter.translate(300, 300);
	painter.rotate(90);
	painter.drawText(0, 0, "This is a example.");
	painter.restore();

	painter.drawEllipse(QPoint(300, 300), 100, 100);

	//painter.drawText(300, 300, "This is the result.");
	float angle = 240;
	painter.save();
	//painter.translate(300, 300);
	//painter.rotate(90 + angle);
	//painter.moveTo(300, 300);
	painter.drawLine(300, 300, 300 + 100 * qCos(qDegreesToRadians(360.0 - angle)), 300 -100 * qSin(qDegreesToRadians(360.0 - angle)));
	painter.translate(300 + 100 * qCos(qDegreesToRadians(360.0 - angle)), 300 -100 * qSin(qDegreesToRadians(360.0 - angle)));
	painter.rotate(angle + 90);
	painter.drawText(0, 0, "This is sample");
	painter.restore();

	int nWidth = rect().width();
	int nHeight = rect().height();

	QPolygon regionPolygon;
	regionPolygon.setPoints(7, Offset_X, 0,
		nWidth, 0,
		nWidth, Offset_Y,
		nWidth - Offset_X, nHeight,
		0, nHeight,
		0, nHeight - Offset_Y,
		Offset_X, 0);
	painter.drawPolygon(regionPolygon);

}
