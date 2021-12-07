#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <utility> // pair
#include <string>
#include "convex.h"
#include "measure.h"

// isNum gets whether it is a number or a decimal
bool isNum(char num)
{
    // test if number, decimal, or negative sign
    if(std::isdigit(num) || num == '.' || num == '-')
        return true;
    return false;
}

// print vec of pairs for test
void printPoints(std::vector<std::pair<double, double>> * point_vec)
{
    for(int i = 0; i < (*point_vec).size(); i ++)
    {
        // used this to see if could add doubles
        double second = (*point_vec)[i].second;
        std::cout << "(" << (*point_vec)[i].first << "," << second << ")" << std::endl;
    }
}
// print stack of pairs for test
void printPointsStack(std::stack<std::pair<double, double>> *hullFinished)
{
    while(!hullFinished->empty())
    {
        std::cout << "(" << hullFinished->top().first << "," << hullFinished->top().second << ")" << std::endl;
        hullFinished->pop();
    }
}

// put in to DOT file
void WriteDot(std::string file_name, std::stack<std::pair<double, double>> * dotPoints, int offX, int offY, 
std::vector<double> * pConvex, double area){
    // temp pair of first element to point back in dot file
    std::pair<double, double> first = std::make_pair(dotPoints->top().first, dotPoints->top().second);
    // string variable to automatically extend DOT file
    std::string str = std::to_string(first.first);

    // Opens the outfile file, prepares it for writing
    std::ofstream output_file(file_name);

    // header for dot file
    output_file << "digraph convexPoints {\n\t";

    // subgraphs in dot file
    //perimeter
    output_file << "subgraph cluster_0 {\n\t\tstyle=filled;"
    << "\n\t\tcolor=grey;\n\t\tnode [style=filled,color=green,shape=diamond];\n\t\t" <<
    (*pConvex)[pConvex->size()-1] << "\n\t\tlabel = \"Perimeter\"\n";

    //area
    output_file << "\t}subgraph cluster_1 {\n\t\tstyle=filled;"
    << "\n\t\tcolor=grey;\n\t\tnode [style=filled,color=red,shape=diamond];\n\t\t" <<
    area << "\n\t\tlabel = \"Area\"\n\t}\n";
    
    // point to subgraphs
    output_file << "\"Measure\" -> \""<<(*pConvex)[pConvex->size()-1] 
    <<"\"\n\"Measure\" ->\""<< area <<"\"";

    // Loop rows
    for(int i = 0; i < dotPoints->size()+5; i++)
    {
        // Loop points on convex hull
        // dot file requires arrow and next
        output_file << "\"(" << dotPoints->top().first - offX << "," <<  
        dotPoints->top().second - offY << ")\"" << " -> ";
        dotPoints->pop();
        output_file << "\"(" << dotPoints->top().first - offX << "," <<  
        dotPoints->top().second  - offY << ")\"";
        output_file << "[label = <<font color=\"green\">" << (*pConvex)[i] << "</font>>]\n";
    }
    output_file << "\"(" << dotPoints->top().first - offX << "," <<  
    dotPoints->top().second - offX << ")\"" << " -> " << "\"(" << first.first 
    - offX << "," <<  first.second - offY << ")\"";
    output_file << "[label = <<font color=\"green\">" << (*pConvex)[pConvex->size()-2] << "</font>>]\n";
    // close digraph
    output_file << "}";
    output_file.close();
}

// modify conversion to take first number as .first
// then second number as .second
// then go to the next pair
// *precondtion* - must have left parentheses before number, and comma before second
void conversion_file(std::string file_name, std::vector<std::pair<double, double>> * point_vec)
{
        // Create the input filestream - opens the file & prepares it for reading
    std::ifstream file(file_name);

    // Temporary string to hold a single line of the file
    std::string str;
    // temp string and int to convert to sting to int to store in vec
    std::string toAppend = "";
    double dtoAppend = 0;
    // temp vec to hold numbers until added as pair
    std::vector<double> temp;
    std::pair<double, double> tempPair;
    std::string final = "";
    std::string tempString = "";

    // Reads all lines in the file, 1 at at time
    while (std::getline(file, str))
    {
       // get rid of spaces
       std::stringstream ss(str);
       while(std::getline(ss, tempString, ' '))
       {
           final.append(tempString);
       }
       // std::cout << final << std::endl;
       // iterate through string
       for(int i = 0; i < final.length(); i++)
       {
           // if number is after a '(' or ',', put into final
           if(final[i] == '(')
           {
               while(isNum(final[i+1]))
               {
                   toAppend.push_back(final[i+1]);
                   i++;
               }
           }
           else if(final[i] == ',')
           {
               while(isNum(final[i+1]))
               {
                   toAppend.push_back(final[i+1]);
                   i++;
               }
           }
           // test if empty to not do anything if there is nothing in toAppend
           if(!toAppend.empty())
           {
               // convert to double
               dtoAppend = stod(toAppend);
               temp.push_back(dtoAppend);
               // erase toAppend to add numbers by themselves
               while(!toAppend.empty())
               {
                   toAppend.pop_back();
                   // std::cout << toAppend << std::endl;
               }
           }
       }
       // clear so it doesn't include what it had before
       final.clear();
    }

    // temp doubles to add into tempPair
    double first = 0;
    double second = 0;

    for(int i = 0; i < temp.size(); i+=2)
    {
        first = temp[i];
        second = temp[i+1];
        tempPair = std::make_pair(first, second);
        (*point_vec).push_back(tempPair);
    }
}

// only input to start is File_Name
int main(int argc, char * argv[])
{
    std::vector<std::pair<double, double>> points;
    std::string file_name = argv[1];
    std::string output_name = argv[2];
    std::stack<std::pair<double, double>> * convex_hull;
    std::vector<std::pair<double, double>> convexPoints;
    std::vector<double> * perimeter;
    double area = 0;

    conversion_file(file_name, &points);

    // printPoints(&points);

    Convex c = Convex(points);
    // c.getCount_x();
    // c.getCount_y();
    // c.callTranslate();
    // c.printVec();
    // std::cout << std::endl;
    // c.callSortByAngle();
    c.callQuickSortByAngle();
    // c.printVec();
    // printPointsStack(c.findConvex());
    // c.findConvex();
    // std::cout << "x " << x << " and " << "y " << y << std::endl;
    convex_hull = c.findConvex();
    int x = c.getCount_x();
    int y = c.getCount_y();

    Measure m = Measure(*convex_hull);
    perimeter = m.getPerimeter();
    area = m.getArea();
    // printPointsStack(convex_hull);
    
    WriteDot(output_name, convex_hull, x, y, perimeter, area);
}