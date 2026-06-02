#include "textureatlas.h"

#include <cstring>
#include <iostream>

namespace Core {

    stbrp_rect getRect(const char* path, int id)
    {
        stbrp_rect rect{};

        int width;
        int height;
        int channels;

        if (!stbi_info(path, &width, &height, &channels))
        {
            std::cerr
                << "Failed to read image info: "
                << path
                << "\n";

            rect.id = id;
            rect.w = 0;
            rect.h = 0;

            return rect;
        }

        rect.id = id;
        rect.w = static_cast<stbrp_coord>(width);
        rect.h = static_cast<stbrp_coord>(height);

        return rect;
    }

    std::unordered_map<int, AtlasData> packRects(std::vector<stbrp_rect>& rects)
    {
        stbrp_context context;

        std::vector<stbrp_node> nodes(atlasWidth);

        stbrp_init_target(
            &context,
            atlasWidth,
            atlasHeight,
            nodes.data(),
            static_cast<int>(nodes.size())
        );

        stbrp_pack_rects(
            &context,
            rects.data(),
            static_cast<int>(rects.size())
        );

        std::unordered_map<int, AtlasData> result;

        bool allPacked = true;

        for (const stbrp_rect& rect : rects)
        {
            if (!rect.was_packed)
            {
                allPacked = false;

                std::cerr
                    << "Failed to pack texture id "
                    << rect.id
                    << " (" << rect.w
                    << "x" << rect.h
                    << ")\n";

                continue;
            }

            AtlasData data{};

            data.id = rect.id;

            data.u0 =
                rect.x / static_cast<float>(atlasWidth);

            data.v0 =
                rect.y / static_cast<float>(atlasHeight);

            data.u1 =
                (rect.x + rect.w) /
                static_cast<float>(atlasWidth);

            data.v1 =
                (rect.y + rect.h) /
                static_cast<float>(atlasHeight);

            result[data.id] = data;
        }

        if (!allPacked)
        {
            std::cerr
                << "Atlas size "
                << atlasWidth
                << "x"
                << atlasHeight
                << " is too small.\n";
        }

        return result;
    }

    TextureAtlas generateAtlasImageData(
        const std::vector<const char*>& paths)
    {
        TextureAtlas atlas{};

        atlas.width = atlasWidth;
        atlas.height = atlasHeight;
        atlas.channels = 4;

        atlas.data = new unsigned char[
            atlas.width *
                atlas.height *
                atlas.channels
        ]();

        std::vector<stbrp_rect> rects;
        rects.reserve(paths.size());

        for (size_t i = 0; i < paths.size(); ++i)
        {
            rects.push_back(
                getRect(
                    paths[i],
                    static_cast<int>(i)
                )
            );
        }

        atlas.regions = packRects(rects);

        for (size_t i = 0; i < paths.size(); ++i)
        {
            const stbrp_rect& rect = rects[i];

            if (!rect.was_packed)
                continue;

            int width;
            int height;
            int channels;

            unsigned char* src =
                stbi_load(
                    paths[i],
                    &width,
                    &height,
                    &channels,
                    4
                );

            if (!src)
            {
                std::cerr
                    << "Failed to load image: "
                    << paths[i]
                    << "\n";

                continue;
            }

            for (int y = 0; y < height; ++y)
            {
                unsigned char* dstRow =
                    atlas.data +
                    (
                        (
                            (rect.y + y)
                            * atlas.width
                            )
                        + rect.x
                        ) * 4;

                unsigned char* srcRow =
                    src + (y * width * 4);

                memcpy(
                    dstRow,
                    srcRow,
                    width * 4
                );
            }

            stbi_image_free(src);
        }

        return atlas;
    }

    void remapUVs(Mesh2D& mesh, const AtlasData& data) {
        float du = data.u1 - data.u0;
        float dv = data.v1 - data.v0;

        for (auto& vertex : mesh.vertices) {
            vertex.uv.x = data.u0 + vertex.uv.x * du;
            vertex.uv.y = data.v0 + vertex.uv.y * dv;
        }
    }

    bool saveAtlasPNG(
        const TextureAtlas& atlas,
        const char* path
    )
    {
        if (!atlas.data)
            return false;

        bool success =
            stbi_write_png(
                path,
                atlas.width,
                atlas.height,
                atlas.channels,
                atlas.data,
                atlas.width * atlas.channels
            ) != 0;

        if (success)
        {
            std::cout
                << "Saved atlas to: "
                << path
                << "\n";
        }
        else
        {
            std::cerr
                << "Failed to save atlas to: "
                << path
                << "\n";
        }

        return success;
    }
}