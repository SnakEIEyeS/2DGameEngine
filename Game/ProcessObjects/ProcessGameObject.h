#pragma once

#include <assert.h>
#include <stdint.h>
#include <string.h>

#include "Lua\lua.hpp"

void CreateGameObject(const char * i_pFileName, const char * i_JobQueueName);

size_t ReadFloatArray(lua_State * i_pState, int i_index, float * o_pFloats, size_t i_numFloats);
size_t ReadIntArray(lua_State * i_pState, int i_index, unsigned int * o_pInts, size_t i_numInts);

void ProcessGameObject(const char * pFileName);
