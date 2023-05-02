#include "opglwidget.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

void OPGLWidget::initializeGL() {
	glClearDepth(1.0f);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat light_array[] = {0.4, 0.4, 0.4, 0.4};
	GLfloat light_position[] = {10.0, 20.0, 10.0, 1.0};
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_array);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_array);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_array);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void OPGLWidget::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	reorient();
}

void OPGLWidget::reorient() {
	float F_mag = pow(loc[0], 2) + pow(loc[1], 2) +pow(loc[2], 2);
	GLfloat f[] = {-loc[0]/F_mag, -loc[1] / F_mag, -loc[2] / F_mag};

	GLfloat s[] = {-f[2], 0, f[0]};
	float s_mag = pow(s[0], 2) + pow(s[1], 2) + pow(s[2], 2);

	GLfloat u[] = {(s[1] * f[2] - s[2] * f[1]) / s_mag, (s[0] * f[2] - s[2] * f[0]) / s_mag, (s[0] * f[1] - s[1] * f[0]) / s_mag};

	const GLfloat m[] = {s[0], u[0], -f[0], 0, s[1], u[1], -f[1], 0, s[2], u[2], -f[2], 0, 0, 0, 0, 1};
	glMultMatrixf(m);
	glTranslatef(-loc[0], -loc[1], -loc[2]);
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
