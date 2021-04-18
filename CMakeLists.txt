cmake_minimum_required(VERSION 3.17)

project(CppCCQtemplate)

set(CMAKE_CXX_STANDARD 17)

include(CMake/conan.cmake)
conan_cmake_run(REQUIRES
    qt/6.0.1@bincrafters/stable
    BASIC_SETUP CMAKE_TARGETS
    BUILD missing)

add_subdirectory(src)
