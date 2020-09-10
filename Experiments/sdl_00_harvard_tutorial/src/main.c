#include <stdio.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main() {

	if (SDL_Init(SDL_INIT_VIDEO)) {
		printf("Error: %s\n", SDL_GetError());
		return 1;
	}



	SDL_Quit();
	return 0;
}