#include "explosion.h"

explosion::explosion()
    {
        frame = 0;
    }

explosion::~explosion()
{
    exp_texture.free();
}

void explosion::load_ExpImg(string path)
{
    if(!exp_texture.loadFromFile(path.c_str() )) cout << "cant load img " << path << endl;
}

void explosion::setClip()
{
    clips[0].x = 0;
    clips[0].y = 0;
    clips[0].w = EXP_WIDTH;
    clips[0].h = EXP_HEIGHT;

    clips[1].x = EXP_WIDTH;
    clips[1].y = 0;
    clips[1].w = EXP_WIDTH;
    clips[1].h = EXP_HEIGHT;

    clips[2].x = EXP_WIDTH*2;
    clips[2].y = 0;
    clips[2].w = EXP_WIDTH;
    clips[2].h = EXP_HEIGHT;

    clips[3].x = EXP_WIDTH*3;
    clips[3].y = 0;
    clips[3].w = EXP_WIDTH;
    clips[3].h = EXP_HEIGHT;

}

void explosion::show(const int& x_, const int &y_, const int &type)
{
    exp_texture.render(x_, y_, getRect(), type);
}


