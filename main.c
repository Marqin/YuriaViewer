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

int init(GLFWwindow **window, int width, int height)
{
	if (!glfwInit())
		return 1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	*window = glfwCreateWindow(width, height, "YuriaView 0.2", NULL, NULL);

	if (!(*window))
	{
		glfwTerminate();
		return 1;
	}

	return 0;
}

void load(void)
{
	GLuint programId, vaoId, vertexShaderId, fragmentShaderId;

	// Vertex Array Obj

	glGenVertexArrays(1, &vaoId);
	glBindVertexArray(vaoId);

	// Shaders
	const GLchar * vs = getShader("vertex.glsl");
	const GLchar * fs = getShader("fragment.glsl");

	vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderId, 1, &vs, NULL);
	glCompileShader(vertexShaderId);

	fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderId, 1, &fs, NULL);
	glCompileShader(fragmentShaderId);

	GLint isCompiled = 0;
	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &isCompiled);
	if(isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(fragmentShaderId, GL_INFO_LOG_LENGTH, &maxLength);

		GLchar errorLog[maxLength];
		glGetShaderInfoLog(fragmentShaderId, maxLength, &maxLength, &errorLog[0]);
		printf( "Fragment Shader ERR: %s\n", errorLog );

		glDeleteShader(fragmentShaderId); // Don't leak the shader.
		return;
	}

	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &isCompiled);
	if(isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(vertexShaderId, GL_INFO_LOG_LENGTH, &maxLength);

		GLchar errorLog[maxLength];
		glGetShaderInfoLog(vertexShaderId, maxLength, &maxLength, &errorLog[0]);
		printf( "Vertex Shader ERR: %s\n", errorLog );

		glDeleteShader(vertexShaderId); // Don't leak the shader.
		return;
	}

	programId = glCreateProgram();
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);

	glLinkProgram(programId);
	glUseProgram(programId);

	unsigned int block_index = glGetUniformBlockIndex(programId, "ProgData");
	glUniformBlockBinding(programId, block_index, BINDING_POINT_INDEX);
}

void render(GLFWwindow **window)
{
	pstates *prog = (pstates *) glfwGetWindowUserPointer(*window);
	if(prog == NULL)
		return; // need better error handling

	GLuint vboId, uniformBufferId;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	int i = 0;
	size_t s_Vertices;;
	s_Vertices = sizeof(GLfloat) * (2 * (prog->w) * (prog->h));
	GLfloat *Vertices = (GLfloat *) malloc(s_Vertices);

	GLfloat a = -1.0, b = -1.0;
	for(int x = 0; x < prog->w; x++, a += 2.0/prog->w)
	{
		for(int y = 0; y < prog->h; y++, b += 2.0/prog->h)
		{
			Vertices[i] = a;
			Vertices[i+1] = b;
			i += 2;
		}
		b = -1.0;
	}


	// Vertex Buffer Objects
	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, s_Vertices, Vertices, GL_STATIC_DRAW);
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
	glDrawArrays(GL_POINTS, 0, prog->h * prog->w);
	glfwSwapBuffers(*window);

	// Free memory
	glDeleteBuffers(1, &vboId);
	glDeleteBuffers(1, &uniformBufferId);
	free(Vertices);
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

	GLint n=0;
	int GL_double=0;
	glGetIntegerv(GL_NUM_EXTENSIONS, &n);
	for (GLint i = 0; i < n; i++) {
		const GLchar * ext = (GLchar *)glGetStringi(GL_EXTENSIONS, i);  // u -> sig!
		if (strcmp(ext, "GL_ARB_gpu_shader_fp64") == 0) {
			GL_double = 1;
			break;
		}
	}

	if(GL_double) {
		load();
		mainloop(&window);
	} else {
		fprintf(stderr, "ERROR: Your GPU does not support GL_ARB_gpu_shader_fp64!");
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	exit(EXIT_SUCCESS);
}
