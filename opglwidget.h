#include <QtWidgets/QOpenGLWidget>
#include "obj.h"

class OPGLWidget : public QOpenGLWidget
{
	Q_OBJECT
public:
	OPGLWidget(QWidget *parent) : QOpenGLWidget(parent) {}
public slots:
	void paintGL();
	void update_camera();
protected:
	void initializeGL();
	void resizeGL(int w, int h);
	void reorient();

	int mtl_idx = -1;
	float loc[3] = {0, 0, 10};
	float f[3] = {0, 0, -1};
	float vel[3] = {0, 0, -0.01};
	ObjectLoader obj;
};
