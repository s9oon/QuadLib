#pragma once

#include <vector>

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
	Vec2 scale;

	Transform(Vec2 position, float rotation, Vec2 scale) : 
		position(position), rotation(rotation), scale(scale) {};
};

struct Mesh2D { 
	std::vector<Vertex2D> vertices;
	std::vector<uint16_t> indices;

	Mesh2D(std::vector<Vertex2D> vertices, std::vector<uint16_t> indices) : 
		vertices(vertices), indices(indices) {};
};

class Element {
public:
	Mesh2D* mesh;
	Transform transform;
	const char* texturepath; 

	Element(Mesh2D* mesh, const Transform& transform, const char* texturepath) :
		mesh(mesh), transform(transform), texturepath(texturepath) {};
};