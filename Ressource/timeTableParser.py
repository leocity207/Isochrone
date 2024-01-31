import os



def Get_File_data(filename):
    with open(filename,encoding='utf8') as file:
        return file.readlines()


def Divide_ligne(lines):
    side_1 = []
    side_2 = []
    has_encounter_first_side = False
    has_finishe_first_side = False
    for i in range(len(lines)):
        if(i == 0):
            continue
        if lines[i].startswith("Ligne "):
            if(has_encounter_first_side or not(has_finishe_first_side)):
               has_encounter_first_side = True
               #lines[i] = lines[i].replace('\t',' ')
               lines[i] = lines[i].replace('\n',' ')
               side_1.append(lines[i])
            if(has_finishe_first_side):
                #lines[i] = lines[i].replace('\t',' ')
                lines[i] = lines[i].replace('\n',' ')
                side_2.append(lines[i])
        else:
            if(has_encounter_first_side):
                has_finishe_first_side = True
    return side_1,side_2

def Divide_Unique_Line(line):
    line = line.replace('\t\t','@')
    line = line.replace('\t','@')
    line = line.split()
        
if __name__ == "__main__":
    data = Get_File_data("C:\\Users\\Leo\\Documents\\python\\isochrone\\timetable\\ligne 1.txt")
    side_1,side_2 = Divide_ligne(data)
    for line in side_1:
        Divide_Unique_Line(line)
        print(line)
        