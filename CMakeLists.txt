cmake_minimum_required(VERSION 3.8)
project(Background_blur)

set(CMAKE_CXX_STANDARD 11)
find_package(OpenCV REQUIRED)

set(SOURCE_FILES main.cpp)
add_executable(Background_blur ${SOURCE_FILES})
target_link_libraries(Background_blur ${OpenCV_LIBS})