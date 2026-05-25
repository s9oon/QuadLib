#include "api/quadlib.h"
#include <iostream>

int main() {
	if (!QuadLib::Init()) {
		std::cerr << "Failed to init\n";
	}

	std::cout << "Init passed well\n";
	system("pause");	

	QuadLib::shutDown();
}