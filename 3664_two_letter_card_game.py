
##  This question was hugely misunderstood for a long time... functions have been written and deleted various times in the process.

from copy import deepcopy

class Solution:

    def score(self, cards: List[str], x: str) -> int:

        pairs = 0

        ##  Find all pairs within same type.

        for card_type in range(2):

            cards, new_pairs = self.pair_singles(cards, x, card_type)

            pairs += new_pairs

        print('pairs pre-doubles', pairs)

        card_counts = self.count_cards(cards, x)

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
        

    def pair_singles(self, cards: list[str], x: str, card_type: int) -> tuple[list[str], str]:

        new_cards = []

        x_cards = defaultdict(int)

        for card in cards:
            if card[card_type] == x:
                x_cards[card] += 1
            else:
                new_cards += [card]

        alpha = "abcdefghijklmnopqrstuvwxyz".replace(x, '')

        pairs = 0

        for i, a in enumerate(alpha):
            
            target = f"{x}{a}"

            if card_type == 1:
                target = f"{a}{x}"

            for j, b in enumerate(alpha):

                target2 = f"{x}{b}"

                if card_type == 1:
                    target2 = f"{b}{x}"

                if (target != target2):

                    if x_cards[target] > x_cards[target2]:
                        new_pairs = x_cards[target2]
                    
                    else:
                        new_pairs = x_cards[target]

                    x_cards[target2] -= new_pairs
                    x_cards[target] -= new_pairs
                    pairs += new_pairs
        
        for card, quantity in x_cards.items():
            for _ in range(quantity):
                new_cards += [card]

        return new_cards, pairs



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

    
    # def count_duplicates(self, cards: list[str], x:str) -> int:

    #     alpha = "abcdefghijklmnopqrstuvwxyz"
    #     alpha.replace(x, '')

    #     duplicates_ax = defaultdict(int)
    #     duplicates_xa = defaultdict(int)

    #     extras_xa, extras_ax = 0, 0

    #     for card in cards:
    #         if card[0] == x:
    #             duplicates_xa[card] += 1
    #         elif card[1] == x:
    #             duplicates_xa[card] += 1

    #     for k, v in duplicates_xa.values():
    #         if v > 1:
    #             extras_xa += v - 1

    #     for k, v in duplicates_ax.values():
    #         if v > 1:
    #             extras_ax += v - 1

    #     return ({f"{x}_": extras_xa, f"_{x}": extras_ax})

