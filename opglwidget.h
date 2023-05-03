#include <QtWidgets/QOpenGLWidget>
#include "obj.h"

class OPGLWidget : public QOpenGLWidget
{
public:
	OPGLWidget(QWidget *parent) : QOpenGLWidget(parent) {}
protected:
	void paintGL();
	void initializeGL();
	void resizeGL(int w, int h);
	void reorient();

	int mtl_idx = -1;
	float loc[3] = {0, 0, 10};
	float f[3] = {0, 0, -1};
	ObjectLoader obj;
};
