# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 3.1.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project (AstroCalHome)

# Recurse into the "Hello" and "Demo" subdirectories. This does not actually
# cause another cmake executable to run. The same process will walk through
# the project's entire directory structure.
add_subdirectory (AstroCal)
add_subdirectory (AstroCalTest)

set_property(TARGET AstroCal PROPERTY C_STANDARD 11)
