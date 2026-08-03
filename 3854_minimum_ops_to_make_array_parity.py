class Solution:

    def makeParityAlternating(self, nums: List[int]) -> List[int]:

        answer = [0, 0]

        nums_norm = self.normalise_nums(nums)

        ##print(nums_norm)

        min_ops, differences = self.deduce_pattern_with_fewest_differences(nums_norm)

        print(differences[0])
        print(differences[1])

        answer[0] = min(min_ops)

        answer[1] = self.find_minimum_range(nums, min(min_ops), differences)

        return answer


    def find_minimum_range(self, nums: List[int], limit: int, differences: tuple[List[int]]) -> int:

        ##  Leetcode tests begin to throw myriad edge cases at this point.

        ##  min() and max() disregard positions, so the values returned may not be the best possible.

        min_potential = min(nums)
        max_potential = max(nums)

        min_best = 65536
        max_best = -65536

        patterns_final = [copy.deepcopy(nums),
                          copy.deepcopy(nums)]

        res = ()

        for pat_n, pat_diff in enumerate(differences):

            if sum(pat_diff) <= limit:

                ##  Deduce the best possible max/min based on what can't be changed.

                for i, d in enumerate(pat_diff):

                    if d == 0:

                        if nums[i] == min_potential:
                            
                            min_best = min_potential

                        if nums[i] == max_potential:

                            max_best = max_potential

                ##  If the current max/min is/are not fixed, then it/they can be changed.

                if max_best == -65536:
                    max_best = max_potential - 1
                if min_best == 65536:
                    min_best = min_potential + 1

                ##  Make changes accordingly.

                for i, d in enumerate(pat_diff):

                    if d == 1:
                        
                        if min_best <= nums[i] and nums[i] < max_best:

                            patterns_final[pat_n][i] += 1

                        elif nums[i] < min_best:

                            patterns_final[pat_n][i] += 1

                        elif nums[i] >= max_best:

                            patterns_final[pat_n][i] -= 1

                res = res + (max(patterns_final[pat_n]) - min(patterns_final[pat_n]),)

        # for x in patterns_final:

        #     print(x)

        return min(res)


    def deduce_pattern_with_fewest_differences(self, nums: List[int]) -> tuple[int, tuple[List[int]]]:

        patterns = self.generate_bit_combinations(len(nums))

        ##print(patterns[0])
        ##print(patterns[1])

        differences = ([0 for i in range(len(nums))],
                        [0 for i in range(len(nums))])

        for pat_n, pat in enumerate(patterns):

            for i, _ in enumerate(pat):

                if nums[i] != pat[i]:

                    differences[pat_n][i] = 1

        res = [sum(differences[0]), sum(differences[1])]

        return res, differences
                    

    def generate_bit_combinations(self, len_nums: int) -> tuple[List[int]]:

        combos = ([(i + 1) % 2 for i in range(len_nums)],
                  [i % 2 for i in range(len_nums)])

        return combos


    def normalise_nums(self, nums: List[int]) -> List[int]:

        toggle = 0

        nums_norm = [0 for _ in range(len(nums))]

        for i, v in enumerate(nums):

            if nums[i] % 2 == toggle:

                nums_norm[i] = toggle

            else:

                nums_norm[i] = 1 - toggle

        return nums_norm
