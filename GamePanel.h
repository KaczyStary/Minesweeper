#ifndef MINESWEEPER_GAMEPANEL_H
#define MINESWEEPER_GAMEPANEL_H

#include <SFML/Graphics.hpp>

#include <vector>
#include <ctime>
#include <iostream>
#include <cstdlib>

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

class GamePanel {
private:

    // ZMIENNE //

    int width;
    int height;
    int scale=4;
public:
    int tileSize=scale*12;
private:

    // TYPY WYLICZENIOWE //

    GameMode gameMode;
    GameState gameState;

public:

    void setter();


    int getWidth() const;

    void setWidth(int width);

    int getHeight() const;

    void setHeight(int height);

    int getScale() const;

    GameMode getGameMode() const;

    void setGameMode(GameMode gameMode);

    GameState getGameState() const;

    void setGameState(GameState gameState);

};


#endif