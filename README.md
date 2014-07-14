ray-tracer
==========

A simple 3D renderer based on ray-tracing algorithm.
For now, all computations are done on CPU, but future versions may leverage GPU computing power via OpenGL shaders.

## Currently implemented

- JPEG output
- Camera view matrix
- Basic scene data structure
- Basic lights representations
- Cube intersections
- Diffuse lighting

## TODO

- Specular lighting
- More geometric figures
  - Sphere
  - Arbitrary parallelepiped
- Directed lighting
- Materials system

## Dependencies

- [`eigein` 3.2.1](http://eigen.tuxfamily.org/) for linear algebra data structures and operations
- [`libjpeg`](http://www.ijg.org/) for JPEG output
