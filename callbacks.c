/*
 * Copyright 2014 Hubert Jarosz
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "includes.h"

extern void help();

extern void error_callback(int error, const char* description)
{
  printf("%d: %s\n", error, description);
}

extern void key_callback(GLFWwindow* window, int key, int scancode _UNUSED_, int action, int mods _UNUSED_)
{
  if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
  
  pstates * prog = (pstates*) glfwGetWindowUserPointer(window);
  if(prog == NULL) return;
 
 if(action == GLFW_PRESS) 
  switch(key)
  {
    case GLFW_KEY_Z:
      prog->zoom *= 2.0;   
      break;
      
    case GLFW_KEY_X:
      prog->zoom /= 2.0;
      break;
      
    case GLFW_KEY_LEFT:
      prog->posX -= 1.0/prog->zoom;
      break;
      
    case GLFW_KEY_RIGHT:
      prog->posX += 1.0/prog->zoom;
      break;
            
    case GLFW_KEY_DOWN:
      prog->posY -= 1.0/prog->zoom;
      break;
            
    case GLFW_KEY_UP:
      prog->posY += 1.0/prog->zoom;
      break;

    case GLFW_KEY_C:
      prog->vis += 10;
      break;

    case GLFW_KEY_V:
      prog->vis -= 10;
      break;

    case GLFW_KEY_D:
      printf("z:%lf x:%lf y:%lf v:%d\n", prog->zoom, prog->posX, prog->posY,prog->vis);
      break;

    case GLFW_KEY_H:
      help();
      break;
      
    default:
      break;
  }
  
}
