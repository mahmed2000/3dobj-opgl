#include <QtWidgets/QApplication>
#include <QMainWindow>
#include <QTimer>
#include "include/ui_mainwindow.h"
#include <QCommandLineParser>
#include <QCommandLineOption>

int main(int argc, char **argv) {
	QApplication app(argc, argv);
	QCommandLineParser parser;
	QCommandLineOption mtl_filepath_opt({"m", "material"}, "Material file path", "path");
	QCommandLineOption obj_filepath_opt({"o", "object"}, "Object file path", "path");
	parser.addOption(mtl_filepath_opt);
	parser.addOption(obj_filepath_opt);
	parser.process(app);
	QString mtl_filepath = parser.value(mtl_filepath_opt);
	QString obj_filepath = parser.value(obj_filepath_opt);
	if (mtl_filepath.isEmpty() || obj_filepath.isEmpty()) {
		return -1;
	}
	QMainWindow w;
	Ui::MainWindow ui;
	ui.setupUi(&w);
	ui.openGLWidget->obj.load_mtl(mtl_filepath.toStdString());
	ui.openGLWidget->obj.load_obj(obj_filepath.toStdString());

	QTimer timer_draw;
	QTimer timer_cam;
	w.connect(&timer_draw, SIGNAL(timeout()), ui.openGLWidget, SLOT(paintGL()));
	w.connect(&timer_cam, SIGNAL(timeout()), ui.openGLWidget, SLOT(update_camera()));
	timer_draw.start(16);
	timer_cam.start(16);
	w.show();
	return app.exec();
}
