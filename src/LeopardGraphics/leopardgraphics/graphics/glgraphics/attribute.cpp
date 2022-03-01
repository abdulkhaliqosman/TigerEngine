#include <leopardgraphics/leopardpch.h>
#include "attribute.h"

template<>
void Attribute<int>::SetAttribPointer(unsigned int slot) const
{
	glVertexAttribIPointer(slot, 1, GL_INT, 0, (void*)0);
}

template<>
void Attribute<ivec4>::SetAttribPointer(unsigned int slot) const
{
	glVertexAttribIPointer(slot, 4, GL_INT, 0, (void*)0);
}

template<>
void Attribute<float>::SetAttribPointer(unsigned int slot) const
{
	glVertexAttribPointer(slot, 1, GL_FLOAT, GL_FALSE, 0, 0);
}

template<>
void Attribute<vec2>::SetAttribPointer(unsigned int slot) const
{
	glVertexAttribPointer(slot, 2, GL_FLOAT, GL_FALSE, 0, 0);
}

template<>
void Attribute<vec3>::SetAttribPointer(unsigned int slot) const
{
	glVertexAttribPointer(slot, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

template<>
void Attribute<vec4>::SetAttribPointer(unsigned int slot) const
{
	glVertexAttribPointer(slot, 4, GL_FLOAT, GL_FALSE, 0, 0);
}
