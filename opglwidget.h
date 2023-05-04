#include <QtWidgets/QOpenGLWidget>
#include "obj.h"
#include <QKeyEvent>
#include <QMouseEvent>

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

	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);

	int mtl_idx = -1;
	float loc[3] = {0, 0, 10};
	float f[3] = {0, 0, -1};
	float up[3] = {0, 1, 0};
	float right[3] = {1, 0, 0};
	float vel[3] = {0, 0, 0};
	float speed = 0;
	ObjectLoader obj;
	bool key_states[6] = {false, false, false, false, false, false};
	float mouse_loc_old[2];
};
