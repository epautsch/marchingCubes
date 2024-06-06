#include "Grid.hpp"


Grid::Grid(int width, int height, int depth) 
	: width(width), height(height), depth(depth), values(width * height * depth) {}

float Grid::getValue(int x, int y, int z) const {
	return values[x + y * width + z * width * height];
}

void Grid::setValue(int x, int y, int z, float value) {
	values[x + y * width + z * width * height] = value;
}
