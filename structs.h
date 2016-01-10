/*
 *  Copyright (c) Hubert Jarosz. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for full license information.
 */

#pragma once

typedef struct program_states {
	int w, h, maxi, vis;
	double zoom, posX, posY;
	float con[2];
} pstates;
