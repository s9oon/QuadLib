#include "quadlib.h"

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

#include <iostream>

#include <SDL3/SDL.h>

namespace QuadLib {

	bool QuadLib::Init() {

        if (!SDL_Init(SDL_INIT_VIDEO)) {
            std::cout << SDL_GetError() << "\n";
            return false;
        }

        SDL_Window* window = SDL_CreateWindow(
            "QuadLib",
            1280, 720,
            SDL_WINDOW_RESIZABLE
        );

        // SDL native window handle
        SDL_PropertiesID props = SDL_GetWindowProperties(window);

        void* nativeWindow = SDL_GetPointerProperty(props, SDL_PROP_WINDOW_CREATE_WIN32_HWND_POINTER, nullptr);

        bgfx::PlatformData pd{};
        pd.nwh = nativeWindow;

        bgfx::Init init;
        init.type = bgfx::RendererType::Count;
        init.resolution.width = 1280;
        init.resolution.height = 720;
        init.resolution.reset = BGFX_RESET_VSYNC;
        init.platformData = pd;

        if (bgfx::init(init)) {
            return false;
        }

        return true;
	}

    void QuadLib::shutDown() {
        bgfx::shutdown();
        SDL_Quit();
    }
}