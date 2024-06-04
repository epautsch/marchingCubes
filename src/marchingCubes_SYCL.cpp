#include <sycl/sycl.hpp>
#include <iostream>
#include <vector>
#include <cmath>

#include "define.h"

using namespace sycl;

struct Point {
  float x, y, z;
  float value;
};

int getIndex(const Point cube[8]) {
  int index = 0;
  for (int i = 0; i < 8; i++) {
    if (cube[i].value < 0) {
      index |= (1 << i);
    }
  }
  return index;
}

void marchingCubes(queue &q, Point *points, int gridSize, 
                          std::vector<int> &outputIndices) {
	int numCubes = (gridSize - 1) * (gridSize - 1);
	outputIndices.clear();

	buffer<Point, 1> pointsBuf(points, range<1>(gridSize * gridSize * gridSize));
	buffer<int, 1> outputIndicesBuf(outputIndices.data(), range<1>(gridSize * gridSize * gridSize * 15));

	q.submit([&](handler &h) {
		auto pointsAcc = pointsBuf.get_access<access::mode::read>(h);
		auto outputIndicesAcc = outputIndicesBuf.get_access<access::mode::write>(h);

		h.parallel_for(range<3>(gridSize - 1, gridSize - 1, gridSize - 1), [=](id<3> idx) {
			int x = idx[0], y = idx[1], z = idx[2];
			Point cube[8];

			for (int i = 0; i < 8; i++) {
				int xi = x + (i & 1);
				int yi = y + ((i & 2) >> 1);
				int zi = z + ((i & 4) >> 2);
				cube[i] = pointsAcc[zi * gridSize * gridSize + yi * gridSize + xi];
			}

			int cubeIndex = getIndex(cube);
			if (edgeTable[cubeIndex] == 0) return;

			int indexOffset = (z * (gridSize - 1) * (gridSize - 1) + y * (gridSize - 1) + x) * 15;
			for (int i = 0; triTable[cubeIndex][i] != -1; i += 3) {
				outputIndicesAcc[indexOffset + i] = triTable[cubeIndex][i];
				outputIndicesAcc[indexOffset + i + 1] = triTable[cubeIndex][i + 1];
				outputIndicesAcc[indexOffset + i + 2] = triTable[cubeIndex][i + 2];
			}
		});
	}).wait();

	outputIndices.assign(outputIndicesBuf.get_access<access::mode::read>().get_pointer(), outputIndicesBuf.get_access<access::mode::read>().get_pointer() + outputIndicesBuf.get_size());
}

void createSphere(Point *points, int gridSize, float radius, Point center) {
	int index = 0;
	for (int z = 0; z < gridSize; z++) {
		for (int y = 0; y < gridSize; y++) {
			for (int x = 0; x < gridSize; x++) {
				float dx = (x - center.x);
				float dy = (y - center.y);
				float dz = (z - center.z);
				float distance = sqrt(dx * dx + dy * dy + dz * dz);
				points[index] = {static_cast<float>(x), static_cast<float>(y), static_cast<float>(z), distance - radius};
				index++;
			}
		}
	}
}

int main() {
	const int gridSize = 20;
	const float radius = 8.0f;
	Point center = {gridSize / 2.0f, gridSize / 2.0f, gridSize / 2.0f};

	int numPoints = gridSize * gridSize * gridSize;
	Point *points = new Point[numPoints];
	createSphere(points, gridSize, radius, center);

	std::vector<int> outputIndices(gridSize * gridSize * gridSize * 15);
	queue q;

	marchingCubes(q, points, gridSize, outputIndices);

	for (int i = 0; i < outputIndices.size(); i++) {
		std::cout << outputIndices[i] << " ";
		if ((i + 1) % 3 == 0) {
			std::cout << std::endl;
		}
	}

	delete[] points;
	return 0;
}

