cmake_minimum_required(VERSION 3.20)

project(plot VERSION 0.0.1 DESCRIPTION "plot library")

file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ./)

include_directories(include)


FILE(GLOB lib_sources src/*)
FILE(GLOB exec_sources src/*)

list(FILTER lib_sources EXCLUDE REGEX "main.cpp")


message(${lib_sources})
message(${exec_sources})

add_compile_options(-g -Wall)

add_library(plot ${lib_sources})

add_executable(plot_e ${exec_sources})


#include(ExternalProject)
#ExternalProject_Add(freetype2
#  GIT_REPOSITORY    https://git.savannah.gnu.org/git/freetype/freetype2.git
#  GIT_TAG           master
#  SOURCE_DIR        "${CMAKE_BINARY_DIR}/packages/freetype"
#  BINARY_DIR        "${CMAKE_BINARY_DIR}/packages"
#  CONFIGURE_COMMAND cd "${CMAKE_BINARY_DIR}/packages/freetype"
#  BUILD_COMMAND     cd "${CMAKE_BINARY_DIR}/packages/freetype" && ./autogen.sh && ./configure && mkdir -p build && cd build && cmake .. && make
#  INSTALL_COMMAND   ""
#  TEST_COMMAND      ""
#  )





include(FetchContent)
FetchContent_Declare(
        freetype2
        GIT_REPOSITORY https://git.savannah.gnu.org/git/freetype/freetype2.git
        GIT_TAG master
)
FetchContent_MakeAvailable(freetype2)

#include(ExternalProject)
#ExternalProject_Add(freetype2
#  URL ./freetype2
#  PREFIX ${CMAKE_BINARY_DIR}/freetype2
#  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=.
#)

# include_directories(${CMAKE_BINARY_DIR}/packages/freetype/include)

# target_link_directories(plot_e PUBLIC ${CMAKE_BINARY_DIR}/packages/freetype/build)

set_target_properties(plot PROPERTIES PUBLIC_HEADER include/plot.hpp)


target_link_libraries(plot PRIVATE pthread GL glfw GLEW png freetype)
target_link_libraries(plot_e PRIVATE pthread GL glfw GLEW png freetype)

# add_dependencies(plot_e freetype2)
# add_dependencies(plot freetype2)
