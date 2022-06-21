
def IsLeter(c):
    if c in "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ":
        return True
    return False

def IsNumber(c):
    if c in "1234567890":
        return True
    return False

def IsSpace(c):
    if c == ' ':
        return True
    return False

def IsTwoPoint(c):
    if c == ':':
        return True
    return False
def IsDashPoint(c):
    if c == ';':
        return True
    return False
def IsPipe(c):
    if c == '|':
        return True
    return False

def Is_Data(data,i):
    if(IsNumber(data[i]) and IsNumber(data[i+1]) and IsTwoPoint(data[i+2])):
        return True
    if(IsNumber(data[i]) and IsTwoPoint(data[i+1]) and IsNumber(data[i+2])):
        return True
    return False

if __name__ == "__main__":
    file = "C:/Users/Leocl/Documents/Isochrone/Ressource/Ligne3/line.txt"
    file2 = "C:/Users/Leocl/Documents/Isochrone/Ressource/Ligne3/liner.txt"
    data = []
    
    CITY_TEMPLATE = ["VIENNE","ESTRABLIN","SEYSSUEL","ST-ROMAIN"]
    with open(file,"r+",encoding="utf-8") as f:
            data = f.readlines()
    line_Length = []
    for i in range(len(data)):
        line = data[i]
        line=line.replace('|','')
        has_been_popped = False
        #check city
        for city in CITY_TEMPLATE:
            if city in line:
                data.remove(line)
                has_been_popped = True
                break
        if has_been_popped:
            continue
        line_list = list(line)
        
        #pop number if there are some
        while(IsNumber(line_list[0]) or IsSpace(line_list[0])):
            line_list.pop(0)
            
        #find the longest title
        l = 0
        while(not(Is_Data(line_list,l))):
            l+=1
        line_Length.append(l)
        line_list.insert(l,';')
        line = ""
        data[i] = line.join(line_list)
    
    max_length = max(line_Length)
    for i in range(len(data)):
        line = data[i]
        line_list = list(line)
        if i == 29:
            print('l')
        for l in range(max_length):
            if(not(IsDashPoint(line_list[l]))):
                continue
            else:
                line_list.insert(l,' ')
        #remove unwanted space and add dot comma
        l = max_length
        while l < (len(line_list)-1):
            if(IsNumber(line_list[l]) and IsSpace(line_list[l+1])):
                line_list[l+1] = ";"
                l+=1
            elif(IsSpace(line_list[l])):
                line_list.pop(l)
            else:
                l+=1

        line = ""
        line_list.insert(-1,';')
        data[i] = line.join(line_list)
    for line in data:
        print(line)
    with open(file2,"w",encoding="utf-8") as f:
         data = f.writelines(data)
       
    
        
    
        
            
        
        
        