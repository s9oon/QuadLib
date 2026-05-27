#pragma once

#include <SDL3/SDL.h>
#include <bgfx/bgfx.h>
#include <vector>

enum PresetShaders {
	BASIC,
};

std::vector<PresetShaders> preset_shaders;

namespace Core {
	void updateOrtho(float* ortho, int width, int height);
	bgfx::PlatformData getPlatformData(SDL_Window* window);
}