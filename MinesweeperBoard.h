#ifndef MINESWEEPER_MINESWEEPERBOARD_H
#define MINESWEEPER_MINESWEEPERBOARD_H

#include "GamePanel.h"


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

    GamePanel gamePanel;

    // BIBLIOTEKA SFML //
    sf::Event event{};
    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite, counter_01, counter_02;

    // WEKTORY/TABLICE //

    std::vector<std::vector<Field>> boardVector;
    std::vector<sf::Texture> textures;

public:

    // GENERIC
    explicit MinesweeperBoard(GamePanel gamePanel);
    void gameStart();
    void render(sf::RenderWindow& window);
    void debugDisplay() const;
    void run();

    // FUNKCJE "GENERUJACE"

    void generateBoard();
    void loadTextures();
    void setMines();

    // FUNKCJE OPERACJI

    void toggleFlag(int width, int height);
    void revealField(int width, int height);

    // ZWRACAJACE

    int todo(int col, int row);
    int countMinesOnBoard();
    int minesAroundField(int height, int width);

    void update();
};


#endif
