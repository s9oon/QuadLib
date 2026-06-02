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

    Texture loadTexture(const char* path) {
        if (!std::filesystem::exists(path)) {
            std::cerr << "[TextureLoader] File not found: "
                << std::filesystem::absolute(path).string()
                << std::endl;

            return {};
        }

        ImageData img = loadSTB_Image(path);

        if (!img.data) {
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