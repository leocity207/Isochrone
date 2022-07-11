from data import *
from map import *
import matplotlib.pyplot as plt
import numpy as np
 
def Optimize_Station_Travel_Time(stations):
    for station in station_list:
        if(station.Is_Current_Best_Time_Better_Than_Base_Travel_Time()):
            continue
        else:
            station.Update_Station_with_default_Traveling_time()


if __name__ == "__main__":
    toolbox = {}
    toolbox["starting coordinate"] = np.array([50,50])
    toolbox["starting time"] = 0
    toolbox["speed"] = 5
    station_list = Get_All_Station(toolbox)
    station_list.sort()
    toolbox["station_list"] = station_list
    map = Map(toolbox)
    #Optimize_Station_Travel_Time(toolbox["station_list"])
    planar_value = map.Commpute_Planar_Value()

    plt.figure()
    bins = np.linspace(np.min(planar_value),np.max(planar_value), 20)
    plt.imshow(np.digitize(planar_value,bins),cmap='hot')
    plt.show()
