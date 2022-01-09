set(Boost_INCLUDE_DIR /usr/include/boost PARENT_SCOPE)
message(STATUS "Boost_INCLUDE_DIR = ${Boost_INCLUDE_DIR}")

add_subdirectory(model)

include_directories(${LIBWEBSOCKETS_INCLUDE})
include_directories(${JSONCPP_INCLUDE})
include_directories(${CURL_INCLUDE})
include_directories(${BINACPP_INCLUDE})
include_directories(${Boost_INCLUDE_DIR})

add_library(cryptalgo SHARED
        MarketDataInterface.cpp
        Config.cpp
        OrderManager.h
        MarketData.h
        MarketData.cpp
        Factory.h
        Event.h
        OrderInterface.cpp
        OrderInterface.h)

target_link_libraries(cryptalgo
        binance-cxx-api
        boost_system
        pthread
        cryptalgomodel
        )

add_subdirectory(strategy)

install(TARGETS
        cryptalgo
        RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin
        LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/lib COMPONENT funcs)