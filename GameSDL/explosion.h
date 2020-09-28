#ifndef EXPLOSION_H_INCLUDED
#define EXPLOSION_H_INCLUDED

#include "common.h"
#include "Ltexture.h"
//size of explore image
const int EXP_WIDTH = 165;
const int EXP_HEIGHT = 165;

class explosion
{
public:
    explosion();

    ~explosion();

    void load_ExpImg(string path);

    void setFrame(int n) { frame = n;}

    void setClip();

    SDL_Rect* getRect() { return &clips[frame];}

    void show(const int& x_, const int &y_, const int &type = 0);

private:
    int frame;
    SDL_Rect clips[4];
    LTexture exp_texture;
};

#endif // EXPLOSION_H_INCLUDED
