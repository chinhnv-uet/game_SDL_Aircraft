#ifndef LTEXTURE_H_INCLUDED
#define LTEXTURE_H_INCLUDED

#include "common.h"

using namespace std;

class LTexture
{
	public:
		//Initializes variables
		LTexture();

		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool loadFromFile( std::string path );

		bool loadFromRenderedText( std::string textureText, SDL_Color textColor = BLACK, TTF_Font *font = gFont);


		//Deallocates texture
		void free();

		//Renders texture at given point
		void render(const int &x, const int &y , SDL_Rect* clip = NULL, const int &TYPE = 0); //type use to ser explosion of enemy plane

		//Gets image dimensions
		int getWidth() {return mWidth;}
		int getHeight() {return mHeight;}
        SDL_Texture* getTexture() { return mTexture;}
	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;
};


#endif // LTEXTURE_H_INCLUDED
