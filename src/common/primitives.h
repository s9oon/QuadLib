#pragma once
#include "types.h"

namespace QuadLib {
    inline Mesh2D getQuad() {
        return Mesh2D(
            {
                { {-0.5f,  0.5f}, {0.0f, 0.0f} },
                { { 0.5f,  0.5f}, {1.0f, 0.0f} },
                { { 0.5f, -0.5f}, {1.0f, 1.0f} },
                { {-0.5f, -0.5f}, {0.0f, 1.0f} },
            },
            { 0, 1, 2, 2, 3, 0 }
            );
    }

    inline constexpr Transform getOrigin() {
        return Transform({ 0.0f, 0.0f }, 0.0f, { 1.0f, 1.0f });
    }
}