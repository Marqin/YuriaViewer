/*
 *  Copyright (c) Hubert Jarosz. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for full license information.
 */


#include "includes.h"
#include "shaders.h"
#include "program.h"

extern void error_callback(int error, const char *description);
extern void key_callback(GLFWwindow *window, int key, int scancode, int action,
                         int mods);
extern void resize_callback(GLFWwindow *window, int width, int height);
extern void iconify_callback(GLFWwindow *window, int iconified);
extern void scroll_callback(GLFWwindow* window, double xoffset _UNUSED_, double yoffset );

int init(GLFWwindow **window, uint32_t res[2])
{
  if (!glfwInit())
    return 1;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  *window = glfwCreateWindow(res[0], res[1], "Yuria Viewer 0.4", NULL, NULL);

  if (!(*window))
  {
    glfwTerminate();
    return 1;
  }

  return 0;
}

void createVertexArrayObject()
{
  GLuint vaoId;
  glGenVertexArrays(1, &vaoId);
  glBindVertexArray(vaoId);
}

void load(GLFWwindow **window)
{
  pstates *prog = (pstates *) glfwGetWindowUserPointer(*window);
  if(prog == NULL)
    return; // need better error handling

  createVertexArrayObject();

  GLuint vertexShaderId = createShader("vertex.glsl", GL_VERTEX_SHADER);

  if(! loadProgram(prog, &prog->program32bit, vertexShaderId, createShader("fragment_32.glsl", GL_FRAGMENT_SHADER)))
  {
    return;
  }

  if( prog->GPUHas64BitSupport )
  {
    if(! loadProgram(prog, &prog->program64bit, vertexShaderId, createShader("fragment_64.glsl", GL_FRAGMENT_SHADER)))
    {
      return;
    }
  }

  updateProgram(prog);
}

void render(GLFWwindow **window)
{
  pstates *prog = (pstates *) glfwGetWindowUserPointer(*window);
  if(prog == NULL)
    return; // need better error handling

  GLuint vboId, uniformBufferId;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  GLfloat Vertices[12] = {
      -1.0, -1.0,
       1.0, -1.0,
      -1.0,  1.0,
      -1.0,  1.0,
       1.0, -1.0,
       1.0,  1.0
  };


  // Vertex Buffer Objects
  glGenBuffers(1, &vboId);
  glBindBuffer(GL_ARRAY_BUFFER, vboId);
  glBufferData(GL_ARRAY_BUFFER, 12*sizeof(GLfloat), Vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // Uniform Buffer Objects
  glGenBuffers(1, &uniformBufferId);
  glBindBuffer(GL_UNIFORM_BUFFER, uniformBufferId);
  glBufferData(GL_UNIFORM_BUFFER, sizeof(prog->uniformStruct), &prog->uniformStruct, GL_DYNAMIC_DRAW);
  glBindBuffer(GL_UNIFORM_BUFFER, 0);
  glBindBufferBase(GL_UNIFORM_BUFFER, BINDING_POINT_INDEX, uniformBufferId);



  // Draw
  glDrawArrays(GL_TRIANGLES, 0, 6);//prog->h * prog->w);
  glfwSwapBuffers(*window);

  // Free memory
  glDeleteBuffers(1, &vboId);
  glDeleteBuffers(1, &uniformBufferId);
}

void mainloop(GLFWwindow **window)
{
  render(window);

  while (!glfwWindowShouldClose(*window))
  {
    glfwWaitEvents();
    glfwPollEvents();
  }
}

int getInputParameters(uniform_struct_t* uniformStruct)
{
  int s = 0;

  s += get_float("Real part of const: ", &uniformStruct->con[0]);
  s += get_float("Imaginary part of const: ", &uniformStruct->con[1]);
  s += get_int("Max iterations: ", &uniformStruct->maxi);
  printf("\n\n");

  return s;
}

void help(void)
{
  puts("\nUSAGE:");
  puts("arrow keys - move");
  puts("z/x or scroll - zoom in/out");
  puts("c/v - decrease/increase number of colors");
  puts("d - print debug information");
  puts("p - swap between 32 and 64 bit modes");
  puts("h - this help\n");
}

int main(void)
{
  pstates prog = init_pstates();

  if(getInputParameters(&prog.uniformStruct) != 3)
  {
    puts("Erroneous getInputParameters.");
    return 1;
  }

  GLFWwindow *window = NULL;
  glfwSetErrorCallback(error_callback);

  if(init(&window, prog.uniformStruct.res))
    exit(EXIT_FAILURE);

  glfwSetKeyCallback(window, key_callback);
  glfwSetWindowSizeCallback(window, resize_callback);
  glfwSetWindowIconifyCallback(window, iconify_callback);
  glfwSetScrollCallback(window, scroll_callback);

  glfwSetWindowUserPointer(window, &prog);
  glfwMakeContextCurrent(window);

  glewExperimental = GL_TRUE; // need for VAO
  if(glewInit() != GLEW_OK)
    exit(EXIT_FAILURE);

  bool GL_double = false;
  GLint n = 0;
  glGetIntegerv(GL_NUM_EXTENSIONS, &n);
  for (GLint i = 0; i < n; i++) {
    const GLchar * ext = (GLchar *)glGetStringi(GL_EXTENSIONS, i);  // u -> sig!
    if (strcmp(ext, "GL_ARB_gpu_shader_fp64") == 0) {
      GL_double = true;
      break;
    }
  }

  if( ! GL_double ) {
    prog.GPUHas64BitSupport = false;
    fprintf(stderr,
            "ERROR: Your GPU does not support GL_ARB_gpu_shader_fp64!\n");
    fprintf(stderr, "Falling back to 32-bit mode.\n\n");
  }

  load(&window);
  mainloop(&window);

  glfwDestroyWindow(window);
  glfwTerminate();

  exit(EXIT_SUCCESS);
}
