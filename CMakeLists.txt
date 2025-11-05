cmake_minimum_required(VERSION 3.11)
project(lock-free-data-structures)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME} src/main.cpp src/stack.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE atomic)
