#include <stdio.h>
#include <time.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define WIDTH 800
#define HEIGHT 600
#define IMG_PATH "res/timo.png"

int main (int argc, char *argv[]) {

	// variable declarations
	SDL_Window *win = NULL;
	SDL_Renderer *renderer = NULL;
	SDL_Texture *img = NULL;
			  // Initialize SDL.
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return 1;

	// create the window and renderer
	// note that the renderer is accelerated
	win = SDL_CreateWindow("FUCKING BEES", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	// load our image
	img = IMG_LoadTexture(renderer, IMG_PATH);

	int w, h; // texture width & height
	SDL_QueryTexture(img, NULL, NULL, &w, &h);

	int d = 1;
	SDL_Rect texr;
	int mx, my;

	// main loop
	while (1) {

		// event handling
		SDL_Event e;
		if ( SDL_PollEvent(&e) ) {
			if (e.type == SDL_QUIT)
				break;
			else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)
				break;
		} 

		SDL_RenderClear(renderer);

		SDL_GetMouseState(&mx, &my);

		d = mx;

		int maxcount = d ? WIDTH / d + 1 : 0;
		
		for (int xi = 0; xi < maxcount; xi++) {
			for (int yi = 0; yi < maxcount; yi++) {
				texr = (SDL_Rect) {xi*d, yi*d, d, d};
				SDL_RenderCopy(renderer, img, NULL, &texr);
			}
		}

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyTexture(img);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);

	return 0;
}