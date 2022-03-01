#pragma once
#include "glad\glad.h"

class VertexArray
{
public:
	VertexArray() {}
	~VertexArray() { if (VAO) { Unload(); } }
	void Load(unsigned int count) { m_Count = count; VAO = new GLuint[count]; glGenVertexArrays(count, VAO); }
	void Bind(unsigned int idx) { glBindVertexArray(VAO[idx]); }
	void Unbind() { glBindVertexArray(0); }
	void Unload() { glDeleteVertexArrays(m_Count, VAO); delete[] VAO; VAO = nullptr; }
private:
	GLuint* VAO;
	int m_Count = 0;
};

