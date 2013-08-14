#ifndef QT_TRANSPARENT_PUSHBUTTON_H
#define QT_TRANSPARENT_PUSHBUTTON_H

#include <QPushButton>

class QTTransparentPushButton : public QPushButton
{
public:
    QTTransparentPushButton(QWidget* parent = NULL);
    QTTransparentPushButton(const QString& text, QWidget* parent = NULL);
    QTTransparentPushButton(const QIcon& icon, const QString& text, QWidget* parent = NULL);
    ~QTTransparentPushButton();

private:
    void init();
};

#endif