FILE(GLOB Sources *.cpp)
add_library(cryptalgo_strategies SHARED Strategies.cpp ${Sources})

target_link_libraries(cryptalgo_strategies cryptalgo)

include_directories(../)
include_directories(../model/)

install(TARGETS
        cryptalgo_strategies
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
	    COMPONENT strategies)
