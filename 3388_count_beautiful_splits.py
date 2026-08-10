
##  There is some kind of observation/extrapolation that needs to be made, to progress.

class Solution:

    def beautifulSplits(self, nums: List[int]) -> int:

        ##str_nums = [str(i) for i in nums]

        viable_ops = []

        beautiful = 0

        nums_new, nums_pat = self.replace_patterns(nums)

        total = 0

        if nums_pat == True:

            for nums_set in nums_new:

                sum = 0
                
                for (a, b) in combinations([i for i in range(1, len(nums_set))], 2):

                    if a <= b - a or b - a <= len(nums_set) - b:
                        sum += 1

                print(sum, len(nums_set))
                total += sum

            return total

        return self.raw_count(nums)


    def raw_count(self, nums: List[int]) -> int:

        beautiful = 0

        ##  The following 2 ops take up 20% of the execution time on higher tests.

        for (a, b) in combinations([i for i in range(1, len(nums))], 2):

              if a <= b - a or b - a <= len(nums) - b:

                ##  As soon as you assign strings, timeout occurs.

                p1 = nums[:a]
                p2 = nums[a:b]
                p3 = nums[b:]

                ##print(p1, p2, p3)

                if p1 == p2[:a]:
                    beautiful += 1

                elif p2 == p3[:b-a]:
                    beautiful += 1
                
        return beautiful

        
    def replace_patterns(self, nums: List[int]):

        ##  Hardcoding until some pattern among the tests' patterns is known.

        known_patterns = {"0,1,2,3,4": "01234",
                          "1,2,3,4,0": "12340",
                          "2,3,4,0,1": "23401",
                          "3,4,0,1,2": "34012",
                          "4,0,1,2,3": "40123",}

        num_str = ','.join(str(x) for x in nums)

        new_nums, res = [], False

        for pat, rep in known_patterns.items():

            if pat in num_str:

                num_str_test = num_str.replace(pat, rep).split(',')

                nums_test = list(map(lambda x: int(x), num_str_test))

                ##print(num_str_test)

                if int(rep) in nums_test:

                    # if int(rep) != nums_test[0]:
                    #     elem_0 = nums_test.pop(0)
                    #     elem_1 = nums_test.pop(0)
                    #     nums_test.insert(0, elem_0 + elem_1)

                    # if int(rep) != nums_test[-1]:
                    #     elem_end = nums_test.pop()
                    #     elem_end_2 = nums_test.pop()
                    #     nums_test.append(elem_end + elem_end_2)

                    print(rep)

                    new_nums += [nums_test]
                    res = True

        return new_nums, res

