Vendored programs all have their own LICENSE files located in the directory the
source can be found in.

Vendored directories:
	SDL: a mirror of the SDL development repo
	Lua: a copy of the Lua 5.4 source code - not a submodule

Vendored files:
	sds.h, sds.c, sdsalloc.h: a small dynamic string library

Unix dependencies:
	liblua54.a: static library for Lua 5.4
	libSDL3.so.0.2.12: dynamic library for SDL

	.so files are symlinked into <name>.so.0 and
	<name>.so within the build directory during the
	build process.

Win dependencies:
	lua54.dll: dynamic library for Lua 5.4
	lua54.dll.a: static library for Lua 5.4 only needed at link/compile time
	SDL3.dll: dynamic library for SDL
