#ifndef _MOVE_
#define _MOVE_
#include "piece.h"
#include "cell.h"
#include <string>
#include <vector>

class Player;
class TextDisplay;
class Graphics;

class Move{
    std::vector<std::vector<Cell*>> board;//cells on board
    std::vector<Piece*> white;//pieces of white player
    std::vector<Piece*> black;//pieces of black player
    std::vector<std::vector<std::string>> history;//record the history. each record contains 2 strings, first is the name of piece moved, second is the piece being captured. i.e. {"k0","P1"}
    float whiteScore=0;
    float blackScore=0;
    std::string result=""; //became "white","black", or "stalemate" when a game is over
    TextDisplay *td;
    Graphics* g;
    void detectNextPos(Piece* piece);//find NextPos for piece and set their effect on board
    void clearNextPos(Piece* piece);//clear all nextPos of piece and their effect on other cells
    void othersRecalculate(Cell* cell);//let others fo cell recalculate nextPos
    void setPiece(Piece* piece, Cell* cell);//set piece on cell
    void unsetPiece(Piece* piece, Cell* cell);//unset a piece on cell
    void move(Cell* cell1, Cell* cell2, Piece* piece);//move piece from cell1 to cell2
    void upgrade(Piece* piece,Cell* cell, std::string type);//piece on cell upgrade to type,it is assume type is correct
    bool dangerousFor(Cell* cell,std::string colour);//check if a cell is dangerous for a colour

    bool availableMoves(std::string colour);//calculate if player with colour still has available moves

    public:
    Move(TextDisplay* td, Graphics* g);
    ~Move();
    void BoardSetUp();//setup board. create new cells
    void clearBoard();//clear all pieces in players and board,clear history
    void set(std::string name, std::string pos);//set a piece with name at pos
    void unset(std::string pos);//unset the piece at pos
    void move(Player* computer);//for computer to generate a move
    void move(std::string colour,std::string pos1, std::string pos2, std::string piece="");//for player of colour,move from pos1 to pos2. might need to upgrade to piece.
    void undo();
    std::string getResult();
    float getWhiteScore();
    float getBlackScore();
    void whiteResign();
    void blackResign();
    void start();//start a new game. set result to "", clear and set up default pieces
    void setUpCheck();//check if requirement met before leaving set up mode, an exception will be thrown if requirement does not meet
    bool ifIncheck(std::string colour);
};

#endif 
