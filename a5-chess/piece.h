#ifndef _PIECE_
#define _PIECE_
#include "cell.h"
#include <string>
#include <vector>

class Piece{
    std::string name;
    int number;
    int steps=0;//steps moved so far
    std::string pos="";//position of the cell the piece on. might be ""
    std::vector<std::string> nextPos;//next positions it can move to
    std::vector<std::string> historyPos; //a vector of history pos

    public:
    Piece(std::string name,int number);
    virtual ~Piece();
    std::string getName();
    int getNumber();
    int getSteps();
    void stepsIncrement();
    void stepsDecrement();
    std::string getPos();
    int nextPosLen();//length of nextPos
    std::string nextPosAt(int index);//return nextPos[index]
    void setPos(std::string pos);
    void addNextPos(std::string nextPos);
    void deleteNextPos(std::string nextPos);
    void clearNextPos();
    virtual void detectNextPos(std::vector<std::vector<Cell*>>& board)=0;
    void pushHistoryPos(std::string pos);
    void popHistoryPos();
    int historyPosLen();
    std::string lastHistoryPos();
};

#endif
