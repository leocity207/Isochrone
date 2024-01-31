

FILE(GLOB_RECURSE MY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/../../includes/utils/*.h")

add_library(utils OBJECT                       
    coordinate.cpp
    daytime.cpp
    general.cpp

    ${MY_HEADERS}
)

target_include_directories(utils

PRIVATE
                            
${CMAKE_CURRENT_SOURCE_DIR}/../../includes/utils/
)




target_link_libraries(utils)


