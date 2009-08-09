/**
* Copyright (c) 2006-2009 LOVE Development Team
* 
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* 
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 
* 1. The origin of this software must not be misrepresented; you must not
*    claim that you wrote the original software. If you use this software
*    in a product, an acknowledgment in the product documentation would be
*    appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
*    misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
**/

// LOVE
#include "wrap_Timer.h"

namespace love
{
namespace timer
{
namespace sdl
{
	static Timer * instance = 0;

	int w_step(lua_State * L)
	{
		instance->step();
		return 0;
	}

	int w_getDelta(lua_State * L)
	{
		lua_pushnumber(L, instance->getDelta());
		return 1;
	}

	int w_getFPS(lua_State * L)
	{
		lua_pushnumber(L, instance->getFPS());
		return 1;
	}

	int w_sleep(lua_State * L)
	{
		int ms = luaL_checkint(L, 1);
		instance->sleep(ms);
		return 0;
	}

	int w_getTime(lua_State * L)
	{
		lua_pushnumber(L, instance->getTime());
		return 1;
	}

	int w_Timer_open(lua_State * L)
	{
		// List of functions to wrap.
		static const luaL_Reg functions[] = {
			{ "step", w_step },
			{ "getDelta", w_getDelta },
			{ "getFPS", w_getFPS },
			{ "sleep", w_sleep },
			{ "getTime", w_getTime },
			{ 0, 0 }
		};

		if(instance == 0)
		{
			try 
			{
				instance = new Timer();
			} 
			catch(Exception & e)
			{
				return luaL_error(L, e.what());
			}
		}

		luax_register_gc(L, instance);

		return luax_register_module(L, functions, 0, 0, "timer");
	}

} // sdl
} // timer
} // love
