#//////////////////////////////////
# SOURCE FILES
FILE(GLOB RESOURCE_CSV_ENGINE_SOURCE engine/*.cpp)
FILE(GLOB RESOURCE_CSV_PARSER_SOURCE parser/*.cpp)

#////////
# LIBRARY
add_library(csv STATIC                       
	${RESOURCE_CSV_ENGINE_SOURCE}
	${RESOURCE_CSV_PARSER_SOURCE}
)

#//////////////
# LIBRARY LINKS
target_link_libraries(csv
	utils
	log
)