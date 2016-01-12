#version 410

in vec2 in_Position;
out vec3 ex_Color;

layout (std140) uniform ProgData
{
  int w, h, maxi, vis;
  float zoom, posX, posY;
  vec2 c;
};

vec2 c_pow( in vec2 c, in float n )
{
  float r = length( c );
  float fi = atan( c.y/c.x );
  r = pow(r, n);
  fi *= n;
  return vec2( r*cos(fi), r*sin(fi) );
}

vec2 c_exp( in vec2 c )
{
  float r = exp( c.y );
  float fi = atan( c.y/c.x );
  return vec2( r*cos(fi), r*sin(fi) );
}

vec3 color(in vec2 pos)
{
  pos.x = ( pos.x + 1.0 ) / ( 2.0/w );
  pos.y = ( pos.y + 1.0 ) / ( 2.0/h );

  vec3 result = vec3(0.0, 0.0, 0.0);

  vec2 z;
  z.x = 1.5 * (pos.x - w / 2.0) / (0.5 * zoom * w) + posX * 0.5;
  z.y = (pos.y - h / 2.0) / (0.5 * zoom * h) + posY * 0.5;

  int i;
  for(i = 0; i < maxi && length(z) <= 2.0; i++)
  {
    z = c_pow(z, 2) + c;
    //z = c_pow(z, 7) + vec2(0.626, 0.0);    // experiments
    //z = c_exp(c_pow(z,2)) - vec2(0.65, 0); // experiments
  }

  if (i >= vis)
  {
    result = vec3((i+0.0)/maxi, 0.6, 1.0);
  }
  return result;
}

vec3 hsv2rgb(in vec3 c)
{
  vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
  vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
  return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

void main()
{
  gl_Position = vec4(in_Position, 0.0, 1.0);
  ex_Color = vec3(hsv2rgb(color(in_Position)));
}
