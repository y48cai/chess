#include "cell.h"
#include <string>
#include <vector>
using namespace std;

Cell::Cell(string pos):pos{pos}{}

string Cell::getPos(){ return pos;}

string Cell::getCurrent(){return current;}

int Cell::othersLen(){ return static_cast<int>(others.size());}

string Cell::otherAt(int index){ return others[index];}

void Cell::setCurrent(string other, int num){
    current=other+to_string(num);
}

void Cell::unsetCurrent(){
    current="";
}

void Cell::addOther(string other, int num){
    this->others.push_back(other+to_string(num));
}

void Cell::deleteOther(string other, int num){//delete other is other is in others. otherwise do nothing
    string piece=other+to_string(num);
    for (int i=0; i<othersLen(); ++i){
        if (piece==others[i]){
            others.erase(others.begin()+i);
            break;
        }
    }
}

void Cell::clearCell(){
    current="";
    others.clear();
}
