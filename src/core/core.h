#pragma once

#include <SDL3/SDL.h>
#include <bgfx/bgfx.h>
#include <vector>

struct Vec2 {
	float x, y;
};

struct Transform {
	Vec2 position;
	float rotation;
	Transform(Vec2 position, float rotation) : position(position), rotation(rotation) {};
};

struct Mesh2D {
	std::vector<Vec2> vertices;
	std::vector<uint16_t> indices;
};

namespace Core {
	void updateOrtho(float* ortho, int width, int height);
	bgfx::PlatformData getPlatformData(SDL_Window* window);
}