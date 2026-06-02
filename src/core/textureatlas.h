#pragma once

#include "texture.h"
#include "../common/types.h"

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
    inline constexpr int atlasWidth = 2048;
    inline constexpr int atlasHeight = 2048;
    stbrp_rect getRect(const char* path, int id);

    std::unordered_map<int, AtlasData> packRects(std::vector<stbrp_rect>& rects);

    TextureAtlas generateAtlasImageData(const std::vector<const char*>& paths);

    void remapUVs(Mesh2D& mesh, const AtlasData& data);

    bool saveAtlasPNG(const TextureAtlas& atlas, const char* path);
}