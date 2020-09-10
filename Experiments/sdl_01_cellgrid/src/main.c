#include <stdio.h>
#include <stdlib.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

const int VSYNC_ENABLED = 0;

#define TW 6 // grid tile width
#define GRID_W 100
#define GRID_H 80

#define GRID_PX_W (GRID_W*TW)
#define GRID_PX_H (GRID_H*TW)

#define GRID_PX_SIZE (GRID_PX_W * GRID_PX_H * 4) // gridPixels size in bytes

// grid with cell values [y][x]
int grid[GRID_H][GRID_W] = {{0}};

// grid pixels
const unsigned char emptyGridPixels[GRID_PX_SIZE] = {0};
unsigned char gridPixels[GRID_PX_SIZE] = {0};

unsigned char bluePixelRow[4*TW] = {0};

// renders grid pixels from grid 
void renderGridPixels() {
	/* 
	for( unsigned int i = 0; i < 100000; i++ )
	{
	const unsigned int x = rand() % (GRID_W * TW);
	const unsigned int y = rand() % (GRID_H * TW);

	const unsigned int offset = ( GRID_W * TW * 4 * y ) + x * 4;
	gridPixels[ offset + 0 ] = rand() % 256;        // b
	gridPixels[ offset + 1 ] = rand() % 256;        // g
	gridPixels[ offset + 2 ] = rand() % 256;        // r
	gridPixels[ offset + 3 ] = SDL_ALPHA_OPAQUE;    // a
	}
	*/
	/*
	single pixel = 4 channels * 1 byte = 4 chars
	pixel byte offset = (texWidth*4*y + 4*x) bytes

	// single pixel cpy at the start of texture :
	unsigned char redPix[4] = {0, 0, 255, 255};
	memcpy(&gridPixels[0], &redPix[0], 4);
	*/

	// cpy empty grid to grid pixels
	memcpy(gridPixels, emptyGridPixels, GRID_PX_SIZE);

	// if we find a non-black tile, then copy every pixel row of that tile into gridPixels buffer
	for (int y = 0; y < GRID_H; y++) {
		for (int x = 0; x < GRID_W; x++) {
			// draw pixels only if grid tile is not zero
			if (grid[y][x] > 0) {
				for (int row = 0; row < TW; row++) {
					// ===== rendering by coping pixel rows ====
					// calculate row start pixel position and
					// copy pixel row into that start according to xy formula above
					/*
					int pxY = y*TW + row;
					int pxX = x * TW;
					memcpy(&gridPixels[GRID_PX_W * 4 * pxY + 4 * pxX], bluePixelRow, 4*TW);
					*/

					// ======== alternative =======
					// -> fill in each pixel manually depending on grid value
					for (int col = 0; col < TW; col++) {
						int pxY = y*TW + row;
						int pxX = x*TW + col;

						unsigned char pixel[4] = {255, 200, 0, grid[y][x]};
						memcpy(&gridPixels[GRID_PX_W * 4 * pxY + 4 * pxX], pixel, 4);
					}
				}
			}
		}
	}
}

int main() {

	// init SDL
	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);
	SDL_Window* win = SDL_CreateWindow(
		"Cell grid", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		GRID_PX_W, GRID_PX_H, 0
	);
	SDL_Renderer* rend = SDL_CreateRenderer(
		win, -1,
		VSYNC_ENABLED ? SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC :
		SDL_RENDERER_ACCELERATED
	);

	// renderer info
	SDL_RendererInfo info;
	SDL_GetRendererInfo(rend, &info);
	printf("Renderer: %s\n", info.name);
	printf("Texture formats:\n");
	for (Uint32 i = 0; i < info.num_texture_formats; i++) {
		printf("  %s\n", SDL_GetPixelFormatName(info.texture_formats[i]));
	}

	// texture setup
	SDL_Texture* gridTexture = SDL_CreateTexture(
		rend, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
		GRID_W * TW, GRID_H * TW
	);
	SDL_SetTextureBlendMode(gridTexture, SDL_BLENDMODE_BLEND);

	// pixel rows for copying into pixel buffer as tiles
	const unsigned char pixel[4] = {255, 255,  0, 255};
	for (int i = 0; i < TW; i++) memcpy(&bluePixelRow[i*4], pixel, 4);

	// custom setup grid
	for (int gx = 0; gx < GRID_W; gx++) {
		for (int gy = 0; gy < GRID_H; gy++) {
			grid[gy][gx] = 127;
		}
	}

	// start render
	SDL_Rect rect = {0, 0, 0, 0};
	SDL_Event e;
	int active = 1;
	double fpsMs = 0;
	int mx, my;
	int winw, winh;
	while (active) {
		Uint64 startTime = SDL_GetPerformanceCounter();

		// events
		while (SDL_PollEvent(&e)) switch (e.type) {
			case SDL_QUIT: active = 0; break;
			case SDL_KEYUP:
				switch (e.key.keysym.sym) {
					case SDLK_ESCAPE: active = 0; break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				SDL_GetMouseState(&mx, &my);

				int* clickedCell = &grid[(size_t) GRID_H * my / GRID_PX_H][(size_t) GRID_W * mx / GRID_PX_W];
				
				*clickedCell += 20;

				break;
		}

		// prepare
		SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
		SDL_RenderClear(rend);
		SDL_GetMouseState(&mx, &my);

		// weird stuff
		for (int i = 0; i < 2000; i++) {
			int* cell = &grid[rand() % GRID_H][rand() % GRID_W];
			int d = 20 - (rand() % 40);
			
			// byte ceiling and flooring
			if (*cell + d > 255) *cell = 255;
			else if (*cell + d < 0) *cell = 0;
			else *cell += d;
		}
		
		// render grid pixels, copy to texture, render texture
		renderGridPixels();
		SDL_UpdateTexture(gridTexture, NULL, gridPixels, GRID_W * TW * 4);
		SDL_RenderCopy(rend, gridTexture, NULL, NULL);

		// finish
		SDL_RenderPresent(rend);

		int framePerf = SDL_GetPerformanceCounter() - startTime;
		fpsMs += framePerf / (float) 10000;
		if (fpsMs > 500) { // show fps
			printf("FPS = %d\n", 10000000L / framePerf);
			fpsMs = 0;
		}
	}

	SDL_Quit();
	return 0;
}

