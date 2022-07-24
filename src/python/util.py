import numpy as np

def Get_Base_Travel_distance(coord_1,coord_2):
    return np.linalg.norm([coord_1[0]-coord_2[0],coord_1[1]-coord_2[1]])

def Get_Base_Travel_Time(coord_1,coord_2,toolbox):
    return Get_Base_Travel_distance(coord_1,coord_2)/toolbox["speed"]