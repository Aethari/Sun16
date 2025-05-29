/*
 * "Cartridge" data management
 * 2025 Aethari
 */

#ifndef CART_H
#define CART_H

// == Getters ==================================================
sds cart_get_title();

// == Setters ==================================================
void cart_set_title(sds new_title);

// == Other functions ==========================================

/// Creates a Lua instance and loads data from a
/// cart.s16 file located in the working directory.
///
/// Parameters:
/// - cwd: An sds string representing the directory where Sun16 was started from
void cart_init(sds cwd);

#endif
