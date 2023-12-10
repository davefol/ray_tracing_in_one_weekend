cmake_minimum_required(VERSION 3.0.0)
project(ray_tracer_in_one_weekend VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(ray_tracer_in_one_weekend main.cpp)
include_directories(include)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
