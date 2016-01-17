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



## 32/64-bit shaders

You can swap between 32/64-bit shaders pressing `p` key.

64-bit mode is default, unless your GPU don't have `GL_ARB_gpu_shader_fp64`
extension. If 64-bit mode it's too slow for you or you see black screen
( possible on some broken driver ), then you should change to 32-bit shaders.
