#include "opglwidget.h"
#include <GL/gl.h>
#include <math.h>

void OPGLWidget::initializeGL() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void OPGLWidget::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT);
}

void OPGLWidget::resizeGL(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float aspect = w / float(h);
	float top = 0.2f * tan(M_PI / 8);
	float right = 0.2f * tan(M_PI / 8) * aspect;
	glFrustum(-right , right, -top, top, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
}
