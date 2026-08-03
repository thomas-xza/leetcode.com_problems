##  If represented graphically, this is allegedly an NP-hard problem:
##  https://en.wikipedia.org/wiki/Longest_path_problem
##  Admittedly I never really liked graph theory (both before and during university), but understand the value in mapping software.
##  So, this is intentionally unfinished.
##  There are presumably some greedy algorithms that work for the tests, but I don't know how long it would take to find one.

class Solution:
    
    def longestSubsequence(self, nums: List[int]) -> int:

        boundaries = [0 for _ in range(len(nums))]

        diffs = [0 for _ in range(len(nums))]

        for i, v in enumerate(nums):

            if i > 0:

                diffs[i] = abs(nums[i-1] - nums[i])

            if i > 1 and (diffs[i-1] < diffs[i]):

                boundaries[i-1] = 1

        seqs = []
        seqs_diffs = []

        start = 0

        for i, v in enumerate(boundaries):

            if v == 1:

                seqs += [nums[start:i+1]]
                seqs_diffs += [diffs[start:i+1]]

                start = i + 1

        seqs += [nums[start:i+1]]
        seqs_diffs += [diffs[start:i+1]] 

        seqs_meta = gen_metadata(seqs)

        print(boundaries, "boundaries")
        print(diffs, "diffs")
        print(seqs, "seqs")
        print(seqs_diffs, "seqs_diffs")


        
