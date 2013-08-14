#include "QTAdaptation/QTLineEdit.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTLineEdit w;
	//QWidget w;
	w.setWindowOpacity(0.5);
    w.show();
    return a.exec();
}
