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
		prog->zoom *= 2.0;
		render(&window);
		break;

	case GLFW_KEY_X:
		prog->zoom /= 2.0;
		render(&window);
		break;

	case GLFW_KEY_LEFT:
		prog->posX -= 1.0/prog->zoom;
		render(&window);
		break;

	case GLFW_KEY_RIGHT:
		prog->posX += 1.0/prog->zoom;
		render(&window);
		break;

	case GLFW_KEY_DOWN:
		prog->posY -= 1.0/prog->zoom;
		render(&window);
		break;

	case GLFW_KEY_UP:
		prog->posY += 1.0/prog->zoom;
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
		       prog->zoom, prog->posX, prog->posY, prog->vis);
		break;

	case GLFW_KEY_H:
		help();
		break;

	default:
		break;
	}
}

extern void resize_callback(GLFWwindow *window, int width, int height)
{
	pstates *prog = (pstates *) glfwGetWindowUserPointer(window);
	if(prog == NULL)
		return;

	prog->w = width;
	prog->h = height;
	glViewport(0, 0, (GLint)width, (GLint)height);
	render(&window);
}

extern void iconify_callback(GLFWwindow *window, int iconified)
{
	if(iconified == GL_FALSE)
		render(&window);
}
