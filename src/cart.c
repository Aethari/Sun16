/*
 * "Cartridge" data management
 * See cart.h for documentation
 * 2025 Aethari
 */

#include <stdio.h>
#include <stdlib.h>

#include <lua.h>
#include <lauxlib.h>

#include <sds.h>

#ifdef __unix__
	#include <unistd.h>
#elif _WIN32
	#include <io.h>
	#define F_OK 0
	#define access _access
#endif

// The max amound of spritesheets allowed
#define MAX_SPRITE_LEN 16

// The max amount of tilemaps allowed
#define MAX_TILE_LEN 16

// The max amount of sounds allowed
#define MAX_SFX_LEN 32

// The max amount of music tracks allowed
#define MAX_MUSIC_LEN 32

// == Local variables ==========================================
sds cart_title;
sds *spritesheets;
sds *tilemaps;
sds *sounds;
sds *music;

// == Getters ==================================================
sds cart_get_title() {
	if(cart_title != NULL) {
		return cart_title;
	} else {
		return sdsnew("Sun16 Cartridge");
	}
}

sds cart_get_spritesheet(int i) {
	if(i < 0) {
		printf("Error (cart.c): Attempt to access spritesheet with negative index (%d given).\n", i);
		exit(1);
	}

	if(i < MAX_SPRITE_LEN) {
		if(spritesheets[i] != NULL) {
			return sdsdup(spritesheets[i]);
		} else {
			printf("Error (cart.c): Spritesheet at index %d is invalid. Check your cart.s16 file.\n", i);
			exit(1);
		}
	} else {
		// find the first valid spritesheet and return it
		for(int j = 0; j < MAX_SPRITE_LEN; j++) {
			if(spritesheets[j] != NULL) {
				return sdsdup(spritesheets[j]);
			}
		}

		printf("Error (cart.c): No spritesheets were found. Check your cart.s16 file.\n");
		exit(1);
	}
}

sds cart_get_tilemap(int i) {
	if(i < 0) {
		printf("Error (cart.c): Attempt to access tilemap with negative index (%d given).\n", i);
		exit(1);
	}

	if(i < MAX_TILE_LEN) {
		if(tilemaps[i] != NULL) {
			return sdsdup(tilemaps[i]);
		} else {
			printf("Error (cart.c): Tilemap at index %d is invalid. Check your cart.s16 file.\n", i);
			exit(1);
		}
	} else {
		// find the first valid tilemap and return it
		for(int j = 0; j < MAX_TILE_LEN; j++) {
			if(tilemaps[j] != NULL) {
				return sdsdup(tilemaps[j]);
			}
		}

		printf("Error (cart.c): No tilemaps were found. Check your cart.s16 file.\n");
		exit(1);
	}
}

sds cart_get_sound(int i) {
	if(i < 0) {
		printf("Error (cart.c): Attempt to access sound with negative index (%d given).\n", i);
		exit(1);
	}

	if(i < MAX_SFX_LEN) {
		if(sounds[i] != NULL) {
			return sdsdup(sounds[i]);
		} else {
			printf("Error (cart.c): Sound at index %d is invalid. Check your cart.s16 file.\n", i);
			exit(1);
		}
	} else {
		// find the first valid sound and return it
		for(int j = 0; j < MAX_SFX_LEN; j++) {
			if(sounds[j] != NULL) {
				return sdsdup(sounds[j]);
			}
		}

		printf("Error (cart.c): No sounds were found. Check your cart.s16 file.\n");
		exit(1);
	}
}

sds cart_get_music(int i) {
	if(i < 0) {
		printf("Error (cart.c): Attempt to access music track with negative index (%d given).\n", i);
		exit(1);
	}

	if(i < MAX_MUSIC_LEN) {
		if(music[i] != NULL) {
			return sdsdup(music[i]);
		} else {
			printf("Error (cart.c): Music track at index %d is invalid. Check your cart.s16 file.\n", i);
			exit(1);
		}
	} else {
		// find the first valid music track and return it
		for(int j = 0; j < MAX_MUSIC_LEN; j++) {
			if(music[j] != NULL) {
				return sdsdup(music[j]);
			}
		}

		printf("Error 9cart.c): No music tracks were found. Check your cart.s16 file.\n");
		exit(1);
	}
}

// == Other functions ==========================================
void cart_init(sds cwd) {
	// create a lua instance at cwd/cart.s16 to pull globals from
	lua_State *L = luaL_newstate();

	sds cartpath = sdscat(cwd, "/cart.s16");

	if(!access(cartpath, F_OK) == 0) {
		printf("Error (cart.c): No cart.s16 file found. Make sure your project's cart file exists!\n");
		exit(1);
	}

	if(luaL_dofile(L, cartpath) == LUA_OK) {
		// retrieve globals from cart.s16
		
		// title
		lua_getglobal(L, "title");
		if(lua_isstring(L, -1))  {
			cart_title = sdsnew(lua_tostring(L, -1));
		} else {
			printf("Error (cart.c): Project title is not a string. Check your cart.s16 file.\n");
			sdsfree(cartpath);
			exit(1);
		}

		// spritesheet table
		spritesheets = (sds *)calloc(MAX_SPRITE_LEN, sizeof(sds));
		lua_getglobal(L, "spritesheets");
		if(lua_istable(L, -1)) {
			// get the length of the table and pop it
			lua_len(L, -1);
			int len = lua_tonumber(L, -1);
			lua_pop(L, 1);

			// spritesheets is still at top of stack
			for(int i = 0; i < len; i++) {
				lua_pushinteger(L, i+1);
				lua_gettable(L, -2);

				// puts path on top of stack
				lua_pushstring(L, "path");
				lua_gettable(L, -2);

				sds path = sdsnew(lua_tostring(L, -1));
				lua_pop(L, 1);

				// puts index on top of stack
				lua_pushstring(L, "index");
				lua_gettable(L, -2);

				int index = lua_tointeger(L, -1);

				if(index > MAX_SPRITE_LEN) {
					index = MAX_SPRITE_LEN;
				} else if(index <= 0) {
					printf("Error (cart.c): Spritesheet index cannot be 0 or negative (%d given). Check your cart.s16 file.\n", index);
					exit(1);
				}

				// pop 2 values for "index" value and the subtable
				lua_pop(L, 2);

				spritesheets[index-1] = sdsdup(path);
				sdsfree(path);
			}
		} else {
			printf("Error (cart.c): Global \"spritesheets\" is not a table or does not exist. Check your cart.s16 file.\n");
			sdsfree(cartpath);
			exit(1);
		}
		
		// tilemap table
		tilemaps = (sds *)calloc(MAX_TILE_LEN, sizeof(sds));
		lua_getglobal(L, "tilemaps");
		if(lua_istable(L, -1)) {
			// get the length of the table and pop it
			lua_len(L, -1);
			int len = lua_tonumber(L, -1);
			lua_pop(L, 1);

			// tilemaps is still at top of stack
			for(int i = 0; i < len; i++) {
				lua_pushinteger(L, i+1);
				lua_gettable(L, -2);

				// puts path on top of stack
				lua_pushstring(L, "path");
				lua_gettable(L, -2);

				sds path = sdsnew(lua_tostring(L, -1));
				lua_pop(L, 1);

				// puts index on top of stack
				lua_pushstring(L, "index");
				lua_gettable(L, -2);

				int index = lua_tointeger(L, -1);

				if(index > MAX_TILE_LEN) {
					index = MAX_TILE_LEN;
				} else if(index <= 0) {
					printf("Error (cart.c): Tilemap index cannot be 0 or negative (%d given). Check your cart.s16 file.\n", index);
					exit(1);
				}

				// pop 2 values for "index" value and the subtable
				lua_pop(L, 2);

				tilemaps[index-1] = sdsdup(path);
				sdsfree(path);
			}
		} else {
			printf("Error (cart.c): Global \"tilemaps\" is not a table or does not exist. Check your cart.s16 file.\n");
			sdsfree(cartpath);
			exit(1);
		}
		
		// sfx table
		sounds = (sds *)calloc(MAX_SFX_LEN, sizeof(sds));
		lua_getglobal(L, "sounds");
		if(lua_istable(L, -1)) {
			// get the length of the table and pop it
			lua_len(L, -1);
			int len = lua_tonumber(L, -1);
			lua_pop(L, 1);

			// sounds is still at top of stack
			for(int i = 0; i < len; i++) {
				lua_pushinteger(L, i+1);
				lua_gettable(L, -2);

				// puts path on top of stack
				lua_pushstring(L, "path");
				lua_gettable(L, -2);

				sds path = sdsnew(lua_tostring(L, -1));
				lua_pop(L, 1);

				// puts index on top of stack
				lua_pushstring(L, "index");
				lua_gettable(L, -2);

				int index = lua_tointeger(L, -1);

				if(index > MAX_SFX_LEN) {
					index = MAX_SFX_LEN;
				} else if(index <= 0) {
					printf("Error (cart.c): Sound index cannot be 0 or negative (%d given). Check your cart.s16 file.\n", index);
					exit(1);
				}

				// pop 2 values for "index" value and the subtable
				lua_pop(L, 2);

				sounds[index-1] = sdsdup(path);
				sdsfree(path);
			}
		} else {
			printf("Error (cart.c): Global \"sounds\" is not a table or does not exist. Check your cart.s16 file.\n");
			sdsfree(cartpath);
			exit(1);
		}
		
		// music table
		music = (sds *)calloc(MAX_MUSIC_LEN, sizeof(sds));
		lua_getglobal(L, "music");
		if(lua_istable(L, -1)) {
			// get the length of the table and pop it
			lua_len(L, -1);
			int len = lua_tonumber(L, -1);
			lua_pop(L, 1);

			// music is still at top of stack
			for(int i = 0; i < len; i++) {
				lua_pushinteger(L, i+1);
				lua_gettable(L, -2);

				// puts path on top of stack
				lua_pushstring(L, "path");
				lua_gettable(L, -2);

				sds path = sdsnew(lua_tostring(L, -1));
				lua_pop(L, 1);

				// puts index on top of stack
				lua_pushstring(L, "index");
				lua_gettable(L, -2);

				int index = lua_tointeger(L, -1);

				if(index > MAX_MUSIC_LEN) {
					index = MAX_MUSIC_LEN;
				} else if(index <= 0) {
					printf("Error (cart.c): Music track index cannot be 0 or negative (%d given). Check your cart.s16 file.\n", index);
					exit(1);
				}

				// pop 2 values for "index" value and the subtable
				lua_pop(L, 2);

				music[index-1] = sdsdup(path);
				sdsfree(path);
			}
		} else {
			printf("Error (cart.c): Global \"music\" is not a table or does not exist. Check your cart.s16 file.\n");
			sdsfree(cartpath);
			exit(1);
		}
	} else {
		printf("Error (cart.c): Failed to execute \"%s\":\n", cartpath);
		luaL_error(L, "Error:%s\n", lua_tostring(L, -1));

		sdsfree(cartpath);
		lua_close(L);
		exit(1);
	}

	sdsfree(cartpath);
	lua_close(L);
}

void cart_free() {
	free(spritesheets);
	free(tilemaps);
	free(sounds);
	free(music);
}
