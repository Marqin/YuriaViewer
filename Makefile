#
#  Copyright (c) Hubert Jarosz. All rights reserved.
#  Licensed under the MIT license. See LICENSE file in the project root for full license information.
#

CC = gcc
CCFlags = -Wall -Werror -Wextra -pedantic -O2 -std=c99
Source = fractal.c callbacks.c main.c utils.c
Headers = includes.h shaders.h structs.h utils.h

OS_NAME = $(shell uname -s)
ifeq ($(OS_NAME), Darwin)
  Libs = -lm -lGLEW -lglfw3 -framework QuartzCore -framework IOKit -framework OpenGL -framework Cocoa
else
  Libs = -lm -lGLEW -lglfw -lGL -lGLU
endif

.PHONY: all clean

bin/YuriaViewer: Makefile $(Source) $(Headers)
	mkdir -p bin
	$(CC) $(CCFlags) $(Source) $(Libs) -o bin/YuriaViewer

clean:
	if [ -d "./bin" ]; then rm -r ./bin; fi
