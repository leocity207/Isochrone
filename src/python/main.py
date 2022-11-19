from data import *
from map import *
import matplotlib.pyplot as plt
import numpy as np
from station import *
from file_data import *
from tqdm import tqdm
 
def Optimize_Station_Travel_Time(stations_no_copy):
    stations = stations_no_copy.copy()
    i = 1
    while(len(stations) != 0):
        print("{}/{}{}".format(i,len(stations),"!"*i))
        i+=1
        stations.sort()

        station = stations.pop(0)
        station.Set_As_Optimized()
        station.Optimize_Base_Other_Station_Distance(stations)
        station.Optimize_Stations_Line(stations)


if __name__ == "__main__":
    toolbox = {}
    toolbox["starting coordinate"] = np.array([0,0])
    toolbox["starting time"] = datetime.datetime.strptime("7:00","%H:%M")
    toolbox["speed"] = 1.11 #m/s
    toolbox["earth radius"]= 6339000
    toolbox["Ressource_path"] = "c:\\Users\\Leocl\\Documents\\Isochrone"
    toolbox["day info"] = [WEEK_DAY.MONDAY,DAY_TYPE.SCHOOL]
    
    #get all the station and order them
    Get_All_Station(toolbox)
    Get_All_Lines(toolbox)
    map = Map(toolbox)
    print("All data loaded, begining station optimization")
    #optimize all station first
    Optimize_Station_Travel_Time(toolbox["station_list"])
    
    #compute voronoi diagram
    planar_value = map.Commpute_Planar_Value()

    #plot values
    plt.figure()
    bins = np.linspace(np.min(planar_value),np.max(planar_value), 20)
    plt.imshow(np.digitize(planar_value,bins),cmap='hot')
    plt.show()
