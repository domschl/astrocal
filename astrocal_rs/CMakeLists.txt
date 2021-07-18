
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(ENV{RUSTFLAGS} "-L ~/git/CScratch/astrocal/build/AstroCal")
    set(CARGO_CMD cargo build --verbose)
    set(TARGET_DIR "debug")
else ()
    set(ENV{RUSTFLAGS} "-L /Users/dsc/git/CScratch/astrocal/build/AstroCal")
    set(CARGO_CMD cargo build --release --verbose)
    set(TARGET_DIR "release")
endif ()

set(ASTROCAL_RS "${CMAKE_CURRENT_BINARY_DIR}/${TARGET_DIR}/astrocal_rs")

add_custom_target(astrocal_rs ALL
    COMMENT "Compiling astrocal_rs"
    COMMAND cp -v "${CMAKE_CURRENT_BINARY_DIR}/../AstroCal/libAstroCal*" "${CMAKE_CURRENT_BINARY_DIR}/release/deps"
    COMMAND CARGO_TARGET_DIR=${CMAKE_CURRENT_BINARY_DIR} ${CARGO_CMD} 
    COMMAND cp ${ASTROCAL_RS} ${CMAKE_CURRENT_BINARY_DIR}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(astrocal_rs PROPERTIES LOCATION ${CMAKE_CURRENT_BINARY_DIR})

add_test(NAME astrocal_rs_test 
    COMMAND cargo test
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

