



from decimal import InvalidContext
from operator import truediv


class Line:
    toolbox = {}
    def __init__(self,stations_list,a_way,r_way,toolbox) -> None:
        self.station_list = stations_list
        self.m_a_way = a_way
        self.m_r_way = r_way
        if not(Line.toolbox):
            Line.toolbox = toolbox
            
    #-----------------------------------------------------------------------
    # give all the station in the line excluding the one given in parameters
    # - station-to_exclude: the station to exclude from the list
    # - return: the station list of the line excluding the one given in the parameters 
    def Get_Stations_Excluding(self,station_to_exclude):
        station_list = self.station_list.copy()
        station_list.remove(station_to_exclude)
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

        timetable = [[]] 
        if(index_start>index_end):
            timetable = self.m_a_way
        else:
            timetable = self.m_r_way
        
        i = 0
        # find the first passing time that is valid
        while(i<len(timetable[0])-1 and (timetable[index_start,i] is None or timetable[index_start,i] <start_station.Get_Best_Travel_Time_Start_To_Station()) ):
            i+=1
        #if nothing was found just return nothing 
        if(i == len(timetable[0])-1 ):
            return -1

        #try to find a path from start to end that could match 
        while(i<len(timetable[0])-1):
            if(not(timetable[index_end,i] is None) and not(timetable[index_start,i] is None)):
                return timetable[index_end,i] #yes we found a matching path
            i+=1
        
        #if we just don't fidna  path from start to end that mean none exist
        return -1
        

    #------------------------------------------
    # get if the given station is in the current line
    # - station: a station object you want to check if in the current line
    # - return : a boolean wich is true if the station is in the line
    def Is_Station_In_Line(self,station):   
        if station in self.station_list:
            return True
        return False
