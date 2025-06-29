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
#include "input.h"
#include "sprite.h"

#ifdef __unix__
	#include <unistd.h>
#elif _WIN32
	#include <direct.h>
	#define getcwd _getcwd
#endif

#define PATH_MAX_LEN 2048
#define VERSION "0.4.0 (alpha)"

int main(int argc, char *argv[]) {
	if(argc > 1) {
		if(strcmp(argv[1], "-v") == 0) {
			printf("Sun16 version %s\n", VERSION);
			printf("2025 Aethari\n");
			printf("https://github.com/Aethari/Sun16\n");
			exit(0);
		} else {
			printf("Error (main.c): Command line argument \"%s\" not recognized.\n", argv[1]);
			exit(1);
		}
	}

	printf("Sun16 version %s\n", VERSION);
	printf("2025 Aethari\n");
	printf("https://github.com/Aethari/Sun16\n");
	printf("====================================\n\n");

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

	// setup SDL
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

	// setup Sun16 (other than config)
	render_init(window);
	sprite_init(sdsdup(cwd));

	// core loop
	while(running) {
		render_draw();
		running = input_update();
	}

	sdsfree(cwd);
	cart_free();
	return 0;
}
