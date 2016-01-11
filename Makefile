#
#  Copyright (c) Hubert Jarosz. All rights reserved.
#  Licensed under the MIT license. See LICENSE file in the project root for full license information.
#

CC = gcc
Warnings = -pedantic -Wall -Wextra -Wshadow -Wstrict-overflow
override CFLAGS += $(Warnings) -Werror -std=c99 -Os -O2 -fno-strict-aliasing
Source = callbacks.c main.c utils.c shaders.c
Headers = includes.h shaders.h structs.h utils.h
LibsHeaders = $(shell pkg-config --static --cflags glew) $(shell pkg-config --static --cflags glfw3)
Libs = $(shell pkg-config --static --libs glew) $(shell pkg-config --static --libs glfw3) -lm
Dist = ./bin

.PHONY: all clean

$(Dist)/YuriaViewer: Makefile $(Source) $(Headers)
	mkdir -p "$(Dist)"
	$(CC) $(CFLAGS) $(Source) $(LibsHeaders) $(Libs) -o $(Dist)/YuriaViewer

clean:
	if [ -d "$(Dist)" ]; then rm -r -- "$(Dist)"; fi
