cmake_minimum_required (VERSION 3.1.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project (AstroCalHome)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
endif()
  
add_subdirectory (AstroCal)
add_subdirectory (AstroCalTest)
add_subdirectory (Astrocal.jl)
add_subdirectory (astrocal_rs)

set_property(TARGET AstroCal PROPERTY C_STANDARD 11)
