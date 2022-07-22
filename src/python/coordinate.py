
from pickle import NONE
from pydoc import doc
import numpy as np

#--------------------------------------------------------------------
# Transform a angle(degree,minute,second) into a single decimal angle
# - degree : the degree value of the angle
# - minute : the minute value of the angle
# - second : the second value of the angle
# - return : the angle as a decimal value
def To_Decimal(degree: int,minute: int,second: int) -> float:
    return degree + minute/60 + second/3600


#---------------------------------------------------------
# transforma string representing an angule into it's value
# - the string : a string representing an angle (ex : " 46°31'57.5"N ")
# - return : - degree (int)  : the degree value of the angle
#            - minute (int)  : the minute value of the angle
#            - seconde (int) : the second value of the angle
#            - letter (str)  : the letter indicating in wich hemisphere we are giving the coordinate ("N,S,W,E")
def Coordinate_String_To_Angulare_Decomposition(the_string: str) -> tuple:
    degree = ""
    minute = ""
    second = ""
    letter = ""

    i=0

    while(the_string[i] != '°'):
        degree += the_string[i]
        i+=1
    i+=1
    while (the_string[i] != '\''):
        minute += the_string[i]
        i+=1
    i+=1
    while (the_string[i] != "\""):
        second += the_string[i]
        i+=1
    i+=1
    letter = the_string[i]
    return (int(degree),int(minute),float(second),letter)
     
def Parse_String_To_Angular_Decimal(the_string: str) -> tuple():
    deg,min,sec,let = Coordinate_String_To_Angulare_Decomposition(the_string)
    return (To_Decimal(deg,min,sec),let)


def Parse_Angular_String_To_Plane(the_string: str,mean_latitude_factor: float,planet_radius: float) -> float:
    splited_string = the_string.split()
    assert(len(splited_string) == 2)
    plane_coord = ["",""]
    for i in range(2):
        angle,let = Parse_String_To_Angular_Decimal(splited_string[i])
        if(let == "N" or let == 'S'):
            assert(plane_coord[0] == "")
            plane_coord[0] = planet_radius*angle
        elif(let == "E" or let == "W"):
            assert(plane_coord[1] == "")
            plane_coord[1] = planet_radius*angle*mean_latitude_factor
    return plane_coord

def Parse_Angular_String_To_Decimal(the_string: str) ->float:
    splited_string = the_string.split()
    assert(len(splited_string) == 2)
    angular_coord = ["",""]
    for i in range(2):
        angle,let = Parse_String_To_Angular_Decimal(splited_string[i])
        if(let == "N" or let == 'S'):
            assert(angular_coord[0] == "")
            angular_coord[0] = angle
        elif(let == "E" or let == "W"):
            assert(angular_coord[1] == "")
            angular_coord[1] = angle
    return angular_coord

def Get_Mean_Latitude_Angular_Strings(string_list: list) -> float:
    list_of_decimal_angular_latitude = []
    for string in string_list:
        list_of_decimal_angular_latitude.append(Parse_Angular_String_To_Decimal(string)[0])
    return np.mean(list_of_decimal_angular_latitude)
    


def Parse_Angular_String_To_Plane_List(string_list: list,planet_radius: float) -> tuple:
    mean_latitude_factor = Get_Mean_Latitude_Angular_Strings(string_list)
    list_coordinate = []
    for string in string_list:
        list_coordinate.append(Parse_Angular_String_To_Plane(string,mean_latitude_factor,planet_radius))
    mean_x = np.mean([row[0] for row in list_coordinate])
    mean_y = np.mean([row[1] for row in list_coordinate])
    for i in range(len(list_coordinate)):
        list_coordinate[i] = [list_coordinate[i][0]-mean_x,list_coordinate[i][1]-mean_y]
    return (list_coordinate,mean_x,mean_y)


if __name__ == "__main__":
    EARTH_RADIUS = 1
    a = ["46°31\'57.5\"N 4°52\'27.4\"E",
         "45°31\'57.5\"N 4°52\'27.4\"E",
         "47°31\'57.5\"N 4°52\'27.4\"E",
         "44°31\'57.5\"N 4°52\'27.4\"E",
         "43°31\'57.5\"N 4°52\'27.4\"E"]
    print(Parse_Angular_String_To_Plane_List(a,EARTH_RADIUS))
    
