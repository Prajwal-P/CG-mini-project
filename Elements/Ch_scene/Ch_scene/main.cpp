#include <GL/glut.h>
#include "SOIL2.h"
#include <iostream>
#include<string.h>
#include<stdio.h>
#define MAX 10
char scene[50];
int ch_scene = 1;
int page;
using namespace std;
int i_plane;
GLuint tex_2d_plane;
void* currentfont;
void setFont(void* font)
{
	currentfont = font;
}
void drawstring(float x, float y, float z, char* string)
{
	char* c;
	glRasterPos3f(x, y, z);

	for (c = string; *c != '\0'; c++)
	{
		glColor3f(0.0, 0.0, 0.0);
		glutBitmapCharacter(currentfont, *c);
	}
}

//Sets jimmy's initial position and size.
//rsize equals half of jimmy's height and width
GLfloat x = 0.0f;
GLfloat y = 0.0f;
GLfloat rsize = 8;
int frames = 5, full = 0;
int i = 0;
//Sets the direction and velocity of jimmy at the program initialization
/*The value of these variables defines the amount of pixels along the standard Cartesian coordinate system
Jimmy moves. For example, setting xstep to -2.0f would mean that jimmy would move two pixels
in a certain amount of time defined by the frames variable. The frames variable dictates the amount of milliseconds inbetween each movement of the square.
That means that if frames = 2, I get 50 fps, and therefore 50 movements of jimmy in a second.*/
GLfloat xstep = 0.0f;   //defines mivement. Stopped if 0
GLfloat ystep = 0.0f;

GLfloat windowWidth;
GLfloat windowHeight;

GLuint tex_2d;


void keycrap(unsigned char key, int x, int y)
{
	switch (key)
	{
		//27 is the ASCII value of the ESC key
	case 27:        //exit game
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
			glutReshapeWindow(800, 600);
			glutPositionWindow(320, 150);
			full = 0;
		}
	}
}

void SpecialKeys(int key, int x, int y) //to specify direction of jimmy
{
	switch (key)
	{
	case GLUT_KEY_UP:
	case GLUT_KEY_RIGHT:
		if (ch_scene < 5)
		{
			ch_scene++;
			i = 0;
			cout << ch_scene << endl;
		}
		break;

	case GLUT_KEY_DOWN:
	case GLUT_KEY_LEFT:
		if (ch_scene > 1)
		{
			ch_scene--;
			i = 0;
			cout << ch_scene << endl;
		}
		break;
	}
	glutPostRedisplay();
}

void draw_chScene_text()
{
	char string[15][120];
	int i, lengthOfString;


	strcpy(string[0], "Choose Scene");
	strcpy(string[1], "Use arrow keys");
	strcpy(string[2], "Next");

	glLineWidth(2);
	glPushMatrix();
	glTranslatef(-130, 55, 0);
	glScalef(0.3, 0.3, 0.3);
	lengthOfString = (int)strlen(string[0]);
	for (i = 0; i < lengthOfString; i++)
	{
		glColor3f(1, 1, 1);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, string[0][i]);
	}
	glPopMatrix();

	glLineWidth(3);
	glPushMatrix();
	glTranslatef(-75, 35, 0);
	glScalef(0.15, 0.15, 0.15);
	lengthOfString = (int)strlen(string[1]);
	for (i = 0; i < lengthOfString; i++)
	{
		glColor3f(1, 1, 1);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, string[1][i]);
	}
	glPopMatrix();

	glLineWidth(2);
	glPushMatrix();
	glTranslatef(-25, -75, 0);
	glScalef(0.1, 0.1, 0.1);
	lengthOfString = (int)strlen(string[2]);
	for (i = 0; i < lengthOfString; i++)
	{
		glColor3f(1, 1, 1);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, string[2][i]);
	}
	glPopMatrix();

}

void mouse(int button, int m_state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && m_state == GLUT_UP)
	{
		cout << x << " " << y << endl;
		if (full == 0)
		{
			if (x > 338 && x < 410 && y > 365 && y < 401)
			{
				cout << "next" << endl;
				i_plane = 0;
				page = 3;
			}
		}
		else
		{
			if (x > 821 && x < 969 && y > 879 && y < 955)
			{
				cout << "next" << endl;
				i_plane = 0;
				page = 3;
			}
		}
	}
}


void select_scene()
{
	switch (ch_scene)
	{
	case 1:
		sprintf(scene, "res/scene1.jpg");
		break;
	case 2:
		sprintf(scene, "res/scene2.png");
		break;
	case 3:
		sprintf(scene, "res/scene3.png");
		break;
	case 4:
		sprintf(scene, "res/scene4.jpg");
		break;
	case 5:
		sprintf(scene, "res/scene5.jpg");
		break;
	}
}

void RenderScene()
{
	//Clears the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT);

	glEnable(GL_TEXTURE_2D);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	select_scene();

	if (i == 0)
	{
		tex_2d = SOIL_load_OGL_texture
		(
			scene,
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

	draw_chScene_text();

	glutSwapBuffers();
}



void SetupRC(void)
{
	//Sets the clear color. Again, the values are in RGBA float format
	glClearColor(0.0f, 0.8f, 0.0f, 1.0f);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_TEXTURE_2D);
}

void ChangeSize(int w, int h)
{
	GLfloat aspectRatio;

	//Prevents a divid by zero. We wouldn't want that, now, would we.
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

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800, 450);
	glutCreateWindow("Choose Scene");
	glutPositionWindow(320, 150);
	glutIgnoreKeyRepeat(1);
	glutSpecialFunc(SpecialKeys);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keycrap);
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	SetupRC();
	glutMainLoop();

	return 0;
}
