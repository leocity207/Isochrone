


from logging import raiseExceptions
from util import *
import numpy as np
from util import *

class Station:
    toolbox = {}
    def __init__(self,coordinate,toolbox):
        Station.toolbox = toolbox
        self.coordinate = coordinate
        self.best_time = float('inf')
        self.reached_by_transport = False
        self.base_time_from_start = np.linalg.norm(Station.toolbox["starting coordinate"] - self.coordinate)

    def Get_Travel_Time_Station_Coordinate(self, coordinate):
        return Get_Base_Travel_Time(coordinate,self.coordinate,Station.toolbox)
    
    def Get_Best_Travel_Time_Start_To_Station(self):
        return self.best_time
    
    def Force_Set_Best_Time(self,value):
        self.best_time = value
    
    def Set_New_Best_Point(self,new_best_point):
        new_best_time = Get_Base_Travel_Time(self.coordinate,new_best_point,Station.toolbox)
        assert(new_best_time<self.best_time)
        self.best_time = new_best_time

    def Get_Time_From_Start(self):
        return(Get_Base_Travel_Time(self.coordinate,toolbox=["starting coordinate"]))
    
    def Is_Current_Best_Time_Better_Than_Base_Travel_Time(self):
        return self.best_time < self.Get_Time_From_Start()
    
    def Update_Station_with_default_Traveling_time():
        pass


