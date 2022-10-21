
from hashlib import new
import os
from typing import List
from station import *
import csv
from coordinate import *
from pprint import pprint
import matplotlib.pyplot as plt
from pprint import pprint
import datetime
from line import *
from station import *

#----------------------------------------------------------------
# fetch all the station from the ressources files of coordinate
# - toolbox: the toolbox containing all the data
def Get_All_Station(toolbox: dict) -> None:
    path_to_cordinate_file = "Ressource\Geographie\coordinate.csv"
    with open(path_to_cordinate_file,"r",encoding='utf8') as file:
        coordinate_csv = list(csv.reader(file, delimiter= ';'))
        angular_coord_strings = [e[1] for e in coordinate_csv]
        planar_angular_coordinate,toolbox["mean_x"],toolbox["mean_y"] = Parse_Angular_String_To_Plane_List(angular_coord_strings,toolbox["earth radius"])
        station_list = []
        for i in range(len(coordinate_csv)):
            station_list.append(Station(planar_angular_coordinate[i],coordinate_csv[i][0].rstrip(),toolbox))
    station_list.sort()
    toolbox["station_list"] = station_list
    return
            
    
#-------------------------------------
#function used to yield all the weekday inside a string containing them
# - letter_list: the string containing all the weekday letter ('l','ma','me'...)
# - yield : all the fulname of every week contianied in the letter_list
def Get_WeekDay(letter_list: str) -> str:
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


#-----------------------------------------------------------
# give all the attribute of a filename writen as "#_#_#_#.*"
# - file_name: the file_name that we want to extract the attribute from
# - return: the list of all attribute (generaly the third and the fourth are used)
def Get_File_Attribute(file_name: str) -> list:
    file_without_extension = file_name.split('.')[0]
    return file_without_extension.split('_')
         

#-------------------------------------------------------------------------------------
# load all the line from the ressource and populate the "line list" insde the toolbox
# - toolbox : the toolbox containing all the program data
def Get_All_Lines(toolbox:dict) -> None:
    path_to_ressource = "Ressource"
    lines_folders = ["ligne1","ligne2","ligne3","ligne4","ligne5","ligne6","ligne7","ligne8","ligne134"]
    toolbox["line list"] = []
    for line_folder in lines_folders:
        path_to_line = os.path.join(path_to_ressource,line_folder)
        schedules = []
        file_datas = []
        for root,dir,files in os.walk(path_to_line):
            for file in files:
                if not(file.endswith(".csv")):
                    continue
                schedule_with_station = Get_CSV_File_As_data(os.path.join(path_to_line,file))
                file_data = Get_File_Attribute(file)
                file_datas.append(file_data)
                schedules.append(schedule_with_station)
            break
        print("Creating line {0}".format(line_folder))
        new_line = Line.Create_Line_From_Schedules(file_datas,schedules,toolbox)     
        toolbox["line list"].append(new_line)


#----------------------------------------------------
# check if the charachter given is a number
# - c : a character
# - return: true if it's a number and False otherwise
def IsNumber(c: str) -> bool:
    if c in "1234567890":
        return True
    return False

#------------------------------------------------------------------------------------------
# check if the given string is representing a date or note (format should be xx:xx or x:xx)
# - data: the date as a string representation
def Is_Date(data:str) -> bool:
    try:
        if(IsNumber(data[0]) and IsNumber(data[1]) and data[2] == ':'):
            return True
        if(IsNumber(data[0]) and data[1]==':' and IsNumber(data[2])):
            return True
        return False
    except IndexError:
        pass

#-----------------------------------------------------------------
# given a filepath to a schedule,fetch the file data and give it back as a list
# - filepath: path to the schedule file
# - return: the schedule file as a list
def Get_CSV_File_As_data(filepath: str) -> list:
    with open(filepath,encoding='utf8') as csv_file:
        the_list = list(csv.reader(csv_file, delimiter=';'))
        for row in the_list:
            row[0] = row[0].rstrip()
            for i in range(1,len(row)):
                if(Is_Date(row[i]) and len(row[i])>3):
                    try:
                        row[i] = datetime.datetime.strptime(row[i].rstrip(),"%H:%M")
                    except ValueError:
                        print("lol" + row[i])                    
                else:
                    row[i]= None
        return the_list




if __name__ == "__main__":
    if(False):
        toolbox = {}
        Get_All_Lines(toolbox)
        pprint(toolbox)
    if(False):
        toolbox = {}
        Get_All_Station(toolbox)
    if(False): #test get geogrpahic coordinate
        toolbox = {"earth radius": 6339000}
        Get_All_Station(toolbox)
        pprint(toolbox["coordinate"])
        x = [toolbox["coordinate"][key][0] for key in toolbox["coordinate"]]
        y = [toolbox["coordinate"][key][1] for key in toolbox["coordinate"]]
        plt.figure()
        plt.scatter(y,x)
        a = [key for key in toolbox["coordinate"]]
        for i,label in enumerate(a):
            plt.annotate(label,(y[i],x[i]))
        plt.show()
    