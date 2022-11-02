


from logging import raiseExceptions
from util import *
import numpy as np
from util import *

class Station:
    toolbox = {}
    def __init__(self,coordinate,name,toolbox):
        Station.toolbox = toolbox
        self.coordinate = coordinate
        self.best_time = Station.toolbox["starting time"] + Get_Base_Travel_Time(Station.toolbox["starting coordinate"],self.coordinate,toolbox)
        self.name = name
        self.reached_by_transport = False
        self.m_has_been_reached_by_transport = False
        self.base_time_from_start = Get_Base_Travel_Time(Station.toolbox["starting coordinate"],self.coordinate,toolbox)
        self.m_arriving_time = Station.toolbox["starting time"] + self.base_time_from_start
        self.m_has_been_optimized = False

    def Set_As_Optimized(self):
        self.m_has_been_optimized = True

    def Get_Coordinate(self):
        return self.coordinate
 
    def Get_Travel_Time_Station_Coordinate(self, station):
        return Get_Base_Travel_Time(station.coordinate,self.coordinate,Station.toolbox)
    
    def Get_Best_Travel_Time_Start_To_Station(self):
        return self.best_time
    
    def Force_Set_Best_Time(self,value):
        self.best_time = value
    
    def Set_New_Best_Point(self,new_best_point):
        new_best_time = Get_Base_Travel_Time(self.coordinate,new_best_point,Station.toolbox)
        assert(new_best_time<self.best_time)
        self.best_time = new_best_time

    def Get_Time_From_Start(self):
        return(Get_Base_Travel_Time(self.coordinate,Station.toolbox["starting coordinate"],Station.toolbox))
    
    def Is_Current_Best_Time_Better_Than_Base_Travel_Time(self):
        return self.best_time < self.Get_Time_From_Start()
    
    def Update_Station_with_default_Traveling_time():
        pass

    def __lt__(self, other):
        return self.Get_Best_Travel_Time_Start_To_Station() < other.Get_Best_Travel_Time_Start_To_Station()

    def Try_Set_Best_Time(self,new_test_time):
        if new_test_time < self.best_time:
                self.best_time = new_test_time
    
    #try to see if we can reach other station faster than 
    def Optimize_Base_Other_Station_Distance(self,stations):
        #better than foot need to be reached by the transport(triangular inequality)
        if not(self.m_has_been_reached_by_transport):
            return
        for station in stations:
            new_test_time = station.Get_Travel_Time_Station_Coordinate(self)+self.best_time
            station.Try_Set_Best_Time(new_test_time)
            
    def Get_Passing_Lines(self):
        passing_lines = []
        for line in Station.toolbox["line list"]:
            if(line.Is_Station_In_Line(self)):
                passing_lines.append(line)
        return passing_lines
    #-------------------------------------------------------------------------
    # Try to see if there is a best time from this station to the end station
    # Knowing that self is the reference and we know the time we arrive at the 
    # we expect the time when we arrive at the next station 
    def Optimize_Stations_Line(self,stations):
        lines = self.Get_Passing_Lines()
        for line in lines:
            stations_in_lines = line.Get_Stations_Excluding(self)
            for station in stations_in_lines:
                new_best_time = line.Get_Best_Time_To_Station(self,station)
                if(new_best_time == -1):
                    continue
                station.Try_Set_Best_Time(new_best_time)
    
    @staticmethod
    def Find_Station_By_Name(station_name):
        for station in Station.toolbox["station_list"]:
            if station.name == station_name:
                return station
        raise Exception()
