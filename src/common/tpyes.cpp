#include "types.h"
#include "../core/core.h"

Element::~Element() {
    if (loaded) Core::unloadElement(*this);
    if (ownsMesh) delete mesh;
}

ElementUI::ElementUI() {

    // bake transform into a new mesh so we don't modify the original
    Mesh2D* baked = new Mesh2D(*mesh);

    float cosR = bx::cos(transform.rotation);
    float sinR = bx::sin(transform.rotation);

    for (auto& v : baked->vertices) {
        // scale
        float x = v.vertex.x * transform.scale.x;
        float y = v.vertex.y * transform.scale.y;
        // rotate
        float rx = x * cosR - y * sinR;
        float ry = x * sinR + y * cosR;
        // translate
        v.vertex.x = rx + transform.position.x;
        v.vertex.y = ry + transform.position.y;
    }

    this->mesh = baked;
    this->ownsMesh = true;
}

Batch::Batch(std::vector<ElementUI*> elements) {
    // needs to 
}