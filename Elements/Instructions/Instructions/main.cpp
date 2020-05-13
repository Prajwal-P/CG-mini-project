#include <GL/glut.h>
#include "SOIL2.h"
#include<string.h>

int full = 0;
GLfloat windowWidth;
GLfloat windowHeight;

GLuint tex_2d;

void keyboard(unsigned char key, int x, int y)
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
			glutReshapeWindow(800, 450);
			glutPositionWindow(320, 150);
			full = 0;
		}
	}
}

void draw_inst_text()
{
	char string[15][120];
	int i, lengthOfString;

	strcpy(string[0], "Instructions:");
	strcpy(string[1], "The main objective of this game is to go as far");
	strcpy(string[2], "as possible in your plane, without hitting the");
	strcpy(string[3], "missiles.");
	strcpy(string[4], "Press left mouse button to increase altitude!");
	strcpy(string[5], "Leaving it will automatically take you down.");
	strcpy(string[6], "Keep a close eye on the fuel guage though :P");
	strcpy(string[7], "Have FUN!!!");
	glLineWidth(3);

	glPushMatrix();
	glTranslatef(-45, 50, 0);
	glScalef(0.15, 0.15, 0.15);
	lengthOfString = (int)strlen(string[0]);
	for (i = 0; i < lengthOfString; i++)
	{
		glColor3f(1, 1, 1);
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, string[0][i]);
	}
	glPopMatrix();

	glLineWidth(1);
	int y_pos_21 = 30;
	for (int k_t = 1; k_t <= 7; k_t++)
	{
		glPushMatrix();
		glTranslatef(-40, y_pos_21 -= 10, 0);
		glScalef(0.06, 0.06, 0.06);
		lengthOfString = (int)strlen(string[k_t]);
		for (i = 0; i < lengthOfString; i++)
		{
			glColor3f(1, 1, 1);
			glutStrokeCharacter(GLUT_STROKE_ROMAN, string[k_t][i]);
		}
		glPopMatrix();
	}

}

void RenderScene()
{
	//Clears the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT);

	//Load the background image
	glEnable(GL_TEXTURE_2D);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	tex_2d = SOIL_load_OGL_texture
	(
		"res/instructions2.png",
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

	draw_inst_text();
	glutSwapBuffers();
}



void SetupRC(void)
{
	//Sets the clear color. Again, the values are in RGBA float format
	glClearColor(0.0f, 0.8f, 0.0f, 1.0f);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_TEXTURE_2D);
}

void reShape(int w, int h)
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


//Actually opens the window, initializes all the functions I made, and throws it all into a loop. Hooray!
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800, 450);
	glutCreateWindow("Instructions");
	glutPositionWindow(320, 150);
	if (full == 1)
	{
		glutFullScreen();
	}
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(reShape);
	SetupRC();
	glutMainLoop();

	return 0;
}
