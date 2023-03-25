#ifndef MINESWEEPER_GAMEPANEL_H
#define MINESWEEPER_GAMEPANEL_H

#include "GamePanel.h"

#include <SFML/Graphics.hpp>

#include <vector>
#include <ctime>
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
    GAMEMENU,
    GAMESTART,
    GAMECONTINUE,
    GAMEWIN,
    GAMELOST
};

class GamePanel {

private:

    // ZMIENNE //

    int width;
    int height;
    int scale;

    bool rightClick=false;
    bool leftClick=false;
public:
    bool isRightClick() const;

    void setRightClick(bool rightClick);

    bool isLeftClick() const;

    void setLeftClick(bool leftClick);

private:

    // TYPY WYLICZENIOWE //

    GameMode gameMode;
    GameState gameState;



public:

    std::vector<std::vector<Field>> boardVector;

    GamePanel(int width, int height,int scale, GameMode gameMode);

    int tileSize=scale*12;

    void setHeight(int height);
    void setWidth(int width);

    int getHeight() const;
    int getWidth() const;
    int getScale() const;


    void setGameMode(GameMode gameMode);
    void setGameState(GameState gameState);

    GameMode getGameMode() const;
    GameState getGameState() const;
    int minesAroundField(int height, int width);

};

#endif