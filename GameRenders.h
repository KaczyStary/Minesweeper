#ifndef MINESWEEPER_GAMERENDERS_H
#define MINESWEEPER_GAMERENDERS_H

#include "GamePanel.h"
#include "MinesweeperBoard.h"

#include <SFML/Graphics.hpp>

#include <vector>
#include <ctime>
#include <iostream>
#include <cstdlib>

enum GameWindow{
    MAIN,
    GAME,
    POSTGAME
};

class GameRenders {
private:
    GameWindow gameWindow;

public:
    void menuRender(sf::RenderWindow& window);
    void gameRender(sf::RenderWindow& window);
    void postGameWinRender(sf::RenderWindow& window);
    void postGameLossRender(sf::RenderWindow& window);
};


#endif
