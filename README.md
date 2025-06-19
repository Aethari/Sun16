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

### Potential features
Some features that may or may not be added later, but are cool ideas anyway:
- Custom fonts (and font sizes)

## Specs
| Component			| Specs						  |
|-------------------|-----------------------------|
| Screen size		| 256x128 px				  |
| Palette			| 16 colors					  |
| Sprite size		| 16x16						  |
| Sprite sheet size | 256x256					  |
| Tilemap			| 256x256 tiles               |
| Sfx               | 32 sounds                   |
| Music             | 32 total tracks             |
| Input				| joystick/arrows + 4 buttons |

## Roadmap
| Task            | Completed? | Target version |
|-----------------|------------|----------------|
| Cart metadata   | Yes        | 0.1.0 (alpha)  |
| Graphics        | Yes        | 0.1.0 (alpha)  |
| Input           | Yes        | 0.2.0 (alpha)  |
| Text Graphics   | Yes        | 0.3.0 (alpha)  |
| Sprites         | Yes        | 0.4.0 (alpha)  |
| Tilemaps        | No         | 0.4.0 (alpha)  |
| Sounds/music    | No         | 0.5.0 (alpha)  |
| Lua interface   | No         | 0.1.0          |
| Binary exports  | No         | 0.2.0          |
| Bugfixes/polish | No         | 1.0.0          |

In addition to these features that will be implemented in Sun16 itself, I plan
on making two standalone editors: SunSprite (for Sun16 sprite editing) and 
SunTile (for Sun16 tilemap editing). These may have a working version by the
time Sun16 version 0.1.0 releases, or they may not depending on how motivated
I am.  

Here are links to each of the editors (or where they will eventually be):
- [SunSprite](https://github.com/Aethari/SunSprite)
- [SunTile](https://github.com/Aethari/SunTile)

#### Planned features
These features are things I would *like* to add to the engine, but some
of them may not end up happening.

| Task            | Completed? |
|-----------------|------------|
| HTML5 exports   | No         |
| Engine logging  | No         |

## Usage
Sun16 has official documentation, hosted within this repo's [doc](doc/) folder 
as plain Markdown. See the [Getting Started](doc/getting_started.md) guide
there to learn how to use the framework. The guide assumes that you already
know about how to program, and is not the *most* suitable for beginners.

### Source documentation
I did my best to document the source code so that others can use and improve
upon my code. Documentation is found in the header (`.h`) files, as opposed
to the implementation (`.c`) files. Headers also have a brief description of
their function in the block comment at the top of the file.  

The amount of headers was intentionally kept small, to reduce the size of
the project, and to increase navigatability. At its core, Sun16 is not a
very complicated program, so it doesn't need *too* much code (at least, I
hope for future me).

#### A note on indexing
This will probably be moved to somewhere in the documentation later, but I had
nowhere better to put it, so here it is.  

Becuase Sun16 uses Lua, indexing between the two languages (Lua and the C source
code) can become quite muddled. To clarify, I have created a table to know when
to use 1 or 0 based indexing. The table is to be used for **both** languages
(i.e. if you are to use 1-based indexing, parameters, even in C, should use
1-based, even though C is 0-based).

| Instance                                        | 1-based | 0-based |
|-------------------------------------------------|---------|---------|
| Cart data tables (spritesheets, tilemaps, etc.) |    X    |    -    |
| Pixel coordinates                               |    -    |    X    |
| Tile coordinates                                |    -    |    X    |
| Screen/display coordinates                      |    -    |    X    |
| Color indicies                                  |    X    |    -    |

When using 1-based indexing in C, an issue arises in that C arrays are not
0-indexed. The solution is to place an `<index var>--;` line at the top of
the function to translate the data back into 0-indexing, wrapped in a bounds
check. See [sprite_draw()](src/sprite.c) for an example.  

Indexing differences only *really* matter when navigating/working on the source
code. To the normal user, who only interacts with Lua, the differences are
trivial and make much more logical sense relating to the language. I hope that
whole section actually clarified indexing for you, and didn't confuse you even
more :)

### Adding platforms
At the moment, Sun16 only supports two platforms: Unix and Windows. This 
availability would not be a problem if Sun16 did not use stdin/out for file
access, but because it does, there is platform specific code.  

Luckily there are/will be very few places where Sun16 actually uses the
filesystem. If you want to add support for more platforms, simply update the
`#ifdef`/`#elif` directives with your platform in the following files:
- [main.c](main.c) - needs a definition for unix `getcwd()`
- [cart.c](src/cart.c) - needs a definition for unix `access()`

## License
Sun16 is licensed under the MIT license.  
See [LICENSE.txt](LICENSE.txt) for license info.
