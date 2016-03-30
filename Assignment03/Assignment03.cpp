#include <gl/glew.h>
#pragma comment(lib, "glew32.lib")
#include <gl/glut.h>
#include <stdio.h>
#include <stdlib.h>


static char* vsSource = "#version 120 \n\
attribute vec4 vertex; \n\
void main(void) { \n\
  gl_Position = vertex; \n\
}";

static char* fsSource = "#version 120 \n\
void main(void) { \n\
  gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0); \n\
}";

GLfloat plane0[] = {
	-0.2F, -0.8F, 0.0F, 1.0F,
	+0.2F, -0.8F, 0.0F, 1.0F,
	+0.0F, -0.5F, 0.0F, 1.0F,
};

GLfloat plane1[] = {
	-0.2F, -0.8F, 0.0F, 1.0F,
	+0.2F, -0.8F, 0.0F, 1.0F,
	+0.0F, -0.5F, 0.0F, 1.0F,
};

GLfloat stone0[] = {
	-0.5F, +0.9F, 0.0F, 1.0F,
	-0.5F, +0.8F, 0.0F, 1.0F,
	-0.4F, +0.8F, 0.0F, 1.0F,
};

GLfloat stone1[] = {
	-0.5F, +0.9F, 0.0F, 1.0F,
	-0.5F, +0.8F, 0.0F, 1.0F,
	-0.4F, +0.8F, 0.0F, 1.0F,
};

GLuint vs = 0;
GLuint fs = 0;
GLuint prog = 0;
const float planeStep = 0.04F;
const float stoneStep = 0.01F;

void myidle(void) {
	Sleep(100);
	stone1[1] -= stoneStep;
	stone1[5] -= stoneStep;
	stone1[9] -= stoneStep;
	if (stone1[9] < -1.0F) {
		memcpy(stone1, stone0, sizeof(stone0));
	}
	glutPostRedisplay();
}

void mykeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27: exit(0); break;
	case 'r':
		memcpy(plane1, plane0, sizeof(plane0));
		glutPostRedisplay();
		break;
	case 'a':
		plane1[0] -= planeStep;
		plane1[4] -= planeStep;
		plane1[8] -= planeStep;
		glutPostRedisplay();
		break;
	case 'd':
		plane1[0] += planeStep;
		plane1[4] += planeStep;
		plane1[8] += planeStep;
		glutPostRedisplay();
		break;
	case 32:
		break;
	}
}

void myinit(void) {
	vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vsSource, NULL);
	glCompileShader(vs);

	fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fsSource, NULL);
	glCompileShader(fs);

	prog = glCreateProgram();
	glAttachShader(prog, vs);
	glAttachShader(prog, fs);
	glLinkProgram(prog);
	glUseProgram(prog);
}

void mydisplay(void) {
	GLuint loc;

	glClearColor(0.3, 0.3, 0.3, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	loc = glGetAttribLocation(prog, "vertex");
	glEnableVertexAttribArray(loc);

	glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, plane1);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, stone1);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glFlush();
	glutSwapBuffers();
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("game");
	glutDisplayFunc(mydisplay);
	glutKeyboardFunc(mykeyboard);
	glutIdleFunc(myidle);
	glewInit();
	myinit();
	glutMainLoop();
	return 0;
}
