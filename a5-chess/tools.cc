#include "tools.h"
#include <string>
#include <sstream>

Location to_Location(std::string pos){
    return Location{pos[1]-'1',pos[0]-'a'};
}

std::string to_Position(Location loc){
    std::ostringstream oss;
    oss<<(char(loc.col+'a'))<<(char(loc.row+'1'));
    return oss.str();
}

std::string to_Position(int row, int col){
    std::ostringstream oss;
    oss<<char(col+'a')<<char(row+'1');
    return oss.str();
}

bool ifPosExists(std::string pos){
    Location loc = to_Location(pos);
    if (loc.row>=0 && loc.row<8 && loc.col>=0 && loc.col<8 && pos.length()==2){
        return true;
    }else{
        return false;
    }
}

std::string whatColour(std::string pieceName){
    if (pieceName[0]>'a' && pieceName[0]<'z'){
        return "black";
    }else{
        return "white";
    }
}

bool validPiece(std::string piece){
    char arr[12]={'R','N','B','Q','K','P','r','n','b','q','k','p'};
    bool valid=false;
    for (int i=0; i<12; ++i){
        if (arr[i]==piece[0]){
            valid=true;
            break;
        }
    }
    return valid;
}

