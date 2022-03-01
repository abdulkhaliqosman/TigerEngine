#pragma once

class ElementBuffer;

enum class DrawMode
{
	Points,
	LineStrip,
	LineLoop,
	Lines,
	Triangles,
	TriangleStrip,
	TriangleFan
};

void Draw(const ElementBuffer& inElementBuffer, DrawMode mode);
void Draw(unsigned int vertexCount, DrawMode mode);

void DrawInstanced(ElementBuffer& inElementBuffer, DrawMode mode, unsigned int instanceCount);
void DrawInstanced(unsigned int vertexCount, DrawMode mode, unsigned int numInstances);