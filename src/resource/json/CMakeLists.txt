#//////////////////////////////////
# SOURCE FILES
FILE(GLOB RESOURCE_JSON_SOURCE parser/*.cpp)

#////////
# LIBRARY
add_library(json STATIC                       
	${RESOURCE_JSON_SOURCE}
)

#//////////////
# LIBRARY LINKS
target_link_libraries(json
	utils
	log
)