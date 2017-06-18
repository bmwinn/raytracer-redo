Ray Tracer
Bridget Winn

To run:
   run make
   ./raytrace <width> <height> ___.pov <destination directory>

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
- Blinn Phong shading
- shadows (upcoming)
- moving camera (upcoming)

Part 3:
- triangles
- reflection
- refraction
   * filter: 0 means 100% refractive, 1 means 0% refractive
   * ask Ian Dunn.
