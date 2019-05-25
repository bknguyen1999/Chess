CXX = g++
CXXFLAGS = -std=c++14 -Werror=vla -L/usr/X11R6/lib -I/usr/X11R6/include  -Wall -MMD -g
EXEC = chess
OBJECTS = graphicsdisplay.o window.o movegen.o display.o controller.o ai.o player.o main.o board.o move.o normalmove.o capture.o enpassant.o castle.o promotepawn.o square.o textdisplay.o queen.o piece.o rook.o bishop.o pawn.o king.o knight.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${DEPENDS}
.PHONY: clean
