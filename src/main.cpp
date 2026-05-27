#include "api/quadlib.h"
#include <iostream>

int main() {
	QuadLib::initWindow("my window", 1280, 720);

	Shader shader { "assets/shaders/fs_basic.sc", ShaderType::Fragment };

	QuadLib::compileShader(shader);

	while (!QuadLib::windowShouldClose()) {
		QuadLib::beginFrame(QuadLib::RGBA(255, 255, 0, 255));
		QuadLib::endFrame();
	}

	QuadLib::Shutdown();
}