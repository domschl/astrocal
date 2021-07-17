add_test(NAME AstroCalJl
    COMMAND julia astrocal.jl
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
