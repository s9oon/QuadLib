#pragma once

#include <SDL3/SDL.h>
#include <bgfx/bgfx.h>

namespace Core {
	void updateOrtho(float* ortho, int width, int height);
	bgfx::PlatformData getPlatformData(SDL_Window* window);
}