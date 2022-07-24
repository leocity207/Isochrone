



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
        #todo
        