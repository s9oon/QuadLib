#include "types.h"
#include "../core/core.h"
#include <bx/math.h>

Element::~Element() {
    if (loaded) Core::unloadElement(*this);
    if (ownsMesh) delete mesh;
}

ElementUI::ElementUI(Mesh2D* mesh, Transform transform, const char* texturepath)
    : Element(nullptr, texturepath)
{
    Mesh2D* baked = new Mesh2D(*mesh);

    float cosR = bx::cos(transform.rotation);
    float sinR = bx::sin(transform.rotation);

    for (auto& v : baked->vertices) {
        float x = v.vertex.x * transform.scale.x;
        float y = v.vertex.y * transform.scale.y;
        float rx = x * cosR - y * sinR;
        float ry = x * sinR + y * cosR;
        v.vertex.x = rx + transform.position.x;
        v.vertex.y = ry + transform.position.y;
    }

    this->mesh = baked;
    this->ownsMesh = true;
}

Batch::Batch(std::vector<ElementUI*> elements) {
    // needs to 
}