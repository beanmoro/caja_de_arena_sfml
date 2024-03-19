#include "game.h"
#include "include.h"

void Game::updateEvents(){



    for(int i = 0; i < maxChunks; i++){

        if(mouse_x > chunkCoord[i].left && mouse_y > chunkCoord[i].top && mouse_x < (chunkCoord[i].left+chunkCoord[i].width) && mouse_y < (chunkCoord[i].top-chunkCoord[i].height)){
            cout << "Entra!" << endl;
            for(int j  = 0; j < 16; j++){
                for(int k = 0; k < 16; k++){

                    if(onTerrain[i][j][k].x < mouse_x &&
                       onTerrain[i][j][k].y < mouse_y &&
                       onTerrain[i][j][k].x+16 > mouse_x &&
                       onTerrain[i][j][k].y+16 > mouse_y && mbLeft == true && onTerrain[i][j][k].blockId != 0){

                        if(loopStartTicks-destroyBlockDelay > 100){

                            if(onTerrain[i][j][k].durability > 0){
                                onTerrain[i][j][k].durability-=100;
                            }
                            destroyBlockDelay = gameTime.asMilliseconds();
                        }


                    }

                    if(onTerrain[i][j][k].durability <= 0){
                        onTerrain[i][j][k] = dataBlock[0];

                    }



                }
            }
        }
    }

    if(leftEvent){camX -= camSpeed/zoomW; }
    if(upEvent){camY -= camSpeed/zoomW; }
    if(rightEvent){camX += camSpeed/zoomW; }
    if(downEvent){camY += camSpeed/zoomW; }


}
