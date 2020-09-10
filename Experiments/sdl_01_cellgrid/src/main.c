#include <stdio.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int VSYNC_ENABLED = 1;

#define TW 6 // grid tile width
#define GRID_W 100
#define GRID_H 80

int grid[GRID_W][GRID_H] = {0};
unsigned char gridPixels[GRID_W * TW * GRID_H * TW * 4] = {0};

int main() {

	// init SDL
	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);
	SDL_Window* win = SDL_CreateWindow(
		"Cell grid", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		GRID_W * TW, GRID_H * TW, 0
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

	// specific
	SDL_Texture* gridTexture = SDL_CreateTexture(
		rend, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
		GRID_W * TW, GRID_H * TW
	);

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
			case SDL_KEYUP: switch (e.key.keysym.sym) {
				case SDLK_ESCAPE: active = 0; break;
			}
		}

		// prepare
		SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
		SDL_RenderClear(rend);
		SDL_GetMouseState(&mx, &my);

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

		// set grid pixels


		// render texture
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