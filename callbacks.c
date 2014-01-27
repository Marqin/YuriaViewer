#include "includes.h"

extern void error_callback(int error _UNUSED_, const char* description)
{
  fputs(description, stderr);
}

extern void key_callback(GLFWwindow* window, int key, int scancode _UNUSED_, int action, int mods _UNUSED_)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}
