# YuriaViewer

[![Build Status](https://travis-ci.org/Marqin/YuriaViewer.svg?branch=master)](https://travis-ci.org/Marqin/YuriaViewer)

Yuria Viewer is simple (yet) Julia set explorer written in C99.

Prerequisites (probably not all):
  * OpenGL 4.1 (higher should work)
  * GLFW 3
  * GLEW, GLU

To list all avalible commands press 'h' while displaying a set.

## Compilation

`make` - builds Yuria Viewer

`make CCFlags=-Dsingle` - builds Yuria Viewer in single-precision mode

`make clean` - cleans build directory


## Example usage

You need to run Yuria Viewer while beeing ( your shell ) in the same dir as
shaders:
`./bin/YuriaViewer < samples/0.in`

In case of problems, see below:

## single-precision mode

If your GPU doesn't have `GL_ARB_gpu_shader_fp64`, drivers have broken
implementation of `double` type, or double-precision shaders are just too slow
for your GPU, then you should fallback to single-precision mode.

Keep in mind that you cannot zoom as much in this mode, as in double-precision
mode.
