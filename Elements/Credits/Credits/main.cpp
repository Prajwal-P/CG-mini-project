#include <GL/glut.h>
#include "SOIL2.h"
#include <iostream>
#include<string.h>

using namespace std;


int frames = 60;
int direction = 0;
float y_cre = 0;
int full = 0;

GLfloat windowWidth;
GLfloat windowHeight;

GLuint tex_2d, tex_2d_plane;

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		//27 is the ASCII value of the ESC key
	case 27:
		exit(0);
		break;

	case 'f':       //full screen
		if (full == 0)
		{
			glutFullScreen();
			full = 1;
		}
		else
		{
			glutReshapeWindow(800, 450);
			glutPositionWindow(320, 150);
			full = 0;
		}
	}
}

void draw_text()
{
	char string[6][50];
	int i, lengthOfString;

	strcpy(string[3], "Bangalore Institute of Technology");
	strcpy(string[2], "Thank you!");
	strcpy(string[1], "Revanth P N");
	strcpy(string[0], "Prajwal P");
	strcpy(string[5], "1BI17CS111");
	strcpy(string[4], "1BI17CS123");


	glLineWidth(1);

	glPushMatrix();
	glTranslatef(-105, 150 - y_cre, 0);
	glScalef((GLfloat)0.1, (GLfloat)0.1, (GLfloat)0.1);
	lengthOfString = (int)strlen(string[3]);
	for (i = 0; i < lengthOfString; i++)
	{
		glColor3f(1, 1, 1);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, string[3][i]);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-35, 120 - y_cre, 0);
	glScalef((GLfloat)0.1, (GLfloat)0.1, (GLfloat)0.1);
	lengthOfString = (int)strlen(string[2]);
	for (i = 0; i < lengthOfString; i++)
	{
		glColor3f(1, 1, 1);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, string[2][i]);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-140, -75 + y_cre, 0);
	glScalef((GLfloat)0.1, (GLfloat)0.1, (GLfloat)0.1);
	lengthOfString = (int)strlen(string[1]);
	for (i = 0; i < lengthOfString; i++)
	{
		glColor3f(1, 1, 1);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, string[1][i]);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(59, -75 + y_cre, 0);
	glScalef((GLfloat)0.1, (GLfloat)0.1, (GLfloat)0.1);
	lengthOfString = (int)strlen(string[0]);
	for (i = 0; i < lengthOfString; i++)
	{
		glColor3f(1, 1, 1);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, string[0][i]);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-135, -95 + y_cre, 0);
	glScalef((GLfloat)0.1, (GLfloat)0.1, (GLfloat)0.1);
	lengthOfString = (int)strlen(string[4]);
	for (i = 0; i < lengthOfString; i++)
	{
		glColor3f(1, 1, 1);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, string[4][i]);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(55, -95 + y_cre, 0);
	glScalef((GLfloat)0.1, (GLfloat)0.1, (GLfloat)0.1);
	lengthOfString = (int)strlen(string[5]);
	for (i = 0; i < lengthOfString; i++)
	{
		glColor3f(1, 1, 1);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, string[5][i]);
	}
	glPopMatrix();
}

void drawLogo()
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glColor4f((GLfloat)1.0f, (GLfloat)1.0f, (GLfloat)1.0f, (GLfloat)((y_cre / 100.0)));
	cout << y_cre << endl;
	tex_2d_plane = SOIL_load_OGL_texture
	(
		"res/logo.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MULTIPLY_ALPHA
	);

	glBindTexture(GL_TEXTURE_2D, tex_2d_plane);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);
	glVertex2f(-30, -95);
	glTexCoord2f(1.0, 1.0);
	glVertex2f(30, -95);
	glTexCoord2f(1.0, 0.0);
	glVertex2f(30, -30);
	glTexCoord2f(0.0, 0.0);
	glVertex2f(-30, -30);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

void RenderScene()
{

	glClear(GL_COLOR_BUFFER_BIT);

	glEnable(GL_TEXTURE_2D);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	tex_2d = SOIL_load_OGL_texture
	(
		"res/cre.jpg",
		SOIL_LOAD_RGBA,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_NTSC_SAFE_RGB
	);
	glBindTexture(GL_TEXTURE_2D, tex_2d);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);


	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);
	glVertex2f(-178.0f, -100.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex2f(178.0f, -100.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex2f(178.0f, 100.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex2f(-178.0f, 100.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	drawLogo();
	draw_text();
	glutSwapBuffers();

}

void SetupRC(void)
{

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_TEXTURE_2D);
}

void reshape(int w, int h)
{
	GLfloat aspectRatio;

	if (h == 0)
		h = 1;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	aspectRatio = (GLfloat)w / (GLfloat)h;
	if (w <= h)
	{
		windowWidth = 100;
		windowHeight = 100 / aspectRatio;
		glOrtho(-100.0, 100.0, -windowHeight, windowHeight, 1.0, -1.0);
	}
	else
	{
		windowWidth = 100 * aspectRatio;
		windowHeight = 100;
		glOrtho(-windowWidth, windowWidth, -100.0, 100.0, 1.0, -1.0);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void TimerFunction(int value)
{
	if (y_cre < 80)
		y_cre+=3;

	glutPostRedisplay();
	glutTimerFunc(1, TimerFunction, value);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800, 450);
	glutCreateWindow("Credits");
	glutPositionWindow(320, 150);
	if (full == 1)
	{
		glutFullScreen();
	}
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(RenderScene);
	glutTimerFunc(100, TimerFunction, frames);
	glutReshapeFunc(reshape);
	SetupRC();
	glutMainLoop();
	return 0;
}
