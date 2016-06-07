
import math

prime_list = [2]

def isPrime(n):
    half = int(math.sqrt(n))
    for i in prime_list:
        if i > half:
            break
        if n % i == 0:
            return False
    return True

i = 3
while len(prime_list) < 1000:
    if isPrime(i):
        prime_list.append(i)
    i += 2

print '%d' % sum(prime_list)
