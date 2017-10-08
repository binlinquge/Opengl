#include<stdlib.h>
#include<stdio.h>
#include<GL/glut.h>

#define GLUT_WHEEL_UP 3
#define GLUT_WHEEL_DOWN 4

GLfloat vertices[][3] = { { -1.0,-1.0,-1.0 },{ 1.0,-1.0,-1.0 },{ 1.0,1.0,-1.0 },{ -1.0,1.0,-1.0 },{ -1.0,-1.0,1.0 },{ 1.0,-1.0,1.0 },{ 1.0,1.0,1.0 },{ -1.0,1.0,1.0 } };
GLfloat colors[][3] = { { 0.0,0.0,0.0 },{ 1.0,0.0,0.0 },{ 1.0,0.0,0.0 },{ 1.0,1.0,0.0 },{ 0.0,0.0,1.0 },{ 1.0,0.0,1.0 },{ 1.0,1.0,1.0 },{ 0.0,1.0,1.0 } };

GLfloat theta[] = { 0.0,0.0,0.0 };
GLfloat delta = 2;
GLint axis = 2;
float hight = 0;
float weight = 0;
float vert;
int x1, y1;
void spinCube()
{
	theta[axis] += delta;
	if (theta[axis]>360.0)
		theta[axis] -= 360.0;
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 'd')
		for (int i = 0; i < 8; i++)
		{
			vertices[i][0] += 0.1;
			hight += 0.1;
		}
	else if (key == 'a')
		for (int i = 0; i < 8; i++)
		{
			vertices[i][0] -= 0.1;
			hight -= 0.1;
		}
	else if (key == 'w')
		for (int i = 0; i < 8; i++)
		{
			vertices[i][1] += 0.1;
			weight += 0.1;
		}
	else if (key == 's')
		for (int i = 0; i < 8; i++)
		{
			vertices[i][1] -= 0.1;
			weight -= 0.1;
		}


	if (key == 'u')
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 3; j++)
				colors[i][j] += 0.1;
	else if (key == 'x')
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 3; j++)
				colors[i][j] -= 0.1;
	if (key == 'l')
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 3; j++)
			{
				if (vertices[i][j]<0)
					vertices[i][j] += 0.1;
				else vertices[i][j] -= 0.1;
			}
	else if (key == 'b')
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 3; j++)
			{
				if (vertices[i][j]>0)
					vertices[i][j] += 0.1;
				else vertices[i][j] -= 0.1;
			}
	if (key == 'q' || key == 'Q') exit(0);
	if (key == ' ')
		glutIdleFunc(NULL);
	else
		glutIdleFunc(spinCube);
}

void move(int x, int y)
{
			for (int i = 0; i < 8; i++)
			{
				vertices[i][0] += ((float)x - (float)x1) / 1000;
				hight += ((float)x - (float)x1) / 1000;
				vertices[i][1] -= (((float)y - (float)y1) / 1000 );
				weight -= (((float)y - (float)y1) / 1000);
			}
			x1 = x; y1 = y;
}
void mouse(int btn, int state, int x, int y)
{
	//mouse calback ,select an axis about which to rotate
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) { axis = 0; x1 = x; y1 = y;}
	if (btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) { axis = 1; x1 = x; y1 = y;}
	if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) { axis = 2; x1 = x; y1 = y;}
	if (btn == GLUT_WHEEL_UP && state == GLUT_UP) 
	{
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 3; j++)
				colors[i][j] += 0.1;
	}
	if (btn == GLUT_WHEEL_DOWN && state == GLUT_UP)
	{
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 3; j++)
				colors[i][j] -= 0.1;
	}
	glutIdleFunc(spinCube);
}

void face(int a, int b, int c, int d)
{
	glBegin(GL_POLYGON);
	glColor3fv(colors[a]);
	glVertex3fv(vertices[a]);
	glColor3fv(colors[b]);
	glVertex3fv(vertices[b]);
	glColor3fv(colors[c]);
	glVertex3fv(vertices[c]);
	glColor3fv(colors[d]);
	glVertex3fv(vertices[d]);
	glEnd();
}

void colorcube(void)
{
	face(0, 3, 2, 1);
	face(2, 3, 7, 6);
	face(0, 4, 7, 3);
	face(1, 2, 6, 5);
	face(4, 5, 6, 7);
	face(0, 1, 5, 4);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glTranslatef(hight, weight, 0);
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);
	colorcube();
	//glFlush();
	glutSwapBuffers();
}

void myReshape(int w, int h)
{
	GLfloat aspect = (GLfloat)w / (GLfloat)h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-2.0, 2.0, -2.0 / aspect, 2.0 / aspect, -10.0, 10.0);
	else
		glOrtho(-2.0 * aspect, 2.0 * aspect, -2.0, 2.0, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("cube");
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutIdleFunc(spinCube);
	glutMouseFunc(mouse);
	glutMotionFunc(move);
	glutKeyboardFunc(keyboard);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	return 0;
}