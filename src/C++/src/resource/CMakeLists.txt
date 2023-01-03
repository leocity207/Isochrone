add_library(csv STATIC                       
    csv_reader.cpp
    csv_schedule_reader.cpp
    csv_station_reader.cpp
    resource_getter.cpp
)

target_link_libraries(csv
log
network_optimizer
utils
)