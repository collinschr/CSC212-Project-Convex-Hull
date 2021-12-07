# Convex Hulls Project

# Description

This program takes in a text file containing a set of points and uses the Graham Scan algorithm to determine a Convex Hull. It will output a DOT file containing the Convex Hull which you can visualize using an extension. 
The DOT file will also contain the perimeter and area as well as the distance between each point.

## Installation

We recommend the use of VS Code and/or Visual Studio for running this program.
### Required
An extension that allows for the use of DOT files.

[This](https://marketplace.visualstudio.com/items?itemName=joaompinto.vscode-graphviz) is a great VS Code extension you can use for DOT files.

## Dependencies
Your grid.txt file can look like this:
```c++
    //characters outside of the parenthesis are ignored
    //spaces are entirely ignored
    //different points can also be on the same line
    (251, 3739) (399, 3732)
    (251, 3739),

    //each point must be in this format (point,point) (spaces inside do not matter)
    (251, 3739)
```
There must be at least three points in your grid.txt or you will not have a convex hull.

The write file does not automatically compute the bite size of the final point. You must manually enter that value.
```c++
    // the '+5' here would be the bite size
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
```

## Usage
This program takes in three command line arguments: input text file, output DOT file, and choice of either selectionSort or quickSort.
In order for there to be a Convex Hull, you must have at least 3 points
grid.txt file must be in specific format

IN TERMINAL
```c++
    //NOTE: all cpp files must be compiled

    g++ main.cpp convex.cpp measure.cpp -o prog
    //will output runtime of selection sort as well as DOT file for points in grid.txt
    ./prog grid.txt convexhull.dot selectionSort

    //OR

    //will output runtime of selection sort as well as DOT file for points in grid.txt
    ./prog grid.txt convexhull.dot quickSort

```
## Additional Notes
This program was written with the use of Selection Sort in mind. Quick Sort was added as an additional feature afterward.
grid.txt can be changed to use points of your liking, so long as there are 3 points, you will have a Convex Hull.
convexhull.dot can also be cleared, as the program will write it.
This program can also be adapted into [SFML](https://www.sfml-dev.org/) to produce another visual.


## Contributing
Please do not initiate any pull requests or attempt any edits.
This project is complete.

# Contributions

Code edits were sent via email and also worked off of single driver. Only the final minor edits as well as readme changes were pushed to GitHub.


```c++
Ryan Fish
Main Methods and classes made
    main
        WriteDot
        conversion_file
    Convex.cpp
        Translate
        sortByAngle (selection sort)
        findConvex
        computeAngle
        interiorAngle
    Measure.cpp
        getPerimeter
    Assisted with report and presentation

Christian Collins
    Created repository and pushed code on github
    Wrote readme.md
    Main Program
        Convex.cpp
            Compute area function
            Compute time 
            quickSort
            Comparing quicksort and selection
        Graphs in report
    Assisted with report and presentation 
	
Cristopher Quenes
    Research
        Researched and found real life points for the convex hull from a reliable source
        Found other ways convex hulls is applied in other fields in the real world
        Found graphs that elaborated the idea of convex hulls 
    Assisted with report and presentation
    Main Program
        Assisted with troubleshooting quick & selection sort algorithm 
        Points.txt

Orion Joyner
    SFML
    Researched a way to help create a visual for the algorithm
    Used multimedia platforms to help assist
    Presentation home
    Assisted in with report and presentation
```
## Authors
Ryan Fish, Christian Collins, Cristopher Quenes, Orion Joyner
