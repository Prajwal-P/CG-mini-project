#include <GL/glut.h>
#include "SOIL2.h"
#include <iostream>
#include<string.h>
#include<stdio.h>
int hit_missile = 0;
using namespace std;
int no_of_missiles = 0;
int dist = 0;
int full = 0;   //defines state of screen (fullscreen or not)
int frames = 2;
int direction = 0;
int y_cre = 0;
int i;

GLfloat windowWidth;
GLfloat windowHeight;

GLuint tex_2d;

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		//27 is the ASCII value of the ESC key
	case 27:
		//go back to previous page
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
	char string[6][40];
	int i, lengthOfString;

	strcpy(string[0], "WOW!!");
	sprintf(string[1], "You just travelled %d meters", dist);
	sprintf(string[2], "and douged %d missiles", no_of_missiles);
	sprintf(string[3], "before you ran out of fuel!!");
	sprintf(string[4], "before you were hit by one!!");

	glLineWidth(2);
	glPushMatrix();
	glTranslatef(-105, 55, 0);
	glScalef(0.3, 0.3, 0.3);
	lengthOfString = (int)strlen(string[0]);
	for (i = 0; i < lengthOfString; i++)
	{
		glColor3f(1, 1, 1);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, string[0][i]);
	}
	glPopMatrix();

	glLineWidth(1);
	glPushMatrix();
	glTranslatef(-155, 35, 0);
	glScalef(0.1, 0.1, 0.1);
	lengthOfString = (int)strlen(string[1]);
	for (i = 0; i < lengthOfString; i++)
	{
		glColor3f(1, 1, 1);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, string[1][i]);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-155, 20, 0);
	glScalef(0.1, 0.1, 0.1);
	lengthOfString = (int)strlen(string[2]);
	for (i = 0; i < lengthOfString; i++)
	{
		glColor3f(1, 1, 1);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, string[2][i]);
	}
	glPopMatrix();

	if (!hit_missile)
	{
		glPushMatrix();
		glTranslatef(-155, 5, 0);
		glScalef(0.1, 0.1, 0.1);
		lengthOfString = (int)strlen(string[3]);
		for (i = 0; i < lengthOfString; i++)
		{
			glColor3f(1, 1, 1);
			glutStrokeCharacter(GLUT_STROKE_ROMAN, string[3][i]);
		}
		glPopMatrix();
	}
	else
	{
		glPushMatrix();
		glTranslatef(-155, 5, 0);
		glScalef(0.1, 0.1, 0.1);
		lengthOfString = (int)strlen(string[4]);
		for (i = 0; i < lengthOfString; i++)
		{
			glColor3f(1, 1, 1);
			glutStrokeCharacter(GLUT_STROKE_ROMAN, string[4][i]);
		}
		glPopMatrix();
	}
}

void RenderScene()
{

	//Clears the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT);

	//load .png image
	glEnable(GL_TEXTURE_2D);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	if (i == 0)
	{
		tex_2d = SOIL_load_OGL_texture
		(
			"res/finish.png",
			SOIL_LOAD_RGBA,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_NTSC_SAFE_RGB
		);
		i = 1;
	}
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
	//drawText();
	draw_text();
	glutSwapBuffers();

}

void SetupRC(void)
{
	//Sets the clear color. Again, the values are in RGBA float format
	glClearColor(0.234f, 0.220f, 0.193f, 0.0f);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_TEXTURE_2D);
}

void reshape(int w, int h)
{
	GLfloat aspectRatio;

	//Prevents a divide by zero. We wouldn't want that, now, would we.
	if (h == 0)
		h = 1;

	//Makes sure that the OpenGL viewport fills the whole screen
	glViewport(0, 0, w, h);

	//Resets the coordinate system so that the center of the window is (0,0,0) Cartesian x,y,z style
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//Sets the clipping volume to the dimensions of the window, including depth ^_^
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

//Actually opens the window, initializes all the functions I made, and throws it all into a loop. Hooray!
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800, 450);
	glutCreateWindow("Splash!");
	glutPositionWindow(320, 150);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(reshape);
	SetupRC();
	glutMainLoop();
	return 0;
}
