#include "QTLineEdit.h"

#include <QPolygon>
#include <QRegion>
#include <QResizeEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QBitmap>
#include <QPalette>
#include <QPushButton>
#include <QApplication>

#include <QVBoxLayout>

#include "QTIrregularCheckablePushButton.h"
#include "QTFillAnnularPie.h"
#include <QStyleOption>
#include <QStylePainter>

//QExtendLineEdit
//////////////////////////////////////////////////////////////////////////
QExtendLineEdit::QExtendLineEdit(QWidget* parent)
	:QLineEdit(parent)
{

}

QExtendLineEdit::~QExtendLineEdit()
{

}

void 
QExtendLineEdit::paintEvent(QPaintEvent* event)
{
	QLineEdit::paintEvent(event);

	// Over paint the border to white to make it invisible.
	QPainter painter(this);
	QPen pen(Qt::white);
	pen.setWidth(2);
	painter.setPen(pen);
	painter.drawLine(0, 0, rect().width(), 0);
	painter.drawLine(rect().width() - 1, 0, rect().width() - 1, rect().height());
	painter.drawLine(rect().width(), rect().height(), 0, rect().height());
	painter.drawLine(0 + 1, rect().height(), 0 + 1, 0);
}

const static int Offset_X = 20;
const static int Offset_Y = 5;
const static int nDefaultWidth = 100;
const static int nDefaultHeight = 24;

QTLineEdit::QTLineEdit(QWidget* parent /* = NULL */)
    :QWidget(parent)
    , m_pLineEdit(NULL)
{
    init();
}

QTLineEdit::~QTLineEdit()
{

}


void 
QTLineEdit::init()
{
    // No frames
    this->setWindowFlags(Qt::FramelessWindowHint);

    // Transparent
    this->setAttribute(Qt::WA_TranslucentBackground);

    // Input line edit
    //m_pLineEdit = new QExtendLineEdit(this);

    //resize(nDefaultWidth, nDefaultHeight);
	/*	QString strPath = qApp->applicationDirPath();
		QPalette p = palette();
		QPixmap* pImg = new QPixmap("E:/project/ProfileTweak/ProfileTweak/Resources/a.png");
		QBitmap* pMask = new QBitmap("E:/project/ProfileTweak/ProfileTweak/Resources/mask.png");
		p.setBrush(backgroundRole(), QBrush(*pImg));
		setPalette(p);
		setMask(*pMask);*/

	//setWindowFlags(Qt::FramelessWindowHint);
	//resize(600, 400);

	//setWindowFlags(Qt::FramelessWindowHint);///去掉标题栏  

	//=========================半透明窗体==========================================  
		///移除所有能移除的,包括状态栏,标题栏,工具栏什么的  

		//setAttribute(Qt::WA_TranslucentBackground, true);  
	//this->setStyleSheet("border-image:url(background.png) 10 10 10 10 stretch stretch;");  ///使用border-image可以实现背景的拉伸  
	//this->setStyleSheet("background-image::url(E:/project/ProfileTweak/ProfileTweak/Resources/007.png);");     
	
    //resize(800, 600);

	//QWidget w(this);
	//w.setWindowOpacity(0.5);
	//w.resize(400, 300);
	//w.show();
    QVBoxLayout* pMainLayout = new QVBoxLayout();
    QTIrregularCheckablePushButton* pNewWidget =  new QTIrregularCheckablePushButton("Wolfe");
   
    /*  pNewWidget->setStyleSheet("QTIrregularCheckablePushButton{background-color: rgba(204, 204, 204, 80%);"
    "border-top-left-radius: 0px;"
    "border-top-right-radius: 0px;"
    "border-bottom-right-radius: 6px;"
    "border-bottom-left-radius: 6px;"
    "padding: 0px;"
    "border-style: solid;"
    "border-width: 1px 1px 1px 1px;" 
    "border-color: rgba(119, 119, 119, 140);}");*/
    //pNewWidget->resize(400, 300);

	this->resize(600, 400);
	pMainLayout->addWidget(pNewWidget);
	pMainLayout->addWidget(new QTFillAnnularPie());

    this->setLayout(pMainLayout);

	//this->adjustSize();

   // resize(800, 600);
    //setStyleSheet("{background-color: rgba(204, 204, 204, 50%);");

	///使用标准的 background-image ,适用于固定窗体,PNG图片要与窗口尺寸相等  
	
}

void 
QTLineEdit::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);

	//QRect editRect(Offset_X, 0, rect().width() - 2 * Offset_X, rect().height());
	//m_pLineEdit->setGeometry(editRect);

    //int nWidth = event->size().width();
    //int nHeight = event->size().height();

    //// Create region polygon
    //QPolygon regionPolygon;
    //regionPolygon.setPoints(7, Offset_X, 0,
    //                           nWidth, 0,
    //                           nWidth, Offset_Y,
    //                           nWidth - Offset_X, nHeight,
    //                           0, nHeight,
    //                           0, nHeight - Offset_Y,
    //                           Offset_X, 0);

    //QRegion widgetRegion(regionPolygon);

    //this->setMask(widgetRegion);
}

void 
QTLineEdit::paintEvent(QPaintEvent* event)
{
    QWidget::paintEvent(event);
    
    //QStylePainter p(this);

    //// Draw the background and border according to the style.
    //QStyleOption opt;
    //opt.initFrom(this);
    //p.drawPrimitive(QStyle::PE_Widget, opt);

    //QPainter painter(this);

    //painter.setRenderHint(QPainter::Antialiasing);
    //QPixmap pic("C:/Users/wolfe/Desktop/ATIGPUMonitor/src/UI/TestingProject/ProfileTweak/Resources/102.png");
    //painter.setBackgroundMode(Qt::TransparentMode);
    //painter.drawPixmap(0,0, pic);

   /* painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QColor(0, 255, 0, 150));
    painter.setBrush(QColor(0, 255, 0, 150));
    painter.drawRoundedRect(rect(),50, 50);

    painter.setCompositionMode(QPainter::CompositionMode_Source);

    QPixmap pixmap(QSize(300, 300));
    QPainter painterBmp(&pixmap);
    painterBmp.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painterBmp.setRenderHint(QPainter::Antialiasing, true);
    painterBmp.fillRect(QRect(100, 100, 200, 200), Qt::red);
    painter.drawPixmap(0, 0, pixmap);
*/
	/*int nWidth = rect().width();
	int nHeight = rect().height();

	QPolygon regionPolygon;
	regionPolygon.setPoints(7, Offset_X, 0,
	nWidth, 0,
	nWidth, Offset_Y,
	nWidth - Offset_X, nHeight,
	0, nHeight,
	0, nHeight - Offset_Y,
	Offset_X, 0);

	QPen pen(Qt::white);
	QBrush brush(Qt::white);
	painter.setPen(pen);
	painter.setBrush(brush);
	painter.drawPolygon(regionPolygon);*/
}
