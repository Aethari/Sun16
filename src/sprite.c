/*
 * Sprite loading/drawing functions
 * See sprite.h for documentation
 * 2025 Aethari
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include <SDL3/SDL.h>

#include <sds.h>

#include "cart.h"
#include "render.h"

// == Local variables ==========================================
typedef struct {
	int index;
	sds data;
} Spritesheet;

Spritesheet sheets[16];

// == Color helper functions ====================================
Color index_to_color(char index) {
	switch(index) {
		case '1':
			return BLACK;
		case '2':
			return WHITE;
		case '3':
			return GRAY;
		case '4':
			return RED;
		case '5':
			return ORANGE;
		case '6':
			return YELLOW;
		case '7':
			return GREEN;
		case '8':
			return BLUE;
		case '9':
			return PURPLE;
		case 'a':
			return BROWN;
		case 'b':
			return DARK_GRAY;
		case 'c':
			return DARK_RED;
		case 'd':
			return DARK_YELLOW;
		case 'e':
			return DARK_GREEN;
		case 'f':
			return DARK_BLUE;
		case 'g':
			return DARK_PURPLE;
		default:
			return BLACK;
	}
}

// == Functions =================================================
char sprite_get_pix(int sheet, int x, int y) {
	if(sheet > 0 && sheet <= 16) {
		sheet--;
	} else {
		printf("Error (sprite.c): Spritesheet index cannot be 0, negative, or higher than 16 (%d given). Make sure you are using proper numbers when accessing spritesheets.\n", sheet);
		exit(1);
	}

	if(sheets[sheet].data != NULL) {
		// 257 accounts for newlines; 256 was giving incorrect
		// numbers
		int start = y * 257 + x;

		if(start >= 65536 || start < 0) {
			printf("Error (sprite.c): Attempt to access out of bounds pixel (%d, %d).\n", x, y);
			exit(1);
		}

		return sheets[sheet].data[start];
	} else {
		return ' ';
	}
}

void sprite_draw(int sheet, int index, int x, int y) {
	if(sheet > 0 && sheet < 16) {
		sheet--;
	} else {
		printf("Error (sprite.c): Spritesheet index cannot be 0, negative, or higher than 16 (%d given). Make sure you are using proper numbers when accessing spritesheets.\n", sheet);
		exit(1);
	}

	if(sheets[sheet].data != NULL) {
		int sx = 0, sy = 0;

		while(index >= 16) {
			index -= 16;
			sy += 16;
		}
		sx = index*16;

		for(int py = sy; py < sy+16; py++) {
			for(int px = sx; px < sx+16; px++) {
				// sheet+1 because sprite_get_pix() automatically subtracts
				// 1 again to get the correct index
				char pix = sprite_get_pix(sheet+1, px, py);

				Color col = index_to_color(pix);
				render_pix(x + (px-sx), y + (py-sy), col);
			}
		}
	}
}

void sprite_init(sds cwd) {
	for(int i = 0; i < 16; i++) {
		sds stored_path = cart_get_spritesheet(i);

		if(stored_path != NULL) {
			sds sheet_path = sdscatfmt(sdsdup(cwd), "/%s", stored_path);

			FILE *ss = fopen(sheet_path, "rb");
			if(ss == NULL) {
				printf("Error (sprite.c): Could not open file \"%s\" (spritesheet %d).\n", sheet_path, i+1);
				exit(1);
			}

			fseek(ss, 0, SEEK_END);
			long len = ftell(ss);
			fseek(ss, 0, SEEK_SET);

			sds buff = sdsnewlen(NULL, len);

			size_t bytes = fread(buff, 1, len, ss);

			if(bytes != (size_t)len) {
				printf("Error (sprite.c): Failed to read spritesheet data.\n");
				exit(1);
			}

			fclose(ss);

			sheets[i].data = sdsdup(buff);
			sheets[i].index = i;

			sdsfree(buff);
			sdsfree(sheet_path);
		}
	}

	sdsfree(cwd);
}
