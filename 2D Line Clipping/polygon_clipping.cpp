#include<bits/stdc++.h>
#include <GL/glut.h>
typedef long long ll;
typedef long double ld;
#define pb push_back
#define F first
#define S second
#define all(a) a.begin(),a.end()
#define vi vector<double>
#define ii pair<double, double>
#define vii vector<ii>
#define si set<double>
#define mi map<double,double>
#define msi map<string, double>
#define vpp pair< pair<double,double> , pair<double,double> >
#define present(container, element) (container.find(element) != container.end()) //for set and map
#define cpresent(container, element) (find(all(container),element) != container.end()) //for vectors
#define REP(i, a, b) \
for(int i = a; i <= b; i++) // a to b, and variable i is local!
#define REPL(i, a, b) \
for(ll i = a; i <= b; i++) // a to b, and variable i is local!
#define tr(container, it) \
for(auto it = container.begin(); it != container.end(); it++)
#define ios ios_base::sync_with_stdio(false);cin.tie(NULL);
using namespace std;
// $ g++ gl.cpp -o gl -lGL -lGLU -lglut- To compile //
float x_1,y_1,x_2,y_2,xmax,xmin,ymax,ymin;
vii vertices;

void Init() {
    glClearColor(1.0,1.0,1.0,0); //clear color-black
    glColor3f(0.0,0.0,0.0); //fill color-white
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0 , 500 , 0 , 500);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);
        glVertex2f(xmin,ymin);
        glVertex2f(xmin,ymax);
        glVertex2f(xmin,ymax);
        glVertex2f(xmax,ymax);
        glVertex2f(xmax,ymax);
        glVertex2f(xmax,ymin);
        glVertex2f(xmax,ymin);
        glVertex2f(xmin,ymin);
        for(int i=0;i<4;i++)
        {
            glVertex2f(vertices[i].F,vertices[i].S);
            glVertex2f(vertices[(i+1)%4].F,vertices[(i+1)%4].S);
        }
    glEnd();
    glFlush();
}

void clippedLine(double u1,double u2) {
    double delta_x = x_2 - x_1;
    double delta_y = y_2 - y_1;
    double cl1_x = x_1 + delta_x*u1;
    double cl2_x = x_1 + delta_x*u2;
    double cl1_y = y_1 + delta_y*u1;
    double cl2_y = y_1 + delta_y*u2;
    cout<<cl1_x<<" "<<cl1_y<<" "<<cl2_x<<" "<<cl2_y<<"\n";
    glBegin(GL_LINES);
        glVertex2f(x_1 + delta_x*u1,y_1 + delta_y*u1);
        glVertex2f(x_1 + delta_x*u2,y_1 + delta_y*u2);
    glEnd();
    // glFlush();
}

void LiangBarsky() {
    double delta_x = x_2 - x_1;
    double delta_y = y_2 - y_1;
    vector<double> p ;
    p.push_back(delta_x);
    p.push_back(-delta_x);
    p.push_back(delta_y);
    p.push_back(-delta_y);
    vector<double>q ;
    q.push_back(xmax - x_1);
    q.push_back(x_1 - xmin);
    q.push_back(ymax - y_1);
    q.push_back(y_1 - ymin);
    double u1 = 0,u2 = 1;
    for (int i = 0; i < 4; ++i) {
        /* code */
        if(p[i] < 0)
            u1 = max(u1,q[i]/p[i]);
        else if(p[i] >0)
            u2 = min(u2,q[i]/p[i]);
        else
            if(q[i] < 0) {
                cout<<"Line outside the clipping window\n";
                return;
            }
    }
    if(u1 > u2) {
        cout<<"Line outside the clipping window\n";
        return;
    }
    else {
        clippedLine(u1,u2);
    }
}

void myKey(unsigned char key,int x,int y) {
    if(key=='l') {
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_LINES);
        glVertex2f(xmin,ymin);
        glVertex2f(xmin,ymax);
        glVertex2f(xmin,ymax);
        glVertex2f(xmax,ymax);
        glVertex2f(xmax,ymax);
        glVertex2f(xmax,ymin);
        glVertex2f(xmax,ymin);
        glVertex2f(xmin,ymin);
        glEnd();
        for(int i=0;i<4;i++) {
            x_1 = vertices[i].F; y_1 = vertices[i].S;
            x_2 = vertices[(i+1)%4].F; y_2 = vertices[(i+1)%4].S;
            LiangBarsky();
        }
        glFlush();
    }
}

int main(int argc, char **argv) {
    /* code */
    int n = 4;
    cout<<"Enter the four vertices :\n";
    for (int i = 0; i < 4; ++i) {
        ii c;
        cin>>c.F>>c.S;
        vertices.pb(c);
    }
    cout<<"Enter the xmin and xmax of clipping window :\n";
    cin>>xmin>>xmax;
    cout<<"Enter the ymin and ymax of clipping window :\n";
    cin>>ymin>>ymax;
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (500,500);
    glutInitWindowPosition (700,7000);
    glutCreateWindow ("Polygon Clipping");
    Init();
    glutDisplayFunc(display);
    glutKeyboardFunc(myKey);
    // glutCreateWindow ("Liang Barsky's Line Clipping");
    // Init();
    // glutDisplayFunc(LiangBarsky);
    glutMainLoop();
    return 0;
}
