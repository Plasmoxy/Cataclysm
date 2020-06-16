
#include <stdio.h>
#include <stdlib.h>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		printf("sdl init error");
		return 1;
	}

	SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);

	if (win == NULL){
		printf("create window error");
		SDL_Quit();
		return 1;
	}

	while (1) {
		SDL_Delay(1000);
	}
}