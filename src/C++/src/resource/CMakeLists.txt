add_library(csv OBJECT                       
    csv_reader.cpp
    csv_schedule_reader.cpp
    csv_station_reader.cpp
)

target_link_libraries(csv
log
network_optimizer
utils
)