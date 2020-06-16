#include <stdio.h>
#include <stdlib.h>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#define GLEW_STATIC
#include <GL/glew.h>

void sdlExit(const char* msg) {
	printf("%s: %s\n", msg, SDL_GetError());
	SDL_Quit();
	exit(1);
}

void sdlCheckErr(int line) {
	const char* e = SDL_GetError();
	if (*e != '\0') {
		printf("[line %i] SDL Error: %s\n", line, e);
		SDL_ClearError();
	}
}
#define SDL_CHECK() sdlCheckErr(__LINE__)

int main() {

	SDL_Window* win;
	SDL_GLContext ctx;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) sdlExit("init err");

	// gl 3.3
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	win = SDL_CreateWindow("sdl2 test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 512, 512, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	if (!win) sdlExit("win err");
	SDL_CHECK();

	ctx = SDL_GL_CreateContext(win);
	SDL_CHECK();

	SDL_GL_SetSwapInterval(1); // vsync

	// after gl ctx, init glew
	if (glewInit() != GLEW_OK) {
		sdlExit("Glew init err");
	}

	glClearColor(1, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapWindow(win);
	SDL_Delay(2000);

	glClearColor(0, 0, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapWindow(win);
	SDL_Delay(2000);

	SDL_GL_DeleteContext(ctx);
	SDL_DestroyWindow(win);
	SDL_Quit();

	return 0;
}