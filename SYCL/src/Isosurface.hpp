#ifndef ISOSURFACE_HPP
#define ISOSURFACE_HPP

#include <vector>
#include <tuple>


class Isosurface {
public:
	void addTriangle(const std::tuple<float, float, float>& v1,
			 const std::tuple<float, float, float>& v2,
			 const std::tuple<float, float, float>& v3);
	const std::vector<std::tuple<float, float, float>>& getTriangles() const;
private:
	std::vector<std::tuple<float, float, float>> triangles;
};

#endif
