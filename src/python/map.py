import numpy as np

from util import Get_Base_Travel_Time


class Map:
    toolbox = {}
    def __init__(self,toolbox):
        self.min_x = 0
        self.min_y = 0
        self.max_x = 100
        self.max_y = 100
        self.resolution = 1
        if not(Map.toolbox):
            Map.toolbox = toolbox
    
    def Commpute_Planar_Value(self):
        x_range = (self.max_x-self.min_x)*self.resolution
        y_range = (self.max_y-self.min_y)*self.resolution
        plane = np.zeros((x_range,y_range))
        for i in range(x_range):
            for j in range(y_range):
                print("{x},{y}".format(x=i,y=j))
                best_time = Get_Base_Travel_Time(np.array([i,j]),Map.toolbox["starting coordinate"],Map.toolbox)
                for station in Map.toolbox["station_list"]:
                    testing_time = station.Get_Travel_Time_Station_Coordinate((i,j)) + station.Get_Best_Travel_Time_Start_To_Station()
                    if(testing_time < best_time):
                        best_time = testing_time
                plane[i,j] = best_time
        return plane

            
    

