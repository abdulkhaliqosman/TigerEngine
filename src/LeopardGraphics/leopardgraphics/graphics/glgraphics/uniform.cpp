#include <leopardgraphics/leopardpch.h>
#include "uniform.h"


template <typename T>
void Uniform<T>::Set(unsigned int slot, const T& value)
{
	Set(slot, (T*)&value, 1);
}

template <>
void Uniform<bool>::Set(unsigned int s, const std::vector<bool>& v)
{
	std::vector<int> vector;
	for (int i = 0; i < v.size(); ++i)
	{
		vector[i] = v[i];

	}
	Set(s, (bool*)&vector[0], (unsigned int)v.size());
}

template <typename T>
void Uniform<T>::Set(unsigned int s, const std::vector<T>& v)
{
	Set(s, &v[0], (unsigned int)v.size());
}

template<>
void Uniform<bool>::Set(unsigned int slot, const bool* data, unsigned int length)
{
	glUniform1iv(slot, (GLsizei)length, (int*)&data[0]);
}

template<>
void Uniform<int>::Set(unsigned int slot, const int* data, unsigned int length)
{
	glUniform1iv(slot, (GLsizei)length, (int*)&data[0]);
}

template<>
void Uniform<ivec2>::Set(unsigned int slot, const ivec2* data, unsigned int length)
{
	glUniform2iv(slot, (GLsizei)length, (int*)&data[0]);
}

template<>
void Uniform<ivec4>::Set(unsigned int slot, const ivec4* data, unsigned int length)
{
	glUniform4iv(slot, (GLsizei)length, (int*)&data[0]);
}

template<>
void Uniform<float>::Set(unsigned int slot, const float* data, unsigned int length)
{
	glUniform1fv(slot, (GLsizei)length, (float*)&data[0]);
}

template<>
void Uniform<vec2>::Set(unsigned int slot, const vec2* data, unsigned int length)
{
	glUniform2fv(slot, (GLsizei)length, (float*)&data[0]);
}

template<>
void Uniform<vec3>::Set(unsigned int slot, const vec3* data, unsigned int length)
{
	glUniform3fv(slot, (GLsizei)length, (float*)&data[0]);
}

template<>
void Uniform<vec4>::Set(unsigned int slot, const vec4* data, unsigned int length)
{
	glUniform4fv(slot, (GLsizei)length, (float*)&data[0]);
}

template<>
void Uniform<jgr::quat>::Set(unsigned int slot, const jgr::quat* data, unsigned int length)
{
	glUniform4fv(slot, (GLsizei)length, (float*)&data[0]);
}

template<>
void Uniform<mat4>::Set(unsigned int slot, const mat4* inputArray, unsigned int arrayLength)
{
	glUniformMatrix4fv(slot, (GLsizei)arrayLength, false, (float*)&inputArray[0]);
}