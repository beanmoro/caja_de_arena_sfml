#include "game.h"
#include "include.h"

void Game::initLights(){

    lightMapTexture.create( 1280,720);




    lightMap.setTexture(lightMapTexture.getTexture());

    lightTexture.loadFromFile("biglight.png");
    lightTexture.setSmooth(true);

    light.setTexture(lightTexture);
    light.setTextureRect(IntRect(0,0,300,300));
    light.setOrigin(150.f, 150.f);

}

void Game::updateLightMap(){

    lightMapTexture.clear(Color(50,50,80));

    for(int i = 0; i < lights.size(); i++){

        light.setScale(lights[i].scale);
        light.setColor(lights[i].color);
        light.setPosition( lights[i].position.x-camX+(camera.getSize().x/2),lights[i].position.y-camY+(camera.getSize().y/2));

        lightMapTexture.draw(light, sf::RenderStates(BlendAdd));
    }

    lightMapTexture.display();

}

void Game::drawLights(){


    lightMap.setTextureRect(IntRect(0,0,1280,720));
    lightMap.setPosition(camLeft,camTop);


    win.draw(lightMap, sf::RenderStates(BlendMultiply));

}

