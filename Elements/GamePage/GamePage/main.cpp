#include <iostream>
#include <GL/glut.h>
#include <SOIL2.h>
#include <string.h>
#include <stdio.h>

#define UP 1
#define DOWN 0
#define MAX 10
#define SIZE_MIS_X 55   //determines the size of missiles
#define SIZE_MIS_y 30   //determines the size of missiles
#define MAX_MISSILES 3  //maximum number of missiles in game
#define SPEED 1

using namespace std;
int frames = 60;

//  The number of frames
int frameCount = 0;
//  Number of frames per second
float fps = 0;
//  currentTime - previousTime is the time elapsed
//  between every call of the Idle function
int currentTime = 0, previousTime = 0;

//for choose scene
char scene[50];
int ch_scene = 1;

//high scores
int max_dist, max_miss;

//flag to check if you were hit by a missile
int hit_missile = 0;

//flad to determint the plane chosen by the user
int plane_choice = 2;

//flag for setting
int setting = 0;

void* currentfont;

float x_step = -171.0;    //for loading bar movement (in pg=0)

float y_cre = 0;            //for credits text moveemnt
float y_pos = 0;          //y axis position of plane
float theta = 0;          //angle of the plane
bool state;             //state of plane (either going up or down)

int update_mis;

GLfloat x = 0.0f;       //background screen position

GLfloat fuel = 98;        //fuel left in plane
GLfloat dist, missiles; //dustance travelled and missiled douged
GLfloat missile_x = 250, missile_y[MAX_MISSILES] = { 0 };//position of missiles
int no_of_missiles = 3;   //determines number of missiles in the game

int full = 0;
int i_bck, i_mis1, i_mis2, i_mis3, i_plane, i_inst21;
int i_cre22, i_sel31, i_sel32, i_fin4, i_2, i_23, i_0, i_1;
int i_s;

GLfloat windowWidth;
GLfloat windowHeight;

GLuint tex_2d, tex_2d_mis[4], tex_2d_plane;
GLuint tex_2d_0, tex_2d_1, tex_2d_2, tex_2d_21, tex_2d_22, tex_2d_31, tex_2d_4, tex_2d_23;

//determines the current screen
int page = 3;
//class to draw the plane
class plane
{
public:
	float x[MAX], y[MAX];
	// float ymax, ymin;
	// int button;
	plane()
	{
		x[1] = -30, x[2] = 30, x[3] = 30, x[4] = -30;
		y[1] = 15, y[2] = 15, y[3] = -15, y[4] = -15;
	}
	void draw_plane()
	{
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		if (plane_choice == 1)
		{
			if (i_plane == 0)
			{
				tex_2d_plane = SOIL_load_OGL_texture
				(
					"res/plane2.png",
					SOIL_LOAD_AUTO,
					SOIL_CREATE_NEW_ID,
					SOIL_FLAG_MULTIPLY_ALPHA
				);
				i_plane = 1;
			}
		}
		if (plane_choice == 2)
		{
			if (i_plane == 0)
			{
				tex_2d_plane = SOIL_load_OGL_texture
				(
					"res/plane3.png",
					SOIL_LOAD_AUTO,
					SOIL_CREATE_NEW_ID,
					SOIL_FLAG_MULTIPLY_ALPHA
				);
				i_plane = 1;
			}
		}
		glBindTexture(GL_TEXTURE_2D, tex_2d_plane);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBegin(GL_POLYGON);
		glTexCoord2f(0.0, 0.0);
		glVertex2f(x[1], y[1]);
		glTexCoord2f(1.0, 0.0);
		glVertex2f(x[2], y[2]);
		glTexCoord2f(1.0, 1.0);
		glVertex2f(x[3], y[3]);
		glTexCoord2f(0.0, 1.0);
		glVertex2f(x[4], y[4]);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
	}
} plane1;

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		//27 is the ASCII value of the ESC key
	case 27:
		//exit game
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
		break;
	}
}

//For glutBitmapCharacter (used only in page 1)
void setFont(void* font)
{
	currentfont = font;
}

void drawString(float x, float y, float z, const char *string)
{
	int i;
	glRasterPos3f(x, y, z);
	for (i = 0; string[i] != '\0'; i++)
	{
		glutBitmapCharacter(currentfont, string[i]);
	}
}

//Determines the action on mouse click event
void Mouse(int button, int m_state, int m_x, int m_y)
{
	if (page == 3)
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

//print the score in page 3 (prints the game scores during game play)
void draw_score()
{
	int length, i;
	char score_text[15];
	strcpy(score_text, "Distance: ");
	glLineWidth(1);
	glPushMatrix();
	glTranslatef(85, 82, 0);
	glScalef(0.08, 0.08, 0.08);
	length = (int)strlen(score_text);
	for (i = 0; i < length; i++)
	{
		glColor3f(1, 0, 1);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, score_text[i]);
	}
	glPopMatrix();

	char dist_text_val[15];
	sprintf(dist_text_val, "%d", (int)dist);
	glPushMatrix();
	glTranslatef(130, 82, 0);
	glScalef(0.08, 0.08, 0.08);
	length = (int)strlen(dist_text_val);
	for (i = 0; i < length; i++)
	{
		glColor3f(1, 0, 1);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, dist_text_val[i]);
	}
	glPopMatrix();

	char missiles_text[15];
	strcpy(missiles_text, "Missiles: ");
	glPushMatrix();
	glTranslatef(85, 72, 0);
	glScalef(0.08, 0.08, 0.08);
	length = (int)strlen(missiles_text);
	for (i = 0; i < length; i++)
	{
		glColor3f(0, 1, 1);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, missiles_text[i]);
	}
	glPopMatrix();

	char mis_text_val[15];
	sprintf(mis_text_val, "%d", (int)missiles);
	glPushMatrix();
	glTranslatef(130, 72, 0);
	glScalef(0.08, 0.08, 0.08);
	length = (int)strlen(mis_text_val);
	for (i = 0; i < length; i++)
	{
		glColor3f(0, 1, 1);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, mis_text_val[i]);
	}
	glPopMatrix();

	char fuel_text[15];
	strcpy(fuel_text, "Fuel:  %");
	glPushMatrix();
	glTranslatef(-149, 82, 0);
	glScalef(0.08, 0.08, 0.08);
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
	glScalef(0.08, 0.08, 0.08);
	length = (int)strlen(fuel_text_val);
	for (i = 0; i < length; i++)
	{
		glColor3f(1, 0, 0);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, fuel_text_val[i]);
	}
	glPopMatrix();
}

void rocket1(int x_cor, int y_cor)
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	if (i_mis1 == 0)
	{
		tex_2d_mis[1] = SOIL_load_OGL_texture
		(
			"res/rocket2.png",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MULTIPLY_ALPHA
		);
		i_mis1 = 1;
	}
	glBindTexture(GL_TEXTURE_2D, tex_2d_mis[1]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);
	glVertex2f(x_cor, y_cor);
	glTexCoord2f(1.0, 1.0);
	glVertex2f(x_cor + SIZE_MIS_X, y_cor);
	glTexCoord2f(1.0, 0.0);
	glVertex2f(x_cor + SIZE_MIS_X, y_cor + SIZE_MIS_y - 10);
	glTexCoord2f(0.0, 0.0);
	glVertex2f(x_cor, y_cor + SIZE_MIS_y - 10);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

void rocket2(int x_cor, int y_cor)
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	if (i_mis2 == 0)
	{
		tex_2d_mis[2] = SOIL_load_OGL_texture
		(
			"res/rocket3.png",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MULTIPLY_ALPHA
		);
		i_mis2 = 1;
	}
	glBindTexture(GL_TEXTURE_2D, tex_2d_mis[2]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);
	glVertex2f(x_cor, y_cor);
	glTexCoord2f(1.0, 1.0);
	glVertex2f(x_cor + SIZE_MIS_X, y_cor);
	glTexCoord2f(1.0, 0.0);
	glVertex2f(x_cor + SIZE_MIS_X, y_cor + SIZE_MIS_y - 10);
	glTexCoord2f(0.0, 0.0);
	glVertex2f(x_cor, y_cor + SIZE_MIS_y - 10);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

void rocket3(int x_cor, int y_cor)
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	if (i_mis3 == 0)
	{
		tex_2d_mis[3] = SOIL_load_OGL_texture
		(
			"res/rocket4.png",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MULTIPLY_ALPHA
		);
		i_mis3 = 1;
	}
	glBindTexture(GL_TEXTURE_2D, tex_2d_mis[3]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);
	glVertex2f(x_cor, y_cor);
	glTexCoord2f(1.0, 1.0);
	glVertex2f(x_cor + SIZE_MIS_X, y_cor);
	glTexCoord2f(1.0, 0.0);
	glVertex2f(x_cor + SIZE_MIS_X, y_cor + SIZE_MIS_y - 10);
	glTexCoord2f(0.0, 0.0);
	glVertex2f(x_cor, y_cor + SIZE_MIS_y - 10);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

void draw_rockets()
{
	if (missile_x > 200)
	{
		no_of_missiles = rand() % MAX_MISSILES + 1;
	}
	if (missile_x >= 195 && missile_x <= 200)
	{
		for (int k = 1; k <= no_of_missiles; k++)
			missile_y[k] = -101 + rand() % 165;
	}
	switch (no_of_missiles)
	{
	case 1:
		rocket1(missile_x, missile_y[1]);
		break;
	case 2:
		rocket1(missile_x, missile_y[1]);
		rocket2(missile_x, missile_y[2]);
		break;
	case 3:
		rocket1(missile_x, missile_y[1]);
		rocket2(missile_x, missile_y[2]);
		rocket3(missile_x, missile_y[3]);
		break;
	case 4:
		rocket1(missile_x, missile_y[1]);
		rocket3(missile_x, missile_y[2]);
		rocket2(missile_x, missile_y[3]);
		rocket3(missile_x, missile_y[4]);
		break;
	default:
	case 5:
		rocket1(missile_x, missile_y[1]);
		rocket3(missile_x, missile_y[2]);
		rocket2(missile_x, missile_y[3]);
		rocket3(missile_x, missile_y[4]);
		rocket1(missile_x, missile_y[5]);
		break;

	}
}

void draw_chosen_plane()
{
	glColor3f(1, 1, 1);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-150, -40);
	glVertex2f(-30, -40);
	glVertex2f(-30, 40);
	glVertex2f(-150, 40);
	glEnd();

	glPushMatrix();
	glTranslatef(-90, 0, 0);
	glScalef((GLfloat)1.6, (GLfloat)1.6, (GLfloat)0);
	plane1.draw_plane();
	glPopMatrix();
}

void RenderScene()
{
	if (page == 3)
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glEnable(GL_TEXTURE_2D);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		if (i_bck == 0)
		{
			tex_2d = SOIL_load_OGL_texture
			(
				scene,
				SOIL_LOAD_RGBA,
				SOIL_CREATE_NEW_ID,
				SOIL_FLAG_NTSC_SAFE_RGB
			);
			i_bck = 1;
		}
		glBindTexture(GL_TEXTURE_2D, tex_2d);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBegin(GL_POLYGON);
		glTexCoord2f(0.0, 1.0);
		glVertex2f(-190.0f + x, -100.0f);
		glTexCoord2f(1.0, 1.0);
		glVertex2f(890.0f + x, -100.0f);
		glTexCoord2f(1.0, 0.0);
		glVertex2f(890.0f + x, 100.0f);
		glTexCoord2f(0.0, 0.0);
		glVertex2f(-190.0f + x, 100.0f);
		glEnd();
		glDisable(GL_TEXTURE_2D);

		//fuel indicator outline
		glColor3f(0, 0, 0);
		glLineWidth(3);
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

		draw_rockets();

		glPushMatrix();
		glTranslatef(-130, y_pos, 0);
		glRotatef(theta, 0, 0, 1);
		plane1.draw_plane();
		glPopMatrix();
		glutSwapBuffers();
	}
}

void TimerFunction(int v)
{
	if (page == 3)
	{
		if (fuel == 98 || x < -700)
			x = 0;
		x -= 0.3 * SPEED;
		cout << x << endl;
		if (missile_x < -210)
			missile_x = 250;
		missile_x -= 1 * SPEED;
		if (state == UP)
		{
			if (fuel > 0)
				fuel -= .1 * SPEED;
		}

		dist += 0.1 * SPEED;

		//update number of missiles douged
		{
			if (missile_x < -90)
			{
				if (update_mis == 0)
				{
					missiles += no_of_missiles;
					update_mis = 1;
				}
			}
			else
				update_mis = 0;
		}

		//plane position
		if (state == UP)
		{
			if (fuel > 0)
			{
				if (y_pos <= 90)
					SPEED* y_pos++;
				if (theta < 0)
					theta += .3 * SPEED;
				else
					theta += .1 * SPEED;
			}
			else
				y_pos--* SPEED;
		}
		else
		{
			if (y_pos >= -100)
				SPEED* y_pos--;
			else
			{
				y_pos = 0;
				page = 4;
			}
			if (theta > 0)
				theta -= .3 * SPEED;
			else
				theta -= .1 * SPEED;

		}

		//check for collision
		if (missile_x < -110)
		{
			cout << "Possibility of crash" << endl;
			for (int m = 1; m <= no_of_missiles; m++)
			{
				if (missile_y[m] > y_pos - 10 && missile_y[m] < y_pos + 10)
				{
					cout << "Crash" << endl;
					hit_missile = 1;
					for (int m1 = 1; m1 <= no_of_missiles; m1++)
						missile_x = 200;
					y_pos = 0;
					x = 0;
					page = 4;
					break;
				}
			}

		}
	}

	glutPostRedisplay();
	glutTimerFunc(1000 / v, TimerFunction, v);
}

void myinit(void)
{
	glClearColor(0.0f, 0.8f, 0.0f, 1.0f);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
}

void reShape(int w, int h)
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


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800, 450);
	glutCreateWindow("Airplane!");
	//glutPositionWindow(320,150);
	if (full == 1)
	{
		glutFullScreen();
	}
	myinit();
	glutKeyboardFunc(keyboard);
	glutMouseFunc(Mouse);
	glutDisplayFunc(RenderScene);
	glutTimerFunc(100, TimerFunction, frames);
	glutReshapeFunc(reShape);
	glutMainLoop();
	return 0;
}
