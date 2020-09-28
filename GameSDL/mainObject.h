#ifndef MAINOBJECT_H_INCLUDED
#define MAINOBJECT_H_INCLUDED

#include "common.h"
#include "bulletObject.h"
#include "Object.h"
#include <SDL_mixer.h>
class MainObj
{
public:
    MainObj();

    ~MainObj();

    void LoadPlaneImg(string path);

    void HandleInput(SDL_Event e);

    void PlaneMove()
    {
        Plane.move();
    }

    void PlaneRender()
    {
        Plane.render();
    }

    void BulletMove();

    void BulletRender();

    SDL_Rect getRect();

    int getPosX() { return Plane.getPosX();}
    int getPosY() { return Plane.getPosY();}
    int getWidth() { return Plane.getWidth();}
    int getHeight() { return Plane.getHeight();}

    vector<BulletObject*> getBulletList() { return bullet_list;}

    void remove_bullet(const int& id);
    void resert_plane();

private:
    Object Plane;

    vector<BulletObject*> bullet_list;
};

#endif // MAINOBJECT_H_INCLUDED
