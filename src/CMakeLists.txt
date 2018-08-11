find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW 2 REQUIRED)

add_executable(YuriaViewer main.c callbacks.c utils.c shaders.c program.c program.h)

target_link_libraries(YuriaViewer
        OpenGL::GL
        glfw
        GLEW::GLEW)

configure_file(../shaders/fragment_32.glsl fragment_32.glsl COPYONLY)
configure_file(../shaders/fragment_64.glsl fragment_64.glsl COPYONLY)
configure_file(../shaders/vertex.glsl vertex.glsl COPYONLY)
