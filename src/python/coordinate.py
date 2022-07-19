
from pickle import NONE
from pydoc import doc
import numpy as np


def To_Decimal(degree,minute,second):
    return degree + minute/60 + second/3600

def Coordinate_String_To_Angulare_Decomposition(the_string):
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
     
def Parse_String_To_Angular_Decimal(the_string):
    deg,min,sec,let = Coordinate_String_To_Angulare_Decomposition(the_string)
    return (To_Decimal(deg,min,sec),let)


def Parse_Angular_String_To_Plane(the_string,mean_latitude_factor,planet_radius):
    splited_string = the_string.split()
    assert(len(splited_string) == 2)
    angular_coord = ["",""]
    for i in range(2):
        angle,let = Parse_String_To_Angular_Decimal(splited_string[i])
        if(let == "N" or let == 'S'):
            assert(angular_coord[0] == "")
            angular_coord[0] = planet_radius*angle
        elif(let == "E" or let == "W"):
            assert(angular_coord[1] == "")
            angular_coord[1] = planet_radius*angle*mean_latitude_factor
    return angular_coord




if __name__ == "__main__":
    EARTH_RADIUS = 1
    mean_latitude_factor =  np.cos(np.pi/4)
    test = "45°31\'57.5\"N 4°52\'27.4\"E"
    test1 = "45°31\'57.5\"N"
    print(test1)
    deg,min,sec,let = Coordinate_String_To_Angulare_Decomposition(test1)
    print(To_Decimal(deg,min,sec))
    print("---------------------")
    print(Parse_Angular_String_To_Plane(test,mean_latitude_factor,EARTH_RADIUS))
    
