#include "includes.h"
#include "shaders.h"

extern void error_callback(int error, const char* description);
extern void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

int init(GLFWwindow** window)
{
  if (!glfwInit())
    return 1;
  
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  
  *window = glfwCreateWindow(640, 480, "YuriaView 0.1", NULL, NULL);
  
  if (!(*window))
  {
    glfwTerminate();
    return 1;
  }
  
  return 0;
}

void load()
{
// Some simple testing code.
  GLuint vaoId, vboId, vertexShaderId,
         fragmentShaderId, programId, colorBufferId;
        
  GLfloat Vertices[] = {
                -0.8f, -0.8f, 0.0f, 1.0f,
                 0.0f,  0.8f, 0.0f, 1.0f,
                 0.8f, -0.8f, 0.0f, 1.0f
  };

  GLfloat Colors[] = {
                1.0f, 0.0f, 0.0f, 1.0f,
                0.0f, 1.0f, 0.0f, 1.0f,
                0.0f, 0.0f, 1.0f, 1.0f
  };


  // Vertex Array Obj
  
  glGenVertexArrays(1, &vaoId);
  glBindVertexArray(vaoId);
  
  // Vertex Buffer Obj
  
  glGenBuffers(1, &vboId);
  glBindBuffer(GL_ARRAY_BUFFER, vboId);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);
  
  // Color Buffer
  
  glGenBuffers(1, &colorBufferId);
  glBindBuffer(GL_ARRAY_BUFFER, colorBufferId);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(1);
  
  // Shaders
  
  vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShaderId, 1, &VertexShader, NULL);
  glCompileShader(vertexShaderId);

  fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShaderId, 1, &FragmentShader, NULL);
  glCompileShader(fragmentShaderId);

  programId = glCreateProgram();
  glAttachShader(programId, vertexShaderId);
  glAttachShader(programId, fragmentShaderId);
  glLinkProgram(programId);
  glUseProgram(programId);

}


void render(GLFWwindow** window)
{

  // Some simple testing code.
  while (!glfwWindowShouldClose(*window))
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    
        
    glDrawArrays(GL_TRIANGLES, 0, 3);    
    
    glfwSwapBuffers(*window);
    glfwPollEvents();
  }
  
}

int main(void)
{
  GLFWwindow* window=NULL;
  glfwSetErrorCallback(error_callback);
  
  if(init(&window))
    exit(EXIT_FAILURE);

  glfwSetKeyCallback(window, key_callback);
  glfwMakeContextCurrent(window);
  
  glewExperimental = GL_TRUE; // need for VAO
  if(glewInit() != GLEW_OK)
    return -1;
  glViewport(0, 0, 640,480);
  
  load();
  render(&window);
  
  glfwDestroyWindow(window);
  glfwTerminate();
  
  exit(EXIT_SUCCESS);
}
