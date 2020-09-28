#ifndef ENEMYOBJECT_H_INCLUDED
#define ENEMYOBJECT_H_INCLUDED

#include "common.h"
#include "bulletObject.h"
#include "Object.h"

class EnemyObject
{
public:
    EnemyObject();

    ~EnemyObject();

    void loadEnemyImg(string path)
    {
        enemy.LoadImg(path.c_str());
    }

    void InitBullet(BulletObject* enemy_bullet);

    void MakeBullet();

    void E_BulletRender();

    void EnemyMove() {  enemy.move(); }

    void EnemyRender();

    void setPosX(const int& n)
    {
        enemy.setPosX(n);
    }
    void setPosY(const int& n)
    {
        enemy.setPosY(n);
    }

    void setVelX(const int& n)
    {
        enemy.setVelX(n);
    }

    int getVelX() { return enemy.getVelX();}

    int getPosX() { return enemy.getPosX();}

    int getPosY() { return enemy.getPosY(); }

    SDL_Rect getRect();

    vector<BulletObject*> getEBulletList() { return e_bullet_list;}

    int MakeRandValue();

    void resertPosision();

    void setBulletVelX(const int &n);
private:
    Object enemy;
    vector<BulletObject*> e_bullet_list;
};

#endif // ENEMYOBJECT_H_INCLUDED
