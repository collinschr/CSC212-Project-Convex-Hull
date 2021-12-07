#include "measure.h"
#include <math.h>

Measure::Measure(std::stack<std::pair<double, double> > hull)
{
    this->hull = hull;
    area = 0;

    // add points from hull to convexPoints (while loop)
    // then add the points back into hull (for loop)
    while(!hull.empty())
    {
        convexPoints.push_back(hull.top());
        hull.pop();
    }
    
    for(int i = convexPoints.size()-1; i >= 0; i--)
    {
        hull.push(convexPoints[i]);
    }
}

// HELPER FUNCTIONS
// prints perimeter
void Measure::printPerimeter()
{
    for(int i = 0; i < perimeter.size(); i++)
    {
        std::cout << "i " << perimeter[i] << std::endl;
    }
}

// disance returns the distance in between two points
double Measure::distance(double x1, double y1, double x2, double y2)
{
    // to return
    double length = 0;
    // difference between x and y values
    double x = x1 - x2;
    double y = y1 - y2;
    // distance formula
    length = sqrt(pow(x, 2) + pow(y, 2));

    return length;
}

// perimeter of convexHull
std::vector<double> * Measure::getPerimeter()
{
    // temp length to get for distance
    double length = 0;
    int size = convexPoints.size();
    double totPerim = 0;

    // loop through convexPoints and find length between all
    for(int i = 0; i < size-1; i++)
    {
        // get length to push
        length = distance(convexPoints[i].first, convexPoints[i].second,
        convexPoints[i+1].first, convexPoints[i+1].second);
        totPerim += length;
        // push length into perimeter
        perimeter.push_back(length);
    }
    // between first and last point
    length = distance(convexPoints[0].first, convexPoints[0].second,
    convexPoints[size - 1].first, convexPoints[size - 1].second);
    totPerim += length;
    
    perimeter.push_back(length);
    perimeter.push_back(totPerim);
    return &perimeter;
}

// gets area of convex hull by using the shoelace formula
double Measure::getArea()
{
    // size of vec
    int n = convexPoints.size();
    // start at last point in vector
    int j = n - 1;
    
    // loop through and add area to itself
    for(int i = 0; i < n; i ++)
    {
        // cross product of all points in convex hull
        area += (convexPoints[j].first + convexPoints[i].first) * (convexPoints[j].second - convexPoints[i].second);
        j = i;
    }

    // divide by 2 for area
    return abs(area/2);
}