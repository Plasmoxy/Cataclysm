#include <stdio.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define TW 6
#define GRID_W 100
#define GRID_H 80

int fpsframe = 0;

int main() {

	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);
	SDL_Window* win = SDL_CreateWindow(
		"harvard_tutorial", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		GRID_W * TW, GRID_H * TW, 0
	);
	SDL_Renderer* rend = SDL_CreateRenderer(
		win, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC
	);

	SDL_Rect rect = {0, 0, 0, 0};
	SDL_Event e;
	int active = 1;
	int mx, my;
	int winw, winh;
	while (active) {
		int starttime = SDL_GetTicks();

		// events
		while (SDL_PollEvent(&e)) switch (e.type) {
			case SDL_QUIT: active = 0; break;
			case SDL_KEYUP: switch (e.key.keysym.sym) {
				case SDLK_ESCAPE: active = 0; break;
			}
		}

		SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
		SDL_RenderClear(rend);
		SDL_GetMouseState(&mx, &my);

		// render grid
		

		// control rect
		SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);
		rect = (SDL_Rect) { mx, my, 50, 50 };
		SDL_RenderFillRect(rend, &rect);

		SDL_RenderPresent(rend);
		if (fpsframe++ == 10) { // show fps every 10 frames
			printf("FPS: %d\n", 1000 / (SDL_GetTicks() - starttime));
			fpsframe = 0;
		}
	}

	SDL_Quit();
	return 0;
}