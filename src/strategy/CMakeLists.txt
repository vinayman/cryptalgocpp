FILE(GLOB Sources *.cpp)
FILE(GLOB Headers *.h)
add_library(cryptalgo_strategies SHARED Strategies.cpp ${Sources} ${Headers})

target_link_libraries(cryptalgo cryptalgo_strategies)

include_directories(${PROJECT_SOURCE_DIR}/src/)
include_directories(${PROJECT_SOURCE_DIR}/src/model/)

install(TARGETS
        cryptalgo_strategies
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
	    COMPONENT strategies)
