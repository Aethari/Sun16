/*
 * "Cartridge" data management
 * See cart.h for documentation
 * 2025 Aethari
 */

#include <lua.h>
#include <lauxlib.h>

#include <sds.h>

void cart_init(sds cwd) {
	// create a lua instance at cwd/cart.s16 to pull globals from
	lua_State *L = luaL_newstate();

	sds cartpath = sdscat(cwd, "/cart.s16");

	printf("%s\n", cartpath);

	lua_close(L);
}
