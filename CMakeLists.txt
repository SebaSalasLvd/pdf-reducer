cmake_minimum_required(VERSION 3.10)
project(MiProyectoImGui)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(third-party/imgui)

set(SOURCE_FILES
    src/main.cpp
)

add_executable(MiProyectoImGui ${SOURCE_FILES})
target_link_libraries(MiProyectoImGui PRIVATE imgui)