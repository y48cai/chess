#ifndef _GRAPHICS_
#define _GRAPHICS_
#include <string>
#include "window.h"

class Graphics{
    Xwindow xwin;
    int n;//rectangles per row
    int len;//length of each rectangle
    int mar;//margin
    public:
    void displayResult(std::string msg);//show msg to the graphics display
    Graphics(int n=8, int width=500, int height=500);
    void notify(int row,int col, std::string s, int colour=1);
};


#endif
