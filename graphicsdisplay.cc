#include "graphicsdisplay.h"
#include "piece.h"
#include <sstream>
#include <string>
// 
using namespace std;

void GraphicsDisplay::printCODBoard(Board board) {

    w.fillRectangle(0, 0, 500, 500, Xwindow::Black);
    w.fillRectangle(50, 50, 400, 400, Xwindow::White);
    // making the board

    stringstream ss;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (j == 8) {
                if (i == 0) {
                    w.drawString(475, (i * 50) + 75, "8", Xwindow::White);
                } else if (i == 1) {
                    w.drawString(475, (i * 50) + 75, "7", Xwindow::White);
                } else if (i == 2) {
                    w.drawString(475, (i * 50) + 75, "6", Xwindow::White);
                } else if (i == 3) {
                    w.drawString(475, (i * 50) + 75, "5", Xwindow::White);
                } else if (i == 4) {
                    w.drawString(475, (i * 50) + 75, "4", Xwindow::White);
                } else if (i == 5) {
                    w.drawString(475, (i * 50) + 75, "3", Xwindow::White);
                } else if (i == 6) {
                    w.drawString(475, (i * 50) + 75, "2", Xwindow::White);
                } else if (i == 7) {
                    w.drawString(475, (i * 50) + 75, "1", Xwindow::White);
                }
            } else if (i == 8) {
                if (j == 0) {
                    w.drawString(j * 50 + 75, (i * 50) + 75, "a", Xwindow::White);
                } else if (j == 1) {
                    w.drawString(j * 50 + 75, (i * 50) + 75, "b", Xwindow::White);
                } else if (j == 2) {
                    w.drawString(j * 50 + 75, (i * 50) + 75, "c", Xwindow::White);
                } else if (j == 3) {
                    w.drawString(j * 50 + 75, (i * 50) + 75, "d", Xwindow::White);
                } else if (j == 4) {
                    w.drawString(j * 50 + 75, (i * 50) + 75, "e", Xwindow::White);
                } else if (j == 5) {
                    w.drawString(j * 50 + 75, (i * 50) + 75, "f", Xwindow::White);
                } else if (j == 6) {
                    w.drawString(j * 50 + 75, (i * 50) + 75, "g", Xwindow::White);
                } else if (j == 7) {
                    w.drawString(j * 50 + 75, (i * 50) + 75, "h", Xwindow::White);
                }
w.fillRectangle(50,50,2,400, Xwindow::White);  // vertical left
w.fillRectangle(50,50,400,2 , Xwindow::White);
w.fillRectangle(450,50,2, 400, Xwindow::White);
w.fillRectangle(50,450,400,2, Xwindow::White); // horizontal bottom
            } else if ((i + j) % 2 != 0) {
                int y = i * 50;
                int x = j * 50;
	//	w.fillRectangle(x +50, y+50, 50, 50, Xwindow::White);
                w.fillRectangle(x + 50, y + 50, 50, 50, Xwindow::DarkGreen);
	   } else if ((i+j) %2 == 0) {
		int y = i * 50;
		int x = j * 50;
		w.fillRectangle(x + 50, y + 50, 50, 50, Xwindow::Black);
		}
	}
}



    for (int i = 0; i < 9; i++) {
        if (i == 0) {
            w.drawString(25, (i*50) + 75, "8", Xwindow::White);
            w.drawString(i * 50 + 75, 25, "a", Xwindow::White);
        } else if (i == 1) {
            w.drawString(25, (i*50) + 75, "7", Xwindow::White);
            w.drawString(i * 50 + 75, 25, "b", Xwindow::White);
        } else if (i == 2) {
            w.drawString(25, (i*50) + 75, "6", Xwindow::White);
            w.drawString(i * 50 + 75, 25, "c", Xwindow::White);
        } else if (i == 3) {
            w.drawString(25, (i*50) + 75, "5", Xwindow::White);
            w.drawString(i * 50 + 75, 25, "d", Xwindow::White);
        } else if (i == 4) {
            w.drawString(25, (i*50) + 75, "4", Xwindow::White);
            w.drawString(i * 50 + 75, 25, "e", Xwindow::White);
        } else if (i == 5) {
            w.drawString(25, (i*50) + 75, "3", Xwindow::White);
            w.drawString(i * 50 + 75, 25, "f", Xwindow::White);
        } else if (i == 6) {
            w.drawString(25, (i*50) + 75, "2", Xwindow::White);
            w.drawString(i * 50 + 75, 25, "g", Xwindow::White);
        } else if (i == 7) {
            w.drawString(25, (i*50) + 75, "1", Xwindow::White);
            w.drawString(i * 50 + 75, 25, "h", Xwindow::White);
        }
    }

    for (int i = 0; i < 64; i++) {
        int y = i / 8;
        int x = i % 8;
        int z;
        z = abs(y-7);
        x = abs(x - 7);
        Piece *cur {board.getSquare(z, x).getPiece()};
        if (cur != nullptr) {
            PieceType pType{cur->getType()};
            Colour pColour{cur->getColour()};
            if (pType == PieceType::King && pColour == Colour::White) {
                w.drawString(73 + (x * 50), 77 + ((8 - y) * 50) - 50, "w_K", Xwindow::White);
            } else if (pType == PieceType::King && pColour == Colour::Black) {
                w.drawString(73 + (x * 50), 77 + ((8 - y) * 50) - 50, "b_K", Xwindow::White);
            } else if (pType == PieceType::Queen && pColour == Colour::White) {
                w.drawString(73 + (x * 50), 77 + ((8 - y) * 50) - 50, "w_Q", Xwindow::White);
            } else if (pType == PieceType::Queen && pColour == Colour::Black) {
                w.drawString(73 + (x * 50), 77 + ((8 - y) * 50) - 50, "b_Q", Xwindow::White);
            } else if (pType == PieceType::Bishop && pColour == Colour::White) {
                w.drawString(73 + (x * 50), 77 + ((8 - y) * 50) - 50, "w_B", Xwindow::White);
            } else if (pType == PieceType::Bishop && pColour == Colour::Black) {
                w.drawString(73 + (x * 50), 77 + ((8 - y) * 50) - 50, "b_B", Xwindow::White);
            } else if (pType == PieceType::Knight && pColour == Colour::White) {
                w.drawString(73 + (x * 50), 77 + ((8 - y) * 50) - 50, "w_N", Xwindow::White);
            } else if (pType == PieceType::Knight && pColour == Colour::Black) {
                w.drawString(73 + (x * 50), 77 + ((8 - y) * 50) - 50, "b_N", Xwindow::White);
            } else if (pType == PieceType::Rook && pColour == Colour::White) {
                w.drawString(73 + (x * 50), 77 + ((8 - y) * 50) - 50, "w_R", Xwindow::White);
            } else if (pType == PieceType::Rook && pColour == Colour::Black) {
              w.drawString(73 + (x * 50), 77 + ((8 - y) * 50) - 50, "b_R", Xwindow::White);
            } else if (pType == PieceType::Pawn && pColour == Colour::White) {
                w.drawString(73 + (x * 50), 77 + ((8 - y) * 50) - 50, "w_P", Xwindow::White);
            } else if (pType == PieceType::Pawn && pColour == Colour::Black) {
                w.drawString(73 + (x * 50), 77 + ((8 - y) * 50) - 50, "b_P", Xwindow::White);
            }
        }
    }
}




void GraphicsDisplay::printBoard(Board board) {
    w.fillRectangle(0, 0, 500, 500, Xwindow::Magenta);
    w.fillRectangle(50, 50, 400, 400, Xwindow::White);
    // making the board

    stringstream ss;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (j == 8) {
                if (i == 0) {
                    w.drawString(475, (i * 50) + 75, "8", Xwindow::Black);
                } else if (i == 1) {
                    w.drawString(475, (i * 50) + 75, "7", Xwindow::Black);
                } else if (i == 2) {
                    w.drawString(475, (i * 50) + 75, "6", Xwindow::Black);
                } else if (i == 3) {
                    w.drawString(475, (i * 50) + 75, "5", Xwindow::Black);
                } else if (i == 4) {
                    w.drawString(475, (i * 50) + 75, "4", Xwindow::Black);
                } else if (i == 5) {
                    w.drawString(475, (i * 50) + 75, "3", Xwindow::Black);
                } else if (i == 6) {
                    w.drawString(475, (i * 50) + 75, "2", Xwindow::Black);
                } else if (i == 7) {
                    w.drawString(475, (i * 50) + 75, "1", Xwindow::Black);
                }
            } else if (i == 8) {
                if (j == 0) {
                    w.drawString(j * 50 + 75, (i * 50) + 75, "a", Xwindow::Black);
                } else if (j == 1) {
                    w.drawString(j * 50 + 75, (i * 50) + 75, "b", Xwindow::Black);
                } else if (j == 2) {
                    w.drawString(j * 50 + 75, (i * 50) + 75, "c", Xwindow::Black);
                } else if (j == 3) {
                    w.drawString(j * 50 + 75, (i * 50) + 75, "d", Xwindow::Black);
                } else if (j == 4) {
                    w.drawString(j * 50 + 75, (i * 50) + 75, "e", Xwindow::Black);
                } else if (j == 5) {
                    w.drawString(j * 50 + 75, (i * 50) + 75, "f", Xwindow::Black);
                } else if (j == 6) {
                    w.drawString(j * 50 + 75, (i * 50) + 75, "g", Xwindow::Black);
                } else if (j == 7) {
                    w.drawString(j * 50 + 75, (i * 50) + 75, "h", Xwindow::Black);
                }
            } else if ((i + j) % 2 != 0) {
                int y = i * 50;
                int x = j * 50;
                w.fillRectangle(x + 50, y + 50, 50, 50, Xwindow::Cyan);

            }
        }
    }

    for (int i = 0; i < 9; i++) {
        if (i == 0) {
            w.drawString(25, (i*50) + 75, "8", Xwindow::Black);
            w.drawString(i * 50 + 75, 25, "a", Xwindow::Black);
        } else if (i == 1) {
            w.drawString(25, (i*50) + 75, "7", Xwindow::Black);
            w.drawString(i * 50 + 75, 25, "b", Xwindow::Black);
        } else if (i == 2) {
            w.drawString(25, (i*50) + 75, "6", Xwindow::Black);
            w.drawString(i * 50 + 75, 25, "c", Xwindow::Black);
        } else if (i == 3) {
            w.drawString(25, (i*50) + 75, "5", Xwindow::Black);
            w.drawString(i * 50 + 75, 25, "d", Xwindow::Black);
        } else if (i == 4) {
            w.drawString(25, (i*50) + 75, "4", Xwindow::Black);
            w.drawString(i * 50 + 75, 25, "e", Xwindow::Black);
        } else if (i == 5) {
            w.drawString(25, (i*50) + 75, "3", Xwindow::Black);
            w.drawString(i * 50 + 75, 25, "f", Xwindow::Black);
        } else if (i == 6) {
            w.drawString(25, (i*50) + 75, "2", Xwindow::Black);
            w.drawString(i * 50 + 75, 25, "g", Xwindow::Black);
        } else if (i == 7) {
            w.drawString(25, (i*50) + 75, "1", Xwindow::Black);
            w.drawString(i * 50 + 75, 25, "h", Xwindow::Black);
        }
    }

    for (int i = 0; i < 64; i++) {
        int y = i / 8;
        int x = i % 8;
        int z;
        z = abs(y-7);
        x = abs(x - 7);
        Piece *cur {board.getSquare(z, x).getPiece()};
        if (cur != nullptr) {
            PieceType pType{cur->getType()};
            Colour pColour{cur->getColour()};

            if (pType == PieceType::King && pColour == Colour::White) {
                w.drawString(73 + (x * 50), 77 + ((8 - y) * 50) - 50, "w_K");
            } else if (pType == PieceType::King && pColour == Colour::Black) {
                w.drawString(73 + (x * 50), 77 + ((8 - y) * 50) - 50, "b_K");
            } else if (pType == PieceType::Queen && pColour == Colour::White) {
                w.drawString(73 + (x * 50), 77 + ((8 - y) * 50) - 50, "w_Q");
            } else if (pType == PieceType::Queen && pColour == Colour::Black) {
                w.drawString(73 + (x * 50), 77 + ((8 - y) * 50) - 50, "b_Q");
            } else if (pType == PieceType::Bishop && pColour == Colour::White) {
                w.drawString(73 + (x * 50), 77 + ((8 - y) * 50) - 50, "w_B");
            } else if (pType == PieceType::Bishop && pColour == Colour::Black) {
                w.drawString(73 + (x * 50), 77 + ((8 - y) * 50) - 50, "b_B");
            } else if (pType == PieceType::Knight && pColour == Colour::White) {
                w.drawString(73 + (x * 50), 77 + ((8 - y) * 50) - 50, "w_N");
            } else if (pType == PieceType::Knight && pColour == Colour::Black) {
                w.drawString(73 + (x * 50), 77 + ((8 - y) * 50) - 50, "b_N");
            } else if (pType == PieceType::Rook && pColour == Colour::White) {
                w.drawString(73 + (x * 50), 77 + ((8 - y) * 50) - 50, "w_R");
            } else if (pType == PieceType::Rook && pColour == Colour::Black) {
                w.drawString(73 + (x * 50), 77 + ((8 - y) * 50) - 50, "b_R");
            } else if (pType == PieceType::Pawn && pColour == Colour::White) {
                w.drawString(73 + (x * 50), 77 + ((8 - y) * 50) - 50, "w_P");
            } else if (pType == PieceType::Pawn && pColour == Colour::Black) {
                w.drawString(73 + (x * 50), 77 + ((8 - y) * 50) - 50, "b_P");
            }
        }
    }
}


void GraphicsDisplay::printMsg(string msg) {
    w.fillRectangle(0, 560, 500, 20, Xwindow::White);
    int length = msg.size() * 4;
    int position = 200 - (length / 2);
    w.drawString(position, 570, msg, Xwindow::Black);
}

void GraphicsDisplay::printKillMsg(string msg) {
    w.fillRectangle(0, 520, 500, 20, Xwindow::White);
    int length = msg.size() * 4;
    int position = 200 - (length / 2);
    w.drawString(position, 530, msg, Xwindow::Red);
}

void GraphicsDisplay::printKillStreakMsg(string msg) {
    w.fillRectangle(0, 535, 500, 20, Xwindow::White);
    int length = msg.size() * 4;
    int position = 200 - (length / 2);
    w.drawString(position, 545, msg, Xwindow::Red);
}


void GraphicsDisplay::printInfoMsg(string msg) {
    w.fillRectangle(0, 585, 500, 20, Xwindow::White);
    int length = msg.size() * 5;
    int position = 200 - (length / 2);
    w.drawString(position, 595, msg, Xwindow::Black);
}

GraphicsDisplay::~GraphicsDisplay() {}
