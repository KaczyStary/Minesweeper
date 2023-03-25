#ifndef MINESWEEPER_MINESWEEPERBOARD_H
#define MINESWEEPER_MINESWEEPERBOARD_H

#include "GamePanel.h"
#include "GameRender.h"


struct Field
{
    bool hasMine;
    bool hasFlag;
    bool isRevealed;

    Field(bool mine=false, bool flag=false, bool revealed=false)
            : hasMine(mine), hasFlag(flag), isRevealed(revealed)
    {
    }

};

class MinesweeperBoard
{
private:
    GameRender gameRender;
    GamePanel gamePanel;

    // BIBLIOTEKA SFML //

//    sf::Image image;

    // WEKTORY/TABLICE //

    std::vector<std::vector<Field>> boardVector;


public:

    // GENERIC
    explicit MinesweeperBoard(GamePanel& gamePanel, GameRender& gameRender);

    void debugDisplay() const;
//    void run();
    void run2(sf::RenderWindow& window);

    // FUNKCJE "GENERUJACE"

    void generateBoard();
    void setMines();

    // FUNKCJE OPERACJI

    void toggleFlag(int width, int height);
    void revealField(int width, int height);

    // ZWRACAJACE

    int todo(int col, int row);
    int countMinesOnBoard();
    int minesAroundField(int height, int width);
};


#endif
