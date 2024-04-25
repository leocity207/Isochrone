#//////////////////////////////////
# SOURCE FILES
FILE(GLOB RESOURCE_CSV_ENGINE_SOURCE engine/*.cpp)
FILE(GLOB RESOURCE_CSV_PARSER_SOURCE parser/*.cpp)
FILE(GLOB RESOURCE_CSV_VALIDATOR_SOURCE validator/*.cpp)

#////////
# LIBRARY
add_library(csv STATIC                       
	${RESOURCE_CSV_ENGINE_SOURCE}
	${RESOURCE_CSV_PARSER_SOURCE}
	${RESOURCE_CSV_VALIDATOR_SOURCE}
)

#//////////////
# LIBRARY LINKS
target_link_libraries(csv
	network
	log
)