/*
 *  Copyright (c) Hubert Jarosz. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for full license information.
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <GL/glew.h>

typedef struct uniform_struct {
  int32_t maxi, vis;
  uint32_t res[2];
  float con[2];
  float pos[2];
  float zoom_32;
  double zoom_64;
} uniform_struct_t;


typedef struct program_states {
  uniform_struct_t uniform;
  GLuint prog_32, prog_64;
  uint8_t precision;
  bool support_64;
} pstates;
