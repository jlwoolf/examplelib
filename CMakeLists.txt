cmake_minimum_required(VERSION 3.0.0)
project("examplelib" VERSION 0.1.0 LANGUAGES C)

set_property(GLOBAL PROPERTY C_STANDARD 90)

set(LIBRARY_NAME ${PROJECT_NAME})

# check if VCPKG exists and get path
set(VCPKG_PATH "$ENV{VCPKG_ROOT}")
if(${VCPKG_PATH} STREQUAL "")
    message(SEND_ERROR "VCPKG_ROOT environment variable undefined.")
else()
    set(VCPKG TRUE)
    set(CMAKE_TOOLCHAIN_FILE "${VCPKG_PATH}/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file")
endif()

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(IS_TOPLEVEL_PROJECT TRUE)
else()
    set(IS_TOPLEVEL_PROJECT FALSE)
endif()

# define LINUX helper variable
if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

# flags for building examples, tests, installing, and other flags
option(${LIBRARY_NAME}_OPT_BUILD_EXAMPLES "Build ${LIBRARY_NAME} examples" ${IS_TOPLEVEL_PROJECT})
option(${LIBRARY_NAME}_OPT_BUILD_TESTS "Build and perform ${LIBRARY_NAME} tests" ${IS_TOPLEVEL_PROJECT})
option(${LIBRARY_NAME}_OPT_INSTALL "Generate and install ${LIBRARY_NAME} target" ${IS_TOPLEVEL_PROJECT})
option(${LIBRARY_NAME}_OPT_EXAMPLE "Build ${LIBRARY_NAME} with example flag" FALSE)

FILE(GLOB_RECURSE ${LIBRARY_NAME}_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")
FILE(GLOB_RECURSE ${LIBRARY_NAME}_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/inc/*.h")

if(${LIBRARY_NAME}_OPT_OTHER)
    add_compile_definitions(${LIBRARY_NAME}_EXAMPLE)
    # list(APPEND ${LIBRARY_NAME}_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/${LIBRARY_NAME}_example.c;")
endif()

# build examples
if(${LIBRARY_NAME}_OPT_BUILD_EXAMPLES)
    add_subdirectory(example)    
endif()

# build tests
if(${LIBRARY_NAME}_OPT_BUILD_TESTS)
    enable_testing()
    include(CTest)
    add_subdirectory(test)
endif()

# build library
add_library(${LIBRARY_NAME} INTERFACE)
add_library(${LIBRARY_NAME}::${LIBRARY_NAME} ALIAS ${LIBRARY_NAME})

target_include_directories(${LIBRARY_NAME}
        INTERFACE
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
            $<INSTALL_INTERFACE:inc>)