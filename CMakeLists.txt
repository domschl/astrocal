cmake_minimum_required (VERSION 3.1.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project (AstroCalHome)

add_subdirectory (AstroCal)
add_subdirectory (AstroCalTest)
add_subdirectory (astrocal_rs)

set_property(TARGET AstroCal PROPERTY C_STANDARD 11)
