
class A:
    def __init__(self,a):
        self.a = a 
    def change_a(self,param):
        self.a["a"] = param
if __name__ == "__main__":
    a = {}
    obj = A(a)
    print(a)
    a["c"]="c"
    print(a)
    obj.change_a("a")
    print(a)
