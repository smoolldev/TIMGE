#include "TIMGE/Vertex.hpp"

namespace TIMGE
{
    Vertex::Vertex(float x, float y, float z)
     : x{x},
       y{y},
       z{z}
    {}

    ColoredVertex::ColoredVertex(float x, float y, float z, float r, float g, float b)
     : x{x},
       y{y},
       z{z},
       r{r},
       g{g},
       b{b}
    {}

    TexturedVertex::TexturedVertex(float x, float y, float z, float r, float g, float b, float u, float v)
     : x{x},
       y{y},
       z{z},
       r{r},
       g{g},
       b{b},
       u{u},
       v{v}
    {}
}
