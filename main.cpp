#include "MinesweeperBoard.h"
#include "GamePanel.h"

int main() {

//    GamePanel gamePanel;

    GamePanel gamePanel;
    gamePanel.setter();

    std::cout<<gamePanel.getHeight()<<std::endl;
    std::cout<<gamePanel.getHeight()<<std::endl;

    MinesweeperBoard minesweeperBoard(gamePanel);

    return 0;
}
