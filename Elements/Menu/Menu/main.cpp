#include <GL/glut.h>
#include "SOIL2.h"
#include <iostream>
#include<string.h>

using namespace std;

void* currentfont;
int full = 0;   //defines state of screen (fullscreen or not)
int frames = 50;

GLfloat windowWidth;
GLfloat windowHeight;

GLuint tex_2d;

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

void draw_menu_text()
{
	char string_menu[10][20];
	int lengthOfString, i;

	strcpy(string_menu[0], "Play!");
	strcpy(string_menu[1], "Settings");
	strcpy(string_menu[2], "Instructions");
	strcpy(string_menu[3], "Credit");
	strcpy(string_menu[4], "Exit..");

	glPushMatrix();
	glTranslatef(-120, 50, 0);
	glScalef(0.1, 0.1, 0.1);
	lengthOfString = (int)strlen(string_menu[0]);
	for (i = 0; i < lengthOfString; i++)
	{
		glColor3f(1, 1, 1);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, string_menu[0][i]);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-120, 35, 0);
	glScalef(0.1, 0.1, 0.1);
	lengthOfString = (int)strlen(string_menu[1]);
	for (i = 0; i < lengthOfString; i++)
	{
		glColor3f(1, 1, 1);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, string_menu[1][i]);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-120, 20, 0);
	glScalef(0.1, 0.1, 0.1);
	lengthOfString = (int)strlen(string_menu[2]);
	for (i = 0; i < lengthOfString; i++)
	{
		glColor3f(1, 1, 1);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, string_menu[2][i]);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-120, 5, 0);
	glScalef(0.1, 0.1, 0.1);
	lengthOfString = (int)strlen(string_menu[3]);
	for (i = 0; i < lengthOfString; i++)
	{
		glColor3f(1, 1, 1);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, string_menu[3][i]);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-120, -10, 0);
	glScalef(0.1, 0.1, 0.1);
	lengthOfString = (int)strlen(string_menu[4]);
	for (i = 0; i < lengthOfString; i++)
	{
		glColor3f(1, 1, 1);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, string_menu[4][i]);
	}
	glPopMatrix();
}

void RenderScene()
{
	//Clears the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT);

	//load .jpg image
	glEnable(GL_TEXTURE_2D);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	tex_2d = SOIL_load_OGL_texture
	(
		"res/plane_menu.jpg",
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

	draw_menu_text();

	glutSwapBuffers();

}

void SetupRC(void)
{
	//Sets the clear color. Again, the values are in RGBA float format
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

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

void mouse(int button, int state, int x, int y)
{
	//set the coordinates and update page
	if (full == 0)
	{
		if (state == GLUT_UP)
		{
			cout << x << " " << y << endl;
			if (x > 130 && x < 189 && y > 86 && y < 114)
			{
				cout << "play" << endl;
			}
			if (x > 130 && x < 235 && y > 120 && y < 150)
			{
				cout << "Settings" << endl;
			}
			if (x > 130 && x < 279 && y > 154 && y < 182)
			{
				cout << "Instructions" << endl;
			}
			if (x > 130 && x < 209 && y > 187 && y < 217)
			{
				cout << "Credit" << endl;
			}
			if (x > 130 && x < 189 && y > 221 && y < 250)
			{
				cout << "Exit" << endl;
			}
		}
	}
	else if (full == 1)
	{
		if (state == GLUT_UP)
		{
			cout << x << " " << y << endl;
			if (x > 314 && x < 453 && y > 206 && y < 273)
			{
				cout << "play" << endl;
			}
			if (x > 314 && x < 562 && y > 291 && y < 356)
			{
				cout << "Settings" << endl;
			}
			if (x > 314 && x < 667 && y > 373 && y < 436)
			{
				cout << "Instructions" << endl;
			}
			if (x > 314 && x < 502 && y > 452 && y < 516)
			{
				cout << "Credit" << endl;
			}
			if (x > 314 && x < 451 && y > 535 && y < 596)
			{
				cout << "Exit" << endl;
			}
		}
	}
}


//Actually opens the window, initializes all the functions I made, and throws it all into a loop. Hooray!
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800, 450);
	glutCreateWindow("Menu");
	glutPositionWindow(320, 150);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(reshape);
	SetupRC();
	glutMainLoop();
	return 0;
}
