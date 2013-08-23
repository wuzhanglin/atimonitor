#include "atimonitor.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ATIMonitor w;
	w.show();
	return a.exec();
}
