/*
 *  Copyright (c) Hubert Jarosz. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for full license information.
 */

#pragma once

#include <stdint.h>

typedef struct program_states {
	int32_t maxi, vis;
	uint32_t res[2];
	float con[2], pos[2];
	float zoom_32, offset;
	double zoom_64;
} pstates;
