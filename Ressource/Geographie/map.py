from coordinate import *
import os
import matplotlib.pyplot as plt

if __name__ == "__main__":
    filename = "Ressource\\Geographie\\coordinate.csv"
    filepath = os.path.join(os.getcwd(),filename)
    data = []
    regulx = 45.5
    reguly = 4.4
    with open(filepath,"r",encoding="utf-8") as f:
         data = f.readlines()
    for i in range(len(data)):
        data[i]=data[i].replace('\n','')
        data[i]=data[i].split(';')
    print(data)
    X=[]
    Y=[]
    for i in range(len(data)):
        coordinate = data[i][1]
        coordinate = coordinate.split(' ')
        X += [Parse_String_To_Decimal(coordinate[0])-regulx]
        Y += [Parse_String_To_Decimal(coordinate[1])-reguly]
    plt.figure()
    plt.plot(Y,X)
    plt.show()
