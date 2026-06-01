#pragma once

#include <bgfx/bgfx.h>

struct Texture {
	bgfx::TextureHandle handle = BGFX_INVALID_HANDLE;
};

namespace Core {
	Texture loadTexture(const char* path);
	bool compileTexture();
}