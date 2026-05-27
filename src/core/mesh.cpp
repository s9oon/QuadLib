#include "mesh.h"

#include <bgfx/bgfx.h>

namespace {
    bgfx::VertexLayout VertexLayout;
    bool layoutInitialized = false;

    void initLayout()
    {
        if (layoutInitialized)
            return;

        VertexLayout
            .begin()
            .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
            .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
            .add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
            .end();

        layoutInitialized = true;
    }
}

struct Mesh2D::Impl {
    bgfx::VertexBufferHandle vbh;
    bgfx::IndexBufferHandle ibh;

    uint32_t indexCount = 0;
};

Mesh2D::Mesh2D()
{
    m_impl = new Impl();

    m_impl->vbh = BGFX_INVALID_HANDLE;
    m_impl->ibh = BGFX_INVALID_HANDLE;
    m_impl->indexCount = 0;
}

Mesh2D::~Mesh2D()
{
    Destroy();

    delete m_impl;
    m_impl = nullptr;
}

bool Mesh2D::Create(
    const std::vector<Vertex2D>& vertices,
    const std::vector<uint16_t>& indices
) {
    initLayout();

    Destroy();

    const bgfx::Memory* vmem = bgfx::copy(
        vertices.data(),
        uint32_t(vertices.size() * sizeof(Vertex2D))
    );

    m_impl->vbh = bgfx::createVertexBuffer(
        vmem,
        VertexLayout
    );

    const bgfx::Memory* imem = bgfx::copy(
        indices.data(),
        uint32_t(indices.size() * sizeof(uint16_t))
    );

    m_impl->ibh = bgfx::createIndexBuffer(imem);

    m_impl->indexCount = (uint32_t)indices.size();

    return bgfx::isValid(m_impl->vbh)
        && bgfx::isValid(m_impl->ibh);
}

void Mesh2D::Destroy()
{
    if (bgfx::isValid(m_impl->vbh)) {
        bgfx::destroy(m_impl->vbh);
        m_impl->vbh = BGFX_INVALID_HANDLE;
    }

    if (bgfx::isValid(m_impl->ibh)) {
        bgfx::destroy(m_impl->ibh);
        m_impl->ibh = BGFX_INVALID_HANDLE;
    }

    m_impl->indexCount = 0;
}