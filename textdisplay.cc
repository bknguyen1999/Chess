#include "textdisplay.h"

using namespace std;

TextDisplay::TextDisplay() {}

void TextDisplay::printSquare(Square sqr, pair<int, int> pos) {
    Piece *p = sqr.getPiece();
    if (p == nullptr) {
        char c = ' ';
        if ((pos.first + pos.second) % 2 == 0) {
            c = '_';
        }
        cout << c;
    } else {
        printPiece(p);
    }
}

void TextDisplay::printPiece(Piece *p) {
    char capital = 'A' - 'a';
    if (p->getColour() == Colour::Black) {
        capital = 0;
    }
    PieceType type = p->getType();
    char c = '\0';
    if (type == PieceType::King) {
        c = 'k' + capital;
    } else if (type == PieceType::Queen) {
        c = 'q' + capital;
    } else if (type == PieceType::Knight) {
        c = 'n' + capital;
    } else if (type == PieceType::Rook) {
        c = 'r' + capital;
    } else if (type == PieceType::Bishop) {
        c = 'b' + capital;
    } else if (type == PieceType::Pawn) {
        c = 'p' + capital;
    }
    cout << c;
}

void TextDisplay::printMsg(std::string msg) {
    cout << msg << endl;
}

void TextDisplay::printBoard(Board b) {
    int bSize = b.getSize();
    int rowprint = bSize;
    for (int i = 0; i < bSize; i++) {
        cout << rowprint << " ";
        for (int j = 0; j < bSize; j++) {
            Square sqr = b.getSquare(i, j);
            printSquare(sqr, make_pair(i, j));
        }
        cout << endl;
        rowprint--;
    }
    cout << "~~~~~~~~~~~~" << endl;
    cout << "  " << "abcdefgh" << endl;
}

void TextDisplay::printCODBoard(Board b) {
    int bSize = b.getSize();
    int rowprint = bSize;
    cout << "~~~~~~~~~~~~" << endl;
    for (int i = 0; i < bSize; i++) {
        cout << rowprint << " ";
        for (int j = 0; j < bSize; j++) {
            Square sqr = b.getSquare(i, j);
            printSquare(sqr, make_pair(i, j));
        }
        cout << endl;
        rowprint--;
    }
    cout << "~~~~~~~~~~~~" << endl;
    cout << "  " << "abcdefgh" << endl;
}


void TextDisplay::printKillMsg(std::string msg) {
    cout << msg << endl;
}

void TextDisplay::printInfoMsg(std::string msg) {
    cout << msg << endl;
}

void TextDisplay::printKillStreakMsg(std::string msg) {
	cout << msg << endl;
}
TextDisplay::~TextDisplay() {}
