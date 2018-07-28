#ifndef _CELL_
#define _CELL_
#include <string>
#include <vector>

class Cell{
    std::string pos;//position 
    std::string current="";//name of the current piece with their number
    std::vector<std::string> others;//names of other pieces with their number. Those pieces are pieces should be notified when there is a change in cell.

    public:
    Cell(std::string pos);
    std::string getPos();
    std::string getCurrent();//name of the current Piece followed by its number
                             //i.e., "K0","k0"
    int othersLen();//length of the others
    std::string otherAt(int index);//return the name of the others at index
    void setCurrent(std::string current, int num);
    void unsetCurrent();
    void addOther(std::string other, int num);
    void deleteOther(std::string other, int num);
    void clearCell();//return to default state
};

#endif
