
import os
from typing import List
from station import *
import csv

def Get_All_Coordinate(toolbox):
    path_to_cordinate_file = "../../Ressource/Geographie/coordinate.csv"
    with open(path_to_cordinate_file,"r") as file:
        coordinate_csv = list(csv.reader(file, delimiter= ';'))
        for i in range(len(coordinate_csv)):
            coordinate_csv[i][1]
        

        


def Get_All_Station(toolbox) -> List:
    path_to_ressource = "../../Ressource"
    lines_folders = ["ligne1","ligne2","ligne3","ligne4","ligne5","ligne6","ligne7","ligne8","ligne134"]
    line_list = 
    for line_folder in lines_folders:
        path_to_line = os.path.join(path_to_ressource,line_folder)
        for root,dir,files in os.walk(path_to_line):
            for file in files:
                if not(file.endswith(".csv")):
                    continue
                type = Get_Path(os.path.basename(file))
                
    return list_of_station
