cmake_minimum_required(VERSION 3.20)

project(CppCCQtemplate)

option(BUILD_UNIT_TESTS "Build unit tests (default OFF)" OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CMake/conan.cmake)
conan_cmake_run(REQUIRES
    qt/6.0.1@bincrafters/stable
    openssl/1.1.1j
    BASIC_SETUP CMAKE_TARGETS
    BUILD missing)

add_subdirectory(src)

if (BUILD_UNIT_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()