#pragma once

#include "../../assets/stb_image.h"
#include "../../assets/stb_rect_pack.h"
#include "../../assets/stb_image_write.h"
#include <bgfx/bgfx.h>

struct ImageData {
    int width = 0;
    int height = 0;
    int channels = 0;
    unsigned char* data = nullptr;
};

struct TextureAtlas {
    int width = 1024;
    int height = 1024;

    std::vector<unsigned char> pixels;

    TextureAtlas() {
        pixels.resize(width * height * 4, 0);
    }
};

struct Texture {
    bgfx::TextureHandle handle = BGFX_INVALID_HANDLE;
};

namespace Core {
    extern bgfx::UniformHandle s_texColor;

    // Need getRect done
    stbrp_rect getRect(const char* path, int id);


    bool packRect(std::vector<stbrp_rect>& rects, TextureAtlas& atlas);

    bool writeImage(std::vector<const char*> paths, const char* submission, TextureAtlas& atlas);
    Texture loadTexture(const char* path);
    ImageData loadSTB_Image(const char* path);

    bool compileTexture();
}