/*
 *  Copyright (c) Hubert Jarosz. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for full license information.
 */


#include "includes.h"
#include "program.h"

extern void help(void);
extern void render(GLFWwindow **window);

extern void error_callback(int error, const char *description)
{
  printf("%d: %s\n", error, description);
}

void scroll_callback(GLFWwindow* window, double xoffset _UNUSED_, double yoffset )
{
  pstates *prog = (pstates *) glfwGetWindowUserPointer(window);
  if(prog == NULL)
    return;

  if( fabs(yoffset) <= 0.25 )
    return;

  bool neg = false;

  if( yoffset < 0.0 )
  { // zoom out
    yoffset *= -1.0;
    neg = true;
  }

  yoffset = yoffset > 1.0 ? 1.0 : yoffset;
  yoffset = yoffset < 0.25 ? 0.25 : yoffset;
  yoffset = (yoffset - 0.25)/0.75 + 1.0;
  yoffset = neg ? 1.0/yoffset : yoffset;

  prog->uniformStruct.zoom_64 *= yoffset;
  prog->uniformStruct.zoom_32 = prog->uniformStruct.zoom_64;
  render(&window);
}

extern void key_callback(GLFWwindow *window, int key, int scancode _UNUSED_,
                         int action, int mods _UNUSED_)
{
  if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);

  pstates *prog = (pstates *) glfwGetWindowUserPointer(window);
  if(prog == NULL)
    return;

  if(action == GLFW_PRESS) switch(key)
  {
  case GLFW_KEY_Z:
    prog->uniformStruct.zoom_64 *= 2.0;
    prog->uniformStruct.zoom_32 = prog->uniformStruct.zoom_64;
    render(&window);
    break;

  case GLFW_KEY_X:
    prog->uniformStruct.zoom_64 /= 2.0;
    prog->uniformStruct.zoom_32 = prog->uniformStruct.zoom_64;
    render(&window);
    break;

  case GLFW_KEY_LEFT:
    prog->uniformStruct.pos[0] -= 1.0/prog->uniformStruct.zoom_64;
    render(&window);
    break;

  case GLFW_KEY_RIGHT:
    prog->uniformStruct.pos[0] += 1.0/prog->uniformStruct.zoom_64;
    render(&window);
    break;

  case GLFW_KEY_DOWN:
    prog->uniformStruct.pos[1] -= 1.0/prog->uniformStruct.zoom_64;
    render(&window);
    break;

  case GLFW_KEY_UP:
    prog->uniformStruct.pos[1] += 1.0/prog->uniformStruct.zoom_64;
    render(&window);
    break;

  case GLFW_KEY_C:
    prog->uniformStruct.vis += 10;
    render(&window);
    break;

  case GLFW_KEY_V:
    prog->uniformStruct.vis -= 10;
    render(&window);
    break;

  case GLFW_KEY_D:
    printf("z:%lf x:%lf y:%lf v:%d\n",
           prog->uniformStruct.zoom_64, prog->uniformStruct.pos[0], prog->uniformStruct.pos[1], prog->uniformStruct.vis);
    fflush(stdout);
    break;

  case GLFW_KEY_H:
    help();
    break;

  case GLFW_KEY_P:
    if(! prog->GPUHas64BitSupport)
    {
      fprintf(stderr, "Your GPU does not support GL_ARB_gpu_shader_fp64!\n");
      fflush(stdout);
      break;
    }

    if(prog->currentProgram == prog->program32bit)
    {
      prog->currentProgram = prog->program64bit;
    }
    else
    {
      prog->currentProgram = prog->program32bit;
    }
    updateProgram(prog);

    render(&window);
    break;

  default:
    break;
  }
}


extern void resize_callback(GLFWwindow *window, int32_t width, int32_t height)
{
  pstates *prog = (pstates *) glfwGetWindowUserPointer(window);
  if(prog == NULL)
    return;

  prog->uniformStruct.res[0] = width;
  prog->uniformStruct.res[1] = height;
  glViewport(0, 0, (GLint)width, (GLint)height);
  render(&window);
}

extern void iconify_callback(GLFWwindow *window, int iconified)
{
  if(iconified == GL_FALSE)
    render(&window);
}
