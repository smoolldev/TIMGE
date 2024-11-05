#include "TIMGE/Vertex.hpp"

namespace TIMGE
{
    Vertex::Vertex(float x, float y)
     : x{x},
       y{y}
    {}

    ColoredVertex::ColoredVertex(float x, float y, float r, float g, float b, float a)
     : x{x},
       y{y},
       r{r},
       g{g},
       b{b},
       a{a}
    {}

    TexturedVertex::TexturedVertex(float x, float y, float r, float g, float b, float a, float u, float v)
     : x{x},
       y{y},
       r{r},
       g{g},
       b{b},
       a{a},
       u{u},
       v{v}
    {}
}
