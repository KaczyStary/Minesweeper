#ifndef MINESWEEPER_GAMERENDER_H
#define MINESWEEPER_GAMERENDER_H

#include "GamePanel.h"

class GameRender {

private:
    GamePanel& gamePanel;

    sf::Texture texture;
    std::vector<sf::Texture> textures;
    sf::Sprite sprite, menuGame, postGame;

public:

    sf::Event event{};

    explicit GameRender(GamePanel& gamePanel);


    void InGameRender(sf::RenderWindow& window);
    void MenuRender(sf::RenderWindow& window);
    void PostGameRender(sf::RenderWindow& window);
    void Render(sf::RenderWindow& window);


    void loadTextures();
    int setTextures(int col, int row);

};

#endif