#include "convex.h"
#include <math.h>

// constructor
Convex::Convex(std::vector<std::pair<double, double> > points)
{
    this->points = points;

    // counters
    count_x = 0;
    count_y = 0;
}

// offset in x-direction
int Convex::getCount_x()
{
    return count_x;
}

// offset in y-direction
int Convex::getCount_y()
{
    return count_y;
}

// HELPER FUNCTIONS
// function to test to see what points looks like
void Convex::printVec()
{
    for(int i = 0; i < points.size(); i++)
    {
        std::cout << i << " (" << points[i].first << "," << points[i].second << ")" << std::endl;
    }
}

// public Translate
void Convex::callTranslate()
{
    translate();
}

// public sortByAngle
void Convex::callSortByAngle()
{
    sortByAngle();
}

void Convex::callQuickSortByAngle()
{
    quickSortByAngle(0, points.size() - 1);
}

// next one used in sortByAngle
// sorting angle determination
double Convex::computeAngle(double x, double y)
{
    const double PI = 3.1415926535897;
    // if on same line, return 0;
    if(y == points[0].second)
        return 0;
    double magnitudeY = y-points[0].second;
    double magnitudeX = x-points[0].first;
    // angle should be bigger if on left of lowest
    if(magnitudeX<=0)
    {
        magnitudeX = abs(magnitudeX);
        double angle = magnitudeX/magnitudeY;
        angle = atan(angle);
        angle = angle*(180/PI);
        return angle+90;
    }
    // for the right side
    else
    {
        double angle = magnitudeY/magnitudeX;
        angle = atan(angle);
        angle = angle*(180/PI);
        return angle;
    }
}

// next are used exclusively in findConvex
// checking if above 180 degrees or not
double Convex::interiorAngle(double x1, double x2, double y1, double y2,
double z1, double z2)
{
    double angle = (y1 - x1)*(z2 - x2) - (y2 - x2)*(z1 - x1);
    return angle;
}

// returning the one after the top in stack
std::pair<double, double> Convex::nextToTop()
{
    std::pair<double, double> top = std::make_pair(hull.top().first, hull.top().second);
    hull.pop();
    std::pair<double, double> next = std::make_pair(hull.top().first, hull.top().second);
    hull.push(top);
    return next;
}
int Convex::partition(int low, int high){
    int pi = low + (high - low) / 2;
    double pivot = computeAngle(points[pi].first, points[pi].second);
    int i = low, j = high;
    std::pair<double, double> temp;
    temp = std::make_pair(0, 0);
    while(i <= j) {

        while(computeAngle(points[i].first, points[i].second) < pivot) {
            i++;

        }

        while(computeAngle(points[j].first, points[j].second) > pivot) {
            j--;
        }

        if(i <= j) {
            temp = points[i];
            points[i] = points[j];
            points[j] = temp;
            i++;
            j--;
        }
    }

    return i;
}

void Convex::quickSortByAngle(int low, int high){
    if(low < high) {
        
        int pi = partition(low, high);

        quickSortByAngle(low, pi - 1);

        quickSortByAngle(pi, high);
    }

    for(int i = 1; i < points.size()-1; i++)
    {
        int minAngle;
        minAngle = computeAngle(points[i].first, points[i].second);
        // gets rid of duplicates
        if(minAngle == computeAngle(points[i+1].first, points[i+1].second))
        {
            // compute distance
            // whichever distance is smaller get rid of that point
            if(sqrt(pow(points[i].first, 2) + pow(points[i].second, 2)) > 
            sqrt(pow(points[i+1].first, 2) + pow(points[i+1].second, 2)))
            {
                points.erase(points.begin()+i+1);
            }
            else
            {
                points.erase(points.begin()+i);
            }
        }
    }

}





// first part of algorithm
// also put lowest x and y coordinate in first spot of vector
void Convex::translate()
{
    // counters to add to everything in end
    // temp pair to store lowest point
    // counters are private in convex.h
    // they are called count_x and count_y

    std::pair<double, double> lowest = std::make_pair(points[0].first, points[0].second);
    // to switch easily in end
    int indexLow = 0;

    for(int i = 0; i < points.size(); i++)
    {
        // first two if's determine offset
        if(points[i].first < 0 && count_x < (points[i].first * -1) + 1)
        {
            count_x = (points[i].first * -1) + 1;
        }

        if(points[i].second < 0 && count_y < (points[i].second * -1) + 1)
        {
            count_y = (points[i].second * -1) + 1;
        }
        // replace lowest to get true lowest value
        if(lowest.second > points[i].second)
        {
            lowest = points[i];
            indexLow = i;
        }
        else if(lowest.second == points[i].second)
        {
            if(lowest.first > points[i].first)
            {
                lowest = points[i];
                indexLow = i;
            }
        }
    }

    // switch lowest value with first number
    points[indexLow] = points[0];
    points[0] = lowest;

    // loop through again to add offset
    for(int i = 0; i < points.size(); i++)
    {
        points[i].first += count_x;
        points[i].second += count_y;
    }
}

// second part of algorithm
// sort by the polar angle from the lowest point
void Convex::sortByAngle()
{
    // temp pair to swap values
    std::pair<double, double> temp;
    temp = std::make_pair(0, 0);
    double minAngle = 0.0;
    int minidx = 0;

    for(int i = 1; i < points.size(); i++)
    {
        // calculate new min angle
        minAngle = computeAngle(points[i].first, points[i].second);
        minidx = i;
        for(int j = i+1; j < points.size(); j++)
        {
            // selection sort to sort by angle size
            if(minAngle > computeAngle(points[j].first, points[j].second))
            {
                minAngle = computeAngle(points[j].first, points[j].second);
                minidx = j;
            }
        }
        // swap
        if(minidx != i)
        {
            temp = points[minidx];
            points[minidx] = points[i];
            points[i] = temp;
        }
    }

    // loop through again and get rid of duplicates
    for(int i = 1; i < points.size()-1; i++)
    {
        minAngle = computeAngle(points[i].first, points[i].second);
        // gets rid of duplicates
        if(minAngle == computeAngle(points[i+1].first, points[i+1].second))
        {
            // compute distance
            // whichever distance is smaller get rid of that point
            if(sqrt(pow(points[i].first, 2) + pow(points[i].second, 2)) > 
            sqrt(pow(points[i+1].first, 2) + pow(points[i+1].second, 2)))
            {
                points.erase(points.begin()+i+1);
            }
            else
            {
                points.erase(points.begin()+i);
            }
        }
    }
}








std::stack<std::pair<double, double> > * Convex::findConvex()
{
    // let points be the list of points (in class)
    // let stack = empty_stack()
    std::pair<double, double> x = std::make_pair(0, 0);

    // find the lowest y-coordinate and leftmost point, called P0
    translate();

    // sort points by polar angle with P0,
    // if several points have the same polar angle then only keep the farthest
    //sortByAngle();
    quickSortByAngle(0, points.size() - 1);

    // test case to see if there are not enough points
    if(points.size() <= 3)
    {
        for(int i = 0; i < points.size(); i++)
        {
            hull.push(points[i]);
        }
        return &hull;
    }

    // start stack
    hull.push(points[0]);
    hull.push(points[1]);

    // for point in points:
    for(int i = 2; i < points.size(); i++)
    {
        // pop the last point from the stack if we turn clockwise to reach this point
        // while count stack > 1 and ccw(next_to_top(stack), top(stack), point) <= 0:
        while(hull.size() > 1 && interiorAngle(nextToTop().first,
        nextToTop().second, hull.top().first, hull.top().second,
        points[i].first, points[i].second) <= 0)
        {
            // pop stack
            hull.pop();
        }
        // push point to stack
        x = points[i];
        hull.push(x);
    // end
    }
    return &hull;
}