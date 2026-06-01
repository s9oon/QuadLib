#include "mesh.h"

namespace Core {
    GPUMesh2D loadMesh(const Mesh2D& mesh) {
        GPUMesh2D gpuMesh{};

        // Create vertex buffer
        const bgfx::Memory* vertexMemory = bgfx::copy(
            mesh.vertices.data(),
            static_cast<uint32_t>(mesh.vertices.size() * sizeof(Vertex2D))
        );

        gpuMesh.vbh = bgfx::createVertexBuffer(
            vertexMemory,
            g_VertexLayout
        );

        // Create index buffer
        const bgfx::Memory* indexMemory = bgfx::copy(
            mesh.indices.data(),
            static_cast<uint32_t>(mesh.indices.size() * sizeof(uint16_t))
        );

        gpuMesh.ibh = bgfx::createIndexBuffer(indexMemory);

        return gpuMesh;
    }

    GPUMesh2D::~GPUMesh2D() {
        if (bgfx::isValid(vbh)) {
            bgfx::destroy(vbh);
            vbh = BGFX_INVALID_HANDLE;
        }

        if (bgfx::isValid(ibh)) {
            bgfx::destroy(ibh);
            ibh = BGFX_INVALID_HANDLE;
        }
    }
}