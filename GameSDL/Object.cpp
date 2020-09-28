#include "Object.h"
//
Object::Object()
{
    //Initialize the offsets
    mPosX = 0;
    mPosY = 0;

    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
}

Object::~Object()
{
    imgLoadedl.free();
}

void Object::handleEvent( SDL_Event& e )
		{

		    //If a key was pressed
            if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
            {
                //Adjust the velocity
                switch( e.key.keysym.sym )
                {
                    case SDLK_UP: mVelY -= OBJECT_VEL; break;
                    case SDLK_DOWN: mVelY += OBJECT_VEL; break;
                    case SDLK_LEFT: mVelX -= OBJECT_VEL; break;
                    case SDLK_RIGHT: mVelX += OBJECT_VEL; break;
                }
            }
            //If a key was released
            else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
            {
                //Adjust the velocity
                switch( e.key.keysym.sym )
                {
                    case SDLK_UP: mVelY += OBJECT_VEL; break;
                    case SDLK_DOWN: mVelY -= OBJECT_VEL; break;
                    case SDLK_LEFT: mVelX += OBJECT_VEL; break;
                    case SDLK_RIGHT: mVelX -= OBJECT_VEL; break;
                }
            }
		}

void Object::move()
		{
            //Move the dot left or right
            mPosX += mVelX;

            //If the dot went too far to the left or right
            if( ( mPosX < 0 )  )
            {
                //Move back
                mPosX = 0;
            }

            //Move the dot up or down
            mPosY += mVelY;

            //If the dot went too far up or down
            if( ( mPosY < 0 ) || ( mPosY + OBJECT_VEL + imgLoadedl.getHeight() > SCREEN_HEIGHT*8/10 ) )
            {
                //Move back
                mPosY -= mVelY;
            }
		}

bool Object::bulletMove()
		{
		    mPosX += mVelX;
            if (mPosX + imgLoadedl.getWidth() > SCREEN_WIDTH) return false;
            return true;
		}



void Object::LoadImg(string path)
        {
            imgLoadedl.loadFromFile(path);
        }
