#pragma once

#include "JobSystem\IJob.h"

#include <assert.h>
#include <stdint.h>

#include "JobSystem\JobSystem.h"
#include "Lua\lua.hpp"

class ProcessGOFileJob : public Engine::JobSystem::IJob
{
public:
	ProcessGOFileJob(lua_State * i_pluaState, uint8_t * i_pFileContents);

	void Run();
private:
	size_t ReadFloatArray(lua_State * i_pState, int i_index, float * o_pFloats, size_t i_numFloats)
	{
		lua_pushnil(i_pState);

		size_t index = 0;
		while (lua_next(i_pState, i_index - 1) != 0)
		{
			assert(lua_type(i_pState, -1) == LUA_TNUMBER);

			o_pFloats[index++] = float(lua_tonumber(i_pState, -1));
			//pop value
			lua_pop(i_pState, 1);

			if (index >= i_numFloats)
			{
				lua_pop(i_pState, 1);
				break;
			}
		}

		return index;
	}

	size_t ReadIntArray(lua_State * i_pState, int i_index, unsigned int * o_pInts, size_t i_numInts)
	{
		lua_pushnil(i_pState);

		size_t index = 0;
		while (lua_next(i_pState, i_index - 1) != 0)
		{
			assert(lua_type(i_pState, -1) == LUA_TNUMBER);

			o_pInts[index++] = static_cast<unsigned int>(lua_tointeger(i_pState, -1));
			//pop value
			lua_pop(i_pState, 1);

			if (index >= i_numInts)
			{
				lua_pop(i_pState, 1);
				break;
			}
		}

		return index;
	}

	lua_State * pLuaState;
	uint8_t * pFileContents;

};
