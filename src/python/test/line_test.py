import unittest

import sys
 
# setting path
sys.path.append('../')

from line import *
from data import *

class Line_Test(unittest.TestCase):

    Line.toolbox = {}
    
    @classmethod
    def setUpClass(cls):
        Line.toolbox["starting time"] = datetime.datetime.strptime("7:00","%H:%M")
        Line.toolbox["speed"] = 5
        Line.toolbox["starting coordinate"] = np.array([50,50])
        Line.toolbox["earth radius"]= 6339000
        Line.toolbox["Ressource_path"] = "..\..\.."
        Get_All_Lines(Line.toolbox)
        Get_All_Station(Line.toolbox)
        
        
    
    def test_Get_Correct_Timetable(self):
        line_list = Line.toolbox["line list"]
        
        Line.toolbox["day info"] = [WEEK_DAY.MONDAY,DAY_TYPE.SCHOOL]
        line_2 =  Line.Get_Line_By_Name("line 2")
        line_2_schedule = line_2.Get_Correct_Timetable(True)
        self.assertEqual(line_2_schedule, line_list[1].m_a_way[0]["schedule"])
        print("test_Get_Correct_Timetable 1 OK")
        
        Line.toolbox["day info"] = [WEEK_DAY.SUNDAY,DAY_TYPE.EVERYDAY]
        line_2 =  Line.Get_Line_By_Name("line 2")
        line_2_schedule = line_2.Get_Correct_Timetable(True)
        self.assertEqual(line_2_schedule, line_list[1].m_a_way[2]["schedule"])
        print("test_Get_Correct_Timetable 2 OK")
        
        Line.toolbox["day info"] = [WEEK_DAY.SUNDAY,DAY_TYPE.SCHOOL]
        line_2 =  Line.Get_Line_By_Name("line 2")
        line_2_schedule = line_2.Get_Correct_Timetable(True)
        self.assertEqual(line_2_schedule, None)
        print("test_Get_Correct_Timetable 3 OK")
        
        Line.toolbox["day info"] = [WEEK_DAY.MONDAY,DAY_TYPE.SCHOOL]
        line_1 =  Line.Get_Line_By_Name("line 1")
        line_1_schedule = line_1.Get_Correct_Timetable(False)
        self.assertEqual(line_1_schedule, line_list[0].m_r_way[0]["schedule"])
        print("test_Get_Correct_Timetable 4 OK")
        
        
    def test_Get_Stations_Excluding(self):
        print("")
        
        line_7 =  Line.Get_Line_By_Name("line 7")
        
        station_list = line_7.Get_Stations_Excluding(Line.toolbox["station_list"][0])
        self.assertEqual(station_list,line_7.station_list)
        print("test_Get_Stations_Excluding 1 OK")
        
        station_list_2 = line_7.Get_Stations_Excluding(Line.toolbox["station_list"][11])
        copy_line_7_station = line_7.station_list
        copy_line_7_station.pop(copy_line_7_station.index("Jardin de Ville"))
        self.assertEqual(station_list_2,copy_line_7_station)
        print("test_Get_Stations_Excluding 2 OK")

    
    def test_Is_Station_In_Line(self):
        print("")

        gare_de_vienne = Station.Find_Station_By_Name("Gare de Vienne")
        
        line_1 = Line.Get_Line_By_Name("line 1")
        line_134 =  Line.Get_Line_By_Name("line 134")

        self.assertEqual(line_1.Is_Station_In_Line(gare_de_vienne),True)
        print("test_Is_Station_In_Line 1 OK")

        self.assertEqual(line_134.Is_Station_In_Line(gare_de_vienne),False)
        print("test_Is_Station_In_Line 1 OK")
    

    def test_Get_Best_Time_To_Station(self):
        print("")
        line_6 = Line.Get_Line_By_Name("Line_6")
        Line.toolbox["starting time"] = datetime.datetime.strptime("6:00","%H:%M")

        gare_de_vienne = Station.Find_Station_By_Name("Gare de Vienne")
        Claire_de_lune = Station.Find_Station_By_Name("Clair de Lune")

        best_time = line_6.Get_Best_Time_To_Station(gare_de_vienne,Claire_de_lune)

        self.assertEqual(best_time,datetime.datetime.strptime("7:38","%H:%M"))

        #station need to change their best time
        Line.toolbox["starting time"] = datetime.datetime.strptime("21:00","%H:%M")

        best_time = line_6.Get_Best_Time_To_Station(gare_de_vienne,Claire_de_lune)

        self.assertEqual(best_time,-1)


if __name__ == '__main__':
    unittest.main()