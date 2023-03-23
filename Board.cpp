#include <cstdlib>
#include <iostream>
#include "World.h"
#include "PieceArray.h"
#include "RedPiece.cpp"
#include "BlackPiece.cpp"

using namespace std;

class Board : public World{
    public:
    
        RedPiece red_pieces[12];
        BlackPiece black_pieces[12];

        Board() {
            turn = 0;

            red_remaining = 12;
            black_remaining = 12;
            num_remaining = red_remaining + black_remaining;

            gameOver = false;

            int red_id = 0;
            int black_id = 0;

            for (int x = 0; x < 8; x++) {
                for (int y = 0; y < 8; y++) {
                    if (y != 3 && y != 4) {
                        if (y % 2 == 1) {
                            if (x % 2 == 0 && y > 4) {
                                red_pieces[red_id] = *(new RedPiece(red_id, x, y));
                                red_id++;
                            }
                            if (x % 2 == 0 && y < 4) {
                                black_pieces[black_id] = *(new BlackPiece(black_id, x, y));
                                black_id++;
                            }
                        } else if (y % 2 == 0) {
                            if (x % 2 == 1 && y > 4) {
                                red_pieces[red_id] = *(new RedPiece(red_id, x, y));
                                red_id++;
                            }
                            if (x % 2 == 1 && y < 4) {
                                black_pieces[black_id] = *(new BlackPiece(black_id, x, y));
                                black_id++;
                            }
                        }
                    }
                }
            }
        }

        ~Board() {
            
        }

        int getRedRemaining() {
            return red_remaining;
        }

        int getBlackRemaining() {
            return black_remaining;
        }

        void removeRedPiece(int id) {
            turn++;
            red_pieces[id].setIsTaken();
            red_remaining--;
        }

        void removeBlackPiece(int id) {
            turn++;
            black_pieces[id].setIsTaken();
            black_remaining--;
        }

        RedPiece getRedPiece(int id) {
            for (int i = 0; i < 12; i++) {
                if (red_pieces[i].getID() == id) {
                    return red_pieces[i];
                }
            }
            return *(new RedPiece());
        }

        BlackPiece getBlackPiece(int id) {
            for (int i = 0; i < 12; i++) {
                if (black_pieces[i].getID() == id) {
                    return black_pieces[i];
                }
            }
            return *(new BlackPiece());
        }


        Piece getPosition(int x_pos, int y_pos) {
            for (int i = 0; i < 12; i++) {
                if (red_pieces[i].getXPos() == x_pos && red_pieces[i].getYPos() == y_pos && !red_pieces[i].getIsTaken()) {
                    return red_pieces[i];
                }
                if (black_pieces[i].getXPos() == x_pos && black_pieces[i].getYPos() == y_pos && !black_pieces[i].getIsTaken()) {
                    return black_pieces[i];
                }
            }
            Piece * empty = new Piece();
            return *empty;
        }

        void moveRed() {
            int num = rand() % 12;
            if (!red_pieces[num].getIsTaken()) {
                moveRedPiece(red_pieces[num]);
            } else if (red_pieces[num].getIsTaken()) {
                moveRed();
            }
        }

        void moveBlack() {
            int num = rand() % 12;
            if (!black_pieces[num].getIsTaken()) {
                moveBlackPiece(black_pieces[num]);
            } else if (black_pieces[num].getIsTaken()) {
                moveBlack();
            }
        }

        void moveRedPiece(Piece & red_piece) {
            int move = rand() % 4;
            if (move == 0) {
                moveUpLeft(red_piece);
            } else if (move == 1) {
                moveUpRight(red_piece);
            } else if (move == 2) {
                moveDownLeft(red_piece);
            } else if (move == 3) {
                moveDownRight(red_piece);
            }

        }

        void moveBlackPiece(Piece & black_piece) {
            int move = rand() % 4;
            if (move == 0) {
                moveUpLeft(black_piece);
            } else if (move == 1) {
                moveUpRight(black_piece);
            } else if (move == 2) {
                moveDownLeft(black_piece);
            } else if (move == 3) {
                moveDownRight(black_piece);
            }
        }

        void checkWinner() {
            if (red_remaining == 0) {
                cout << "Black is the winner!" << endl;
                gameOver = true;
            } else if (black_remaining == 0) {
                cout << "Red is the winner!" << endl;
                gameOver = true;
            }
        }

        void updateBoard() {
            for(int row = 0; row < 8; row++) {
                for(int col = 0; col < 8; col++) {
                    grid[row][col] = ' ';
                }
            }
            for (int i = 0; i < 12; i++) {
                if (!red_pieces[i].getIsTaken()) {
                    grid[red_pieces[i].getYPos()][red_pieces[i].getXPos()] = red_pieces[i].toString();
                }
                if (!black_pieces[i].getIsTaken()) {
                    grid[black_pieces[i].getYPos()][black_pieces[i].getXPos()] = black_pieces[i].toString();
                }
            }
        }

        int getTurns() {
            return turn;
        }

        bool isOver() {
            return gameOver;
        }

        string toString() {
            string ret = "";
            this->updateBoard();
            for(int i = 0; i < 8; i++) {
                for(int j = 0; j < 8; j++) {
                    ret += grid[i][j] + " ";
                }
                ret += "\n";
            }
            return ret;
        }

        void moveDownLeft(Piece & piece) {
            int new_x = piece.getXPos() - 1;
            int new_y = piece.getYPos() + 1;
            if(checkBounds(new_x, new_y)) {
                if ((piece.getIsKing() && piece.getIsRed()) || (!piece.getIsRed())) {
                    if(grid[new_y][new_x] == 'R' || grid[new_y][new_x] == 'B') {
                        Piece check = getPosition(new_x, new_y);
                        if (piece.matches(check)) {
                            if (!piece.getNoMove()) {
                                piece.setNoMove(true);
                                moveUpLeft(piece);
                            }
                        } else if (!piece.matches(check) && checkBounds(new_x - 1, new_y - 1)) {
                                piece.setPos(new_x - 1, new_y - 1);
                                piece.setNoMove(false);
                                if(piece.getIsRed()) {
                                    removeBlackPiece(check.getID());
                                } else if(!piece.getIsRed()) {
                                    removeRedPiece(check.getID());
                                }
                        }
                    }
                    else if (grid[new_y][new_x] == ' ') {
                        piece.setPos(new_x, new_y);
                        piece.setNoMove(false);
                    }
                }
            } else if(piece.getIsRed()) {
                moveRed();
            } else if(!piece.getIsRed()) {
                moveBlack();
            }
        } 

        void moveDownRight(Piece & piece) {
            int new_x = piece.getXPos() + 1;
            int new_y = piece.getYPos() + 1;
            if(checkBounds(new_x, new_y)) {
                if ((piece.getIsKing() && piece.getIsRed()) || (!piece.getIsRed())) {
                    if(grid[new_y][new_x] == 'R' || grid[new_y][new_x] == 'B') {
                        Piece check = getPosition(new_x, new_y);
                        if (piece.matches(check)) {
                            if (!piece.getNoMove()) {
                                piece.setNoMove(true);
                                moveUpLeft(piece);
                            } 
                        } else if (!piece.matches(check) && checkBounds(new_x + 1, new_y + 1)) {
                                piece.setPos(new_x + 1, new_y + 1);
                                piece.setNoMove(false);
                                if(piece.getIsRed()) {
                                    removeBlackPiece(check.getID());
                                } else if(!piece.getIsRed()) {
                                    removeRedPiece(check.getID());
                                }
                        }
                    }
                    else if (grid[new_y][new_x] == ' ') {
                        piece.setPos(new_x, new_y);
                        piece.setNoMove(false);
                    }
                }
            } else if(piece.getIsRed()) {
                moveRed();
            } else if(!piece.getIsRed()) {
                moveBlack();
            }
        }

        void moveUpLeft(Piece & piece) {
            int new_x = piece.getXPos() - 1;
            int new_y = piece.getYPos() - 1;
            if(checkBounds(new_x, new_y)) {
                if ((piece.getIsKing() && !piece.getIsRed()) || (piece.getIsRed())) {
                    if(grid[new_y][new_x] == 'R' || grid[new_y][new_x] == 'B') {
                        Piece check = getPosition(new_x, new_y);
                        if (piece.matches(check)) {
                            if (!piece.getNoMove()) {
                                piece.setNoMove(true);
                                moveUpLeft(piece);
                            } 
                        } else if (!piece.matches(check) && checkBounds(new_x - 1, new_y - 1)) {
                                piece.setPos(new_x - 1, new_y - 1);
                                piece.setNoMove(false);
                                if(piece.getIsRed()) {
                                    removeBlackPiece(check.getID());
                                } else if(!piece.getIsRed()) {
                                    removeRedPiece(check.getID());
                                }
                        }
                    }
                    else if (grid[new_y][new_x] == ' ') {
                        piece.setPos(new_x, new_y);
                        piece.setNoMove(false);
                    }
                }
            } else if(piece.getIsRed()) {
                moveRed();
            } else if(!piece.getIsRed()) {
                moveBlack();
            }
        } 

        void moveUpRight(Piece & piece) {
            int new_x = piece.getXPos() + 1;
            int new_y = piece.getYPos() - 1;
            if(checkBounds(new_x, new_y)) {
                if ((piece.getIsKing() && !piece.getIsRed()) || (piece.getIsRed())) {
                    if(grid[new_y][new_x] == 'R' || grid[new_y][new_x] == 'B') {
                        Piece check = getPosition(new_x, new_y);
                        if (piece.matches(check)) {
                            if (!piece.getNoMove()) {
                                piece.setNoMove(true);
                                moveUpLeft(piece);
                            }
                        } else if (!piece.matches(check) && checkBounds(new_x - 1, new_y - 1)) {
                                piece.setPos(new_x - 1, new_y - 1);
                                piece.setNoMove(false);
                                if(piece.getIsRed()) {
                                    removeBlackPiece(check.getID());
                                } else if(!piece.getIsRed()) {
                                    removeRedPiece(check.getID());
                                }
                        }
                    }
                    else if (grid[new_y][new_x] == ' ') {
                        piece.setPos(new_x, new_y);
                        piece.setNoMove(false);
                    }
                }
            } else if(piece.getIsRed()) {
                moveRed();
            } else if(!piece.getIsRed()) {
                moveBlack();
            }
        }

        void checkKings() {
            for(int i = 0; i < 12; i++) {
                if(red_pieces[i].getYPos() == 0) {
                    red_pieces[i].king();
                }
                if(black_pieces[i].getYPos() == 7) {
                    black_pieces[i].king();
                }
            }
        }

        void PrintGrid() {
            cout << endl;
            cout << "---------------" << endl;
            for(int i = 0; i < 8; i++) {
                for(int j = 0; j < 8; j++) {
                    cout << grid[i][j] << ' ';
                }
                cout << endl;
            }
            cout << "---------------" << endl;
            cout << endl;
        }

        void UpdateGrid() {
            updateBoard();
        }

        void initGrid() {
            for(int i = 0; i < 8; i++) {
                for(int j = 0; j < 8; j++) {
                    grid[i][j] = ' ';
                }
            }
        }

        bool checkBounds(int xPos, int yPos) {
            return(xPos <= 8 && xPos >= 0 && yPos <= 8 && yPos >= 0);
        }

    private:
        int red_remaining;
        int black_remaining;
        int num_remaining;
        bool gameOver;
};