#include "QTTransparentPushButton.h"

QTTransparentPushButton::QTTransparentPushButton(QWidget* parent /* = NULL */)
    : QPushButton(parent)
{
    init();
}

QTTransparentPushButton::QTTransparentPushButton(const QString& text, QWidget* parent /* = NULL */)
    : QPushButton(text, parent)
{
    init();
}

QTTransparentPushButton::QTTransparentPushButton(const QIcon& icon, const QString& text, QWidget* parent /* = NULL */)
    : QPushButton(icon, text, parent)
{
    init();
}

QTTransparentPushButton::~QTTransparentPushButton()
{

}

void 
QTTransparentPushButton::init()
{
    // Transparent background
    //setStyleSheet("background-color:transparent");
}