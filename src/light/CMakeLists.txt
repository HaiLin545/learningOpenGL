cmake_minimum_required(VERSION 3.24)
# set the project name
project(Light)

# main entry
set(MAIN_ENTRY 1_color)

set(main_file ${MAIN_ENTRY}.cpp)

# code
file(GLOB MAIN ${main_file})

add_executable(${PROJECT_NAME} ${MAIN} ${HEADS} ${DEPS})

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE glfw3)