#include<vector>
#include <set>
#include <algorithm>
#include<iostream>
using namespace std;

int quad(pair<int, int> p);

bool compare(pair<int, int> p1, pair<int, int> q1);

vector<pair<int, int> > merger(vector<pair<int, int> > a,
    vector<pair<int, int> > b);

vector<pair<int, int> > bruteHull(vector<pair<int, int> > a);

vector<pair<int, int>> findHull(vector<pair<int, int>> a);

vector<pair<int, int>> removePoint(vector<pair<int, int>> a,
    vector<pair<int, int>> hull,
    pair<int, int> p);


