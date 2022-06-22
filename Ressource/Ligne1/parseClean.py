import argparse
import os

#template inside the string that apear and that we want removed
CITY_TEMPLATE = ["VIENNE","ESTRABLIN","SEYSSUEL","ST-ROMAIN"]

#Used for parsing args 
def Parse_Args():
    parser = argparse.ArgumentParser(description='Made to prosse and Clean schedule files.')
    parser.add_argument('String', metavar='filename', type=str, help='the filename of the file to clean')
    return parser.parse_args()

# check if the given parameter 'c' is a Leter 
def IsLeter(c):
    if c in "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ":
        return True
    return False

# check if the given parameter 'c' is a number (strin)
def IsNumber(c):
    if c in "1234567890":
        return True
    return False

#check if the data at index i is part of date
def Is_Date(data,i):
    if(IsNumber(data[i]) and IsNumber(data[i+1]) and data[i+2] == ':'):
        return True
    if(IsNumber(data[i]) and data[i+1]==':' and IsNumber(data[i+2])):
        return True
    return False

#return the file data as a list of line
def Get_File_Data(filename):
    with open(filename,"r",encoding="utf-8") as f:
            return f.readlines()

#strip the lines of the CITY_TEMPLATE
def Strip_Big_City(lines):
    for i in range(len(lines)):
        for city in CITY_TEMPLATE:
            if city in lines[i]:
                lines[i] = lines[i].replace(city, "")
                break
    return lines
# Remove unwanted number in front of the lines
def Remove_Front_Number_Space(lines):
    for i in range(len(lines)):
        line_as_list = list(lines[i])
        while(IsNumber(line_as_list[0]) or line_as_list[0] == ' '):
            line_as_list.pop(0)
        lines[i] = ''.join(line_as_list)
    return lines

#give back the length of the station string inside the whole sring
def Get_Station_Lengths(lines):
    stations_length =[]
    for i in range(len(lines)):
        l = 0
        while(not(Is_Date(lines[i],l))):
            l+=1
        stations_length.append(l)
    return stations_length

#remove the '|' from all the strings
def Remove_Pipe_Character(lines):
    for i in range(len(lines)):
        lines[i] = lines[i].replace('|','')
    return lines

#equalize the titles to be more readable
def Equalize_Titles(lines,max_length):
    for i in range(len(lines)):
        line_as_list = list(lines[i])
        for l in range(max_length):
            if(not(IsNumber(line_as_list[l]))):
                continue
            else:
                line_as_list.insert(l,' ')
        line_as_list.insert(max_length,';')
        lines[i] = ''.join(line_as_list)
    return lines

#separate the dates by 
def Separate_Dates(lines):
    for i in range(len(lines)):
        line_as_list = list(lines[i])
        l = max_length
        while l < (len(line_as_list)-1):
            if(IsNumber(line_as_list[l]) and line_as_list[l+1]==' '):
                line_as_list[l+1] = ";"
                l+=1
            elif(line_as_list[l] == ' '):
                line_as_list.pop(l)
            else:
                l+=1
        line_as_list.insert(-1,';')
        lines[i] = ''.join(line_as_list)
    return lines
    
    
if __name__ == "__main__":
    args = Parse_Args()
    print(args.String)
    filename = ""
    if args.String:
        filename = args.String
    filepath = os.path.join(os.getcwd(),filename)
    
    data_list = Get_File_Data(filename)
    
    data_list = Remove_Pipe_Character(data_list)
    
    data_list = Strip_Big_City(data_list)
    
    data_list = Remove_Front_Number_Space(data_list)
    
    station_length_list = Get_Station_Lengths(data_list)
    
    max_length = max(station_length_list)
    
    data_list = Equalize_Titles(data_list,max_length)
    
    data_list = Separate_Dates(data_list)
    
    with open(filepath,"w",encoding="utf-8") as f:
         data = f.writelines(data_list)
       
    
        
    
        
            
        
        
        