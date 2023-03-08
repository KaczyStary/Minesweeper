//
// Created by huber on 08.03.2023.
//

#include <vector>
#include <iostream>
#include <cstdlib>
#include "MinesweeperBoard.h"

MinesweeperBoard::MinesweeperBoard(int width, int height, GameMode gameMode) {
    this->width=width;
    this->height=height;
    this->gameMode=gameMode;

    generateBoard();
    setMines();
    debugDisplay();
    std::cout<<minesAroundField(9,0);
}


void MinesweeperBoard::debugDisplay() const {

    for (int i = 0; i < boardVector.size(); i++) {
        for (int j = 0; j < boardVector[i].size(); j++) {
            std::cout << "[" << boardVector[i][j].hasMine << boardVector[i][j].hasFlag << boardVector[i][j].isRevealed << "] ";
        }
        std::cout<<std::endl;
    }
}

int MinesweeperBoard::getWidth() const {
    return width;
}

void MinesweeperBoard::setWidth(int width) {
    MinesweeperBoard::width = width;
}

int MinesweeperBoard::getHeight() const {
    return height;
}

void MinesweeperBoard::setHeight(int height) {
    MinesweeperBoard::height = height;
}

void MinesweeperBoard::generateBoard() {

    for (int i = 0; i < getHeight(); i++) {
        std::vector<Field> row;
        for (int j = 0; j < getWidth(); j++) {
            Field field(false, false, false);
            row.push_back(field);
        }
        boardVector.push_back(row);
    }
}

void MinesweeperBoard::setMines() {

    int numberOfMines=0;

    srand(time(NULL));

    int minRandomHeightWidth=0;
    int maxRandomWidth=getWidth();
    int maxRandomHeigh=getHeight();

    //10% OF BOARD FILLED WITH MINES
    if (getGameMode()==EASY){
        numberOfMines=getHeight()*getWidth()*0.10;

        while (numberOfMines>0){

            int randomHeight=rand() % (maxRandomHeigh - minRandomHeightWidth) + minRandomHeightWidth;
            int randomWidth=rand() % (maxRandomWidth - minRandomHeightWidth) + minRandomHeightWidth;

            if (!boardVector[randomHeight][randomWidth].hasMine) {
                boardVector[randomHeight][randomWidth].hasMine = true;
                numberOfMines--;
            }
        }
    }

    //20% OF BOARD FILLED WITH MINES
    else if (getGameMode()==NORMAL){
        numberOfMines=getHeight()*getWidth()*0.2;

        while (numberOfMines>0){

            int randomHeight=rand() % (maxRandomHeigh - minRandomHeightWidth) + minRandomHeightWidth;
            int randomWidth=rand() % (maxRandomWidth - minRandomHeightWidth) + minRandomHeightWidth;

            if (!boardVector[randomHeight][randomWidth].hasMine) {
                boardVector[randomHeight][randomWidth].hasMine = true;
                numberOfMines--;
            }
        }
    }

    //30% OF BOARD FILLED WITH MINES
    else if (getGameMode()==HARD){
        numberOfMines=getHeight()*getWidth()*0.3;

        while (numberOfMines>0){

            int randomHeight=rand() % (maxRandomHeigh - minRandomHeightWidth) + minRandomHeightWidth;
            int randomWidth=rand() % (maxRandomWidth - minRandomHeightWidth) + minRandomHeightWidth;

            if (!boardVector[randomHeight][randomWidth].hasMine) {
                boardVector[randomHeight][randomWidth].hasMine = true;
                numberOfMines--;
            }
        }
    }

    else if(getGameMode()==DEV){

    }
}

GameMode MinesweeperBoard::getGameMode() const {
    return gameMode;
}

void MinesweeperBoard::revealField(int a, int b) {
    if (!boardVector[a][b].isRevealed){
        if (!boardVector[a][b].hasFlag) {
            boardVector[a][b].isRevealed = true;
            if (boardVector[a][b].hasMine==true){
                //GAME LOST
            }
        }
    }
}

void MinesweeperBoard::toggleFlag(int a, int b) {
    if (!boardVector[a][b].isRevealed){
        if (!boardVector[a][b].hasFlag) {
            boardVector[a][b].hasFlag = true;
        }
    }
}

int MinesweeperBoard::minesAroundField(int a, int b) {

    int minesAroundField = 0;
    int fCol;
    int fRow;

    //MIDTABLE
    if (a == 0 && b == 0) { //TOP LEFT CORNER
        for (fCol = a; fCol <= a + 1; fCol++) {
            for (fRow = b; fRow <= b + 1; fRow++) {
                if (boardVector[fCol][fRow].hasMine) {
                    minesAroundField++;
                }
            }
        }
        //TOP RIGHT CORNER
    } else if (a == 0 && b == getWidth() - 1) {
        for (fCol = a; fCol <= a + 1; fCol++) {
            for (fRow = b; fRow >= b-1; fRow--) {
                if (boardVector[fCol][fRow].hasMine) {
                    minesAroundField++;
                }
            }
        }
        //LEFT BOTTOM CORNER
    } else if (a == getHeight()-1 && b == 0) {
        for (fCol = a; fCol >= a - 1; fCol--) {
            for (fRow = b; fRow <= b+1; fRow++) {
                if (boardVector[fCol][fRow].hasMine) {
                    minesAroundField++;
                }
            }
        }
        //BOTTOM RIGHT CORNER
    }else if (a == getHeight()-1 && b == getWidth()-1) {
        for (fCol = a; fCol >= a-1; fCol--) {
            for (fRow = b; fRow >= b-1; fRow--) {
                if (boardVector[fCol][fRow].hasMine) {
                    minesAroundField++;
                }
            }
        }
    }else if (a==0){
        for (fCol = a; fCol <= a + 1; fCol++) {
            for (fRow = b-1; fRow <= b + 1; fRow++) {
                if (boardVector[fCol][fRow].hasMine) {
                    minesAroundField++;
                }
            }
        }
    } else if (a==getHeight()-1) {
        for (fCol = a; fCol >= a-1; fCol--) {
            for (fRow = b-1; fRow <= b + 1; fRow++) {
                if (boardVector[fCol][fRow].hasMine) {
                    minesAroundField++;
                }
            }
        }
    } else if (b==0) {
        for (fCol = a-1; fCol <= a+1; fCol++) {
            for (fRow = b; fRow <= b + 1; fRow++) {
                if (boardVector[fCol][fRow].hasMine) {
                    minesAroundField++;
                }
            }
        }
    } else if (b==getWidth()-1) {
        for (fCol = a-1; fCol <= a+1; fCol++) {
            for (fRow = b-1; fRow <= b; fRow++) {
                if (boardVector[fCol][fRow].hasMine) {
                    minesAroundField++;
                }
            }
        }
    }else {
        for (fCol = a-1; fCol <= a + 1; fCol++) {
            for (fRow = b-1; fRow <= b + 1; fRow++) {
                if (boardVector[fCol][fRow].hasMine) {
                    minesAroundField++;
                }
            }
        }
    }

    if (boardVector[fCol][fRow].hasMine){
        minesAroundField--;
    }

    return minesAroundField;
}


