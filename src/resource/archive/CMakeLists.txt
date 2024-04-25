#//////////////////////////////////
# SOURCE FILES
FILE(GLOB RESOURCE_ARCHIVE_SOURCE *.cpp)

#////////
# LIBRARY
add_library(archive STATIC                       
	${RESOURCE_ARCHIVE_SOURCE}
)

#//////////////
# LIBRARY LINKS
target_link_libraries(archive
	csv
	json
)