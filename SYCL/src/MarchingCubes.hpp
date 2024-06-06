#ifndef MARCHINGCUBES_HPP
#define MARCHINGCUBES_HPP

#include "Grid.hpp"
#include "Isosurface.hpp"
#include "SYCLUtils.hpp"


class MarchingCubes {
public:
	MarchingCubes(float isoLevel);
	void generateIsosurface(const Grid& grid, Isosurface& isosurface);
private:
	float isoLevel;
	void processCube(int x, int y, int z, const Grid& grid, Isosurface& isosurface);
};

#endif 
