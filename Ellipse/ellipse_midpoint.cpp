#include<stdlib.h>
#include<iostream>
#include <GL/glut.h>
#include <stdio.h>

using namespace std;
int xc,yc,rx,ry;

void myInit() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 500, 0, 500);
}

void draw_pixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void draw_ellipse(int xc, int yc, int rx, int ry) {
    int x,y;
    float p;

    p=ry*ry-rx*rx*ry+rx*rx/4;
    x=0;y=ry;
    while(2.0*ry*ry*x <= 2.0*rx*rx*y) {
	    if(p < 0) {
	        x++;
	        p = p+2*ry*ry*x+ry*ry;
	    }
	    else {
	        x++;y--;
	        p = p+2*ry*ry*x-2*rx*rx*y-ry*ry;
	    }
	    draw_pixel(xc+x,yc+y);
	    draw_pixel(xc+x,yc-y);
	    draw_pixel(xc-x,yc+y);
	    draw_pixel(xc-x,yc-y);
    }

    p=ry*ry*(x+0.5)*(x+0.5)+rx*rx*(y-1)*(y-1)-rx*rx*ry*ry;
    while(y > 0) {
	    if(p <= 0) {
	        x++;y--;
	        p = p+2*ry*ry*x-2*rx*rx*y+rx*rx;
	    }
	    else {
	        y--;
	        p = p-2*rx*rx*y+rx*rx;
	    }
	    draw_pixel(xc+x,yc+y);
	    draw_pixel(xc+x,yc-y);
	    draw_pixel(xc-x,yc+y);
	    draw_pixel(xc-x,yc-y);
    }
}

void myDisplay() {
    draw_ellipse(xc,yc,rx,ry);
    glFlush();
}

int main(int argc, char **argv) {

    cout<<"Enter coordinates of centre : ";
    cin>>xc>>yc;
    cout<<"Enter x,y radius of ellipse: ";
    cin>>rx>>ry;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Midpoint Ellipse Drawing");
    myInit();
    glutDisplayFunc(myDisplay);
    glutMainLoop();
}
