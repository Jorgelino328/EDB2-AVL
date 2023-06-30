cmake_minimum_required(VERSION 3.0)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

project(EDB2-ABB)

include_directories(include)

file(GLOB_RECURSE TREE_SRC "src/*.cpp")

add_executable(
    EDB2-ABB
    ${TREE_SRC}
)

target_include_directories(
    EDB2-ABB PUBLIC
    include
)