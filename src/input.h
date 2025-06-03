/*
 * Input handling for Sun16
 * 2025 Aethari
 */

#ifndef INPUT_H
#define INPUT_H

/// Every button that Sun16 supports
typedef enum {
	// = 1 to make enum start at 1, not 0
	LEFT = 1,
	RIGHT,
	UP,
	DOWN,
	A,
	B,
	X,
	Y
} Buttons;

// == Functions ================================================
/// Checks if the specified button is currently
/// pressed.
///
/// Button indicies:
/// +-------+--------+
/// | Index | Button |
/// +-------+--------+
/// | 1     | left   |
/// | 2     | right  |
/// | 3     | up     |
/// | 4     | down   |
/// +-------+--------+
/// | 5     | a      |
/// | 6     | b      |
/// | 7     | x      |
/// | 8     | y      |
/// +-------+--------+
///
/// Returns:
/// True if the specified button is pressed, false if
/// not.
bool input_button_pressed(Buttons btn);

/// Handles input events, both for SDL (window quits,
/// resizes, etc.) and states for SunUI's buttons.
///
/// Returns:
/// A boolean value representing whether Sun16 should
/// keep running or not. If false, closes the window
/// and stops the process.
bool input_update();

#endif
