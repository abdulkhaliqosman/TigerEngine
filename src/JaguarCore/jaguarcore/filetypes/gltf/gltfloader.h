#pragma once

struct cgltf_data;

JAGUAR_DLL cgltf_data* LoadGLTFFile(const char* path);
JAGUAR_DLL void FreeGLTFFile(cgltf_data* handle);

