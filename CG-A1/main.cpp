//Jeff Chastine
#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include <stack>

using namespace std;

char title[] = "Graham Scan Algorithm";
struct Point
{
    int x, y;
};

Point p0; int n, flag=0;
Point points[100];
stack<Point> S;

// A utility function to find next to top in a stack
Point nextToTop(stack<Point>& S)
{
    Point p = S.top();
    S.pop();
    Point res = S.top();
    S.push(p);
    return res;
}

// A utility function to swap two points
int swap(Point& p1, Point& p2)
{
    Point temp = p1;
    p1 = p2;
    p2 = temp;
    return 0;
}

// A utility function to return square of distance
// between p1 and p2
int distSq(Point p1, Point p2)
{
    return (p1.x - p2.x) * (p1.x - p2.x) +
        (p1.y - p2.y) * (p1.y - p2.y);
}

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(Point p, Point q, Point r)
{
    int val = (q.y - p.y) * (r.x - q.x) -
        (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0; // colinear
    return (val > 0) ? 1 : 2; // clock or counterclock wise
}

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
    // Find the bottommost point
    int ymin = points[0].y, min = 0;
    for (int i = 1; i < n; i++)
    {
        int y = points[i].y;

        // Pick the bottom-most or chose the left
        // most point in case of tie
        if ((y < ymin) || (ymin == y &&
            points[i].x < points[min].x))
            ymin = points[i].y, min = i;
    }

    // Place the bottom-most point at first position
    swap(points[0], points[min]);

    // Sort n-1 points with respect to the first point.
    // A point p1 comes before p2 in sorted output if p2
    // has larger polar angle (in counterclockwise
    // direction) than p1
    p0 = points[0];
    qsort(&points[1], n - 1, sizeof(Point), compare);

    // If two or more points make same angle with p0,
    // Remove all but the one that is farthest from p0
    // Remember that, in above sorting, our criteria was
    // to keep the farthest point at the end when more than
    // one points have same angle.
    int m = 1; // Initialize size of modified array
    for (int i = 1; i < n; i++)
    {
        // Keep removing i while angle of i and i+1 is same
        // with respect to p0
        while (i < n - 1 && orientation(p0, points[i], points[i + 1]) == 0)
            i++;
        points[m] = points[i];
        m++; // Update size of modified array
    }

    // If modified array of points has less than 3 points,
    // convex hull is not possible
    if (m < 3) return;

    // Create an empty stack and push first three points
    // to it.
    
   
    S.push(points[0]);
    S.push(points[1]);
    S.push(points[2]);

    // Process remaining n-3 points
    for (int i = 3; i < m; i++)
    {
        // Keep removing top while the angle formed by
        // points next-to-top, top, and points[i] makes
        // a non-left turn
        while (orientation(nextToTop(S), S.top(), points[i]) != 2)
            S.pop();
        S.push(points[i]);
    }

    // Now stack has the output points, print contents of stack
    Point r = S.top();
    Point q = r;
    if (flag == 0)
    cout << "(" << r.x << ", " << r.y << ") ";
    S.pop();
    while (!S.empty())
    {
        Point p = S.top();
        if(flag==0)
        cout << "(" << p.x << ", " << p.y << ") ";
        drawLine(q.x, q.y, p.x, p.y);
        S.pop();
        q = p;
    }
    flag = 1;
    drawLine(q.x, q.y, r.x, r.y);
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
    glColor3f(1.0, 0.0, 0.);
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
    glTranslatef(0.0f, 0.0f, -20.0f);  // Move right and into the screen
 /**Here, the planar contours are drawn in red.*/
    
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
    glutCreateWindow("Hello, GL");
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