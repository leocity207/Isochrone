



class Line:
    toolbox = {}
    def __init__(self,stations_list,toolbox) -> None:
        self.station_list = stations_list
        if not(Line.toolbox):
            Line.toolbox = toolbox
    
    def Get_Further_Station(self,station):
        index = self.station_list.index(station)
        return (self.station_list[:index],self.station_list[index+1:])