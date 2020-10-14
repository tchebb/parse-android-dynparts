cmake_minimum_required(VERSION 3.10)

project(parse-dynparts VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(liblp)

add_executable(parse-dynparts main.cpp)
target_compile_options(parse-dynparts PRIVATE -Wall -Wextra -pedantic)
target_link_libraries(parse-dynparts PRIVATE lp)
