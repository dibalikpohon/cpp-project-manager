cmake_minimum_required(VERSION 3.1)

project(cpp_project_manager VERSION 0.0.1)

find_package(Argumentum CONFIG REQUIRED)
find_package(fmt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

add_library(init_proj_cmdopt OBJECT src/init_proj_cmdopt/init_proj_cmdopt.cpp)

add_executable(pprojman src/main.cpp)
target_link_libraries(pprojman PRIVATE Argumentum::argumentum)
target_link_libraries(pprojman PRIVATE init_proj_cmdopt)
target_link_libraries(pprojman PRIVATE fmt::fmt)
