cmake_minimum_required(VERSION 3.24)
# set the project name
project(LearningOpenGL)

add_compile_definitions(MY_ROOT="D:/learn/graphics/learningOpenGL/")

# dependency
set(INCLUDE_DIRS ./deps/include)
set(LIB_DIRS ./deps/lib)


file(GLOB HEADS ./heads/*.hpp heads/*.h)
file(GLOB DEPS ./deps/*.cpp deps/*.c deps/*.h)

include_directories(./heads ${INCLUDE_DIRS})
link_directories(${LIB_DIRS})

add_subdirectory(./src/basic)
add_subdirectory(./src/Light)