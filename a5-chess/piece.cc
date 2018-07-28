#include "piece.h"
#include <string>
#include <vector>
using namespace std;

Piece::Piece(string name, int number):name{name},number{number}{}

Piece::~Piece(){};

string Piece::getName(){return name;}

int Piece::getNumber(){return number;}

int Piece::getSteps(){return steps;}

void Piece::stepsIncrement(){ steps++;}

void Piece::stepsDecrement(){ steps--;}

string Piece::getPos(){ return pos;}

int Piece::nextPosLen(){return static_cast<int>(nextPos.size());}

string Piece::nextPosAt(int index){return nextPos[index];}

void Piece::setPos(string pos){ this->pos=pos;}

void Piece::addNextPos(string nextPos){
    this->nextPos.push_back(nextPos);
}

void Piece::deleteNextPos(string nextPos){
    for (int i=0; i<nextPosLen(); ++i){
        if (this->nextPos[i]==nextPos){
            this->nextPos.erase(this->nextPos.begin()+i);
            break;
        }
    }
}

void Piece::clearNextPos(){
    nextPos.clear();
}

void Piece::pushHistoryPos(string pos){
    historyPos.push_back(pos);
}

void Piece::popHistoryPos(){
    historyPos.pop_back();
}

int Piece::historyPosLen(){
    return static_cast<int>(historyPos.size());
}

string Piece::lastHistoryPos(){
    string pos=historyPos[static_cast<int>(historyPos.size())-1];
    return pos;
}

