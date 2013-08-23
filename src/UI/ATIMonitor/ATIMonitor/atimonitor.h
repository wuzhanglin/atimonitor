#ifndef ATIMONITOR_H
#define ATIMONITOR_H

#include <QtWidgets/QMainWindow>
#include "ui_atimonitor.h"

class ATIMonitor : public QMainWindow
{
	Q_OBJECT

public:
	ATIMonitor(QWidget *parent = 0);
	~ATIMonitor();

private:
	Ui::ATIMonitorClass ui;
};

#endif // ATIMONITOR_H
