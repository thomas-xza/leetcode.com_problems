##  Leaning on libraries implemented in C to avoid execution timeouts.

from collections import Counter
from itertools import combinations
from collections import defaultdict

class Solution:

    def maximumWidth(self, planks: list[int]) -> int:

        if len(planks) == 1:
            return 1

        ##  Convert raw data to structured dictionary.

        counts = Counter(planks)

        planks_uniq = list(counts.keys())

        ##print(planks_uniq)

        heights = defaultdict(int)

        combs = combinations(planks_uniq, 2)

        for (p1, p2) in combs:

            h = p1 + p2

            heights[h] += min([counts[p1], counts[p2]])
                    
        ##print(heights)

        for h in list(counts.keys()):
            
            heights[h] += counts[h]

            if counts[h] > 1:
                heights[h*2] += counts[h] // 2

        ##print(heights)

        return max(heights.values())
