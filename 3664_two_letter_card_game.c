
##  NOTE: this needs some (currently) unknown kinds of changes, as the wording of question was originally misunderstood.
##  Specifically, the phrase:
##    "Two cards are compatible if the strings differ in exactly 1 position."
##    Is interpreted (by the Leetcode author) to mean that "BA" and "AB" differ in 2 positions.
##  So the following solution needs to be refactored to account for this pain-in-the-nuts edge case.

################################################################################

##  When considering the cards as instances of quantities (AX, XA, AA),
##    and the order in which they are paired between (AX, XA, AA),
##    there are a large quantity of permutations.
##  Consider a > b > c OR a > b = c OR a = b > c.
##  For example, if AX > XA > AA, pairing (AA, AX) and then the remainder, is 1 permutation.
##  Specifically, there seem to be 13 possible variations in quantities,
##    when considering greater-than or equals signs,
##    and 3 possible ways of pairing them, resulting in 39 (13*3) permutations.

##  A proof by exhaustion can be written out fairly quickly,
##    via itertools.permutations([a, b, c], 3).

# (AA, AX, XA)  Pair(AA, AX)    Pair(AX, XA)
# (1, 2, 3)     3               2
# (1, 3, 2)     3               2
# (2, 1, 3)     2               3
# (2, 3, 1)     3               2
# (3, 1, 2)     3               2
# (3, 2, 1)     3               2
# (1, 2, 2)     2               2
# (2, 1, 2)     2               2
# (2, 2, 1)     2               2
# (1, 1, 2)     1               2
# (1, 2, 1)     2               2
# (2, 1, 1)     2               1
# (1, 1, 1)     1               1

##  The hypothesis seems to be to pair whichever is of largest quantity first.
##  We will now test this hypothesis...


class Solution:

    def score(self, cards: List[str], x: str) -> int:

        # raw_card_quants = defaultdict(int)
        # card_count = defaultdict(int)

        # for card in cards:
        #     raw_card_quants[card] += 1

        card_counts = self.count_cards(cards, x)

        counts = order_counts(list(card_counts.items()))

        counts = sorted(counts, key=lambda x: x[1])

        

        new_pairs = counts[1][0]
        counts[0][0] -= new_pairs
        counts[1][0] -= new_pairs
        
        print(counts)

        pairs = 0

        ##  All homo cards need to be matched first, with whichever hetero is more available,
        ##    homo cards cannot be matched together.

        # if target > card_counts[homo]:
        #     new_pairs = card_counts[homo]
        #     card_counts[homo] -= new_pairs
        #     card_counts[target] -= new_pairs
        #     pairs += new_pairs
        # else:
        #     new_pairs = card_counts[target]
        #     card_counts[homo] -= new_pairs
        #     card_counts[target] -= new_pairs
        #     pairs += new_pairs


    def order_counts(counts: list[tuple[str, int]]) -> list[tuple[str, int]]:

        counts = sorted(counts, key=lambda x: x[1])

        counts.reverse()
        


    def count_cards(self, cards: list[str], target) -> dict[str, int]:

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

        # ##  The ordering of the letters is irrelevant, so prevent duplicates.
        # ##  This is an edge case but Leetcode is full of them.

        # alpha = "abcdefghijklmnopqrstuvwxyz"

        # for i, x in enumerate(alpha):
        #     for j in range(i, len(alpha)):

        #         q = raw_card_quants[f"{x}{alpha[j]}"]
        #         if x != alpha[j]:
        #             q += raw_card_quants[f"{alpha[j]}{x}"]

        #         if q != 0:
        #             card_count[f"{x}{alpha[j]}"] = q

        ##letter_count = self.count_letters(dict(card_count))
        ##print(letter_count)


    # def count_letters(self, card_count: dict[str, int]) -> dict[str,int]:

    #     letter_quants = defaultdict(list)

    #     for card, qs in card_count.items():

    #         letter_quants[card[0]] += [card]
    #         if card[1] != card[0]:
    #             letter_quants[card[1]] += [card]

    #     return letter_quants
            
        
