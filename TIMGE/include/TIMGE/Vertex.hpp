#ifndef VERTEX_HPP
#define VERTEX_HPP

namespace TIMGE
{
    struct Vertex
    {
        float x;
        float y;

        Vertex(float x, float y);
    };

    struct ColoredVertex
    {
        float x;
        float y;

        float r;
        float g;
        float b;
        float a;

        ColoredVertex(float x, float y, float r, float g, float b, float a);
    };

    struct TexturedVertex
    {
        float x;
        float y;

        float r;
        float g;
        float b;
        float a;

        float u;
        float v;

        TexturedVertex(float x, float y, float r, float g, float b, float a, float u, float v);
    };
}

#endif // VERTEX_HPP
