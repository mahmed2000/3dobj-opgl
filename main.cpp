#include <QtWidgets/QApplication>
#include <QMainWindow>
#include <QTimer>
#include "ui_mainwindow.h"

int main(int argc, char **argv) {
	QApplication app(argc, argv);
	QMainWindow w;
	Ui::MainWindow ui;
	ui.setupUi(&w);
	QTimer timer_draw;
	QTimer timer_cam;
	w.connect(&timer_draw, SIGNAL(timeout()), ui.openGLWidget, SLOT(paintGL()));
	w.connect(&timer_cam, SIGNAL(timeout()), ui.openGLWidget, SLOT(update_camera()));
	timer_draw.start(16);
	timer_cam.start(16);
	w.show();
	return app.exec();
}
