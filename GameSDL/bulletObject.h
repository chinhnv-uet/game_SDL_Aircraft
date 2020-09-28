#ifndef BULLETOBJECT_H_INCLUDED
#define BULLETOBJECT_H_INCLUDED
#include "common.h"
#include "Object.h"

class BulletObject
{
public:
    BulletObject();

    ~BulletObject();

    void handleInput(SDL_Event events);

    void HandleMove();

    void HandleMoveRightToLeft();

    int getType() const { return Bullet_Type; }

    void setType(const int& type);

    bool Get_isMove() { return is_move; }

    void Set_isMove(bool _move) { is_move = _move;}

    void setBulletPosX(int n)
    {
        m_bullet.setPosX(n);
    }

    void setBulletPosY(int n) { m_bullet.setPosY(n); }

    Object getBulletObject() { return m_bullet;}

    void BulletRender();

    SDL_Rect getBulletRect();

    void setBulletVel(const int &n);

private:
    Object m_bullet;
    int Bullet_Type;
    bool is_move;
};

#endif // BULLETOBJECT_H_INCLUDED
