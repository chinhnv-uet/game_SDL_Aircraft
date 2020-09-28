#include "enemyObject.h"

EnemyObject::EnemyObject()
{
    //
}

EnemyObject::~EnemyObject()
{
    for (int i = 0; i < e_bullet_list.size(); i++) delete e_bullet_list[i];
    e_bullet_list.clear();
}

void EnemyObject::InitBullet(BulletObject* enemy_bullet)
{
    if (enemy_bullet)
    {
        enemy_bullet->setType(2);
        enemy_bullet->Set_isMove(true);
        enemy_bullet->setBulletPosX(enemy.getPosX());
        enemy_bullet->setBulletPosY(enemy.getPosY() + enemy.getHeight()/2);
        e_bullet_list.push_back(enemy_bullet);
    }
}

void EnemyObject::MakeBullet()
{
    for (int i = 0; i < e_bullet_list.size(); i++)
    {
        BulletObject* p_bullet = e_bullet_list.at(i);
        if (p_bullet)
        {
            if (p_bullet->Get_isMove())
            {
                p_bullet->HandleMoveRightToLeft();
            }
            else {
                p_bullet->Set_isMove(true);
                p_bullet->setBulletPosX(enemy.getPosX());
                p_bullet->setBulletPosY(enemy.getPosY() + enemy.getHeight()/2);
            }
        }
    }
}

void EnemyObject::E_BulletRender()
{
    for (int i = 0; i < e_bullet_list.size(); i++) e_bullet_list[i]->BulletRender();
}

void EnemyObject::EnemyRender()
    {
        if (enemy.getPosX() <= 0) {
            enemy.setPosX(SCREEN_WIDTH-enemy.getWidth()-10);
            enemy.setPosY(MakeRandValue());
        }
        enemy.render();
    }

SDL_Rect EnemyObject::getRect()
    {
        SDL_Rect rect;
        rect.x = enemy.getPosX();
        rect.y = enemy.getPosY();
        rect.w = enemy.getWidth();
        rect.h = enemy.getHeight();
        return rect;
    }

void EnemyObject::resertPosision()
{
    enemy.setPosX(SCREEN_WIDTH);
    enemy.setPosY(MakeRandValue());
}

int EnemyObject::MakeRandValue()
{
    return rand() % (SCREEN_HEIGHT*7/10);
}

void EnemyObject::setBulletVelX(const int &n)
{
    for (int i = 0; i < e_bullet_list.size(); i++)
    {
        e_bullet_list[i]->setBulletVel(n);
    }
}
