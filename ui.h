#include <SDL_ttf.h>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED

using namespace std;

class Text{

    int x, y, ww, hh;
    TTF_Font* fnt;
    SDL_Texture* texture;
    SDL_Color col;
    SDL_Rect pos[2];


public:
    Text(int _x, int _y);
    void txt_Draw(SDL_Renderer *ren, string _text);


};

class UI{
    Text clock1;

public:

    UI();
    void ui_Step();
    void ui_Draw(string _text, SDL_Renderer *ren);
};

#endif // UI_H_INCLUDED
