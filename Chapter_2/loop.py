from time import time

N = 2**4

t1=time()
tot= 0.0

for i in range(N):
    tot += i

t2=time()

print(tot)
print("Took:",t2-t1)
