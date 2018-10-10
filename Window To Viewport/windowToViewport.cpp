/*
 *  window_viewport.c
 *  This program demonstrates the window-viewport transformation
 *	and the reshape callback in openGL/GLUT.
 */
#include<bits/stdc++.h>
#include <GL/glut.h>

/* globals for world window */
GLfloat win_left = 0.0;
GLfloat win_right = 14.0;
GLfloat win_bottom = 0.0;
GLfloat win_top = 14.0;

/*
* display: display function called when main loop is entered and
* when window is marked for redisplay
*/

void draw_house()
{
	/* clear the window */
	glClearColor(0.0, 0.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	/* house shape */
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
		glVertex2i(0, 0);
		glVertex2i(10, 0);
		glVertex2i(10, 10);
		glVertex2i(0, 10);
	glEnd();

	/* door */
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
		glVertex2i(4, 0);
		glVertex2i(4, 3);
		glVertex2i(6, 3);
		glVertex2i(6, 0);
	glEnd();

	/* windows */
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_QUADS);
		glVertex2i(1, 5);
		glVertex2i(1, 8);
		glVertex2i(3, 8);
		glVertex2i(3, 5);

		glVertex2i(7, 5);
		glVertex2i(7, 8);
		glVertex2i(9, 8);
		glVertex2i(9, 5);
	glEnd();

	/* roof */
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
		glVertex2i(0, 10);
		glVertex2i(5, 13);
		glVertex2i(10, 10);
	glEnd();

	/* show the output */
	glFlush();
}

void my_reshape(int w, int h)
{
	/* 3 possibilities for viewports */
	
	/* Possibility 1: always use entire screen window as viewport */
	/* graphics will distort when non-square aspect ratio) */
	glViewport(0, 0, w, h);
	
	/* Possibility 2: always use a square viewport as big as possible */
	/* graphics will remain undisorted, but large portions of screen window */
	/* may be unused */
	//if(w<=h) glViewport(0, 0, w, w);
	//else glViewport(0, 0, h, h);
	
	/* Possibility 3: keep same viewport throughout */
	/* Graphics will be clipped as window is made smaller */
	// glViewport(0, 0, 500, 500);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(win_left, win_right, win_bottom, win_top);
	
	glMatrixMode(GL_MODELVIEW);
}

void my_keyboard(unsigned char key, int x, int y)
{
	GLfloat win_center_x, win_center_y;

	switch(key){
		/* pan up */
		case 'w':
			win_bottom += 1.0;
			win_top += 1.0;
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluOrtho2D(win_left, win_right, win_bottom, win_top);
			glutPostRedisplay();
			break;
		/* pan down */
		case 's':
			win_bottom -= 1.0;
			win_top -= 1.0;
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluOrtho2D(win_left, win_right, win_bottom, win_top);
			glutPostRedisplay();
			break;
		/* pan left */
		case 'a':
			win_left -= 1.0;
			win_right -= 1.0;
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluOrtho2D(win_left, win_right, win_bottom, win_top);
			glutPostRedisplay();
			break;
		/* pan right */
		case 'd':
			win_left += 1.0;
			win_right += 1.0;
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluOrtho2D(win_left, win_right, win_bottom, win_top);
			glutPostRedisplay();
			break;
		/* zoom in */
		case '=':
			win_center_x = (win_left + win_right)/2.0;
			win_center_y = (win_bottom + win_top)/2.0;
			win_left = ((win_left - win_center_x)*0.5) + win_center_x;
			win_right = ((win_right - win_center_x)*0.5) + win_center_x;
			win_bottom = ((win_bottom - win_center_y)*0.5) + win_center_y;
			win_top = ((win_top - win_center_y)*0.5) + win_center_y;
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluOrtho2D(win_left, win_right, win_bottom, win_top);
			glutPostRedisplay();
			break;
		/* zoom out */
		case '-':
			win_center_x = (win_left + win_right)/2.0;
			win_center_y = (win_bottom + win_top)/2.0;
			win_left = ((win_left - win_center_x)*2.0) + win_center_x;
			win_right = ((win_right - win_center_x)*2.0) + win_center_x;
			win_bottom = ((win_bottom - win_center_y)*2.0) + win_center_y;
			win_top = ((win_top - win_center_y)*2.0) + win_center_y;
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluOrtho2D(win_left, win_right, win_bottom, win_top);
			glutPostRedisplay();
			break;
		default:
			break;
	}
}

int main(int argc, char **argv)
{
	/* create window, set coordinate space */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Windows, Viewports, and Reshaping");
        
	/* register callbacks */
	glutDisplayFunc(draw_house);
	glutReshapeFunc(my_reshape);
	glutKeyboardFunc(my_keyboard);

	/* enter the main loop */
	glutMainLoop();
	
	return 0;
}
