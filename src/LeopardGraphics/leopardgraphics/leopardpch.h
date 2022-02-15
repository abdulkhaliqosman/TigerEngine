// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

// add headers that you want to pre-compile here
#ifdef LEOPARDGRAPHICS_EXPORTS 
   /*Enabled as "export" while compiling the dll project*/
#define LEOPARD_DLL __declspec(dllexport)  
#else
   /*Enabled as "import" in the Client side for using already created dll file*/
#define LEOPARD_DLL __declspec(dllimport)  
#endif

// Windows Header Files
#include <windows.h>


#endif //PCH_H
