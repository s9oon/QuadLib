#pragma once

#include "texture.h"
#include "core.h"

#include <unordered_map>
#include <vector>

struct AtlasData {
    int id;

    float u0;
    float v0;
    float u1;
    float v1;
};

struct TextureAtlas : ImageData {
    std::unordered_map<int, AtlasData> regions;
};

namespace Core {
    stbrp_rect getRect(const char* path, int id);

    std::unordered_map<int, AtlasData> packRects(std::vector<stbrp_rect>& rects);

    TextureAtlas generateAtlasImageData(const std::vector<const char*>& paths);

    bool saveAtlasPNG(const TextureAtlas& atlas, const char* path);
}