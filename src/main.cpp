#include "api/quadlib.h"
#include <iostream>

int main() {
	QuadLib::initWindow("my window", 1280, 720);

	while (!QuadLib::windowShouldClose()) {
		QuadLib::beginFrame(QuadLib::RGBA(255, 255, 0, 255));
		QuadLib::endFrame();
	}

	QuadLib::Shutdown();
}