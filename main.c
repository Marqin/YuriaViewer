/*
 *  Copyright (c) Hubert Jarosz. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for full license information.
 */


#include "includes.h"
#include "shaders.h"

extern void error_callback(int error, const char *description);
extern void key_callback(GLFWwindow *window, int key, int scancode, int action,
                         int mods);
extern void resize_callback(GLFWwindow *window, int width, int height);
extern void iconify_callback(GLFWwindow *window, int iconified);

#define BINDING_POINT_INDEX 2

int init(GLFWwindow **window, uint32_t res[2])
{
	if (!glfwInit())
		return 1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	*window = glfwCreateWindow(res[0], res[1], "YuriaView 0.3", NULL, NULL);

	if (!(*window))
	{
		glfwTerminate();
		return 1;
	}

	return 0;
}

void load(GLFWwindow **window)
{
  pstates *prog = (pstates *) glfwGetWindowUserPointer(*window);
  if(prog == NULL)
    return; // need better error handling

	GLuint vaoId, vertexShaderId, fragment32ShaderId, fragment64ShaderId;

	// Vertex Array Obj
	glGenVertexArrays(1, &vaoId);
	glBindVertexArray(vaoId);

  if( ! compileShader(&vertexShaderId, "vertex.glsl", GL_VERTEX_SHADER) )
  {
    return;
  }
  if( ! compileShader(&fragment32ShaderId, "fragment_32.glsl", GL_FRAGMENT_SHADER) )
  {
    return;
  }
  if( ! compileShader(&fragment64ShaderId, "fragment_64.glsl", GL_FRAGMENT_SHADER) )
  {
    return;
  }

	prog->prog_32 = glCreateProgram();
	glAttachShader(prog->prog_32, vertexShaderId);
  glAttachShader(prog->prog_32, fragment32ShaderId);
  glLinkProgram(prog->prog_32);

  prog->prog_64 = glCreateProgram();
  glAttachShader(prog->prog_64, vertexShaderId);
  glAttachShader(prog->prog_64, fragment64ShaderId);
  glLinkProgram(prog->prog_64);


  unsigned int block_index;

  glUseProgram(prog->prog_64);
  block_index = glGetUniformBlockIndex(prog->prog_64, "ProgData");
  glUniformBlockBinding(prog->prog_64, block_index, BINDING_POINT_INDEX);

  glUseProgram(prog->prog_32);
  block_index = glGetUniformBlockIndex(prog->prog_32, "ProgData");
  glUniformBlockBinding(prog->prog_32, block_index, BINDING_POINT_INDEX);
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
	glBufferData(GL_UNIFORM_BUFFER, sizeof(*prog), prog, GL_DYNAMIC_DRAW);
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

int input(pstates *prog)
{
	int s = 0;

	s += get_float("Real part of const: ", &prog->con[0]);
	s += get_float("Imaginary part of const: ", &prog->con[1]);
	s += get_int("Max iterations: ", &prog->maxi);

	return s;
}

void help(void)
{
	puts("\nUSAGE:");
	puts("arrow keys - move");
	puts("z/x - zoom in/out");
	puts("c/v - decrease/increase number of colors");
	puts("d - print debug information");
  puts("p - swap between 32 and 64 bit modes");
	puts("h - this help\n");
}

int main(void)
{
	pstates prog = init_pstates();

	if(input(&prog) != 3)
	{
		puts("Erroneous input.");
		return 1;
	}

	GLFWwindow *window = NULL;
	glfwSetErrorCallback(error_callback);

	if(init(&window, prog.res))
		exit(EXIT_FAILURE);

	glfwSetKeyCallback(window, key_callback);
	glfwSetWindowSizeCallback(window, resize_callback);
	glfwSetWindowIconifyCallback(window, iconify_callback);

	glfwSetWindowUserPointer(window, &prog);
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE; // need for VAO
	if(glewInit() != GLEW_OK)
		exit(EXIT_FAILURE);

  load(&window);
  mainloop(&window);

	glfwDestroyWindow(window);
	glfwTerminate();

	exit(EXIT_SUCCESS);
}
