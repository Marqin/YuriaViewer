/*
 *  Copyright (c) Hubert Jarosz. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for full license information.
 */

#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#ifdef _WIN32
  #define GLEW_STATIC
#endif
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "utils.h"
#include "structs.h"
#include <stdbool.h>
#include <stdint.h>

#define _UNUSED_ __attribute__ ((unused))
