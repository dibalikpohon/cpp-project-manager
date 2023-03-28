cmake_minimum_required(VERSION 3.1)

project(cpp_project_manager VERSION 0.0.1)

find_package(Argumentum CONFIG REQUIRED)
find_package(fmt)
find_package(GTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

add_library(init_proj_cmdopt OBJECT src/init_proj_cmdopt/init_proj_cmdopt.cpp)
add_library(cmakegen OBJECT src/cmakegen/cmakegen.cpp)

target_link_libraries(cmakegen PUBLIC fmt::fmt)

add_executable(pprojman src/main.cpp)
target_link_libraries(pprojman PRIVATE Argumentum::argumentum)
target_link_libraries(pprojman PRIVATE init_proj_cmdopt)

enable_testing()

add_executable(cmakegen_test test/cmakegen_test.cpp)
target_include_directories(cmakegen_test PRIVATE src/cmakegen)
target_link_libraries(cmakegen_test PRIVATE cmakegen)
target_link_libraries(cmakegen_test PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(cmakegen_test)
