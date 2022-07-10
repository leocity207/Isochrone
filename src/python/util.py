import numpy as np
def Get_Base_Travel_Time(coord_1,coord_2,toolbox):
    return np.linalg.norm(coord_1-coord_2)/toolbox["speed"]