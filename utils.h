/*
 *  Copyright (c) Hubert Jarosz. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for full license information.
 */

#pragma once

#include "structs.h"

int get_int(const char * const text, int * i);

int get_float(const char * const text, float * f);

pstates init_pstates();
