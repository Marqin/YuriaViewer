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

dvec3 color(in vec2 pos)
{
  pos.x = ( pos.x + 1.0 ) / ( 2.0/w );
  pos.y = ( pos.y + 1.0 ) / ( 2.0/h );
  dvec2 new, old;
  int i;
  dvec3 result = dvec3(0.0, 0.0, 0.0);
  new.x = 1.5 * (pos.x - w / 2.0) / (0.5 * zoom * w) + posX * 0.5;
  new.y = (pos.y - h / 2.0) / (0.5 * zoom * h) + posY * 0.5;

  for(i = 0; i < maxi && abs( new.x*new.x + new.y*new.y ) <= 4.0; i++)
  {
    old = new;
    new.x = old.x * old.x - old.y * old.y + con.x;
    new.y = 2.0 * old.x * old.y + con.y;
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
