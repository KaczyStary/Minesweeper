#include "GameRender.h"

GameRender::GameRender(GamePanel& gamePanel)
    : gamePanel(gamePanel)
{

}

void GameRender::MenuRender(sf::RenderWindow& window) {
    window.clear(sf::Color::Black);


}

void GameRender::InGameRender(sf::RenderWindow& window) {
    int x=0;
    int y=0;



    for (int i = 0; i < gamePanel.getWidth(); i++) {
        for (int j = 0; j < gamePanel.getHeight(); j++) {
            sprite.setTexture(textures[MinesweeperBoard.todo(i,j)]);
            sprite.setScale(gamePanel.getScale(),gamePanel.getScale());

            sprite.setPosition(x*gamePanel.getScale(),2*48+y*gamePanel.getScale());
            window.draw(sprite);
            y+=12;
        }
        y=0;
        x+=12;
    }
}

void GameRender::PostGameRender(sf::RenderWindow& window) {

}

void GameRender::loadTextures() {

    // 0-9 - LICZBA MIN
    // 10-15 STANY POL

    // 10 - FLAGA, ALE NIEODKRYTE POLE, BEZ MINY
    // 11 - ROZBROJONA MINA
    // 12 - NIEODKRYTE POLE
    // 13 - POLE Z MINA, ALE NIEODKRYTE
    // 14 - ODKRYTE POLE
    // 15 - ODKRYTE POLE, ALE Z MINA

    for (int i = 0; i < 16; ++i) {
        std::string filename = "C:/Users/huber/CLionProjects/Minesweeper/Resources/" + std::to_string(i) + ".png";
        texture.loadFromFile(filename);
        textures.push_back(texture);
    }

}

