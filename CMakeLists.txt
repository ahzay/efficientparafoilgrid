cmake_minimum_required(VERSION 3.25)
project(efficientparafoilgrid)

set(CMAKE_CXX_STANDARD 23)

# Set the include directories
include_directories(/usr/include/alglib)
link_directories(/usr/lib)
find_package(OpenMP REQUIRED)
if(OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()


add_executable(efficientparafoilgrid main.cpp main.h state.cpp state.h attributes.cpp attributes.h
        parameters.cpp parameters.h cmdlineoptions.cpp cmdlineoptions.h visualizer.cpp visualizer.h)
target_link_libraries(efficientparafoilgrid alglib)
