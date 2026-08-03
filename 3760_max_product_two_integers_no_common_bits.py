##  Fails later test featuring a large quantity of unique data.

from itertools import combinations

class Solution:

    def maxProduct(self, nums: List[int]) -> int:

        best = 0
        
        candidates = []

        nums_uniq = list(set(nums))

        nums_uniq.sort()

        for c in combinations(nums_uniq, 2):

            if c[0] & c[1] == 0:

                test = c[0] * c[1]

                if test > best:

                    best = test  
                
        return best




        
