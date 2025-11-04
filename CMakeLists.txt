cmake_minimum_required(VERSION 3.11)
project(lock-free-data-structures)

add_executable(${PROJECT_NAME} src/main.cpp src/queue.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE atomic)

set_property(TARGET ${PROJECT_NAME} PROPERTY CMAKE_CXX_STANDARD 23 CMAKE_CXX_STANDARD_REQUIRED ON)
