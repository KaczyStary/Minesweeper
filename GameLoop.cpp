#include "GameLoop.h"

GameLoop::GameLoop(GamePanel &gamePanel, GameRender &gameRender)
        :gamePanel(gamePanel), gameRender(gameRender)
{

}

void GameLoop::GameMenuLoop(sf::RenderWindow &window) {

//    if (gameRender.event.type == sf::Event::MouseButtonPressed) {
//        if (gameRender.event.mouseButton.button == sf::Mouse::Left) {
//            gamePanel.setLeftClick(true);
//        } else if (gameRender.event.mouseButton.button == sf::Mouse::Right) {
//            gamePanel.setRightClick(true);
//        }
//    }
//
//    if (gameRender.event.type == sf::Event::MouseButtonReleased) {
//        if (gameRender.event.mouseButton.button == sf::Mouse::Left) {
//            if (gamePanel.isLeftClick()) {
//                if (mousePos.x>gamePanel.getWidth()*48/2&&mousePos.x<(gamePanel.getWidth()*48/2)+21*gamePanel.getScale()*2){
//                    if (mousePos.y>gamePanel.getHeight()*48/2-48&&mousePos.y<gamePanel.getHeight()*48/2-48+7*gamePanel.getScale()*2){
//                        gamePanel.setGameState(GAMESTART);
//                    }
//                }
//                gamePanel.setLeftClick(false);
//            }
//        } else if (gameRender.event.mouseButton.button == sf::Mouse::Right) {
//            if (gamePanel.isRightClick()) {
//                gamePanel.setRightClick(false);
//            }
//        }
//    }
}
