#pragma once

#include <vector>
#include "glad/glad.h"
#include "jaguarcore/math/math.h"

template<typename T>
class Attribute
{
public:
	Attribute();
	Attribute(Attribute&& other);

	~Attribute();

	void Set(const T* inputArray, unsigned int arrayLength);
	void Set(const std::vector<T>& input);

	void BindTo(unsigned int slot) const;
	void UnBindFrom(unsigned int slot) const;

	unsigned int Count() const;
	unsigned int GetHandle();

	static constexpr int INVALID_HANDLE = -1;
private:
	Attribute(const Attribute& other) = delete;
	Attribute& operator=(const Attribute& other) = delete;

	void Invalidate();

	void SetAttribPointer(unsigned int slot) const;

	int mHandle = INVALID_HANDLE;
	unsigned int mCount = 0;
};

template Attribute<int>;
template Attribute<ivec4>;

template Attribute<float>;
template Attribute<vec2>;
template Attribute<vec3>;
template Attribute<vec4>;

template<typename T>
Attribute<T>::Attribute()
{
	unsigned int handle;
	glGenBuffers(1, &handle);
	mHandle = handle;
}

template<typename T>
Attribute<T>::Attribute(Attribute&& other)
	:mHandle{ other.mHandle }, mCount{ other.mCount }
{
	other.Invalidate();
}

template<typename T>
Attribute<T>::~Attribute()
{
	if (mHandle != INVALID_HANDLE)
	{
		unsigned int handle = mHandle;
		glDeleteBuffers(1, &handle);
	}

	Invalidate();
}

template<typename T>
unsigned int Attribute<T>::Count() const
{
	return mCount;
}

template<typename T>
unsigned int Attribute<T>::GetHandle()
{
	return mHandle;
}

template<typename T>
void Attribute<T>::Invalidate()
{
	mHandle = INVALID_HANDLE;
}

template<typename T>
void Attribute<T>::Set(const T* inputArray, unsigned int arrayLength)
{
	mCount = arrayLength;
	size_t size = sizeof(T);
	glBindBuffer(GL_ARRAY_BUFFER, mHandle);
	glBufferData(GL_ARRAY_BUFFER, size * mCount, inputArray, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

template<typename T>
void Attribute<T>::Set(const std::vector<T>& input)
{
	Set(&input[0], (unsigned int)input.size());
}

template<typename T>
void Attribute<T>::BindTo(unsigned int slot) const
{
	glBindBuffer(GL_ARRAY_BUFFER, mHandle);
	glEnableVertexAttribArray(slot);
	SetAttribPointer(slot);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

template<typename T>
void Attribute<T>::UnBindFrom(unsigned int slot) const
{
	glBindBuffer(GL_ARRAY_BUFFER, mHandle);

	glDisableVertexAttribArray(slot);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}