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

The following is an explanantion of our `processCube` implementation and please refer to the `isosurface.cpp` for the full implementation: 

```cpp
void Isosurface::processCube(const Grid& grid, size_t x, size_t y, size_t z,
                             float isovalue,
                             std::vector<Triangle>& triangles) const;
```
1. Purpose:
   - The goal is to gather the values at the eight corners of the current cube. These values are used to determine the shape and placement if the 
    isosurface within this cube.
2. Vertices:
    - `std::array<Vertex, 8> cubeVertices`: This declares an array of  eight `Vertex` structures defined in our `types.h`. Each `Vertex`contains a `Point` (also defined in `types.h`) representing its $3D$ position and a `float` representing a scalar value from the grid.
3. Filling the Array:
    - The array if filled with `Vertex` objects. Each `Vertex` is constructed using an initializer list that sets the `Point` and its 
    assocaited value from the gird.
4. Grid Values:
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

## What is interpolation? 
Interpolation is a method of estimating unknown values that fall between known 
values. In the marching cubes algorithm, interpolation helps determine the exact point on the edge of a cube where the scalar-field reaches a specific isovalue. 

The `interpolate` function calculates the position of the vertex on the isosurface between two vetices `v1`and `v2` where the scalar field reaches the isovalue.

1. Close to isovalue check:
    - The function first checks if either `v1` or `v2` is very close to the isovalue using a small $\epsilon$. If `v1` is close to the isovalue, it returns `v1`, and similarly, if `v2` is close to the isovalue, it returns `v2`.
2. Vertices are similar:
    - The function also checks to see if `v1` and `v2` are very close to each other. If true it means their is very little difference between scalar values and WLOG return `v1`.
3. Linear Interpolation:
    - If the above conditions are not met, the function performs linear interpolation to find the exact position where the isovalue intersects the edge between `v1` and `v2`.
    - $t$ is calculated as follows 
        $$t = \frac{\text{isovalue} - v1.\text{value}}{v2.\text{value} - v1.\text{value}}$$
4. Interpolate positions:
    - For example the $x$-coordinate:
        $$v.\text{position}.x = v1.\text{position}.x + t \times (v2.\text{position}.x - v1.\text{position}.x)$$
        - $\Delta x = v2.\text{position}.x - v1.\text{position}.x$ represents the total distance in the $x$-direction between `v1`and `v2`.
        - The scaled difference $t \times \Delta x$ scales the difference by the interpolation factor $t$, effectively giving us the distance from `v1` to the interpolated point in the $x$-direction.
        - Interpolated $x$-coordinate: Lastly the $v.\text{position}.x = v1.\text{position}.x + t \times \Delta x$ adds the scaled difference to the $x$-coordinate of `v1`.  

```cpp
Vertex Isosurface::interpolate(const Vertex& v1, const Vertex& v2,
                               float isovalue) const {
    // If v1 is very close to the isovalue then
    // v1 is on the isosurface
    if (std::abs(isovalue - v1.value) < EPISOLN) {
        return v1;
    }
    // If v2 is very close to the isovalue then
    // v2 is on the isosurface
    if (std::abs(isovalue - v2.value) < EPISOLN) {
        return v2;
    }
    // If v1 and v2 are very close to each other
    // then the two verices are the same scalar
    // value (no need for interpolation)
    // WLOG return v1
    if (std::abs(v1.value - v2.value) < EPISOLN) {
        return v1;
    }

    float t = (isovalue - v1.value) / (v2.value - v1.value);
    Vertex v;
    v.position.x = v1.position.x + t * (v2.position.x - v1.position.x);
    v.position.y = v1.position.y + t * (v2.position.y - v1.position.y);
    v.position.z = v1.position.z + t * (v2.position.z - v1.position.z);
    v.value = isovalue;
    return v;
}
```