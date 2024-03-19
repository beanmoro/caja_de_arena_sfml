#include "game.h"
#include "include.h"

int Game::randomNumber(int from, int to){

    return (rand() % (to-from)) + from;
}

void Game::FPS(){

    if( loopStartTicks-startTicks > 1000){
        nFPS = framesPassed;
        framesPassed = 0;
        startTicks = gameTime.asMilliseconds();
    }


}
