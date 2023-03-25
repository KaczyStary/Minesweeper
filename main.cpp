#include "MinesweeperBoard.h"
#include "GamePanel.h"
#include "GameRender.h"

int main() {
    GamePanel gamePanel(10,10,4,EASY);
    GameRender gameRender(gamePanel);
    GameLoop gameLoop(gamePanel,gameRender);
    sf::RenderWindow window(sf::VideoMode(gamePanel.getWidth()*48, gamePanel.getHeight()*48), "Okno SFML");

    MinesweeperBoard minesweeperBoard(gamePanel,gameRender,gameLoop);
    minesweeperBoard.run(window);

    return 0;
}
