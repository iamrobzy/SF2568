# SF2568

# MPI Mandelbrot Implementation

This repository contains an MPI-based implementation of the Mandelbrot algorithm in C, C++, or Fortran. To run this program, access to MPI on one of the platforms is required, preferably Dardel.

## Issues to Consider

When using MPI, it's important to note the following considerations:

1. **Graphics Handling**: Since MPI usually does not have access to a graphics system, the final image cannot be displayed by the parallel program. It's recommended to write the final result to hard disk and use MATLAB or another program for graphical representation.
   
2. **File Saving**: The final image can be saved either in binary or ASCII format to hard disk. Different machines may have different binary formats, while ASCII files require more disk space. With the given image size, the ASCII file may occupy up to 30MB on hard disk.

3. **Color Data Type**: The recommended data type for color is `unsigned char` in C or `integer(kind=2)` in Fortran.

## Instructions

1. Implement the Mandelbrot program using MPI. Ensure that the number of processors divides the number of columns evenly.
   
2. Reproduce the figure from the lecture notes. Feel free to experiment with different palettes in MATLAB.
   
3. Magnify interesting parts of the figure by computing only parts of the complete picture using higher resolutions.

Please refer to the description of Lab 1 to understand how to run programs on Dardel.

## Points Distribution

- Implementing MPI Mandelbrot program: 4 points
- Reproducing figure from lecture notes: 1 point
- Magnifying interesting parts of the figure: 2 points
