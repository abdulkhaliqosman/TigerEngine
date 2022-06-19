#pragma once

// STANDARDIZE: little endian
class NetMsgReadVisitor
{
public:
	inline NetMsgReadVisitor(const char* buffer, int length) :m_Buffer{ buffer }, m_Length{ length }{}

	template<typename T>  // TODO fix to primitive type
	void Peek(T& dest) const; // TODO peek with index
	
	template<typename T>
	void Read(T& dest) const;

	inline void ReadBuffer(char* buffer, int length) const;
private:
	inline char ReadChar() const { return m_Buffer[idx++]; }

	static constexpr unsigned char BYTE_MASK = 0xFF;
	static constexpr int BYTE_BIT_LENGTH = 8;

	const char* m_Buffer;
	int m_Length;
	mutable int idx = 0;
};

class NetMsgWriteVisitor
{
public:
	inline NetMsgWriteVisitor(char* buffer, int length):m_Buffer{buffer}, m_Length{length}{}

	template<typename T> // TODO fix to primitive type
	void Write(const T& dest);

	inline void WriteBuffer(const char* buffer, int length);
	inline int GetWrittenLength() { return idx; }
private:
	inline void WriteChar(char val) { m_Buffer[idx++] = val; }


	static constexpr unsigned char BYTE_MASK = 0xFF;
	static constexpr int BYTE_BIT_LENGTH = 8;

	char* m_Buffer;
	int m_Length;
	mutable int idx = 0;
};

template<typename T>
void NetMsgReadVisitor::Peek(T& dest) const
{
	for (int i = 0; i < sizeof(T); ++i)
	{
		T val = m_Buffer[idx + i];
		dest |= val << (i * BYTE_BIT_LENGTH);
	}
}

template<typename T>
void NetMsgReadVisitor::Read(T& dest) const
{
	for (int i = 0; i < sizeof(T); ++i)
	{
		T val = ReadChar();
		dest |= val << (i * BYTE_BIT_LENGTH);
	}
}

template<>
inline void NetMsgReadVisitor::Read(float& val) const
{
	NetMsgReadVisitor::Read<int>(reinterpret_cast<int&>(val));
}

inline void NetMsgReadVisitor::ReadBuffer(char* buffer, int destLength) const
{
	int srcLength = m_Length - idx;
	assert(destLength <= srcLength);

	memcpy_s(buffer, destLength, m_Buffer + idx, destLength);

	idx += destLength;
}

template<typename T> // TODO fix to primitive type
void NetMsgWriteVisitor::Write(const T& val)
{
	assert(sizeof(T) <= m_Length - idx);

	for (int i = 0; i < sizeof(T); ++i)
	{
		WriteChar(static_cast<char>((val >> (i * BYTE_BIT_LENGTH)) & BYTE_MASK));
	}
}

template<>
inline void NetMsgWriteVisitor::Write(const float& val)
{
	NetMsgWriteVisitor::Write<int>(reinterpret_cast<const int&>(val));
}

inline void NetMsgWriteVisitor::WriteBuffer(const char* buffer, int srcLength)
{
	int destLength = m_Length - idx;

	assert(srcLength <= destLength);

	memcpy_s(m_Buffer + idx, destLength, buffer, srcLength);

	idx += srcLength;
}