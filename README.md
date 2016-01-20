# YuriaViewer

[![Build Status](https://travis-ci.org/Marqin/YuriaViewer.svg?branch=master)](https://travis-ci.org/Marqin/YuriaViewer)

Yuria Viewer is simple (yet) Julia set explorer written in C99.

Prerequisites (probably not all):
  * OpenGL 4.1 (higher should work)
  * GLFW 3
  * GLEW, GLU
  * pkg-config
  * MSYS2 for Windows build

To list all avalible commands press 'h' while displaying a set.

## Compilation

For Windows see [below](#building-on-windows).

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


## Building on Windows

### Prerequisites
You will need [MSYS2](https://msys2.github.io/).

### Update MSYS2
`update core`, restart MSYS2, then `pacman -Syu`

### Install dependencies

    pacman -Sy
    pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-glew mingw-w64-x86_64-glfw mingw-w64-x86_64-pkg-config make git
    PATH+=:/mingw64/bin:
### Build

The same as described in **Compilation** section.
But if you want to use it on system that does not have MSYS2/glfw/glew then you need to compile it with `make CFLAGS=-static`.
