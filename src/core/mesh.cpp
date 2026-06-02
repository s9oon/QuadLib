#include "mesh.h"
#include <iostream>

namespace Core {
    /*
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
    */
    GPUMesh2D loadMesh(const Mesh2D& mesh)
    {
        GPUMesh2D gpuMesh{};

        if (mesh.vertices.empty() || mesh.indices.empty())
        {
            std::cout << "[ERROR] Empty mesh passed to loadMesh" << std::endl;
            return gpuMesh;
        }

        const bgfx::Memory* vertexMemory =
            bgfx::copy(mesh.vertices.data(),
                mesh.vertices.size() * sizeof(Vertex2D));

        gpuMesh.vbh = bgfx::createVertexBuffer(vertexMemory, g_VertexLayout);

        const bgfx::Memory* indexMemory =
            bgfx::copy(mesh.indices.data(),
                mesh.indices.size() * sizeof(uint16_t));

        gpuMesh.ibh = bgfx::createIndexBuffer(indexMemory);

        if (!bgfx::isValid(gpuMesh.vbh))
            std::cout << "[FATAL] Invalid vertex buffer" << std::endl;

        if (!bgfx::isValid(gpuMesh.ibh))
            std::cout << "[FATAL] Invalid index buffer" << std::endl;

        return gpuMesh;
    }
}