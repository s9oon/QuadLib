#pragma once

#include <bgfx/bgfx.h>

struct ImageData {
    int width = 0;
    int height = 0;
    int channels = 0;
    unsigned char* data = nullptr;
};

struct Texture {
    bgfx::TextureHandle handle = BGFX_INVALID_HANDLE;
};

namespace Core {
    extern bgfx::UniformHandle s_texColor;

    Texture loadTexture(const char* path);
    ImageData loadSTB_Image(const char* path);

    bool compileTexture();
}