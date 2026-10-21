cmake_minimum_required(VERSION 4.0)
project(kovalevskaya VERSION 0.0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-Wall -O3 -fopenmp -march=native -funroll-loops)

find_package(SDL3 REQUIRED)

if (UNIX)
    find_package(OpenMP REQUIRED)
endif()

file(GLOB SOURCES "src/*.cpp" "src/*/*.cpp" "src/*/*/*.cpp" "src/*/*/*/*.cpp")
add_executable(kovalevskaya main.cpp ${SOURCES})
target_include_directories(kovalevskaya PRIVATE "include")

if (UNIX)
    target_link_libraries(kovalevskaya PRIVATE SDL3::SDL3 OpenMP::OpenMP_CXX)
elseif (WIN32)
    target_link_libraries(kovalevskaya PRIVATE SDL3::SDL3)
endif()

find_package(doctest REQUIRED)

file(GLOB TESTING_SOURCES "src/maths/*.cpp" "src/types/*/*.cpp" "src/types/*/*/*.cpp" "src/util/*.cpp" "src/render/raytracer/lighting.cpp" "src/utils/*.cpp" "tests/*.cpp" "tests/misc/base.h")
add_executable(kovalevskaya_test ${TESTING_SOURCES})
target_include_directories(kovalevskaya_test PRIVATE "include")

if (UNIX)
    target_link_libraries(kovalevskaya_test PRIVATE doctest::doctest)
elseif (WIN32)
    target_link_libraries(kovalevskaya_test PRIVATE doctest::doctest)
endif()