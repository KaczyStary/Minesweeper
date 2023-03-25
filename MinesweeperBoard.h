#ifndef MINESWEEPER_MINESWEEPERBOARD_H
#define MINESWEEPER_MINESWEEPERBOARD_H

#include "GamePanel.h"
#include "GameRender.h"
#include "GameLoop.h"

class MinesweeperBoard{

private:

public:
    GamePanel& gamePanel;
    GameRender& gameRender;
    GameLoop& gameLoop;

    // GENERIC
    explicit MinesweeperBoard(GamePanel& gamePanel, GameRender& gameRender, GameLoop& gameLoop);
    void debugDisplay() const;
    void run(sf::RenderWindow& window);
    void startNewGame();

    // FUNKCJE "GENERUJACE"

    void generateBoard();
    void setMines();

    // FUNKCJE OPERACJI

    void toggleFlag(int width, int height);
    void revealField(int width, int height);

    // ZWRACAJACE

    int countMinesOnBoard();
};

#endif