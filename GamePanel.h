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
    int scale;

    // TYPY WYLICZENIOWE //

    GameMode gameMode;
    GameState gameState;

public:

    explicit GamePanel();
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


};


#endif