#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

using namespace std;

//to init window
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 700;
const std::string WINDOW_TITTLE = "AirCraft";

static const int BULLET_VEL = 11;
static const int OBJECT_VEL = 7;

static int ENEMY_VEL1 = 4;
static int ENEMY_VEL2 = 5;
static int ENEMY_VEL3 = 7;
static int ENEMY_VEL4 = 8;
static int ENEMY_VEL5 = 9;
static int Num_Enemy = 4;

static SDL_Renderer *gRenderer = NULL;
static SDL_Window *gWindow = NULL;

//init font and color to render text to screen
static TTF_Font *gFont = NULL;
static SDL_Color RED = {255, 0, 0};
static SDL_Color WHITE = {255, 255, 255};
static SDL_Color BLACK = {0, 0, 0};

//use to play again
static bool skipMenu = false;

//sound effect
static Mix_Chunk *laser_m = NULL;
static Mix_Chunk *explo_m = NULL;
static Mix_Chunk *exploMain_m = NULL;
