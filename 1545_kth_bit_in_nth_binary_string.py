class Solution:

    def findKthBit(self, n: int, k: int) -> str:

        print("(n, k) =", n, k)

        l_seq = self.gen_l_seq(n)
        # k_seq, n = (14,), 4

        k_seq = (k,)
        print(n, k_seq)

        while n > 1:

            k_new = self.gen_k_seq(k_seq[0], n, l_seq)

            n -= 1
            k_seq = (k_new,) + k_seq
            print(n, k_seq)

        return str(self.gen_binary_seq(l_seq, k_seq)[-1])


    def gen_binary_seq(self, l: tuple[int], k_seq: tuple[int]):

        seq = ()

        for i, k in enumerate(k_seq):

            n = i + 1

            if n == 1 and k == 1:
                seq = seq + (0,)
            elif k == -1:
                seq = seq + (1,)
            elif k < l[n - 1]:
                seq = seq + (seq[-1],)
            elif k > l[n - 1] + 1:
                if seq[-1] == 1:
                    seq = seq + (0,)
                elif seq[-1] == 0:
                    seq = seq + (1,)

            print("(n, k, seq) =", n, k, seq)

        return seq


    def gen_k_seq(self, k:int, n:int, l: tuple[int]) -> tuple[int]:

        ##  l[n] = length of string S_n

        if k <= l[n - 1]:
            return k

        elif k == l[n - 1] + 1:
            return -1

        else:
            return l[n - 1] + 1 - (k - l[n-1] - 1)


    def gen_l_seq(self, n: int) -> tuple[int]:

        i, l = 1, 1

        seq = (0, 1)

        while i < n:
            i += 1
            l = l * 2 + 1
            seq = seq + (l,)

        return seq

