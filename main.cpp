#include "MinesweeperBoard.h"
#include "GamePanel.h"
#include "GameRender.h"

int main() {
    GamePanel gamePanel(11,16,4,HARD);
    GameRender gameRender(gamePanel);
    sf::RenderWindow window(sf::VideoMode(800, 600), "Okno SFML");

    MinesweeperBoard minesweeperBoard(gamePanel, gameRender);

    minesweeperBoard.run2(window);


    // MinesweeperBoard minesweeperBoard(gamePanel,gameRender);
    //minesweeperBoard.run2(window);


    return 0;
}
