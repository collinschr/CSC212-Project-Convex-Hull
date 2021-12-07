#include <iostream>
#include <vector>
#include <utility> // pair
#include <stack>
#include <ctime>

class Convex{
    private:
        // points is all
        // stack is convex hull
        std::vector<std::pair<double, double> > points;
        std::stack<std::pair<double, double> > hull;

        // offsets (for original bounds if needed)
        int count_x;
        int count_y;

        // helper functions for findConvex
        // find angles with respect to origin and sort
        void sortByAngle();
        void quickSortByAngle(int low, int high);
        int partition(int low, int high);
        double computeAngle(double x, double y);


        // see if above 180 degrees to pop
        double interiorAngle(double x1, double y1, double x2, double y2,
        double z1, double z2);

        // make sure all points are positive (just translate)
        // also puts lowest value in beginning of array
        void translate();

        // function to get point before to not alter points that much
        std::pair<double, double> nextToTop();


    public:
        // constructors
        Convex(std::vector<std::pair<double, double> > points);

        // getters
        int getCount_x();
        int getCount_y();

        // helper functions to print/debug
        void printVec();
        void callTranslate();
        void callSortByAngle();
        void callQuickSortByAngle();

        // final stack for convex hull
        std::stack<std::pair<double, double> > * findConvex(std::string choose_sorting);
};