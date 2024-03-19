#include "game.h"
#include "include.h"


void Game::confChunks(){

    chunkCoord = new IntRect[maxChunks];
    int n_var = 0;
    int preSize = 256;

    for(int i = 0; i < yChunk; i++){
        n_var = i*xChunk;
        for(int j = 0; j< xChunk; j++){
            chunkCoord[n_var].left = preSize*j;
            chunkCoord[n_var].top = preSize*i;
            chunkCoord[n_var].width = preSize;
            chunkCoord[n_var].height = preSize;

            n_var++;
        }
    }




}
