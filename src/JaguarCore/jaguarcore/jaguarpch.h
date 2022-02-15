// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef JAGUARPCH_H
#define JAGUARPCH_H

// add headers that you want to pre-compile here
#define JGR_WINDOWS

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#ifdef JAGUARCORE_EXPORTS 
   /*Enabled as "export" while compiling the dll project*/
#define JAGUAR_DLL __declspec(dllexport)  
#else
   /*Enabled as "import" in the Client side for using already created dll file*/
#define JAGUAR_DLL __declspec(dllimport)  
#endif

// Windows Header Files
#include <windows.h>

#include "memory/memory.h"
#include "log/log.h"

#endif //PCH_H
