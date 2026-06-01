#include "texture.h"

namespace Core {
	bool compileTexture() {
		// TODO
	}

    bgfx::TextureHandle loadTexture(const char* path) {
        ImageData img = loadSTB_Image(path);

        if (!img.data)
            return BGFX_INVALID_HANDLE;

        const bgfx::Memory* mem = bgfx::copy(
            img.data,
            img.width * img.height * 4
        );

        bgfx::TextureHandle tex = bgfx::createTexture2D(
            (uint16_t)img.width,
            (uint16_t)img.height,
            false,
            1,
            bgfx::TextureFormat::RGBA8,
            BGFX_TEXTURE_NONE,
            mem
        );

        stbi_image_free(img.data);

        return tex;
    }

    ImageData loadSTB_Image(const char* path)
    {
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