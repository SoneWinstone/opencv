cmake_minimum_required(VERSION 3.8)
project(11_edgeDetection)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
add_executable(11_edgeDetection ${SOURCE_FILES})

set(OpenCV_DIR "E:\\OpenCV3.2\\opencv\\MinGW-build")
find_package(OpenCV REQUIRED)

target_link_libraries(11_edgeDetection ${OpenCV_LIBS})