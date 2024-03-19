#include "game.h"
#include "include.h"

void Game::verifyTilesFile(string filename){
/*
    string line;
    string u;

    ifstream tilesFile;
    tilesFile.open(filename.c_str(), ios::in);
    int x_size = 0;
    int y_size = 0;

    if(tilesFile.fail()){
        cout << "ERROR AL VERIFICAR TILES!" << endl;

    }else{
        while(getline(tilesFile, line)){
            istringstream _stream(line);
            x_size = 0;
            while(_stream >> u){
                x_size++;
            }
            y_size++;
        }
        tilesFileLines = y_size;
        tilesFileOptions = x_size;

    }
    tilesFile.close();*/
}

void Game::searchTiles(int terrainNumber, int xCut, int yCut){

    if(terrainNumber != 0){
        xCut = tilesParam[terrainNumber][0]*16;
        yCut = tilesParam[terrainNumber][1]*16;
        cout << "WENA" << endl;
    }
    //cout << tilesParam[terrainNumber][0] << " " << tilesParam[terrainNumber][1] << endl;
}

void Game::loadTilesFile(){
/*
    ifstream tilesFile;
    string filename = "tiles.tte";
    tilesFile.open(filename.c_str(), ios::in);

    if(tilesFile.fail()){

        cout << "ERROR AL CARGAR ARCHIVO DE TILES!" << endl;
    }else{

        verifyTilesFile(filename);

        tilesName = new string[tilesFileLines];
        tilesParam = new int*[tilesFileLines];
        for(int i = 0; i < tilesFileLines; i++){
            tilesParam[i] = new int[3];
        }

        for(int i = 0; i < tilesFileLines; i++){
            for(int j = 0; j < tilesFileOptions; j++){

                if(j == 0){
                    tilesFile >> tilesName[i];
                    cout << tilesName[i] << endl;
                }else if(j == 1){
                    tilesFile >> tilesParam[i][0];
                }else if(j == 2){
                    tilesFile >> tilesParam[i][1];
                }else if(j == 3){
                    tilesFile >> tilesParam[i][2];
                }


            }
        }
    }
    tilesFile.close();
    */

}
