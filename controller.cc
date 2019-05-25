#include "controller.h"
//no
using namespace std;

Controller::Controller(ChessDisplay *d, int size) : display{d}, curBoard{Board{size}} {}

void Controller::normalGame() {
    // create new standard chess board, make curBoard point at it

    for (int i = 0; i < 8; i++) {
        Piece *b_pawn = new Pawn{Colour::Black};
        curBoard.addPiece(b_pawn, 1, i);
    }

    for (int i = 0; i < 8; i++) {
        Piece *w_pawn = new Pawn{Colour::White};
        curBoard.addPiece(w_pawn, 6, i);
    }

    Piece *w_rook1 = new Rook{Colour::White};
    curBoard.addPiece(w_rook1, 7, 0);
    Piece *w_rook2 = new Rook{Colour::White};
    curBoard.addPiece(w_rook2, 7, 7);
    Piece *w_horse1 = new Knight{Colour::White};
    curBoard.addPiece(w_horse1, 7, 1);
    Piece *w_horse2 = new Knight{Colour::White};
    curBoard.addPiece(w_horse2, 7, 6);
    Piece *w_bish1 = new Bishop{Colour::White};
    curBoard.addPiece(w_bish1, 7, 2);
    Piece *w_bish2 = new Bishop{Colour::White};
    curBoard.addPiece(w_bish2, 7, 5);
    Piece *w_queen = new Queen{Colour::White};
    curBoard.addPiece(w_queen, 7, 3);
    Piece *w_king = new King{Colour::White};
    curBoard.addPiece(w_king, 7, 4);

    Piece *b_rook1 = new Rook{Colour::Black};
    curBoard.addPiece(b_rook1, 0, 0);
    Piece *b_rook2 = new Rook{Colour::Black};
    curBoard.addPiece(b_rook2, 0, 7);
    Piece *b_horse1 = new Knight{Colour::Black};
    curBoard.addPiece(b_horse1, 0, 1);
    Piece *b_horse2 = new Knight{Colour::Black};
    curBoard.addPiece(b_horse2, 0, 6);
    Piece *b_bish1 = new Bishop{Colour::Black};
    curBoard.addPiece(b_bish1, 0, 2);
    Piece *b_bish2 = new Bishop{Colour::Black};
    curBoard.addPiece(b_bish2, 0, 5);
    Piece *b_queen = new Queen{Colour::Black};
    curBoard.addPiece(b_queen, 0, 3);
    Piece *b_king = new King{Colour::Black};
    curBoard.addPiece(b_king, 0, 4);
}


void Controller::insertToBoard(string piecetype, string pos_of_piece, Colour colour) {
    int row;
    int col;
    char letter = pos_of_piece[0] - 'a';
    col = letter;
    row = pos_of_piece[1] - '1';
    row = abs(row-7);
    Square &square = curBoard.getSquare(row, col);
    char type = piecetype[0];
    Piece *piece = nullptr;
    if (type >= 'a') {
        colour = Colour::Black;
        piecetype[0] += 'A' - 'a';
    }
    else {
        colour = Colour::White;
    }
    if (piecetype == "K") {
        King *k1 = new King{ colour };
        square.addPiece(k1);
        piece = k1;
    }
    else if (piecetype == "Q") {
        Queen *q1 = new Queen{ colour };
        square.addPiece(q1);
        piece = q1;
    }
    else if (piecetype == "N") {
        Knight *n1 = new Knight{ colour };
        square.addPiece(n1);
        piece = n1;
    }
    else if (piecetype == "P") {
        Pawn *p1 = new Pawn{ colour };
        square.addPiece(p1);
        piece = p1;
    }
    else if (piecetype == "R") {
        Rook *r1 = new Rook{ colour };
        square.addPiece(r1);
        piece = r1;
    }
    else {
        Bishop *b1 = new Bishop{ colour };
        square.addPiece(b1);
        piece = b1;
    }
    curBoard.addPiece(piece, row, col);
}

void Controller::removeFromBoard(string pos) {
    int col = pos[0] - 'a';
    int row = pos[1] - '1';
    row = abs(row-7);
    if (row >= 0 && row <= 7 && col >= 0 && col <= 7) {
        Square &square = curBoard.getSquare(row, col);
        Piece *piece = square.getPiece();
        if (piece != nullptr) {
            curBoard.removePiece(row, col);
        }
        square.addPiece(nullptr);
    }
    else {
        display->printMsg("Please enter values within bounds.");
    }
}

int Controller::setupGame() {
    Colour colour = Colour::White;

    // main loop
    while (1) {
        try {
            string s1;
            cin >> s1;
            if (s1 == "done") {
                display->printBoard(curBoard);
                if (curBoard.isValid()) {
                    break;
                }
                else {
                    display->printMsg("Board not legal. Continue.");
                    continue;
                }
            } else if (s1 == "+") {
                string type;
                cin >> type;
                string pos;
                cin >> pos;
                insertToBoard(type, pos, colour);
                display->printBoard(curBoard);
            } else if (s1 == "-") {
                string pos;
                cin >> pos;
                removeFromBoard(pos);
                display->printBoard(curBoard);
            } else if (s1 == "=") {
                string colour;
                cin >> colour;
                if (colour == "Black" || colour == "black") {
                    turn = 1;
                } else if (colour == "White" || colour == "white") {
                    turn = 0;
                } else {
                    display->printMsg("Try Again, Wrong input");
                    continue;
                }
            }
        } catch (ios::failure &f) {
            if (cin.eof()) {
                return -1;
            }
            cin.clear();
            string clearcin;
            getline(cin, clearcin);
        }
    }
    return 0;
}

int Controller::start() {
    while (true) {
        string command;
        cin >> command;
        if (command != "game") {
            display->printKillMsg("Illegal Command, Try Again");
            continue;
        }
        string w_player;
        string b_player;
        cin >> w_player;
        if (w_player == "human") {
            Player p1{Colour::White};
            players.emplace_back(p1);
        } else if (w_player.substr(0,8) == "computer") {
            // create White AI
            char num = w_player[9];
            int difficulty = num - 48;
            Player p1{Colour::White, difficulty};
            players.emplace_back(p1);
        } else {
            display->printKillMsg("Error, Enter human or computer[<ai level>]");
            continue;
        }
        cin >> b_player;
        if (b_player == "human") {
            Player p2{Colour::Black};
            players.emplace_back(p2);
        } else if (b_player.substr(0,8) == "computer") {
            // create Black AI
            char num = b_player[9];
            int difficulty = num - 48;
            Player p2{Colour::Black, difficulty};
            players.emplace_back(p2);
        }
        return 1;
    }
    return 1;
}

void Controller::undo() {
    // point curBoard to previous board
    Board temp = history.back();
    history.pop_back();
    curBoard = temp;
}

void Controller::resign() {
    if (turn % 2 == 0) {
        p2Score++;
        display->printMsg("Black Wins!!!");
    } else {
        p1Score++;
        display->printMsg("White Wins!!!");
    }
}

bool Controller::gameOver() {
    State bstate = curBoard.getState();
    if(tacticalNuke == true){
        if (turn % 2 == 0) {
            p2Score++;
        } else {
            p1Score++;
        }
        return true;
    }
    if (bstate == State::WhiteCheck) {
        display->printInfoMsg("White is in Check");
        return false;
    } else if (bstate == State::BlackCheck) {
        display->printInfoMsg("Black is in Check");
        return false;
    } else if (bstate == State::WhiteCheckmate) {
        display->printMsg("Checkmate! Black Wins!");
        p2Score++;
        return true;
    } else if (bstate == State::BlackCheckmate) {
        display->printMsg("Checkmate! White Wins!");
        p1Score++;
        return true;
    } else if (bstate == State::Stalemate) {
        display->printMsg("Stalemate, game is a tie");
        p1Score++;
        p2Score++;
        return true;
    }
    return false;
}

void Controller::printScore() {
    cout << "Final Score: " << endl;
    cout << "White: " << p1Score << endl;
    cout << "Black: " << p2Score << endl;
}

int Controller::convertCoords(char c){
    if(97 <= c && c <= 104){ // convert the column
        return c - 'a';
    }
    else{ // convert the row
        int row = static_cast<int>(c) - 48;
        int ret  = row - 8;
        if(ret < 0){
            ret = ret * -1;
        }
        return ret;
    }
}


void Controller::killMsg(Piece *p, Piece *old) {
    string retstr;
    string killstr;
    if (old->getColour() == Colour::Black) {
        killstr += "Black ";
    } else {
        killstr += "White ";
    }
    if (old->getType() == PieceType::King) {
        killstr += "King ";
    } else if (old->getType() == PieceType::Queen) {
        killstr += "Queen ";
    } else if (old->getType() == PieceType::Knight) {
        killstr += "Knight ";
    } else if (old->getType() == PieceType::Rook) {
        killstr += "Rook ";
    } else if (old->getType() == PieceType::Bishop) {
        killstr += "Bishop ";
    } else if (old->getType() == PieceType::Pawn) {
        killstr += "Pawn ";
    }
    
    
    if (p->getColour() == Colour::Black) {
        retstr += "Black ";
    } else {
        retstr += "White ";
    }
    if (p->getType() == PieceType::King) {
        retstr += "King ";
    } else if (p->getType() == PieceType::Queen) {
        retstr += "Queen ";
    } else if (p->getType() == PieceType::Knight) {
        retstr += "Knight ";
    } else if (p->getType() == PieceType::Rook) {
        retstr += "Rook ";
    } else if (p->getType() == PieceType::Bishop) {
        retstr += "Bishop ";
    } else if (p->getType() == PieceType::Pawn) {
        retstr += "Pawn ";
    }
    if (firstblood) {
        retstr += "Drew First Blood!!";
        firstblood = false;
        display->printKillMsg(retstr);
        return;
    }
    if (p->getConsecutiveKills() > 1) {
        // print doublekill/etc to display->killmsg
        if (p->getConsecutiveKills() == 2) {
            retstr += "DOUBLE KILL!!!";
        } else if (p->getConsecutiveKills() == 3) {
            retstr += "TRIPLE KILL!!!";
        } else if (p->getConsecutiveKills() == 4) {
            retstr += "QUADRA KILL!!!";
        } else if (p->getConsecutiveKills() == 5) {
            retstr += "PENTA KILL!!!";
        } else if (p->getConsecutiveKills() > 5) {
            retstr += "IS GODLIKE!!!!!!!!!!!!";
        }
    } else {
        if (p->getKilledCount() > 1) {
            stringstream ss;
            ss << p->getKilledCount();
            string count;
            ss >> count;
            retstr += count;
            retstr += " Kill Streak!";
        } else if (p->getConsecutiveKills() == 1) {
            display->printKillMsg(retstr + "has slain " + killstr);
            return;
        } else {
            display->printKillMsg(" ");
            return;
        }
    }
    display->printKillMsg(retstr);
}





Board Controller::killStreak(Board b, pair<int,int> dest, Piece *p, Piece *old, bool is_ai){
    Board newBoard = b;
    Piece *killer = newBoard.getSquare(dest.first, dest.second).getPiece();
    int killstreak = p->getKilledCount();
    string streak;
    if(killstreak == 3){
        streak = "3";
    }
    else if(killstreak == 7){
        streak = "7";
    }
    else if(killstreak == 12){
        streak = "12";
    }
    else{
        display->printKillStreakMsg(" ");
        return b;
    }
    if (CODchess) {
        display->printCODBoard(b);
    } else {
        display->printBoard(b);
    }
    string colour;
    if(p->getColour() == Colour::White){
        colour = "White ";
    }
    else{
        colour = "Black";
    }
    string type;
    if(p->getType() == PieceType::King){
        type = "King ";
    }
    else if(p->getType() == PieceType::Queen){
        type = "Queen ";
    }
    else if(p->getType() == PieceType::Knight){
        type = "Knight ";
    }
    else if(p->getType() == PieceType::Bishop){
        type = "Bishop ";
    }
    else if(p->getType() == PieceType::Rook){
        type = "Rook ";
    }
    else if(p->getType() == PieceType::Pawn){
        type = "Pawn ";
    }
    if(killstreak == 3){ //kill an enemy pawn for free
        // CHECK IF THERES ANY PAWNS ON THE BOARD!!!! IF NOT, PRINT 3 KILLSTREAK!
        int enemyPawnsOnBoard = 0;
        vector<Square> pawnsToKill;
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                Square &s = newBoard.getSquare(i,j);
                Piece *cur = s.getPiece();
                if(cur == nullptr){
                    continue;
                }
                if(cur->getColour() != p->getColour() && cur->getType() == PieceType::Pawn){
                    enemyPawnsOnBoard++;
                    pawnsToKill.emplace_back(s);
                }
            }
        }
        if(enemyPawnsOnBoard == 0){
            killMsg(p, old);
            return b;
        }
        if(is_ai == true){
            string msg = colour + type + streak + " Kill Streak! Calling in RCXD.";
            display->printKillStreakMsg(msg);
            random_shuffle(pawnsToKill.begin(), pawnsToKill.end());
            Square choice = pawnsToKill[0];
            pair<int,int> killPos = choice.getPos();
            Square &killSqr = newBoard.getSquare(killPos.first, killPos.second);
            Piece *killed = killSqr.getPiece();
            string killedColour;
            string killedType;
            if(killed->getColour() == Colour::White){
                killedColour = "White ";
            }
            else{
                killedColour = "Black ";
            }
            if(killed->getType() == PieceType::King){
                killedType = "King ";
            }
            else if(killed->getType() == PieceType::Queen){
                killedType = "Queen ";
            }
            else if(killed->getType() == PieceType::Knight){
                killedType = "Knight ";
            }
            else if(killed->getType() == PieceType::Bishop){
                killedType = "Bishop ";
            }
            else if(killed->getType() == PieceType::Rook){
                killedType = "Rook ";
            }
            else if(killed->getType() == PieceType::Pawn){
                killedType = "Pawn ";
            }
            msg = colour + type + "Has Killed " + killedColour + killedType + "With an RCXD!";
            display->printKillStreakMsg(msg);
            killSqr.removePiece();
            return newBoard;
        }
        else{
            string msg = colour + type + streak + " Kill Streak! Calling in RCXD. Which Pawn Do You Want To Kill?";
            display->printKillStreakMsg(msg);
            string coord;
            int row;
            int col;
            Piece *pawn = nullptr;
            while(true){
                cin >> coord;
                char c = coord[0];
                char r = coord[1];
                row = convertCoords(r);
                col = convertCoords(c);
                if(row >= 0 && row <= 7 && col >= 0 && col <= 7){
                    pawn = newBoard.getSquare(row,col).getPiece();
                    if(pawn != nullptr){
                        if(pawn->getType() == PieceType::Pawn && pawn->getColour() != p->getColour()){
                            break;
                        }
                    }
                }
                display->printKillStreakMsg("Invalid Choice. Try Again.");
            }
            Square &pawnSqr = newBoard.getSquare(row,col);
            pawnSqr.removePiece();
            string oppositecolour;
            if(colour == "White "){
                oppositecolour = "Black ";
            }
            else{
                oppositecolour = "White ";
            }
            display->printKillStreakMsg(colour + type + "Killed " + oppositecolour + "Pawn with an RCXD!");
            killer->incKillCount();
            killer->incConsecutiveKills();
            return newBoard;
        }
    }


    else if(killstreak == 7){ // bomb whole row/column, but it can't have the king
        if(is_ai == true){
            string msg = "Calling in AirStrike.";
            display->printKillStreakMsg(msg);
            int mostEnemies = 0;
            int which = 0; // if 0 <= which <= 7, then its a row. If 8<= which <= 15, then its a column.
            for(int i = 0; i < 8; i++){ // checks all rows
                bool hasKing = false;
                int enemiesOnRow = 0;
                for(int j = 0; j < 8; j++){
                    Piece *cur = newBoard.getSquare(i,j).getPiece();
                    if(cur == nullptr){
                        continue;
                    }
                    if(cur->getType() == PieceType::King && cur->getColour() != p->getColour()){
                        hasKing = true;
                        break;
                    }
                    if(cur->getColour() != p->getColour()){
                        enemiesOnRow++;
                    }
                }
                if(hasKing == false){
                    if(enemiesOnRow > mostEnemies){
                        mostEnemies = enemiesOnRow;
                        which = i;
                    }
                }
            }
            for(int i = 8; i < 16; i++){ // checks all columns
                bool hasKing = false;
                int col = i - 8;
                int enemiesOnCol = 0;
                for(int j = 0; j < 8; j++){
                    Piece *cur = newBoard.getSquare(j, col).getPiece();
                    if (cur == nullptr){
                        continue;
                    }
                    if(cur->getType() == PieceType::King && cur->getColour() != p->getColour()){
                        hasKing = true;
                        break;
                    }
                    if(cur->getColour() != p->getColour()){
                        enemiesOnCol++;
                    }
                }
                if(hasKing == false){
                    if(enemiesOnCol > mostEnemies){
                        mostEnemies = enemiesOnCol;
                        which = i;
                    }
                }
            }
            if(which < 8){ // going to bomb a row
                for(int i = 0; i < 8; i++){
                    Square &s = newBoard.getSquare(which, i);
                    Piece *cur = s.getPiece();
                    if(cur == nullptr){
                        continue;
                    }
                    if(cur->getColour() != p->getColour()){
                        s.removePiece();
                        killer->incKillCount();
                        killer->incConsecutiveKills();
                    }
                }
                string row;
                stringstream ss;
                ss << which;
                ss >> row;
                display->printKillStreakMsg(colour + type + "Called in an Airstrike on Row " + row);
                return newBoard;
            }
            else{
                int col = which - 8;
                for(int i = 0; i < 8; i++){ // going to bomb a column
                    Square &s = newBoard.getSquare(i, col);
                    Piece *cur = s.getPiece();
                    if(cur == nullptr){
                        continue;
                    }
                    if(cur->getColour() != p->getColour()){
                        s.removePiece();
                        killer->incKillCount();
                        killer->incConsecutiveKills();
                    }
                }
                string c;
                stringstream ss;
                ss << col;
                ss >> c;
                display->printKillStreakMsg(colour + type + "Called in an Airstrike on Column " + c);
                return newBoard;
            }
        }
        else{
            string msg = "Calling in AirStrike. Which Row/Column Would You Like To Bomb?";
            display->printKillStreakMsg(msg);
            char input;
            int row = -1;
            int col = -1;
            while(true){
                cin >> input;
                if(input >= 'a' && input <= 'h'){
                    col = convertCoords(input);
                    bool legal = true;
                    for(int i = 0; i < 8; i++){
                        Square &s = newBoard.getSquare(i, col);
                        Piece *cur = s.getPiece();
                        if(cur == nullptr){
                            continue;
                        }
                        if(cur->getType() == PieceType::King && cur->getColour() != p->getColour()){ // enemy king is in the column you're trying to bomb
                            legal = false;
                        }
                    }
                    if(legal){
                        break;
                    }
                    display->printKillStreakMsg("Can't Bomb That Column. Try Again.");
                    continue;
                }
                else if(input >= '1' && input <= '8'){
                    row = convertCoords(input);
                    bool legal = true;
                    for(int i = 0; i < 8; i++){ // checks if enemy king is in the row you're trying to bomb
                        Square &s = newBoard.getSquare(row, i);
                        Piece *cur = s.getPiece();
                        if(cur == nullptr){
                            continue;
                        }
                        if(cur->getType() == PieceType::King && cur->getColour() != p->getColour()){ // enemy king is in the row you're trying to bomb
                            legal = false;
                        }
                    }
                    if(legal){
                        break;
                    }
                    display->printKillStreakMsg("Can't Bomb That Row. Try Again.");
                    continue;
                }
                display->printKillStreakMsg("Invalid Choice. Try Again.");
                continue;
            }
            if(row > -1){
                for(int i = 0; i < 8; i++){
                    Square &s = newBoard.getSquare(row,i);
                    Piece *cur = s.getPiece();
                    if(cur == nullptr){
                        continue;
                    }
                    if(cur->getColour() != p->getColour()){
                        s.removePiece();
                        killer->incKillCount();
                        killer->incConsecutiveKills();
                    }
                }
                string r;
                stringstream ss;
                ss << input;
                ss >> r;
                display->printKillStreakMsg(colour + type + "Called in an Airstrike on row " + r);
                return newBoard;
            }
            else if(col > -1){
                for(int i = 0; i < 8; i++){
                    Square &s = newBoard.getSquare(i,col);
                    Piece *cur = s.getPiece();
                    if(cur == nullptr){
                        continue;
                    }
                    if(cur->getColour() != p->getColour()){
                        s.removePiece();
                        killer->incKillCount();
                        killer->incConsecutiveKills();
                    }
                }
                string c;
                char colBomb = input - ('a' - 'A');
                stringstream ss;
                ss << colBomb;
                ss >> c;
                display->printKillStreakMsg(colour + type + "Called in an Airstrike on row " + c);
                return newBoard;
            }
        }
    }
    killstreak = killer->getKilledCount();
    if(killstreak >= 12){ // nuke and end the game
        tacticalNuke = true;
        display->printKillStreakMsg("Tactical Nuke Inbound. " + colour + type + "Has Nuked the Game. Game Over.");
        display->printMsg(" ");
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                Square &s = newBoard.getSquare(i,j);
                s.removePiece();
            }
        }
        return newBoard;
    }
}





int Controller::move() {
    Colour c;
    char col;
    char row;
    Player currplayer;
    if (turn % 2 == 0) {            // getting player
        currplayer = players[0];
    } else {
        currplayer = players[1];
    }

    c = currplayer.getColour();
    pair<int, int> from;
    pair<int, int> dest;

    if (currplayer.getIsAI()) {
        try {
            AI wizard{currplayer.getColour(), currplayer.getAILevel()};
            pair<pair<int, int>, pair<int, int>> moves = wizard.getMove(curBoard);
            from = moves.first;
            dest = moves.second;
            
            Move ai_move{curBoard, from, dest, c};
            
            history.emplace_back(curBoard);
            if (ai_move.isEnPassant()) {
                Move *moveE = new EnPassant{curBoard, from, dest, c};
                Piece *old = nullptr;
                if(c == Colour::White){
                    old = curBoard.getSquare(dest.first + 1, dest.second).getPiece()->clonePiece();
                }
                else{
                    old = curBoard.getSquare(dest.first - 1, dest.second).getPiece()->clonePiece();
                }
                curBoard = moveE->movePiece();
                Piece *p = curBoard.getSquare(dest.first, dest.second).getPiece();
                killMsg(p, old);
                if (CODchess) {
                    Board postKillstreak = killStreak(curBoard, dest, p, old, true);
                    if(postKillstreak == curBoard){ // the killStreak wasn't 3, 5 or 10
                        // do nothing
                    }
                    else{
                        history.emplace_back(curBoard);
                        curBoard = postKillstreak;
                    }
                }
                delete old;
                delete moveE;
                
            } else if (ai_move.isCastle()) {
                Move *moveC = new Castle{curBoard, from, dest, c};
                curBoard = moveC->movePiece();
                display->printKillMsg(" ");
                display->printKillStreakMsg(" ");
                delete moveC;
                
            } else if (ai_move.isPromotePawn()) {
                char promote;
                if (c == Colour::White){
                    promote = 'Q';
                }
                else {
                    promote = 'q';
                }
                bool isKill = false;
                if (curBoard.getSquare(dest.first, dest.second).getPiece()) {
                    isKill = true;
                }
                Move *movePP = new PromotePawn{curBoard, from, dest, c};
                Piece *old = nullptr;
                if (isKill) {
                    old = curBoard.getSquare(dest.first, dest.second).getPiece()->clonePiece();
                }
                curBoard = movePP->movePiece(promote);
                Piece *p = curBoard.getSquare(dest.first, dest.second).getPiece();
                if (isKill) {
                    killMsg(p, old);
                    if (CODchess) {
                        Board postKillstreak = killStreak(curBoard, dest, p, old, true);
                        if(postKillstreak == curBoard){ // the killStreak wasn't 3, 5 or 10
                            // do nothing
                        }
                        else{
                            history.emplace_back(curBoard);
                            curBoard = postKillstreak;
                        }
                    }
                }
                delete old;
                delete movePP;
                
            } else if (ai_move.isCapture()) {
                Move *moveEat = new Capture{curBoard, from, dest, c};
                Piece *old = curBoard.getSquare(dest.first, dest.second).getPiece()->clonePiece();
                curBoard = moveEat->movePiece();
                Piece *p = curBoard.getSquare(dest.first, dest.second).getPiece();
                killMsg(p, old);
                if (CODchess) {
                    Board postKillstreak = killStreak(curBoard, dest, p, old, true);
                    if(postKillstreak == curBoard){ // the killStreak wasn't 3, 5 or 10
                        // do nothing
                    }
                    else{
                        history.emplace_back(curBoard);
                        curBoard = postKillstreak;
                    }
                }
                delete old;
                delete moveEat;
                
            } else if (ai_move.isNormalMove()) {
                Move *moveNormal = new NormalMove{curBoard, from, dest, c};
                curBoard = moveNormal->movePiece();
                delete moveNormal;
                display->printKillMsg(" ");
                display->printKillStreakMsg(" ");
            }
        } catch(InvalidMove &err){
            curBoard = history.back();
            history.pop_back();
            display->printMsg("Illegal Move, Try Again");
            return 0;
        }
    } else {
        try {                       // human shit
            string move_to_make;
            vector<string> list_of_moves;
            while (list_of_moves.size() != 2) {
                cin >> move_to_make;
                list_of_moves.push_back(move_to_make);
                
            }
            if (list_of_moves.size() < 2) {
                curBoard = history.back();
                history.pop_back();
                display->printMsg("not enough commands provided");
                return 0;
            }
            
            col = list_of_moves[0][0]; // defining from and dest
            row = list_of_moves[0][1];
            int rowFrom = convertCoords(row);
            int colFrom = convertCoords(col);
            from = make_pair(rowFrom,colFrom);
            col = list_of_moves[1][0];
            row = list_of_moves[1][1];
            int rowDest = convertCoords(row);
            int colDest = convertCoords(col);
            dest = make_pair(rowDest, colDest);

            Move movehero{curBoard, from, dest, c}; // created move class to decipher type of move

            history.emplace_back(curBoard);
            if (movehero.isEnPassant()) {
                Move *moveE = new EnPassant{curBoard, from, dest, c};
                Piece *old = nullptr;
                if(c == Colour::White){
                    old = curBoard.getSquare(dest.first + 1, dest.second).getPiece()->clonePiece();
                }
                else{
                    old = curBoard.getSquare(dest.first - 1, dest.second).getPiece()->clonePiece();
                }
                curBoard = moveE->movePiece();
                Piece *p = curBoard.getSquare(dest.first, dest.second).getPiece();
                killMsg(p, old);
                if (CODchess) {
                    Board postKillstreak = killStreak(curBoard, dest, p, old, false);
                    if(postKillstreak == curBoard){ // the killStreak wasn't 3, 5 or 10
                        // do nothing
                    }
                    else{
                        history.emplace_back(curBoard);
                        curBoard = postKillstreak;
                    }
                }
                delete old;
                delete moveE;
                
            } else if (movehero.isCastle()) {
                Move *moveC = new Castle{curBoard, from, dest, c};
                curBoard = moveC->movePiece();
                display->printKillMsg(" ");
                display->printKillStreakMsg(" ");
                delete moveC;
                
            } else if (movehero.isPromotePawn()) {
                display->printMsg("What would you like to promote your pawn to?");
                char promote;
                while(cin >> promote){
                    if(promote == 'Q' || promote == 'q' || promote == 'R' || promote == 'r'
                    || promote == 'B' || promote == 'b' || promote == 'N' || promote == 'n'){
                        break;
                    } else {
                        display->printMsg("Invalid piece type. Try again.");
                    }
                }
                bool isKill = false;
                if (curBoard.getSquare(dest.first, dest.second).getPiece()) {
                    isKill = true;
                }
                Move *movePP = new PromotePawn{curBoard, from, dest, c};
                Piece *old = nullptr;
                if (isKill) {
                    old = curBoard.getSquare(dest.first, dest.second).getPiece()->clonePiece();
                }
                curBoard = movePP->movePiece(promote);
                Piece *p = curBoard.getSquare(dest.first, dest.second).getPiece();
                if (isKill) {
                    killMsg(p, old);
                    if (CODchess) {
                        Board postKillstreak = killStreak(curBoard, dest, p, old, false);
                        if(postKillstreak == curBoard){ // the killStreak wasn't 3, 5 or 10
                            // do nothing
                        }
                        else{
                            history.emplace_back(curBoard);
                            curBoard = postKillstreak;
                        }
                    }
                }
                delete old;
                delete movePP;
                
            } else if (movehero.isCapture()) {
                Move *moveEat = new Capture{curBoard, from, dest, c};
                Piece *old = curBoard.getSquare(dest.first, dest.second).getPiece()->clonePiece();
                curBoard = moveEat->movePiece();
                Piece *p = curBoard.getSquare(dest.first, dest.second).getPiece();
                killMsg(p, old);
                if (CODchess) {
                    Board postKillstreak = killStreak(curBoard, dest, p, old, false);
                    if(postKillstreak == curBoard){ // the killStreak wasn't 3, 5 or 10
                        // do nothing
                    }
                    else{
                        history.emplace_back(curBoard);
                        curBoard = postKillstreak;
                    }
                }
                delete old;
                delete moveEat;
                
            } else if (movehero.isNormalMove()) {
                Move *moveNormal = new NormalMove{curBoard, from, dest, c};
                curBoard = moveNormal->movePiece();
                display->printKillMsg(" ");
                display->printKillStreakMsg(" ");
                delete moveNormal;
            }
            
        } catch (InvalidMove &invalid) {
            curBoard = history.back();
            history.pop_back();
            display->printKillMsg("Illegal Move, Try Again");
            return 0;
        }
    }
    return 1;
}


void Controller::play() {
    // check legality of move, then make it or print error
    string command;
    int result = 1;

    while (true) {
	curBoard = Board{8};
        display->printKillMsg(" ");
        display->printInfoMsg(" ");
        display->printKillStreakMsg(" ");
        firstblood = true;
        tacticalNuke = false;
        display->printMsg("To play: Enter <game (human/computer) (human/computer)>");
        result = start();   // adding players in , (game human human)
        if (result == -1) {
            printScore();
            return;
        }
        display->printMsg("Enter <setup> to create a new board instance, else enter <normal>");
        display->printBoard(curBoard);
        while (cin >> command) {
            if (command == "setup" || command == "normal" || command == "COD") {
                break;
            } else {
                display->printMsg("Enter setup or normal");
                continue;
            }
        }
        
        if (command == "setup") { // setting up game
            result = setupGame();
        } else if (command == "normal") {
            normalGame();
        }
        else if(command == "COD"){
            CODchess = true;
            normalGame();
        }
        if (result == -1) { // set up failed
            printScore();
            return;
        } else {
            if (CODchess) {
                display->printCODBoard(curBoard);
            } else {
                display->printBoard(curBoard);
            }
        }
        while (true) {
            display->printInfoMsg(" ");
            if (gameOver()) {
                    break; // play again?
                }
                display->printInfoMsg("Commands: <resign>, <move (a-h)(1-8) (a-h)(1-8)>, <undo>");
                if (turn % 2 == 0) {
                    display->printMsg("White's turn");
                } else {
                    display->printMsg("Black's turn");
                }
                if (cin >> command) {
                    if (command != "resign" && command != "move" && command != "undo") {
                        display->printKillMsg("Invalid command dumbass, Try again");
                        continue;
                    }
                } else {
                    printScore();
                    return;
                }
                if (command == "resign") {
                    resign();
                    break; // play again?
                } else if (command == "move") {
                    result = move();
                    if (CODchess) {
                        display->printCODBoard(curBoard);
                    } else {
                        display->printBoard(curBoard);
                    }
                } else if (command == "undo") {
                    if (turn <= 0) {
                        display->printKillMsg("Cannot Undo, Enter another command");
                        continue;
                    }
                    curBoard = history.back();
                    history.pop_back();
                    turn--;
                    if (CODchess) {
                        display->printCODBoard(curBoard);
                    } else {
                        display->printBoard(curBoard);
                    }
                    display->printKillMsg("Undid last move");
                    continue;
                }
                if (result == -1) {
                    printScore();
                    return;  // end game
                } else if (result == 0) {
                    continue; // loop again, invalid move was made
                }
            turn++;
        }
        display->printInfoMsg("You got murked but would you like to play again? (Y/N)");
        turn = 0;
        while (cin >> command) {
            if (command == "Y"|| command == "y" || command == "N" || command == "n") {
                break;
            } else {
                continue;
            }
        }
        if (command == "Y" || command == "y") {
            continue; // play another
        } else {
            printScore();
            return;   // end game
        }
    }
}

Controller::~Controller() {
    delete display;
}
