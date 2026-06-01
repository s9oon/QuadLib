#pragma once

#include <SDL3/SDL.h>
#include <bgfx/bgfx.h>
#include <vector>
#include "../common/types.h"

namespace Core {
	extern bgfx::UniformHandle s_texColor;
	extern bgfx::VertexLayout g_VertexLayout;

	extern uint16_t VIEW_MAIN;
	extern SDL_Window* window;
	extern float ortho[16];
	extern int window_width;
	extern int window_height;

	void init();
	void shutdown();

	void initVertexLayout();

	void updateOrtho(float* ortho, int width, int height);
	bgfx::PlatformData getPlatformData(SDL_Window* window);
}