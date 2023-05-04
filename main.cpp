#include <QtWidgets/QApplication>
#include <QMainWindow>
#include <QTimer>
#include "ui_mainwindow.h"

int main(int argc, char **argv) {
	QApplication app(argc, argv);
	QMainWindow w;
	Ui::MainWindow ui;
	ui.setupUi(&w);
	QTimer timer;
	w.connect(&timer, SIGNAL(timeout()), ui.openGLWidget, SLOT(paintGL()));
	timer.start(16);
	w.show();
	return app.exec();
}
