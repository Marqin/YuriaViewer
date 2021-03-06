/*
*  Copyright (c) Hubert Jarosz. All rights reserved.
*  Licensed under the MIT license. See LICENSE file in the project root for full license information.
*/


#include "includes.h"

GLchar * getShader (const char * const path)
{

  FILE * f = fopen (path, "rb");
  if (!f)
  {
      return NULL;
  }

  fseek (f, 0, SEEK_END);
  long flen = ftell (f);
  fseek (f, 0, SEEK_SET);

  if((long long unsigned)flen > SIZE_MAX)
  {
    return NULL;
  }

  size_t length = (size_t)flen;
  char * buffer = NULL;

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


  return buffer;
}

bool isOK( GLuint shaderId, const char * const name )
{
  GLint isCompiled = 0;
  glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);
  if(isCompiled == GL_FALSE)
  {
    GLint maxLength = 0;
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);

    GLchar errorLog[maxLength];
    glGetShaderInfoLog(shaderId, maxLength, &maxLength, &errorLog[0]);
    printf( "%s: %s\n", name, errorLog );

    return false;
  }
  return true;
}

GLuint createShader(const char * const path, GLenum type)
{
  GLuint shaderId = glCreateShader(type);

  const GLchar * shader = getShader(path);
  glShaderSource(shaderId, 1, &shader, NULL);
  glCompileShader(shaderId);
  if( ! isOK(shaderId, path) )
  {
    glDeleteShader(shaderId);
    return 0;
  }
  return shaderId;
}
