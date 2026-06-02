#include <filesystem>
#include <iostream>

#define STB_RECT_PACK_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "texture.h"


namespace Core {
	bool compileTexture() {
		// TODO forget this

        return true;
	}

    stbrp_rect getRect(const char* path, int id) {
        ImageData img = loadSTB_Image(path);

        if (!img.data) { return {}; }

        stbrp_rect rect{};
        rect.id = id;
        rect.w = img.width;
        rect.h = img.height;

        stbi_image_free(img.data);

        return rect;
    }

    bool packRect(std::vector<stbrp_rect>& rects, TextureAtlas& atlas) {
        std::vector<stbrp_node> nodes(atlas.width);

        stbrp_context ctx;

        stbrp_init_target(
            &ctx,
            atlas.width,
            atlas.height,
            nodes.data(),
            atlas.width
        );

        int success = stbrp_pack_rects(
            &ctx,
            rects.data(),
            (int)rects.size()
        );

        return success == 1;
    }

    bool writeImage(std::vector<const char*> paths, const char* submission, TextureAtlas& atlas) {
        // loop through paths and give custom id's
        // call pack rect
        // then do something idk really what but just make a new png file at submissions location

        // chatgpt's response
        std::cout << "[Atlas] Output: " << submission << "\n";
        std::cout << "[Atlas] Images: " << paths.size() << "\n";

        const int atlasW = atlas.width;
        const int atlasH = atlas.height;

        atlas.pixels.clear();
        atlas.pixels.resize(
            static_cast<size_t>(atlasW) *
            static_cast<size_t>(atlasH) * 4,
            0
        );

        std::vector<stbrp_rect> rects;
        rects.reserve(paths.size());

        // ----------------------------
        // Load metadata
        // ----------------------------
        std::cout << "[Atlas] Loading image sizes...\n";

        for (int i = 0; i < static_cast<int>(paths.size()); i++)
        {
            std::cout << "  -> Loading: " << paths[i] << "\n";

            ImageData img = loadSTB_Image(paths[i]);

            if (!img.data)
            {
                std::cout << "  !! FAILED to load: " << paths[i] << "\n";
                return false;
            }

            std::cout
                << "     size: "
                << img.width
                << "x"
                << img.height
                << "\n";

            stbrp_rect rect{};
            rect.id = i;
            rect.w = img.width;
            rect.h = img.height;

            rects.push_back(rect);

            stbi_image_free(img.data);
        }

        // ----------------------------
        // Packing
        // ----------------------------
        std::cout << "[Atlas] Packing rectangles...\n";

        std::vector<stbrp_node> nodes(atlasW);
        stbrp_context ctx;

        stbrp_init_target(
            &ctx,
            atlasW,
            atlasH,
            nodes.data(),
            static_cast<int>(nodes.size())
        );

        int success = stbrp_pack_rects(
            &ctx,
            rects.data(),
            static_cast<int>(rects.size())
        );

        if (!success)
        {
            std::cout << "!! PACKING FAILED (atlas too small)\n";
            return false;
        }

        std::cout << "[Atlas] Packing complete.\n";

        // ----------------------------
        // Build pixel atlas
        // ----------------------------
        std::cout << "[Atlas] Building pixel buffer...\n";

        for (int i = 0; i < static_cast<int>(paths.size()); i++)
        {
            if (!rects[i].was_packed)
            {
                std::cout << "  !! Not packed: " << paths[i] << "\n";
                continue;
            }

            std::cout
                << "  -> Placing: "
                << paths[i]
                << " at ("
                << rects[i].x
                << ", "
                << rects[i].y
                << ")\n";

            ImageData img = loadSTB_Image(paths[i]);

            if (!img.data)
            {
                std::cout << "  !! Failed reload: " << paths[i] << "\n";
                continue;
            }

            if (rects[i].x + img.width > atlasW ||
                rects[i].y + img.height > atlasH)
            {
                std::cout
                    << "  !! Out of bounds placement: "
                    << paths[i]
                    << "\n";

                stbi_image_free(img.data);
                continue;
            }

            for (int y = 0; y < img.height; y++)
            {
                for (int x = 0; x < img.width; x++)
                {
                    const size_t src =
                        static_cast<size_t>(
                            (y * img.width + x) * 4
                            );

                    const size_t dst =
                        static_cast<size_t>(
                            ((rects[i].y + y) * atlasW +
                                (rects[i].x + x)) * 4
                            );

                    if (dst + 3 >= atlas.pixels.size())
                    {
                        std::cout
                            << "  !! BAD DST INDEX: "
                            << dst
                            << "\n";

                        stbi_image_free(img.data);
                        return false;
                    }

                    atlas.pixels[dst + 0] = img.data[src + 0];
                    atlas.pixels[dst + 1] = img.data[src + 1];
                    atlas.pixels[dst + 2] = img.data[src + 2];
                    atlas.pixels[dst + 3] = img.data[src + 3];
                }
            }

            stbi_image_free(img.data);
        }

        // ----------------------------
        // Write PNG
        // ----------------------------
        std::cout << "[Atlas] Writing PNG...\n";

        int result = stbi_write_png(
            submission,
            atlasW,
            atlasH,
            4,
            atlas.pixels.data(),
            atlasW * 4
        );

        if (!result)
        {
            std::cout << "!! Failed to write PNG\n";
            return false;
        }

        std::cout << "[Atlas] Done!\n";

        return true;
    }

    Texture loadTexture(const char* path) {
        if (!std::filesystem::exists(path))
        {
            std::cerr << "[TextureLoader] File not found: "
                << std::filesystem::absolute(path).string()
                << std::endl;

            return {};
        }

        ImageData img = loadSTB_Image(path);

        if (!img.data)
        {
            std::cerr << "[TextureLoader] Failed to load texture: "
                << path << std::endl;

            return {};
        }

        const bgfx::Memory* mem = bgfx::copy(
            img.data,
            img.width * img.height * 4
        );

        Texture texture;

        texture.handle = bgfx::createTexture2D(
            static_cast<uint16_t>(img.width),
            static_cast<uint16_t>(img.height),
            false,
            1,
            bgfx::TextureFormat::RGBA8,
            BGFX_TEXTURE_NONE,
            mem
        );

        stbi_image_free(img.data);

        return texture;
    }

    ImageData loadSTB_Image(const char* path) {
        ImageData img;

        img.data = stbi_load(
            path,
            &img.width,
            &img.height,
            &img.channels,
            4 // force RGBA
        );

        img.channels = 4;

        return img; // ownership of data is returned
    }
}