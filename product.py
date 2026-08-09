##  Wizako GMAT practice questions

from itertools import product
c = 0 

for tup in product([1,2], repeat=6):

##  print(tup)

  n = int(''.join(str(x) for x in tup))

  if n % 3 == 0: 
    print(n)
    c+= 1

print(c)
