
from pydoc import doc


def To_Decimal(degree,minute,second):
    return degree + minute/60 + second/3600

def Parse_String_To_Coordinate(the_string):
    degree = ""
    minute = ""
    second = ""
    letter = ""

    i=0

    while(the_string[i] != '°'):
        degree += the_string[i]
        i+=1
    i+=1
    while (the_string[i] != '\''):
        minute += the_string[i]
        i+=1
    i+=1
    while (the_string[i] != "\""):
        second += the_string[i]
        i+=1
    i+=1
    letter = the_string[i]
    return (int(degree),int(minute),float(second),letter)
     
def Parse_String_To_Decimal(the_string):
    deg,min,sec,let = Parse_String_To_Coordinate(the_string)
    return To_Decimal(deg,min,sec)

if __name__ == "__main__":
    test = "45°31\'57.5\"N 4°52\'27.4\"E"
    test1 = "45°31\'57.5\"N"
    print(test1)
    deg,min,sec,let = Parse_String_To_Coordinate(test1)
    print(To_Decimal(deg,min,sec))
    
