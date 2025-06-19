/*
 * Tilemap loading/drawing functions
 * 2025 Aethari
 */

#ifndef TILEMAP_H
#define TILEMAP_H

char tilemap_get_tile(int map, int x, int y);
void tilemap_draw(int map, int sheet, int sx, int sy, int x, int y);

void tilemap_init(sds cwd);

#endif
