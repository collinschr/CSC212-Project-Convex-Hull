# Convex Hulls



## Installation

We recommend the use of VS Code or Visual Studio for running this program.
### Required
Some sort of extension that allows for the use of DOT files.

[This](https://marketplace.visualstudio.com/items?itemName=joaompinto.vscode-graphviz) is a great VS Code extension you can use for DOT files.


## Usage
This program takes in three command line arguments: input text file, output DOT file, and choice of either selectionSort or quickSort
In terminal
```c++
    g++ main.cpp convex.cpp measure.cpp -o prog
    //will output runtime of selection sort as well as DOT file for points in grid.txt
    ./prog grid.txt convexhull.dot selectionSort
    OR
    //will output runtime of selection sort as well as DOT file for points in grid.txt
    ./prog grid.txt convexhull.dot quickSort

```

## Contributing
Please do not initiate any pull requests or attempt any edits.
This project is intended to be complete.
## License
[MIT](https://choosealicense.com/licenses/mit/)