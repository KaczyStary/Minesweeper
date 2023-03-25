#include "MinesweeperBoard.h"
#include "GamePanel.h"

MinesweeperBoard::MinesweeperBoard(GamePanel& gamePanel, GameRender& gameRender)
        : gamePanel(gamePanel), gameRender(gameRender)
{
    gameRender.loadTextures();
    generateBoard();
    setMines();
    debugDisplay();

}

void MinesweeperBoard::run2(sf::RenderWindow &window) {

    while (window.isOpen()){

        while (window.pollEvent(gameRender.event)){

            if(gameRender.event.type==sf::Event::Closed) {
                window.close();
            }

        }

        gameRender.MenuRender(window);
        window.display();
    }
}

//void MinesweeperBoard::run() {
//
//    bool leftClick= false;
//    bool rightClick=false;
//
//    int move=0;
//    int tempMove=0;
//
//
//
//        if (gamePanel.getGameState()==GAMESTART){
//
//            if (event.type==sf::Event::MouseButtonPressed){
//
//                if (event.mouseButton.button==sf::Mouse::Left) {
//                    revealField(mousePos.x / 48, (mousePos.y - 2 * 48) / 48);
//                    move++;
//                }else if(event.mouseButton.button == sf::Mouse::Right){
//                    toggleFlag(mousePos.x/48, (mousePos.y-2*48)/48);
//                    move++;
//                }
//            }
//
//            // RUCH
//            if (move>tempMove){
//                render(window);
//                tempMove=move;
//                gamePanel.setGameState(GAMECONTINUE);
//                setMines();
//            }
//
//        }
//
//        if (gamePanel.getGameState()==GAMECONTINUE){
//
//            if (event.type==sf::Event::MouseButtonPressed) {
//
//                if (event.mouseButton.button == sf::Mouse::Left) {
//                    leftClick=true;
//                }else if(event.mouseButton.button == sf::Mouse::Right){
//                    rightClick= true;
//                }
//            }
//            if (event.type==sf::Event::MouseButtonReleased){
//                if (event.mouseButton.button == sf::Mouse::Left) {
//                    if (leftClick){
//                        revealField(mousePos.x / 48, (mousePos.y - 2 * 48) / 48);
//                        move++;
//                        leftClick= false;
//                    }
//                }else if(event.mouseButton.button == sf::Mouse::Right){
//                    if (rightClick){
//                        toggleFlag(mousePos.x/48, (mousePos.y-2*48)/48);
//                        move++;
//                        rightClick=false;
//                    }
//                }
//            }
//
//            // RUCH
//            if (move>tempMove){
//                render(window);
//                tempMove=move;
//                std::cout<<countMinesOnBoard()<<std::endl;
//            }
//        }
//    }
//
//}

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

    srand(time(NULL));

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

void MinesweeperBoard::revealField(int width, int height) {
    if (!boardVector[width][height].isRevealed){
        if (!boardVector[width][height].hasFlag) {
            boardVector[width][height].isRevealed = true;
            if (boardVector[width][height].hasMine){
                gamePanel.setGameState(GAMELOST);
            }
        }
    }
}

void MinesweeperBoard::toggleFlag(int a, int b) {
    if (!boardVector[a][b].isRevealed){
        if (!boardVector[a][b].hasFlag) {
            boardVector[a][b].hasFlag = true;
        }else if(boardVector[a][b].hasFlag){
            boardVector[a][b].hasFlag = false;
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

//void MinesweeperBoard::render(sf::RenderWindow& window) {

//
//
//    counter_01.setScale(gamePanel.getScale(), gamePanel.getScale());
//    counter_01.setTexture(textures[countMinesOnBoard()/10]);
//    counter_01.setPosition(gamePanel.getScale()*gamePanel.getWidth()*5,0);
//    window.draw(counter_01);
//
//    counter_02.setScale(gamePanel.getScale(), gamePanel.getScale());
//    counter_02.setTexture(textures[countMinesOnBoard()%10]);
//    counter_02.setPosition(gamePanel.getScale()*gamePanel.getWidth()*6,0);
//    window.draw(counter_02);
//
//
//    window.display();
//}

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











