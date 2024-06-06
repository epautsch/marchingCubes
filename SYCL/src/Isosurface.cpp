#include "Isosurface.hpp"


void Isosurface::addTriangle(const std::tuple<float, float, float>& v1,
			     const std::tuple<float, float, float>& v2,
			     const std::tuple<float, float, float>& v3) {
	triangles.push_back(v1);
	triangles.push_back(v2);
	triangles.push_back(v3);
}

const std::vector<std::tuple<float, float, float>>& Isosurface::getTriangles() const {
	return triangles;
}
