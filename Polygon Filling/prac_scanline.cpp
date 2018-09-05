#include <bits/stdc++.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

#define mod                          1000000007
#define ll                           long long
#define vll                          vector<ll>
#define pll                          vector< pair<ll,ll> >
#define pb                           push_back
#define mp                           make_pair
#define all(v)                       v.begin(),v.end()
#define sz(a)                        (ll)a.size()
#define F                            first
#define S                            second
#define rep(i,a,b)                   for(i=a;i<b;i++)
#define ios                          ios_base::sync_with_stdio(false);cin.tie(NULL);
using namespace std;
ll n;
pll v;
FILE *fp;
struct edgetable{
    ll ymin;
    ll ymax;
    ll x;
    double minv;
};
edgetable et[1000];
void printtable()
{
    ll i;
    rep(i,0,n)
        cout<<"Edge "<<i<<" "<<et[i].ymin<<" "<<et[i].ymax<<endl;
}
bool comp(edgetable a,edgetable b)
{
    return a.ymin<b.ymin;
}

void Init() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0,0.0,0.0,0); //clear color-white
    glColor3f(1.0,1.0,1.0); //fill color-black
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0 , 640 , 0 , 480);
}
/* To draw a edge of polygon */
void drawline(ll x1, ll y1, ll x2, ll y2)
{
    glBegin(GL_LINES);
    glVertex2i(x1,y1);
    glVertex2i(x2,y1);
    glEnd();
    glFlush();
    
}

void polygonfill()
{
    ll i,j;
    
    rep(i,0,n)
    {
        ll x1=v[i].F, x2=v[(i+1)%n].F, y1=v[i].S, y2=v[(i+1)%n].S;
        if(y2==y1) continue;
        double m=(x2-x1)/((y2-y1)*1.0);
        et[i].ymin=min(y2,y1);
        et[i].ymax=max(y2,y1);
        et[i].x = ((y2>y1)?x1:x2);
        et[i].minv = m;
    }
    printtable();
    sort(et,et+n,comp);
    
    ll miny =LLONG_MAX, maxy=LLONG_MIN;
    rep(i,0,n)
    {
        miny=min(miny,et[i].ymin);
        maxy=max(maxy,et[i].ymax);
    }

    rep(i,miny,maxy+1)
    {

        set<ll> emax;
        vll points;
        rep(j,0,n)
        {
            ll in = et[j].x- et[j].minv*(et[j].ymin-i);
            if(et[j].ymin < i && et[j].ymax > i)
            {
                points.pb(in);
            }
            else if(et[j].ymax==i)
            {
                points.pb(in);
                emax.insert(in);
            }
            else if(et[j].ymin==i && emax.find(in)==emax.end())
            {
                points.pb(in);
            }
        }
        sort(points.begin(),points.end());
        cout<<" for scanline "<<i<<" ";
        for(ll k=0;k<points.size();k++) cout << points[k] << " "; cout << endl;
        if(points.size() >0 )
        {
            for(j=0;j<points.size()-points.size()%2;j+=2)
            {
                ll x1=points[j],x2=points[j+1];
                drawline(x1,i,x2,i);
            }
        }
    }
    
}
void readfile()
{
 
    rewind(fp);
    while(!feof(fp) )
    {
        int x1,y1;
        fscanf(fp, "%d,%d", &x1, &y1);
        v.pb(mp(x1,y1));
        n++;
    }
         
         
}

int main(int argc, char **argv)
{
    ios
    ll i,j,k;
    fp=fopen ("polygon.txt","r");
    if ( fp == NULL )
    {
        printf( "Could not open file" ) ;
        return 0;
    }
    readfile();
                        
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(640,0);
    glutInitWindowSize(640,480);
    glutCreateWindow("Scan Line");
    Init();
    glutDisplayFunc(polygonfill);
    glutMainLoop();
    return 0;
}