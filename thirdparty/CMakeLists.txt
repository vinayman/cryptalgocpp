#### Third party ####

# Installed packagesbb
find_package(Boost REQUIRED)
find_package(Threads REQUIRED)

include_directories(${BOOST_INCLUDE_DIR} PARENT_SCOPE)
message(STATUS "BOOST_INCLUDE_DIR = ${BOOST_INCLUDE_DIR}")

set(CURL_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/curl/include")
include_directories(${CURL_INCLUDE_DIRS})

add_subdirectory(binance-cxx-api)
add_subdirectory(plog)
set(BINACPP_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/binance-cxx-api/include PARENT_SCOPE)
set(PLOG_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/plog/include PARENT_SCOPE)
set(CURL_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/binance-cxx-api/ThirdParty/curl/include PARENT_SCOPE)
set(JSONCPP_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/binance-cxx-api/ThirdParty/jsoncpp/include PARENT_SCOPE)
set(LIBWEBSOCKETS_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/binance-cxx-api/ThirdParty/libwebsockets/include PARENT_SCOPE)

install(TARGETS
        binance-cxx-api
        RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin
        LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/lib
        )
