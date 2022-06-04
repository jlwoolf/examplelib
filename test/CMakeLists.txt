cmake_minimum_required(VERSION 3.0.0)
project("${LIBRARY_NAME}_test" VERSION 0.1.0)

set(${LIBRARY_NAME}_TEST_LIBRARIES "${LIBRARY_NAME}" "check")

if(CMAKE_C_COMPILER_ID MATCHES "MSVC")
    set(OPTIONS /MD)
     if(HAS_PERMISSIVE_FLAG)
        set(OPTIONS ${OPTIONS} /permissive-)
    endif()

elseif(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_VERBOSE_MAKEFILE ON)
    set(OPTIONS -Werror)

    list(APPEND ${LIBRARY_NAME}_TEST_LIBRARIES "m")

endif()

function(make_test src target)
    add_executable(${target} ${src} ${${LIBRARY_NAME}_SOURCE_FILES})
    target_compile_options(${target} PRIVATE ${OPTIONS})
    target_link_libraries(${target} PRIVATE ${${LIBRARY_NAME}_TEST_LIBRARIES})
    set_target_properties(${target} PROPERTIES C_EXTENSIONS OFF)
    add_test(NAME ${target} COMMAND ${target})
endfunction()

if (WIN32)
    include_directories("${VCPKG_PATH}/installed/x64-windows/include")
    link_directories("${VCPKG_PATH}/installed/x64-windows/lib")
else()
    include_directories("${VCPKG_PATH}/installed/x64-linux/include")
    link_directories("${VCPKG_PATH}/installed/x64-linux/lib")
endif()


add_compile_definitions(ROOT_DIR="${CMAKE_SOURCE_DIR}")
add_compile_definitions(TEST_PRINT_MODE=CK_NORMAL)

make_test(test.c ${PROJECT_NAME})