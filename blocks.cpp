#include "game.h"
#include "include.h"

void Game::loadBlocks(){

    Block tempBlock;
    ifstream blocksFile;
    string filename = "blocks.tte";
    int counter = 0;
    blocksFile.open(filename.c_str(), ios::in);

    if(blocksFile.fail()){

        cout << "ERROR AL CARGAR ARCHIVO DE BLOQUES!" << endl;
    }else{

        verifyBlocksFile(filename);

        for(int i = 0; i < blocksFileLines; i++){

            blocksFile >> tempBlock.name;
            if(tempBlock.name[0] != '#' ){
                tempBlock.blockId = i-counter;
                blocksFile >> tempBlock.cutX >> tempBlock.cutY >> tempBlock.anim >> tempBlock.frames >> tempBlock.durability >> tempBlock.gravity;
                dataBlock.push_back(tempBlock);

            }else{
                counter++;
                //cout << tempBlock.name << endl;
            }

        }
    }



    blocksFile.close();


}

void Game::verifyBlocksFile(string filename){
    string line;
    string u;

    ifstream blockFile;
    blockFile.open(filename.c_str(), ios::in);
    int x_size = 0;
    int y_size = 0;

    if(blockFile.fail()){
        cout << "ERROR AL VERIFICAR blockS!" << endl;

    }else{
        while(getline(blockFile, line)){
            istringstream _stream(line);
            x_size = 0;
            while(_stream >> u){
                x_size++;
            }
            y_size++;
        }
        blocksFileLines = y_size;
        blocksFileOptions = x_size;

    }
    blockFile.close();


}

void Game::createTerrainData(){

    onTerrain = new Block**[maxChunks];
    for(int i = 0; i < maxChunks; i++){
        onTerrain[i] = new Block*[16];
        for(int j = 0; j< 16; j++){
            onTerrain[i][j] = new Block[16];

        }
    }

}
