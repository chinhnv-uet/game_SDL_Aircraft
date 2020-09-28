#pragma once
#include "common.h"
#include "Ltexture.h"

class Object
{
    public:

		//Initializes the variables
		Object();

        ~Object();

		//Takes key presses and adjusts the dot's velocity
		void handleEvent( SDL_Event& e );

		//Moves the dot
		void move();

		//move bullet
		bool bulletMove();

		//Shows the dot on the screen
		void render();

        //load img
        void LoadImg(string path);

        void setPosX(int n) { mPosX = n;}
        int getPosX() { return mPosX;}

        void setPosY(int n) { mPosY = n;}
        int getPosY() { return mPosY;}

        void setVelX(int n) { mVelX = n;}
        int getVelX() { return mVelX;}

        void setVelY(int n) { mVelY = n;}
        int getVelY() { return mVelY;}

        int getWidth() { return imgLoadedl.getWidth();}

        int getHeight() { return imgLoadedl.getHeight();}

        LTexture getBulletObject() { return imgLoadedl;}
    private:
		//The X and Y offsets of the dot
		int mPosX, mPosY;

		//The velocity of the dot
		int mVelX, mVelY;

		LTexture imgLoadedl;
};

