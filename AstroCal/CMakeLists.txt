add_library (AstroCal SHARED astrocal.c)

target_include_directories (AstroCal PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
