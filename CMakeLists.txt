cmake_minimum_required(VERSION 3.10)
project(MiProyectoImGui)

set(CMAKE_CXX_STANDARD 17)


find_package(OpenGL REQUIRED)
find_package(GLFW3 REQUIRED)


add_subdirectory(third-party/imgui)


include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${GLFW3_INCLUDE_DIRS})


set(SOURCE_FILES
    src/main.cpp
)


add_executable(MiProyectoImGui ${SOURCE_FILES})


target_link_libraries(MiProyectoImGui PRIVATE 
    imgui
    ${OPENGL_LIBRARIES}
    ${GLFW3_LIBRARIES}
    dl
)