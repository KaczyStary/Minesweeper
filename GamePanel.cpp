#include "GamePanel.h"

int GamePanel::getWidth() const {
    return width;
}

void GamePanel::setWidth(int width) {
    GamePanel::width = width;
}

int GamePanel::getHeight() const {
    return height;
}

void GamePanel::setHeight(int height) {
    GamePanel::height = height;
}

GameMode GamePanel::getGameMode() const {
    return gameMode;
}

void GamePanel::setGameMode(GameMode gameMode) {
    GamePanel::gameMode = gameMode;
}

GameState GamePanel::getGameState() const {
    return gameState;
}

void GamePanel::setGameState(GameState gameState) {
    GamePanel::gameState = gameState;
}

int GamePanel::getScale() const {
    return scale;
}

void GamePanel::setter() {

    setHeight(10);
    setWidth(10);
    setGameMode(EASY);

}
