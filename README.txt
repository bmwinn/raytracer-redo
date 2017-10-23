Ray Tracer
Bridget Winn

To run:
   run make
   ./raytrace <width> <height> ___.pov <destination directory>

   example:
   ./raytrace 640 480 simple.pov tga

   The .pov file should be in the same directory as the executable.
   The program will name the resulting .tga file after the incoming
   .pov file and place it in the tga directory.
      
      ./raytrace 640 480 simple.pov tga -> simple.tga
      ./raytrace 640 480 pov/simple.pov tga -> <error>

   A script is included that builds the program, runs the program
   with each .pov file, and saves all .tgas in a tga directory.

Part 1:
- ray/sphere intersections
- ray/plane intersections
- basic colors

Part 2:
- Blinn-Phong shading
   --> add another BRDF for fun, Cook-Torrance?
- shadows
- moving camera

Part 3:
- triangles
- reflection
- refraction
   * filter: 0 means 100% refractive, 1 means 0% refractive

* Upcoming *
Part 4:
- transforms
- anti aliasing (9 samples per pixel)
- spatial data structure, will choose from:
   --> bounding volume hierarchy
   --> binary space partitioning tree
   --> oct-tree

TODOs
- kill off vector and point classes
   --> replace with glm
   --> better for transforms later
