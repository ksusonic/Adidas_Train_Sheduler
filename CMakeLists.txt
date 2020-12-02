cmake_minimum_required(VERSION 3.17)
project(Adidas)

set(CMAKE_CXX_STANDARD 20)

set(CURL_LIBRARY "-lcurl")
find_package(CURL REQUIRED)
add_executable(Adidas main.cpp)
include_directories(${CURL_INCLUDE_DIR})
target_link_libraries(Adidas ${CURL_LIBRARIES})

