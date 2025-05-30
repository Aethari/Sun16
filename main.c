/*
 * Sun16 entry point/core loops
 * 2025 Aethari
 */

#include <stdio.h>
#include <stdlib.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <sds.h>

#include "cart.h"
#include "render.h"

#ifdef __unix__
	#include <unistd.h>
#elif _WIN32
	#include <direct.h>
	#define getcwd _getcwd
#endif

#define PATH_MAX_LEN 2048

int main(int argc, char *argv[]) {
	// get cwd
	char *buff = (char *)malloc(PATH_MAX_LEN);
	if(buff == NULL) {
		printf("Error (main.c): Memory allocation failed for cwd buffer\n");
		return 1;
	}

	if(getcwd(buff, PATH_MAX_LEN) == NULL) {
		printf("Error (main.c): getcwd failed\n");
		return 1;
	}
	
	sds cwd = sdsnew(buff);
	free(buff);

	cart_init(sdsdup(cwd));

	SDL_Window *window;
	bool running = true;

	SDL_Init(
		SDL_INIT_AUDIO |
		SDL_INIT_VIDEO |
		SDL_INIT_JOYSTICK |
		SDL_INIT_EVENTS
	);

	window = SDL_CreateWindow(
		cart_get_title(),
		1024,
		512,
		SDL_WINDOW_OPENGL |
		SDL_WINDOW_RESIZABLE
	);
	render_init(window);

	while(running) {
		SDL_Event event;

		render_draw();

		while(SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_EVENT_QUIT:
					running = false;
					break;
				case SDL_EVENT_WINDOW_RESIZED:
					render_scale();
					break;
			}
		}
	}

	sdsfree(cwd);
	cart_free();
	return 0;
}
