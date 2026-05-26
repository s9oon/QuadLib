#include "quadlib.h"

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

#include <iostream>

#include <SDL3/SDL.h>
#include <bx/math.h>

#include "../core/core.h"

namespace QuadLib {
    static constexpr uint16_t VIEW_MAIN = 0;
    static SDL_Window* window = nullptr;
    static float ortho[16];
    static int window_width;
    static int window_height;
    bool m_running = true;

    // Convert color to bgfx
    uint32_t RGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
        return (uint32_t(r) << 24) |
            (uint32_t(g) << 16) |
            (uint32_t(b) << 8) |
            uint32_t(a);
    }

    // initalise quadlib + basic window
	bool initWindow(const char* title, int width, int height) {
        window_width = width;
        window_height = height;

        if (!SDL_Init(SDL_INIT_VIDEO)) {
            std::cout << SDL_GetError() << "\n";
            return false;
        }

        window = SDL_CreateWindow(
            title,
            width, height,
            SDL_WINDOW_RESIZABLE
        );

        if (!window) {
            std::cout << SDL_GetError() << "\n";
            return false;
        }

        // SDL native window handle
        SDL_PropertiesID props = SDL_GetWindowProperties(window);

        // not cross platform
        void* nativeWindow = SDL_GetPointerProperty(props, SDL_PROP_WINDOW_WIN32_HWND_POINTER, nullptr);

        bgfx::PlatformData pd{};
        pd.nwh = nativeWindow;

        // initalise bgfx
        bgfx::Init init;
        init.type = bgfx::RendererType::Count;
        init.resolution.width = width;
        init.resolution.height = height;
        init.resolution.reset = BGFX_RESET_VSYNC;
        init.platformData = pd;

        if (!bgfx::init(init)) {
            std::cout << "BGFX init failed\n";
            return false;
        }

        Core::updateOrtho(ortho, window_width, window_height);

        return true;
	}

    // check if window should close
    bool windowShouldClose() {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                m_running = false;
            }
        }

        return !m_running;
    }

    void getWindowSize(int& width, int& height) {
        SDL_GetWindowSizeInPixels(window, &width, &height);
    }

    void beginFrame(uint32_t color) {

        getWindowSize(window_width, window_height);

        bgfx::setViewRect(VIEW_MAIN, 0, 0, uint16_t(window_width), uint16_t(window_height));
        clearBackground(color);

        bgfx::setViewTransform(VIEW_MAIN, nullptr, ortho);

        bgfx::touch(VIEW_MAIN);
    }

    void endFrame() {
        bgfx::frame();
    }

    // clear background
    void clearBackground(uint32_t color) {
        bgfx::setViewClear(
            VIEW_MAIN,
            BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH,
            color,
            1.0f,
            0
        );
    }

    void Shutdown() {
        bgfx::shutdown();
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
}