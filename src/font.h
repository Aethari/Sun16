/*
 * Sun16's font
 * 2025 Aethari
 */

#ifndef FONT_H
#define FONT_H

/// Gets the data for a given character.
///
/// Returns:
/// A pointer to an integer array representing
/// the character's bits (on and off).
int *font_get_data(char chr);

#endif
