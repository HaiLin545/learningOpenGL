cmake_minimum_required(VERSION 3.24)

# set the project name
project(LearningOpenGL)

set(lib_dir D:/envs/openGL/GLFW)
set(INCLUDE_DIRS ${lib_dir}/include)
set(LIB_DIRS ${lib_dir}/lib)

set(MAIN_ENTRY 1_shader)
set(MAIN_ENTRY 2_texture)
# set(MAIN_ENTRY 3_transform)
set(main_file src/${MAIN_ENTRY}.cpp)

file(GLOB heads src/heads/*.hpp src/heads/*.h)
file(GLOB libs libs/*.cpp libs/*.c libs/*.h)
file(GLOB main ${main_file})

link_directories(${LIB_DIRS})
add_executable(${PROJECT_NAME} ${main} ${heads} ${libs})

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE glfw3)