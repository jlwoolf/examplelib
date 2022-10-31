include(CheckCCompilerFlag)

# compiler flags for GNU/Clang and MSVC
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    set(OPTIONS -Werror)
elseif(CMAKE_C_COMPILER_ID MATCHES "MSVC")
    set(OPTIONS /MD)
endif()

# helper function to make examples
function(make_example src target)
    add_executable(${target} ${src} ${${LIBRARY_NAME}_SOURCE_FILES})
    set_target_properties(${target} PROPERTIES C_EXTENSIONS OFF)
    target_compile_options(${target} PRIVATE ${OPTIONS})
    target_link_libraries(${target} PRIVATE ${LIBRARY_NAME})
endfunction()

make_example(example.c ${LIBRARY_NAME}_example)