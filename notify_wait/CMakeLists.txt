cmake_minimum_required(VERSION 2.8)
project(sample CXX)

set(CMAKE_CXX_FLAGS "-std=c++11")

file(GLOB SRC RELATIVE ${PROJECT_SOURCE_DIR} src/*.cpp)
add_executable(${PROJECT_NAME} ${SRC})

foreach(S ${SRC})
    message(${S})
endforeach()

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} pthread)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
