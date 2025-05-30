**Disclaimer:** This project is under development. Information in this document
may not reflect the final program, or the program currently in the repo.

# Sun16: A fantasy console(ish) framework
Welcome to Sun16, a game framework designed to limit developers without being
too restrictive.  

Sun16 aims to provide a retro-feeling environment for developers, while still
allowing them to create modern games and apps. While there are some restrictions,
Sun16 is far less limiting then consoles like the legendary PICO-8, especially
when it comes to code size.

## Features
- Small
- Fast
- Runs Lua
	- No compilation required
	- Easy for beginners
	- Memory is handled by Lua's VM
- Portable
	- Sun16 is designed to work anywhere SDL can be ran, as long as you keep
	  the files that it requires alongside the executable
	- Some platforms may need to be added to the [Makefile](Makefile) - there
	  is only support for Unix and Windows at the moment
- Limited, yet limitless
	- While Sun16 imposes a limit on the *sizes* of sprites, spritesheets, and
	  tilemaps, you can store and display up to 16 of each in your project

## Specs
| Component			| Specs						  |
|-------------------|-----------------------------|
| Screen size		| 256x128 px				  |
| Palette			| 16 colors					  |
| Sprite size		| 16x16						  |
| Sprite sheet		| 256x256					  |
| Tilemap			| 256x256					  |
| Audio				| 16 total tracks			  |
| Input				| joystick/arrows + 4 buttons |

## Building from source

### Adding platforms
At the moment, Sun16 only supports two platforms: Unix and Windows. This 
availability would not be a problem if Sun16 did not use stdin/out for file
access, but because it does, there is platform specific code.  

Luckily there is/will be very few places where Sun16 actually uses the
filesystem. If you want to add support for more platforms, simply update the
`#ifdef`/`#elif` directives with your platform in the following files:
- [main.c](main.c) - needs a definition for unix `getcwd()`
- [cart.c](src/cart.c) - needs a definition for unix `access()`

## License
Sun16 is licensed under the MIT license.  
See [LICENSE.txt](LICENSE.txt) for license info.
