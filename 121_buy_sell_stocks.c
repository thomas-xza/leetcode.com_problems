#include <limits.h>

int maxProfit(int* prices, int pricesSize) {

    int max_profit = 0;
    int i, j, max, min, test, min_i, max_i;

    int suffix_zeros_cut = 0;

    if (prices[pricesSize - 1] == 0) {

        for (i = pricesSize - 1; i >= 0 ; i--) {

            if (suffix_zeros_cut == 0 && prices[i] == 0)
                pricesSize -= 1;

            if (prices[i] == 0 && prices[i-1] != 0)
                suffix_zeros_cut = 1;

        }
    }

    int check_profitability = 0;

    for (i = 0 ; i < pricesSize - 1 ; i++) {

        if (prices[i + 1] - prices[i] > 0)
            check_profitability += 1;

    }

    if (check_profitability == 0)
        return 0;

    max_i = -1;
    min_i = -1;
    max = INT_MIN;
    min = INT_MAX;


    
    for (i = 0 ; i < pricesSize - 1 ; i++) {

        if (min_i < i) {

            min = prices[i];
        
            // for (j = i ; j < pricesSize ; j++) {

            //     if (prices[j] < min) {
            //         min = prices[j];
            //         min_i = j;
            //     }

            // }

        }

        if (max_i < i) {

            max = prices[i + 1];
        
            for (j = i + 1 ; j < pricesSize ; j++) {

                if (prices[j] > max) {
                    max = prices[j];
                    max_i = j;
                }

            }

        }

        test = max - min;

        if (test > max_profit)
            max_profit = test;

    }

    return max_profit;

}
