#pragma once

#include <vector>
#include "glad/glad.h"
#include "jaguarcore/math/math.h"

template <typename T>
class Uniform
{
public:
	static void Set(unsigned int slot, const T& value);
	static void Set(unsigned int slot, const T* arr, unsigned int len);
	static void Set(unsigned int slot, const std::vector<T>& arr);

private:
	Uniform();
	~Uniform();

	Uniform(const Uniform&) = delete;
	Uniform& operator=(const Uniform&) = delete;
};

template Uniform<bool>;

template Uniform<int>;
template Uniform<ivec2>;
template Uniform<ivec4>;

template Uniform<float>;
template Uniform<vec2>;
template Uniform<vec3>;
template Uniform<vec4>;

template Uniform<jgr::quat>;
template Uniform<mat4>;
