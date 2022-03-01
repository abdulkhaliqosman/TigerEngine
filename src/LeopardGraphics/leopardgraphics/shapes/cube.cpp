#include <leopardgraphics/leopardpch.h>
#include "cube.h"

#include "leopardgraphics/graphics/glgraphics/glgraphics.h"

namespace lpd
{
    static vec3 vertices[] = {
            vec3{ 0.5f,  0.5f,  0.5f}, // top right
            vec3{ 0.5f, -0.5f,  0.5f}, // bottom right
            vec3{-0.5f, -0.5f,  0.5f}, // bottom left
            vec3{-0.5f,  0.5f,  0.5f}, // top left 
            vec3{ 0.5f,  0.5f, -0.5f}, // top right
            vec3{ 0.5f, -0.5f, -0.5f}, // bottom right
            vec3{-0.5f, -0.5f, -0.5f}, // bottom left
            vec3{-0.5f,  0.5f, -0.5f}  // top left 
    };

    static unsigned int indices[] = {  // note that we start from 0!
        0, 3, 2,  // first Triangle
        0, 2, 1,  // second Triangle
        4, 0, 1,
        4, 1, 5,
        7, 4, 5,
        7, 5, 6,
        3, 7, 6,
        3, 6, 2,
        4, 7, 3,
        4, 3, 0,
        6, 5, 1,
        6, 1, 2
    };

    static vec3 normals[] = {
            vec3::Forward(), // top right
            vec3::Right(), // bottom right
            vec3::Down(), // bottom left
            vec3::Left(), // top left 
            vec3::Right(), // top right
            vec3::Down(), // bottom right
            vec3::Back(), // bottom left
            vec3::Up()  // top left 
    };

    static vec2 texcoords[] = {
        // texture coords
        vec2{1.0f, 0.0f}, // top right
        vec2{1.0f, 1.0f}, // bottom right
        vec2{0.0f, 1.0f}, // bottom left
        vec2{0.0f, 0.0f}, // top left 
        vec2{1.0f, 0.0f}, // top right
        vec2{1.0f, 1.0f}, // bottom right
        vec2{0.0f, 1.0f}, // bottom left
        vec2{0.0f, 0.0f}, // top left 
    };

    const vec3* Cube::GetVertices() const
    {
        return vertices;
    }

    unsigned int Cube::GetVertexCount() const
    {
        return 8;
    }

    const unsigned int* Cube::GetIndices() const
    {
        return indices;
    }

    unsigned int Cube::GetIndexCount() const
    {
        return 36;
    }

    const vec3* Cube::GetNormals() const
    {
        return normals;
    }

    unsigned int Cube::GetNormalCount() const
    {
        return 8;
    }
}
