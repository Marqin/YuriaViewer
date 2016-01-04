/*
 *  Copyright (c) Hubert Jarosz. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for full license information.
 */

#pragma once

#include "includes.h"

const GLchar* vertexShader =
{
        "#version 410\n\
        \
        in vec2 in_Position;\n\
        in vec3 in_Color;\n\
        out vec4 ex_Color;\n\
        \
        void main(void)\n\
        {\n\
               gl_Position = vec4(in_Position, 0.0, 1.0);\n\
               ex_Color = vec4(in_Color, 1.0);\n\
        }\n"
};

const GLchar* fragmentShader =
{
        "#version 410\n\
        \
        in vec4 ex_Color;\n\
        out vec4 out_Color;\n\
        \
        void main(void)\n\
        {\n\
               out_Color = ex_Color;\n\
        }\n"
};
