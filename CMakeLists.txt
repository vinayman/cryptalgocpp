cmake_minimum_required(VERSION 3.21.0)
project(cryptalgocpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)
add_compile_options("-fPIC")

add_subdirectory(thirdparty)
add_subdirectory(src)
add_subdirectory(test)

message(STATUS "LIBWEBSOCKETS_INCLUDE = ${LIBWEBSOCKETS_INCLUDE}")
message(STATUS "JSONCPP_INCLUDE = ${JSONCPP_INCLUDE}")
message(STATUS "CURL_INCLUDE = ${CURL_INCLUDE}")
message(STATUS "BINACPP_INCLUDE = ${BINACPP_INCLUDE}")
include_directories(${LIBWEBSOCKETS_INCLUDE})
include_directories(${JSONCPP_INCLUDE})
include_directories(${CURL_INCLUDE})
include_directories(${BINACPP_INCLUDE})
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/src/model)

set(Boost_LIBRARY_DIR /usr/lib/x86_64-linux-gnu)
include_directories(${Boost_INCLUDE_DIR})

add_executable(cryptalgocpp main.cpp)

target_link_libraries(cryptalgocpp
        cryptalgo
        boost_program_options)
