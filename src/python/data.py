
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
# fetch all the station from the ressources files
# - toolbox: the toolbox containing all the data
def Get_All_Station(toolbox: dict) -> None:
    path_to_cordinate_file = "..\..\Ressource\Geographie\coordinate.csv"
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
    path_to_ressource = "../../Ressource"
    lines_folders = ["ligne1"]
    line_list = []
    for line_folder in lines_folders:
        path_to_line = os.path.join(path_to_ressource,line_folder)
        a_way = {"scolaire":{"monday":[],"tuesday":[],"wednesday":[],"thushday":[],"friday":[],"saturday":[],"sunday":[]},"holyday":{"monday":[],"tuesday":[],"wednesday":[],"thushday":[],"friday":[],"saturday":[],"sunday":[]}}
        r_way = {"scolaire":{"monday":[],"tuesday":[],"wednesday":[],"thushday":[],"friday":[],"saturday":[],"sunday":[]},"holyday":{"monday":[],"tuesday":[],"wednesday":[],"thushday":[],"friday":[],"saturday":[],"sunday":[]}}
        station_list = []
        for root,dir,files in os.walk(path_to_line):
            for file in files:
                if not(file.endswith(".csv")):
                    continue
                file_data = Get_CSV_File_As_data(os.path.join(path_to_line,file))
                Update_station_list(station_list,file_data)
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
        toolbox["line list"] = Line(station_list,toolbox)

#-------------------------------------------------------------------------------------------
# given a list of already registered station check if the new station should be added or not
# - station_list  : a list of string containing all the already registered station
# - new_file_data : all the new station that probably need to be added to the station_list 
def Update_station_list(station_list: list, new_file_data: list) -> None:
    for row in new_file_data:
        if row[0] in station_list:
            continue
        station_list.append(row[0])

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
        print(len(data))

#-----------------------------------------------------------------
# given a filepath to a schedule,fetch the file data and give it back as a list
# - filepath: path to the schedule file
# - return: the schedule file as a list
def Get_CSV_File_As_data(filepath: str) -> list:
    with open(filepath) as csv_file:
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
        Get_All_Station(toolbox)
    if(True): #test get geogrpahic coordinate
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