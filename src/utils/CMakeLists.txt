#//////////////////////////////////
# SOURCE FILES
FILE(GLOB UTILS_SOURCE "./*.cpp")

#////////
# LIBRARY
add_library(utils OBJECT                       
    ${UTILS_SOURCE}
)

#//////////////
# LIBRARY LINKS
target_link_libraries(utils
    log
)


