# Examplelib C library

This is a template library for C using CMake that can be modified to easily add examples and tests. To adapt for whatever library you are making, change the `PROJECT_NAME` in [CMakeLists.txt](./CMakeLists.txt). 

This uses [check](https://github.com/libcheck/check) for testing, which can be linked to relatively easily using [vcpkg](https://github.com/microsoft/vcpkg). If you already have vcpkg on your machine, define and environmental variable `VCPKG_ROOT` pointing to its location. To add tests, use the `make_test` function defined in [test/CMakeLists.txt](./test/CMakeLists.txt). The same goes for examples, but instead use `make_example` defined in [example/CMakeLists.txt](./test/CMakeLists.txt). 

Obviously you may need to tweak a few things in each `CMakeLists.txt`, but otherwise this will build after installing vcpkg and check. Refer to the linked repos for vcpkg and check if you need it. This is more for my personal use, but I figured I'd make it public.

