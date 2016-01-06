/*
 *  Copyright (c) Hubert Jarosz. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for full license information.
 */


#include "includes.h"

int get_int(const char * const text, int * i)
{
	printf("%s", text);
	fflush(stdout);
	int s = scanf("%d", i);
	return s;
}

int get_float(const char * const text, float * d)
{
	printf("%s", text);
	fflush(stdout);
	int s = scanf("%f", d);
	return s;
}

complex new_complex(double r, double i)
{
	complex c;
	c.r = r;
	c.i = i;
	return c;
}

pstates init_pstates()
{
	pstates p;

	p.zoom = 1l;
	p.posX = 0l;
	p.posY = 0l;

	p.w = 800;
	p.h = 600;
	p.maxi = 0;
	p.vis = 50;

	p.con[0] = 0.0;
	p.con[1] = 0.0;

	return p;
}

color new_color(double r, double g, double b)
{
	color c;
	c.r = r;
	c.g = g;
	c.b = b;
	return c;
}
