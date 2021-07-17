add_executable (astroCalTest astroCalTest.c)

target_link_libraries (astroCalTest LINK_PUBLIC AstroCal m)

add_test(NAME AstroCalTest
    COMMAND astroCalTest
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
