#pragma once
#include "staticshape.h"

namespace lpd
{
	class Cube : public StaticShape
	{
	public:
		const vec3* GetVertices() const override;
		unsigned int GetVertexCount() const override;

		const unsigned int* GetIndices() const override;
		unsigned int GetIndexCount() const override;

		const vec3* GetNormals() const override;
		unsigned int GetNormalCount() const override;
	};
}
