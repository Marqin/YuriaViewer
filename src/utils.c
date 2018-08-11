/*
 *  Copyright (c) Hubert Jarosz. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for full license information.
 */


#include "includes.h"

int get_int(const char * text, int32_t * i)
{
  printf("%s", text);
  fflush(stdout);
  int s = scanf("%d", i);
  return s;
}

int get_float(const char * text, float * d)
{
  printf("%s", text);
  fflush(stdout);
  int s = scanf("%f", d);
  return s;
}

pstates init_pstates()
{
  pstates p;

  p.uniformStruct.zoom_32 = 1.0;
  p.uniformStruct.zoom_64 = 1.0;
  p.uniformStruct.pos[0] = 0l;
  p.uniformStruct.pos[1] = 0l;

  p.uniformStruct.res[0] = 800;
  p.uniformStruct.res[1] = 600;
  p.uniformStruct.maxi = 0;
  p.uniformStruct.vis = 50;

  p.uniformStruct.con[0] = 0.0;
  p.uniformStruct.con[1] = 0.0;

  p.GPUHas64BitSupport = true;

  return p;
}
