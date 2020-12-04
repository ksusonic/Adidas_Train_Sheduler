cmake_minimum_required(VERSION 3.17)
project(Adidas)

set(CMAKE_CXX_STANDARD 20)

# Libcurl library
set(CURL_LIBRARY "-lcurl")
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})

add_executable(Adidas main.cpp User.cpp User.h parser.h)

target_link_libraries(Adidas ${CURL_LIBRARIES})


