#include "MinesweeperBoard.h"
#include "GamePanel.h"

int main() {


    GamePanel gamePanel;
    gamePanel.setter();

    MinesweeperBoard minesweeperBoard(gamePanel);

    return 0;
}
