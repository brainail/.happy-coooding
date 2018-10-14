from math import factorial as fact
 
def goodEnough(n,r):
    return fact(n)/((fact(n-r)*fact(r)))
 
def goodStringsCount(n):
    return goodEnough(26,n)*(2**n - n - 1)