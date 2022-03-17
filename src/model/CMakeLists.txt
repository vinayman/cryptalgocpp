include_directories(${LIBWEBSOCKETS_INCLUDE})
include_directories(${JSONCPP_INCLUDE})
include_directories(${CURL_INCLUDE})
include_directories(${BINACPP_INCLUDE})
include_directories(${Boost_INCLUDE_DIR})
include_directories(${PLOG_INCLUDE})
include_directories(${PROJECT_SOURCE_DIR}/src/)

add_library(cryptalgomodel SHARED
        KLines.cpp
        Price.h
        Quote.h
        Quote.cpp
        Symbol.h
        Allocation.h
        Allocations.h
        Allocations.cpp
        Trade.h
        Trade.cpp)