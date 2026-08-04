from collections import Counter, OrderedDict
from itertools import combinations

class Solution:

    def longestBalanced(self, s: str) -> int:

        ss_dict = OrderedDict()

        all_subs = []

        ##  Generate all substrings in useful order (as opposed to s[i:j]).

        for i in range(0, len(s)):

            for j in range(0, len(s) - i):

                all_subs += [s[j:j + i]]

        print(all_subs)

        ##  Count quantities within each substring.

        for sub in all_subs:

            if sub not in ss_dict:
                ss_dict[sub] = Counter(sub)

        print(ss_dict)

        ##  Cut the last substring.

        last = ss_dict.popitem()

        ##  Nothing can be added to the largest substring, so check only that.

        if last[1]['0'] == last[1]['1']:

            return len(last[0])

        ##  For any smaller substring...



        for i in range(len(ss_dict)):

            last_new = ss_dict.popitem()

            ##if last_new[1]['0'] == last_new[1]['1']

            print(last_new)

        

        


        
