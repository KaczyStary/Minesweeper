#ifndef MINESWEEPER_MINESWEEPERBOARD_H
#define MINESWEEPER_MINESWEEPERBOARD_H

#include "MinesweeperBoard.h"
#include <SFML/Graphics.hpp>

#include <vector>
#include <time.h>
#include <iostream>
#include <cstdlib>

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

enum GameMode{
    EASY,
    NORMAL,
    HARD,
    DEV
};

enum GameState{
    GAMESTART,
    GAMECONTINUE,
    GAMEWIN,
    GAMELOST
};

class MinesweeperBoard
{
private:
    // ZMIENNE //

    int width;
    int height;
    int scale=4;

    // BIBLIOTEKA SFML //

    sf::Event event;
    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;

    // TYPY WYLICZENIOWE //

    GameMode gameMode;
    GameState gameState;

    // WEKTORY/TABLICE //

    std::vector<std::vector<Field>> boardVector;
    std::vector<sf::Texture> textures;

public:

    // GENERIC
    MinesweeperBoard(int height, int width, GameMode gameMode);
    void gameStart();
    void render();
    void debugDisplay() const;

    // FUNKCJE "GENERUJACE"

    void generateBoard();
    void loadTextures();
    void setMines();

    // FUNKCJE OPERACJI

    void toggleFlag(int width, int height);
    void revealField(int height, int width);
    void gameStateChecker();

    // ZWRACAJACE

    int todo(int col, int row);
    int countMinesOnBoard();
    int minesAroundField(int height, int width);

    // GETTER/SETTER
    int getHeight() const;
    int getWidth() const;

    GameState getGameState() const;
    GameMode getGameMode() const;

    void setGameState(GameState gameState);
    void setWidth(int width);
    void setHeight(int height);


};


#endif
