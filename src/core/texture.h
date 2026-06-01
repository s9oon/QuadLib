#pragma once

#include <bgfx/bgfx.h>

struct ImageData
{
    int width = 0;
    int height = 0;
    int channels = 0;
    unsigned char* data = nullptr;
};

namespace Core {
    extern bgfx::UniformHandle s_texColor;
	bgfx::TextureHandle loadTexture(const char* path);
    ImageData loadSTB_Image(const char* path);
	bool compileTexture();
}