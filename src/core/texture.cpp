#include "texture.h"
#include <filesystem>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "../../assets/stb_image.h"

namespace Core {
	bool compileTexture() {
		// TODO

        return true;
	}

    bgfx::TextureHandle loadTexture(const char* path) {
        // Check if the file exists first.
        if (!std::filesystem::exists(path))
        {
            std::cerr << "[TextureLoader] File not found: "
                << std::filesystem::absolute(path).string()
                << std::endl;

            return BGFX_INVALID_HANDLE;
        }

        ImageData img = loadSTB_Image(path);

        // Check if STB failed to load the image.
        if (!img.data) {
            std::cerr << "[TextureLoader] Failed to load texture: "
                << std::filesystem::absolute(path).string()
                << "\nReason: "
                << (stbi_failure_reason() ? stbi_failure_reason() : "Unknown error")
                << std::endl;

            return BGFX_INVALID_HANDLE;
        }

        const bgfx::Memory* mem = bgfx::copy(
            img.data,
            img.width * img.height * 4
        );

        bgfx::TextureHandle tex = bgfx::createTexture2D(
            static_cast<uint16_t>(img.width),
            static_cast<uint16_t>(img.height),
            false,
            1,
            bgfx::TextureFormat::RGBA8,
            BGFX_TEXTURE_NONE,
            mem
        );

        stbi_image_free(img.data);

        return tex;
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