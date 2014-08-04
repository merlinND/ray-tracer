ray-tracer
==========

A simple 3D renderer based on ray-tracing algorithm.
For now, all computations are done on CPU, but future versions may leverage GPU computing power via OpenGL shaders.

![Render example](renders/such-coordinates.jpg)

## Currently implemented

- JPEG output
- Camera view matrix
- Basic scene data structure
- Basic lights representations
- Cube & sphere (intersections and normal vectors)
- Diffuse lighting
- Materials

## TODO

- Specular lighting
- More geometric figures
  - Arbitrary parallelepiped
  - Pyramid
- Arbitrary rotation of objects
- Directed lighting
- Attenuation of light with distance
- Refraction (supporting arbitrary indices for all rays)

## Dependencies

- [`eigein` 3.2.1](http://eigen.tuxfamily.org/) for linear algebra data structures and operations
- [`libjpeg`](http://www.ijg.org/) for JPEG output

## Credits

Some algorithms were adapted from ["Algorithmes pour la synthèse d'images et l'animation 3D"](http://www.dunod.com/informatique-multimedia/graphisme-et-web-design/web-design-et-animation-web/algorithmes-pour-la-synthese-dimages-et-lani) by Rémy Malgouyres.
