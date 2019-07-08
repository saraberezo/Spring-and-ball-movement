#include "stdafx.h"
#include <Windows.h>
#include "include\GL\GL.H"
#include "include\GL\GLU.H"
#include "include\GL\glut.h"
#include <math.h>

#define PI 3.14159265

double rotate_y = 0;
double rotate_x = 0;
int dir = 1;
float heigh = 0.6;


// Function to rotate project with keys
void specialKeys(int key, int x, int y) {

	if (key == GLUT_KEY_RIGHT)
		rotate_y += 5;

	else if (key == GLUT_KEY_LEFT)
		rotate_y -= 5;

	else if (key == GLUT_KEY_UP)
		rotate_x += 5;

	else if (key == GLUT_KEY_DOWN)
		rotate_x -= 5;

}


// Timer to rotate
void timer(int a) {

	if (dir == 0) {
		heigh -= 0.06;
	}
	if (dir == 1) {
		heigh += 0.06;
	}

	glutPostRedisplay();

}


// Function to load texture images
GLuint LoadTexture(const char * filename, int width, int height) {

	GLuint texture;
	unsigned char * data;

	FILE * file;
	errno_t err = fopen_s(&file, filename, "rb");

	if (file == NULL) return 0;
	data = (unsigned char *)malloc(width * height * 3);
	fread(data, width * height * 3, 1, file);
	fclose(file);

	for (int i = 0; i < width * height; ++i)
	{
		int index = i * 3;
		unsigned char B, R;
		B = data[index];
		R = data[index + 2];

		data[index] = R;
		data[index + 2] = B;

	}

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
	free(data);

	return texture;
}





void MyDisplay(void) {

	glPushMatrix();

	//  Clear the screen and Z-buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// The new scene
	glLoadIdentity();

	glTranslatef(0, 20.0, -20.0f);

	glRotatef(rotate_x, 1.0, 0.0, 0.0);
	glRotatef(rotate_y, 0.0, 1.0, 0.0);

	// Texture for table
	GLuint texture;
	texture = LoadTexture("textures/wood.bmp", 320, 160);
	glBindTexture(GL_TEXTURE_2D, texture);

	// DESK
	// Front side
	glBegin(GL_POLYGON);
	glTexCoord2i(1, 0); glVertex3f(14, -5, -15);
	glTexCoord2i(1, 1); glVertex3f(14, 5, -15);
	glTexCoord2i(0, 1); glVertex3f(-14, 5, -15);
	glTexCoord2i(0, 0); glVertex3f(-14, -5, -15);
	glEnd();

	// Back side
	glBegin(GL_POLYGON);
	glTexCoord2i(1, 0); glVertex3f(14, -5, -30);
	glTexCoord2i(1, 1); glVertex3f(14, 5, -30);
	glTexCoord2i(0, 1); glVertex3f(-14, 5, -30);
	glTexCoord2i(0, 0); glVertex3f(-14, -5, -30);
	glEnd();

	// Right side
	glBegin(GL_POLYGON);
	glTexCoord2i(1, 0); glVertex3f(14, -5, -30);
	glTexCoord2i(1, 1); glVertex3f(14, 5, -30);
	glTexCoord2i(0, 1); glVertex3f(14, 5, -15);
	glTexCoord2i(0, 0); glVertex3f(14, -5, -15);
	glEnd();

	// Left side
	glBegin(GL_POLYGON);
	glTexCoord2i(1, 0); glVertex3f(-14, -5, -15);
	glTexCoord2i(1, 1); glVertex3f(-14, 5, -15);
	glTexCoord2i(0, 1); glVertex3f(-14, 5, -30);
	glTexCoord2i(0, 0); glVertex3f(-14, -5, -30);
	glEnd();
	
	// Top side
	glBegin(GL_POLYGON);
	glTexCoord2i(1, 0); glVertex3f(14, 5, -15);
	glTexCoord2i(1, 1); glVertex3f(14, 5, -30);
	glTexCoord2i(0, 1); glVertex3f(-14, 5, -30);
	glTexCoord2i(0, 0); glVertex3f(-14, 5, -15);
	glEnd();

	// Bottom side
	glBegin(GL_POLYGON);
	glTexCoord2i(1, 0); glVertex3f(14, -5, -30);
	glTexCoord2i(1, 1); glVertex3f(14, -5, -15);
	glTexCoord2i(0, 1); glVertex3f(-14, -5, -15);
	glTexCoord2i(0, 0); glVertex3f(-14, -5, -30);
	glEnd();


	glTranslatef(0, -5, (-15 - 30) / 2);
	glRotatef(90, 1, 0, 0);

	// Texture for cylinder (the one that join the table and the sprint)
	GLuint texture2;
	texture2 = LoadTexture("textures/bricks.bmp", 540, 540);
	glBindTexture(GL_TEXTURE_2D, texture2);


	// CYLINDER
	glBegin(GL_POLYGON);

	GLUquadric* cylinder;
	cylinder = gluNewQuadric();
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluQuadricTexture(cylinder, GL_TRUE);
	gluQuadricNormals(cylinder, GLU_SMOOTH);

	gluCylinder(cylinder, 3.0, 3.0, 8.0, 50, 50);
	glEnd();

	glTranslatef(-1.5, 0.0, 8.0);


	// Texture for the sprint
	GLuint texture3;
	texture3 = LoadTexture("textures/metal.bmp", 275, 183);
	glBindTexture(GL_TEXTURE_2D, texture3);

	// SPRINT
	glBegin(GL_QUAD_STRIP);

	float t_esphere = 0.0;

	for (float t = 0; t < 8 * PI; t += 0.1) {

		for (float u = 0; u < 2 * PI; u += 0.1) {
			float x1 = cos(t) * (3 + cos(u));
			float y1 = sin(t) * (3 + cos(u));
			float z1 = heigh * t + sin(u);

			float x2 = cos(t + 0.1) * (3 + cos(u));
			float y2 = sin(t + 0.1) * (3 + cos(u));
			float z2 = heigh * (t + 0.1) + sin(u);

			glTexCoord2i(0, 0); glVertex3d(x1, y1, z1);
			glTexCoord2i(0, 1); glVertex3d(x2, y2, z2);

			t_esphere = z2;
		}

	}
	glEnd();

	if (heigh < 0.6) {
		dir = 1;
	}
	if (heigh > 3.0) {
		dir = 0;
	}

	glTranslatef(0.0, 0.0, t_esphere + 8.0);

	// Texture for the sphere
	GLuint texture4;
	texture4 = LoadTexture("textures/color.bmp", 960, 640);
	glBindTexture(GL_TEXTURE_2D, texture4);

	// SPHERE
	glBegin(GL_POLYGON);
	GLUquadric* sphere;
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, GL_TRUE);
	gluQuadricNormals(sphere, GLU_SMOOTH);

	gluSphere(sphere, 8.0, 50, 50);

	glEnd();

	glPopMatrix();

	
	// The end of scene
	glFlush();//start processing buffered OpenGL routines
	glutTimerFunc(10, timer, 0); // Timer in milliseconds
}


void MyInit(void) {
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST); // It test each pixel and decide if it must be shown or not
	glClearColor(0.0, 0.0, 0.0, 0.0);//select clearing (background) color
									 /* initialize viewing values */
	glViewport(0, 0, 300, 300);//window origin and size
	glMatrixMode(GL_PROJECTION);//
	glLoadIdentity();//=1
	gluPerspective(140.0f, (float)(16 / 9), 0.1f, 500.0f);
	/*
	void gluPerspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar);
		fovy: Specifies the field of view angle, in degrees, in the y direction.
		aspect: Specifies the aspect ratio that determines the field of view in the x direction.The aspect ratio is the ratio of x(width) to y(height).
		zNear: Specifies the distance from the viewer to the near clipping plane(always positive).
		zFar: Specifies the distance from the viewer to the far clipping plane(always positive).
	*/
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();//=1
}

int main(int argc, char** argv) { //<- for normal API
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);//single buffer and RGBA
	glutInitWindowSize(500, 500);//initial window size
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Sprint");//create widnow, hello title bar
	MyInit();
	glutDisplayFunc(MyDisplay);
	glutSpecialFunc(specialKeys);
	glutMainLoop();//enter main loop and process events
	return 0;
}