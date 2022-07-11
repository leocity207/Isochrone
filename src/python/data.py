

from typing import List
from station import *


def Get_All_Station(toolbox) -> List:
    list_of_station = []
    list_of_station.append(Station(np.array([25,30]),toolbox))
    list_of_station[-1].Force_Set_Best_Time(0)
    list_of_station.append(Station(np.array([10,15]),toolbox))
    list_of_station[-1].Force_Set_Best_Time(0)
    list_of_station.append(Station(np.array([30,20]),toolbox))
    list_of_station[-1].Force_Set_Best_Time(0)
    list_of_station.append(Station(np.array([70,81]),toolbox))
    list_of_station[-1].Force_Set_Best_Time(5)
    return list_of_station
