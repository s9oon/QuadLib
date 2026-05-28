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
	const char* sourcePath;
	const char* compiledPath;

	ShaderType type;
	bgfx::RendererType::Enum backend = bgfx::RendererType::Enum::Count;
	Platform platform = Platform::Auto;
};

namespace Core {
	inline constexpr const char* VaryingDefPath = QUADLIB_PROJECT_ROOT "/assets/shaders/varying.def.sc";
	bool compileShader(Shader& shader);
	bgfx::ShaderHandle loadShader(const char* path);
	bgfx::ProgramHandle getProgram(const char* vspath, const char* fspath);
}