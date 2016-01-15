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

	p.zoom_32 = 1.0;
	p.zoom_64 = 1.0;
	p.pos[0] = 0l;
	p.pos[1] = 0l;

	p.res[0] = 800;
	p.res[1] = 600;
	p.maxi = 0;
	p.vis = 50;

	p.con[0] = 0.0;
	p.con[1] = 0.0;

	return p;
}
