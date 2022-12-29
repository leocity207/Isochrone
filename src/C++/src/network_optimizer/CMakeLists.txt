add_library(network_optimizer OBJECT                       
    day_info.cpp
    line.cpp
    schedule.cpp
    station.cpp
    network.cpp
)

target_link_libraries(network_optimizer
log
)