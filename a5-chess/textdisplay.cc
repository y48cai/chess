#include "textdisplay.h"
#include "tools.h"
#include "cell.h"
#include <iostream>
#include <string>
using namespace std;

TextDisplay::TextDisplay(int n):n{n}{
    for (int i=0; i<n;++i){
        vector<char> row;
        for (int j=0; j<n;++j){
            if ((i%2==0 && j%2==0) || (i%2==1 && j%2==1)){
                row.push_back('-');
            }else{
                row.push_back(' ');
            }
        }
        theDisplay.push_back(row);
    }
}

void TextDisplay::notify(Cell* cell){
    Location loc=to_Location(cell->getPos());  
    string curr=cell->getCurrent();
    if (curr==""){
        if ((loc.row%2==0 && loc.col%2==0) || (loc.row%2==1 && loc.col%2==1)){
            theDisplay[loc.row][loc.col]='-';
        }else{
            theDisplay[loc.row][loc.col]=' ';
        }
       return; 
    }
    theDisplay[loc.row][loc.col]=curr[0];

}

ostream& operator<<(ostream& out, const TextDisplay& td){
    for (int i=td.n-1; i>=0; --i){
        out<<i+1<<" ";
        for (int j=0; j<td.n; ++j){
            out<<td.theDisplay[i][j];
        }
        out<<endl;
    }
    out<<"  abcdefgh";
    return out;
}
