#pragma once

typedef struct color {
  double r,g,b;
} color;

typedef struct complex {
  double r, i;
} complex;

typedef struct program_states {
  double zoom, posX, posY;
  int w, h, maxi, vis;
  complex con;
} pstates;
