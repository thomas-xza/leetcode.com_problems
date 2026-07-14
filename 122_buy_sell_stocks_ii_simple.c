#include <limits.h>

//  Eventually tried Leedcode's "Analysis" AI feature, which gives the solution away.


int suffix_cut(int* prices, int pricesSize);
int chk_profitability(int* prices, int pricesSize);


int maxProfit(int* prices, int pricesSize) {

    int i;  //  start, end, value

    pricesSize = suffix_cut(prices, pricesSize);

    if (chk_profitability(prices, pricesSize) == 0)
        return 0;

    int profit = 0;

    for (i = 0 ; i < pricesSize - 1; i++) {

        if (prices[i+1] > prices[i]) {

            profit += prices[i+1] - prices[i];

        }

    }

    return profit;

}


int suffix_cut(int* prices, int pricesSize) {

    int suffix_zeros_cut = 0;

    if (prices[pricesSize - 1] == 0) {
        for (int i = pricesSize - 1; i >= 0 ; i--) {
            if (suffix_zeros_cut == 0 && prices[i] == 0)
                pricesSize -= 1;
            if (prices[i] == 0 && prices[i-1] != 0)
                suffix_zeros_cut = 1;
        }
    }

    return pricesSize;

}


int chk_profitability(int* prices, int pricesSize) {

    int check_profitability = 0;

    for (int i = 0 ; i < pricesSize - 1 ; i++) {
        if (prices[i + 1] - prices[i] > 0)
            check_profitability += 1;
    }

    return check_profitability;

}
