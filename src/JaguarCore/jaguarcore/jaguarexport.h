#pragma once

#ifdef JAGUARCORE_EXPORTS 
/*Enabled as "export" while compiling the dll project*/
#define JAGUAR_DLL __declspec(dllexport)  
#else
/*Enabled as "import" in the Client side for using already created dll file*/
#define JAGUAR_DLL __declspec(dllimport)  
#endif

#include "jaguarcore/memory/memory.h"
#include "jaguarcore/log/log.h"
#include "jaguarcore/math/math.h"

using vec2 = jgr::vec2;
using vec3 = jgr::vec3;
using vec4 = jgr::vec4;
using ivec2 = jgr::ivec2;
using ivec4 = jgr::ivec4;
using mat4 = jgr::mat4;
using quat = jgr::quat;