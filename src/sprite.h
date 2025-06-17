/*
 * Sprite loading/drawing functions
 * 2025 Aethari
 */

#ifndef SPRITE_H
#define SPRITE_H

/// Retrieves the color of a pixel at the specified
/// coordinates on the specified spritesheet.
///
/// Parameters:
/// - sheet: The index of the spritesheet to use
/// - x, y: The coordinates of the pixel whose color will be gotten
///
/// Returns:
/// A char representing the color index of the pixel
/// at the given coordinates.
char sprite_get_pix(int sheet, int x, int y);

/// Draws a sprite from the spritesheet on the screen.
///
/// Parameters:
/// - sheet: The index of the spritesheet to use
/// - index: The index of the sprite
/// - x, y: The coordinates to draw the sprite at (top left corner)
void sprite_draw(int sheet, int index, int x, int y);

/// Opens the spritesheets provided in the cart.s16 file
/// and reads the data into several internal arrays.
/// The header than references these arrays later in
/// sprite_get_pix() and sprite_draw().
///
/// Parameters:
/// - cwd: An sds string representing the directory where Sun16 was started from
void sprite_init(sds cwd);

#endif
