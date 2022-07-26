#pragma once

// define to mem debug the game
#define JGR_MEM_DEBUG

#include "jaguarcore/memory/memory.h"
#include "jaguarcore/log/log.h"
#include "jaguarcore/math/math.h"
#include <jaguarcore/system/isystem.h>
#include <jaguarcore/components/component.h>
#include <jaguarcore/gameobject/gameobject.h>

// all the stl we love
#include <cassert>

using vec2 = jgr::vec2;
using vec3 = jgr::vec3;
using vec4 = jgr::vec4;
using ivec2 = jgr::ivec2;
using ivec4 = jgr::ivec4;
using mat4 = jgr::mat4;
using quat = jgr::quat;

using iSystem = jgr::iSystem;
using Component = jgr::Component;
using GameObject = jgr::GameObject;
