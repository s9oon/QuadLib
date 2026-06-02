#pragma once

#include <vector>

struct Vec2 {
    float x, y;
    constexpr Vec2(float x, float y) : x(x), y(y) {};
    constexpr Vec2() : x(0.0f), y(0.0f) {};
};

struct Vertex2D {
    Vec2 vertex;
    Vec2 uv;
};

struct Transform {
    Vec2 position;
    float rotation;
    Vec2 scale;

    constexpr Transform() : position(0.0f, 0.0f), rotation(0.0f), scale(1.0f, 1.0f) {};
    constexpr Transform(Vec2 position, float rotation, Vec2 scale) :
        position(position), rotation(rotation), scale(scale) {
    };
};

struct Mesh2D { 
	std::vector<Vertex2D> vertices;
	std::vector<uint16_t> indices;

	Mesh2D(std::vector<Vertex2D> vertices, std::vector<uint16_t> indices) : 
		vertices(vertices), indices(indices) {};
};

struct GPUMesh2D;
struct Texture;

class Element {
public:
    Mesh2D* mesh;
    const char* texturepath;

    bool loaded = false;
    bool ownsMesh = false;

    GPUMesh2D* gpuMesh = nullptr;
    Texture* texture = nullptr;

    Element() : mesh(nullptr), texturepath(nullptr) {}
    Element(Mesh2D* mesh, const char* texturepath) : mesh(mesh), texturepath(texturepath) {};

    ~Element();
};

class ElementWorld : public Element {
public:
    Transform transform;

    ElementWorld(Mesh2D* mesh, Transform transform, const char* texturepath) :
        Element(mesh, texturepath), transform(transform) {
    };
};

class ElementUI : public Element {
public:
    ElementUI(Mesh2D* mesh, Transform transform, const char* texturepath);

private:
    Transform transform;
};

class Batch {
public:
    Element finalelement;
    
    Batch(std::vector<ElementUI*> elements);

private:
    std::vector<ElementUI*> elements;
};
