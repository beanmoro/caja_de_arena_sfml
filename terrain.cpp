#include "game.h"
#include "include.h"

void Game::generateTerrain(int seed, mapType _size){

    int rLvl, rLvl_2, cRand, cTileRandX, cTileRandY, caveW, caveH, caveChunk, countX, countY, caveVariant, caveNumber, caveChunk_tmp, caveChunk_tmp2;
    bool otherChunkY, otherChunkX;

    // -- Cargar Tiles -- //
    //tmp_Surface = IMG_Load("beta_tile.png");
    //tilesImage = SDL_CreateTextureFromSurface(ren, tmp_Surface);
    //SDL_FreeSurface(tmp_Surface);

    tmp_Texture.loadFromFile("beta_tile.png");


    // -- Definir Tamaño del mapa -- //
    if(_size == small){
        terrainSize = 512;
        cout << "Creating small terrain." << endl;
    }else if(_size == normal){
        terrainSize = 1024;
        cout << "Creating normal terrain." << endl;
    }else if(_size == large){
        terrainSize = 2048;
        cout << "Creating large terrain." << endl;
    }

    xChunk = terrainSize/16;
    yChunk = terrainSize/16;
    maxChunks = xChunk*yChunk;
    confChunks();

    // -- Definir Array -- //
    terrain = new int**[maxChunks];
    for(int i = 0;  i < maxChunks; i++){
        terrain[i] = new int*[16];
        for(int j = 0; j < 16; j++){
            terrain[i][j] = new int[16];
        }
    }

    // -- Llenar terreno con vacio -- //
    for(int i = 0;  i < maxChunks; i++){
        for(int j = 0; j < 16; j++){
            for(int k = 0; k < 16; k++){
                terrain[i][j][k] = 0;
            }
        }
    }

    // -- Creando Terreno desnivelado -- //
    for(int i = 0; i < xChunk; i++){

        for(int j = 0; j < 16; j++){
            rLvl =randomNumber(6,12);
            rLvl_2 = randomNumber(10,14);

            // -- Poner piedra en el subsuelo -- //
            for(int k = 9; k < yChunk; k++){
                for(int l = 0; l < 16; l++){
                    terrain[(k*xChunk)+i][l][j] = 1;
                }
            }
        }
    }

    genHills(2, 0, 7); // Generar Superficie
    genHills(1, 2, 8); // Generar Division entre la superficie y el subsuelo
    genCaves(500);

        // -- Deteccion de cambio -- //
        // -- Poner Material  2 encima de Material 1 si esque no hay nada -- //
        for(int i = 0; i < maxChunks; i++){
            for(int j = 0; j < 16; j++){
                for(int k = 0; k < 16; k++){

                    if(terrain[i][j][k] == 1){

                        for(int l = 0; l < randomNumber(2, 6); l++){

                            if(j-l >= 0){
                                if(terrain[i][j-l][k] == 0){
                                    terrain[i][j-l][k] = 2;
                                }
                                //cout << "Entra!" << endl;
                            }else{

                                if(terrain[i-(xChunk)][(j-l)+16][k] == 0){
                                    terrain[i-(xChunk)][(j-l)+16][k] = 2;
                                }
                            }
                        }
                    }
                }
            }
        }
    createTerrain();
}

void Game::deleteTerrain(){

    for(int i = 0;  i < maxChunks; i++){

        for(int j = 0; j < 16; j++){
            delete[] terrain[i][j];
            delete[] onTerrain[i][j];
        }
        delete[] terrain[i];
        delete[] onTerrain[i];
    }
    delete[] terrain;
    delete[] onTerrain;

    terrain = NULL;
    onTerrain = NULL;




}

void Game::createTerrain(){

    int id;
    createTerrainData();
    for(int i = 0; i < maxChunks; i++){
            for(int j = 0; j < 16; j++){
                for(int l = 0; l < 16; l++){

                        id = terrain[i][j][l];

                        onTerrain[i][j][l].name =  dataBlock[id].name;
                        onTerrain[i][j][l].cutX = dataBlock[id].cutX;
                        onTerrain[i][j][l].cutY = dataBlock[id].cutY;
                        onTerrain[i][j][l].anim = dataBlock[id].anim;
                        onTerrain[i][j][l].frames = dataBlock[id].frames;
                        onTerrain[i][j][l].durability = dataBlock[id].durability;
                        onTerrain[i][j][l].gravity = dataBlock[id].gravity;
                        onTerrain[i][j][l].blockId = id;

                        onTerrain[i][j][l].chunk = i;
                        onTerrain[i][j][l].x = chunkCoord[i].left+(l*16);
                        onTerrain[i][j][l].y = chunkCoord[i].top+(j*16);

                }
            }
    }
    //cout << onTerrain.size() << endl;

}


void Game::drawTerrain(){

    //Vector2f cameraSize = camera.getSize();


    for(int i = 0; i < maxChunks; i++){
        // -- Si esquina (0,0) o esquina (16,16) esta dentro de la pantalla de el paso al mas comprobaciones (Metodo antilag) -- //
        if( ( (chunkCoord[i].left) < camX+(camera.getSize().x/2) && (chunkCoord[i].top) < camY+(camera.getSize().y/2))
           && ( (chunkCoord[i].left+chunkCoord[i].width) > camX-(camera.getSize().x/2) && (chunkCoord[i].top+chunkCoord[i].height) > camY-(camera.getSize().y/2)) ){

            for(int j = 0; j < 16; j++){
                for(int l = 0; l < 16; l++){


                        if( (chunkCoord[i].left+(l*16)) > camX-(camera.getSize().x/2)-32 && (chunkCoord[i].top+(j*16)) > camY-(camera.getSize().y/2)-32
                           && (chunkCoord[i].left+(l*16)+16) < camX+(camera.getSize().x/2)+32 && (chunkCoord[i].top+(j*16)+16) < camY+(camera.getSize().y/2)+32 )  {


                                onTerrain[i][j][l].image.setTexture(tmp_Texture);
                                onTerrain[i][j][l].image.setPosition(Vector2f(onTerrain[i][j][l].x,onTerrain[i][j][l].y));
                                onTerrain[i][j][l].image.setTextureRect(IntRect(onTerrain[i][j][l].cutX*16,onTerrain[i][j][l].cutY*16,16,16));
                                win.draw(onTerrain[i][j][l].image);






                        }
                    }
                }


        }
    }

}

void Game::genHills(int mat0, int mat1, int chunkLvl){

    int yPos = 0, yLvl = 15, minH = 12, maxH = 2, swt = 0, chance = 0, yPos2 = 0;
    int indX= 0, indY= 0, indChunk = 0;

    while(indChunk < xChunk){


        while(indX < 16){

            // -- Cambio de altura -- //
            if(swt==0){
                yLvl += randomNumber(0,randomNumber(1,4));
            }else if(swt == 1 ){
                yLvl -= randomNumber(0,randomNumber(1,4));
            }

            // -- AntiCrash -- //
            if(yLvl > 15){
                swt=1;
                yLvl=15;
            }else if( yLvl < 0){
                swt=0;
                yLvl=0;
            }

            // Chance para cambio brusco -- //
            chance = randomNumber(0, 1000);
            if(chance > 500 && chance < 600){
                if(swt == 0){ swt=1;}else{swt=0;}
                    minH = randomNumber(8, 14);
                    maxH = randomNumber(0, 8);
            }

            // -- Crear pilar -- //
            yPos = yLvl;
            yPos2 = yLvl-1;
            while(yPos < 16){
                terrain[(chunkLvl*xChunk)+indChunk][yPos][indX] = mat0;
                yPos++;
            }

            while(yPos2 >=  0){
                terrain[(chunkLvl*xChunk)+indChunk][yPos2][indX] = mat1;
                yPos2--;
            }

        indX++;
        yPos = 0;
        }
        indChunk++;
        indX = 0;
    }





}

void Game::genCaves(int caves){

    int nCaves = caves, caveCounter = 0, n_Chunk = 0, tmp_Chunk = 0, caveWidth, xRand, yRand, xx, yy, yHeight, xInd = 0, yInd = 0, swt = 0, yLvl, chance, border;
    int planeCounter = 0, oldY;
    bool UseTempChunk = false;


    while(caveCounter < nCaves){

        n_Chunk = randomNumber(8*xChunk,maxChunks-1);
        tmp_Chunk = n_Chunk;
        xRand = randomNumber(0,8);
        yRand = randomNumber(0,8);
        caveWidth = randomNumber(10,128);
        xx = 0;
        xInd = xRand;
        yInd = yRand;


        while(xx < caveWidth){

            if(xInd > 15){
                xInd -=16;
                if(n_Chunk+1 < maxChunks-1){
                    n_Chunk +=1;
                }
            }


            if(swt==0){
                yLvl += randomNumber(0,randomNumber(1,4));
            }else if(swt == 1 ){
                yLvl -= randomNumber(0,randomNumber(1,4));
            }

            chance = randomNumber(0, 1000);
            if(chance > 500 && chance < 600){
                if(swt == 0){ swt=1;}else{swt=0;}
                if(swt==0){
                    yLvl += randomNumber(0,randomNumber(1,4));
                }else if(swt == 1 ){
                    yLvl -= randomNumber(0,randomNumber(1,4));
                }
            }



            if(oldY == yLvl && xx > 0){

                while(planeCounter > 5 && oldY == yLvl){
                    if(swt==0){
                        yLvl += randomNumber(0,randomNumber(1,4));
                    }else if(swt == 1 ){
                        yLvl -= randomNumber(0,randomNumber(1,4));
                    }

                }


                planeCounter++;
            } else if( oldY != yLvl && planeCounter > 5 && xx > 0){
                planeCounter = 0;
            }


            // -- AntiCrash -- //
            if(yLvl > 15){
                swt=1;
                yLvl=15;
            }else if( yLvl < 0){
                swt=0;
                yLvl=0;
            }




            yHeight = randomNumber(12,16);
            yInd = yRand+yLvl;
            oldY = yLvl;
            yy = 0;
            border = abs(caveWidth-xx);


            while(yy < yHeight){

                if(yInd > 15){
                    yInd -=16;
                    if(n_Chunk+(xChunk) < maxChunks){
                        tmp_Chunk=n_Chunk+xChunk;
                    }
                    UseTempChunk = true;
                }


                if(UseTempChunk){
                    terrain[tmp_Chunk][yInd][xInd] = 0;
                }else{
                    terrain[n_Chunk][yInd][xInd] = 0;
                }
                yy++;
                yInd++;
            }
            UseTempChunk = false;
            xInd++;
            xx++;
        }
        caveCounter++;
    }




}
