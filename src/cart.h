/*
 * "Cartridge" data management
 * 2025 Aethari
 */

#ifndef CART_H
#define CART_H

// == Getters ==================================================
sds cart_get_title();

/// Because these functions all work with arrays, the
/// index of the spritesheet is used as opposed to the
/// whole array.
/// IMPORTANT: these functions do not deal with actual
/// 		   DATA - they just return the path where
/// 		   the data is stored
///
/// Parameters:
/// - i: The index of the spritesheet to be retrieved
sds cart_get_spritesheet(int i);
sds cart_get_tilemap(int i);
sds cart_get_sound(int i);
sds cart_get_music(int i);

// == Other functions ==========================================

/// Creates a Lua instance and loads data from a
/// cart.s16 file located in the working directory.
///
/// Parameters:
/// - cwd: An sds string representing the directory where Sun16 was started from
void cart_init(sds cwd);

/// Frees any loose memory allocated by this 
/// header. Recommended to be called directly before
/// a program quits.
void cart_free();

#endif
