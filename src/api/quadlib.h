#pragma once

#include <cstdint>
#include "../core/mesh.h"

#ifdef QUADLIB_BGFX_TOOLS
#include "../core/shader.h"
#endif

enum PresetShaders {
	BASIC,
};

namespace QuadLib {
#ifdef QUADLIB_BGFX_TOOLS
	bool compileShader(Shader& shader);
	void drawElement(const Mesh2D& mesh, const char* pngpath, bgfx::ProgramHandle& program);
#endif

	void drawElement(const Mesh2D& mesh, const char* pngpath, PresetShaders shaders);

	// convert color to bgfx
	uint32_t RGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);

	// public variable to cancel / begin game loop
	extern bool running;

	// begin frame / auto clears background 
	void beginFrame(uint32_t color = 0x303030ff);

	// clear background
	void clearBackground(uint32_t color = 0x303030ff);

	// end frame
	void endFrame();

	// initalise quadlib + basic window
	bool initWindow(const char* title = "QuadLib", int width = 1280, int height = 720);

	// get window size
	void getWindowSize(int& width, int& height);

	// check if window should close
	bool windowShouldClose();

	// shutdown / deinitalise quadlib
	void Shutdown();
}