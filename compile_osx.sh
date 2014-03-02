# TODO: cmake

mkdir -p bin
clang -lm -lGLEW -lglfw3 -framework QuartzCore -framework IOKit -framework OpenGL -framework Cocoa -Wall -Werror -Wextra -pedantic -O2 -std=c99 fractal.c callbacks.c main.c -o bin/YuriaViewer
