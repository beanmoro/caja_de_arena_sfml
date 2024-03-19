#include "include.h"

#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED



class Game{
    // -- General -- //
    RenderWindow win;
    Time gameTime;
    int globalTime;
    Texture tmp_Texture;
    Clock globalTimer;
    View camera;


    bool OnGame;

    int screenW = 1280, screenH = 720;
    float zoomW, zoomH;
    int mouse_x, mouse_y;

    Vector2i mouseCoords;

    // -- Fuentes -- //
    Font fnt;

    // -- DayCycle -- //
    int r, g, b, rLimit, gLimit, bLimit;
    int tpd;
    float rpd, gpd, bpd, tph, tpm, tps;
    int days, hours, minutes;
    int seconds;

    // -- Textos -- //
    char Reloj[50];
    char cFPS[999];
    Text tClock, tFps;

    // -- Camara -- //
    int camX, camY, camSpeedX, camSpeedY, camMaxSpeed, camSpeed, camLeft, camTop;


    // -- Terreno -- //
    int ***terrain;
    enum mapType {small, normal, large};
    int tileW, tileH, tileSize, chunkArea;
    int terrainSize, ChunkNumber, maxChunks, xChunk, yChunk, aChunk, lastTile;
    IntRect tilePos, imgCut;


    // -- Keyboard & Mouse -- //
    bool leftEvent, upEvent, rightEvent, downEvent, mbLeft;

    // -- Events -- //
    int oldCnt;
    int startTicks;
    int loopStartTicks;
    int framesPassed = 0;
    int nFPS = 0;


    // -- Tiles -- //
    string* tilesName; // Nombre, Coordenada X, Coordenada Y, Numero Frames(10);
    int** tilesParam;
    int blocksFileLines, blocksFileOptions;

    // -- Chunks -- //

    IntRect *chunkCoord;

    // -- Bloques -- //

    struct Block{ // Bloque base
        string name;
        int x, y, chunk, blockId;
        int cutX, cutY;
        int durability, gravity;
        int anim, frames;
        bool exist = true;
        Sprite image;
    };

    Block*** onTerrain; // Contiene los bloques en terreno
    vector<Block> dataBlock;// Contiene toda la lista de tipos de bloques
    int destroyBlockDelay = 0;


    // -- Luz -- //
    Texture lightTexture;
    Sprite light;

    RenderTexture lightMapTexture;
    Sprite lightMap;

    struct Light{
        Vector2f position;
        Vector2f scale;
        Color color;
        Light(Vector2f nposition, Vector2f nscale, Color ncolor) :
            position(nposition),
            scale(nscale),
            color(ncolor)
        {
        }
    };

    vector<Light> lights;




public:

    Game();
    void init();
    void update();
    void dayCycle();
    void text(int x, int y, string _text);
    void generateTerrain(int seed, mapType _size);
    void drawTerrain();
    void keyboardEvents();
    void updateEvents();
    void searchTiles(int terrainNumber, int xCut, int yCut);
    void loadTilesFile();
    void verifyTilesFile(string filename);
    void genHills(int mat0, int mat1, int chunkLvl);
    void genCaves(int caves);
    void deleteTerrain();

    void initLights();
    void updateLightMap();
    void drawLights();

    void verifyBlocksFile(string filename);
    void loadBlocks();
    void createTerrain();
    void createTerrainData();

    void FPS();

    // -- Metodos Utiles -- //
    int randomNumber(int from, int to);
    void confChunks();


};

#endif // GAME_H_INCLUDED
