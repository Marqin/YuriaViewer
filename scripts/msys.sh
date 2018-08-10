#!/usr/bin/env sh

PREFIX=mingw-w64-$(uname -m)
pacman -Sy $PREFIX-toolchain $PREFIX-cmake $PREFIX-glew $PREFIX-glfw
