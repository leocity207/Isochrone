import numpy as np

from util import Get_Base_Travel_Time

def Get_Max_Min_Coordinate(stations):
    x_min = 0
    x_max = 0
    y_min = 0
    y_max = 0
    for station in stations:
        coordinate = station.Get_Coordinate()
        if(coordinate[0] < x_min):
            x_min = coordinate[0]
        if(coordinate[0] > x_max):
            x_max = coordinate[0]
        if(coordinate[1] < y_min):
            y_min = coordinate[1]
        if(coordinate[1] > y_max):
            y_max = coordinate[1]
    return (x_min,x_max,y_min,y_max)

def compute_distance_to_station(station,i,j):
    return station.Get_Travel_Time_Station_Coordinate((i,j)) + station.Get_Best_Travel_Time_Start_To_Station()
    
class Map:
    toolbox = {}
    def __init__(self,toolbox):
        self.min_x,self.max_x,self.min_y,self.max_y = Get_Max_Min_Coordinate(toolbox["station_list"])
        self.resolution = 0.1
        if not(Map.toolbox):
            Map.toolbox = toolbox
    
    def Commpute_Planar_Value(self):
        x_range = int(np.round((self.max_x-self.min_x)*self.resolution))
        y_range = int(np.round((self.max_y-self.min_y)*self.resolution))
        print(x_range)
        print(y_range)
        plane = np.zeros((x_range,y_range))
        for i in range(x_range):
            print(i)
            for j in range(y_range):
                best_time = Get_Base_Travel_Time(np.array([(i-self.min_x)/self.resolution,(j-self.min_y)/self.resolution]),Map.toolbox["starting coordinate"],Map.toolbox)
                list_value = list(map(lambda station : compute_distance_to_station(station,i-self.min_x,j-self.min_y),Map.toolbox["station_list"]))
                plane[i,j] = min([best_time]+list_value)
        return plane

            
    

