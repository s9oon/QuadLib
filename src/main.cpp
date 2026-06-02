#include "api/quadlib.h"
#include <iostream>

#define LOG(x) std::cout << "[LOG] " << x << std::endl;

int main()
{
    QuadLib::initWindow("batched ui", 1280, 720);

    Mesh2D quad = QuadLib::getQuad();

    Vec2 center(640.0f, 360.0f);
    float spacing = 120.0f;

    // ?? CENTER (circle)
    ElementUI circle(
        quad,
        Transform(
            center,
            0.0f,
            Vec2(200.0f, 200.0f)
        ),
        QUADLIB_ROOT "/assets/circle2.png"
    );

    // ?? ABOVE circle (triangle on top)
    ElementUI triangle(
        quad,
        Transform(
            Vec2(center.x, center.y - spacing),
            0.0f,
            Vec2(200.0f, 200.0f)
        ),
        QUADLIB_ROOT "/assets/triangle2.png"
    );

    // ? RIGHT of circle (square)
    ElementUI square(
        quad,
        Transform(
            Vec2(center.x + spacing, center.y),
            0.0f,
            Vec2(200.0f, 200.0f)
        ),
        QUADLIB_ROOT "/assets/square2.png"
    );

    std::vector<ElementUI*> elements = { &circle, &triangle, &square };

    Batch uiBatch(elements);

    bgfx::ProgramHandle basic = Core::getProgram(
        QUADLIB_ROOT "/assets/shaders/compiled/vs_basic.bin",
        QUADLIB_ROOT "/assets/shaders/compiled/fs_basic.bin"
    );

    while (!QuadLib::windowShouldClose())
    {
        QuadLib::beginFrame(QuadLib::RGBA(255, 255, 0, 255));

        QuadLib::drawElement(uiBatch.finalelement, basic);

        QuadLib::endFrame();
    }

    QuadLib::Shutdown();
}