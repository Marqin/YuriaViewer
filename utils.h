/*
 *  Copyright (c) Hubert Jarosz. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for full license information.
 */

#pragma once

#include "structs.h"

int get_int(const char * const text, int * i);

int get_double(const char * const text, double * d);

complex new_complex(double r, double i);

pstates init_pstates();

color new_color(double r, double g, double b);
