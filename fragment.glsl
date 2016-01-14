#version 410
#extension GL_ARB_gpu_shader_fp64 : require

out vec4 ex_Color;

layout (std140) uniform ProgData
{
  int w, h, maxi, vis;
  double zoom, posX, posY;
  vec2 c;
};

dvec3 color(in vec2 pos)
{
  dvec3 result = dvec3(0.0, 0.0, 0.0);

  dvec2 z;
  z.x = 1.5 * (pos.x - w / 2.0) / (0.5 * zoom * w) + posX * 0.5;
  z.y = (pos.y - h / 2.0) / (0.5 * zoom * h) + posY * 0.5;

  // uncomment to get Mandelbrot set
  //dvec2 c = z;
  //z = dvec2(0,0);

  int i;
  for(i = 0; i < maxi && length(z) <= 2.0; i++)
  {
    double tmp = z.x * z.y;
    z.x = z.x * z.x - z.y * z.y;
    z.y = 2.0 * tmp;

    z += c;
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
  dvec3 col = hsv2rgb(color( vec2(gl_FragCoord.xy ) ));
  ex_Color = vec4(vec3(col), 1.0);
}
