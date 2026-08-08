
##  Fails test 837/844; execution limit timeout.

##  The reason is because sorted() is called approximately n/2 times,
##    and Timsort is O(nlogn), so find_two_largest() is a member of O(n^2logn).

##  The function could be changed so that the data is only sorted once,
##    and then statefully maintained thereon, via small adjustments 2n times,
##    but this would need some refactoring.
##    find_two_largest() could then become a member of O(n^2) instead.

##  This question was hugely misunderstood for a long time...
##    functions have been written and deleted various times in the process.
##    So the desire to optimise the algorithm has become diminished.

class Solution:

    def score(self, cards: List[str], x: str) -> int:

        pairs = 0

        ##  Cut all superflous cards.
        cards = list(filter(lambda card: x in card, cards))

        print(cards)

        res = True
        pairs_n = 0

        counts = dict(Counter(cards))

        while res == True and len(cards) > 1:

            res = False

            pair, counts = self.find_two_largest_quantity_pairable(cards, x, counts)

            ##print("Pair selected", pair)

            if pair is not (None, None):
                cards, res, counts = self.remove_pair(cards, pair, counts)

            ##print(counts)

            if res == True:
                pairs_n += 1

        return pairs_n


    def remove_pair(self, cards: list[str], pair: tuple[str], counts: dict[str, int]) -> tuple[list[str], int]:

        if counts[pair[0]] > 0 and counts[pair[1]] > 0:

            for card in pair:
                cards.remove(card)
                counts[card] -= 1
                if counts[card] == 0:
                    counts.pop(card, None)

            return cards, True, counts

        else:
            return cards, False, counts


    def find_two_largest_quantity_pairable(self, cards: List[str], x: str, counts: dict[str, int]) -> tuple[int]:

        ##print(list(counts.items()))

        ##  Need to sort primarily by quantity, and secondarily by type (doubles last).
        ##  This is currently the execution time bottleneck.
        
        sorted_counts = sorted(list(counts.items()), key=lambda x: x[1])

        sorted_counts.reverse()

        subsorted_counts = []
        subsorted_subend = []
        quantity_state = sorted_counts[0][1]

        for (card, card_q) in sorted_counts:

            ##  Card quantity just changed. Append all known doubles to end and empty data structure.

            if card_q != quantity_state:
                subsorted_counts += subsorted_subend
                subsorted_subend = []
                quantity_state = card_q

            if card[0] == card[1]:
                subsorted_subend += [(card, card_q)]
            else:
                subsorted_counts += [(card, card_q)]

        subsorted_counts += subsorted_subend

        for i, (card, card_q) in enumerate(subsorted_counts):

            card_type = self.classify(card, x)

            for j, (card2, card2_q) in enumerate(subsorted_counts):

                card_type2 = self.classify(card2, x)

                if card_q > 0 and card2_q > 0 and card != card2 and (
                    (card_type < 2 and card_type2 < 2 and card_type == card_type2) or
                    (card_type == 2 and card_type2 != 2) or
                    (card_type != 2 and card_type2 == 2)
                ):

                    return (card, card2), counts

        return (None, None), counts


    def classify(self, card: str, x: str) -> int:

        if card[0] == x and card[1] != x:
            return 0  ## f"{x}_"
        elif card[1] == x and card[0] != x:
            return 1  ## f"_{x}"
        else:
            return 2  ## f"{x}{x}"
