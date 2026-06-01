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

namespace Core {
    inline constexpr const char* VaryingDefPath = QUADLIB_PROJECT_ROOT "/assets/shaders/varying.def.sc";
    bgfx::ShaderHandle loadShader(const char* path);
    bgfx::ProgramHandle getProgram(const char* vspath, const char* fspath);
}

struct Shader {
    const char* sourcePath;
    const char* compiledPath;
    ShaderType type;
    bgfx::RendererType::Enum backend = bgfx::RendererType::Enum::Count;
    Platform platform = Platform::Auto;
    const char* varyingDefPath = Core::VaryingDefPath;
};

namespace Core {
    bool compileShader(Shader& shader);
}