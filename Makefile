#
#  Copyright (c) Hubert Jarosz. All rights reserved.
#  Licensed under the MIT license. See LICENSE file in the project root for full license information.
#

CC = gcc
Warnings = -pedantic -Wall -Wextra -Wshadow -Wstrict-overflow=5
override CFLAGS += $(Warnings) -Werror -std=c99 -O2 -fstrict-aliasing
Source = callbacks.c main.c utils.c shaders.c
Headers = includes.h shaders.h structs.h utils.h
LibsHeaders = $(shell pkg-config --cflags glfw3) $(shell pkg-config --cflags glew)
Libs = $(shell pkg-config --libs glfw3) $(shell pkg-config --libs glew)
OS_NAME = $(shell uname -s)
ifeq ($(OS_NAME), Darwin)
	Libs += -framework OpenGL -framework Cocoa -framework IOKit
endif

Dist = ./bin

.PHONY: all clean

$(Dist)/YuriaViewer: Makefile $(Source) $(Headers)
	mkdir -p "$(Dist)"
	$(CC) $(CFLAGS) $(Source) $(LibsHeaders) $(Libs) -o $(Dist)/YuriaViewer
	cp *\.glsl "$(Dist)"

clean:
	if [ -d "$(Dist)" ]; then rm -r -- "$(Dist)"; fi
