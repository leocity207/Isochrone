import numpy as np

from python.util import Get_Base_Travel_Time


class Map:
    toolbox = {}
    def __init__(self,toolbox):
        self.min_x = 0
        self.min_y = 0
        self.max_x = 100
        self.max_y = 100
        self.resolution = 10
        if not(toolbox):
            Map.toolbox = toolbox
    
    def Commpute_Planar_Value(self):
        x_range = (self.max_x-self.min_x)*self.resolution
        y_range = (self.max_y-self.min_y)*self.resolution
        np.zeros(x_range,y_range)
        for i in range(x_range):
            for j in range(y_range):
                best_time = Get_Base_Travel_Time((i,j),Map.toolbox["starting coordinate"])
                for station in Map.toolbox["station_list"]:
                    testing_time = station.Get_Travel_Time_Station_Coordinate((i,j)) + station.Get_Best_Travel_Time_Start_To_Station()
                    if(testing_time < best_time):
                        best_time = testing_time
            
    

