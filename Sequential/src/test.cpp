#include <iostream>

#include "define.h"

int main() {
    // Calculate the number of rows
    int numRows = sizeof(triTable) / sizeof(triTable[0]);

    // Calculate the number of columns in each row
    int numCols = sizeof(triTable[0]) / sizeof(triTable[0][0]);

    // Print the results
    std::cout << "Number of rows: " << numRows << std::endl;
    std::cout << "Number of columns: " << numCols << std::endl;

    return 0;
}