/*
 *  Copyright (c) Hubert Jarosz. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for full license information.
 */

#pragma once

#include "includes.h"

#include <stdbool.h>

GLchar * getShader (const char * const path);

bool isOK( GLuint, const char * const );

bool compileShader( GLuint *, const char * const, GLenum );
