#include "MinesweeperBoard.h"

MinesweeperBoard::MinesweeperBoard(int height, int width, GameMode gameMode) {
    this->width=width;
    this->height=height;
    this->gameMode=gameMode;

}

void MinesweeperBoard::run() {
    gameStart();

}

void MinesweeperBoard::gameStart() {

    generateBoard();
    setMines();
    debugDisplay();
    render();

}

void MinesweeperBoard::debugDisplay() const {

    for (int i = 0; i < boardVector.size(); i++) {
        for (int j = 0; j < boardVector[i].size(); j++) {

                std::cout << "[";
                std::cout <<boardVector[i][j].hasMine;
                if (boardVector[i][j].hasFlag){
                    std::cout <<"F";
                } else{
                    std::cout <<boardVector[i][j].hasFlag;
                }
                if (boardVector[i][j].isRevealed){
                    std::cout<<"R";
                }else {
                    std::cout << boardVector[i][j].isRevealed;
                }
                    std::cout <<"] ";

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

        for (int i = 0; i < getHeight()-1; ++i) {
            for (int j = 0; j <getWidth()-1 ; ++j) {
                if (i==j){
                    boardVector[i][j].hasMine=true;
                }
            }
        }

    }
}

GameMode MinesweeperBoard::getGameMode() const {
    return gameMode;
}

void MinesweeperBoard::revealField(int a, int b) {
    if (!boardVector[a][b].isRevealed){
        if (!boardVector[a][b].hasFlag) {
            boardVector[a][b].isRevealed = true;
            if (boardVector[a][b].hasMine){
                gameState=GAMELOST;
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

int MinesweeperBoard::minesAroundField(int col, int row) {

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

int MinesweeperBoard::countMinesOnBoard() {
    int minesOnBoard=0;

    for (int iCol = 0; iCol <= getHeight()-1; ++iCol) {
        for (int jRow = 0; jRow <= getWidth()-1; ++jRow) {
            if (boardVector[iCol][jRow].hasMine){
                minesOnBoard++;
            }
        }
    }


    return minesOnBoard;
}

void MinesweeperBoard::gameStateChecker() {
    if(countMinesOnBoard()==0){
        setGameState(gameState=GAMEWIN);
    }else{
        gameState=GAMECONTINUE;
    }
}

GameState MinesweeperBoard::getGameState() const {
    return gameState;
}

void MinesweeperBoard::setGameState(GameState gameState) {
    MinesweeperBoard::gameState = gameState;
}

void MinesweeperBoard::render() {
    int x=0;
    int y=0;

    loadTextures();

    sf::RenderWindow window(sf::VideoMode((getWidth() * 12)*scale, (getHeight() * 12)*scale),
                            "Minesweeper");

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

        }

        for (int i = 0; i < getWidth(); i++) {
            for (int j = 0; j < getHeight(); j++) {
                sprite.setTexture(textures[todo(i,j)]);
                sprite.setScale(scale,scale);

                sprite.setPosition(x*scale,y*scale);
                window.draw(sprite);
                y+=12;
            }
            y=0;
            x+=12;
        }
        x=0;y=0;
        window.display();
    }
}

void MinesweeperBoard::loadTextures() {

    // 0-9 - LICZBA MIN
    // 10-15 STANY POL

    // 10 - FLAGA, ALE NIEODKRYTE POLE, BEZ MINY
    // 11 - ROZBROJONA MINA
    // 12 - NIEODKRYTE POLE
    // 13 - POLE Z MINA, ALE NIEODKRYTE
    // 14 - ODKRYTE POLE
    // 15 - ODKRYTE POLE, ALE Z MINA

    for (int i = 0; i < 16; ++i) {
        std::string filename = "C:/Users/huber/CLionProjects/Minesweeper/Resources/" + std::to_string(i) + ".png";
        texture.loadFromFile(filename);
        textures.push_back(texture);
    }

}

int MinesweeperBoard::todo(int col, int row) {

    int numText=0;

        // NIE ODKRYTE, BEZ MINY, BEZ FLAGI - MOZLIWE
    if (!boardVector[col][row].isRevealed&&!boardVector[col][row].hasMine&&!boardVector[col][row].hasFlag){
        numText=12;
    }
    // NIE ODKRYTE, BEZ MINY, FLAGA - MOZLIWE
    else if (!boardVector[col][row].isRevealed&&!boardVector[col][row].hasMine&&boardVector[col][row].hasFlag){
        numText=10;
    }
    // NIE ODKRYTE, MINA, BEZ FLAGI - MOZLIWE
    else if (!boardVector[col][row].isRevealed&&boardVector[col][row].hasMine&&!boardVector[col][row].hasFlag){
        numText=13;
    }
    // NIE ODKRYTE, MINA, FLAGA - MOZLIWE
    else if (!boardVector[col][row].isRevealed&&boardVector[col][row].hasMine&&boardVector[col][row].hasFlag){
        numText=11;
    }

    // ODKRYTE, BEZ MINY, BEZ FLAGI - MOZLIWE
    else if (boardVector[col][row].isRevealed&&!boardVector[col][row].hasMine&&!boardVector[col][row].hasFlag){
        numText=14;
    }
    // ODKRYTE, BEZ MINY, FLAGA - NIE MOZLIWE
    else if (boardVector[col][row].isRevealed&&!boardVector[col][row].hasMine&&boardVector[col][row].hasFlag){
        numText=15;
    }
    // ODKRYTE, MINA, BEZ FLAGI - MOZLIWE
    else if (boardVector[col][row].isRevealed&&boardVector[col][row].hasMine&&!boardVector[col][row].hasFlag){
        numText=15;
    }
    // ODKRYTE, MINA, FLAGA - NIE MOZLIWE
    else if (boardVector[col][row].isRevealed&&boardVector[col][row].hasMine&&boardVector[col][row].hasFlag){
        numText=16;
    }else
    {
        numText=16;
    }

    return numText;
}






