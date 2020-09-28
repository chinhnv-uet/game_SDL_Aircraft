#include "mainObject.h"

MainObj::MainObj()
{
    //
}

MainObj::~MainObj()
{
    for (unsigned int i = 0; i < bullet_list.size(); i++) delete bullet_list[i];
    bullet_list.clear();
}

void MainObj::LoadPlaneImg(string path)
{
    Plane.LoadImg(path.c_str());
}


void MainObj::BulletMove()
{
    for (int i = 0; i < bullet_list.size(); i++)
    {
        bullet_list[i]->HandleMove();
        if (!bullet_list[i]->Get_isMove()) remove_bullet(i);
    }

}

void MainObj::BulletRender()
{
    for (int i = 0; i < bullet_list.size(); i++) bullet_list[i]->BulletRender();
}

SDL_Rect MainObj::getRect()
{
    SDL_Rect rect;
    rect.x = Plane.getPosX()-5;
    rect.y = Plane.getPosY()+5;
    rect.w = Plane.getWidth() - 10; // to see collosion easier
    rect.h = Plane.getHeight() - 8; //
    return rect;
}

void MainObj::remove_bullet(const int& id)
{
    if (bullet_list.size() > 0 && id < bullet_list.size())
    {

        BulletObject* p_bull = bullet_list.at(id);
        bullet_list.erase(bullet_list.begin() + id);

        if (p_bull != NULL) {
            delete p_bull;
            p_bull = NULL;
        }
    }
}

void MainObj::resert_plane()
{
    Plane.setPosX(0);
    Plane.setPosY(0);
    Plane.setVelX(0);
    Plane.setVelY(0);

    for (unsigned int i = 0; i < bullet_list.size(); i++) delete bullet_list[i];
    bullet_list.clear();
}
