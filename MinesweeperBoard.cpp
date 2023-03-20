#include "MinesweeperBoard.h"
#include "GamePanel.h"
#include "GameRenders.h"

MinesweeperBoard::MinesweeperBoard(GamePanel gamePanel) {
    this->gamePanel=gamePanel;
    loadTextures();
    gameStart();

}

void MinesweeperBoard::run() {
    int move=0;
    int tempMove=0;

    sf::RenderWindow window(sf::VideoMode(gamePanel.getWidth()*gamePanel.tileSize,gamePanel.getHeight()*gamePanel.tileSize+2*gamePanel.tileSize),"Minesweeper");

    render(window);

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        if (gamePanel.getGameState()==GAMESTART){

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)&&mousePos.y>2*gamePanel.tileSize){

                if (!boardVector[mousePos.x/gamePanel.tileSize][(mousePos.y-2*gamePanel.tileSize)/gamePanel.tileSize].isRevealed) {
                    revealField(mousePos.x / gamePanel.tileSize,
                                (mousePos.y - 2 * gamePanel.tileSize) / gamePanel.tileSize);
                    move++;
                }

            }else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)){

                std::cout<<"x: "<<mousePos.x/gamePanel.tileSize<<std::endl;
                std::cout<<"y: "<<(mousePos.y-2*gamePanel.tileSize)/gamePanel.tileSize<<std::endl;


                if (!boardVector[mousePos.x/gamePanel.tileSize][(mousePos.y-2*gamePanel.tileSize)/gamePanel.tileSize].hasFlag) {
                    toggleFlag(mousePos.x / gamePanel.tileSize,
                               (mousePos.y - 2 * gamePanel.tileSize) / gamePanel.tileSize);
                    move++;

                } else if (boardVector[mousePos.x/gamePanel.tileSize][(mousePos.y-2*gamePanel.tileSize)/gamePanel.tileSize].hasFlag){
                    unToggleFlag(mousePos.x / gamePanel.tileSize,
                               (mousePos.y - 2 * gamePanel.tileSize) / gamePanel.tileSize);
                    move++;
                }

            }

            // RUCH
            if (move>tempMove){
                render(window);
                tempMove=move;
                gamePanel.setGameState(GAMECONTINUE);
                setMines();
            }

        }

        if (gamePanel.getGameState()==GAMECONTINUE){

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)&&mousePos.y>2*gamePanel.tileSize){

                if (!boardVector[mousePos.x/gamePanel.tileSize][(mousePos.y-2*gamePanel.tileSize)/gamePanel.tileSize].isRevealed) {
                    revealField(mousePos.x / gamePanel.tileSize,
                                (mousePos.y - 2 * gamePanel.tileSize) / gamePanel.tileSize);
                    move++;
                }

            }else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                std::cout<<"x: "<<mousePos.x/gamePanel.tileSize<<std::endl;
                std::cout<<"y: "<<(mousePos.y-2*gamePanel.tileSize)/gamePanel.tileSize<<std::endl;

                if (!boardVector[mousePos.x / gamePanel.tileSize][(mousePos.y - 2 * gamePanel.tileSize) /
                                                                  gamePanel.tileSize].hasFlag) {
                    toggleFlag(mousePos.x / gamePanel.tileSize,
                               (mousePos.y - 2 * gamePanel.tileSize) / gamePanel.tileSize);
                    move++;

                } else if (boardVector[mousePos.x / gamePanel.tileSize][(mousePos.y - 2 * gamePanel.tileSize) /
                                                                         gamePanel.tileSize].hasFlag) {
                    unToggleFlag(mousePos.x / gamePanel.tileSize,
                                 (mousePos.y - 2 * gamePanel.tileSize) / gamePanel.tileSize);
                    move++;
                }
            }

            // RUCH
            if (move>tempMove){
                render(window);
                tempMove=move;
            }

            if (countMinesOnBoard()==0){
                gamePanel.setGameState(GAMEWIN);
                break;
            }
        }
    }
}

void MinesweeperBoard::gameStart() {
    gamePanel.setGameState(GAMESTART);

    generateBoard();
    run();
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

void MinesweeperBoard::generateBoard() {

    for (int i = 0; i < gamePanel.getHeight(); i++) {
        std::vector<Field> row;
        for (int j = 0; j < gamePanel.getWidth(); j++) {
            Field field(false, false, false);
            row.push_back(field);
        }
        boardVector.push_back(row);
    }
}

void MinesweeperBoard::setMines() {

    int numberOfMines=0;

    srand(time(nullptr));

    int minRandomHeightWidth=0;
    int maxRandomWidth=gamePanel.getWidth();
    int maxRandomHeigh=gamePanel.getHeight();

    //10% OF BOARD FILLED WITH MINES
    if (gamePanel.getGameMode()==EASY){
        numberOfMines=gamePanel.getHeight()*gamePanel.getWidth()*0.10;

        while (numberOfMines>0){

            int randomHeight=rand() % (maxRandomHeigh - minRandomHeightWidth) + minRandomHeightWidth;
            int randomWidth=rand() % (maxRandomWidth - minRandomHeightWidth) + minRandomHeightWidth;

            if (!boardVector[randomHeight][randomWidth].hasMine&&!boardVector[randomHeight][randomWidth].isRevealed) {
                boardVector[randomHeight][randomWidth].hasMine = true;
                numberOfMines--;
            }
        }
    }

    //20% OF BOARD FILLED WITH MINES
    else if (gamePanel.getGameMode()==NORMAL){
        numberOfMines=gamePanel.getHeight()*gamePanel.getWidth()*0.2;

        while (numberOfMines>0){

            int randomHeight=rand() % (maxRandomHeigh - minRandomHeightWidth) + minRandomHeightWidth;
            int randomWidth=rand() % (maxRandomWidth - minRandomHeightWidth) + minRandomHeightWidth;

            if (!boardVector[randomHeight][randomWidth].hasMine&&!boardVector[randomHeight][randomWidth].isRevealed) {
                boardVector[randomHeight][randomWidth].hasMine = true;
                numberOfMines--;
            }
        }
    }

    //30% OF BOARD FILLED WITH MINES
    else if (gamePanel.getGameMode()==HARD){
        numberOfMines=gamePanel.getHeight()*gamePanel.getWidth()*0.3;

        while (numberOfMines>0){

            int randomHeight=rand() % (maxRandomHeigh - minRandomHeightWidth) + minRandomHeightWidth;
            int randomWidth=rand() % (maxRandomWidth - minRandomHeightWidth) + minRandomHeightWidth;

            if (!boardVector[randomHeight][randomWidth].hasMine&&!boardVector[randomHeight][randomWidth].isRevealed) {
                boardVector[randomHeight][randomWidth].hasMine = true;
                numberOfMines--;
            }
        }
    }

    else if(gamePanel.getGameMode()==DEV){

        for (int i = 0; i < gamePanel.getHeight()-1; ++i) {
            for (int j = 0; j <gamePanel.getWidth()-1 ; ++j) {
                if (i==j){
                    boardVector[i][j].hasMine=true;
                }
            }
        }

    }
}


void MinesweeperBoard::revealField(int col, int row) {
    if (!boardVector[col][row].isRevealed){
        if (!boardVector[col][row].hasFlag) {
            boardVector[col][row].isRevealed = true;
            if (boardVector[col][row].hasMine){
                gamePanel.setGameState(GAMELOST);
            }
        }
    }
}

void MinesweeperBoard::toggleFlag(int col, int row) {
    if (!boardVector[col][row].isRevealed){

        if (!boardVector[col][row].hasFlag) {
            boardVector[col][row].hasFlag = true;
        }
    }
}

void MinesweeperBoard::unToggleFlag(int col, int row) {
    if (!boardVector[col][row].isRevealed){

        if (boardVector[col][row].hasFlag) {
            boardVector[col][row].hasFlag = false;
        }
    }
}

int MinesweeperBoard::minesAroundField(int col, int row) {

    int minesAroundField = 0;

                //UPPER LIMIT
    if (col==0&&row!=0&&row!=(gamePanel.getWidth()-1)) {
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
    }else if (col==gamePanel.getHeight()-1&&row!=0&&row!=(gamePanel.getWidth()-1)) {
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
    }else if (row==0&&col!=0&&col!=gamePanel.getHeight()-1) {
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
    }else if (row==gamePanel.getWidth()-1&&col!=0&&col!=gamePanel.getHeight()-1) {
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
    }else if (col==0&&row==gamePanel.getWidth()-1) {
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
    }else if (col==gamePanel.getHeight()-1&&row==gamePanel.getWidth()-1) {
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
    }else if (col==gamePanel.getHeight()-1&&row==0) {
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

    for (int iCol = 0; iCol <= gamePanel.getHeight()-1; ++iCol) {
        for (int jRow = 0; jRow <= gamePanel.getWidth()-1; ++jRow) {
            if (boardVector[iCol][jRow].hasMine){
                minesOnBoard++;
            }
        }
    }

    for (int iCol = 0; iCol <= gamePanel.getHeight()-1; ++iCol) {
        for (int jRow = 0; jRow <= gamePanel.getWidth()-1; ++jRow) {
            if (boardVector[iCol][jRow].hasMine&&boardVector[iCol][jRow].hasFlag){
                minesOnBoard--;
            }
        }
    }

    return minesOnBoard;
}

void MinesweeperBoard::render(sf::RenderWindow& window) {

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
        numText=minesAroundField(col,row);
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

void MinesweeperBoard::update() {

}






