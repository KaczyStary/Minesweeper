#include "GamePanel.h"

int GamePanel::getWidth() const {
    return width;
}

void GamePanel::setWidth(int width) {
    GamePanel::width = width;
}

int GamePanel::getHeight() const {
    return height;
}

void GamePanel::setHeight(int height) {
    GamePanel::height = height;
}

GameMode GamePanel::getGameMode() const {
    return gameMode;
}

void GamePanel::setGameMode(GameMode gameMode) {
    GamePanel::gameMode = gameMode;
}

GameState GamePanel::getGameState() const {
    return gameState;
}

void GamePanel::setGameState(GameState gameState) {
    GamePanel::gameState = gameState;
}

int GamePanel::getScale() const {
    return scale;
}

GamePanel::GamePanel(int width, int height,int scale, GameMode gameMode) : width(width), height(height),scale(scale), gameMode(gameMode) {

}

int GamePanel::minesAroundField(int col, int row) {
    int minesAroundField = 0;

    //UPPER LIMIT
    if (col==0&&row!=0&&row!=(getWidth()-1)) {
        for (int iCol = col; iCol <= col + 1; ++iCol) {
            for (int jRow = row - 1; jRow <= row + 1; ++jRow) {
                if (boardVector[iCol][jRow].hasMine) {
                    minesAroundField++;
                }
                if (col == iCol && row == jRow) {
                    if (boardVector[iCol][jRow].hasMine) {
                        minesAroundField--;
                    }
                }
            }
        }
        //LOWER LIMIT
    }else if (col==getHeight()-1&&row!=0&&row!=(getWidth()-1)) {
        for (int iCol = col-1; iCol <= col; ++iCol) {
            for (int jRow = row - 1; jRow <= row + 1; ++jRow) {
                if (boardVector[iCol][jRow].hasMine) {
                    minesAroundField++;
                }
                if (col == iCol && row == jRow) {
                    if (boardVector[iCol][jRow].hasMine) {
                        minesAroundField--;
                    }
                }
            }
        }
        //LEFT LIMIT
    }else if (row==0&&col!=0&&col!=getHeight()-1) {
        for (int iCol = col-1; iCol <= col+1; ++iCol) {
            for (int jRow = row; jRow <= row + 1; ++jRow) {
                if (boardVector[iCol][jRow].hasMine) {
                    minesAroundField++;
                }
                if (col == iCol && row == jRow) {
                    if (boardVector[iCol][jRow].hasMine) {
                        minesAroundField--;
                    }
                }
            }
        }
        //RIGHT LIMIT
    }else if (row==getWidth()-1&&col!=0&&col!=getHeight()-1) {
        for (int iCol = col-1; iCol <= col+1; ++iCol) {
            for (int jRow = row-1; jRow <= row; ++jRow) {
                if (boardVector[iCol][jRow].hasMine) {
                    minesAroundField++;
                }
                if (col == iCol && row == jRow) {
                    if (boardVector[iCol][jRow].hasMine) {
                        minesAroundField--;
                    }
                }
            }
        }
        // [0][0]
    }else if (col==0&&row==0) {
        for (int iCol = col; iCol <= col+1; ++iCol) {
            for (int jRow = row; jRow <= row + 1; ++jRow) {
                if (boardVector[iCol][jRow].hasMine) {
                    minesAroundField++;
                }
                if (col == iCol && row == jRow) {
                    if (boardVector[iCol][jRow].hasMine) {
                        minesAroundField--;
                    }
                }
            }
        }
        // [0][LAST]
    }else if (col==0&&row==getWidth()-1) {
        for (int iCol = col; iCol <= col+1; ++iCol) {
            for (int jRow = row-1; jRow <= row; ++jRow) {
                if (boardVector[iCol][jRow].hasMine) {
                    minesAroundField++;
                }
                if (col == iCol && row == jRow) {
                    if (boardVector[iCol][jRow].hasMine) {
                        minesAroundField--;
                    }
                }
            }
        }
        // [LAST][LAST]
    }else if (col==getHeight()-1&&row==getWidth()-1) {
        for (int iCol = col-1; iCol <= col; ++iCol) {
            for (int jRow = row-1; jRow <= row; ++jRow) {
                if (boardVector[iCol][jRow].hasMine) {
                    minesAroundField++;
                }
                if (col == iCol && row == jRow) {
                    if (boardVector[iCol][jRow].hasMine) {
                        minesAroundField--;
                    }
                }
            }
        }
        //[LAST][0]
    }else if (col==getHeight()-1&&row==0) {
        for (int iCol = col-1; iCol <= col; ++iCol) {
            for (int jRow = row; jRow <= row+1; ++jRow) {
                if (boardVector[iCol][jRow].hasMine) {
                    minesAroundField++;
                }
                if (col == iCol && row == jRow) {
                    if (boardVector[iCol][jRow].hasMine) {
                        minesAroundField--;
                    }
                }
            }
        }
        // OTHER
    }else{
        for (int iCol = col-1; iCol <= col+1; ++iCol) {
            for (int jRow = row - 1; jRow <= row + 1; ++jRow) {
                if (boardVector[iCol][jRow].hasMine){
                    minesAroundField++;
                }
                if (col == iCol && row == jRow) {
                    if (boardVector[iCol][jRow].hasMine) {
                        minesAroundField--;
                    }
                }
            }
        }
    }
    return minesAroundField;
}

bool GamePanel::isRightClick() const {
    return rightClick;
}

void GamePanel::setRightClick(bool rightClick) {
    GamePanel::rightClick = rightClick;
}

bool GamePanel::isLeftClick() const {
    return leftClick;
}

void GamePanel::setLeftClick(bool leftClick) {
    GamePanel::leftClick = leftClick;
}
