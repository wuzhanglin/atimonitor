#ifndef QT_IRREGULAR_CHECKABLE_PUSHBUTTON_H
#define QT_IRREGULAR_CHECKABLE_PUSHBUTTON_H

#include "QTCheckablePushButton.h"

class QTIrregularCheckablePushButton : public QTCheckablePushButton
{
public:
    QTIrregularCheckablePushButton(QWidget* parent = NULL);
    QTIrregularCheckablePushButton(const QString& text, QWidget* parent = NULL);
    QTIrregularCheckablePushButton(const QIcon& icon, const QString& text, QWidget* parent = NULL);
    ~QTIrregularCheckablePushButton();

protected:
    virtual void paintEvent(QPaintEvent* pEvent);
    virtual void resizeEvent(QResizeEvent* pEvent);

private:
    void init();
};

#endif