#version 410

out vec4 ex_Color;

layout (std140) uniform ProgData
{
  int maxi, vis;
  uvec2 resolution;
  vec2 complex, camera;
  float zoom;
};

vec3 color(in vec2 pos)
{
  vec3 result = vec3(0.0, 0.0, 0.0);

  vec2 z;

  z.x = 1.5 * pos.x/float(resolution.x/2) - 1.5;
  z.y = pos.y/float(resolution.y/2) - 1.0;
  z /= zoom;
  z += camera;

  // uncomment to get Mandelbrot set
  //vec2 c = z;
  //z = vec2(0,0);

  int i;
  for(i = 0; i < maxi && length(z) <= 2.0; i++)
  {
    z = mat2(z,-z.y,z.x)*z + complex;
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
  vec3 col = hsv2rgb(color( gl_FragCoord.xy  ));
  ex_Color = vec4(col, 1.0);
}
