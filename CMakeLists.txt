cmake_minimum_required(VERSION 3.10)

project(YuriaViewer)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW 2 REQUIRED)

set(CMAKE_C_STANDARD 99)
set(C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -Werror -pedantic -Wall -Wextra -Wshadow -Wstrict-overflow=5")

add_executable(YuriaViewer main.c callbacks.c utils.c shaders.c)

target_link_libraries(YuriaViewer
        OpenGL::GL
        glfw
        GLEW::GLEW)

configure_file(fragment_32.glsl fragment_32.glsl COPYONLY)
configure_file(fragment_64.glsl fragment_64.glsl COPYONLY)
configure_file(vertex.glsl vertex.glsl COPYONLY)
