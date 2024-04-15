cmake_minimum_required(VERSION 3.24)

# set the project name
project(Basic)
# main entry
#set(MAIN_ENTRY 1_shader)
#set(MAIN_ENTRY 2_texture)
#set(MAIN_ENTRY 3_transform)
set(MAIN_ENTRY 4_3d)
set(MAIN ${MAIN_ENTRY}.cpp)

add_executable(${PROJECT_NAME} ${MAIN} ${HEADS} ${DEPS} )

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE glfw3)