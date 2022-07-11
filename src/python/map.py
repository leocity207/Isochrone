import numpy as np

from util import Get_Base_Travel_Time

def compute_distance_to_station(station,i,j):
    return station.Get_Travel_Time_Station_Coordinate((i,j)) + station.Get_Best_Travel_Time_Start_To_Station()
    
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
                best_time = Get_Base_Travel_Time(np.array([i,j]),Map.toolbox["starting coordinate"],Map.toolbox)
                list_value = list(map(lambda station : compute_distance_to_station(station,i,j),Map.toolbox["station_list"]))
                plane[i,j] = min([best_time]+list_value)
        return plane

            
    

