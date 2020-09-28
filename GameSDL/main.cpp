#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <SDL_ttf.h>
#include "common.h"
#include "Ltexture.h"
#include "Object.h"
#include "bulletObject.h"
#include "mainObject.h"
#include "enemyObject.h"
#include "explosion.h"
#include "Menu.h"
#include <SDL_mixer.h>

using namespace std;

bool init();
bool loadMedia();
void close();

// check collision
bool checkCollosion(SDL_Rect a, SDL_Rect b);

//to load and render background
LTexture gBGTexture;

//explore animation
explosion Exp_plane;
explosion exp_enemy;

//load text and render text to screen
LTexture gTextTexture;

//plane Object;
MainObj my_plane;
EnemyObject* p_enemy;

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
        {
            cout << "Failed to initialize!\n";
            return 0;
        }

GameStart:

        //init score and enemy when start a game
        int score = 0;
        p_enemy = new EnemyObject[Num_Enemy];
        srand(time(0));

		//Load media
		if( !loadMedia() )
		{
			cout << "Failed to load media!\n" ;
		}
		else
		{
            //Main loop flag
			bool quit = false;


			//Event handler
			SDL_Event e;

            //The background scrolling offset
			int scrollingOffset = 0;

            //menu start game
            if (!skipMenu) {
                int res = showMenu(); // case 1 for quit and case 0 for play game
                if (res == 1) quit = true;
                else quit = false;
            }

			//While application is running
			while( !quit )
			{

				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
                    else my_plane.HandleInput(e);
				}

                my_plane.PlaneMove();
                my_plane.BulletMove();

                for (int i = 0; i < Num_Enemy; i++)
                {
                    EnemyObject *n_enemy = (p_enemy + i);
                    n_enemy->EnemyMove();
                    n_enemy->MakeBullet();
                }

                //Scroll background
				--scrollingOffset;
				if( scrollingOffset < -gBGTexture.getWidth() ) scrollingOffset = 0;

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0, 255, 255, 0xFF );
				SDL_RenderClear( gRenderer );

                //Render background
				gBGTexture.render( scrollingOffset, 0 );
				gBGTexture.render( scrollingOffset + gBGTexture.getWidth(), 0 );

                //render my plane
                my_plane.PlaneRender();
                my_plane.BulletRender();

                //init and render score string to screen
                string text = "Score: ", tmp;
                tmp = to_string(score);
                text += tmp;
                gTextTexture.loadFromRenderedText(text, BLACK);
                gTextTexture.render(20, 0);

                for (int i = 0; i < Num_Enemy; i++)
                {
                    EnemyObject *n_enemy = (p_enemy + i);

                    //set veloc by score
                    if (score >= 0 && score <= 50) {
						n_enemy->setVelX(-ENEMY_VEL1);
                        n_enemy->setBulletVelX(ENEMY_VEL1+2);
					}
					else if (score > 50 && score <= 150) {
						n_enemy->setVelX(-ENEMY_VEL2);
						n_enemy->setBulletVelX(ENEMY_VEL2+2);
					}
					else if (score > 150 && score <= 300) {
						n_enemy->setVelX(-ENEMY_VEL3);
						n_enemy->setBulletVelX(ENEMY_VEL3+2);
					}
					else if (score > 300 && score <= 500)
                    {
                        n_enemy->setVelX(-ENEMY_VEL4);
                        n_enemy->setBulletVelX(ENEMY_VEL4+2);
                    }
					else {
                            n_enemy->setVelX(-ENEMY_VEL5);
                            n_enemy->setBulletVelX(ENEMY_VEL5+2);
					}

                    n_enemy->E_BulletRender();
                    n_enemy->EnemyRender();
                }

                //handle collosion
                for (int i = 0; i < Num_Enemy; i++)
                {
                    EnemyObject *n_enemy = (p_enemy + i);

                    //check collosion between my plane and enemy plane
                    if (checkCollosion(my_plane.getRect(), n_enemy->getRect()) )
                    {
                        Mix_PlayChannel(-1, exploMain_m, 0);

                        //animation when explore
                        for (int ex = 0; ex < 4; ex++)
                            {
                                Exp_plane.setFrame(ex);
                                Exp_plane.show(my_plane.getPosX()-30 , my_plane.getPosY() -30);
                                SDL_Delay(100);
                                SDL_RenderPresent(gRenderer);
                            }

                        SDL_Delay(1000);

                        //show gameOver img and handle event
                        int GoverSelect = gameOver(score);
                        if (GoverSelect == 0) quit = true;
                        else if (GoverSelect == 1) {
                            skipMenu = true;
                            delete [] p_enemy;
                            my_plane.resert_plane();

                            goto GameStart;
                        }
                        else if (GoverSelect == 2) {
                            skipMenu = false;
                            delete [] p_enemy;
                            my_plane.resert_plane();
                            goto GameStart;
                        }

                    }

                    //ckeck collosion between  enemy bullet and my plane
                    vector<BulletObject*> E_bullet = n_enemy->getEBulletList();
                    for (unsigned int j = 0; j < E_bullet.size(); j++)
                    {
                        BulletObject *enm_bullet = E_bullet.at(j);
                        if (enm_bullet)
                        {
                            if (checkCollosion(enm_bullet->getBulletRect(), my_plane.getRect()))
                            {
                                Mix_PlayChannel(-1, exploMain_m, 0);

                                //animation when explore
                                for (int ex = 0; ex < 4; ex++)
                                    {
                                        Exp_plane.setFrame(ex);
                                        Exp_plane.show(my_plane.getPosX()-30 , my_plane.getPosY() -30);
                                        SDL_Delay(50);
                                        SDL_RenderPresent(gRenderer);
                                    }

                                //shown gameover img and handle ev
                                int GoverSelect = gameOver(score);
                                if (GoverSelect == 0) quit = true;
                                else if (GoverSelect == 1) {
                                        skipMenu = true;
                                        delete [] p_enemy;
                                        my_plane.resert_plane();

                                        goto GameStart;
                                    }
                                else if (GoverSelect == 2) {
                                    skipMenu = false;
                                    delete [] p_enemy;
                                    my_plane.resert_plane();
                                    goto GameStart;
                                }

                            }
                        }
                    }

                    //ceck collosion between my bullet and enemy
                    vector<BulletObject*> bullets = my_plane.getBulletList();
                    for (unsigned int id = 0; id < bullets.size(); id++) {
                        BulletObject* p_bullet = bullets[id];
                        if (p_bullet)
                        {
                            if (checkCollosion(p_bullet->getBulletRect(), n_enemy->getRect()))
                            {
                                Mix_PlayChannel(-1, explo_m, 0);
                                //explosion animation
                                for (int ex = 0; ex < 4; ex++)
                                    {
                                        exp_enemy.setFrame(ex);
                                        exp_enemy.show(n_enemy->getPosX()+5 , n_enemy->getPosY()+5, 1);

                                    }
                                SDL_RenderPresent(gRenderer);

                                my_plane.remove_bullet(id);
                                n_enemy->resertPosision();
                                score += 10;
                            }
                        }

                    }

                }

				//Update screen
				SDL_RenderPresent( gRenderer );
			}
		}

	//Free resources and close SDL
	close();

	return 0;
}

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( WINDOW_TITTLE.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else

			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

				 //Initialize SDL_mixer
				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					success = false;
				}
			}
		}
	}

    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
        {
            printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
            success = false;
        }

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;
    my_plane.LoadPlaneImg("myPlane1.png");
    if (!gBGTexture.loadFromFile("Bgr1.png")) success = false;

    gFont = TTF_OpenFont("arial.ttf", 28);
    if (gFont == NULL) {
        cout << "\n cant load font. Error: " << TTF_GetError();
        success = false;
    }

    //load explosion
    Exp_plane.setClip();
    Exp_plane.load_ExpImg("exp_main.png");

    exp_enemy.setClip();
    exp_enemy.load_ExpImg("exp_enemy.png");

    //init enemy
    for (int i = 0; i < Num_Enemy; i++)
    {
        EnemyObject *n_enemy = (p_enemy + i);
        n_enemy->loadEnemyImg("enemy1.png");
        n_enemy->setPosX(SCREEN_WIDTH + (i*200-100));
        n_enemy->setPosY(n_enemy->MakeRandValue());
        n_enemy->setVelX(-ENEMY_VEL1);

        BulletObject* enemy_bullet = new BulletObject;
        n_enemy->InitBullet(enemy_bullet);
        n_enemy->setVelX(ENEMY_VEL1+3);
    }

    //load sound effect
    laser_m = Mix_LoadWAV("Laser.wav");
    if (laser_m == NULL) {
        cout << "cant load Laser.wav . Error: " << Mix_GetError();
        success = false;
    }

    explo_m = Mix_LoadWAV("Explosion.wav");
    if (explo_m == NULL) {
        cout << "cant load Explosion.wav . Error: " << Mix_GetError();
        success = false;
    }

    exploMain_m = Mix_LoadWAV("ExplosionMain.wav");
    if (explo_m == NULL) {
        cout << "cant load ExplosionMain.wav . Error: " << Mix_GetError();
        success = false;
    }

	return success;
}

void close()
{

    delete [] p_enemy;
	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

    //free sound effect loaded
    Mix_FreeChunk(laser_m);
    Mix_FreeChunk(explo_m);
    Mix_FreeChunk(exploMain_m);
    laser_m = NULL;
    explo_m = NULL;
    exploMain_m = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	Mix_Quit();
}


bool checkCollosion(SDL_Rect a, SDL_Rect b)
{
    int leftA, rightA, topA, bottomA;
    int leftB, rightB, topB, bottomB;

    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y+a.h;

    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}


//I try to put some files in their file.cpp but its have some error when run so i put it here
bool LTexture::loadFromFile(string path)
{
    		    //Get rid of preexisting texture
            free();

            //The final texture
            SDL_Texture* newTexture = NULL;

            //Load image at specified path
            SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
            if( loadedSurface == NULL )
            {
                printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
            }
            else
            {
                //Color key image
                SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
                //Create texture from surface pixels
                newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
                if( newTexture == NULL )
                {
                    printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
                }
                else
                {
                    //Get image dimensions
                    mWidth = loadedSurface->w;
                    mHeight = loadedSurface->h;
                }

                //Get rid of old loaded surface
                SDL_FreeSurface( loadedSurface );
            }

            //Return success
            mTexture = newTexture;
            return mTexture != NULL;
}

bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor, TTF_Font* Font)
{
    //Get rid of preexisting texture
    free();

    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid( Font, textureText.c_str(), textColor );
    if( textSurface == NULL )
    {
        cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() ;
    }
    else
    {
        //Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );

        if( mTexture == NULL )
        {
            cout << "Unbale to create texture from renderer text! SDL_Error: " << SDL_GetError();
        }
        else
        {
            //Get image dimensions
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }

        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }

    //Return success
    return mTexture != NULL;
}

void LTexture::render(const int &x,const int &y , SDL_Rect* clip, const int &type)
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, mWidth, mHeight};

    //Set clip rendering dimensions
    if( clip != NULL)
    {
        if (type == 0)
        {
            renderQuad.w = clip->w;
            renderQuad.h = clip->h;
        }
        if (type == 1)
        {
            renderQuad.w = 100;
            renderQuad.h = 100;
        }
    }

    //Render to screen
    SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad);
}

void Object::render()
		{
		    SDL_Rect RenderQuad;
            RenderQuad.x = mPosX;
            RenderQuad.y = mPosY;
            RenderQuad.w = imgLoadedl.getWidth();
            RenderQuad.h = imgLoadedl.getHeight();
            SDL_RenderCopy(gRenderer, imgLoadedl.getTexture(), NULL, &RenderQuad);
		}

void MainObj::HandleInput(SDL_Event e)
    {
        //If a key was pressed
            if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
            {
                //Adjust the velocity
                switch( e.key.keysym.sym )
                {
                    case SDLK_UP: Plane.setVelY(Plane.getVelY() - OBJECT_VEL); break;
                    case SDLK_DOWN: Plane.setVelY(Plane.getVelY() + OBJECT_VEL); break;
                    case SDLK_LEFT: Plane.setVelX(Plane.getVelX() - OBJECT_VEL); break;
                    case SDLK_RIGHT: Plane.setVelX(Plane.getVelX() + OBJECT_VEL); break;
                    case SDLK_SPACE:
                            {
                                Mix_PlayChannel(-1, laser_m, 0);

                                BulletObject *newBullet = new BulletObject();
                                newBullet->setType(1);
                                newBullet->Set_isMove(true);
                                newBullet->setBulletPosX(Plane.getPosX());
                                newBullet->setBulletPosY(Plane.getPosY() + Plane.getHeight()/2);

                                bullet_list.push_back(newBullet);
                            }
                            break;
                }
            }
            //If a key was released
            else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
            {
                //Adjust the velocity
                switch( e.key.keysym.sym )
                {
                    case SDLK_UP: Plane.setVelY(Plane.getVelY() + OBJECT_VEL); break;
                    case SDLK_DOWN: Plane.setVelY(Plane.getVelY() - OBJECT_VEL); break;
                    case SDLK_LEFT: Plane.setVelX(Plane.getVelX() + OBJECT_VEL); break;
                    case SDLK_RIGHT: Plane.setVelX(Plane.getVelX() - OBJECT_VEL); break;
                }
            }
    }

//void LTexture::render_Enemy_Exp(const int &x, const int &y, )
