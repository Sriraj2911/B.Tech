import numpy as np

nan32 = np.float32('nan')

def factorial(a: int) -> int:
    result = 1
    while a > 0:
        result *= a
        a -= 1
    return result

def power(a: float, n: int) -> np.float32:
    a = np.float32(a)
    if n == 0:
        return np.float32(1)
    if a == np.float32(0):
        return np.float32(0)
    result = np.float32(1)
    while n > 0:
        result *= a
        n -= 1
    return np.float32(result)

def exp(a: float, n: int) -> np.float32:
    a = np.float32(a)
    result = np.float32(0)
    while(n > 0):
        num = power(a, n-1)
        den = factorial(n-1)
        result += np.float32(num / den)
        n -= 1
    return np.float32(result)

def sin(a:float, n:int) -> np.float32:
    a = np.float32(a)
    result = np.float32(0)
    while(n > 0):
        temp = 2*n-1
        num = power(a, temp)
        den = factorial(temp)
        # Add to the result if odd term
        if(n%2):
            result += np.float32(num/den)
        # Subtract from the result if even term
        else:
            result -= np.float32(num/den)
        n -= 1
    return np.float32(result)

def cos(a:float, n:int) -> np.float32:
    a = np.float32(a)
    result = np.float32(0)
    while(n > 0):
        temp = 2*n-2
        num = power(a, temp)
        den = factorial(temp)
        # Add to the result if odd term
        if(n%2):
            result += np.float32(num/den)
        # Subtract from the result if even term
        else:
            result -= np.float32(num/den)
        n -= 1
    return np.float32(result)

def ln(a:float, n:int) -> np.float32:
    if(a <= 0):
        return nan32
    
    a = a-1
    a = -1*a
    a = np.float32(a)
    result = np.float32(0)
    while(n > 0):
        num = power(a, n)
        den = n
        result += np.float32(num/den)
        n -= 1
    return np.float32(-1*result)

def inv(a:float, n:int) -> np.float32:
    if(a<=0 or a>=2):
        return nan32
    
    a = 1-a
    a = np.float32(a)
    result = np.float32(0)
    while(n > 0):
        result += np.float32(power(a, n-1))
        n -= 1
    return np.float32(result)


# Example usage
a = float(input())
n = int(input())
print(ln(a, n))