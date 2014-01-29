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
#include "shaders.h"

extern void error_callback(int error, const char* description);
extern void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
extern void resize_callback(GLFWwindow* window, int width, int height);
extern void iconify_callback(GLFWwindow * window, int iconified);
extern color point_color(double x, double y, pstates* prog);


int init(GLFWwindow** window, int width, int height)
{
  if (!glfwInit())
    return 1;
  
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  
  *window = glfwCreateWindow(width, height, "YuriaView 0.1", NULL, NULL);
  
  if (!(*window))
  {
    glfwTerminate();
    return 1;
  }
  
  return 0;
}

void load()
{  
  GLuint vaoId, vertexShaderId,
  fragmentShaderId,  programId;
        
  // Vertex Array Obj
  
  glGenVertexArrays(1, &vaoId);
  glBindVertexArray(vaoId);
  
  // Shaders
  
  vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShaderId, 1, &vertexShader, NULL);
  glCompileShader(vertexShaderId);

  fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShaderId, 1, &fragmentShader, NULL);
  glCompileShader(fragmentShaderId);

  programId = glCreateProgram();
  glAttachShader(programId, vertexShaderId);
  glAttachShader(programId, fragmentShaderId);
  glLinkProgram(programId);
  glUseProgram(programId);
  
}

void render(GLFWwindow** window)
{
    pstates * prog = (pstates*) glfwGetWindowUserPointer(*window);
    if(prog == NULL) return; // need better error handling
  
    GLuint vboId, colorBufferId;
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    int i=0, j=0;
    size_t s_Vertices, s_Colors;
    s_Vertices = sizeof(GLfloat)*(2 * (prog->w) * (prog->h));
    s_Colors = sizeof(GLfloat)*(3 * (prog->w) * (prog->h));
    GLfloat* Vertices = (GLfloat*) malloc(s_Vertices);
    GLfloat* Colors = (GLfloat*) malloc (s_Colors);

    GLfloat a = -1.0,b = -1.0;
    for(int x = 0; x < prog->w; x++, a += 2.0/prog->w)
    {
      for(int y = 0; y < prog->h; y++, b += 2.0/prog->h)
      {
        Vertices[j]=a;
        Vertices[j+1]=b;
        j+=2;
      }
      b = -1.0;
    }

    for(int x = 0; x < prog->w; x++)
      for(int y = 0; y < prog->h; y++)
      {
        color point = point_color((double) x, (double) y, prog);
        Colors[i] = (float) point.r;
        Colors[i+1] = (float) point.g;
        Colors[i+2] = (float) point.b;
        i+=3;
      }
  
  // Vertex Buffer Objects
  glGenBuffers(1, &vboId);
  glBindBuffer(GL_ARRAY_BUFFER, vboId);
  glBufferData(GL_ARRAY_BUFFER, s_Vertices, Vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0,2, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);
  
  // Color Buffer
  glGenBuffers(1, &colorBufferId);
  glBindBuffer(GL_ARRAY_BUFFER, colorBufferId);
  glBufferData(GL_ARRAY_BUFFER, s_Colors, Colors, GL_STATIC_DRAW);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(1);
  
  // Draw
  glDrawArrays(GL_POINTS, 0, prog->h * prog->w);    
  glfwSwapBuffers(*window);
  
  // Free memory
  glDeleteBuffers(1, &vboId);
  glDeleteBuffers(1, &colorBufferId);
  free(Vertices);
  free(Colors);  
}

void mainloop(GLFWwindow** window)
{
  render(window);
  
  while (!glfwWindowShouldClose(*window))
  {
    
    // Process events
    glfwWaitEvents();
    glfwPollEvents();
  
  }
  
}

void input(pstates *prog)
{
  puts("Real part of const:");
  scanf("%lf", &prog->con.r);
  puts("Imaginary part of const:");
  scanf("%lf", &prog->con.i);
  puts("Max iterations:");
  scanf("%d", &prog->maxi);
}

void help()
{
  puts("\nUSAGE:");
  puts("arrow keys - move");
  puts("z/x - zoom in/out");
  puts("c/v - decrease/increase number of colors");
  puts("d - print debug information");
  puts("h - this help\n");
}

int main(void)
{
  pstates prog;  
  
  input(&prog);
  
  //** INIT BEGIN **//
  prog.w = 640;
  prog.h = 480;
  prog.zoom = 1;
  prog.posX = prog.posY = 0;
  prog.vis = 50;
  //** INIT END **//
  
  GLFWwindow* window=NULL;
  glfwSetErrorCallback(error_callback);
  
  if(init(&window, prog.w, prog.h))
    exit(EXIT_FAILURE);

  glfwSetKeyCallback(window, key_callback);
  glfwSetWindowSizeCallback(window, resize_callback);
  glfwSetWindowIconifyCallback(window, iconify_callback);
  
  glfwSetWindowUserPointer(window, &prog);
  glfwMakeContextCurrent(window);
  
  glewExperimental = GL_TRUE; // need for VAO
  if(glewInit() != GLEW_OK)
    exit(EXIT_FAILURE);
  
  load();
  
  mainloop(&window);
  
  glfwDestroyWindow(window);
  glfwTerminate();
  
  exit(EXIT_SUCCESS);
}
