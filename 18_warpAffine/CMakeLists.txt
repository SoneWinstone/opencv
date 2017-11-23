cmake_minimum_required(VERSION 3.8)
project(18_warpAffine)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
add_executable(18_warpAffine ${SOURCE_FILES})

set(OpenCV_DIR "E:\\OpenCV3.2\\opencv\\MinGW-build")
find_package(OpenCV REQUIRED)

target_link_libraries(18_warpAffine ${OpenCV_LIBS})