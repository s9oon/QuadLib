#pragma once

#include <vector>

enum PresetShaders {
	BASIC,
};

struct Vec2 {
	float x, y;
};

struct Vertex2D {
	Vec2 vertex;
	Vec2 uv;
};

struct Transform {
	Vec2 position;
	float rotation;

	Transform(Vec2 position, float rotation) : position(position), rotation(rotation) {};
};

struct Mesh2D {
	std::vector<Vertex2D> vertices;
	std::vector<uint16_t> indices;

	Mesh2D(std::vector<Vertex2D> vertices, std::vector<uint16_t> indices) : vertices(vertices), indices(indices) {};
};