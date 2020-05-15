#include <GL/glut.h>
#include "SOIL2.h"
#include <iostream>
#define MAX 10
#define UP 1
#define DOWN 0

using namespace std;

float y_pos = 0;
float theta = 0;
bool state;

GLfloat fuel = 98;        //fuel left in plane

bool crash = false;

class plane
{
public:
	float x[MAX], y[MAX];
	plane()
	{
		x[1] = -10, x[2] = 40, x[3] = 40, x[4] = -10;
		y[1] = 5, y[2] = 5, y[3] = -5, y[4] = -5;
	}
	void draw_plane()
	{
		glColor3f(1, 0, 0);
		glBegin(GL_POLYGON);
		glVertex2f(x[1], y[1]);
		glVertex2f(x[2], y[2]);
		glVertex2f(x[3], y[3]);
		glVertex2f(x[4], y[4]);
		glEnd();
	}
} plane1;

int frames = 5, full = 0;
//Sets the direction and velocity of airplane at the program initialization
/*The value of these variables defines the amount of pixels along the standard Cartesian coordinate system
airplane moves. For example, setting xstep to -2.0f would mean that airplane would move two pixels
in a certain amount of time defined by the frames variable. The frames variable dictates the amount of milliseconds inbetween each movement of the square.
That means that if frames = 2, I get 50 fps, and therefore 50 movements of airplane in a second.*/

GLfloat windowWidth;
GLfloat windowHeight;

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{		//27 is the ASCII value of the ESC key
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


void mouse(int button, int m_state, int x, int y)
{
	if (!crash)
	{
		if (button == GLUT_LEFT_BUTTON && m_state == GLUT_DOWN)
		{
			state = UP;
			cout << "Going Up!" << endl;
		}
		else if (button == GLUT_LEFT_BUTTON && m_state == GLUT_UP)
		{
			state = DOWN;
			cout << "Going Down" << endl;
		}
	}
}

void draw_score()
{
	int length, i;

	char fuel_text[15];
	strcpy(fuel_text, "Fuel:  %");
	glPushMatrix();
	glTranslatef(-149, 82, 0);
	glScalef((GLfloat)0.08, (GLfloat)0.08, (GLfloat)0.08);
	length = (int)strlen(fuel_text);
	for (i = 0; i < length; i++)
	{
		glColor3f(1, 0, 0);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, fuel_text[i]);
	}
	glPopMatrix();

	char fuel_text_val[15];
	sprintf(fuel_text_val, "%d", (int)fuel);
	glPushMatrix();
	glTranslatef(-125, 82, 0);
	glScalef((GLfloat)0.08, (GLfloat)0.08, (GLfloat)0.08);
	length = (int)strlen(fuel_text_val);
	for (i = 0; i < length; i++)
	{
		glColor3f(1, 0, 0);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, fuel_text_val[i]);
	}
	glPopMatrix();
}

void RenderScene()
{
	if (!crash)
	{
		glClear(GL_COLOR_BUFFER_BIT);

		//fuel indicator outline
		glColor3f(0, 0, 0);
		glLineWidth(2);
		glBegin(GL_LINE_LOOP);
		glVertex2f(-50 - 100, 80);
		glVertex2f(50 - 100, 80);
		glVertex2f(50 - 100, 70);
		glVertex2f(-50 - 100, 70);
		glEnd();

		//fuel indicator
		glColor3f(1, 0, 0);
		glBegin(GL_POLYGON);
		glVertex2f(-49 - 100, 79);
		glVertex2f(-49 + fuel - 100, 79);
		glVertex2f(-49 + fuel - 100, 71);
		glVertex2f(-49 - 100, 71);
		glEnd();

		//seprator--to seprate score and game screen
		glLineWidth(1);
		glColor3f(1, 1, 1);
		glBegin(GL_LINES);
		glVertex2f(-200, 64);
		glVertex2f(200, 64);
		glEnd();

		draw_score();

		glPushMatrix();
		glTranslatef(-150, y_pos, 0);
		glRotatef(theta, 0, 0, 1);
		plane1.draw_plane();
		glPopMatrix();

		glutSwapBuffers();
	}
	else
	{
		;
		// Next page
	}
}

void TimerFunction(int value)
{
	if (!crash)
	{
		if (state == UP)
		{
			if (fuel > 0)
				fuel -= (GLfloat).1;
		}

		cout << "y_pos = " << y_pos << endl;
		if (state == UP && fuel > 0)
		{
			if (y_pos <= 90)
				y_pos++;
			if (theta < 15)
			{
				theta += 0.5;
			}
		}
		else
		{
			if (y_pos >= -90)
				y_pos--;
			if (theta > -15)
			{
				theta -= 0.5;
			}
		}

		// Check for crash
		if (y_pos < -90)
		{
			crash = true;
			cout << "Crash!!!" << endl;
			cout << "Next Page" << endl;
		}
	}

	glutPostRedisplay();
	glutTimerFunc(frames, TimerFunction, 1);
}

void SetupRC(void)
{
	//Sets the clear color. Again, the values are in RGBA float format
	glClearColor(0.0f, 0.8f, 0.0f, 1.0f);
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

}

//Actually opens the window, initializes all the functions I made, and throws it all into a loop. Hooray!
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 450);
	glutCreateWindow("");
	glutPositionWindow(320, 150);
	if (full == 1)
	{
		glutFullScreen();
	}
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(33, TimerFunction, 1);
	SetupRC();
	glutMainLoop();

	return 0;
}
