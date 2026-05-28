#pragma once

#include <SDL3/SDL.h>
#include <bgfx/bgfx.h>
#include <vector>
#include "../common/types.h"


struct GPUMesh2D {
	bgfx::VertexBufferHandle vbh;
	bgfx::IndexBufferHandle ibh;
};

namespace Core {
	extern bgfx::VertexLayout g_VertexLayout;

	void init();

	void initVertexLayout();
	GPUMesh2D loadMesh(const Mesh2D& mesh);

	bgfx::TextureHandle loadSTBTexture(const char* path);

	bgfx::TextureHandle loadCompiledTexture(const char* path);

	void updateOrtho(float* ortho, int width, int height);
	bgfx::PlatformData getPlatformData(SDL_Window* window);
}