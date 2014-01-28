#include "includes.h"

color hsv2rgb(float hue, float sat, float val)
{
  int a;
  float b, c, d, e;
  color result;
   
  if(val == 0)
  {
    result.r = 0;
    result.g = 0;
    result.b = 0;
    return result;
  }

  hue /= 60;
  a = floor(hue);
  b = hue - (float)a;
  c = val * (1.0 - sat);
  d = val * (1.0 - (sat * b));
  e = val * (1.0 - (sat * (1.0 - b)));
  
  switch(a)
  {
    case 0:
      result.r = val;
      result.g = e;
      result.b = c;
      break;
      
    case 1:
      result.r = d;
      result.g = val;
      result.b = c;
      break;
      
    case 2:
      result.r = c;
      result.g = val;
      result.b = e;
      break;
      
    case 3:
      result.r = c;
      result.g = d;
      result.b = val;
      break;
      
    case 4:
      result.r = e;
      result.g = c;
      result.b = val;
      break;
                 
    case 5:
      result.r = val;
      result.g = c;
      result.b = d;
      break;
  }

  return result;
}

double c_abs(complex c)
{
  return abs(c.r*c.r + c.i*c.i);
}

color point_color(double x, double y, pstates* prog)
{    
  complex  new, old;
  int i;
  color result;
  
  new.r = 1.5 * (x - prog->w / 2.0) / (0.5 * prog->zoom * prog->w) + prog->posX * 0.5;
  new.i = (y - prog->h / 2.0) / (0.5 * prog->zoom * prog->h) + prog->posY * 0.5;
  
  for(i = 0; i < prog->maxi && c_abs(new) <= 4.0; i++)
  {
    old = new;    
    new.r = old.r*old.r - old.i*old.i + prog->con.r;
    new.i = 2.0 * old.r * old.i + prog->con.i;
  }
  
  if (i >= prog->vis)
    result = hsv2rgb(((double)i)/prog->maxi * 360.0, 0.6f, 1.0f);
  else
  { 
    result.r = result.g = result.b = 0.0;
  }

  return result;
  
}
