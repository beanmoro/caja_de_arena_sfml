#include "game.h"
#include "include.h"

void Game::keyboardEvents(){
        Event e;
        while(win.pollEvent(e)){


            if(e.type == Event::Closed){
                win.close();
            }

            if(e.type == Event::KeyPressed){
                switch(e.key.code){
                    case Keyboard::Escape:
                         win.close();
                    break;

                    case Keyboard::Left:
                        leftEvent = true;
                        break;
                    case Keyboard::Up:
                        upEvent = true;
                        break;
                    case Keyboard::Right:
                        rightEvent = true;
                        break;
                    case Keyboard::Down:
                        downEvent = true;
                        break;
                    case Keyboard::A:
                        camera.zoom(2);
                        break;
                    case Keyboard::S:
                        camera.zoom(0.5);
                        break;
                    case Keyboard::C:
                        deleteTerrain();
                        generateTerrain(1000, large);
                        break;
                    case Keyboard::L:
                        cout << "Luz creada!" << endl;
                        lights.push_back(Light(Vector2f(mouse_x, mouse_y), Vector2f(0.9f, 0.9f),  Color(255,180,130,255)));
                        break;
                }
            }

            if(e.type == Event::KeyReleased){
                switch(e.key.code){
                    case Keyboard::Left:
                        leftEvent = false;
                        break;
                    case Keyboard::Up:
                        upEvent = false;
                        break;
                    case Keyboard::Right:
                        rightEvent = false;
                        break;
                    case Keyboard::Down:
                        downEvent = false;
                        break;
                }
            }

        }

        if(Mouse::isButtonPressed(Mouse::Left)){

            mbLeft = true;

        }else{

            mbLeft = false;
        }


}
