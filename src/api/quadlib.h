#pragma once

#include <cstdint>
#include "../common/types.h"
#include "../common/primitives.h"

#ifdef QUADLIB_BGFX_TOOLS
#include "../core/shader.h"
#include "../core/mesh.h"
#include "../core/texture.h"
#endif

#ifdef QUADLIB_CORE
#include "../core/core.h"
#endif

namespace QuadLib {
#ifdef QUADLIB_BGFX_TOOLS
	bool compileShader(Shader& shader);

	// draw element with a custom shader
	void drawElement(Element& element, bgfx::ProgramHandle& program);

	// draw element with transform and a custom shader
	void drawElement(ElementWorld& element, bgfx::ProgramHandle& program);

#endif

	// draw element with trasnform and pre made shaders
	void drawElement(ElementWorld& element);

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

	// get centered transform for current window size
	Transform getCenter(float scale = 200.0f);

	// check if window should close
	bool windowShouldClose();

	// shutdown / deinitalise quadlib
	void Shutdown();
}