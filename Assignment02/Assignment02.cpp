#include <gl/glew.h>
#include <gl/glut.h>
#pragma comment(lib, "glew32.lib")
#define GLEW_STATIC

GLuint vs = 0;
GLuint fs = 0;
GLuint prog = 0;

static char* vsSource = "#version 120 \n\
attribute vec4 vertex; \n\
void main(void) { \n\
  gl_Position = vertex; \n\
}";

static char* fsSource = "#version 120 \n\
void main(void) { \n\
  gl_FragColor = vec4(1.0, 1.0, 0.0, 1.0); \n\
}";

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

void mykeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
		exit(0);
		break;
	}
}

GLfloat vertices[] = {
	-0.6, -0.6, 0.0, 1.0,
	+0.4, -0.6, 0.0, 1.0,
	-0.6, +0.4, 0.0, 1.0,
	+0.6, +0.6, 0.0, 1.0,
	-0.4, +0.6, 0.0, 1.0,
	+0.6, -0.4, 0.0, 1.0,
};


void mydisplay(void) {
	GLuint loc;
	glClearColor(0.2F, 0.2F, 0.8F, 1.0F);
	glClear(GL_COLOR_BUFFER_BIT);

	loc = glGetAttribLocation(prog, "vertex");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, vertices);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glFlush();
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("simple");
	glutDisplayFunc(mydisplay);
	glutKeyboardFunc(mykeyboard);
	glewInit();
	myinit();
	glutMainLoop();
	return 0;
}