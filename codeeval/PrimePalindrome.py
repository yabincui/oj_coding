import math

def isPalindrome(n):
    digits = []
    while n != 0:
        digits.append(n % 10)
        n /= 10
    i = 0
    j = len(digits) - 1
    while i < j:
        if digits[i] != digits[j]:
            return False
        i += 1
        j -= 1
    return True

def isPrime(n):
    if n < 2:
        return False
    elif n == 2:
        return True
    elif n % 2 == 0:
        return False
    half = int(math.sqrt(n))
    for i in range(3, half + 1, 2):
        if n % i == 0:
            return False
    return True

for i in range(999, 0, -1):
    if isPrime(i) and isPalindrome(i):
        print '%d' % i
        break
