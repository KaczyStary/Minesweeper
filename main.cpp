#include "MinesweeperBoard.h"
#include "GamePanel.h"
#include "GameRender.h"

int main() {


    GamePanel gamePanel(6,5,4,EASY);



    MinesweeperBoard minesweeperBoard(gamePanel);

    return 0;
}
