#pragma once

#include <SDL3/SDL.h>
#include <bgfx/bgfx.h>
#include <vector>
#include "../common/types.h"
#include "texture.h"
#include "textureatlas.h"

namespace Core {
	extern uint16_t VIEW_MAIN;
	extern SDL_Window* window;
	extern float ortho[16];
	extern int window_width;
	extern int window_height;
	inline constexpr int atlasWidth = 2048;
	inline constexpr int atlasHeight = 2048;

	void init();
	void shutdown();

	void initVertexLayout();
	void loadElement(Element& element);
	void unloadElement(Element& element);
	void updateOrtho(float* ortho, int width, int height);
	bgfx::PlatformData getPlatformData(SDL_Window* window);
}