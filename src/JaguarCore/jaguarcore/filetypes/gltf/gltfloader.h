#pragma once

struct cgltf_data;

cgltf_data* LoadGLTFFile(const char* path);
void FreeGLTFFile(cgltf_data* handle);

