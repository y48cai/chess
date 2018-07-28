#include "graphics.h"
#include "window.h"
#include <cstddef>
#include "tools.h"
#include <string>

using namespace std;

Graphics::Graphics(int size, int width, int height):xwin{width,height}{
    n= size;
    len=500/n;//length of the side of each rectangle to be drawn
    mar=(n-len*n)/2;//margin on the left or upper side of the grid 
    for (int i=0; i<n;++i){//set up the window
        for (int j=0; j<n;++j){
            if ((i%2==0 && j%2==0) || (i%2==1 && j%2==1)){
                xwin.fillRectangle(mar+(j+n/2)*len,(mar+(i+n/2)*len),len*0.95,len*0.95,2);
            }else{
                xwin.fillRectangle(mar+(j+n/2)*len,(mar+(i+n/2)*len),len*0.95,len*0.95,3);
            }
            xwin.drawString(mar+(j+n/2)*len,(mar+(i+n/2+0.09)*len),to_Position(7-i,j),1);
        }

    }
}

void Graphics::notify(int row, int col, string s, int colour){
    xwin.drawBigString(-(mar+(n-1-(col)-n/2+0.5)*len),-(mar+(row-n/2+0.3)*len),s, colour);
}

void Graphics::displayResult(string msg){
    xwin.drawBigString(mar+(n+n/2)/2 * len, mar+(n+n/2)/2 * len,msg,4);
}
