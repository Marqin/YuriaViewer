/*
 *  Copyright (c) Hubert Jarosz. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for full license information.
 */


#include "includes.h"

color hsv2rgb(float hue, float sat, float val)
{
	int a;
	float b, c, d, e;
	color black = new_color(0l, 0l, 0l);

	if(val == 0)
	{
		return black;
	}

	hue /= 60;
	a = floor(hue);
	b = hue - (float)a;
	c = val * (1.0 - sat);
	d = val * (1.0 - (sat * b));
	e = val * (1.0 - (sat * (1.0 - b)));

	switch(a)
	{
	case 0:
		return new_color(val, e, c);

	case 1:
		return new_color(d, val, c);

	case 2:
		return new_color(c, val, e);

	case 3:
		return new_color(c, d, val);

	case 4:
		return new_color(e, c, val);

	case 5:
		return new_color(val, c, d);
	}

	return black;
}

double c_abs(complex c)
{
	return fabs(c.r*c.r + c.i*c.i);
}

color point_color(double x, double y, pstates *prog)
{
	complex new, old;
	int i;
	color result = new_color(0l, 0l, 0l);

	new.r = 1.5 * (x - prog->w / 2.0) / (0.5 * prog->zoom * prog->w)
                + prog->posX * 0.5;
	new.i = (y - prog->h / 2.0) / (0.5 * prog->zoom * prog->h)
                + prog->posY * 0.5;

	for(i = 0; i < prog->maxi && c_abs(new) <= 4.0; i++)
	{
		old = new;
		new.r = old.r * old.r - old.i * old.i + prog->con.r;
		new.i = 2.0 * old.r * old.i + prog->con.i;
	}

	if (i >= prog->vis)
	{
		result = hsv2rgb(((double) i)/prog->maxi * 360l, 0.6l, 1.0l);
	}

	return result;
}
