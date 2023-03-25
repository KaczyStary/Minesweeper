#include "MinesweeperBoard.h"
#include "GamePanel.h"

MinesweeperBoard::MinesweeperBoard(GamePanel& gamePanel, GameRender& gameRender, GameLoop& gameLoop)
        : gamePanel(gamePanel), gameRender(gameRender), gameLoop(gameLoop)
{
    gameRender.loadTextures();
    startNewGame();


}

void MinesweeperBoard::startNewGame() {
    generateBoard();

    gamePanel.setGameState(GAMEMENU);

}

void MinesweeperBoard::run(sf::RenderWindow &window) {

    int move=0;
    int reveal=0;

    int tempMove=0;

    while (window.isOpen()){

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        while (window.pollEvent(gameRender.event)){
            if(gameRender.event.type==sf::Event::Closed) {
                window.close();
            }
        }

        if (gamePanel.getGameState()==GAMEMENU){
            if (gameRender.event.type == sf::Event::MouseButtonPressed) {
                if (gameRender.event.mouseButton.button == sf::Mouse::Left) {
                    gamePanel.setLeftClick(true);
                } else if (gameRender.event.mouseButton.button == sf::Mouse::Right) {
                    gamePanel.setRightClick(true);
                }
            }

            if (gameRender.event.type == sf::Event::MouseButtonReleased) {
                if (gameRender.event.mouseButton.button == sf::Mouse::Left) {
                    if (gamePanel.isLeftClick()) {
                        if (mousePos.x>gamePanel.getWidth()*48/2&&mousePos.x<(gamePanel.getWidth()*48/2)+21*gamePanel.getScale()*2){
                            if (mousePos.y>gamePanel.getHeight()*48/2-48&&mousePos.y<gamePanel.getHeight()*48/2-48+7*gamePanel.getScale()*2){
                                gamePanel.setGameState(GAMESTART);
                            }
                        }
                        gamePanel.setLeftClick(false);
                    }
                } else if (gameRender.event.mouseButton.button == sf::Mouse::Right) {
                    if (gamePanel.isRightClick()) {
                        gamePanel.setRightClick(false);
                    }
                }
            }
        }

        if (gamePanel.getGameState()==GAMESTART||gamePanel.getGameState()==GAMECONTINUE) {
            if (gameRender.event.type == sf::Event::MouseButtonPressed) {
                if (gameRender.event.mouseButton.button == sf::Mouse::Left) {
                    gamePanel.setLeftClick(true);

                } else if (gameRender.event.mouseButton.button == sf::Mouse::Right) {
                    gamePanel.setRightClick(true);
                }
            }

            if (gameRender.event.type == sf::Event::MouseButtonReleased) {
                if (gameRender.event.mouseButton.button == sf::Mouse::Left) {
                    if (gamePanel.isLeftClick()) {
                        revealField(mousePos.x / 48, (mousePos.y) / 48);
                        move++;
                        reveal++;
                        gamePanel.setLeftClick(false);

                        if (reveal == 1) {
                            setMines();
                        }
                    }
                } else if (gameRender.event.mouseButton.button == sf::Mouse::Right) {
                    if (gamePanel.isRightClick()) {
                        toggleFlag(mousePos.x / 48, (mousePos.y) / 48);
                        move++;
                        gamePanel.setRightClick(false);
                    }
                }
            }
        }

        if (gamePanel.getGameState()==GAMEWIN||gamePanel.getGameState()==GAMELOST){
            if (gameRender.event.type == sf::Event::MouseButtonPressed) {
                if (gameRender.event.mouseButton.button == sf::Mouse::Left) {
                    gamePanel.setLeftClick(true);
                } else if (gameRender.event.mouseButton.button == sf::Mouse::Right) {
                    gamePanel.setRightClick(true);
                }
            }

            if (gameRender.event.type == sf::Event::MouseButtonReleased) {
                if (gameRender.event.mouseButton.button == sf::Mouse::Left) {
                    if (gamePanel.isLeftClick()) {
                        gamePanel.setLeftClick(false);
                    }
                } else if (gameRender.event.mouseButton.button == sf::Mouse::Right) {
                    if (gamePanel.isRightClick()) {
                        gamePanel.setGameState(GAMEMENU);
                        gamePanel.setRightClick(false);
                    }
                }
            }
        }

        if(countMinesOnBoard()==0&&reveal>0){
            gamePanel.setGameState(GAMEWIN);
        }

        gameRender.Render(window);

    }
}

void MinesweeperBoard::debugDisplay() const {

    for (int i = 0; i < gamePanel.boardVector.size(); i++) {
        for (int j = 0; j <gamePanel.boardVector[i].size() ; j++) {

                std::cout << "[";
                std::cout <<gamePanel.boardVector[i][j].hasMine;
                if (gamePanel.boardVector[i][j].hasFlag){
                    std::cout <<"F";
                } else{
                    std::cout <<gamePanel.boardVector[i][j].hasFlag;
                }
                if (gamePanel.boardVector[i][j].isRevealed){
                    std::cout<<"R";
                }else {
                    std::cout << gamePanel.boardVector[i][j].isRevealed;
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
        gamePanel.boardVector.push_back(row);
    }
}

void MinesweeperBoard::setMines() {

    int numberOfMines;

    srand(time(nullptr));

    int minRandomHeightWidth=0;
    int maxRandomWidth=gamePanel.getWidth();
    int maxRandomHeight=gamePanel.getHeight();

    //10% OF BOARD FILLED WITH MINES
    if (gamePanel.getGameMode()==EASY){
        numberOfMines=gamePanel.getHeight()*gamePanel.getWidth()*0.10;

        while (numberOfMines>0){

            int randomHeight=rand() % (maxRandomHeight - minRandomHeightWidth) + minRandomHeightWidth;
            int randomWidth=rand() % (maxRandomWidth - minRandomHeightWidth) + minRandomHeightWidth;

            if (!gamePanel.boardVector[randomHeight][randomWidth].hasMine&&!gamePanel.boardVector[randomHeight][randomWidth].isRevealed) {
                gamePanel.boardVector[randomHeight][randomWidth].hasMine = true;
                numberOfMines--;
            }
        }
    }

    //20% OF BOARD FILLED WITH MINES
    else if (gamePanel.getGameMode()==NORMAL){
        numberOfMines=gamePanel.getHeight()*gamePanel.getWidth()*0.2;

        while (numberOfMines>0){

            int randomHeight=rand() % (maxRandomHeight - minRandomHeightWidth) + minRandomHeightWidth;
            int randomWidth=rand() % (maxRandomWidth - minRandomHeightWidth) + minRandomHeightWidth;

            if (!gamePanel.boardVector[randomHeight][randomWidth].hasMine&&!gamePanel.boardVector[randomHeight][randomWidth].isRevealed) {
                gamePanel.boardVector[randomHeight][randomWidth].hasMine = true;
                numberOfMines--;
            }
        }
    }

    //30% OF BOARD FILLED WITH MINES
    else if (gamePanel.getGameMode()==HARD){
        numberOfMines=gamePanel.getHeight()*gamePanel.getWidth()*0.3;

        while (numberOfMines>0){

            int randomHeight=rand() % (maxRandomHeight - minRandomHeightWidth) + minRandomHeightWidth;
            int randomWidth=rand() % (maxRandomWidth - minRandomHeightWidth) + minRandomHeightWidth;

            if (!gamePanel.boardVector[randomHeight][randomWidth].hasMine&&!gamePanel.boardVector[randomHeight][randomWidth].isRevealed) {
                gamePanel.boardVector[randomHeight][randomWidth].hasMine = true;
                numberOfMines--;
            }
        }
    }

    else if(gamePanel.getGameMode()==DEV){

        for (int i = 0; i < gamePanel.getHeight()-1; ++i) {
            for (int j = 0; j <gamePanel.getWidth()-1 ; ++j) {
                if (i==j){
                    gamePanel.boardVector[i][j].hasMine=true;
                }
            }
        }

    }
}

void MinesweeperBoard::revealField(int width, int height) {
    if (!gamePanel.boardVector[width][height].isRevealed){
        if (!gamePanel.boardVector[width][height].hasFlag) {
            gamePanel.boardVector[width][height].isRevealed = true;
            if (gamePanel.boardVector[width][height].hasMine){
                gamePanel.setGameState(GAMELOST);
            }
        }
    }
}

void MinesweeperBoard::toggleFlag(int a, int b) {
    if (!gamePanel.boardVector[a][b].isRevealed){
        if (!gamePanel.boardVector[a][b].hasFlag) {
            gamePanel.boardVector[a][b].hasFlag = true;
        }else if(gamePanel.boardVector[a][b].hasFlag){
            gamePanel.boardVector[a][b].hasFlag = false;
        }
    }
}

int MinesweeperBoard::countMinesOnBoard() {
    int minesOnBoard=0;

    for (int iCol = 0; iCol <= gamePanel.getHeight()-1; ++iCol) {
        for (int jRow = 0; jRow <= gamePanel.getWidth()-1; ++jRow) {
            if (gamePanel.boardVector[iCol][jRow].hasMine){
                minesOnBoard++;
            }
        }
    }

    for (int iCol = 0; iCol <= gamePanel.getHeight()-1; ++iCol) {
        for (int jRow = 0; jRow <= gamePanel.getWidth()-1; ++jRow) {
            if (gamePanel.boardVector[iCol][jRow].hasMine&&gamePanel.boardVector[iCol][jRow].hasFlag){
                minesOnBoard--;
            }
        }
    }

    return minesOnBoard;
}


