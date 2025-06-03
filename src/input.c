/*
 * Input handling for Sun16
 * See input.h for documentation
 * 2025 Aethari
 */

#include <stdbool.h>

#include <SDL3/SDL.h>

#include "render.h"
#include "input.h"

// == Local variables ==========================================
/// State tracker for each of Sun16's buttons
typedef struct {
	bool left;
	bool right;
	bool up;
	bool down;
	bool a;
	bool b;
	bool x;
	bool y;
} ButtonState;

ButtonState buttons = {0};

// == Fuctions =================================================
bool input_button_pressed(Buttons btn) {
	switch(btn) {
		case LEFT:
			return buttons.left;
		case RIGHT:
			return buttons.right;
		case UP:
			return buttons.up;
		case DOWN:
			return buttons.down;
		case A:
			return buttons.a;
		case B:
			return buttons.b;
		case X:
			return buttons.x;
		case Y:
			return buttons.y;
		default:
			return false;
	}
}

bool input_update() {
	SDL_Event event;

	while(SDL_PollEvent(&event)) {
		switch(event.type) {
			case SDL_EVENT_QUIT:
				return false;
				break;
			case SDL_EVENT_WINDOW_RESIZED:
				render_scale();
				break;
		}
	}

	const bool *keys = SDL_GetKeyboardState(NULL);

	// left
	if(
		keys[SDL_SCANCODE_LEFT] ||
		keys[SDL_SCANCODE_A]
	) {
		buttons.left = true;
	} else {
		buttons.left = false;
	}

	// right
	if(
		keys[SDL_SCANCODE_RIGHT] ||
		keys[SDL_SCANCODE_D]
	) {
		buttons.right = true;
	} else {
		buttons.right = false;
	}

	// up
	if(
		keys[SDL_SCANCODE_UP] ||
		keys[SDL_SCANCODE_W]
	) {
		buttons.up = true;
	} else {
		buttons.up = false;
	}

	// down
	if(
		keys[SDL_SCANCODE_DOWN] ||
		keys[SDL_SCANCODE_S]
	) {
		buttons.down = true;
	} else {
		buttons.down = false;
	}

	// A
	if(
		keys[SDL_SCANCODE_V] ||
		keys[SDL_SCANCODE_J]
	) {
		buttons.a = true;
	} else {
		buttons.a = true;
	}

	// B
	if(
		keys[SDL_SCANCODE_C] ||
		keys[SDL_SCANCODE_K]
	) {
		buttons.b = true;
	} else {
		buttons.b = false;
	}

	// X
	if(
		keys[SDL_SCANCODE_X] ||
		keys[SDL_SCANCODE_U]
	) {
		buttons.x = true;
	} else {
		buttons.x = false;
	}

	// Y
	if(
		keys[SDL_SCANCODE_Z] ||
		keys[SDL_SCANCODE_I]
	) {
		buttons.y = true;
	} else {
		buttons.y = false;
	}

	return true;
}
