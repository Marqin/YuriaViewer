/*
 * Copyright 2014 Hubert Jarosz
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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
