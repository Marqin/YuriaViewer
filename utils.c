/*
 *  Copyright (c) Hubert Jarosz. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for full license information.
 */


#include "includes.h"

int get_int(const char * const text, int32_t * i)
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

pstates init_pstates()
{
	pstates p;

	p.uniform.zoom_32 = 1.0;
	p.uniform.zoom_64 = 1.0;
	p.uniform.pos[0] = 0l;
	p.uniform.pos[1] = 0l;

	p.uniform.res[0] = 800;
	p.uniform.res[1] = 600;
	p.uniform.maxi = 0;
	p.uniform.vis = 50;

	p.uniform.con[0] = 0.0;
	p.uniform.con[1] = 0.0;

	p.precision = 64;
	p.support_64 = true;

	return p;
}
