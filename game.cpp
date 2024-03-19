#include "game.h"
#include "include.h"

Game::Game() : win( VideoMode(1280, 720) , "Caja de Arena 001 en SFML")
    {
    r = 0;
    g = 0;
    b = 0;
    rLimit = 189;
    gLimit = 255;
    bLimit = 249;
    tpd = 60*1000;
    days = 0;
    rpd = (tpd/2)/rLimit;
    gpd = (tpd/2)/gLimit;
    bpd = (tpd/2)/bLimit;

    tph = tpd/24;
    tpm = tph/60;
    tps = tpm/60;

    tileW = 16;
    tileH = 16;

    camX = 0+camera.getSize().x/2;
    camY = 0+camera.getSize().y/2;
    camSpeedX = 0;
    camSpeedY = 0;
    camMaxSpeed = 16;
    camSpeed = 16;

    mouse_x = 0;
    mouse_y = 0;
    camLeft = 0;
    camTop = 0;

    leftEvent = false;
    upEvent = false;
    rightEvent = false;
    downEvent = false;
    mbLeft = false;

    startTicks = gameTime.asMilliseconds();
    destroyBlockDelay = gameTime.asMilliseconds();

    screenW = 1280;
    screenH = 720;

    zoomW = 1;
    lastTile = 0;



}


void Game::init(){

    // -- Inicializar Random -- //
    srand(time(NULL));
    camera.reset(FloatRect(0,0,1280,720));

    fnt.loadFromFile("pixelmix_bold.ttf");
    tClock.setFont(fnt);
    tClock.setCharacterSize(16);
    tClock.setColor(Color::White);


    tFps.setFont(fnt);
    tFps.setCharacterSize(16);
    tFps.setColor(Color::White);
    lights.push_back(Light(Vector2f(2000, 2500), Vector2f(0.9f, 0.9f),  Color(255,180,130,255)));

    loadTilesFile();
    loadBlocks();
    generateTerrain(1000, large);
    initLights();


}

void Game::update(){

    while(win.isOpen()){



        gameTime = globalTimer.getElapsedTime();
        mouseCoords = Mouse::getPosition(win);
        camera.setCenter( (float) camX, (float) camY);
        mouse_x = mouseCoords.x+(camX-(int) camera.getSize().x/2);
        mouse_y = mouseCoords.y+(camY-(int) camera.getSize().y/2);
        camLeft = camera.getCenter().x-(camera.getSize().x/2);
        camTop = camera.getCenter().y-(camera.getSize().y/2);


        // -- Actualizacion Ciclo Dia/Noche -- //
        dayCycle();
        updateLightMap();

        loopStartTicks = gameTime.asMilliseconds();
        FPS();

        // -- Input -- //
        keyboardEvents();

        // -- Eventos -- //
        updateEvents();

        // -- Actualizacion de informacion a clock -- //
        tClock.setPosition(camLeft+2,camTop+2);
        tFps.setPosition(camLeft+2,camTop+32);


        sprintf(Reloj, "%02d:%02d:%02d Dia: %02d", hours, minutes, seconds, days);
        sprintf(cFPS, "FPS: %02d X: %d Y: %d\nC = Generar Nuevo Mapa (Laggy).\nS = ZoomIn.\nA = ZoomOut.\nEsc = Salir.\nL = Crear Luz (En el Puntero).", nFPS, mouse_x, mouse_y);


        tClock.setString(Reloj);
        tFps.setString(cFPS);
        win.setView(camera);

        // -- Draw -- //


        win.clear(Color::Black);


        drawTerrain();

        drawLights();

        win.draw(tClock);
        win.draw(tFps);

        framesPassed++;
        win.display();

    }
}
