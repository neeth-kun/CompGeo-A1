#include<vector>
#include<iostream>
#include "dynamichull_add.h"
#include "dynamichull_sub.h"

using namespace std; 

int main()
{
    // the set of points in the convex hull
    vector<pair<int, int> > a;
    a.push_back(make_pair(0, 0));
    a.push_back(make_pair(1, -4));
    a.push_back(make_pair(-1, -5));
    a.push_back(make_pair(-5, -3));
    a.push_back(make_pair(-3, -1));
    a.push_back(make_pair(-1, -3));
    a.push_back(make_pair(-2, -2));
    a.push_back(make_pair(-1, -1));
    a.push_back(make_pair(-2, -1));
    a.push_back(make_pair(-1, 1));

    int n = a.size();

    // sorting the set of points according 
    // to the x-coordinate 
    sort(a.begin(), a.end());
    vector<pair<int, int> >hull = findHull(a);

    cout << "Convex Hull:\n";
    for (auto e : hull)
        cout << "(" << e.first << ", " << e.second << ") ";
    cout << "\n";
    int x, y;
    char c;
    cout << "To add a point, press '+'. To remove a point, press '-'" << endl;
    cin >> c;
    cout << "enter 2 values: \n";
    cin >> x;
    cin >> y;
    pair<int, int> p = { x, y };
    if (c == '+')
        addPoint(hull, p);
    else if (c == '-')
        hull = removePoint(a, hull, p);

    // Print the modified Convex Hull
    cout << "\nModified Convex Hull:\n";
    for (auto e : hull)
        cout << "(" << e.first << ", " << e.second << ") ";

    return 0;
}