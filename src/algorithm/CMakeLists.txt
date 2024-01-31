add_library(algorithm OBJECT                       
    algorithm_station.cpp
    network_optimizer.cpp
)

target_link_libraries(algorithm
log
utils
network_optimizer
)


