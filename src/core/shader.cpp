#include "shader.h"

#include <bgfx/bgfx.h>

#include <cstdlib>
#include <string>
#include <iostream>
#include <filesystem>

namespace Core {
    static Platform detectPlatform() {
#if defined(_WIN32)
        return Platform::Windows;
#elif defined(__linux__)
        return Platform::Linux;
#elif defined(__APPLE__)
        return Platform::MacOS;
#else
        return Platform::Windows;
#endif
    }

    static const char* getShaderTypeArg(ShaderType type)
    {
        switch (type)
        {
        case ShaderType::Vertex:   return "v";
        case ShaderType::Fragment: return "f";
        default: return "";
        }
    }

    static const char* getPlatformArg(Platform platform) {
        switch (platform) {
        case Platform::Windows: return "windows";
        case Platform::Linux:   return "linux";
        case Platform::MacOS:   return "osx";
        case Platform::Android: return "android";
        case Platform::iOS:     return "ios";

        default: return "windows";
        }
    }

    static const char* getProfileArg(bgfx::RendererType::Enum renderer) {
        switch (renderer) {
        case bgfx::RendererType::Direct3D11:
            return "440";

        case bgfx::RendererType::Direct3D12:
            return "s_5_1";

        case bgfx::RendererType::OpenGL:
            return "440";

        case bgfx::RendererType::OpenGLES:
            return "300_es";

        case bgfx::RendererType::Vulkan:
            return "spirv";

        case bgfx::RendererType::Metal:
            return "metal";

        default:
            return "120";
        }
    }

	bool compileShader(Shader& shader) {
        if (shader.platform == Platform::Auto) {
            shader.platform = detectPlatform();
        }
        if (shader.backend == bgfx::RendererType::Enum::Count) {
            shader.backend = bgfx::getRendererType();
        }

        std::filesystem::current_path("C:/QuadLib");

        std::string output =
            std::string(shader.path) + ".bin";

        std::string cmd =
            std::string("C:/QuadLib/build/_deps/bgfx-build/cmake/bgfx/Debug/shaderc.exe ") + " " +
            "-f \"" + std::string(shader.path) + "\" " +
            "-o \"" + output + "\" " +
            "--type " + getShaderTypeArg(shader.type) + " " +
            "-p " + getProfileArg(shader.backend) + " " +
            "--platform " + getPlatformArg(shader.platform) + " " +
            "-i \"C:/QuadLib/build/_deps/bgfx-src/bgfx/src\"";

        std::cout << cmd << std::endl;

        int result = std::system(cmd.c_str());

        return result == 0;
	}
}