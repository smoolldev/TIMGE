#include "TIMGE/Vertex.hpp"

namespace TIMGE
{
    Vertex::Vertex(float x, float y)
     : x{x},
       y{y},
       r{-2.0},
       g{-2.0},
       b{-2.0},
       a{-2.0},
       u{-2.0},
       v{-2.0}
    {}

    Vertex::Vertex(float x, float y, float r, float g, float b, float a)
     : x{x},
       y{y},
       r{r},
       g{g},
       b{b},
       a{a},
       u{-2.0},
       v{-2.0}
    {}

    Vertex::Vertex(float x, float y, float r, float g, float b, float a, float u, float v)
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
