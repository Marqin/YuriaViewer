/*
 *  Copyright (c) Hubert Jarosz. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for full license information.
 */

#pragma once

#include <stdint.h>

typedef struct program_states {
	int32_t w, h, maxi, vis;
	#ifdef single
		float zoom, posX, posY, offset;
	#else
		double zoom, posX, posY;
	#endif
	float con[2];
} pstates;
