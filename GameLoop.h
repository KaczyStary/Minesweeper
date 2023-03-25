#ifndef MINESWEEPER_GAMELOOP_H
#define MINESWEEPER_GAMELOOP_H

#include "GamePanel.h"
#include "GameRender.h"


class GameLoop {
private:


public:
    GamePanel& gamePanel;
    GameRender& gameRender;

    explicit GameLoop(GamePanel& gamePanel, GameRender& gameRender);

    void GameMenuLoop(sf::RenderWindow &window);

};


#endif
