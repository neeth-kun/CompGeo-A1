#include <iostream>
#include <stack>
#include <vector>

using namespace std;

struct Point;

Point nextToTop(stack<Point>& S);
int swap(Point& p1, Point& p2);
int distSq(Point p1, Point p2);
int orientation(Point p, Point q, Point r);