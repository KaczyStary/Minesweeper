#include "GamePanel.h"
#include "GameRender.h"

GameRender::GameRender(GamePanel& gamePanel)
    : gamePanel(gamePanel){

}

void GameRender::MenuRender(sf::RenderWindow& window) {
    window.clear(sf::Color::Cyan);

    menuGame.setTexture(textures[18]);
    menuGame.setScale(2*gamePanel.getScale(),2*gamePanel.getScale());
    menuGame.setPosition(gamePanel.getWidth()*48/2,gamePanel.getHeight()*48/2-48);

    window.draw(menuGame);
}

void GameRender::InGameRender(sf::RenderWindow& window) {
    int x=0;
    int y=0;

    for (int i = 0; i < gamePanel.getWidth(); i++) {
        for (int j = 0; j < gamePanel.getHeight(); j++) {
            sprite.setTexture(textures[setTextures(i,j)]);

            sprite.setScale(gamePanel.getScale(),gamePanel.getScale());

            sprite.setPosition(x*gamePanel.getScale(),y*gamePanel.getScale());
            window.draw(sprite);
            y+=12;
        }
        y=0;
        x+=12;
    }
}

void GameRender::PostGameRender(sf::RenderWindow& window) {
    window.clear(sf::Color::Black);
    if (gamePanel.getGameState()==GAMEWIN){
        postGame.setTexture(textures[16]);
        postGame.setScale(2*gamePanel.getScale(),2*gamePanel.getScale());
        postGame.setPosition(gamePanel.getWidth()*48/2-48,gamePanel.getHeight()*48/2-48);
        window.draw(postGame);


    }else if (gamePanel.getGameState()==GAMELOST){
        postGame.setTexture(textures[17]);
        postGame.setScale(2*gamePanel.getScale(),2*gamePanel.getScale());
        postGame.setPosition(gamePanel.getWidth()*48/2-48,gamePanel.getHeight()*48/2-48);
        window.draw(postGame);

    }
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
    // 16 - POSTGAME WIN
    // 17 - POSTGAME LOSS
    // 18 - MENU GAMESTART

    for (int i = 0; i < 19; ++i) {
        std::string filename = "C:/Users/huber/CLionProjects/Minesweeper/Resources/" + std::to_string(i) + ".png";
        texture.loadFromFile(filename);
        textures.push_back(texture);
    }

}

int GameRender::setTextures(int col,int row) {

    int numText=0;

    // NIE ODKRYTE, BEZ MINY, BEZ FLAGI - MOZLIWE
    if (!gamePanel.boardVector[col][row].isRevealed&&!gamePanel.boardVector[col][row].hasMine&&!gamePanel.boardVector[col][row].hasFlag){

        numText=12;
    }
        // NIE ODKRYTE, BEZ MINY, FLAGA - MOZLIWE
    else if (!gamePanel.boardVector[col][row].isRevealed&&!gamePanel.boardVector[col][row].hasMine&&gamePanel.boardVector[col][row].hasFlag){
        numText=10;
    }
        // NIE ODKRYTE, MINA, BEZ FLAGI - MOZLIWE
    else if (!gamePanel.boardVector[col][row].isRevealed&&gamePanel.boardVector[col][row].hasMine&&!gamePanel.boardVector[col][row].hasFlag){
        numText=13;
    }
        // NIE ODKRYTE, MINA, FLAGA - MOZLIWE
    else if (!gamePanel.boardVector[col][row].isRevealed&&gamePanel.boardVector[col][row].hasMine&&gamePanel.boardVector[col][row].hasFlag){
        numText=11;
    }

        // ODKRYTE, BEZ MINY, BEZ FLAGI - MOZLIWE
    else if (gamePanel.boardVector[col][row].isRevealed&&!gamePanel.boardVector[col][row].hasMine&&!gamePanel.boardVector[col][row].hasFlag){
        numText=gamePanel.minesAroundField(col,row);
    }
        // ODKRYTE, BEZ MINY, FLAGA - NIE MOZLIWE
    else if (gamePanel.boardVector[col][row].isRevealed&&!gamePanel.boardVector[col][row].hasMine&&gamePanel.boardVector[col][row].hasFlag){
        numText=15;
    }
        // ODKRYTE, MINA, BEZ FLAGI - MOZLIWE
    else if (gamePanel.boardVector[col][row].isRevealed&&gamePanel.boardVector[col][row].hasMine&&!gamePanel.boardVector[col][row].hasFlag){
        numText=15;
    }
        // ODKRYTE, MINA, FLAGA - NIE MOZLIWE
    else if (gamePanel.boardVector[col][row].isRevealed&&gamePanel.boardVector[col][row].hasMine&&gamePanel.boardVector[col][row].hasFlag){
        numText=textures.size()+1;
    }else
    {
        numText= textures.size()+1;
    }

    return numText;
}

void GameRender::Render(sf::RenderWindow &window) {

    if (gamePanel.getGameState() == GAMEMENU) {
        MenuRender(window);
    } else if (gamePanel.getGameState() == GAMESTART || gamePanel.getGameState() == GAMECONTINUE) {
        InGameRender(window);
    } else if (gamePanel.getGameState() == GAMEWIN || gamePanel.getGameState() == GAMELOST) {
        PostGameRender(window);
    }

    window.display();
}
