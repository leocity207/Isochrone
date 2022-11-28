import unittest

import sys
 
# setting path
sys.path.append('../')

from line import *
from data import *
from util import *

class Line_Test(unittest.TestCase):

    Line.toolbox = {}
    
    @classmethod
    def setUpClass(cls):
        Line.toolbox["starting time"] = datetime.datetime.strptime("7:00","%H:%M")
        Line.toolbox["speed"] = 1.11 #m/s
        Line.toolbox["starting coordinate"] = np.array([50,50])
        Line.toolbox["earth radius"]= 6339000
        Line.toolbox["Ressource_path"] = "..\..\.."
        Line.toolbox["day info"] = [WEEK_DAY.MONDAY,DAY_TYPE.SCHOOL]
        Get_All_Station(Line.toolbox)
        Get_All_Lines(Line.toolbox)
        
    def test_Get_Coordinate(self):
        print(" ")
        vienne_station = Station.Find_Station_By_Name("Gare de Vienne")
        lycee_station = Station.Find_Station_By_Name("Lycée Ella Fitzgerald")
        
        self.assertEqual(vienne_station.Get_Coordinate(),vienne_station.coordinate)
        self.assertEqual(lycee_station.Get_Coordinate(),lycee_station.coordinate)
        print("test_Get_Coordinate: OK")
    
    def test_Get_Travel_Time_Station_To_Station(self):
        print(" ")
        college_station = Station.Find_Station_By_Name("Collège Grange")
        gare_vienne = Station.Find_Station_By_Name("Gare de Vienne")
        func_ret = college_station.Get_Travel_Time_Station_To_Station(gare_vienne)
        college_coordinate = college_station.coordinate
        vienne_coordinate = gare_vienne.coordinate
        travel_time =   Get_Base_Travel_Time(college_coordinate,vienne_coordinate,Station.toolbox)
        travel_time2 = Get_Base_Travel_Time(vienne_coordinate,college_coordinate,Station.toolbox)
        self.assertEqual(travel_time,func_ret)
        self.assertEqual(func_ret,travel_time2)
        print("Get_Travel_Time_Station_To_Station: OK")
        
    
    def test_Get_Time_From_Start(self):
        print(" ")
        gare_vienne = Station.Find_Station_By_Name("Gare de Vienne")
        Station.toolbox["starting coordinate"] = gare_vienne.coordinate
        
        self.assertEqual(gare_vienne.Get_Time_From_Start(),datetime.timedelta(0))
        print("test_Get_Time_From_Start: OK 1")
        
        horloge = Station.Find_Station_By_Name("L'Horloge")
        time_start_horloge = horloge.Get_Time_From_Start()
        horloge_coordinate = horloge.coordinate
        horloge_computed_time_start = Get_Base_Travel_Time(horloge_coordinate,Station.toolbox["starting coordinate"],Station.toolbox)
        self.assertEqual(time_start_horloge,horloge_computed_time_start)
        print("test_Get_Time_From_Start: OK 2")
    
    def test_Get_Passing_Lines(self):
        print(" ")
        vienne_station = Station.Find_Station_By_Name("Gare de Vienne")
        lycee_station = Station.Find_Station_By_Name("Lycée Ella Fitzgerald")
        
        vienne_lines_list = vienne_station.Get_Passing_Lines()
        vienne_line_name_list = ["line 1","line 2","line 3","line 4","line 5","line 6","line 7","line 8"]
        true_vienne_lines_list = [Line.Get_Line_By_Name(station_name) for station_name in vienne_line_name_list]
        for from_get in vienne_lines_list:
            self.assertTrue(from_get in true_vienne_lines_list)
        for true_get in true_vienne_lines_list:
            self.assertTrue(true_get in vienne_lines_list)
        print("Get_Passing_Lines: OK 1")
        
        lycee_line_list = lycee_station.Get_Passing_Lines()
        lycee_station_name_list = ["line 134"]
        true_lycee_line_liste = [Line.Get_Line_By_Name(station_name) for station_name in lycee_station_name_list]
        for from_get in lycee_line_list:
            self.assertTrue(from_get in true_lycee_line_liste)
        for true_get in true_lycee_line_liste:
            self.assertTrue(true_get in lycee_line_list)
        print("Get_Passing_Lines: OK 2")
    
if __name__ == '__main__':
    unittest.main()