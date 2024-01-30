
FILE(GLOB engine engine/*.cpp)
FILE(GLOB parser parser/*.cpp)

add_library(csv STATIC                      
    ${engine}
    ${parser}
)

target_link_libraries(
    log
)