/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <vector>

#include "atom.h"
#include "fonts.h"

//Screen dimension constants
const int SCREEN_WIDTH = 1920 / 2;
const int SCREEN_HEIGHT = 1080 / 2;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image
SDL_Surface* loadSurface( std::string path );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
	
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

SDL_Renderer* renderer = NULL;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL ) {
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			return false;
		}
		//Initialize PNG loading
		int imgFlags = IMG_INIT_PNG;
		if( !( IMG_Init( imgFlags ) & imgFlags ) )
		{
			printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
			return false;
		}
		//Get window surface
		gScreenSurface = SDL_GetWindowSurface( gWindow );

		renderer = SDL_GetRenderer(gWindow);
		if (renderer == NULL){
			printf("Couldn't get renderer from main window. SDL Error: %s\n", SDL_GetError() );
			return false;
		}

		// Initalize fonts
		if(TTF_Init() == -1) {
			printf(" SDL_TTF failed to initalize. SDL_TTF error: %s\n", TTF_GetError());
			return false;
		}

		Fonts::init();
	}

	return true;
}

SDL_Surface* loadMedia(std::string path)
{
	//Loading success flag
	bool success = true;

	//Load PNG surface
	SDL_Surface* gPNGSurface = loadSurface( path );
	if( gPNGSurface == NULL )
	{
		printf( "Failed to load PNG image!\n" );
	}

	return gPNGSurface;
}

void freeImage(SDL_Surface* surface){
	SDL_FreeSurface( surface );
}

void close()
{
	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Surface* loadSurface( std::string path )
{
	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, 0 );
		if( optimizedSurface == NULL )
		{
			printf( "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return optimizedSurface;
}

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
		close();
		return 1;
	}
	//Load media
	SDL_Surface* pineapple = loadMedia("/home/jeff/Downloads/pineapple.png");
	SDL_Texture* pineapple_texture = SDL_CreateTextureFromSurface(renderer, pineapple);
	
	// Create atoms
	std::vector<atom> atoms = std::vector<atom>();
	SDL_Color hydrogenColor = {0, 0, 255, 255};
	SDL_Color oxygenColor = {255, 0, 0, 255};
	atoms.push_back(atom(hydrogenColor, 400, 200, 75, "H"));
	atoms.push_back(atom(hydrogenColor, 100, 200, 75, "H"));
	atoms.push_back(atom(oxygenColor, 200, 200, 150, "O"));

	if( pineapple == NULL )
	{
		printf( "Failed to load media!\n" );
		close();
		return 2;
	}

	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;

	Uint32 lastFrameTime = 0;
	Uint32 delta = 0;
	//While application is running
	while( !quit )
	{
		lastFrameTime = SDL_GetTicks();
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}
		}

		// Update
		for (atom atom : atoms){
			atom.update(delta);
		}

		// Render
		SDL_Rect srcrect;
		SDL_Rect dstrect;

		SDL_Point size;
		SDL_QueryTexture(pineapple_texture, NULL, NULL, &size.x, &size.y);

		srcrect.x = 0;
		srcrect.y = 0;
		srcrect.w = 256;
		srcrect.h = 256;
		dstrect.x = SCREEN_WIDTH/2 - size.x/4;
		dstrect.y = SCREEN_HEIGHT/2 - size.y/4;
		dstrect.w = SCREEN_WIDTH/2;
		dstrect.h = SCREEN_HEIGHT/2;

		// Clear window
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
		SDL_RenderClear(renderer);

		// Draw everything
		SDL_RenderCopy(renderer, pineapple_texture, &srcrect, &dstrect);
		for (atom atom : atoms){
			atom.draw(renderer);
		}

		// Flip the buffers or whatever
		SDL_RenderPresent(renderer);

		delta = SDL_GetTicks() - lastFrameTime;
		// Wait a little bit
		SDL_Delay(1/60.0f * 1000 - delta);
	}
	freeImage(pineapple);
	//Free resources and close SDL
	close();

	return 0;
}