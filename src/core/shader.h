#pragma once

#include <bgfx/bgfx.h>

enum class ShaderType {
	Vertex,
	Fragment,
};

enum class Platform {
	Auto,
	Windows,
	Linux,
	MacOS,
	Android,
	iOS
};

struct Shader {
	const char* path;
	ShaderType type;
	bgfx::RendererType::Enum backend = bgfx::RendererType::Enum::Count;
	Platform platform = Platform::Auto;
};

namespace Core {
	bool compileShader(Shader& shader);
}