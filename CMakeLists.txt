cmake_minimum_required(VERSION 3.0.0)
project("examplelib" VERSION 0.1.0 LANGUAGES C)

set_property(GLOBAL PROPERTY C_STANDARD 90)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
  CACHE STRING "Vcpkg toolchain file")

set(LIBRARY_NAME ${PROJECT_NAME})
set(VCPKG_PATH "C:/Users/jlwoolf/Documents/Projects/C/vcpkg")

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(IS_TOPLEVEL_PROJECT TRUE)
else()
    set(IS_TOPLEVEL_PROJECT FALSE)
endif()

option(${PROJECT_NAME}_OPT_BUILD_EXAMPLES "Build ${PROJECT_NAME} examples" ${IS_TOPLEVEL_PROJECT})
option(${PROJECT_NAME}_OPT_BUILD_TESTS "Build and perform ${PROJECT_NAME} tests" ${IS_TOPLEVEL_PROJECT})
option(${PROJECT_NAME}_OPT_INSTALL "Generate and install ${PROJECT_NAME} target" ${IS_TOPLEVEL_PROJECT})
option(${PROJECT_NAME}_OPT_EXAMPLE "Build ${PROJECT_NAME} with example flag" TRUE)

set(${PROJECT_NAME}_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(${PROJECT_NAME}_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/${PROJECT_NAME}.c")
set(${PROJECT_NAME}_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/inc/${PROJECT_NAME}.h")

if(${PROJECT_NAME}_OPT_OTHER)
    add_compile_definitions(${PROJECT_NAME}_EXAMPLE)
    # list(APPEND ${LIBRARY_NAME}_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/${LIBRARY_NAME}_windows.c;")
endif()

if(${PROJECT_NAME}_OPT_BUILD_EXAMPLES)
    add_subdirectory(example)    
endif()

if(${PROJECT_NAME}_OPT_BUILD_TESTS)
    enable_testing()
    include(CTest)
    add_subdirectory(test)
endif()

add_library(${PROJECT_NAME} INTERFACE)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
        INTERFACE
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
            $<INSTALL_INTERFACE:inc>)