#include "api/quadlib.h"
#include <iostream>

int main() {
	QuadLib::initWindow("my window", 1280, 720);

	Shader shader { "C:/QuadLib/assets/shaders/fs_basic.sc", "C:/QuadLib/assets/shaders/compiled/fs_basic.bin", ShaderType::Fragment};

	QuadLib::compileShader(shader);

	shader  = { "C:/QuadLib/assets/shaders/vs_basic.sc", "C:/QuadLib/assets/shaders/compiled/vs_basic.bin", ShaderType::Vertex };

	QuadLib::compileShader(shader);

	while (!QuadLib::windowShouldClose()) {
		QuadLib::beginFrame(QuadLib::RGBA(255, 255, 0, 255));
		QuadLib::endFrame();
	}

	QuadLib::Shutdown();
}