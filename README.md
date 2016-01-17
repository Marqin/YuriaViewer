# YuriaViewer

[![Build Status](https://travis-ci.org/Marqin/YuriaViewer.svg?branch=master)](https://travis-ci.org/Marqin/YuriaViewer)

Yuria Viewer is simple (yet) Julia set explorer written in C99.

Prerequisites (probably not all):
  * OpenGL 4.1 (higher should work)
  * GLFW 3
  * GLEW, GLU
  * pkg-config

To list all avalible commands press 'h' while displaying a set.

## Compilation

`make` - builds Yuria Viewer

`make clean` - cleans build directory


## Example usage

You need to run Yuria Viewer while beeing ( your shell ) in the same dir as
shaders:
`./bin/YuriaViewer < samples/0.in`

In case of problems, see below:

## double-precision mode

If your GPU supports `GL_ARB_gpu_shader_fp64`, you can press `p` to go into
64-bit mode in which fractal can be zoomed much more than in 32-bit mode. Keep
in mind, that some drivers have broken 64-bit support and you can see black
screen. In that case just press `p` again to get back to 32-bit mode.
