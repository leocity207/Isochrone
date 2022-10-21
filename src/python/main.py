from data import *
from map import *
import matplotlib.pyplot as plt
import numpy as np
from station import *
from file_data import *
 
def Optimize_Station_Travel_Time(stations_no_copy):
    stations = stations_no_copy.copy()
    while(len(stations) != 0):
        stations.sort()
        
        station = stations.pop(0)
        station.Set_As_Optimized()
        station.Optimize_Base_Other_Station_Distance(stations)
        station.Optimize_Stations_Line(stations)


if __name__ == "__main__":
    toolbox = {}
    toolbox["starting coordinate"] = np.array([50,50])
    toolbox["starting time"] = 0
    toolbox["speed"] = 5
    toolbox["earth radius"]= 6339000
    toolbox["day info"] = [WEEK_DAY.MONDAY,DAY_TYPE.SCHOOL]
    
    #get all the station and order them
    Get_All_Station(toolbox)
    Get_All_Lines(toolbox)
    map = Map(toolbox)
    
    #optimize all station first
    Optimize_Station_Travel_Time(toolbox["station_list"])
    
    #compute voronoi diagram
    planar_value = map.Commpute_Planar_Value()

    #plot values
    plt.figure()
    bins = np.linspace(np.min(planar_value),np.max(planar_value), 20)
    plt.imshow(np.digitize(planar_value,bins),cmap='hot')
    plt.show()
