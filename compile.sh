# TODO: cmake

mkdir -p bin
clang -lm -lGLEW -lglfw -lGL -lGLU -Wall -Werror -Wextra -pedantic -O2 fractal.c callbacks.c main.c -o bin/YuriaViewer
