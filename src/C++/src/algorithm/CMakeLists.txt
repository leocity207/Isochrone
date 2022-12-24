add_library(algorithm OBJECT                       
    algorithm_station.cpp
)

target_link_libraries(algorithm
log
utils
network_optimizer
)


