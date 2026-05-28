#include "core.h"

#include <bx/math.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <SDL3/SDL.h>

namespace Core {
    bgfx::VertexLayout g_VertexLayout;

    void initVertexLayout() {
        g_VertexLayout
            .begin()
            .add(bgfx::Attrib::Position, 2, bgfx::AttribType::Float)
            .add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
            .end();
    }

    GPUMesh2D loadMesh(const Mesh2D& mesh) {
        GPUMesh2D gpuMesh{};

        // Create vertex buffer
        const bgfx::Memory* vertexMemory = bgfx::copy(
            mesh.vertices.data(),
            static_cast<uint32_t>(mesh.vertices.size() * sizeof(Vertex2D))
        );

        gpuMesh.vbh = bgfx::createVertexBuffer(
            vertexMemory,
            g_VertexLayout
        );

        // Create index buffer
        const bgfx::Memory* indexMemory = bgfx::copy(
            mesh.indices.data(),
            static_cast<uint32_t>(mesh.indices.size() * sizeof(uint16_t))
        );

        gpuMesh.ibh = bgfx::createIndexBuffer(indexMemory);

        return gpuMesh;
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

}