#include <GL/glut.h>
#include <GL/glu.h>

void display(void)
{
glClearColor(0.0,0.0,0.0,0.0);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(60.0,1.0,1.0,100.0);
glTranslatef(0.0,0.0,-2.0);
glMatrixMode(GL_MODELVIEW);
glDepthFunc(GL_LEQUAL);
glEnable(GL_DEPTH_TEST);
glClearDepth(-1.0);

glBegin(GL_QUADS);
glColor3f(0.0,-25.0,2.0);
glVertex3f(-0.5,0.5,-0.5);
glVertex3f(-0.5,-0.5,0.5);
glColor3f(0.0,25.0,2.0);
glVertex3f(0.5,-0.5,0.5);
glColor3f(0.0,-50.0,2.0);
glVertex3f(0.5,0.5,-0.5);
glEnd();

glBegin(GL_TRIANGLES);
glColor3f(1.0,0.0,0.0);
glVertex3f(0.0,0.5,0.0);
glColor3f(1.0,0.0,0.0);
glVertex3f(-0.7,-0.5,0.0);
glColor3f(1.0,0.0,0.0);
glVertex3f(0.7,-0.5,0.0);
glEnd();

// move the quadrilateral code portion below the traiangle code to see different view
glFlush();
}


int main(int argc, char **argv)
{
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
glutInitWindowPosition(20,20);
glutInitWindowSize(500,500);
glutCreateWindow("Hello OpenGL");
glutDisplayFunc(display);
glutMainLoop();
return 0;
}
