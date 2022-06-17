
def IsNumber(c):
    if c in['1','2','3','4','5','6','7','8','9','0']:
        return True
    return False
def IsSpace(c):
    if(c in [' ']):
        return True
    return False

if __name__ == "__main__":
    file = "C:/Users/Leo/Documents/python/Isochrone/Ressource/Ligne1/ligne_1_vlmmjv_s.csv"
    with open(file,"r+",encoding="utf-8") as f:
        data = list(f.read())
        for i in range(len(data)):
            if(i<(len(data)-1) and IsNumber(data[i]) and IsSpace(data[i+1])):
                data[i+1] = ";"
        j=0
        while(j < len(data)):
            if(data[j] == "|"):
                data.pop(j)
            else:
                j+=1
        f.seek(0)
        f.write(''.join(data))