cmake_minimum_required(VERSION 3.0.0)
project("${LIBRARY_NAME}_test" VERSION 0.1.0)

# include 'check' library and necessary dependencies
set(${LIBRARY_NAME}_TEST_LIBRARIES "${LIBRARY_NAME}" "check")
if(LINUX)
    list(APPEND ${LIBRARY_NAME}_TEST_LIBRARIES "rt" "pthread")
endif()

# flags for MSVC
if(CMAKE_C_COMPILER_ID MATCHES "MSVC")
    set(OPTIONS /MD)
     if(HAS_PERMISSIVE_FLAG)
        set(OPTIONS ${OPTIONS} /permissive-)
    endif()

# flags for GNU/Clang
elseif(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_VERBOSE_MAKEFILE ON)
    set(OPTIONS -Werror)

    list(APPEND ${LIBRARY_NAME}_TEST_LIBRARIES "m")

endif()

# helper function to make a test
function(make_test src target)
    add_executable(${target} ${src} ${${LIBRARY_NAME}_SOURCE_FILES})
    target_compile_options(${target} PRIVATE ${OPTIONS})
    target_link_libraries(${target} PRIVATE ${${LIBRARY_NAME}_TEST_LIBRARIES})
    set_target_properties(${target} PROPERTIES C_EXTENSIONS OFF)
    add_test(NAME ${target} COMMAND ${target})
endfunction()

# include/link for different OS's and 
if (WIN32)
    if(VCPKG)
        include_directories("${VCPKG_PATH}/installed/x64-windows/include")
        link_directories("${VCPKG_PATH}/installed/x64-windows/lib")
    elseif()
        message(SEND_ERROR "Please define include and link directories here: tests/CMakeLists.txt: ${CMAKE_CURRENT_LIST_LINE}")
        # include_directories("")
        # link_directories("")
    endif()
elseif(LINUX)
    if(VCPKG)
        include_directories("${VCPKG_PATH}/installed/x64-linux/include")
        link_directories("${VCPKG_PATH}/installed/x64-linux/lib")
    elseif()
        message(SEND_ERROR "Please define include and link directories here: tests/CMakeLists.txt: ${CMAKE_CURRENT_LIST_LINE}")
        # include_directories("")
        # link_directories("")
    endif()
else()
    message(SEND_ERROR "I assume this is a Mac which I do not know much about, so manual configuration is necessary here: tests/CMakeLists.txt: ${CMAKE_CURRENT_LIST_LINE}" )
endif()

add_compile_definitions(ROOT_DIR="${CMAKE_SOURCE_DIR}")
add_compile_definitions(TEST_PRINT_MODE=CK_NORMAL)

make_test(test.c ${PROJECT_NAME})