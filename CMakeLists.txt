cmake_minimum_required(VERSION 3.20)

project(plot VERSION 0.0.1 DESCRIPTION "plot library")

file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ./)

include_directories(include)

include_directories(include packages/freetype2/include)

FILE(GLOB lib_sources src/*)
FILE(GLOB exec_sources src/*)

list(FILTER lib_sources EXCLUDE REGEX "main.cpp")


message(${lib_sources})
message(${exec_sources})

add_compile_options(-g -Wall)

add_library(plot ${lib_sources})

add_executable(plot_e ${exec_sources})

set_target_properties(plot PROPERTIES PUBLIC_HEADER include/plot.hpp)


target_link_libraries(plot PRIVATE pthread GL glfw GLEW png freetype)
target_link_libraries(plot_e PRIVATE pthread GL glfw GLEW png freetype)
