#include "piece.h"
#include "rook.h"
#include "queen.h"
#include "pawn.h"
#include "bishop.h"
#include "king.h"
#include "knight.h"
#include "controller.h"
#include "board.h"
#include "move.h"
#include "normalmove.h"
#include "capture.h"
#include "enpassant.h"
#include "castle.h"
#include "promotepawn.h"
#include "square.h"
#include "display.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"
#include "ai.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
	ChessDisplay *d;
	if (argc == 2) {
		d = new TextDisplay{};
	} else {
		d = new GraphicsDisplay{};
	}
	Controller newController{d, 8};
	newController.play();
}
