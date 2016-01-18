/*
 *  Copyright (c) Hubert Jarosz. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for full license information.
 */


#include "includes.h"

extern void help(void);
extern void render(GLFWwindow **window);

extern void error_callback(int error, const char *description)
{
	printf("%d: %s\n", error, description);
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
		prog->zoom_64 *= 2.0;
		prog->zoom_32 = prog->zoom_64;
		render(&window);
		break;

	case GLFW_KEY_X:
		prog->zoom_64 /= 2.0;
		prog->zoom_32 = prog->zoom_64;
		render(&window);
		break;

	case GLFW_KEY_LEFT:
		prog->pos[0] -= 0.5;///prog->zoom_64;
		render(&window);
		break;

	case GLFW_KEY_RIGHT:
		prog->pos[0] += 0.5;///prog->zoom_64;
		render(&window);
		break;

	case GLFW_KEY_DOWN:
		prog->pos[1] -= 0.5;///prog->zoom_64;
		render(&window);
		break;

	case GLFW_KEY_UP:
		prog->pos[1] += 0.5;///prog->zoom_64;
		render(&window);
		break;

	case GLFW_KEY_C:
		prog->vis += 10;
		render(&window);
		break;

	case GLFW_KEY_V:
		prog->vis -= 10;
		render(&window);
		break;

	case GLFW_KEY_D:
		printf("z:%lf x:%lf y:%lf v:%d\n",
		       prog->zoom_64, prog->pos[0], prog->pos[1], prog->vis);
		break;

	case GLFW_KEY_H:
		help();
		break;

	case GLFW_KEY_P:
		if( ! prog->support_64 ) {
			fprintf(stderr, "Your GPU does not support GL_ARB_gpu_shader_fp64!\n");
			break;
		}
		if( prog->precision == 32 ) {
			prog->precision = 64;
			glUseProgram(prog->prog_64);
		} else {
			prog->precision = 32;
			glUseProgram(prog->prog_32);
		}
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

	prog->res[0] = width;
	prog->res[1] = height;
	glViewport(0, 0, (GLint)width, (GLint)height);
	render(&window);
}

extern void iconify_callback(GLFWwindow *window, int iconified)
{
	if(iconified == GL_FALSE)
		render(&window);
}
