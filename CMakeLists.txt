cmake_minimum_required(VERSION 3.16.0)
# include($ENV{IOT_SOLUTION_PATH}/component.cmake)
add_compile_options(-fdiagnostics-color=always)

list(APPEND EXTRA_COMPONENT_DIRS 
                                "${CMAKE_SOURCE_DIR}/components"
                                "${CMAKE_SOURCE_DIR}/components/bus"
                                "${CMAKE_SOURCE_DIR}/components/display"
                                )
include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(HoloCube)

