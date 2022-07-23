
import os
from typing import List
from station import *
import csv
from coordinate import *
from pprint import pprint
import matplotlib.pyplot as plt
from pprint import pprint

def Get_All_Coordinate(toolbox):
    path_to_cordinate_file = "..\..\Ressource\Geographie\coordinate.csv"
    with open(path_to_cordinate_file,"r",encoding='utf8') as file:
        coordinate_csv = list(csv.reader(file, delimiter= ';'))
        angular_coord_strings = [e[1] for e in coordinate_csv]
        planar_angular_coordinate,toolbox["mean_x"],toolbox["mean_y"] = Parse_Angular_String_To_Plane_List(angular_coord_strings,toolbox["earth radius"])
        toolbox["coordinate"] = {}
        for i in range(len(coordinate_csv)):
            toolbox["coordinate"][coordinate_csv[i][0].rstrip()] = planar_angular_coordinate[i]

def Get_WeekDay(letter_list):
    if 'l' in  letter_list:
        yield "monday"
    if "ma" in letter_list:
        yield "tuesday"
    if "me" in letter_list:
        yield "wednesday"
    if "j" in letter_list:
        yield "thursday"
    if "v" in letter_list:
        yield "friday"
    if "s" in letter_list:
        yield "saturday"
    if "d" in letter_list:
        yield "sunday"

def Get_File_Attribute(file_name):
    file_without_extension = file_name.split('.')[0]
    return file_without_extension.split('_')
    
        

        


def Get_All_Station(toolbox) -> list:
    path_to_ressource = "../../Ressource"
    lines_folders = ["ligne1","ligne2","ligne3","ligne4","ligne5","ligne6","ligne7","ligne8","ligne134"]
    line_list = []
    for line_folder in lines_folders:
        path_to_line = os.path.join(path_to_ressource,line_folder)
        a_way = {"scolaire":{"monday":[],"tuesday":[],"wednesday":[],"thushday":[],"friday":[],"saturday":[],"sunday":[]},"holyday":{"monday":[],"tuesday":[],"wednesday":[],"thushday":[],"friday":[],"saturday":[],"sunday":[]}}
        r_way = {"scolaire":{"monday":[],"tuesday":[],"wednesday":[],"thushday":[],"friday":[],"saturday":[],"sunday":[]},"holyday":{"monday":[],"tuesday":[],"wednesday":[],"thushday":[],"friday":[],"saturday":[],"sunday":[]}}
        for root,dir,files in os.walk(path_to_line):
            for file in files:
                if not(file.endswith(".csv")):
                    continue
                file_data = Get_CSV_File_As_data(os.path.join(path_to_line,file))
                attribute = Get_File_Attribute(file)
                if(attribute[1] == 'a'):
                    for weekday in Get_WeekDay(attribute[2]):
                        a_way["scolaire"][weekday] = file_data
                else:     
                    for weekday in Get_WeekDay(attribute[2]):
                        r_way["scolaire"][weekday] = file_data
                if(len(attribute) == 4):
                    if(attribute[1] == 'a'):
                        for weekday in Get_WeekDay(attribute[3]):
                            a_way["holyday"][weekday] = file_data
                    else:     
                        for weekday in Get_WeekDay(attribute[3]):
                            r_way["holyday"][weekday] = file_data
                pprint(a_way)
                pprint(r_way)
    


def Get_CSV_File_As_data(filepath):
    with open('employee_birthday.txt') as csv_file:
        return list(csv.reader(csv_file, delimiter=';'))


if __name__ == "__main__":
    toolbox = {"earth radius": 6339000}
    Get_All_Coordinate(toolbox)
    pprint(toolbox["coordinate"])
    x = [toolbox["coordinate"][key][0] for key in toolbox["coordinate"]]
    y = [toolbox["coordinate"][key][1] for key in toolbox["coordinate"]]
    plt.figure()
    plt.scatter(y,x)
    a = [key for key in toolbox["coordinate"]]
    for i,label in enumerate(a):
        plt.annotate(label,(y[i],x[i]))
    plt.show()