#include "QTCheckablePushButton.h"

QTCheckablePushButton::QTCheckablePushButton(QWidget* parent /* = NULL */)
    : QTTransparentPushButton(parent)
{
    init();
}

QTCheckablePushButton::QTCheckablePushButton(const QString& text, QWidget* parent /* = NULL */)
    : QTTransparentPushButton(text, parent)
{
    init();
}

QTCheckablePushButton::QTCheckablePushButton(const QIcon& icon, const QString& text, QWidget* parent /* = NULL */)
    : QTTransparentPushButton(icon, text, parent)
{
    init();
}

QTCheckablePushButton::~QTCheckablePushButton()
{

}

void 
QTCheckablePushButton::init()
{
    // Set checkable
    this->setCheckable(true);
}