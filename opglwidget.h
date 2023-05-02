#include <QtWidgets/QOpenGLWidget>

class OPGLWidget : public QOpenGLWidget
{
public:
	OPGLWidget(QWidget *parent) : QOpenGLWidget(parent) {}
};
