#ifndef VERTEX_HPP
#define VERTEX_HPP

namespace TIMGE
{
    struct Vertex
    {
        float x;
        float y;

        float r;
        float g;
        float b;
        float a;

        float u;
        float v;

        Vertex(float x, float y);
        Vertex(float x, float y, float r, float g, float b, float a);
        Vertex(float x, float y, float r, float g, float b, float a, float u, float v);
    };
}

#endif // VERTEX_HPP
