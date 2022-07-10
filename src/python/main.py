from data import *
from map import *
 
def Optimize_Station_Travel_Time(stations):
    for station in station_list:
        if(station.Is_Current_Best_Time_Better_Than_Base_Travel_Time()):
            continue
        else:
            station.Update_Station_with_default_Traveling_time()


if __name__ == "__main__":
    toolbox = {}
    toolbox["starting coordinate"] = (4,1)
    toolbox["starting time"] = 0
    toolbox["speed"] = 5
    station_list = Get_All_Station(toolbox)
    toolbox["station_list"] = station_list.sort(key = Get_Best_Time)
    map = Map(toolbox)

    #Optimize_Station_Travel_Time(toolbox["station_list"])
    planar_value = map.Commpute_Planar_Value()
    //show_planaer_value()
