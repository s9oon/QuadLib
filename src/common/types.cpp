#include "types.h"
#include "../core/core.h"
#include "../core/texture.h"
#include <bx/math.h>


Element::~Element() {
    if (loaded) Core::unloadElement(*this);
    if (ownsMesh) delete mesh;
}

ElementUI::ElementUI(Mesh2D* mesh, Transform transform, const char* texturepath)
    : Element(mesh, texturepath), transform(transform) {

    // TODO move out of the constructor / constructor still calls bake
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

Batch::Batch(std::vector<ElementUI*> elements) : elements(elements) {
    // TODO
    // I want to use those texture altas functions to create a png
    // bake the final element's mesh into the uv's and combine all the meshes 
    // its a big task ik but im struggling
}