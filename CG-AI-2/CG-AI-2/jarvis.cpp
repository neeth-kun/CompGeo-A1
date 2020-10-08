#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include <stack>
#include <vector>
#include "point.h"

using namespace std;

char title[] = "Jarvis March";
struct Point
{
    int x, y;
};

Point p0;
int n, flag = 0;
Point points[100];
stack<Point> S;


// A function used by library function qsort() to sort an array of
// points with respect to the first point
int compare(const void* vp1, const void* vp2)
{
    Point* p1 = (Point*)vp1;
    Point* p2 = (Point*)vp2;

    // Find orientation
    int o = orientation(p0, *p1, *p2);
    if (o == 0)
        return (distSq(p0, *p2) >= distSq(p0, *p1)) ? -1 : 1;

    return (o == 2) ? -1 : 1;
}


/**Method draws lines between two 3D points when called. It accepts an input of 6 co-ordinates.*/
void drawLine(float x1, float y1, float x2, float y2)
{
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
    glFlush();
}

// Prints convex hull of a set of n points.
void convexHull(Point points[], int n)
{
    // There must be at least 3 points 
    if (n < 3) return;

    // Initialize Result 
    vector<Point> hull;

    // Find the leftmost point 
    int l = 0;
    for (int i = 1; i < n; i++)
        if (points[i].x < points[l].x)
            l = i;

    // Start from leftmost point, keep moving counterclockwise 
    // until reach the start point again. This loop runs O(h) 
    // times where h is number of points in result or output. 
    int p = l, q;
    do
    {
        // Add current point to result 
        hull.push_back(points[p]);

        // Search for a point 'q' such that orientation(p, x, 
        // q) is counterclockwise for all points 'x'. The idea 
        // is to keep track of last visited most counterclock- 
        // wise point in q. If any point 'i' is more counterclock- 
        // wise than q, then update q. 
        q = (p + 1) % n;
        for (int i = 0; i < n; i++)
        {
            // If i is more counterclockwise than current q, then 
            // update q 
            if (orientation(points[p], points[i], points[q]) == 2)
                q = i;
        }

        // Now q is the most counterclockwise with respect to p 
        // Set p as q for next iteration, so that q is added to 
        // result 'hull' 
        p = q;

    } while (p != l); // While we don't come to first point 

    // Print Result 
    if (flag == 0)
    cout << "(" << hull[0].x << ", "
        << hull[0].y << ") ";
    int i;
    for (i = 1; i < hull.size(); i++)
    {
        if(flag==0)
        cout << "(" << hull[i].x << ", "
            << hull[i].y << ") ";
            drawLine(hull[i].x, hull[i].y, hull[i-1].x, hull[i-1].y);
    }
    flag = 1;
    drawLine(hull[0].x, hull[0].y, hull[i - 1].x, hull[i - 1].y);
    glBegin(GL_POINTS);
    for (int j = 0; j < n; j++)
        glVertex2i(points[j].x, points[j].y);
    glEnd();
    glFlush();
}

    


/** Initialize OpenGL Graphics */
void initGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
    glColor3f(0.0, 1.0, 0.);
    glClearDepth(1.0f);                   // Set background depth to farthest
    glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
    glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
    glShadeModel(GL_SMOOTH);   // Enable smooth shading
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
    glPointSize(8);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 1, 0.1f, 100.0f);
}

void changeViewPort(int w, int h)
{
    glViewport(0, 0, w, h);
}

void render()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix

    glLoadIdentity();                 // Reset the model-view matrix
    glTranslatef(0.0f, 0.0f, -(n * 10));  // Move right and into the screen

    convexHull(points, n);
    glutSwapBuffers();
}



int main(int argc, char* argv[]) {

    int n1, n2;
    cout << "Enter the no. of points:";
    cin >> n;
    cout << "Enter the points" << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> n1;
        cin >> n2;
        points[i] = { n1,n2 };
    }

    // Initialize GLUT
    glutInit(&argc, argv);
    // Set up some memory buffers for our display
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    // Set the window size
    glutInitWindowSize(800, 600);
    // Create the window with the title "Hello,GL"
    glutCreateWindow(title);
    // Bind the two functions (above) to respond when necessary
    glutReshapeFunc(changeViewPort);
    glutDisplayFunc(render);

    // Very important!  This initializes the entry points in the OpenGL driver so we can 
    // call all the functions in the API.
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        fprintf(stderr, "GLEW error");
        return 1;
    }

    initGL();
    glutMainLoop();
    return 0;
}