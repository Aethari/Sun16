# Getting started with Sun16
This is a guide inteded for new users to set up their first cart. It
is (hopefully) the only guide like it in the official documentation.  

If you are looking for API documentation, here is a table of contents:

| Page          | Description                     |
|---------------|---------------------------------|
| coming soon   | coming soon - didn't you see?   |

## How Sun16 works
Before using Sun16, it is vital to understand how the framework
manages cartridges, and the structure of the added modules.

### Assets/resources
If you have used fantasy consoles before, you probably know how
assets work: the console provides a set of tools for you to
create sprites, tilemaps, sound effects, etc. Not Sun16.  

Sun16 assets are stored as external files in your project's
directory, as `sdat` (SunDATa) files (or `.ogg` files for
sfx/music). Sun16 then loads these assets from paths defined
in the `cart.s16` file (see [Cartridges](###-Cartridges)].  

Unfortunately, I have not made any tools for converting png
files and tilemaps into `sdat` format. I plan on making a
simple (external) converter for both sprites and tilemaps,
as well as maybe Tiled and Aseprite plugins.

### `cart.s16`
All Sun16 cartridges have a core file defining where assets
are located, as well as the cart's title. This file is
called `cart.s16` and should be located at your project's
root.  

The `cart.s16` file is just a normal Lua file with a different
file extension. This allows for simplification of Sun16, but a
byproduct is that you can change parameters based on conditions
(like operating systems). The only condition for a parameter to
be valid is that it is global.  

Every `cart.s16` file needs five globals:
- `title`: a string for the cart's name - this will be displayed
           as the window's title
- `spritesheets`: a table with subtables representing locations
                  where spritesheet data is located
- `tilemaps`: a table with subtables representing locations
              where where tilemap data is located
- `sounds`: a table with subtables representing locations where
            sound effect data is located
- `music`: a table with subtables representing locations where
           music track data is located

For an example `cart.s16` file, see the [example project](example/).
For more detailed help about `cart.s16` files, see the
[cart.s16 documentation](doc/cart.md).

### `main.lua`
Each Sun16 cartridge contains a `main.lua` script that is
automatically loaded and ran when you run the cart. The `main.lua`
script should be located in your project's root, right next to
`cart.s16`. See the table of contents at the top of this file
for how to use Sun16's Lua API.

## Creating a cartridge
Guide coming soon, when the framework is more complete!
