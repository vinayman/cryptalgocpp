find_package(GTest REQUIRED)
if(${GTest_FOUND} EQUAL "FALSE")
    message(FATAL "Gtest not found!")
endif(${GTest_FOUND} EQUAL "FALSE")

message(STATUS "GTEST_LIBRARY = ${GTEST_LIBRARY}" )
message(STATUS "GTEST_INCLUDE_DIRS = ${GTEST_INCLUDE_DIRS}" )

FILE(GLOB SourcesToTest ${PROJECT_SOURCE_DIR}/src/*.cpp)
FILE(GLOB ModelsToTest ${PROJECT_SOURCE_DIR}/src/model/*.cpp)
FILE(GLOB StatisticsToTest ${PROJECT_SOURCE_DIR}/src/statistics/*.cpp)

include_directories(${PROJECT_SOURCE_DIR}/src/)
include_directories(${PROJECT_SOURCE_DIR}/src/model/)
include_directories(${PROJECT_SOURCE_DIR}/src/statistics/)
include_directories(${LIBWEBSOCKETS_INCLUDE})
include_directories(${JSONCPP_INCLUDE})
include_directories(${CURL_INCLUDE})
include_directories(${BINACPP_INCLUDE})
include_directories(${Boost_INCLUDE_DIR})
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${PLOG_INCLUDE})

add_library(test_cryptalgo
        ${SourcesToTest}
        ${ModelsToTest}
        ${StatisticsToTest}
        framework/TestMarketDataInterface.cpp
        framework/InputParser.cpp
        framework/TestEnv.cpp
)

add_executable(testCryptalgo
        TestKLines.cpp
        TestPrice.cpp
        TestSymbol.cpp
        TestStrategy.cpp
        test_main.cpp
)

target_link_libraries(test_cryptalgo
        pthread
        dl
        binance-cxx-api
        boost_system
)

target_link_libraries(testCryptalgo
        test_cryptalgo
        GTest::gtest
        binance-cxx-api
        pthread
        dl
        boost_system
        )

install(TARGETS
            testCryptalgo
            test_cryptalgo
        RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin
        LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/lib
        )