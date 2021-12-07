#include <iostream>
#include <vector>
#include <utility> // pair
#include <stack>

class Measure
{
    private:
        // convexPoints holds the convex hull in a vector
        // hull is the original stack
        // perimeter holds lengths and perimeter of convex
        // area is area inside convex
        std::vector<std::pair<double, double> > convexPoints;
        std::stack<std::pair<double, double> > hull;
        std::vector<double> perimeter;
        double area;

        // PRIVATE HELPER FUNCTIONS
        double distance(double x1, double y1, double x2, double y2);
        // print perimeter as a vector
        void printPerimeter();

    public:
        // constructor
        Measure(std::stack<std::pair<double, double> > hull);

        // getPerimter returns a vector of distance between all points
        // also has the actual perimeter at the end of the vector
        std::vector<double> * getPerimeter();

        // getArea returns the area of the convex hull
        double getArea();
};