#ifndef _TEXT_
#define _TEXT_
#include <iostream>
#include <string>
#include <vector>

class Cell;

class TextDisplay{
    int n; //length of the grid
    std::vector<std::vector<char>> theDisplay;//position as the key, the display char as its value
    public:
    TextDisplay(int n=8);//push n*n character "-" with their pos into theDisplay
    void notify(Cell* cell);//look at the info of cell, change the char at pos
    friend std::ostream &operator<<(std::ostream &out, const TextDisplay& td);//print theDisplay as a n*n grid
};


#endif
