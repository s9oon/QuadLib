#pragma once

#include <bgfx/bgfx.h>
#include "../common/types.h"

struct GPUMesh2D {
	bgfx::VertexBufferHandle vbh;
	bgfx::IndexBufferHandle ibh;
};

namespace Core {
	extern bgfx::VertexLayout g_VertexLayout;
	GPUMesh2D loadMesh(const Mesh2D& mesh);
}