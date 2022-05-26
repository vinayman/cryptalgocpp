set(Boost_INCLUDE_DIR /usr/include/boost PARENT_SCOPE)
message(STATUS "Boost_INCLUDE_DIR = ${Boost_INCLUDE_DIR}")

add_subdirectory(model)

include_directories(${LIBWEBSOCKETS_INCLUDE})
include_directories(${JSONCPP_INCLUDE})
include_directories(${CURL_INCLUDE})
include_directories(${BINACPP_INCLUDE})
include_directories(${Boost_INCLUDE_DIR})
include_directories(${PLOG_INCLUDE})
include_directories(${PROJECT_SOURCE_DIR}/src/model/)

add_library(cryptalgo SHARED
        Utils.h
        Config.cpp
        OrderManager.h
        MarketData.h
        MarketData.cpp
        KuCoinMarketData.cpp
        Factory.h
        Event.h
        OrderInterface.cpp
        MarketDataInterface.cpp
        StatisticsInterface.h
        SmaStatistic.cpp
        DampedMeanReversionStatistic.cpp
        StatisticsChain.cpp)

target_link_libraries(cryptalgo
        binance-cxx-api
        boost_system
        pthread
        dl
        cryptalgomodel)

add_subdirectory(strategy)

install(TARGETS
        cryptalgo
        RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin
        LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/lib COMPONENT funcs)