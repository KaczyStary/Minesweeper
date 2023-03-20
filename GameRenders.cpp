#include "GameRenders.h"
#include "GamePanel.h"
#include "MinesweeperBoard.h"

void GameRenders::postGameLossRender(sf::RenderWindow& window) {

}

void GameRenders::menuRender(sf::RenderWindow& window) {

}

void GameRenders::gameRender(sf::RenderWindow& window) {
    int x=0;
    int y=0;

    for (int i = 0; i < gamePanel.getWidth(); i++) {
        for (int j = 0; j < gamePanel.getHeight(); j++) {
            sprite.setTexture(textures[todo(i,j)]);
            sprite.setScale(gamePanel.getScale(),gamePanel.getScale());

            sprite.setPosition(x*gamePanel.getScale(),2*gamePanel.tileSize+y*gamePanel.getScale());
            window.draw(sprite);
            y+=12;
        }
        y=0;
        x+=12;
    }


    counter_01.setScale(gamePanel.getScale(), gamePanel.getScale());
    counter_01.setTexture(textures[countMinesOnBoard()/10]);
    counter_01.setPosition(gamePanel.getScale()*gamePanel.getWidth()*5,0);
    window.draw(counter_01);

    counter_02.setScale(gamePanel.getScale(), gamePanel.getScale());
    counter_02.setTexture(textures[countMinesOnBoard()%10]);
    counter_02.setPosition(gamePanel.getScale()*gamePanel.getWidth()*6,0);
    window.draw(counter_02);


    window.display();
}

void GameRenders::postGameWinRender(sf::RenderWindow& window) {

}
