#include<vector>
#include<iostream>
using namespace std;

int orientation(pair<int, int> a, pair<int, int> b,
    pair<int, int> c);
int sqDist(pair<int, int> p1, pair<int, int> p2);
bool inside(vector< pair<int, int> > a, pair<int, int> p, pair<int, int> mid);
void addPoint(vector<pair<int, int> >& a, pair<int, int> p);
