#pragma once

#include <vector>

class ElementBuffer
{
public:
	ElementBuffer();
	ElementBuffer(ElementBuffer&& other);
	~ElementBuffer();

	void Set(const unsigned int* rr, unsigned int len);
	void Set(const std::vector<unsigned int>& input);

	unsigned int Count() const;
	unsigned int GetHandle() const;

	static constexpr int INVALID_HANDLE = -1;
private:
	ElementBuffer(const ElementBuffer& other) = delete;
	ElementBuffer& operator=(const ElementBuffer& other) = delete;

	void Invalidate();

	int mHandle = INVALID_HANDLE;
	unsigned int mCount = 0;
};
