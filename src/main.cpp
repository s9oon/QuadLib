#include "api/quadlib.h"
#include <iostream>
#include <string>

void printAtlasData(const AtlasData& data) {
	std::cout << "id: " << data.id << std::endl;
	std::cout << "u0: " << data.u0 << std::endl;
	std::cout << "v0: " << data.v0 << std::endl;
	std::cout << "u1: " << data.u1 << std::endl;
	std::cout << "v1: " << data.v1 << std::endl;
}

void remapUVs(Mesh2D& mesh, const AtlasData& data) {
	float du = data.u1 - data.u0;
	float dv = data.v1 - data.v0;

	for (auto& vertex : mesh.vertices) {
		vertex.uv.x = data.u0 + vertex.uv.x * du;
		vertex.uv.y = data.v0 + vertex.uv.y * dv;
	}
}

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

	std::vector<const char*> textures =
	{
		QUADLIB_ROOT "/assets/triangle2.png",
		QUADLIB_ROOT "/assets/circle2.png",
		QUADLIB_ROOT "/assets/square2.png",
	};

	TextureAtlas atlas = Core::generateAtlasImageData(textures);

	Core::saveAtlasPNG(atlas, QUADLIB_ROOT "/assets/finalatlas.png");

	const AtlasData& smallermoon1 = atlas.regions.at(1);

	Mesh2D quad = QuadLib::getQuad();

	remapUVs(quad, smallermoon1);

	ElementUI moon = { &quad, QuadLib::getCenter(200.0f), QUADLIB_ROOT "/assets/finalatlas.png"};

	bgfx::ProgramHandle basic = Core::getProgram(
		QUADLIB_ROOT "/assets/shaders/compiled/vs_basic.bin", QUADLIB_ROOT "/assets/shaders/compiled/fs_basic.bin"
	);

	while (!QuadLib::windowShouldClose()) {
		QuadLib::beginFrame(QuadLib::RGBA(255, 255, 0, 255));
		QuadLib::drawElement(moon, basic);
		QuadLib::endFrame();
	}

	delete[] atlas.data;

	QuadLib::Shutdown();
}