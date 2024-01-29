FILE(GLOB parser parser/*.cpp)

add_library(json STATIC                       
    ${parser}
)

target_link_libraries(
    log
)