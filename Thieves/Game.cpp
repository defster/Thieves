#define VC_EXTRALEAN
#define WIN32_LEAN_AND_MEAN
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"") 

// Added to git

#include <iostream>
#include <stdio.h>
#include <SDL.h>
#include "System.h"
#include "Map.h"
#include "Unit.h"

using namespace std;

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 760;

const int worldSize = 512;
const int tileSize = 16;
int unitxtile = 4;
int unitytile = 24;
int posx = 0;
int posy = 0;

int map[worldSize * worldSize];

Unit units[6];

bool init();
void close();

LWindow gWindow;
Map gMap;

SDL_Renderer *gRenderer = nullptr;


int main(int argc, char *argv[])
{
	if (!init())
	{
		printf("Failed to initialize.\n");
		return -1;
	}

	// TILE RELATED

	for (int i = 0; i < 6; i++)
		units[i].createUnit("na_mod", 1, 1, 1);

	printf("name: %s\n", units[0].name);
	//units[0] = new Unit();

	//printf("%i", units[0].job);

	// Takes map as parameter and modifies it directly through pointer
	gMap.createMap(map, worldSize);

	posx = (unitxtile * tileSize) + (tileSize / 2);
	posy = (unitytile * tileSize) + (tileSize / 2);

	SDL_Event e;
	bool quit = false;
	while (!quit)
	{
		// Get mouse pointer coordinates.
		int mx, my;
		SDL_GetMouseState(&mx, &my);
		
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT) { quit = true; }
			if (e.type == SDL_MOUSEBUTTONDOWN) { printf("x: %i, y: %i\n", mx, my); }

			//gWindow.handleEvent(e);
		}
		
		
		//Only draw when not minimized
		if (!gWindow.isMinimized())
		{
			// draw
		}

		const Uint8 *keys = SDL_GetKeyboardState(NULL);
		if (keys[SDL_SCANCODE_LEFT])
		{ 
			printf("LEFT was pressed.\n");
		}
		if (keys[SDL_SCANCODE_RIGHT])
		{
			printf("RIGHT was pressed.\n");
		}


		// Clear screen
		SDL_SetRenderDrawColor(gRenderer, 0xDD, 0xDD, 0xDD, 0xFF);
		SDL_RenderClear(gRenderer);

		// TILE-RENDERING TEST

		int maxx = ((SCREEN_WIDTH / tileSize) / 2) + 2;
		int maxy = ((SCREEN_HEIGHT / tileSize) / 2) + 2;

		posx+=2;
		posy++;

		unitxtile = posx / tileSize;
		unitytile = posy / tileSize;

		int startx = unitxtile - maxx;
		int starty = unitytile - maxy;
		int endx = unitxtile + maxx;
		int endy = unitytile + maxy;

		if (starty < 0) starty = 0;
		if (startx < 0) startx = 0;
		if (endy >= worldSize) endy = worldSize;
		if (endx >= worldSize) endx = worldSize;

		int midx = SCREEN_WIDTH / 2;
		int midy = SCREEN_HEIGHT / 2;

		int drawx = 0;
		int drawy = 0;
		int index = 0;

		//SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_Rect fillRect;
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
		for (int y = starty; y < endy; y++)
		{
			for (int x = startx; x < endx; x++)
			{
				index = x + (y * worldSize);
				drawx = (x * tileSize) + midx - posx;
				drawy = (y * tileSize) + midy - posy;
				if (map[index] == 1)
				{
					fillRect = { drawx, drawy, tileSize, tileSize };
					SDL_RenderFillRect(gRenderer, &fillRect);
				}
				/*
				if (map[index] == 2)
				{
					SDL_SetRenderDrawColor(gRenderer, 0x99, 0x99, 0x99, 0xFF);
					fillRect = { drawx, drawy, tileSize, tileSize };
					SDL_RenderFillRect(gRenderer, &fillRect);
				}
				*/
			}
		}

		SDL_SetRenderDrawColor(gRenderer, 0x99, 0x99, 0x99, 0xFF);
		for (int y = starty; y < endy; y++)
		{
			for (int x = startx; x < endx; x++)
			{
				index = x + (y * worldSize);
				drawx = (x * tileSize) + midx - posx;
				drawy = (y * tileSize) + midy - posy;
				/*
				if (map[index] == 1)
				{
					SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
					fillRect = { drawx, drawy, tileSize, tileSize };
					SDL_RenderFillRect(gRenderer, &fillRect);
				}
				*/
				if (map[index] == 2)
				{
					fillRect = { drawx, drawy, tileSize, tileSize };
					SDL_RenderFillRect(gRenderer, &fillRect);
				}

			}
		}

		/*
		//Render red filled quad
		SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderFillRect(gRenderer, &fillRect);

		//Draw blue horizontal line
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
		SDL_RenderDrawLine(gRenderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);

		//Draw vertical line of yellow dots
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0x00, 0xFF);
		for (int i = 0; i < SCREEN_HEIGHT; i += 4)
		{
			SDL_RenderDrawPoint(gRenderer, SCREEN_WIDTH / 2, i);
		}
		*/
		//Update screen
		SDL_RenderPresent(gRenderer);
	}

	close();

	return 0;
}

bool init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	else
	{
		//Create window
		if (!gWindow.init(SCREEN_WIDTH, SCREEN_HEIGHT))
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			return false;
		}
		else
		{
			//Create renderer for window
			gRenderer = gWindow.createRenderer();
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				return false;
			}
		}
	}

	return true;
}

void close()
{
	SDL_DestroyRenderer(gRenderer);
	gWindow.free();

	gRenderer = nullptr;

	//Quit SDL subsystems
	SDL_Quit();
}