/*
 *  Copyright (c) Hubert Jarosz. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for full license information.
 */

#include "program.h"
#include "includes.h"

GLuint createProgram(GLuint vertexShaderId, GLuint fragmentShaderId)
{
    GLuint program = glCreateProgram();

    glAttachShader(program, vertexShaderId);
    glAttachShader(program, fragmentShaderId);
    glLinkProgram(program);

    glUseProgram(program);
    const GLuint block_index = glGetUniformBlockIndex(program, "ProgData");
    glUniformBlockBinding(program, block_index, BINDING_POINT_INDEX);

    return program;
}

bool loadProgram(pstates* applicationState, GLuint* programHandle, GLuint vertexShaderId, GLuint fragmentShaderId)
{
    *programHandle = createProgram(vertexShaderId, fragmentShaderId);
    if(! *programHandle) {
        return false;
    }
    applicationState->currentProgram = *programHandle;

    return true;
}

void updateProgram(pstates* applicationState)
{
    glUseProgram(applicationState->currentProgram);
}
