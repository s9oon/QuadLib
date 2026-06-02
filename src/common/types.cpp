#include "types.h"
#include <bx/math.h>
#include <string>
#include "../core/textureatlas.h"

namespace Core {
    void bakeVertices(Mesh2D& mesh, Transform transform);
    void unloadElement(Element& element);
}

ElementUI::ElementUI(Mesh2D mesh, Transform transform, const char* texturepath) : Element(std::move(mesh), texturepath),
transform(transform) {
    Core::bakeVertices(this->mesh, transform);
}

Element::~Element() {
    Core::unloadElement(*this);
}

Batch::Batch(std::vector<ElementUI*> elements) {

    // Count and reserve
    size_t totalVertices = 0;
    size_t totalIndices = 0;

    for (auto* e : elements) {
        totalVertices += e->mesh.vertices.size();
        totalIndices += e->mesh.indices.size();
    }

    finalelement.mesh.vertices.reserve(totalVertices);
    finalelement.mesh.indices.reserve(totalIndices);


    TextureAtlas atlas;

    std::vector<const char*> atlasTextures;
    std::unordered_map<std::string, uint32_t> textureRegions;

    for (auto* e : elements)
    {
        std::string path = e->texturepath;

        if (!textureRegions.contains(path))
        {
            textureRegions[path] = atlasTextures.size();
            atlasTextures.push_back(e->texturepath);
        }
    }

    atlas = Core::generateAtlasImageData(atlasTextures);

    uint16_t vertexOffset = 0;

    for (auto* e : elements)
    {
        Mesh2D mesh = e->mesh;

        uint32_t regionIndex =
            textureRegions[e->texturepath];

        Core::remapUVs(mesh, atlas.regions[regionIndex]);

        finalelement.mesh.vertices.insert(
            finalelement.mesh.vertices.end(),
            mesh.vertices.begin(),
            mesh.vertices.end()
        );

        for (uint16_t idx : mesh.indices)
        {
            finalelement.mesh.indices.push_back(
                idx + vertexOffset
            );
        }

        vertexOffset += static_cast<uint16_t>(
            mesh.vertices.size()
            );
    }

    Core::saveAtlasPNG(atlas, QUADLIB_ROOT "/assets/generated_atlas.png");

    finalelement.texturepath = QUADLIB_ROOT "/assets/generated_atlas.png";
}