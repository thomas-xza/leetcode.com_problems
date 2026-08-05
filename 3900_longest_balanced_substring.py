from collections import Counter, defaultdict, OrderedDict
from hashlib import md5

##  "Don't optimise until you've measured." - David Patterson, Computer Organisation

##  Wrote a coherent BFS search, but potentially only a DFS search works for test 963/992.
##  Memory limit exceeded (perhaps I should've seen it coming).

class Solution:

    def longestBalanced(self, s: str) -> int:

        ##print("s:", s)

        if '1' not in s or '0' not in s:
            return 0

        start = time.time()

        bal_string_chks = {}

        ##  Don't exactly need a key-value store, but do want O(1) lookups.

        ss_counts = OrderedDict()

        biggest_str = True

        ##  Generate all substrings in useful order (as opposed to s[i:j]).
        ##  As in, largest string to smallest string.

        if len(s) % 2 == 0:
            init_q = len(s)
        else:
            init_q = len(s) - 1

        ##print("init_q:", init_q)
        
        w_quantity = [0, 0]
        w_quantity_batch = 0

        for q in range(init_q, 0, -2):

            print(w_quantity)

            w_quantity = [w_quantity_batch, w_quantity[0]]
            w_quantity_batch = 0

            while (w_quantity[1] > 0):
                ss_counts.popitem()
                w_quantity[1] -= 1

            running_counter = {'0': 0, '1': 0}
            
            print("window size:", q)

            for i in range(0, len(s)):

                print("ss counts len:", len(ss_counts))

                # print("i:", i)

                ##  Extract substring.

                sub_s = s[i:i + q]

                ##  Simplest sliding window implementation involves a break.

                if len(sub_s) < q:
                    break
                else:
                    w_quantity_batch += 1

                ##print(sub_s)

                ##  Only call Counter() once, then re-use results.

                if biggest_str == True:
                    biggest_str = False
                    ss_counts[self.hsh(sub_s)] = running_counter | dict(Counter(sub_s))

                    ##print(ss_counts)

                if sub_s not in ss_counts:

                    ##  Count 1s and 0s using minimal computation.
                    running_counter, ss_counts = self.calculate_counts(s, sub_s, ss_counts, dict(running_counter), i, q)

                else:
                    ##  Else simply lookup.
                    running_counter = dict(ss_counts[self.hsh(sub_s)])

                ##print("ss_counts:", ss_counts)

                if sub_s not in bal_string_chks:
                    bal_string_chks[sub_s] = self.check_string(s, sub_s, ss_counts[self.hsh(sub_s)], i)

                if bal_string_chks[sub_s] > -1:

                    return bal_string_chks[sub_s]
            
        return 0


    def calculate_counts(self, s: str, sub_s: str, ss_counts: dict[str, int], running_counter: dict[str, int], i: int, q: int) -> tuple[dict[str, int], dict[str, int]]:

        ##  Counter() calls are the biggest bottleneck in the program,
        ##    so this part becomes a lengthy caching workaround.

        ##  If this is a new sliding window size, use count of larger string.

        ##print("sub_s:", sub_s)

        to_prepend, to_append = '', ''
        if i != 0:
            to_prepend = s[i - 2:i]
        if to_prepend == '':
            to_prepend = '__'

        ##print("i + q:", i+q)

        if i + q < len(s):
            to_append = s[i + q:i + q + 2]
        if to_append == '':
            to_append = '__'

        extra_chars = (to_prepend, to_append)

        if running_counter == {'0': 0, '1': 0 }:

            ##print("ss_counts:", ss_counts)

            ##print("extra_chars:", extra_chars)

            ##  Algorithm will look ahead of substring, before behind.

            if self.hsh(f"{extra_chars[0]}{sub_s}") in ss_counts:
                running_counter = dict(ss_counts[self.hsh(f"{extra_chars[0]}{sub_s}")])
                running_counter[extra_chars[0][0]] -= 1
                running_counter[extra_chars[0][1]] -= 1
                ##print("Updating running counter via prepended substring")
                ##print(sub_s, extra_chars, running_counter)
                
            elif self.hsh(f"{sub_s}{extra_chars[1]}") in ss_counts:
                running_counter = dict(ss_counts[self.hsh(f"{sub_s}{extra_chars[1]}")])
                running_counter[extra_chars[1][0]] -= 1
                running_counter[extra_chars[1][1]] -= 1
                ##print("Updating running counter via appended substring")
                ##print(sub_s, extra_chars, running_counter)
            
            else:
                ##  If biggest_str is an odd length the above won't be reached.
                ##  Simplest to call Counter() once more.
                ##print("Running Counter()")
                ss_counts[self.hsh(sub_s)] = Counter(sub_s)


        ##  Else adjust running_counter.
        else:

            ##print("Updating running counter")

            running_counter[s[i-1]] -= 1
            running_counter[sub_s[-1]] += 1

            ##print(sub_s, extra_chars, running_counter)

        ##  Store for potential future lookups.
        ss_counts[self.hsh(sub_s)] = dict(running_counter)

        ##print(ss_counts)

        return running_counter, ss_counts


    def check_string(self, s: str, sub_s: str, counts: dict[str, int], pos: int) -> int:

        target = None

        ##  If equal quantities of 1 and 0, substring is best.

        ##print("counts", counts)

        if counts['0'] == counts['1']:
            return len(sub_s)

        ##  If there is only 1 character difference: viable candidate.

        elif counts['0'] - 1 == counts['1'] + 1:

            target = '1'

        elif counts['0'] + 1 == counts['1'] - 1:

            target = '0'

        ##  Compare with rest of string, seeking a 1 or a 0.

        if target is not None:

            pre_str = s[0:pos]

            post_str = s[(pos + len(sub_s)):]

            if target in pre_str or target in post_str:

                return len(sub_s)

        return -1

    def hsh(self, s: str) -> str:

        ##  Reducing memory consumption of long (1, 0) strings, via hash.
        ##  In exchange for CPU cycles, that is.
        ##  The cutting of md5 

        return s

        return adler32(str.encode(s))

        return md5(s.encode('utf-8')).hexdigest()
    
