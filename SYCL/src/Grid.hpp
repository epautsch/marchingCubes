#ifndef GRIP_HPP
#define GRIP_HPP

#include <vector>


class Grid {
public:
	Grid(int width, int height, int depth);

	float getValue(int x, int y, int z) const;
	void setValue(int x, int y, int z, float value);

	int getWidth() const { return width; }
	int getHeight() const { return height; }
	int getDepth() const { return depth; }

private:
	int width, height, depth;
	std::vector<float> values;
};

#endif
