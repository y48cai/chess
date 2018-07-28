CXX=g++
CXXFLAGS=-std=c++14 -Wall -Werror=vla -g -MMD
EXEC=chess
OBJECTS=main.o piece.o cell.o move.o king.o tools.o textdisplay.o knight.o queen.o bishop.o rook.o pawn.o player.o human.o window.o graphics.o computer1.o
DEPENDS=${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11
	
-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
	
.PHONY: clean
