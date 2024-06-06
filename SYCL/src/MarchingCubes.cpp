#include "MarchingCubes.hpp"


MarchingCubes::MarchingCubes(float isoLevel) : isoLevel(isoLevel) {}

void MarchingCubes::generateIsosurface(const Grid& grid, Isosurface& isosurface) {
	// Placeholder
	for (int x = 0; x < grid.getWidth() - 1; ++x) {
		for (int y = 0; y < grid.getHeight() - 1; ++y) {
			for (int z = 0; z < grid.getDepth() - 1; ++z) {
				processCube(x, y, z, grid, isosurface);
			}
		}
	}
}

void MarchingCubes::processCube(int x, int y, int z, const Grid& grid, Isosurface& isosurface) {
	// Placeholder
}
