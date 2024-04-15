cmake_minimum_required(VERSION 3.24)
# set the project name
project(LearningOpenGL)

# dependency
set(lib_dir D:/envs/openGL/GLFW)
set(INCLUDE_DIRS ${lib_dir}/include)
set(LIB_DIRS ${lib_dir}/lib)

add_compile_definitions(MY_ROOT="D:/learn/graphics/learningOpenGL/")

file(GLOB HEADS ./heads/*.hpp heads/*.h)
file(GLOB DEPS ./deps/*.cpp deps/*.c deps/*.h)

include_directories(./heads)
link_directories(${LIB_DIRS})

add_subdirectory(./src/basic)