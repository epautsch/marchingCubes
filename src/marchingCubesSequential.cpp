#include <cmath>
#include <iostream>
#include <vector>

#include "define.h"

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

void marchingCubes(Point *points, int gridSize,
                   std::vector<int> &outputIndices) {
    int numCubes = (gridSize - 1) * (gridSize - 1);
    outputIndices.clear();

    for (int z = 0; z < gridSize - 1; z++) {
        for (int y = 0; y < gridSize - 1; y++) {
            for (int x = 0; x < gridSize - 1; x++) {
                Point cube[8];
                int index = 0;

                for (int i = 0; i < 8; i++) {
                    int xi = x + (i & 1);
                    int yi = y + ((i & 2) >> 1);
                    int zi = z + ((i & 4) >> 2);
                    cube[i] = points[(zi * gridSize * gridSize) +
                                     (yi * gridSize) + xi];
                }
                int cubeIndex = getIndex(cube);
                if (edgeTable[cubeIndex] == 0) continue;

                for (int i = 0; triTable[cubeIndex][i] != -1; i += 3) {
                    outputIndices.push_back(triTable[cubeIndex][i]);
                    outputIndices.push_back(triTable[cubeIndex][i + 1]);
                    outputIndices.push_back(triTable[cubeIndex][i + 2]);
                }
            }
        }
    }
}

void createSphere(Point *points, int girdSize, float radius, Point center) {
    int index = 0;
    for (int z = 0; z < girdSize; z++) {
        for (int y = 0; y < girdSize; y++) {
            for (int x = 0; x < girdSize; x++) {
                float dx = (x - center.x);
                float dy = (y - center.y);
                float dz = (z - center.z);
                float distance = sqrt(dx * dx + dy * dy + dz * dz);
                points[index] = {static_cast<float>(x), static_cast<float>(y),
                                 static_cast<float>(z), distance - radius};
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

    std::vector<int> outputIndices;
    marchingCubes(points, gridSize, outputIndices);

    for (int i = 0; i < outputIndices.size(); i++) {
        std::cout << outputIndices[i] << " ";
        if ((i + 1) % 3 == 0) {
            std::cout << std::endl;
        }
    }

    delete[] points;
    return 0;
}