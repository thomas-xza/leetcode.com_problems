
##  This question was hugely misunderstood for a long time... functions have been written and deleted various times in the process.

from copy import deepcopy

class Solution:

    def score(self, cards: List[str], x: str) -> int:

        card_counts = self.count_cards(cards, x)

        duplicates = self.count_duplicates(cards, x)

        # sym_counts = self.symmetric_counts(cards, x)
        # print("sym_counts:", sym_counts)

        pairs = 0

        ##  Find all pairs within same type.

        print("card counts", card_counts)

        for card_type in [f"{x}_", f"_{x}"]:

            pair_singles(f"{x}_")

            new_pairs = (card_counts[card_type] - duplicates[card_type]) // 2
            card_counts[card_type] -= new_pairs
            pairs += new_pairs

        print('pairs pre-doubles', pairs)

        ##  Order remaining single types by quantity available.

        singles = [ [f"{x}_", card_counts[f"{x}_"]],
                               [f"_{x}", card_counts[f"_{x}"]] ]

        doubles = [ [f"{x}{x}", card_counts[f"{x}{x}"]] ]

        for _ in range(2):

            new_pairs = 0

            ##  Pair the doubles with the largest remaining singles.

            singles = self.order_counts(singles)

            print(singles)
            print(doubles)

            if doubles[0][1] > singles[0][1]:
                new_pairs = singles[0][1]
            else:
                new_pairs = doubles[0][1]
            
            singles[0][1] -= new_pairs
            doubles[0][1] -= new_pairs
            pairs += new_pairs

            ##  If no more doubles, nothing more can be done.

            if doubles[0][1] == 0:
                return pairs

        return pairs


    def pair_singles


    def calc_new_pairs(self, counts: list[tuple[str, int]]) -> tuple[list[tuple[str, int]], int]:

        new_pairs = counts[0][1] % 2
        counts[0][1] -= new_pairs

        return counts, new_pairs


    def order_counts(self, counts_in: list[tuple[str, int]]) -> list[tuple[str, int]]:

        counts = sorted(counts_in, key=lambda x: x[1])
        counts.reverse()

        return counts


    def count_cards(self, cards: list[str], target: int) -> dict[str, int]:

        card_count = defaultdict(int)
        alpha = "abcdefghijklmnopqrstuvwxyz"
        char = target

        # for i, char in enumerate(alpha):

        for card in cards:

            if card[0] == char and card[1] == char:
                card_count[f"{char}{char}"] += 1

            elif card[0] == char:
                card_count[f"{char}_"] += 1

            elif card[1] == char:
                card_count[f"_{char}"] += 1

        return card_count    

    
    def count_duplicates(self, cards: list[str], x:str) -> int:

        alpha = "abcdefghijklmnopqrstuvwxyz"
        alpha.replace(x, '')

        duplicates_ax = defaultdict(int)
        duplicates_xa = defaultdict(int)

        extras_xa, extras_ax = 0, 0

        for card in cards:
            if card[0] == x:
                duplicates_xa[card] += 1
            elif card[1] == x:
                duplicates_xa[card] += 1

        for k, v in duplicates_xa.values():
            if v > 1:
                extras_xa += v - 1

        for k, v in duplicates_ax.values():
            if v > 1:
                extras_ax += v - 1

        return ({f"{x}_": extras_xa, f"_{x}": extras_ax})

