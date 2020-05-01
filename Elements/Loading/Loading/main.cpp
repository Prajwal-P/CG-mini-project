#include <GL/glut.h>
#include "SOIL2.h"
#include <iostream>

int full = 0;   //defines state of screen (fullscreen or not)
int frames = 50;
float x_step = -171.0, y_step = -171.0;    //for loading bar movement
/*The value of these variables defines the amount of pixels along the standard Cartesian coordinate system
loading bar moves. For example, setting xstep to -2.0f would mean that the bar would move two pixels
in a certain amount of time defined by the frames variable. The frames variable dictates the amount of milliseconds inbetween each movement of the square.
That means that if frames = 2, I get 50 fps, and therefore 50 movements of bar per second.*/

GLfloat windowWidth;
GLfloat windowHeight;

GLuint tex_2d;

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'r':       //reset values
		x_step = -171.0, y_step = -171.0;;
		break;

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



void RenderScene()
{
	//Clears the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT);

	//load .png image
	glEnable(GL_TEXTURE_2D);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	tex_2d = SOIL_load_OGL_texture
	(
		"res/loading.png",
		SOIL_LOAD_RGBA,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_NTSC_SAFE_RGB
	);
	glBindTexture(GL_TEXTURE_2D, tex_2d);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);


	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);
	glVertex2f(-190.0f, -190.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex2f(190.0f, -190.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex2f(190.0f, 190.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex2f(-190.0f, 190.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	//draw loading bar
	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	glVertex2f(-171.0f, -4.4f);
	glVertex2f(0.0f + x_step, -4.4f);
	glVertex2f(0.0f + x_step, 1.3f);
	glVertex2f(-171.0f, 1.3f);
	glEnd();

	glutSwapBuffers();
	glFlush();

}

void TimerFunction(int value)
{
	if (x_step < 171.0)
		x_step += 6.0;
	//Redraws the scene with all changes above
	glutPostRedisplay();
	glutTimerFunc(frames, TimerFunction, 1);
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

	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
}


//Actually opens the window, initializes all the functions I made, and throws it all into a loop. Hooray!
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800, 450);
	glutCreateWindow("Loading...");
	glutPositionWindow(320, 150);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(RenderScene);
	glutTimerFunc(33, TimerFunction, 1);
	glutReshapeFunc(reshape);
	SetupRC();
	glutMainLoop();

	return 0;
}
