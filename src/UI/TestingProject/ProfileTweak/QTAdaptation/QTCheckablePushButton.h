#ifndef QT_CHECKABLE_PUSHBUTTON_H
#define QT_CHECKABLE_PUSHBUTTON_H

#include "QTTransparentPushButton.h"

class QTCheckablePushButton : public QTTransparentPushButton
{
public:
    QTCheckablePushButton(QWidget* parent = NULL);
    QTCheckablePushButton(const QString& text, QWidget* parent = NULL);
    QTCheckablePushButton(const QIcon& icon, const QString& text, QWidget* parent = NULL);
    ~QTCheckablePushButton();

private:
    void init();
};

#endif