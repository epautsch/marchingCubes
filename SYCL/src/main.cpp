#include <iostream>
#include "MarchingCubes.hpp"
#include "Grid.hpp"
#include "Isosurface.hpp"


int main() {
	std::cout << "Marching Cubes Placeholder Project" << std::endl;

	// test Grid	
	//Grid grid(4, 4, 4);
	//grid.setValue(1, 1, 1, 5.0f);
	//std::cout << "Value at (1,1,1): " << grid.getValue(1, 1, 1) << std::endl; // should be 5

	//test Isosurface
	//Isosurface isosurface;
	//isosurface.addTriangle({0.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f});
	//const auto& triangles = isosurface.getTriangles();
	//std::cout << "Number of vertices: " << triangles.size() << std::endl; // should be 3

	// test MarchingCubes
	Grid grid(4, 4, 4);
	Isosurface isosurface;
	MarchingCubes mc(0.5f);

	grid.setValue(1, 1, 1, 1.0f);
	grid.setValue(2, 2, 2, 1.0f);

	mc.generateIsosurface(grid, isosurface);

	std::cout << "Generated isosurface with " << isosurface.getTriangles().size() / 3 << " triangles" << std::endl;

	return 0;
}
