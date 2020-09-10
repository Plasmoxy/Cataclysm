#include <stdio.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main() {

	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);
	SDL_Window* win = SDL_CreateWindow(
		"harvard_tutorial", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		600, 400, 0
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
		while (SDL_PollEvent(&e)) switch (e.type) {
			case SDL_QUIT: active = 0; break;
			case SDL_KEYUP: switch (e.key.keysym.sym) {
				case SDLK_ESCAPE: active = 0; break;
			}
		}

		SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
		SDL_RenderClear(rend);
		SDL_GetMouseState(&mx, &my);
		SDL_GetWindowSize(win, &winw, &winh);

		SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);
		
		SDL_Rect rect = {0, 0, 50, 50};
		SDL_RenderFillRect(rend, &rect);

		SDL_RenderPresent(rend);
	}

	SDL_Quit();
	return 0;
}