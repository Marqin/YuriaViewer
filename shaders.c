/*
*  Copyright (c) Hubert Jarosz. All rights reserved.
*  Licensed under the MIT license. See LICENSE file in the project root for full license information.
*/


#include "includes.h"

GLchar * getShader (const char * const path)
{
	char * buffer = NULL;
	size_t length;
	FILE * f = fopen (path, "rb");

	if (f)
	{
		fseek (f, 0, SEEK_END);
		length = ftell (f);
		fseek (f, 0, SEEK_SET);
		buffer = calloc (length+1, sizeof(char));
		for( size_t i = 0; i < length+1; i++ ) {
			buffer[i] = '\0';
		}
		if (buffer)
		{
			size_t status = fread (buffer, 1, length, f);
			if( status != length ) {
				fprintf(stderr, "Error while reading \"%s\" file!\n", path);
				buffer[0] = '\0';
			}
		}
		fclose (f);
	}

	return buffer;
}
