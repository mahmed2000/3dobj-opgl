#include "opglwidget.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <QKeyEvent>

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

	obj.load_mtl("untitled.mtl");
	obj.load_obj("untitled.obj");
}

void OPGLWidget::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	reorient();
	glPolygonMode(GL_FRONT, GL_FILL);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < obj.faces.size(); i++) {
		Material* mtl_ptr = obj.faces[i].mtl;
		if (mtl_idx != mtl_ptr->idx) {
			glMaterialfv(GL_FRONT, GL_AMBIENT, mtl_ptr -> ambient);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mtl_ptr -> diffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mtl_ptr -> specular);
			glMaterialf(GL_FRONT, GL_SHININESS, {128.0f});
			mtl_idx =mtl_ptr->idx;
		};
		for (int j = 0; j < 3; j++) {
			glVertex3fv(obj.faces[i].vertices[j] -> pos);
			glNormal3fv(obj.faces[i].normals[j] -> dir);
		};
	};
	glEnd();
	glFlush();
	update();
}

void OPGLWidget::reorient() {
	GLfloat s[] = {-f[2], 0, f[0]};
	float s_mag = pow(pow(s[0], 2) + pow(s[1], 2) + pow(s[2], 2), 0.5);

	GLfloat u[] = {(s[1] * f[2] - s[2] * f[1]) / s_mag, -(s[0] * f[2] - s[2] * f[0]) / s_mag, (s[0] * f[1] - s[1] * f[0]) / s_mag};

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
	glFrustum(-right, right, -top, top, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
}

void OPGLWidget::update_camera() {
	for (int i = 0; i < 3; i++) {
		loc[i] += vel[i] * speed/100.0f;
	};
	if (key_states[0]) {
		for (int i = 0; i < 3; i++) {
			vel[i] += f[i];
		}
	};
	if (key_states[1]) {
		for (int i = 0; i < 3; i++) {
			vel[i] -= f[i];
		}
	};
	if (key_states[2]) {
		for (int i = 0; i < 3; i++) {
			vel[i] += right[i];
		}
	};
	if (key_states[3]) {
		for (int i = 0; i < 3; i++) {
			vel[i] -= right[i];
		}
	};
	if (key_states[4]) {
		for (int i = 0; i < 3; i++) {
			vel[i] += up[i];
		}
	};
	if (key_states[5]) {
		for (int i = 0; i < 3; i++) {
			vel[i] -= up[i];
		}
	};
	speed = pow(pow(vel[0], 2) + pow(vel[1], 2) + pow(vel[2], 2), 0.5);
	if (speed > 2) {
		for (int i = 0; i < 3; i++) {
			vel[i] = vel[i] / speed;
		}
	}
	bool allFalse = true;
	for (int i = 0; i < 6; i++) {
		if (key_states[i]) {
			allFalse = false;
			break;
		}
	}
	if (allFalse) {
		for (int i = 0; i < 3; i++) {
			if (speed > 0.1f) {
				vel[i] -= vel[i] * speed / 10.0f;
			} else {
				vel[i] = 0.0f;
			}
		}
	}
}

void OPGLWidget::keyPressEvent(QKeyEvent *event) {
	switch (event -> key()) {
		case Qt::Key_W:
			key_states[0] = true;
			break;
		case Qt::Key_S:
			key_states[1] = true;
			break;
		case Qt::Key_D:
			key_states[2] = true;
			break;
		case Qt::Key_A:
			key_states[3] = true;
			break;
		case Qt::Key_Space:
			key_states[4] = true;
			break;
		case Qt::Key_Control:
			key_states[5] = true;
			break;
	};
}

void OPGLWidget::keyReleaseEvent(QKeyEvent *event) {
	switch (event -> key()) {
		case Qt::Key_W:
			key_states[0] = false;
			break;
		case Qt::Key_S:
			key_states[1] = false;
			break;
		case Qt::Key_D:
			key_states[2] = false;
			break;
		case Qt::Key_A:
			key_states[3] = false;
			break;
		case Qt::Key_Space:
			key_states[4] = false;
			break;
		case Qt::Key_Control:
			key_states[5] = false;
			break;
	};
}


