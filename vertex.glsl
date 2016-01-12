#version 410
#extension GL_ARB_gpu_shader_fp64 : require

in vec2 in_Position;
out vec3 ex_Color;

layout (std140) uniform ProgData
{
  int w, h, maxi, vis;
  double zoom, posX, posY;
  vec2 con;
};

vec2 c_pow( in dvec2 c, in double n )
{
  double r = length( c );
  double fi = atan( c.y/c.x );
  r = pow(r, n);
  fi *= n;
  return dvec2( r*cos(fi), r*sin(fi) );
}

vec2 c_exp( in vec2 c )
{
  float r = exp( c.y );
  float fi = atan( c.y/c.x );
  return vec2( r*cos(fi), r*sin(fi) );
}

dvec3 color(in vec2 pos)
{
  pos.x = ( pos.x + 1.0 ) / ( 2.0/w );
  pos.y = ( pos.y + 1.0 ) / ( 2.0/h );

  dvec3 result = dvec3(0.0, 0.0, 0.0);

  dvec2 z;
  z.x = 1.5 * (pos.x - w / 2.0) / (0.5 * zoom * w) + posX * 0.5;
  z.y = (pos.y - h / 2.0) / (0.5 * zoom * h) + posY * 0.5;

  int i;
  for(i = 0; i < maxi && length(z) <= 2.0; i++)
  {
    z = c_pow(z, 2) + con;
    //z = c_pow(z, 7) + vec2(0.626, 0.0);    // experiments
    //z = c_exp(c_pow(z,2)) - vec2(0.65, 0); // experiments
  }

  if (i >= vis)
  {
    result = dvec3((i+0.0)/maxi, 0.6, 1.0);
  }
  return result;
}

dvec3 hsv2rgb(in dvec3 c)
{
  vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
  dvec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
  return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

void main()
{
  gl_Position = vec4(in_Position, 0.0, 1.0);
  ex_Color = vec3(hsv2rgb(color(in_Position)));
}
