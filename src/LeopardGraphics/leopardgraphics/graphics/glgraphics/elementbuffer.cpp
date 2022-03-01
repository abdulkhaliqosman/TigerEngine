#include <leopardgraphics/leopardpch.h>
#include "elementbuffer.h"
#include "glad/glad.h"

ElementBuffer::ElementBuffer()
{
	unsigned int handle;
	glGenBuffers(1, &handle);
	mHandle = handle;
}

ElementBuffer::ElementBuffer(ElementBuffer&& other)
	:mHandle{other.mHandle}, mCount{other.mCount}
{
	other.Invalidate();
}

ElementBuffer::~ElementBuffer()
{
	if (mHandle != INVALID_HANDLE)
	{
		unsigned int handle = mHandle;
		glDeleteBuffers(1, &handle);
	}
	
	Invalidate();
}

void ElementBuffer::Invalidate()
{
	// WARNING: DOES NOT FREE
	mHandle = INVALID_HANDLE;
	mCount = 0;
}


unsigned int ElementBuffer::Count() const
{
	return mCount;
}

unsigned int ElementBuffer::GetHandle() const
{
	return mHandle;
}

void ElementBuffer::Set(const unsigned int* inputArray, unsigned int arrayLength)
{
	mCount = arrayLength;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mHandle);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mCount, inputArray, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ElementBuffer::Set(const std::vector<unsigned int>& input)
{
	Set(&input[0], (unsigned int)input.size());
}