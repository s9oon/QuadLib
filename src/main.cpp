#include "api/quadlib.h"
#include <iostream>
#include <string>

int main() {

	QuadLib::initWindow("my window", 1280, 720);

	/*
	* uncomment for compiling new shaders
	Shader fsshader { 
		QUADLIB_PROJECT_ROOT "/assets/shaders/fs_basic.sc", QUADLIB_PROJECT_ROOT "/assets/shaders/compiled/fs_basic.bin", ShaderType::Fragment
	};
	Shader vsshader  = { 
		QUADLIB_PROJECT_ROOT "/assets/shaders/vs_basic.sc", QUADLIB_PROJECT_ROOT "/assets/shaders/compiled/vs_basic.bin", ShaderType::Vertex
	};

	QuadLib::compileShader(fsshader);
	QuadLib::compileShader(vsshader);
	*/

	Mesh2D quad = QuadLib::getQuad();

	ElementUI moon = { &quad, QuadLib::getCenter(200.0f), QUADLIB_ROOT "/assets/basicmoon.png"};

	bgfx::ProgramHandle basic = Core::getProgram(
		QUADLIB_ROOT "/assets/shaders/compiled/vs_basic.bin", QUADLIB_ROOT "/assets/shaders/compiled/fs_basic.bin"
	);

	std::vector<const char*> textures =
	{
		QUADLIB_ROOT "/assets/smallermoon.png",
		QUADLIB_ROOT "/assets/smallermoon.png",
		QUADLIB_ROOT "/assets/smallermoon.png",
	};

	TextureAtlas atlas = Core::generateAtlasImageData(textures);

	Core::saveAtlasPNG(
		atlas,
		QUADLIB_ROOT "/assets/finalatlas.png"
	);

	const AtlasData& smallermoon2 = atlas.regions.at(2);

	while (!QuadLib::windowShouldClose()) {
		QuadLib::beginFrame(QuadLib::RGBA(255, 255, 0, 255));
		QuadLib::drawElement(moon, basic);
		QuadLib::endFrame();
	}

	delete[] atlas.data;

	QuadLib::Shutdown();
}