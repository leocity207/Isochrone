



from decimal import InvalidContext
from operator import truediv
from file_data import *

from pprint import pprint

from station import *

class Line:
    toolbox = {}
    
    def __init__(self,stations_list_name,a_way,r_way,name,toolbox) -> None:
        self.station_list = []
        for stations_name in stations_list_name:
            try:
                
                self.station_list.append(Station.Find_Station_By_Name(stations_name))
            except:
                raise Exception("Station: {} could not be found inside the station list".format(stations_name))
        self.m_a_way = a_way
        self.m_r_way = r_way
        self.name = name
        if not(Line.toolbox):
            Line.toolbox = toolbox
    
    def Get_Correct_Timetable(self,is_a_way):
        way_list = None
        if(is_a_way):
            way_list = self.m_a_way
        else:
            way_list = self.m_r_way
        for schedule_dic in way_list:
            for meta in schedule_dic["meta_list"]:
                if meta.Is_Matching(Line.toolbox["day info"][0],Line.toolbox["day info"][1]):
                    return schedule_dic["schedule"]
        return None
    
    def __eq__(self, other):
        if (other):
            return self.name == other
            
    #-----------------------------------------------------------------------
    # give all the station in the line excluding the one given in parameters
    # - station_to_exclude: the station to exclude from the list
    # - return: the station list of the line excluding the one given in the parameters 
    def Get_Stations_Excluding(self,station_to_exclude):
        station_list = self.station_list.copy()
        try:
            station_list.remove(station_to_exclude)
        finally:
            return station_list
    
    #--------------------------------------------------------------
    # give the time at witch you arrive at the next end_station from the starting station
    # - starting_station : the starting station
    # - end_station: the ending station or the station you wanna go to
    # - return: the best time you ca arrive at the end station
    #           if no path has been found the result is None
    def Get_Best_Time_To_Station(self,start_station,end_station):
        index_start = self.station_list.index(start_station)
        index_end = self.station_list.index(end_station)
        assert index_start != -1
        assert index_end != -1

        timetable = None
        if(index_start>index_end):
            timetable = self.Get_Correct_Timetable(False)
        else:
            timetable = self.Get_Correct_Timetable(True)
        
        #if no timetable exist for that day    
        if timetable is None:
            return -1
        
        i = 0
        # find the first passing time that is valid
        while(i<len(timetable[0])-1 and (timetable[index_start][i] is None or timetable[index_start][i] <start_station.Get_Best_Travel_Time_Start_To_Station()) ):
            i+=1
        #if nothing was found just return nothing 
        if(i == len(timetable[0])-1 ):
            return -1

        #try to find a path from start to end that could match 
        while(i<len(timetable[0])-1):
            if(not(timetable[index_end][i] is None) and not(timetable[index_start][i] is None)):
                return timetable[index_end][i] #yes we found a matching path
            i+=1
        
        #if we just don't fidna  path from start to end that mean none exist
        return -1
        
    #------------------------------------------
    # get if the given station is in the current line
    # - station: a station object you want to check if in the current line
    # - return : a boolean wich is true if the station is in the line
    def Is_Station_In_Line(self,station):
        if station.name == "Gare de Vienne" or station.name == "Gare de Vienne A" or station.name == "Gare de Vienne D":
             G1 = Station.Find_Station_By_Name("Gare de Vienne")
             G2 = Station.Find_Station_By_Name("Gare de Vienne A")
             G3 = Station.Find_Station_By_Name("Gare de Vienne D")
             if G1 in self.station_list:
                 return True
             elif G2 in self.station_list:
                 return True
             elif G3 in self.station_list:
                 return True
             else:
                 return False
        if station in self.station_list:
            return True
        return False

    @staticmethod
    def Clean_Data_Matrix(csv_matrix):
        station_list = []
        for line in csv_matrix:
            station_list.append(line.pop(0))
        return station_list

    @staticmethod
    def Create_Line_From_Schedules(file_datas,csv_matrix,toolbox):
        assert (len(file_datas) == len(csv_matrix))
        final_station_list = None
        name = file_datas[0][0]+" "+file_datas[0][1]
        schedule_list_a_way = []
        schedule_list_r_way = []
        for i in range(len(file_datas)):
            temp_station_list = Line.Clean_Data_Matrix(csv_matrix[i])
            list_file_data = File_Date.Create_from_file_data(file_datas[i])
            if(file_datas[i][2] == 'a'):
                if(final_station_list is None):
                    final_station_list = temp_station_list
                schedule_list_a_way.append({"meta_list":list_file_data,"schedule":csv_matrix[i]})
            elif(file_datas[i][2] == 'r'):
                schedule_list_r_way.append({"meta_list":list_file_data,"schedule":csv_matrix[i]})
            else:
                raise Exception("this should be either a or r")
        return Line(final_station_list,schedule_list_a_way,schedule_list_r_way,name,toolbox)

    @staticmethod
    def Get_Line_By_Name(line_name):
        return Line.toolbox["line list"][Line.toolbox["line list"].index(line_name)]