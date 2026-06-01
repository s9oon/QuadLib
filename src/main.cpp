#include "api/quadlib.h"
#include <iostream>

int main() {

	std::cout << "hello words\n";
	QuadLib::initWindow("my window", 1280, 720);

	Shader vsshader { 
		QUADLIB_PROJECT_ROOT "/assets/shaders/fs_basic.sc", QUADLIB_PROJECT_ROOT "/assets/shaders/compiled/fs_basic.bin", ShaderType::Fragment
	};
	Shader fsshader  = { 
		QUADLIB_PROJECT_ROOT "/assets/shaders/vs_basic.sc", QUADLIB_PROJECT_ROOT "/assets/shaders/compiled/vs_basic.bin", ShaderType::Vertex
	};

	QuadLib::compileShader(vsshader);
	QuadLib::compileShader(fsshader);

	std::vector<Vertex2D> vertices = {
		// Vertex pos     UV pos
		{-0.5f,  0.5f, 0.0f, 0.0f},
		{ 0.5f,  0.5f, 1.0f, 0.0f},
		{ 0.5f, -0.5f, 1.0f, 1.0f},
		{-0.5f, -0.5f, 0.0f, 1.0f},
	};

	std::vector<uint16_t> indices = {
		0, 1, 2,   // first triangle
		2, 3, 0    // second triangle
	};

	Mesh2D quad(vertices, indices);

	Transform origin = { {0.0f, 0.0f},  // position
						 0.0f,          // rotation
						 {1.0f, 1.0f}   // scale
	};

	Element moon = { &quad, origin, QUADLIB_PROJECT_ROOT "/assets/basicmoon.png" };

	bgfx::ProgramHandle basic = Core::getProgram(QUADLIB_PROJECT_ROOT "/assets/shaders/compiled/vs_basic.bin", QUADLIB_PROJECT_ROOT "/assets/shaders/compiled/fs_basic.bin");

	while (!QuadLib::windowShouldClose()) {
		QuadLib::beginFrame(QuadLib::RGBA(255, 255, 0, 255));
		QuadLib::drawElement(moon, basic);
		QuadLib::endFrame();
	}

	Core::unloadElement(moon);

	QuadLib::Shutdown();
}