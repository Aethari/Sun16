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

// == Local variables ==========================================
sds cart_title;

// == Getters ==================================================
sds cart_get_title() {
	if(cart_title != NULL) {
		return cart_title;
	} else {
		return sdsnew("Sun16 Cartridge");
	}
}

// == Setters ==================================================

void cart_set_title(sds new_title) {
	cart_title = sdsdup(new_title);
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
			exit(1);
		}

		// spritesheet table
		lua_getglobal(L, "spritesheets");
		if(lua_istable(L, -1)) {
		} else {
			printf("Error (cart.c): Global \"spritesheets\" is not a table or does not exist. Check your cart.s16 file.\n");
			exit(1);
		}
		
		// tilemap table
		lua_getglobal(L, "tilemaps");
		if(lua_istable(L, -1)) {
		} else {
			printf("Error (cart.c): Global \"tilemaps\" is not a table or does not exist. Check your cart.s16 file.\n");
			exit(1);
		}
		
		// sfx table
		lua_getglobal(L, "sounds");
		if(lua_istable(L, -1)) {
		} else {
			printf("Error (cart.c): Global \"sounds\" is not a table or does not exist. Check your cart.s16 file.\n");
			exit(1);
		}
		
		// music table
		lua_getglobal(L, "music");
		if(lua_istable(L, -1)) {
		} else {
			printf("Error (cart.c): Global \"music\" is not a table or does not exist. Check your cart.s16 file.\n");
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
