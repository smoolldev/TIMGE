#ifndef VERTEX_HPP
#define VERTEX_HPP

namespace TIMGE
{
    struct Vertex
    {
        float x;
        float y;
        float z;

        Vertex(float x, float y, float z);
    };

    struct ColoredVertex
    {
        float x;
        float y;
        float z;

        float r;
        float g;
        float b;

        ColoredVertex(float x, float y, float z, float r, float g, float b);
    };

    struct TexturedVertex
    {
        float x;
        float y;
        float z;

        float r;
        float g;
        float b;

        float u;
        float v;

        TexturedVertex(float x, float y, float z, float r, float g, float b, float u, float v);
    };
}

#endif // VERTEX_HPP
