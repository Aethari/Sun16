/*
 * Tilemap loading/drawing functions
 * See tilemap.h for documentation
 * 2025 Aethari
 */

#include <stdbool.h>

#include <SDL3/SDL.h>

#include <sds.h>

#include "cart.h"
#include "render.h"

// == Local variables ===========================================
typedef struct {
	int index;
	sds data;
} Tilemap;

Tilemap maps[16];

// == Functions =================================================
int tilemap_get_tile(int map, int x, int y) {
}

void tilemap_draw(int map, int sheet, int sx, int sy, int x, int y) {
}

void tilemap_init(sds cwd) {
	sdsfree(cwd);
}
