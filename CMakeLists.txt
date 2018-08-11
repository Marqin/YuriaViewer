cmake_minimum_required(VERSION 3.10)

project(YuriaViewer)

set(CMAKE_C_STANDARD 99)
set(C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -Werror -pedantic -Wall -Wextra -Wshadow -Wstrict-overflow=5")

add_subdirectory (src)