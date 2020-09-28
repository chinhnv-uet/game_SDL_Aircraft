#include "bulletObject.h"

BulletObject::BulletObject()
{
    is_move = false;
    Bullet_Type = 0;
    m_bullet.setVelX(BULLET_VEL);
}

BulletObject::~BulletObject()
{
    is_move = false;
}

void BulletObject::HandleMove()
{
    if (is_move) {
        if (!m_bullet.bulletMove()) is_move = false;
        if (m_bullet.getPosX() > SCREEN_WIDTH) is_move = false;
    }
}

void BulletObject::HandleMoveRightToLeft()
{
    if (is_move)
    {
        m_bullet.setPosX(m_bullet.getPosX() - m_bullet.getVelX());
        if (m_bullet.getPosX() <= 0 || m_bullet.getPosX() > SCREEN_WIDTH) {
            is_move = false;
            m_bullet.setPosX(-10);
            m_bullet.setPosY(-10);
        }
    }

}

void BulletObject::setType(const int& type)
    {
        Bullet_Type = type;
        if (type == 1) m_bullet.LoadImg("laser1.png");
        else if (type == 2) m_bullet.LoadImg("sphere1.png");
    }

void BulletObject::BulletRender()
{
    if (is_move) m_bullet.render();
}

SDL_Rect BulletObject::getBulletRect()
{
    SDL_Rect rect;
    rect.x = m_bullet.getPosX();
    rect.y = m_bullet.getPosY();
    rect.w = m_bullet.getWidth();
    rect.h = m_bullet.getHeight();
    return rect;
}

void BulletObject::setBulletVel(const int &n)
{
    m_bullet.setVelX(n);
}
