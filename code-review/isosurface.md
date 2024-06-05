# Isosurface 

Review and explanation of the isosurface program.

## What is an isosurface?  
An $\text{isosurface}$ is like a $3D$ version of a contour line on a map. It forms a surface that connects all points within a three-dimensional space that share the same value (such as temperature, pressure, velocity, or density). Essentially, it is a surface that highlights where a specific value exists within a $3D$ volume.

We begin by going through the process of generating a isosurface in our isosurface class: 

```cpp
void Isosurface::generateIsosurface(const Grid& grid, float isovalue,
                                    std::vector<Triangle>& triangles) {
    size_t width, height, depth;
    grid.setDimension(width, height, depth);

    // for each cube in the grid
    for (size_t x = 0; x < width - 1; x++) {
        for (size_t y = 0; y < height - 1; y++) {
            for (size_t z = 0; z < depth - 1; z++) {
                processCube(grid, x, y, z, isovalue, triangles);
            }
        }
    }
}
```

In this method we build our grid with the width, height, and depth of our desired $3D$ landscape. Then since we out working in a $3D$ universe we process each cube in the grid by calling the `processCube` with our grid, the $x, y, z$ coordinates, the isovalue and the triangles vector store the triangles formed with our desired surface. 

The following is an explanantion of our `processCube` implementation: 

```cpp
void Isosurface::processCube(const Grid& grid, size_t x, size_t y, size_t z,
                             float isovalue,
                             std::vector<Triangle>& triangles) const;
```
- Purpose:
   - The goal is to gather the values at the eight corners of the current cube. These values are used to determine the shape and placement if the 
    isosurface within this cube.
- Vertices:
    - `std::array<Vertex, 8> cubeVertices`: This declares an array of  eight `Vertex` structures defined in our `types.h`. Each `Vertex`contains a `Point` (also defined in `types.h`) representing its $3D$ position and a `float` representing a scalar value from the grid.
- Filling the Array:
    - The array if filled with `Vertex` objects. Each `Vertex` is constructed using an initializer list that sets the `Point` and its 
    assocaited value from the gird.
- Grid Values:
    - For each vertex position, the scalar value from the grid is fetched 
    usign `grid.getValue(x, y, z)`. This value represents the data that grid point.
```cpp
std::array<Vertex, 8> cubeVertices = {
    // Vertex 0: Bottom-left-front corner of the cube
    Vertex{Point{x_float, y_float, z_float}, grid.getValue(x, y, z)},
    // Vertex 1: Bottom-right-front corner of the cube
    Vertex{Point{x_float + 1, y_float, z_float}, grid.getValue(x + 1, y, z)},
    // Vertex 2: Top-right-front corner of the cube
    Vertex{Point{x_float + 1, y_float + 1, z_float}, grid.getValue(x + 1, y + 1, z)},
    // Vertex 3: Top-left-front corner of the cube
    Vertex{Point{x_float, y_float + 1, z_float}, grid.getValue(x, y + 1, z)},
    // Vertex 4: Bottom-left-back corner of the cube
    Vertex{Point{x_float, y_float, z_float + 1}, grid.getValue(x, y, z + 1)},
    // Vertex 5: Bottom-right-back corner of the cube
    Vertex{Point{x_float + 1, y_float, z_float + 1}, grid.getValue(x + 1, y, z + 1)},
    // Vertex 6: Top-right-back corner of the cube
    Vertex{Point{x_float + 1, y_float + 1, z_float + 1}, grid.getValue(x + 1, y + 1, z + 1)},
    // Vertex 7: Top-left-back corner of the cube
    Vertex{Point{x_float, y_float + 1, z_float + 1}, grid.getValue(x, y + 1, z + 1)},
};
```