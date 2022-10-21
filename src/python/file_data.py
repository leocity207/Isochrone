

from calendar import FRIDAY, THURSDAY
from ctypes.wintypes import CHAR

from enum import Enum
import re
 
class DAY_TYPE(Enum):
    SCHOOL = 1
    VACTION = 2
    EVERYDAY = 3
    HOLIDAY = 4

class WEEK_DAY(Enum):
    MONDAY    = 1
    TUESDAY   = 2
    WEDNESDAY = 3
    THURSDAY  = 4
    FRIDAY    = 5
    SATURDAY  = 6
    SUNDAY    = 7

def Int_To_Week_Day(value: int): 
    for e in WEEK_DAY:
        if e.value == value:
            return e
    raise Exception("weekday is probably not good")


class File_Date:
    def __init__(self,day_list: list,type: DAY_TYPE):
        self.day_list = day_list
        self.type = type

    #------------------------------
    # #Function used to check if a day and day type are compatible with self(day is in day_list and day type is the same)
    # this function is used when trying to match setup and known schedule of transport
    # day: a day of the week 
    # type: a day type
    # return: tru or false if we found the template in our data    
    def Is_Matching(self,day: WEEK_DAY, type:DAY_TYPE):
        if(day in self.day_list and self.type == type):
            return True
        return False

    #-------------------------------------------------------------------------------------------------------
    #it is expected that file data is a list of string contining the title of the file without the extension
    # - file_data : represent the name of the file
    # - return : a list of File_Data
    @staticmethod
    def Create_from_file_data(file_data):
        assert len(file_data)>=4
        list_of_file_data = []
        for i in range(3,len(file_data)):

            data = file_data[i]
            #find all nuymber and convert them into weekday list
            day_num_found = re.findall("[0-9]", data)
            if(day_num_found == []):
                day_num_found = "1234567"
            day_str = [WEEK_DAY(int(day_num_found[i])) for i in range(len(day_num_found))]
            type = re.findall("[a-z]", data)[0]
            #find the leter and transfor it into a day type
            if(type == "t"):
                type = DAY_TYPE.EVERYDAY
            elif(type == "s"):
                type = DAY_TYPE.SCHOOL
            elif(type == "v"):
                type = DAY_TYPE.VACTION
            elif(type == "f"):
                type = DAY_TYPE.HOLIDAY
            else:
                raise Exception("unknown type of day found in file name")
            
            # create a new objct of File_Data and add it to the list to be returned
            list_of_file_data.append(File_Date(day_str,type))
        return list_of_file_data
        