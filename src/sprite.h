/*
 * Sprite loading/drawing functions
 * 2025 Aethari
 */

#ifndef SPRITE_H
#define SPRITE_H

int sprite_get_pix(int sheet, int x, int y);
int sprite_get_sprite(int *sprite, int sheet, int index);

void sprite_draw(int sheet, int index);

void sprite_init(sds cwd);

#endif
