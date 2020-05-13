#include <GL/glut.h>
#include "SOIL2.h"
#include <iostream>
#include<string.h>
#define MAX 10

using namespace std;

int full = 0;

int i_plane=0;
int i = 0;

GLuint tex_2d_plane;
GLuint tex_2d;

GLfloat windowWidth;
GLfloat windowHeight;

int plane_choice=2;

class plane
{
public:
	float x[MAX], y[MAX];
	plane()
	{
		x[1]=-30, x[2]=30, x[3]=30, x[4]=-30;
		y[1]=15, y[2]=15, y[3]=-15, y[4]=-15;
	}
	void draw_plane()
	{
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		if(plane_choice==1)
		{
			if (i_plane == 0)
			{
				tex_2d_plane = SOIL_load_OGL_texture
					       (
						       "res/plane1.png",
						       SOIL_LOAD_AUTO,
						       SOIL_CREATE_NEW_ID,
						       SOIL_FLAG_MULTIPLY_ALPHA
					       );
				i_plane = 1;
			}
		}
		if(plane_choice==2)
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
		glBindTexture(GL_TEXTURE_2D, tex_2d_plane);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
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
	if(button==GLUT_LEFT_BUTTON && m_state==GLUT_UP)
	{
		cout<<x<<" "<<y<<endl;
		if(full==0)
		{
			if(x>505 && x<715 && y>170 && y<205)
			{
				plane_choice=1;
				i_plane=0;
				glutPostRedisplay();
			}
			if(x > 505 && x < 715 && y>240 && y<280)
			{
				plane_choice=2;
				i_plane=0;
				glutPostRedisplay();
			}
			if(x>325 && x<425 && y>350 && y<400)
			{
			        cout<<"next"<<endl;
			        i_plane=0;
					// next page
			}
		}
		else
		{
			if(x>1225 && x<1710 && y>425 && y<490)
			{
				plane_choice=1;
				i_plane=0;
				glutPostRedisplay();
			}
			if(x>1230 && x<1580 && y>590 && y<650)
			{
				plane_choice=2;
				i_plane=0;
				glutPostRedisplay();
			}
			if(x>790 && x<1010 && y>850 && y<945)
			{
			        cout<<"next"<<endl;
			        i_plane=0;
					//next page
			}
		}
	}
}

void draw_chPlane_text()
{
	char string[15][120];
	int i, lengthOfString;


	strcpy(string[0], "Choose Plane");
	strcpy(string[1], "Military X991+");
	strcpy(string[2], "Toy Plane!");
	strcpy(string[3], "Next");

	glLineWidth(2);
	glPushMatrix();
	glTranslatef(-120, 55, 0);
	glScalef((GLfloat)0.3, (GLfloat)0.3, (GLfloat)0.3);
	lengthOfString = (int)strlen(string[0]);
	for (i = 0; i < lengthOfString; i++)
	{
		glColor3f(1, 1, 1);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, string[0][i]);
	}
	glPopMatrix();

	glLineWidth(1);
	GLfloat y_pos_21 = 40;
	for (int k_t = 1; k_t <= 2; k_t++)
	{
		glPushMatrix();
		glTranslatef(50, y_pos_21 -= 30, 0);
		glScalef((GLfloat)0.1, (GLfloat)0.1, (GLfloat)0.1);
		lengthOfString = (int)strlen(string[k_t]);
		for (i = 0; i < lengthOfString; i++)
		{
			glColor3f(1, 1, 1);
			glutStrokeCharacter(GLUT_STROKE_ROMAN, string[k_t][i]);
		}
		glPopMatrix();
	}

	glLineWidth(2);
	glPushMatrix();
	glTranslatef(-30, -75, 0);
	glScalef((GLfloat)0.15, (GLfloat)0.15, (GLfloat)0.15);
	lengthOfString = (int)strlen(string[3]);
	for (i = 0; i < lengthOfString; i++)
	{
		glColor3f(1, 1, 1);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, string[3][i]);
	}
	glPopMatrix();
}

void draw_chosen_plane()
{
	glColor3f(1,1,1);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-150,-40);
	glVertex2f(-30,-40);
	glVertex2f(-30,40);
	glVertex2f(-150,40);
	glEnd();

	glPushMatrix();
	glTranslatef(-90,0,0);
	glScalef((GLfloat)1.6, (GLfloat)1.6, (GLfloat)0);
	plane1.draw_plane();
	glPopMatrix();
}

void RenderScene()
{
//Clears the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT);

	glEnable(GL_TEXTURE_2D);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	if (i == 0)
	{
		tex_2d = SOIL_load_OGL_texture
			 (
				 "res/bck_plane.jpg",
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

	draw_chPlane_text();
	draw_chosen_plane();

	glutSwapBuffers();
}

void reShape(int w, int h)
{
	GLfloat aspectRatio;

//Prevents a divid by zero. We wouldn't want that, now, would we.
	if(h == 0)
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
		glOrtho (-100.0, 100.0, -windowHeight, windowHeight, 1.0, -1.0);
	}
	else
	{
		windowWidth = 100 * aspectRatio;
		windowHeight = 100;
		glOrtho (-windowWidth, windowWidth, -100.0, 100.0, 1.0, -1.0);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


//Actually opens the window, initializes all the functions I made, and throws it all into a loop. Hooray!
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800,450);
	glutCreateWindow("Choose plane");
	glutPositionWindow(320,150);
	if (full == 1)
	{
		glutFullScreen();
	}
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(reShape);
	glutMainLoop();

	return 0;
}
