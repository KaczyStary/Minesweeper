//
// Created by huber on 08.03.2023.
//
#include <vector>
#ifndef MINESWEEPER_MINESWEEPERBOARD_H
#define MINESWEEPER_MINESWEEPERBOARD_H

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

class MinesweeperBoard
{
private:
    int width;
    int height;
    GameMode gameMode;

    std::vector<std::vector<Field>> boardVector;


public:

    MinesweeperBoard(int width, int height, GameMode gameMode);

    void debugDisplay() const;

    void generateBoard();

    int getWidth() const;

    GameMode getGameMode() const;

    void setWidth(int width);

    int getHeight() const;

    void setHeight(int height);
    void setMines();

    void toggleFlag(int width, int height);
    void revealField(int width, int height);
    int minesAroundField(int width, int height);

};


#endif //MINESWEEPER_MINESWEEPERBOARD_H
