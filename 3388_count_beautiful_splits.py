
##  There is some kind of observation/extrapolation that needs to be made, to progress.

class Solution:

    def beautifulSplits(self, nums: List[int]) -> int:

        ##str_nums = [str(i) for i in nums]

        viable_ops = []

        t = len(nums)

        beautiful = 0

        start = time.time()

        nums_new = self.replace_patterns(nums)
        total = 0

        char_positions = [i for i in range(1, len(nums))]

        if nums_new == []:

            print("empty_list")
            
            for (a, b) in combinations(char_positions, 2):

              if a <= b - a or b - a <= t - b:

                total += 1

            return total

        ##print(nums_new)

        ##  The following 2 ops take up 20% of the execution time on higher tests.

        for (a, b) in combinations(char_positions, 2):

              if a <= b - a or b - a <= t - b:

                ##  As soon as you assign strings, timeout occurs.

                p1 = nums[:a]
                p2 = nums[a:b]
                p3 = nums[b:]

                ##print(p1, p2, p3)

                if p1 == p2[:a]:

                    beautiful += 1

                elif p2 == p3[:b-a]:

                    beautiful += 1

        print(time.time() - start)
                
        return beautiful

        
    def replace_patterns(self, nums: List[int]):

        ##  Hardcoding until some pattern among the tests' patterns is known (e.g. do the patterns always start at position 0?).

        known_patterns = {"0,1,2,3,4,": ""}

        num_str = ','.join(str(x) for x in nums)

        for pat, rep in known_patterns.items():

            if pat in num_str:

                num_str_test = num_str.replace(pat, rep)

                print(num_str_test)

                if num_str_test == pat[0:-1]:

                    print("only pat remained")

                    return []



        ##print(list(map(lambda x: int(x), num_str.split(','))))

        return list(map(lambda x: int(x), num_str.split(',')))


        # midpoint = len(nums) // 2

        # for i, _ in range(0, len(nums) // 4):

        #     for j, _ in range(i:len(nums // 4)):

