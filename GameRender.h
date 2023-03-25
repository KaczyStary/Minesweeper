#ifndef MINESWEEPER_GAMERENDER_H
#define MINESWEEPER_GAMERENDER_H
#include "GamePanel.h"
#include <SFML/Graphics.hpp>
#include "MinesweeperBoard.h"

#include <vector>
#include <ctime>
#include <iostream>
#include <cstdlib>

class GameRender {

private:

    sf::Texture texture;
    std::vector<sf::Texture> textures;
    GamePanel gamePanel;
    sf::Sprite sprite, counter_01, counter_02;

public:

    sf::Event event{};

    explicit GameRender(GamePanel& gamePanel);
    void InGameRender(sf::RenderWindow& window);
    void MenuRender(sf::RenderWindow& window);
    void PostGameRender(sf::RenderWindow& window);

    void loadTextures();

};


#endif
