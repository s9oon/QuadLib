#include "shader.h"

#include <bgfx/bgfx.h>
#include <cstdlib>
#include <string>
#include <iostream>
#include <filesystem>
#include <sstream>
#include <bx/file.h>
#include <bx/error.h>

namespace Core {

    namespace fs = std::filesystem;

    static Platform detectPlatform()
    {
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
        case ShaderType::Vertex:   return "vertex";
        case ShaderType::Fragment: return "fragment";
        default:                   return "vertex";
        }
    }

    static const char* getPlatformArg(Platform platform)
    {
        switch (platform)
        {
        case Platform::Windows: return "windows";
        case Platform::Linux:   return "linux";
        case Platform::MacOS:   return "osx";
        case Platform::Android: return "android";
        case Platform::iOS:     return "ios";
        default:                return "windows";
        }
    }

    static const char* getProfileArg(bgfx::RendererType::Enum renderer)
    {
        switch (renderer)
        {
        case bgfx::RendererType::Direct3D11: return "s_5_0";
        case bgfx::RendererType::Direct3D12: return "s_5_1";
        case bgfx::RendererType::OpenGL:     return "440";
        case bgfx::RendererType::OpenGLES:   return "300_es";
        case bgfx::RendererType::Vulkan:     return "spirv";
        case bgfx::RendererType::Metal:      return "metal";
        default:                             return "120";
        }
    }

    bool compileShader(Shader& shader)
    {
        if (shader.platform == Platform::Auto)
            shader.platform = detectPlatform();

        if (shader.backend == bgfx::RendererType::Count)
            shader.backend = bgfx::getRendererType();

        fs::path input(shader.sourcePath);
        fs::path output(shader.compiledPath);

        fs::create_directories(output.parent_path());

        std::stringstream cmd;

        cmd << QUADLIB_SHADERC
            << " -f \"" << input.string() << "\""
            << " -o \"" << output.string() << "\""
            << " --type " << getShaderTypeArg(shader.type)
            << " --platform " << getPlatformArg(shader.platform)
            << " --profile " << getProfileArg(shader.backend)
            << " -i \"" << QUADLIB_BGFX_SRC_DIR << "\"";

        std::cout << "[shaderc] " << cmd.str() << std::endl;

        int result = std::system(cmd.str().c_str());

        if (result != 0) {
            std::cerr << "[shaderc] compilation failed: "
                << shader.sourcePath << std::endl;
            return false;
        }

        return true;
    }

    bgfx::ShaderHandle loadShader(const char* path) {
        std::filesystem::path fullPath = std::filesystem::absolute(path);

        bx::FileReader reader;
        bx::Error err;

        if (!bx::open(&reader, path, &err)) {
            std::cerr << "[QuadLib] Failed to open shader file: "
                << fullPath << std::endl;

            return BGFX_INVALID_HANDLE;
        }

        uint32_t size = (uint32_t)bx::getSize(&reader);

        const bgfx::Memory* mem = bgfx::alloc(size + 1);

        bx::read(&reader, mem->data, size, &err);

        bx::close(&reader);

        mem->data[size] = '\0';

        return bgfx::createShader(mem);
    }

    bgfx::ProgramHandle getProgram(const char* vspath, const char* fspath) {
        bgfx::ShaderHandle vsh = loadShader(vspath);
        bgfx::ShaderHandle fsh = loadShader(fspath);

        return bgfx::createProgram(vsh, fsh, true);
    }
}