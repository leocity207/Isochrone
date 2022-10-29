import numpy as np
import datetime

def Get_Base_Travel_distance(coord_1,coord_2):
    return np.linalg.norm([coord_1[0]-coord_2[0],coord_1[1]-coord_2[1]])

def Get_Base_Travel_Time(coord_1,coord_2,toolbox):
    time_s = round(Get_Base_Travel_distance(coord_1,coord_2)/toolbox["speed"])
    H = time_s // 3600
    M = (time_s - H) // 60
    M_plus = 1 if time_s - (H*3600+M*60) >30 else 0
    M = M + M_plus
    return datetime.timedelta(minutes=M,hours=H)
