/*
 * Sprite loading/drawing functions
 * See sprite.h for documentation
 * 2025 Aethari
 */

#include <stdio.h>
#include <stdlib.h>

#include <sds.h>

#include "cart.h"

// each spritesheet is a custom struct. the struct has values for
// index and data, data is a 1d array of integers.

// == Local variables ==========================================
typedef struct {
	int index;
	int data[];
} Spritesheet;

Spritesheet sheets[16];

// == Getters ==================================================
int sprite_get_pix(int sheet, int x, int y) {
}

int sprite_get_sprite(int *sprite, int sheet, int index) {
}

// == Other functions ==========================================
void sprite_init(sds cwd) {
	for(int i = 0; i < 16; i++) {
		sds stored_path = cart_get_spritesheet(i);
		if(stored_path != NULL) {
			// open the file at the path and read the data into
			// an array
			
			sds sheet_path = sdsdup(cwd);
			sheet_path = sdscat(sheet_path, "/");
			sheet_path = sdscat(sheet_path, stored_path);

			FILE *ss = fopen(sheet_path, "r");

			if(ss == NULL) {
				printf("Error (sprite.c): Could not open file \"%s\" (spritesheet %d)\n", sheet_path, i+1);
				exit(1);
			}
		}
	}
}
