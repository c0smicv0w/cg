#include <stdio.h>
#include <gl/glew.h>
#include <gl/glut.h>
#pragma comment(lib, "glew32.lib")

void myinit(void) {
	const char* strVersion = (char*)glGetString(GL_VERSION);
	printf("version = %s\n", strVersion);
	fflush(stdout);
}

void mydisplay(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}


int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitWindowSize(200, 200);
	glutCreateWindow("simple");
	glewInit();
	myinit();
	glutDisplayFunc(mydisplay);
	glutMainLoop();
	return 0;
}