#include "MinesweeperBoard.h"
#include "GamePanel.h"

int main() {


    GamePanel gamePanel(10,10,4,EASY);

    MinesweeperBoard minesweeperBoard(gamePanel);

    return 0;
}
