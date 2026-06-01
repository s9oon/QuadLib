#include "core.h"

#include <bx/math.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <SDL3/SDL.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../../assets/stb_image.h"

GPUMesh2D::~GPUMesh2D() {
    if (bgfx::isValid(vbh))
    {
        bgfx::destroy(vbh);
        vbh = BGFX_INVALID_HANDLE;
    }

    if (bgfx::isValid(ibh))
    {
        bgfx::destroy(ibh);
        ibh = BGFX_INVALID_HANDLE;
    }
}

namespace Core {
    bgfx::VertexLayout g_VertexLayout;
    bgfx::UniformHandle s_texColor = BGFX_INVALID_HANDLE;

    SDL_Window* window = nullptr;
    float ortho[16];
    int window_width = 0;
    int window_height = 0;

    void initVertexLayout() {
        g_VertexLayout
            .begin()
            .add(bgfx::Attrib::Position, 2, bgfx::AttribType::Float)
            .add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
            .end();
    }

    // simple init function
    void init() {
        initVertexLayout();
        s_texColor = bgfx::createUniform("s_texColor", bgfx::UniformType::Sampler);
    }

    bgfx::TextureHandle loadTexture(const char* path) {
        // TODO
    }

    void updateOrtho(float* ortho, int width, int height) {
        bx::mtxOrtho(
            ortho,
            0.0f, float(width),
            float(height), 0.0f,
            0.0f, 100.0f,
            0.0f,
            bgfx::getCaps()->homogeneousDepth
        );
    }

    bgfx::PlatformData getPlatformData(SDL_Window* window) {
        bgfx::PlatformData pd{};

        SDL_PropertiesID props = SDL_GetWindowProperties(window);

#if defined(_WIN32)

        pd.nwh = SDL_GetPointerProperty(
            props,
            SDL_PROP_WINDOW_WIN32_HWND_POINTER,
            nullptr
        );

#elif defined(__linux__)

        if (SDL_strcmp(SDL_GetCurrentVideoDriver(), "wayland") == 0)
        {
            pd.ndt = SDL_GetPointerProperty(
                props,
                SDL_PROP_WINDOW_WAYLAND_DISPLAY_POINTER,
                nullptr
            );

            pd.nwh = SDL_GetPointerProperty(
                props,
                SDL_PROP_WINDOW_WAYLAND_SURFACE_POINTER,
                nullptr
            );
        }
        else
        {
            pd.ndt = SDL_GetPointerProperty(
                props,
                SDL_PROP_WINDOW_X11_DISPLAY_POINTER,
                nullptr
            );

            pd.nwh = (void*)(uintptr_t)SDL_GetNumberProperty(
                props,
                SDL_PROP_WINDOW_X11_WINDOW_NUMBER,
                0
            );
        }

#elif defined(__APPLE__)

        pd.nwh = SDL_GetPointerProperty(
            props,
            SDL_PROP_WINDOW_COCOA_WINDOW_POINTER,
            nullptr
        );

#endif

        return pd;
    }

    void shutdown() {
        if (bgfx::isValid(s_texColor)) {
            bgfx::destroy(s_texColor);
            s_texColor = BGFX_INVALID_HANDLE;
        }

        bgfx::shutdown();

        SDL_DestroyWindow(window);
        SDL_Quit();
    }
}