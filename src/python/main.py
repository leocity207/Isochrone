from data import *
from map import *
import matplotlib.pyplot as plt
import numpy as np
 
def Optimize_Station_Travel_Time(stations_no_copy):
    stations = stations_no_copy.copy()
    while(len(stations) != 0):
        stations.sort()
        station = station.pop(0)
        station.Optimize_Base_Other_Station_Distance(stations)
        station.Optimize_Stations_Line(stations)


if __name__ == "__main__":
    toolbox = {}
    toolbox["starting coordinate"] = np.array([50,50])
    toolbox["starting time"] = 0
    toolbox["speed"] = 5
    station_list = Get_All_Station(toolbox)
    toolbox["station_list"] = station_list
    map = Map(toolbox)
    Optimize_Station_Travel_Time(toolbox["station_list"])
    planar_value = map.Commpute_Planar_Value()

    plt.figure()
    bins = np.linspace(np.min(planar_value),np.max(planar_value), 20)
    plt.imshow(np.digitize(planar_value,bins),cmap='hot')
    plt.show()
