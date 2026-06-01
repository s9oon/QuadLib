#pragma once

#include <bgfx/bgfx.h>
#include "../common/types.h"

struct GPUMesh2D {
	bgfx::VertexBufferHandle vbh;
	bgfx::IndexBufferHandle ibh;
	~GPUMesh2D();
};

namespace Core {
	GPUMesh2D loadMesh(const Mesh2D& mesh);
}