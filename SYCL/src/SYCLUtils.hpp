#ifndef SYCLUTILS_HPP
#define SYCLUTILS_HPP

#include <sycl/sycl.hpp>
#include "Grid.hpp"
#include "Isosurface.hpp"


class SYCLUtils {
public:
	static void parallelProcessCubes(const Grid& grid, Isosurface& isosurface, float isoLevel);
};

#endif
