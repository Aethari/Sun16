## Cart.s16
All Sun16 cartridges have a core file defining where assets
are located, as well as the cart's title. This file is
called `cart.s16` and should be located at your project's
root.  

The `cart.s16` file is just a normal Lua file with a different
file extension. This allows for simplification of the Sun16 
source, but a byproduct is that you can change parameters based
on conditions (like operating systems). The only condition for
a parameter to be valid is that it is global.  

In Lua, globals are simply variables declared **without** the
`local` keyword. Even if a variable is declared inside of an
`if` or `function` block, as long as it does not have the `local`
keyword, it is a global variable.  

### Types of data
There are two "types" of data Sun16 looks for when loading `cart.s16`:
- simple: A normal variable with a single Lua value that is not a
          table (number, string, etc.).
- multi-table: A table that has children that are also tables. These
               subtables **cannot** be any type other than a table.
               Each subtable contains two simple values:
    - `path`: The path to the resource to be loaded, relative to
              `cart.s16`.
    - `index`: The index that the loaded resource will be located
               at. For example, you can have two spritesheets, one
               at index 1 and another at index 2. If you wanted to
               draw a sprite from spritesheet 1, you would pass 1
               into the relevant function. But if you wanted to use
               a sprite from spritesheet 2, you would pass in 2.
               Indicies should start at 1, not 0.

### Globals
Each `cart.s16` file requires 5 globals to be defined:
- `title`: A simple Lua string for the cart's name. This is what
           will be displayed as the window's title.
- `spritesheets`: A multi-table representing spritesheet locations
                  and indicies.
- `tilemaps`: A multi-table representing tilemap locations and
              indicies.
- `sounds`: A multi-table representing sound effect locations and
            indicies.
- `music`: A multi-table representing music track locations and
           indicies.

The `spritesheets` and `tilemaps` tables both require the paths
to be pointing to an `sdat` (SunDATa) file. If the path points
to a different file extension or a folder, an error will be 
thrown when Sun16 attempts to load the resource.  

The `sounds` and `music` tables both require the paths to be
pointing to an `ogg` file. If the path points to a different
file extension or a folder, an error will be thrown when 
Sun16 attempts to load the resource.  

Because both the `sounds` and `music` tables use `ogg` files,
you can load music tracks into the `sounds` table if you wish.
Just make sure to change the call from music to sounds when
accessing it.

### Example
For clarification on how to write a `cart.s16` file see the
[example cart.s16 file](example/cart.s16).
