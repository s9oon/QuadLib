#include "quadlib.h"

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

#include <SDL3/SDL.h>

#include <iostream>

#include <bx/math.h>

#include "../core/core.h"
#include "../core/shader.h"

namespace QuadLib {
    bool running = true;

#ifdef QUADLIB_BGFX_TOOLS
    bool compileShader(Shader& shader) {
        return Core::compileShader(shader);
    }

    void drawElement(Element& element, bgfx::ProgramHandle& program) {
        // 1. Convert mesh to GPU mesh (BAD to do every frame, but works for now)
        GPUMesh2D gpuMesh = Core::loadMesh(*element.mesh);

        bgfx::setVertexBuffer(0, gpuMesh.vbh);
        bgfx::setIndexBuffer(gpuMesh.ibh);

        // 2. Load texture (also BAD to do every frame, but matches your structure)
        bgfx::TextureHandle tex = Core::loadTexture(element.texturepath);

        if (bgfx::isValid(tex))
        {
            bgfx::setTexture(
                0,
                Core::s_texColor,
                tex
            );
        }

        // 3. Submit draw call
        bgfx::submit(Core::VIEW_MAIN, program);
    }
#endif

    void drawElement(Element& element) {
        // TODO
    }

    // Convert color to bgfx
    uint32_t RGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
        return (uint32_t(r) << 24) |
            (uint32_t(g) << 16) |
            (uint32_t(b) << 8) |
            uint32_t(a);
    }

    // initalise quadlib + basic window
	bool initWindow(const char* title, int width, int height) {
        if (!SDL_Init(SDL_INIT_VIDEO)) {
            SDL_Log("SDL init failed: %s", SDL_GetError());
            return false;
        }

        Core::window = SDL_CreateWindow(
            title,
            width,
            height,
            SDL_WINDOW_RESIZABLE
        );

        if (!Core::window) {
            SDL_Log("Window creation failed: %s", SDL_GetError());
            return false;
        }

        bgfx::PlatformData pd = Core::getPlatformData(Core::window);

        bgfx::Init init{};
        init.type = bgfx::RendererType::Count;
        init.resolution.width = width;
        init.resolution.height = height;
        init.resolution.reset = BGFX_RESET_VSYNC;
        init.platformData = pd;

        if (!bgfx::init(init)) {
            std::cout << "BGFX init failed\n";
            return false;
        }

        Core::init();

        Core::window_width = width;
        Core::window_height = height;

        Core::updateOrtho(Core::ortho, width, height);

        bgfx::setDebug(BGFX_DEBUG_TEXT);

        return true;
	}

    // check if window should close
    bool windowShouldClose() {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        return !running;
    }

    void getWindowSize(int& width, int& height) {
        SDL_GetWindowSizeInPixels(Core::window, &width, &height);
    }

    void beginFrame(uint32_t color) {
        getWindowSize(Core::window_width, Core::window_height);

        bgfx::setViewRect(Core::VIEW_MAIN, 0, 0, uint16_t(Core::window_width), uint16_t(Core::window_height));
        clearBackground(color);

        bgfx::setViewTransform(Core::VIEW_MAIN, nullptr, Core::ortho);

        bgfx::touch(Core::VIEW_MAIN);
    }

    void endFrame() {
        bgfx::frame();
    }

    // clear background
    void clearBackground(uint32_t color) {
        bgfx::setViewClear(
            Core::VIEW_MAIN,
            BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH,
            color,
            1.0f,
            0
        );
    }

    void Shutdown() {
    }
}