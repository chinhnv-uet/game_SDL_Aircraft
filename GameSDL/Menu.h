#pragma once

#include "common.h"
#include "Ltexture.h"

//menu
static LTexture menuImg;
static LTexture MenuSelected[4];
static TTF_Font *menu_font = NULL;
static LTexture MenuText1, MenuText2;
static SDL_Rect rect[2];

//mouse position
static int xm, ym;

//game over
static LTexture gOver_img;
static TTF_Font *g_over_font = NULL;
static LTexture YourScore, gOverText1, gOverText2;
static LTexture gOverSelected[4];
static SDL_Rect g_over_rect[2];


bool checkMouseOnRect(const int &x,const int &y, SDL_Rect rct)
{
    if (x > rct.x && x < rct.x+rct.w && y > rct.y  && y < rct.y + rct.h) return true;
    return false;
}

void initMenu()
{
    menu_font = TTF_OpenFont("OCRAEXT.ttf", 50);

    MenuSelected[0].loadFromRenderedText("PLAY GAME", WHITE, menu_font);
    MenuSelected[1].loadFromRenderedText("PLAY GAME", RED, menu_font);

    MenuSelected[2].loadFromRenderedText("EXIT", WHITE, menu_font);
    MenuSelected[3].loadFromRenderedText("EXIT", RED, menu_font);

    rect[0].x = 0;
    rect[0].y = 340;
    rect[0].w = 278;
    rect[0].h = 34;

    rect[1].x = 0;
    rect[1].y = 414;
    rect[1].w = 100;
    rect[1].h = 26;
}

int showMenu()
{
    initMenu();
    if(!menuImg.loadFromFile("intro.png")) cout << "cant load image menu" << endl;
    else {
        SDL_Event menu_ev;
        MenuText1 = MenuSelected[0];
        MenuText2 = MenuSelected[2];

        bool isRuningMenu = 1;
        while(isRuningMenu)
        {
            while(SDL_PollEvent(&menu_ev) != 0)
            {
                switch(menu_ev.type)
                {
                    case SDL_QUIT: return 1; break;
                    case SDL_MOUSEMOTION:
                        {
                            //get posotion of mouse
                            xm = menu_ev.motion.x;
                            ym = menu_ev.motion.y;

                            if (checkMouseOnRect(xm, ym, rect[0])) MenuText1 = MenuSelected[1];
                            if (!checkMouseOnRect(xm, ym, rect[0])) MenuText1 = MenuSelected[0];

                            if (checkMouseOnRect(xm, ym, rect[1])) MenuText2 = MenuSelected[3];
                            if (!checkMouseOnRect(xm, ym, rect[1])) MenuText2 = MenuSelected[2];

                            break;
                        }
                    case SDL_MOUSEBUTTONDOWN:
                        {
                            xm = menu_ev.motion.x;
                            ym = menu_ev.motion.y;

                            if (checkMouseOnRect(xm, ym, rect[0])) return 0;
                            if (checkMouseOnRect(xm, ym, rect[1])) return 1;
                        }
                }

            }

            menuImg.render(0, 0);

            MenuText1.render(0, 330);
            MenuText2.render(0, 400);

            SDL_RenderPresent(gRenderer);
        }
    }
    return 1;
}

void initGameOver()
{
    g_over_font = TTF_OpenFont("AlphaFridgeMagnets.ttf", 40);

    gOverSelected[0].loadFromRenderedText("PLAY AGAIN", BLACK, g_over_font);
    gOverSelected[1].loadFromRenderedText("PLAY AGAIN", RED, g_over_font);

    gOverSelected[2].loadFromRenderedText("BACK TO MENU", BLACK, g_over_font);
    gOverSelected[3].loadFromRenderedText("BACK TO MENU", RED, g_over_font);

    g_over_rect[0].x = 308;
    g_over_rect[0].y = 491;
    g_over_rect[0].w = 268;
    g_over_rect[0].h = 57;

    g_over_rect[1].x = 622;
    g_over_rect[1].y = 490;
    g_over_rect[1].w = 294;
    g_over_rect[1].h = 54;
}

int gameOver(const int& score)
{
    initGameOver();
    if (!gOver_img.loadFromFile("GameOver.png")) cout << "cant load gameover image" << endl;
    else {
        SDL_Event gOver_ev;
        gOverText1 = gOverSelected[0];
        gOverText2 = gOverSelected[2];

        string ScoreGeted = "You get " ;
        ScoreGeted = ScoreGeted + to_string(score) + " score!";
        YourScore.loadFromRenderedText(ScoreGeted, BLACK, g_over_font);

        bool Runing_gOver = true;
        while (Runing_gOver)
        {
            while (SDL_PollEvent(&gOver_ev) != 0)
            {
                switch(gOver_ev.type)
                {
                    case SDL_QUIT: return 0;//close SDL_window
                    case SDL_MOUSEMOTION:
                        {
                            xm = gOver_ev.motion.x;
                            ym = gOver_ev.motion.y;

                            if (checkMouseOnRect(xm, ym, g_over_rect[0])) gOverText1 = gOverSelected[1];
                            if (!checkMouseOnRect(xm, ym, g_over_rect[0])) gOverText1 = gOverSelected[0];

                            if (checkMouseOnRect(xm, ym, g_over_rect[1])) gOverText2 = gOverSelected[3];
                            if (!checkMouseOnRect(xm, ym, g_over_rect[1])) gOverText2 = gOverSelected[2];

                            break;
                        }
                    case SDL_MOUSEBUTTONDOWN:
                        {
                            xm = gOver_ev.motion.x;
                            ym = gOver_ev.motion.y;

                            if (checkMouseOnRect(xm, ym, g_over_rect[0])) return 1;
                            if (checkMouseOnRect(xm, ym, g_over_rect[1])) return 2;
                        }
                }
            }

            gOver_img.render(300, 150);

            YourScore.render(440, 420);
            gOverText1.render(315, 500);
            gOverText2.render(635, 500);

            SDL_RenderPresent(gRenderer);
        }
    }
    return 0;
}
