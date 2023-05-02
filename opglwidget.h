#include <QtWidgets/QOpenGLWidget>

class OPGLWidget : public QOpenGLWidget
{
public:
	OPGLWidget(QWidget *parent) : QOpenGLWidget(parent) {}
protected:
	void paintGL();
	void initializeGL();
	void resizeGL(int w, int h);
};
